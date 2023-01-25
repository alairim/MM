/*
 * sim_ele.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sim_ele".
 *
 * Model version              : 1.138
 * Simulink Coder version : 9.7 (R2022a) 13-Nov-2021
 * C source code generated on : Wed Jan 18 21:02:23 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sim_ele.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include "sim_ele_private.h"
#include "zero_crossing_types.h"

/* Named constants for Chart: '<Root>/Controller' */
#define sim_ele_IN_DEFAULT             ((uint8_T)1U)
#define sim_ele_IN_EMER_ERR            ((uint8_T)2U)
#define sim_ele_IN_Idel                ((uint8_T)1U)
#define sim_ele_IN_NO_ACTIVE_CHILD     ((uint8_T)0U)
#define sim_ele_IN_Open                ((uint8_T)2U)
#define sim_ele_IN_Run                 ((uint8_T)3U)
#define sim_ele_event_F0               (0)
#define sim_ele_event_F1               (1)
#define sim_ele_event_F2               (2)
#define sim_ele_event_F3               (3)
#define sim_ele_event_F4               (4)
#define sim_ele_event_TIC              (6)
#define sim_ele_event_emergency        (5)

/* Block signals (default storage) */
B_sim_ele_T sim_ele_B;

/* Block states (default storage) */
DW_sim_ele_T sim_ele_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_sim_ele_T sim_ele_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_sim_ele_T sim_ele_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_sim_ele_T sim_ele_Y;

/* Real-time model */
static RT_MODEL_sim_ele_T sim_ele_M_;
RT_MODEL_sim_ele_T *const sim_ele_M = &sim_ele_M_;

/* Forward declaration for local functions */
static real_T sim_ele_setspeed(real_T dir, real_T init_pos, real_T pos, real_T
  des);
static real_T sim_ele_ElevatorDes(real_T dir, uint8_T floor_r, real_T pos);
static void sim_ele_LogicController(void);
static void sim_ele_chartstep_c3_sim_ele(void);

/* Function for Chart: '<Root>/Controller' */
static real_T sim_ele_setspeed(real_T dir, real_T init_pos, real_T pos, real_T
  des)
{
  real_T speed_o;
  if (dir > 0.0) {
    real_T tmp;
    tmp = pos - init_pos;
    if (tmp < 0.2) {
      speed_o = (tmp + 0.001) * 0.3 * 5.0;
    } else {
      tmp = des - pos;
      if (tmp >= 0.2) {
        speed_o = 0.3;
      } else {
        speed_o = tmp * 0.3 * 5.0;
      }
    }
  } else if (dir < 0.0) {
    real_T tmp;
    tmp = init_pos - pos;
    if (tmp < 0.2) {
      speed_o = (tmp + 0.001) * -0.3 * 5.0;
    } else {
      tmp = pos - des;
      if (tmp >= 0.2) {
        speed_o = -0.3;
      } else {
        speed_o = tmp * -0.3 * 5.0;
      }
    }
  } else {
    speed_o = 0.0;
  }

  return speed_o;
}

/* Function for Chart: '<Root>/Controller' */
static real_T sim_ele_ElevatorDes(real_T dir, uint8_T floor_r, real_T pos)
{
  real_T des;
  if (floor_r != 0) {
    if (dir >= 0.0) {
      uint32_T tmp;
      tmp = floor_r & 16U;
      if ((pos >= 3.0) && (tmp != 0U)) {
        des = 4.0;
      } else {
        uint32_T tmp_0;
        tmp_0 = floor_r & 8U;
        if ((pos >= 2.0) && (tmp_0 != 0U)) {
          des = 3.0;
        } else if ((pos >= 2.0) && (tmp != 0U)) {
          des = 4.0;
        } else {
          uint32_T tmp_1;
          tmp_1 = floor_r & 4U;
          if ((pos >= 1.0) && (tmp_1 != 0U)) {
            des = 2.0;
          } else if ((pos >= 1.0) && (tmp_0 != 0U)) {
            des = 3.0;
          } else if ((pos >= 1.0) && (tmp != 0U)) {
            des = 4.0;
          } else if ((pos >= 0.0) && ((floor_r & 2U) != 0U)) {
            des = 1.0;
          } else if ((pos >= 0.0) && (tmp_1 != 0U)) {
            des = 2.0;
          } else if ((pos >= 0.0) && (tmp_0 != 0U)) {
            des = 3.0;
          } else if ((pos >= 0.0) && (tmp != 0U)) {
            des = 4.0;
          } else if ((sim_ele_B.floor_reg & 1U) != 0U) {
            des = 0.0;
          } else {
            des = -1.0;
          }
        }
      }
    } else {
      uint32_T tmp;
      tmp = floor_r & 1U;
      if ((pos <= 1.0) && (tmp != 0U)) {
        des = 0.0;
      } else {
        uint32_T tmp_0;
        tmp_0 = floor_r & 2U;
        if ((pos <= 2.0) && (tmp_0 != 0U)) {
          des = 1.0;
        } else if ((pos <= 2.0) && (tmp != 0U)) {
          des = 0.0;
        } else {
          uint32_T tmp_1;
          tmp_1 = floor_r & 4U;
          if ((pos <= 3.0) && (tmp_1 != 0U)) {
            des = 2.0;
          } else if ((pos <= 3.0) && (tmp_0 != 0U)) {
            des = 1.0;
          } else if ((pos <= 3.0) && (tmp != 0U)) {
            des = 0.0;
          } else if ((pos <= 4.0) && ((floor_r & 8U) != 0U)) {
            des = 3.0;
          } else if ((pos <= 4.0) && (tmp_1 != 0U)) {
            des = 2.0;
          } else if ((pos <= 4.0) && (tmp_0 != 0U)) {
            des = 1.0;
          } else if ((pos <= 4.0) && (tmp != 0U)) {
            des = 0.0;
          } else if ((sim_ele_B.floor_reg & 16U) != 0U) {
            des = 4.0;
          } else {
            des = -1.0;
          }
        }
      }
    }
  } else if ((pos == 0.0) || (pos == 1.0) || (pos == 2.0) || (pos == 3.0) ||
             (pos == 4.0)) {
    des = -1.0;
  } else if (dir >= 0.0) {
    des = ceil(pos);
  } else {
    des = floor(pos);
  }

  return des;
}

/* Function for Chart: '<Root>/Controller' */
static void sim_ele_LogicController(void)
{
  if (sim_ele_DW.is_LogicController == sim_ele_IN_DEFAULT) {
    /* Outport: '<Root>/emer_sig' incorporates:
     *  Inport: '<Root>/position'
     *  Outport: '<Root>/door'
     *  Outport: '<Root>/err_sig'
     *  Outport: '<Root>/speed'
     */
    if (sim_ele_Y.emer_sig || sim_ele_Y.err_sig) {
      if (sim_ele_DW.is_DEFAULT == sim_ele_IN_Open) {
        sim_ele_Y.door = false;
        sim_ele_DW.is_DEFAULT = sim_ele_IN_NO_ACTIVE_CHILD;
      } else {
        sim_ele_DW.is_DEFAULT = sim_ele_IN_NO_ACTIVE_CHILD;
      }

      sim_ele_DW.is_LogicController = sim_ele_IN_EMER_ERR;
      if (sim_ele_DW.cur_dir == 1.0) {
        sim_ele_DW.E_destination = sim_ele_U.position + 0.1;
      } else {
        sim_ele_DW.E_destination = sim_ele_U.position - 0.1;
      }
    } else {
      switch (sim_ele_DW.is_DEFAULT) {
       case sim_ele_IN_Idel:
        if (sim_ele_DW.door_open != 0.0) {
          sim_ele_DW.is_DEFAULT = sim_ele_IN_Open;
          sim_ele_DW.temporalCounter_i1 = 0U;
          sim_ele_DW.door_open = 0.0;
          sim_ele_Y.door = true;
          sim_ele_Y.speed = 0.0;
        } else if ((sim_ele_DW.cur_dir == 1.0) || (sim_ele_DW.cur_dir == -1.0))
        {
          sim_ele_DW.is_DEFAULT = sim_ele_IN_Run;
          sim_ele_DW.init_position = sim_ele_U.position;
        } else if (sim_ele_DW.sfEvent == sim_ele_event_TIC) {
          if (sim_ele_B.floor_reg != 0) {
            sim_ele_DW.destination = sim_ele_ElevatorDes(sim_ele_DW.pre_dir,
              sim_ele_B.floor_reg, sim_ele_U.position);
          } else {
            sim_ele_DW.destination = -1.0;
          }

          if ((sim_ele_DW.destination != -1.0) && (sim_ele_U.position >
               sim_ele_DW.destination - 0.1) && (sim_ele_U.position <
               sim_ele_DW.destination + 0.1)) {
            if (sim_ele_DW.destination == 0.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 254);
            } else if (sim_ele_DW.destination == 1.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 253);
            } else if (sim_ele_DW.destination == 2.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 251);
            } else if (sim_ele_DW.destination == 3.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 247);
            } else if (sim_ele_DW.destination == 4.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 239);
            }

            sim_ele_DW.cur_dir = 0.0;
            sim_ele_DW.door_open = 1.0;
          } else if ((sim_ele_DW.destination != -1.0) && (sim_ele_DW.destination
                      > sim_ele_U.position + 0.1)) {
            sim_ele_DW.cur_dir = 1.0;
          } else if ((sim_ele_DW.destination != -1.0) && (sim_ele_DW.destination
                      < sim_ele_U.position - 0.1)) {
            sim_ele_DW.cur_dir = -1.0;
          } else {
            sim_ele_DW.cur_dir = 0.0;
          }
        }
        break;

       case sim_ele_IN_Open:
        if (sim_ele_DW.temporalCounter_i1 >= 50U) {
          sim_ele_DW.is_DEFAULT = sim_ele_IN_Idel;
          sim_ele_DW.pre_dir = sim_ele_DW.cur_dir;
          sim_ele_DW.cur_dir = 0.0;
          sim_ele_Y.door = false;
          sim_ele_Y.speed = 0.0;
        } else if (sim_ele_DW.sfEvent == sim_ele_event_TIC) {
          if ((sim_ele_U.position > -0.1) && (sim_ele_U.position < 0.1) &&
              ((sim_ele_B.floor_reg & 1U) != 0U)) {
            sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 254);
          } else if ((sim_ele_U.position > 0.9) && (sim_ele_U.position < 1.1) &&
                     ((sim_ele_B.floor_reg & 2U) != 0U)) {
            sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 253);
          } else if ((sim_ele_U.position > 1.9) && (sim_ele_U.position < 2.1) &&
                     ((sim_ele_B.floor_reg & 4U) != 0U)) {
            sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 251);
          } else if ((sim_ele_U.position > 2.9) && (sim_ele_U.position < 3.1) &&
                     ((sim_ele_B.floor_reg & 8U) != 0U)) {
            sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 247);
          } else if ((sim_ele_U.position > 3.9) && (sim_ele_U.position < 4.1) &&
                     ((sim_ele_B.floor_reg & 16U) != 0U)) {
            sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 239);
          }
        }
        break;

       default:
        /* case IN_Run: */
        if (sim_ele_DW.door_open != 0.0) {
          sim_ele_DW.is_DEFAULT = sim_ele_IN_Open;
          sim_ele_DW.temporalCounter_i1 = 0U;
          sim_ele_DW.door_open = 0.0;
          sim_ele_Y.door = true;
          sim_ele_Y.speed = 0.0;
        } else if (sim_ele_DW.sfEvent == sim_ele_event_TIC) {
          if ((sim_ele_U.position > sim_ele_DW.destination - 0.1) &&
              (sim_ele_U.position < sim_ele_DW.destination + 0.1)) {
            if (sim_ele_DW.destination == 0.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 254);
            } else if (sim_ele_DW.destination == 1.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 253);
            } else if (sim_ele_DW.destination == 2.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 251);
            } else if (sim_ele_DW.destination == 3.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 247);
            } else if (sim_ele_DW.destination == 4.0) {
              sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 239);
            }

            sim_ele_DW.door_open = 1.0;
            sim_ele_Y.speed = 0.0;
          } else if (fabs(sim_ele_U.position - sim_ele_DW.destination) < 0.2) {
            sim_ele_Y.speed = sim_ele_setspeed(sim_ele_DW.cur_dir,
              sim_ele_DW.init_position, sim_ele_U.position,
              sim_ele_DW.destination);
          } else {
            sim_ele_DW.destination = sim_ele_ElevatorDes(sim_ele_DW.cur_dir,
              sim_ele_B.floor_reg, sim_ele_U.position);
            sim_ele_Y.speed = sim_ele_setspeed(sim_ele_DW.cur_dir,
              sim_ele_DW.init_position, sim_ele_U.position,
              sim_ele_DW.destination);
          }
        }
        break;
      }
    }

    /* Outport: '<Root>/emer_sig' incorporates:
     *  Inport: '<Root>/position'
     *  Outport: '<Root>/door'
     *  Outport: '<Root>/err_sig'
     *  Outport: '<Root>/speed'
     */
    /* case IN_EMER_ERR: */
  } else if ((!sim_ele_Y.emer_sig) && (!sim_ele_Y.err_sig)) {
    sim_ele_DW.is_LogicController = sim_ele_IN_DEFAULT;
    sim_ele_DW.cur_dir = 0.0;
    sim_ele_DW.door_open = 0.0;
    sim_ele_DW.is_DEFAULT = sim_ele_IN_Idel;
    sim_ele_DW.pre_dir = 0.0;
    sim_ele_Y.door = false;
    sim_ele_Y.speed = 0.0;
  } else {
    sim_ele_Y.speed = sim_ele_setspeed(sim_ele_DW.cur_dir,
      sim_ele_DW.init_position, sim_ele_U.position, sim_ele_DW.E_destination);
  }
}

/* Function for Chart: '<Root>/Controller' */
static void sim_ele_chartstep_c3_sim_ele(void)
{
  /* Chart: '<Root>/Controller' incorporates:
   *  Inport: '<Root>/position'
   *  Outport: '<Root>/emer_sig'
   *  Outport: '<Root>/err_sig'
   */
  if (sim_ele_DW.is_active_c3_sim_ele == 0U) {
    sim_ele_DW.is_active_c3_sim_ele = 1U;
    sim_ele_B.floor_reg = 0U;

    /* Outport: '<Root>/emer_sig' */
    sim_ele_Y.emer_sig = false;
    sim_ele_DW.F0_preTime = -1.0;
    sim_ele_DW.F1_preTime = -1.0;
    sim_ele_DW.F2_preTime = -1.0;
    sim_ele_DW.F3_preTime = -1.0;
    sim_ele_DW.F4_preTime = -1.0;
    sim_ele_DW.is_LogicController = sim_ele_IN_DEFAULT;
    sim_ele_DW.cur_dir = 0.0;
    sim_ele_DW.door_open = 0.0;
    sim_ele_DW.is_DEFAULT = sim_ele_IN_Idel;
    sim_ele_DW.pre_dir = 0.0;

    /* Outport: '<Root>/door' */
    sim_ele_Y.door = false;

    /* Outport: '<Root>/speed' */
    sim_ele_Y.speed = 0.0;
    sim_ele_DW.pre_position = 0.0;

    /* Outport: '<Root>/err_sig' */
    sim_ele_Y.err_sig = false;
  } else {
    if (sim_ele_DW.sfEvent == sim_ele_event_emergency) {
      sim_ele_Y.emer_sig = !sim_ele_Y.emer_sig;
    }

    if (sim_ele_DW.sfEvent == sim_ele_event_F0) {
      if ((sim_ele_B.floor_reg & 1U) == 0U) {
        sim_ele_B.floor_reg |= 1;
        sim_ele_DW.F0_preTime = -1.0;
      } else {
        if ((((sim_ele_M->Timing.clockTick0+sim_ele_M->Timing.clockTickH0*
               4294967296.0)) * 0.1) - sim_ele_DW.F0_preTime <= 1.0) {
          sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 254);
        }

        sim_ele_DW.F0_preTime = (((sim_ele_M->Timing.clockTick0+
          sim_ele_M->Timing.clockTickH0* 4294967296.0)) * 0.1);
      }
    }

    if (sim_ele_DW.sfEvent == sim_ele_event_F1) {
      if ((sim_ele_B.floor_reg & 2U) == 0U) {
        sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg | 2);
        sim_ele_DW.F1_preTime = -1.0;
      } else {
        if ((((sim_ele_M->Timing.clockTick0+sim_ele_M->Timing.clockTickH0*
               4294967296.0)) * 0.1) - sim_ele_DW.F1_preTime <= 1.0) {
          sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 253);
        }

        sim_ele_DW.F1_preTime = (((sim_ele_M->Timing.clockTick0+
          sim_ele_M->Timing.clockTickH0* 4294967296.0)) * 0.1);
      }
    }

    if (sim_ele_DW.sfEvent == sim_ele_event_F2) {
      if ((sim_ele_B.floor_reg & 4U) == 0U) {
        sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg | 4);
        sim_ele_DW.F2_preTime = -1.0;
      } else {
        if ((((sim_ele_M->Timing.clockTick0+sim_ele_M->Timing.clockTickH0*
               4294967296.0)) * 0.1) - sim_ele_DW.F2_preTime <= 1.0) {
          sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 251);
        }

        sim_ele_DW.F2_preTime = (((sim_ele_M->Timing.clockTick0+
          sim_ele_M->Timing.clockTickH0* 4294967296.0)) * 0.1);
      }
    }

    if (sim_ele_DW.sfEvent == sim_ele_event_F3) {
      if ((sim_ele_B.floor_reg & 8U) == 0U) {
        sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg | 8);
        sim_ele_DW.F3_preTime = -1.0;
      } else {
        if ((((sim_ele_M->Timing.clockTick0+sim_ele_M->Timing.clockTickH0*
               4294967296.0)) * 0.1) - sim_ele_DW.F3_preTime <= 1.0) {
          sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 247);
        }

        sim_ele_DW.F3_preTime = (((sim_ele_M->Timing.clockTick0+
          sim_ele_M->Timing.clockTickH0* 4294967296.0)) * 0.1);
      }
    }

    if (sim_ele_DW.sfEvent == sim_ele_event_F4) {
      if ((sim_ele_B.floor_reg & 16U) == 0U) {
        sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg | 16);
        sim_ele_DW.F4_preTime = -1.0;
      } else {
        if ((((sim_ele_M->Timing.clockTick0+sim_ele_M->Timing.clockTickH0*
               4294967296.0)) * 0.1) - sim_ele_DW.F4_preTime <= 1.0) {
          sim_ele_B.floor_reg = (uint8_T)(sim_ele_B.floor_reg & 239);
        }

        sim_ele_DW.F4_preTime = (((sim_ele_M->Timing.clockTick0+
          sim_ele_M->Timing.clockTickH0* 4294967296.0)) * 0.1);
      }
    }

    sim_ele_LogicController();
    if ((sim_ele_U.position < -0.1) || (sim_ele_U.position > 4.1) || (fabs
         (sim_ele_U.position - sim_ele_DW.pre_position) >= 0.3)) {
      sim_ele_Y.err_sig = true;
    } else {
      sim_ele_DW.pre_position = sim_ele_U.position;
    }
  }

  /* End of Chart: '<Root>/Controller' */
}

/* Model step function */
void sim_ele_step(void)
{
  real_T rtb_Clock;
  int32_T i;
  int8_T rtb_inputevents[7];
  boolean_T zcEvent_0;
  ZCEventType zcEvent[7];

  /* DiscretePulseGenerator: '<Root>/Clock' */
  rtb_Clock = (sim_ele_DW.clockTickCounter < sim_ele_P.Clock_Duty) &&
    (sim_ele_DW.clockTickCounter >= 0) ? sim_ele_P.Clock_Amp : 0.0;
  if (sim_ele_DW.clockTickCounter >= sim_ele_P.Clock_Period - 1.0) {
    sim_ele_DW.clockTickCounter = 0;
  } else {
    sim_ele_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Clock' */

  /* Chart: '<Root>/Controller' incorporates:
   *  TriggerPort: '<S1>/input events'
   */
  /* Inport: '<Root>/F0' */
  zcEvent[0] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[0],
                        (sim_ele_U.F0));

  /* Inport: '<Root>/F1' */
  zcEvent[1] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[1],
                        (sim_ele_U.F1));

  /* Inport: '<Root>/F2' */
  zcEvent[2] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[2],
                        (sim_ele_U.F2));

  /* Inport: '<Root>/F3' */
  zcEvent[3] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[3],
                        (sim_ele_U.F3));

  /* Inport: '<Root>/F4' */
  zcEvent[4] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[4],
                        (sim_ele_U.F4));

  /* Inport: '<Root>/Emergency' */
  zcEvent[5] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[5],
                        (sim_ele_U.Emergency));
  zcEvent[6] = rt_ZCFcn(RISING_ZERO_CROSSING,
                        &sim_ele_PrevZCX.Controller_Trig_ZCE[6],
                        (rtb_Clock));
  zcEvent_0 = false;
  for (i = 0; i < 7; i++) {
    zcEvent_0 = (zcEvent_0 || (zcEvent[i] != NO_ZCEVENT));
  }

  if (zcEvent_0) {
    for (i = 0; i < 7; i++) {
      rtb_inputevents[i] = (int8_T)zcEvent[i];
    }

    sim_ele_DW.presentTicks = sim_ele_M->Timing.clockTick0;
    sim_ele_DW.elapsedTicks = sim_ele_DW.presentTicks - sim_ele_DW.previousTicks;
    sim_ele_DW.previousTicks = sim_ele_DW.presentTicks;
    if (sim_ele_DW.temporalCounter_i1 + sim_ele_DW.elapsedTicks <= 63U) {
      sim_ele_DW.temporalCounter_i1 = (uint8_T)(sim_ele_DW.temporalCounter_i1 +
        sim_ele_DW.elapsedTicks);
    } else {
      sim_ele_DW.temporalCounter_i1 = 63U;
    }

    if (rtb_inputevents[0U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_F0;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[1U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_F1;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[2U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_F2;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[3U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_F3;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[4U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_F4;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[5U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_emergency;
      sim_ele_chartstep_c3_sim_ele();
    }

    if (rtb_inputevents[6U] == 1) {
      sim_ele_DW.sfEvent = sim_ele_event_TIC;
      sim_ele_chartstep_c3_sim_ele();
    }
  }

  /* Outport: '<Root>/F0_lamp' incorporates:
   *  DataTypeConversion: '<S2>/Extract Desired Bits'
   */
  sim_ele_Y.F0_lamp = (uint8_T)(sim_ele_B.floor_reg & 1);

  /* Outport: '<Root>/F1_lamp' incorporates:
   *  DataTypeConversion: '<S3>/Extract Desired Bits'
   */
  sim_ele_Y.F1_lamp = (uint8_T)((int32_T)((uint32_T)sim_ele_B.floor_reg >> 1) &
    1);

  /* Outport: '<Root>/F2_lamp' incorporates:
   *  DataTypeConversion: '<S4>/Extract Desired Bits'
   */
  sim_ele_Y.F2_lamp = (uint8_T)((int32_T)((uint32_T)sim_ele_B.floor_reg >> 2) &
    1);

  /* Outport: '<Root>/F3_lamp' incorporates:
   *  DataTypeConversion: '<S5>/Extract Desired Bits'
   */
  sim_ele_Y.F3_lamp = (uint8_T)((int32_T)((uint32_T)sim_ele_B.floor_reg >> 3) &
    1);

  /* Outport: '<Root>/F4_lamp' incorporates:
   *  DataTypeConversion: '<S6>/Extract Desired Bits'
   */
  sim_ele_Y.F4_lamp = (uint8_T)((int32_T)((uint32_T)sim_ele_B.floor_reg >> 4) &
    1);

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  sim_ele_M->Timing.clockTick0++;
  if (!sim_ele_M->Timing.clockTick0) {
    sim_ele_M->Timing.clockTickH0++;
  }
}

/* Model initialize function */
void sim_ele_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)sim_ele_M, 0,
                sizeof(RT_MODEL_sim_ele_T));

  /* block I/O */
  (void) memset(((void *) &sim_ele_B), 0,
                sizeof(B_sim_ele_T));

  /* states (dwork) */
  (void) memset((void *)&sim_ele_DW, 0,
                sizeof(DW_sim_ele_T));

  /* external inputs */
  (void)memset(&sim_ele_U, 0, sizeof(ExtU_sim_ele_T));

  /* external outputs */
  (void)memset(&sim_ele_Y, 0, sizeof(ExtY_sim_ele_T));

  /* Start for DiscretePulseGenerator: '<Root>/Clock' */
  sim_ele_DW.clockTickCounter = 0;

  {
    int32_T i;
    for (i = 0; i < 7; i++) {
      sim_ele_PrevZCX.Controller_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
    }
  }

  /* SystemInitialize for Chart: '<Root>/Controller' */
  sim_ele_DW.is_LogicController = sim_ele_IN_NO_ACTIVE_CHILD;
  sim_ele_DW.is_DEFAULT = sim_ele_IN_NO_ACTIVE_CHILD;
  sim_ele_DW.temporalCounter_i1 = 0U;
  sim_ele_DW.is_active_c3_sim_ele = 0U;
  sim_ele_DW.F0_preTime = 0.0;
  sim_ele_DW.F1_preTime = 0.0;
  sim_ele_DW.F2_preTime = 0.0;
  sim_ele_DW.F3_preTime = 0.0;
  sim_ele_DW.F4_preTime = 0.0;
  sim_ele_DW.cur_dir = 0.0;
  sim_ele_DW.destination = 0.0;
  sim_ele_DW.pre_dir = 0.0;
  sim_ele_DW.door_open = 0.0;
  sim_ele_DW.init_position = 0.0;
  sim_ele_DW.pre_position = 0.0;
  sim_ele_DW.E_destination = 0.0;

  /* SystemInitialize for Outport: '<Root>/emer_sig' incorporates:
   *  Chart: '<Root>/Controller'
   */
  sim_ele_Y.emer_sig = false;

  /* SystemInitialize for Outport: '<Root>/door' incorporates:
   *  Chart: '<Root>/Controller'
   */
  sim_ele_Y.door = false;

  /* SystemInitialize for Chart: '<Root>/Controller' */
  sim_ele_B.floor_reg = 0U;

  /* SystemInitialize for Outport: '<Root>/err_sig' incorporates:
   *  Chart: '<Root>/Controller'
   */
  sim_ele_Y.err_sig = false;

  /* SystemInitialize for Outport: '<Root>/speed' incorporates:
   *  Chart: '<Root>/Controller'
   */
  sim_ele_Y.speed = 0.0;

  /* SystemInitialize for Chart: '<Root>/Controller' */
  sim_ele_DW.presentTicks = 0U;
  sim_ele_DW.elapsedTicks = 0U;
  sim_ele_DW.previousTicks = 0U;

  /* Enable for Chart: '<Root>/Controller' */
  sim_ele_DW.presentTicks = sim_ele_M->Timing.clockTick0;
  sim_ele_DW.previousTicks = sim_ele_DW.presentTicks;
}

/* Model terminate function */
void sim_ele_terminate(void)
{
  /* (no terminate code required) */
}
