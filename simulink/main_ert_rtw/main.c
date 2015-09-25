/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: main.c
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

#include "main.h"
#include "main_private.h"

/* Block signals (auto storage) */
B_main_T main_B;

/* Block states (auto storage) */
DW_main_T main_DW;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_main_T main_Y;

/* Real-time model */
RT_MODEL_main_T main_M_;
RT_MODEL_main_T *const main_M = &main_M_;
real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model step function */
void main_step(void)
{
  char_T *sErr;
  int32_T samplesRead;
  int32_T samplesRead_0;
  int32_T samplesRead_1;
  int32_T samplesRead_2;
  int32_T samplesRead_3;
  int32_T samplesRead_4;
  int32_T samplesRead_5;
  int32_T samplesRead_6;
  int32_T samplesRead_7;
  int32_T samplesRead_8;
  real_T rtb_Memory_idx_0;

  /* S-Function (sdspFromNetwork): '<S20>/Accelerometer' */
  sErr = GetErrorBuffer(&main_DW.Accelerometer_NetworkLib[0U]);
  samplesRead = 3;
  LibOutputs_Network(&main_DW.Accelerometer_NetworkLib[0U], &main_Y.acc[0U],
                     &samplesRead);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Accelerometer_o2 = (uint16_T)samplesRead;
  if (samplesRead == 0) {
    main_Y.acc[0] = 0.0;
    main_Y.acc[1] = 0.0;
    main_Y.acc[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S20>/Accelerometer' */

  /* S-Function (sdspFromNetwork): '<S21>/Gyrometer' */
  sErr = GetErrorBuffer(&main_DW.Gyrometer_NetworkLib[0U]);
  samplesRead_0 = 3;
  LibOutputs_Network(&main_DW.Gyrometer_NetworkLib[0U], &main_Y.gyro[0U],
                     &samplesRead_0);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Gyrometer_o2 = (uint16_T)samplesRead_0;
  if (samplesRead_0 == 0) {
    main_Y.gyro[0] = 0.0;
    main_Y.gyro[1] = 0.0;
    main_Y.gyro[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S21>/Gyrometer' */

  /* S-Function (sdspFromNetwork): '<S22>/Magnetometer' */
  sErr = GetErrorBuffer(&main_DW.Magnetometer_NetworkLib[0U]);
  samplesRead_1 = 3;
  LibOutputs_Network(&main_DW.Magnetometer_NetworkLib[0U], &main_Y.mag[0U],
                     &samplesRead_1);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Magnetometer_o2 = (uint16_T)samplesRead_1;
  if (samplesRead_1 == 0) {
    main_Y.mag[0] = 0.0;
    main_Y.mag[1] = 0.0;
    main_Y.mag[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S22>/Magnetometer' */

  /* S-Function (sdspFromNetwork): '<S7>/GPS' */
  sErr = GetErrorBuffer(&main_DW.GPS_NetworkLib[0U]);
  samplesRead_2 = 3;
  LibOutputs_Network(&main_DW.GPS_NetworkLib[0U], &main_Y.gps[0U],
                     &samplesRead_2);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.GPS_o2 = (uint16_T)samplesRead_2;
  if (samplesRead_2 == 0) {
    main_Y.gps[0] = 0.0;
    main_Y.gps[1] = 0.0;
    main_Y.gps[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S7>/GPS' */

  /* S-Function (sdspFromNetwork): '<S2>/Barometer' */
  sErr = GetErrorBuffer(&main_DW.Barometer_NetworkLib[0U]);
  samplesRead_3 = 3;
  LibOutputs_Network(&main_DW.Barometer_NetworkLib[0U], &main_Y.baro[0U],
                     &samplesRead_3);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Barometer_o2 = (uint16_T)samplesRead_3;
  if (samplesRead_3 == 0) {
    main_Y.baro[0] = 0.0;
    main_Y.baro[1] = 0.0;
    main_Y.baro[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S2>/Barometer' */

  /* S-Function (sdspFromNetwork): '<S4>/Distance sensor' */
  sErr = GetErrorBuffer(&main_DW.Distancesensor_NetworkLib[0U]);
  samplesRead_4 = 3;
  LibOutputs_Network(&main_DW.Distancesensor_NetworkLib[0U], &main_Y.dist[0U],
                     &samplesRead_4);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Distancesensor_o2 = (uint16_T)samplesRead_4;
  if (samplesRead_4 == 0) {
    main_Y.dist[0] = 0.0;
    main_Y.dist[1] = 0.0;
    main_Y.dist[2] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S4>/Distance sensor' */

  /* S-Function (sdspFromNetwork): '<S13>/RC channels' */
  sErr = GetErrorBuffer(&main_DW.RCchannels_NetworkLib[0U]);
  samplesRead_5 = 13;
  LibOutputs_Network(&main_DW.RCchannels_NetworkLib[0U], &main_Y.rc[0U],
                     &samplesRead_5);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.RCchannels_o2 = (uint16_T)samplesRead_5;
  if (samplesRead_5 == 0) {
    memset(&main_Y.rc[0], 0, 13U * sizeof(real_T));
  }

  /* End of S-Function (sdspFromNetwork): '<S13>/RC channels' */

  /* Memory: '<S16>/Memory' */
  rtb_Memory_idx_0 = main_DW.Memory_PreviousInput[0];

  /* MATLAB Function: '<S16>/Blom AHRS' */
  /* MATLAB Function 'Attitude estimator/Blom AHRS/Blom AHRS': '<S17>:1' */
  /* '<S17>:1:8' */
  /* '<S17>:1:9' */
  /* '<S17>:1:10' */
  /* '<S17>:1:13' */
  /* '<S17>:1:14' */
  main_B.rtb_Phi_idx_0 = (rtb_Memory_idx_0 - main_Y.gyro[0] * 0.02) * 0.98 +
    (114.59155902616465 * rt_atan2d_snf(main_Y.acc[1], -main_Y.acc[2]) -
     rtb_Memory_idx_0) * 0.020000000000000018;

  /* Outport: '<Root>/omega' incorporates:
   *  MATLAB Function: '<S16>/Blom AHRS'
   */
  /* '<S17>:1:16' */
  main_Y.omega[0] = main_Y.gyro[0];
  main_Y.omega[1] = main_Y.gyro[1];
  main_Y.omega[2] = main_Y.gyro[2];

  /* ManualSwitch: '<Root>/Controller switch' */
  /* MATLAB Function 'Controller/Rate LQ/MATLAB Function': '<S19>:1' */
  /* '<S19>:1:4' */
  if (main_P.Controllerswitch_CurrentSetting == 1) {
    /* Outport: '<Root>/motor_u' incorporates:
     *  MATLAB Function: '<S18>/MATLAB Function'
     */
    main_Y.motor_u[0] = 0.0;
    main_Y.motor_u[1] = 0.0;
    main_Y.motor_u[2] = 0.0;
    main_Y.motor_u[3] = 0.0;
  } else {
    /* Outport: '<Root>/motor_u' */
    main_Y.motor_u[0] = main_Y.rc[0];
    main_Y.motor_u[1] = main_Y.rc[1];
    main_Y.motor_u[2] = main_Y.rc[2];
    main_Y.motor_u[3] = main_Y.rc[3];
  }

  /* End of ManualSwitch: '<Root>/Controller switch' */

  /* Outport: '<Root>/Phi' */
  main_Y.Phi[0] = main_B.rtb_Phi_idx_0;
  main_Y.Phi[1] = 0.0;
  main_Y.Phi[2] = 0.0;

  /* Outport: '<Root>/P' incorporates:
   *  MATLAB Function: '<S12>/MATLAB Function'
   */
  /* MATLAB Function 'Position estimator/MATLAB Function': '<S24>:1' */
  /* '<S24>:1:4' */
  /* '<S24>:1:5' */
  main_Y.P[0] = 0.0;
  main_Y.P[1] = 0.0;
  main_Y.P[2] = 0.0;

  /* Outport: '<Root>/V' incorporates:
   *  MATLAB Function: '<S12>/MATLAB Function'
   */
  main_Y.V[0] = 0.0;
  main_Y.V[1] = 0.0;
  main_Y.V[2] = 0.0;

  /* MATLAB Function: '<S15>/Triggered for 3 s' incorporates:
   *  Memory: '<S15>/Memory'
   */
  /* MATLAB Function 'Motor output/PWM converter': '<S23>:1' */
  /* '<S23>:1:3' */
  /* '<S23>:1:4' */
  /* '<S23>:1:7' */
  /* MATLAB Function 'Terminate if ch 7 is triggered for 3 s/Triggered for 3 s': '<S25>:1' */
  /* '<S25>:1:2' */
  rtb_Memory_idx_0 = 0.0;

  /* '<S25>:1:3' */
  if (main_Y.rc[6] > 0.5) {
    /* '<S25>:1:4' */
    /* '<S25>:1:5' */
    main_B.time_up = main_DW.Memory_PreviousInput_e + 0.02;
    if (main_DW.Memory_PreviousInput_e + 0.02 > 3.0) {
      /* '<S25>:1:6' */
      /* '<S25>:1:7' */
      rtb_Memory_idx_0 = 1.0;
    }
  } else {
    /* '<S25>:1:10' */
    main_B.time_up = 0.0;
  }

  /* Stop: '<S15>/Stop Simulation' */
  if (rtb_Memory_idx_0 != 0.0) {
    rtmSetStopRequested(main_M, 1);
  }

  /* End of Stop: '<S15>/Stop Simulation' */

  /* S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */
  sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib[0U]);
  samplesRead_6 = 4;
  LibOutputs_Network(&main_DW.ExtController_NetworkLib[0U], &main_Y.extctrl[0U],
                     &samplesRead_6);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.ExtController_o2 = (uint16_T)samplesRead_6;
  if (samplesRead_6 == 0) {
    main_Y.extctrl[0] = 0.0;
    main_Y.extctrl[1] = 0.0;
    main_Y.extctrl[2] = 0.0;
    main_Y.extctrl[3] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */

  /* S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */
  sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib_a[0U]);
  samplesRead_7 = 2;
  LibOutputs_Network(&main_DW.ExtController_NetworkLib_a[0U], &main_Y.extcom[0U],
                     &samplesRead_7);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.ExtController_o2_m = (uint16_T)samplesRead_7;
  if (samplesRead_7 == 0) {
    main_Y.extcom[0] = 0.0;
    main_Y.extcom[1] = 0.0;
  }

  /* End of S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Sin: '<Root>/Sine Wave'
   */
  rtb_Memory_idx_0 = floor(sin(((real_T)main_DW.counter + main_P.SineWave_Offset)
    * 2.0 * 3.1415926535897931 / main_P.SineWave_NumSamp) * main_P.SineWave_Amp
    + main_P.SineWave_Bias);
  if (rtIsNaN(rtb_Memory_idx_0) || rtIsInf(rtb_Memory_idx_0)) {
    rtb_Memory_idx_0 = 0.0;
  } else {
    rtb_Memory_idx_0 = fmod(rtb_Memory_idx_0, 256.0);
  }

  main_B.DataTypeConversion = (uint8_T)(rtb_Memory_idx_0 < 0.0 ? (int32_T)
    (uint8_T)-(int8_T)(uint8_T)-rtb_Memory_idx_0 : (int32_T)(uint8_T)
    rtb_Memory_idx_0);

  /* End of DataTypeConversion: '<Root>/Data Type Conversion' */

  /* DiscretePulseGenerator: '<S9>/Pulse Generator' */
  rtb_Memory_idx_0 = (main_DW.clockTickCounter < main_P.PulseGenerator_Duty) &&
    (main_DW.clockTickCounter >= 0) ? main_P.PulseGenerator_Amp : 0.0;
  if (main_DW.clockTickCounter >= main_P.PulseGenerator_Period - 1.0) {
    main_DW.clockTickCounter = 0;
  } else {
    main_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S9>/Pulse Generator' */

  /* S-Function (armcortexa_LedWrite_sfcn): '<S9>/Model running indicator' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   */
  MW_ledWrite(main_P.Modelrunningindicator_p1, rtb_Memory_idx_0 != 0.0);

  /* S-Function (sdspFromNetwork): '<S14>/Simulation stop' */
  sErr = GetErrorBuffer(&main_DW.Simulationstop_NetworkLib[0U]);
  samplesRead_8 = 1;
  LibOutputs_Network(&main_DW.Simulationstop_NetworkLib[0U],
                     &main_B.Simulationstop_o1, &samplesRead_8);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  main_B.Simulationstop_o2 = (uint16_T)samplesRead_8;
  if (samplesRead_8 == 0) {
    main_B.Simulationstop_o1 = false;
  }

  /* End of S-Function (sdspFromNetwork): '<S14>/Simulation stop' */

  /* Stop: '<S14>/Stop Simulation' */
  if (main_B.Simulationstop_o1) {
    rtmSetStopRequested(main_M, 1);
  }

  /* End of Stop: '<S14>/Stop Simulation' */

  /* Update for Memory: '<S16>/Memory' */
  main_DW.Memory_PreviousInput[0] = main_B.rtb_Phi_idx_0;
  main_DW.Memory_PreviousInput[1] = 0.0;
  main_DW.Memory_PreviousInput[2] = 0.0;

  /* Update for S-Function (sdspToNetwork): '<S10>/Motor control signals' */
  sErr = GetErrorBuffer(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
  LibUpdate_Network(&main_DW.Motorcontrolsignals_NetworkLib[0U],
                    &main_Y.motor_u[0U], 4);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S10>/Motor control signals' */

  /* Update for Memory: '<S15>/Memory' incorporates:
   *  MATLAB Function: '<S15>/Triggered for 3 s'
   */
  main_DW.Memory_PreviousInput_e = main_B.time_up;

  /* Update for Sin: '<Root>/Sine Wave' */
  main_DW.counter++;
  if (main_DW.counter == main_P.SineWave_NumSamp) {
    main_DW.counter = 0;
  }

  /* End of Update for Sin: '<Root>/Sine Wave' */

  /* Update for S-Function (sdspToNetwork): '<Root>/UDP Send' */
  sErr = GetErrorBuffer(&main_DW.UDPSend_NetworkLib[0U]);
  LibUpdate_Network(&main_DW.UDPSend_NetworkLib[0U], &main_B.DataTypeConversion,
                    1);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<Root>/UDP Send' */

  /* Update for S-Function (sdspToNetwork): '<S11>/Pac keeper' incorporates:
   *  Constant: '<S11>/Pace constant'
   */
  sErr = GetErrorBuffer(&main_DW.Packeeper_NetworkLib[0U]);
  LibUpdate_Network(&main_DW.Packeeper_NetworkLib[0U],
                    &main_P.Paceconstant_Value, 1);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  /* End of Update for S-Function (sdspToNetwork): '<S11>/Pac keeper' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(main_M->rtwLogInfo, (&main_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.02s, 0.0s] */
    if ((rtmGetTFinal(main_M)!=-1) &&
        !((rtmGetTFinal(main_M)-main_M->Timing.taskTime0) >
          main_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(main_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++main_M->Timing.clockTick0)) {
    ++main_M->Timing.clockTickH0;
  }

  main_M->Timing.taskTime0 = main_M->Timing.clockTick0 *
    main_M->Timing.stepSize0 + main_M->Timing.clockTickH0 *
    main_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void main_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)main_M, 0,
                sizeof(RT_MODEL_main_T));
  rtmSetTFinal(main_M, 900.0);
  main_M->Timing.stepSize0 = 0.02;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    main_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(main_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(main_M->rtwLogInfo, (NULL));
    rtliSetLogT(main_M->rtwLogInfo, "");
    rtliSetLogX(main_M->rtwLogInfo, "");
    rtliSetLogXFinal(main_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(main_M->rtwLogInfo, "_rt");
    rtliSetLogFormat(main_M->rtwLogInfo, 2);
    rtliSetLogMaxRows(main_M->rtwLogInfo, 0);
    rtliSetLogDecimation(main_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &main_Y.acc[0],
        &main_Y.gyro[0],
        &main_Y.mag[0],
        &main_Y.gps[0],
        &main_Y.baro[0],
        &main_Y.dist[0],
        &main_Y.rc[0],
        &main_Y.extctrl[0],
        &main_Y.extcom[0],
        &main_Y.motor_u[0],
        &main_Y.Phi[0],
        &main_Y.omega[0],
        &main_Y.P[0],
        &main_Y.V[0]
      };

      rtliSetLogYSignalPtrs(main_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        3,
        3,
        3,
        3,
        3,
        3,
        13,
        4,
        2,
        4,
        3,
        3,
        3,
        3
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        3, 1,
        3, 1,
        3, 1,
        3, 1,
        3, 1,
        3, 1,
        13, 1,
        4, 1,
        2, 1,
        4, 1,
        3,
        3,
        3,
        3
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL), (NULL),
        (NULL),
        (NULL),
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4, 4,
        4,
        4,
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "main/acc",
        "main/gyro",
        "main/mag",
        "main/gps",
        "main/baro",
        "main/dist",
        "main/rc",
        "main/extctrl",
        "main/extcom",
        "main/motor_u",
        "main/Phi",
        "main/omega",
        "main/P",
        "main/V" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          14,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(main_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[4] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[5] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[6] = &rt_LoggedOutputWidths[3];
      rt_LoggedCurrentSignalDimensions[7] = &rt_LoggedOutputWidths[3];
      rt_LoggedCurrentSignalDimensions[8] = &rt_LoggedOutputWidths[4];
      rt_LoggedCurrentSignalDimensions[9] = &rt_LoggedOutputWidths[4];
      rt_LoggedCurrentSignalDimensions[10] = &rt_LoggedOutputWidths[5];
      rt_LoggedCurrentSignalDimensions[11] = &rt_LoggedOutputWidths[5];
      rt_LoggedCurrentSignalDimensions[12] = &rt_LoggedOutputWidths[6];
      rt_LoggedCurrentSignalDimensions[13] = &rt_LoggedOutputWidths[6];
      rt_LoggedCurrentSignalDimensions[14] = &rt_LoggedOutputWidths[7];
      rt_LoggedCurrentSignalDimensions[15] = &rt_LoggedOutputWidths[7];
      rt_LoggedCurrentSignalDimensions[16] = &rt_LoggedOutputWidths[8];
      rt_LoggedCurrentSignalDimensions[17] = &rt_LoggedOutputWidths[8];
      rt_LoggedCurrentSignalDimensions[18] = &rt_LoggedOutputWidths[9];
      rt_LoggedCurrentSignalDimensions[19] = &rt_LoggedOutputWidths[9];
      rt_LoggedCurrentSignalDimensions[20] = &rt_LoggedOutputWidths[10];
      rt_LoggedCurrentSignalDimensions[21] = &rt_LoggedOutputWidths[11];
      rt_LoggedCurrentSignalDimensions[22] = &rt_LoggedOutputWidths[12];
      rt_LoggedCurrentSignalDimensions[23] = &rt_LoggedOutputWidths[13];
    }

    rtliSetLogY(main_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &main_B), 0,
                sizeof(B_main_T));

  /* states (dwork) */
  (void) memset((void *)&main_DW, 0,
                sizeof(DW_main_T));

  /* external outputs */
  (void) memset((void *)&main_Y, 0,
                sizeof(ExtY_main_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(main_M->rtwLogInfo, 0.0, rtmGetTFinal(main_M),
    main_M->Timing.stepSize0, (&rtmGetErrorStatus(main_M)));

  {
    char_T *sErr;

    /* Start for S-Function (sdspFromNetwork): '<S20>/Accelerometer' */
    sErr = GetErrorBuffer(&main_DW.Accelerometer_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Accelerometer_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Accelerometer_NetworkLib[0U], 0, "0.0.0.0",
                        22001, "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Accelerometer_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Accelerometer_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S20>/Accelerometer' */

    /* Start for S-Function (sdspFromNetwork): '<S21>/Gyrometer' */
    sErr = GetErrorBuffer(&main_DW.Gyrometer_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Gyrometer_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Gyrometer_NetworkLib[0U], 0, "0.0.0.0", 22002,
                        "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Gyrometer_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Gyrometer_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S21>/Gyrometer' */

    /* Start for S-Function (sdspFromNetwork): '<S22>/Magnetometer' */
    sErr = GetErrorBuffer(&main_DW.Magnetometer_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Magnetometer_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Magnetometer_NetworkLib[0U], 0, "0.0.0.0",
                        22003, "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Magnetometer_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Magnetometer_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S22>/Magnetometer' */

    /* Start for S-Function (sdspFromNetwork): '<S7>/GPS' */
    sErr = GetErrorBuffer(&main_DW.GPS_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.GPS_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.GPS_NetworkLib[0U], 0, "0.0.0.0", 22005,
                        "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.GPS_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.GPS_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S7>/GPS' */

    /* Start for S-Function (sdspFromNetwork): '<S2>/Barometer' */
    sErr = GetErrorBuffer(&main_DW.Barometer_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Barometer_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Barometer_NetworkLib[0U], 0, "0.0.0.0", 22004,
                        "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Barometer_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Barometer_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S2>/Barometer' */

    /* Start for S-Function (sdspFromNetwork): '<S4>/Distance sensor' */
    sErr = GetErrorBuffer(&main_DW.Distancesensor_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Distancesensor_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Distancesensor_NetworkLib[0U], 0, "0.0.0.0",
                        22006, "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Distancesensor_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Distancesensor_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S4>/Distance sensor' */

    /* Start for S-Function (sdspFromNetwork): '<S13>/RC channels' */
    sErr = GetErrorBuffer(&main_DW.RCchannels_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.RCchannels_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.RCchannels_NetworkLib[0U], 0, "0.0.0.0", 22101,
                        "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.RCchannels_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.RCchannels_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S13>/RC channels' */

    /* Start for S-Function (sdspToNetwork): '<S10>/Motor control signals' */
    sErr = GetErrorBuffer(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Motorcontrolsignals_NetworkLib[0U], 1,
                        "255.255.255.255", -1, "127.0.0.1", 25002, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S10>/Motor control signals' */

    /* Start for S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */
    sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.ExtController_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.ExtController_NetworkLib[0U], 0, "0.0.0.0",
                        22102, "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.ExtController_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.ExtController_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */

    /* Start for S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */
    sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib_a[0U]);
    CreateUDPInterface(&main_DW.ExtController_NetworkLib_a[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.ExtController_NetworkLib_a[0U], 0, "0.0.0.0",
                        22201, "0.0.0.0", -1, 8192, 8, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.ExtController_NetworkLib_a[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.ExtController_NetworkLib_a[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */

    /* Start for S-Function (sdspToNetwork): '<Root>/UDP Send' */
    sErr = GetErrorBuffer(&main_DW.UDPSend_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.UDPSend_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.UDPSend_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "192.168.7.1", 27001, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.UDPSend_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.UDPSend_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<Root>/UDP Send' */

    /* Start for DiscretePulseGenerator: '<S9>/Pulse Generator' */
    main_DW.clockTickCounter = 0;

    /* Start for S-Function (armcortexa_LedWrite_sfcn): '<S9>/Model running indicator' */
    MW_ledInit(main_P.Modelrunningindicator_p1);

    /* Start for S-Function (sdspToNetwork): '<S11>/Pac keeper' */
    sErr = GetErrorBuffer(&main_DW.Packeeper_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Packeeper_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Packeeper_NetworkLib[0U], 1, "255.255.255.255",
                        -1, "127.0.0.1", 25001, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Packeeper_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Packeeper_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspToNetwork): '<S11>/Pac keeper' */

    /* Start for S-Function (sdspFromNetwork): '<S14>/Simulation stop' */
    sErr = GetErrorBuffer(&main_DW.Simulationstop_NetworkLib[0U]);
    CreateUDPInterface(&main_DW.Simulationstop_NetworkLib[0U]);
    if (*sErr == 0) {
      LibCreate_Network(&main_DW.Simulationstop_NetworkLib[0U], 0, "0.0.0.0",
                        26001, "0.0.0.0", -1, 8192, 1, 0);
    }

    if (*sErr == 0) {
      LibStart(&main_DW.Simulationstop_NetworkLib[0U]);
    }

    if (*sErr != 0) {
      DestroyUDPInterface(&main_DW.Simulationstop_NetworkLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(main_M, sErr);
        rtmSetStopRequested(main_M, 1);
      }
    }

    /* End of Start for S-Function (sdspFromNetwork): '<S14>/Simulation stop' */

    /* InitializeConditions for Memory: '<S16>/Memory' */
    main_DW.Memory_PreviousInput[0] = main_P.Memory_X0[0];
    main_DW.Memory_PreviousInput[1] = main_P.Memory_X0[1];
    main_DW.Memory_PreviousInput[2] = main_P.Memory_X0[2];

    /* InitializeConditions for Memory: '<S15>/Memory' */
    main_DW.Memory_PreviousInput_e = main_P.Memory_X0_c;

    /* InitializeConditions for Sin: '<Root>/Sine Wave' */
    main_DW.counter = 0;
  }
}

/* Model terminate function */
void main_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspFromNetwork): '<S20>/Accelerometer' */
  sErr = GetErrorBuffer(&main_DW.Accelerometer_NetworkLib[0U]);
  LibTerminate(&main_DW.Accelerometer_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Accelerometer_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Accelerometer_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S20>/Accelerometer' */

  /* Terminate for S-Function (sdspFromNetwork): '<S21>/Gyrometer' */
  sErr = GetErrorBuffer(&main_DW.Gyrometer_NetworkLib[0U]);
  LibTerminate(&main_DW.Gyrometer_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Gyrometer_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Gyrometer_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S21>/Gyrometer' */

  /* Terminate for S-Function (sdspFromNetwork): '<S22>/Magnetometer' */
  sErr = GetErrorBuffer(&main_DW.Magnetometer_NetworkLib[0U]);
  LibTerminate(&main_DW.Magnetometer_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Magnetometer_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Magnetometer_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S22>/Magnetometer' */

  /* Terminate for S-Function (sdspFromNetwork): '<S7>/GPS' */
  sErr = GetErrorBuffer(&main_DW.GPS_NetworkLib[0U]);
  LibTerminate(&main_DW.GPS_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.GPS_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.GPS_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S7>/GPS' */

  /* Terminate for S-Function (sdspFromNetwork): '<S2>/Barometer' */
  sErr = GetErrorBuffer(&main_DW.Barometer_NetworkLib[0U]);
  LibTerminate(&main_DW.Barometer_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Barometer_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Barometer_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S2>/Barometer' */

  /* Terminate for S-Function (sdspFromNetwork): '<S4>/Distance sensor' */
  sErr = GetErrorBuffer(&main_DW.Distancesensor_NetworkLib[0U]);
  LibTerminate(&main_DW.Distancesensor_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Distancesensor_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Distancesensor_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S4>/Distance sensor' */

  /* Terminate for S-Function (sdspFromNetwork): '<S13>/RC channels' */
  sErr = GetErrorBuffer(&main_DW.RCchannels_NetworkLib[0U]);
  LibTerminate(&main_DW.RCchannels_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.RCchannels_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.RCchannels_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S13>/RC channels' */

  /* Terminate for S-Function (sdspToNetwork): '<S10>/Motor control signals' */
  sErr = GetErrorBuffer(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
  LibTerminate(&main_DW.Motorcontrolsignals_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Motorcontrolsignals_NetworkLib[0U], 1);
  DestroyUDPInterface(&main_DW.Motorcontrolsignals_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S10>/Motor control signals' */

  /* Terminate for S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */
  sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib[0U]);
  LibTerminate(&main_DW.ExtController_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.ExtController_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.ExtController_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S6>/Ext. Controller' */

  /* Terminate for S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */
  sErr = GetErrorBuffer(&main_DW.ExtController_NetworkLib_a[0U]);
  LibTerminate(&main_DW.ExtController_NetworkLib_a[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.ExtController_NetworkLib_a[0U], 0);
  DestroyUDPInterface(&main_DW.ExtController_NetworkLib_a[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S5>/Ext. Controller' */

  /* Terminate for S-Function (sdspToNetwork): '<Root>/UDP Send' */
  sErr = GetErrorBuffer(&main_DW.UDPSend_NetworkLib[0U]);
  LibTerminate(&main_DW.UDPSend_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.UDPSend_NetworkLib[0U], 1);
  DestroyUDPInterface(&main_DW.UDPSend_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<Root>/UDP Send' */

  /* Terminate for S-Function (armcortexa_LedWrite_sfcn): '<S9>/Model running indicator' */
  MW_ledTerminate(main_P.Modelrunningindicator_p1);

  /* Terminate for S-Function (sdspToNetwork): '<S11>/Pac keeper' */
  sErr = GetErrorBuffer(&main_DW.Packeeper_NetworkLib[0U]);
  LibTerminate(&main_DW.Packeeper_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Packeeper_NetworkLib[0U], 1);
  DestroyUDPInterface(&main_DW.Packeeper_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspToNetwork): '<S11>/Pac keeper' */

  /* Terminate for S-Function (sdspFromNetwork): '<S14>/Simulation stop' */
  sErr = GetErrorBuffer(&main_DW.Simulationstop_NetworkLib[0U]);
  LibTerminate(&main_DW.Simulationstop_NetworkLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(main_M, sErr);
    rtmSetStopRequested(main_M, 1);
  }

  LibDestroy(&main_DW.Simulationstop_NetworkLib[0U], 0);
  DestroyUDPInterface(&main_DW.Simulationstop_NetworkLib[0U]);

  /* End of Terminate for S-Function (sdspFromNetwork): '<S14>/Simulation stop' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
