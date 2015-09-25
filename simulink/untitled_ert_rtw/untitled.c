/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: untitled.c
 *
 * Code generated for Simulink model 'untitled'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Jun 25 14:19:49 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  /* S-Function (armcortexa_LedWrite_sfcn): '<Root>/LED' incorporates:
   *  Constant: '<Root>/Constant'
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   */
  MW_ledWrite(untitled_P.LED_p1, untitled_P.Constant_Value != 0.0);
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(untitled_M, (NULL));

  /* Start for S-Function (armcortexa_LedWrite_sfcn): '<Root>/LED' */
  MW_ledInit(untitled_P.LED_p1);
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* Terminate for S-Function (armcortexa_LedWrite_sfcn): '<Root>/LED' */
  MW_ledTerminate(untitled_P.LED_p1);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
