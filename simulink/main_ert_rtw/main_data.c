/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: main_data.c
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

/* Block parameters (auto storage) */
P_main_T main_P = {
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S16>/Constant'
                                        */

  /*  Expression: [0 0 0]'
   * Referenced by: '<S16>/Memory'
   */
  { 0.0, 0.0, 0.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S15>/Memory'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  10.0,                                /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  5.0,                                 /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S9>/Pulse Generator'
                                        */
  1,                                   /* Computed Parameter: Paceconstant_Value
                                        * Referenced by: '<S11>/Pace constant'
                                        */
  0U,                                  /* Computed Parameter: Controllerswitch_CurrentSetting
                                        * Referenced by: '<Root>/Controller switch'
                                        */

  /*  Expression: deviceFile
   * Referenced by: '<S9>/Model running indicator'
   */
  { 98U, 101U, 97U, 103U, 108U, 101U, 98U, 111U, 110U, 101U, 58U, 103U, 114U,
    101U, 101U, 110U, 58U, 117U, 115U, 114U, 48U, 0U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
