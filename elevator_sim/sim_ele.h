/*
 * sim_ele.h
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

#ifndef RTW_HEADER_sim_ele_h_
#define RTW_HEADER_sim_ele_h_
#ifndef sim_ele_COMMON_INCLUDES_
#define sim_ele_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* sim_ele_COMMON_INCLUDES_ */

#include "sim_ele_types.h"
#include "rt_zcfcn.h"
#include <string.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  uint8_T floor_reg;                   /* '<Root>/Controller' */
} B_sim_ele_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T F0_preTime;                   /* '<Root>/Controller' */
  real_T F1_preTime;                   /* '<Root>/Controller' */
  real_T F2_preTime;                   /* '<Root>/Controller' */
  real_T F3_preTime;                   /* '<Root>/Controller' */
  real_T F4_preTime;                   /* '<Root>/Controller' */
  real_T cur_dir;                      /* '<Root>/Controller' */
  real_T destination;                  /* '<Root>/Controller' */
  real_T pre_dir;                      /* '<Root>/Controller' */
  real_T door_open;                    /* '<Root>/Controller' */
  real_T init_position;                /* '<Root>/Controller' */
  real_T pre_position;                 /* '<Root>/Controller' */
  real_T E_destination;                /* '<Root>/Controller' */
  int32_T clockTickCounter;            /* '<Root>/Clock' */
  int32_T sfEvent;                     /* '<Root>/Controller' */
  uint32_T presentTicks;               /* '<Root>/Controller' */
  uint32_T elapsedTicks;               /* '<Root>/Controller' */
  uint32_T previousTicks;              /* '<Root>/Controller' */
  uint8_T is_active_c3_sim_ele;        /* '<Root>/Controller' */
  uint8_T is_LogicController;          /* '<Root>/Controller' */
  uint8_T is_DEFAULT;                  /* '<Root>/Controller' */
  uint8_T temporalCounter_i1;          /* '<Root>/Controller' */
} DW_sim_ele_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Controller_Trig_ZCE[7];   /* '<Root>/Controller' */
} PrevZCX_sim_ele_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T F0;                           /* '<Root>/F0' */
  real_T F1;                           /* '<Root>/F1' */
  real_T F2;                           /* '<Root>/F2' */
  real_T F3;                           /* '<Root>/F3' */
  real_T F4;                           /* '<Root>/F4' */
  real_T Emergency;                    /* '<Root>/Emergency' */
  real_T position;                     /* '<Root>/position' */
} ExtU_sim_ele_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T emer_sig;                  /* '<Root>/emer_sig' */
  boolean_T door;                      /* '<Root>/door' */
  uint8_T F0_lamp;                     /* '<Root>/F0_lamp' */
  uint8_T F1_lamp;                     /* '<Root>/F1_lamp' */
  uint8_T F2_lamp;                     /* '<Root>/F2_lamp' */
  uint8_T F3_lamp;                     /* '<Root>/F3_lamp' */
  uint8_T F4_lamp;                     /* '<Root>/F4_lamp' */
  boolean_T err_sig;                   /* '<Root>/err_sig' */
  real_T speed;                        /* '<Root>/speed' */
} ExtY_sim_ele_T;

/* Parameters (default storage) */
struct P_sim_ele_T_ {
  real_T Clock_Amp;                    /* Expression: 1
                                        * Referenced by: '<Root>/Clock'
                                        */
  real_T Clock_Period;                 /* Computed Parameter: Clock_Period
                                        * Referenced by: '<Root>/Clock'
                                        */
  real_T Clock_Duty;                   /* Computed Parameter: Clock_Duty
                                        * Referenced by: '<Root>/Clock'
                                        */
  real_T Clock_PhaseDelay;             /* Expression: 0
                                        * Referenced by: '<Root>/Clock'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sim_ele_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
  } Timing;
};

/* Block parameters (default storage) */
extern P_sim_ele_T sim_ele_P;

/* Block signals (default storage) */
extern B_sim_ele_T sim_ele_B;

/* Block states (default storage) */
extern DW_sim_ele_T sim_ele_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_sim_ele_T sim_ele_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_sim_ele_T sim_ele_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_sim_ele_T sim_ele_Y;

/* Model entry point functions */
extern void sim_ele_initialize(void);
extern void sim_ele_step(void);
extern void sim_ele_terminate(void);

/* Real-time Model object */
extern RT_MODEL_sim_ele_T *const sim_ele_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'sim_ele'
 * '<S1>'   : 'sim_ele/Controller'
 * '<S2>'   : 'sim_ele/Extract Bits'
 * '<S3>'   : 'sim_ele/Extract Bits1'
 * '<S4>'   : 'sim_ele/Extract Bits2'
 * '<S5>'   : 'sim_ele/Extract Bits3'
 * '<S6>'   : 'sim_ele/Extract Bits4'
 */
#endif                                 /* RTW_HEADER_sim_ele_h_ */
