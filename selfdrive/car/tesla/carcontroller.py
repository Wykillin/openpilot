from common.numpy_fast import clip, interp
from selfdrive.car.tesla.teslacan import TeslaCAN
from opendbc.can.packer import CANPacker
from selfdrive.car.tesla.values import CANBUS, CarControllerParams

class CarController():
  def __init__(self, dbc_name, CP, VM):
    self.CP = CP
    self.last_angle = 0
    self.packer = CANPacker(dbc_name)
    self.tesla_can = TeslaCAN(dbc_name, self.packer)

  def update(self, enabled, CS, frame, actuators, cruise_cancel):
    can_sends = []

    # Temp disable steering on a hands_on_fault, and allow for user override
    # TODO: better user blending
    hands_on_fault = (CS.steer_warning == "EAC_ERROR_HANDS_ON" and CS.hands_on_level >= 3)
    lkas_enabled = enabled and (not hands_on_fault)

    if lkas_enabled:
      apply_angle = actuators.steeringAngleDeg

      # Janky user torque blending
      if CS.hands_on_level >= 1:
        req_angle_diff = apply_angle - CS.out.steeringAngleDeg
        apply_angle = CS.out.steeringAngleDeg + clip(req_angle_diff * 0.2, -1, 1)

      # Angular rate limit based on speed
      steer_up = (self.last_angle * apply_angle > 0. and abs(apply_angle) > abs(self.last_angle))
      rate_limit = CarControllerParams.RATE_LIMIT_UP if steer_up else CarControllerParams.RATE_LIMIT_DOWN
      max_angle_diff = interp(CS.out.vEgo, rate_limit.speed_points, rate_limit.max_angle_diff_points)
      apply_angle = clip(apply_angle, (self.last_angle - max_angle_diff), (self.last_angle + max_angle_diff))

      # To not fault the EPS
      apply_angle = clip(apply_angle, (CS.out.steeringAngleDeg - 20), (CS.out.steeringAngleDeg + 20))
    else:
      apply_angle = CS.out.steeringAngleDeg

    self.last_angle = apply_angle
    can_sends.append(self.tesla_can.create_steering_control(apply_angle, lkas_enabled, frame))

    # Cancel when openpilot is not enabled anymore
    if not enabled and bool(CS.out.cruiseState.enabled):
      cruise_cancel = True

    if ((frame % 10) == 0 and cruise_cancel):
      # Spam every possible counter value, otherwise it might not be accepted
      # Sending the counters in reverse is better for the RX checking logic in the ECU
      for counter in range(15, -1, -1):
        can_sends.append(self.tesla_can.create_action_request(CS.msg_stw_actn_req, cruise_cancel, CANBUS.chassis, counter))
        can_sends.append(self.tesla_can.create_action_request(CS.msg_stw_actn_req, cruise_cancel, CANBUS.autopilot, counter))

    # TODO: HUD control

    return can_sends
