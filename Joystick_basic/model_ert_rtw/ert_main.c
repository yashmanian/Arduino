/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'model'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Mar 07 12:09:18 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model.h"
#include "rtwtypes.h"
#include <ext_work.h>
#include <ext_svr.h>
#include <ext_share.h>
#include <updown.h>

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  sei();
  model_step();

  /* Get model outputs here */
  cli();
  OverrunFlag--;
  rtExtModeCheckEndTrigger();
}

int main(void)
{
  volatile boolean_T runModel = 1;
  float modelBaseRate = 0.2;
  float systemClock = 0;
  init();
  MW_Arduino_Init();
  rtmSetErrorStatus(model_M, 0);

  /* initialize external mode */
  rtParseArgsForExtMode(0, NULL);
  model_initialize();
  sei();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(model_M));
  rtExtModeCheckInit(1);

  {
    boolean_T rtmStopReq = false;
    rtExtModeWaitForStartPkt(model_M->extModeInfo, 1, &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(model_M, true);
    }
  }

  rtERTExtModeStartMsg();
  cli();
  configureArduinoAVRTimer();
  runModel =
    (rtmGetErrorStatus(model_M) == (NULL)) && !rtmGetStopRequested(model_M);
  sei();
  sei();
  while (runModel) {
    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModeOneStep(model_M->extModeInfo, 1, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(model_M, true);
      }
    }

    runModel =
      (rtmGetErrorStatus(model_M) == (NULL)) && !rtmGetStopRequested(model_M);
  }

  rtExtModeShutdown(1);

  /* Disable rt_OneStep() here */

  /* Terminate model */
  model_terminate();
  cli();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
