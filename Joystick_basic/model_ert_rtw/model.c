/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.c
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
#include "model_private.h"
#include "model_dt.h"

/* Block signals (auto storage) */
B_model_T model_B;

/* Block states (auto storage) */
DW_model_T model_DW;

/* Real-time model */
RT_MODEL_model_T model_M_;
RT_MODEL_model_T *const model_M = &model_M_;

/* Model step function */
void model_step(void)
{
  /* S-Function (Joystick_basic): '<Root>/S-Function Builder' */
  Joystick_basic_Outputs_wrapper( &model_B.SFunctionBuilder_o1,
    &model_B.SFunctionBuilder_o2 );

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.2s, 0.0s] */
    rtExtModeUpload(0, model_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(model_M)!=-1) &&
        !((rtmGetTFinal(model_M)-model_M->Timing.taskTime0) >
          model_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(model_M, "Simulation finished");
    }

    if (rtmGetStopRequested(model_M)) {
      rtmSetErrorStatus(model_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  model_M->Timing.taskTime0 =
    (++model_M->Timing.clockTick0) * model_M->Timing.stepSize0;
}

/* Model initialize function */
void model_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)model_M, 0,
                sizeof(RT_MODEL_model_T));
  rtmSetTFinal(model_M, -1);
  model_M->Timing.stepSize0 = 0.2;

  /* External mode info */
  model_M->Sizes.checksums[0] = (3983173539U);
  model_M->Sizes.checksums[1] = (2932289502U);
  model_M->Sizes.checksums[2] = (3088870061U);
  model_M->Sizes.checksums[3] = (2976910005U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(model_M->extModeInfo,
      &model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(model_M->extModeInfo, model_M->Sizes.checksums);
    rteiSetTPtr(model_M->extModeInfo, rtmGetTPtr(model_M));
  }

  /* block I/O */
  (void) memset(((void *) &model_B), 0,
                sizeof(B_model_T));

  /* states (dwork) */
  (void) memset((void *)&model_DW, 0,
                sizeof(DW_model_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    model_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;
  }
}

/* Model terminate function */
void model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
