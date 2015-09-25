/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: main.h
 *
 * Code generated for Simulink model 'main'.
 *
 * Model version                  : 1.89
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Wed Aug 12 13:42:19 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_main_h_
#define RTW_HEADER_main_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef main_COMMON_INCLUDES_
# define main_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_logging.h"
#include "HostLib_Network.h"
#include "MW_led_lct.h"
#endif                                 /* main_COMMON_INCLUDES_ */

#include "main_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T time_up;
  real_T rtb_Phi_idx_0;
  uint16_T Accelerometer_o2;           /* '<S20>/Accelerometer' */
  uint16_T Gyrometer_o2;               /* '<S21>/Gyrometer' */
  uint16_T Magnetometer_o2;            /* '<S22>/Magnetometer' */
  uint16_T GPS_o2;                     /* '<S7>/GPS' */
  uint16_T Barometer_o2;               /* '<S2>/Barometer' */
  uint16_T Distancesensor_o2;          /* '<S4>/Distance sensor' */
  uint16_T RCchannels_o2;              /* '<S13>/RC channels' */
  uint16_T ExtController_o2;           /* '<S6>/Ext. Controller' */
  uint16_T ExtController_o2_m;         /* '<S5>/Ext. Controller' */
  uint16_T Simulationstop_o2;          /* '<S14>/Simulation stop' */
  uint8_T DataTypeConversion;          /* '<Root>/Data Type Conversion' */
  boolean_T Simulationstop_o1;         /* '<S14>/Simulation stop' */
} B_main_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Accelerometer_NetworkLib[137];/* '<S20>/Accelerometer' */
  real_T Gyrometer_NetworkLib[137];    /* '<S21>/Gyrometer' */
  real_T Magnetometer_NetworkLib[137]; /* '<S22>/Magnetometer' */
  real_T GPS_NetworkLib[137];          /* '<S7>/GPS' */
  real_T Barometer_NetworkLib[137];    /* '<S2>/Barometer' */
  real_T Distancesensor_NetworkLib[137];/* '<S4>/Distance sensor' */
  real_T RCchannels_NetworkLib[137];   /* '<S13>/RC channels' */
  real_T Memory_PreviousInput[3];      /* '<S16>/Memory' */
  real_T Motorcontrolsignals_NetworkLib[137];/* '<S10>/Motor control signals' */
  real_T Memory_PreviousInput_e;       /* '<S15>/Memory' */
  real_T ExtController_NetworkLib[137];/* '<S6>/Ext. Controller' */
  real_T ExtController_NetworkLib_a[137];/* '<S5>/Ext. Controller' */
  real_T UDPSend_NetworkLib[137];      /* '<Root>/UDP Send' */
  real_T Packeeper_NetworkLib[137];    /* '<S11>/Pac keeper' */
  real_T Simulationstop_NetworkLib[137];/* '<S14>/Simulation stop' */
  int32_T counter;                     /* '<Root>/Sine Wave' */
  int32_T clockTickCounter;            /* '<S9>/Pulse Generator' */
} DW_main_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T acc[3];                       /* '<Root>/acc' */
  real_T gyro[3];                      /* '<Root>/gyro' */
  real_T mag[3];                       /* '<Root>/mag' */
  real_T gps[3];                       /* '<Root>/gps' */
  real_T baro[3];                      /* '<Root>/baro' */
  real_T dist[3];                      /* '<Root>/dist' */
  real_T rc[13];                       /* '<Root>/rc' */
  real_T extctrl[4];                   /* '<Root>/extctrl' */
  real_T extcom[2];                    /* '<Root>/extcom' */
  real_T motor_u[4];                   /* '<Root>/motor_u' */
  real_T Phi[3];                       /* '<Root>/Phi' */
  real_T omega[3];                     /* '<Root>/omega' */
  real_T P[3];                         /* '<Root>/P' */
  real_T V[3];                         /* '<Root>/V' */
} ExtY_main_T;

/* Parameters (auto storage) */
struct P_main_T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S16>/Constant'
                                        */
  real_T Memory_X0[3];                 /* Expression: [0 0 0]'
                                        * Referenced by: '<S16>/Memory'
                                        */
  real_T Memory_X0_c;                  /* Expression: 0
                                        * Referenced by: '<S15>/Memory'
                                        */
  real_T SineWave_Amp;                 /* Expression: 100
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_Bias;                /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_NumSamp;             /* Expression: 100
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_Offset;              /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  int8_T Paceconstant_Value;           /* Computed Parameter: Paceconstant_Value
                                        * Referenced by: '<S11>/Pace constant'
                                        */
  uint8_T Controllerswitch_CurrentSetting;/* Computed Parameter: Controllerswitch_CurrentSetting
                                           * Referenced by: '<Root>/Controller switch'
                                           */
  uint8_T Modelrunningindicator_p1[22];/* Expression: deviceFile
                                        * Referenced by: '<S9>/Model running indicator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_main_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_main_T main_P;

/* Block signals (auto storage) */
extern B_main_T main_B;

/* Block states (auto storage) */
extern DW_main_T main_DW;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_main_T main_Y;

/* Model entry point functions */
extern void main_initialize(void);
extern void main_step(void);
extern void main_terminate(void);

/* Real-time Model object */
extern RT_MODEL_main_T *const main_M;

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
 * '<Root>' : 'main'
 * '<S1>'   : 'main/Attitude estimator'
 * '<S2>'   : 'main/Barometer'
 * '<S3>'   : 'main/Controller'
 * '<S4>'   : 'main/Distance sensor'
 * '<S5>'   : 'main/Ext. commands'
 * '<S6>'   : 'main/Ext. controller'
 * '<S7>'   : 'main/GPS'
 * '<S8>'   : 'main/IMU'
 * '<S9>'   : 'main/Model running indicator'
 * '<S10>'  : 'main/Motor output'
 * '<S11>'  : 'main/Pace keeper'
 * '<S12>'  : 'main/Position estimator'
 * '<S13>'  : 'main/RC channels'
 * '<S14>'  : 'main/Simulation stopper from UDP'
 * '<S15>'  : 'main/Terminate if ch 7 is triggered for 3 s'
 * '<S16>'  : 'main/Attitude estimator/Blom AHRS'
 * '<S17>'  : 'main/Attitude estimator/Blom AHRS/Blom AHRS'
 * '<S18>'  : 'main/Controller/Rate LQ'
 * '<S19>'  : 'main/Controller/Rate LQ/MATLAB Function'
 * '<S20>'  : 'main/IMU/Accelerometer'
 * '<S21>'  : 'main/IMU/Gyrometer'
 * '<S22>'  : 'main/IMU/Magnetometer'
 * '<S23>'  : 'main/Motor output/PWM converter'
 * '<S24>'  : 'main/Position estimator/MATLAB Function'
 * '<S25>'  : 'main/Terminate if ch 7 is triggered for 3 s/Triggered for 3 s'
 */
#endif                                 /* RTW_HEADER_main_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
