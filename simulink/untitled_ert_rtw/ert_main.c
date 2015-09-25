/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "untitled.h"
#include "untitled_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "linuxinitialize.h"

volatile boolean_T runModel = 1;
sem_t stopSem;
sem_t termSem;
sem_t baserateTaskSem;
pthread_t terminateThread;
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
int subratePriority[0];
void baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(untitled_M) == (NULL));
  while (runModel) {
    sem_wait(&baserateTaskSem);
    untitled_step();

    /* Get model outputs here */
    runModel = (rtmGetErrorStatus(untitled_M) == (NULL));
  }

  sem_post(&termSem);
  pthread_exit((void *)0);
}

void exitTask(int sig)
{
  rtmSetErrorStatus(untitled_M, "stopping the model");
}

void terminateTask(void *arg)
{
  int i;
  int ret;
  sem_wait(&termSem);
  terminatingmodel = 1;
  printf("**terminating the model**\n");
  fflush(stdout);

  /* Wait for baseRate task to complete */
  ret = pthread_join(baseRateThread, (void *)&threadJoinStatus);
  CHECK_STATUS(ret, 0, "pthread_join");

  /* Disable rt_OneStep() here */

  /* Terminate model */
  untitled_terminate();
  sem_post(&stopSem);
}

int main(int argc, char **argv)
{
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(untitled_M, 0);

  /* Initialize model */
  untitled_initialize();

  /* Call RTOS Initialization funcation */
  myRTOSInit(0.02, 0);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
