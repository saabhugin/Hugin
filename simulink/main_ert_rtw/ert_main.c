/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
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

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "main_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "rt_logging.h"
#include "linuxinitialize.h"
#define QUOTE1(name)                   #name
#define QUOTE(name)                    QUOTE1(name)              /* need to expand name */
#ifndef SAVEFILE
# define MATFILE2(file)                #file ".mat"
# define MATFILE1(file)                MATFILE2(file)
# define MATFILE                       MATFILE1(MODEL)
#else
# define MATFILE                       QUOTE(SAVEFILE)
#endif

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
  runModel = (rtmGetErrorStatus(main_M) == (NULL)) && !rtmGetStopRequested
    (main_M);
  while (runModel) {
    sem_wait(&baserateTaskSem);
    main_step();

    /* Get model outputs here */
    runModel = (rtmGetErrorStatus(main_M) == (NULL)) && !rtmGetStopRequested
      (main_M);
  }

  sem_post(&termSem);
  pthread_exit((void *)0);
}

void exitTask(int sig)
{
  rtmSetErrorStatus(main_M, "stopping the model");
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
  rt_StopDataLogging(MATFILE, main_M->rtwLogInfo);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  main_terminate();
  sem_post(&stopSem);
}

int main(int argc, char **argv)
{
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(main_M, 0);

  /* Initialize model */
  main_initialize();

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
