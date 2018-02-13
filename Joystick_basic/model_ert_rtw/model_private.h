/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model_private.h
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

#ifndef RTW_HEADER_model_private_h_
#define RTW_HEADER_model_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

extern void Joystick_basic_Outputs_wrapper(real_T *X,
  real_T *Y);

#endif                                 /* RTW_HEADER_model_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
