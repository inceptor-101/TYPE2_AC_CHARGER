/**********************************************************************
* Code: Control/Mathematical Tools typically used in power electronics control
* Programing Language: Embedded C
* Author: Veer Karan Goyal
**********************************************************************/
#include <GTSI_1Phase1MPPT.h>    // Main include file
#include <math.h>


float PIController1(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;
    }
    else{

        Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
        PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


        if (PIControllerOutput > UpperLimit)
        {
            PIControllerOutput = UpperLimit;
        }
        else if (PIControllerOutput < LowerLimit)
        {
            PIControllerOutput = LowerLimit;
        }

        if (resettable == 1)
        {
            if (PIControllerOutput >= UpperLimitforReset)
            {
                PIControllerOutput = resetValue;
            }
        }

        errPreviousValue = error;
    }
    return PIControllerOutput;
}

float PIController2(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
}

float fourQuadtanInverse(float y, float x)
{
    static float phi = 0.0;
    // applying four quadrant tan inverse: Start
    phi = atan(y/x);

    if (y <= 0 && x >= 0)     // fourth quadrant -> no change
    {
      phi = phi;
    }
    else if (y >= 0 && x >= 0)// first quadrant -> no change
    {
      phi = phi;
    }
    else if ( y >= 0 && x <= 0)// second quadrant -> add pi to get positive phi value
    {
      phi = phi + 3.1416;
    }
    else                          // third quadrant -> subtract pi to get negative phi value
    {
      phi = phi - 3.1416;
    }

    return phi;
    // applying four quadrant tan inverse: End
}

void HarmonicOscillator(float omega, float *sine, float *cosine)
{
    static float theta = 0.0;
    static float omegap = 0.0;

    theta = theta + ((Ts/2)*(omega + omegap));
    if (theta >= 6.2832)
    {
      theta = 0;
    }

    omegap = omega;
    *sine = sin(theta);
    *cosine = cos(theta);
}

   // single phase PLL code
   // List of inputs required:
   // input signal, sampleTime (minimum = 12.5 us, maximum = 1500 us).
   // list of outputs:
   // Amplitude, frequency, sinTheta (phase synchronized with fundamental component of input signal), cosTheta (90 deg leading to fundamental component of input signal)
   // Minimum frequency of the input signal: 41 Hz, Maximum frequency of the input signal: 66 Hz

Uint16 singlePhasePll_ipPhaseA(float sampleTime, float ipSignal, float *Amplitude, float *frequency, float *sinTheta, float *cosTheta)
{
    static float Kp_pll=100.0;
    static float Ki_pll=2000.0;
    static float omegaMax = 418.4;   // 66.6 Hz X 2 * pi
    static float omegaMin = 250.0;   // 40 Hz
    static float freq = 50.0;
    static float omega = 314.16;
    static float cycleTime = 0.02;
    static float sampleDelayFloat = 500.0;
    static float QuarterSampleDelayFloat = 125.0;
    static Uint16 QuarterSampleDelayInt = 125;
    static Uint16 sampleDelayInt = 500;
    static float ipSignalBuffer[500];
    static Uint16 index = 0;
    static int16 n1 = 0;
    static int16 n2 = 0;
    static Uint16 firstSamplesCycleComplete = 0;
    static float fq = 0.0;
    static float fd = 0.0;
    static float fqe = 0.0;
    static float fde = 0.0;
    static float sine = 0.0;
    static float cosine = 1.0;
    static float phi = 0.0;
    static float Ts = 0.0;

    if (sampleTime < 12.5 || sampleTime > 1500.0)
    {
        *Amplitude = 0.0;
        *frequency = 0.0;
        *sinTheta = 0.0;
        *cosTheta = 0.0;
        return 0;
    }
    else
    {

        Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
        // Calculating Number of Samples to be delayed: Start
        // computing cycle time from angular frequency: START
        freq = omega/6.2832;
        cycleTime = 1.0/freq;

        // computing cycle time from angular frequency: END
        // Computing samples equivalent cycleTime to cycleTime/4 delay: START, Inputs- cycleTime, Ts (sampling time)
        sampleDelayFloat = cycleTime/(Ts);
        QuarterSampleDelayFloat = sampleDelayFloat/4.0;

        // Computing samples equivalent to T/4 delay: END, Outputs- sampleDelayFloat
        // rounding of sampleDelayFloat and QuarterSampleDelayFloat to nearest integer: START, Input- sampleDelayFloat, QuarterSampleDelayFloat
        QuarterSampleDelayInt   = QuarterSampleDelayFloat;
        QuarterSampleDelayFloat = QuarterSampleDelayFloat - QuarterSampleDelayInt;
        if (QuarterSampleDelayFloat > 0.5)
        {
          QuarterSampleDelayInt = QuarterSampleDelayInt + 1;
        }

        sampleDelayInt   = sampleDelayFloat;
        sampleDelayFloat = sampleDelayFloat - sampleDelayInt;
        if (sampleDelayFloat > 0.5)
        {
          sampleDelayInt = sampleDelayInt + 1;
        }
        // rounding of sampleDelayFloat to nearest integer: END, Output- sampleDelayInt, QuarterSampleDelayInt
        // Calculating Number of Samples to be delayed: End

        // Preparing buffer for input signal T/4 delay: Start
        ipSignalBuffer[index] = ipSignal;
        index= index+1;
        if (index == 500)
        {
          index = 0;
        }

        n1 = index-QuarterSampleDelayInt;
        n2 = index + (500 - QuarterSampleDelayInt);

        if ((index == 499) && (firstSamplesCycleComplete == 0))
        {
          firstSamplesCycleComplete = 1;
        }
        // Preparing buffer for input signal T/4 delay: End

        // Single Phase to Two Phase Transformation using T/4 Delay: Start
        if (firstSamplesCycleComplete==0)
        {
          fq = 0;
        }
        else if (index >= QuarterSampleDelayInt)
        {
          fq = ipSignalBuffer[n1];
        }
        else if (index < QuarterSampleDelayInt)
        {
          fq = ipSignalBuffer[n2];
        }
        // Single Phase to Two Phase Transformation using T/4 Delay: End


        // Feeding input signal to d axis: Start
        fd = ipSignal;
        // Feeding input signal to d axis: End


        // Transformation to positively rotating reference frame: Start
        fqe = fd*cosine + fq*sine;
        fde = fd*sine   - fq*cosine;
        // Transformation to positively rotating reference frame: End
        // Note: This transformation aligns input signal with sine output of PLL

        // applying four quadrant tan inverse: Start
        phi = fourQuadtanInverse(fqe, fde);
        // applying four quadrant tan inverse: End

        // PI Controller + VCO if quarter cycle is complete
        if (firstSamplesCycleComplete==1)
        {
          HarmonicOscillator(omega, &sine, &cosine);
          omega = PIController1(sampleTime, phi, Kp_pll, Ki_pll, omegaMax, omegaMin, 0, 1000.0, 0, 0);

        }

        *Amplitude = fde;
        *frequency = freq;
        *sinTheta = sine;
        *cosTheta = cosine;
        return 1;
    }
}

float PRController1(float sampleTime, float omega,float error, float Kp, float Kr, float UpperLimit, float LowerLimit, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float errPreviousToPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PRControllerOutput = 0.0;
    static float x = 0.0;
    static float pr_p = 0.0;
    static float pr_r = 0.0;
    static float pr_rp = 0.0;
    static float pr_rpp = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        errPreviousToPreviousValue = 0.0;
        Ts = 0.0;
        PRControllerOutput = 0.0;
        x = 0.0;
        pr_p = 0.0;
        pr_r = 0.0;
        pr_rp = 0.0;
        pr_rpp = 0.0;

        return 0.0;
    }
    else{
    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    x = (omega*omega)*(Ts*Ts);

    pr_p = Kp*error;
    pr_r = ((pr_rp*(8.0-(2.0*x)))-(pr_rpp*(4.0+x))+(4.0*Kr*Ts)*(error-errPreviousToPreviousValue))/(4.0+x);

    PRControllerOutput = pr_p + pr_r;

    if (PRControllerOutput > UpperLimit)
    {
        PRControllerOutput = UpperLimit;
    }
    else if (PRControllerOutput < LowerLimit)
    {
        PRControllerOutput = LowerLimit;
    }

    errPreviousToPreviousValue = errPreviousValue;
    errPreviousValue = error;
    pr_rpp = pr_rp;
    pr_rp = pr_r;

    return PRControllerOutput;
    }
}

float PRController2(float sampleTime, float omega,float error, float Kp, float Kr, float UpperLimit, float LowerLimit, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float errPreviousToPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PRControllerOutput = 0.0;
    static float x = 0.0;
    static float pr_p = 0.0;
    static float pr_r = 0.0;
    static float pr_rp = 0.0;
    static float pr_rpp = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        errPreviousToPreviousValue = 0.0;
        Ts = 0.0;
        PRControllerOutput = 0.0;
        x = 0.0;
        pr_p = 0.0;
        pr_r = 0.0;
        pr_rp = 0.0;
        pr_rpp = 0.0;

        return 0.0;
    }
    else{
    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    x = (omega*omega)*(Ts*Ts);

    pr_p = Kp*error;
    pr_r = ((pr_rp*(8.0-(2.0*x)))-(pr_rpp*(4.0+x))+(4.0*Kr*Ts)*(error-errPreviousToPreviousValue))/(4.0+x);

    PRControllerOutput = pr_p + pr_r;

    if (PRControllerOutput > UpperLimit)
    {
        PRControllerOutput = UpperLimit;
    }
    else if (PRControllerOutput < LowerLimit)
    {
        PRControllerOutput = LowerLimit;
    }

    errPreviousToPreviousValue = errPreviousValue;
    errPreviousValue = error;
    pr_rpp = pr_rp;
    pr_rp = pr_r;

    return PRControllerOutput;
    }
}

void abcToqdTransformation(float fa, float fb, float fc, float *fq, float *fd)
{
    *fq = fa;
    *fd = (1.0/sqrt(3.0))*(fc - fb);
}

void stationaryToPositiveRotatingTransformation(float fq, float fd, float sine, float cosine, float *fqePve, float *fdePve)
{
    // Transformation to positively rotating reference frame
    *fqePve = fq*cosine - fd*sine;
    *fdePve = fd*cosine + fq*sine;
}

void stationaryToSeventhHarmonicPositiveRotatingTransformation(float fq, float fd, float sine7, float cosine7, float *fqe7Pve, float *fde7Pve)
{
    // Transformation to positively rotating reference frame
    *fqe7Pve = fq*cosine7 - fd*sine7;
    *fde7Pve = fd*cosine7 + fq*sine7;
}

void stationaryToNegativeRotatingTransformation(float fq, float fd, float sine, float cosine, float *fqeNve, float *fdeNve)
{
    // Transformation to negatively rotating reference frame
    *fqeNve = fq*cosine + fd*sine;
    *fdeNve = fd*cosine - fq*sine;
}

void DDSRFHarmonicOscillator(float omega, float *sine, float *cosine, float *sine2, float *cosine2, float *thetaReturn, Uint16 reset)
{
    static float theta = 0.0;
    static float omegap = 0.0;

    if (reset == 1){
        theta = 0.0;
        omegap = 0.0;
    }
    else{

    theta = theta + ((Ts/2)*(omega + omegap));
    if (theta >= 6.2832)
    {
      theta = 0;
    }

    omegap = omega;
    *sine = sin(theta);
    *cosine = cos(theta);
    *sine2 = sin(2.0*theta);
    *cosine2 = cos(2.0*theta);
    *thetaReturn = theta;
    }
}

float LPF1(float sampleTime, float ipSignal, float wf, Uint16 reset)
{
    static float opSignal = 0.0;
    static float ipSignalPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        ipSignalPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = Ts*wf;

    opSignal = ((opSignal*(1-(af/2)))+((af/2)*(ipSignalPrev+ipSignal)))/(1+(af/2));
    ipSignalPrev = ipSignal;
    }

    return opSignal;

}

float LPF2(float sampleTime, float ipSignal, float wf, Uint16 reset)
{
    static float opSignal = 0.0;
    static float ipSignalPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        ipSignalPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = Ts*wf;

    opSignal = ((opSignal*(1-(af/2)))+((af/2)*(ipSignalPrev+ipSignal)))/(1+(af/2));
    ipSignalPrev = ipSignal;
    }

    return opSignal;

}


float LPF3(float sampleTime, float ipSignal, float wf, Uint16 reset)
{
    static float opSignal = 0.0;
    static float ipSignalPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        ipSignalPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = Ts*wf;

    opSignal = ((opSignal*(1-(af/2)))+((af/2)*(ipSignalPrev+ipSignal)))/(1+(af/2));
    ipSignalPrev = ipSignal;
    }

    return opSignal;

}


float LPF4(float sampleTime, float ipSignal, float wf, Uint16 reset)
{
    static float opSignal = 0.0;
    static float ipSignalPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        ipSignalPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = Ts*wf;

    opSignal = ((opSignal*(1-(af/2)))+((af/2)*(ipSignalPrev+ipSignal)))/(1+(af/2));
    ipSignalPrev = ipSignal;
    }

    return opSignal;

}


// sampleTime is in micro-second
Uint16 DDSRFthreePhasePll(float sampleTime, float ipSignalA, float ipSignalB,  float ipSignalC, float *fqePve, float *fdePve, float *fqeNve, float *fdeNve, float *Omega, float *sinTheta, float *cosTheta, float *thetaReturn, Uint16 reset)
{
    static float omegaMax = 418.4;   // 66.6 Hz X 2 * pi
    static float omegaMin = 250.0;   // 40 Hz
    static float omega = 314.16;
    static float sine = 0.0;
    static float cosine = 1.0;
    static float phi = 0.0;
    static float theta = 0.0;
    // Variables related to DD-SRF PLL


    static float Kp = 100.0;
    static float Ki = 2000.0;
    static float vq_meas = 0;
    static float vd_meas = 0;
    static float vqe = 0;
    static float vde = 0;
    static float vqe_n = 0;
    static float vde_n = 0;
    static float vqe_f = 0;
    static float vde_f = 0;
    static float vqe_nf = 0;
    static float vde_nf = 0;
    static float vqedc = 0;
    static float vdedc = 0;
    static float vqe_ndc = 0;
    static float vde_ndc = 0;
    static float sine2 = 0;
    static float cosine2 = 1;



    if (sampleTime < 12.5 || sampleTime > 1500.0)
    {
        *fqePve = 0.0;
        *fdePve = 0.0;
        *fqeNve = 0.0;
        *fdeNve = 0.0;
        *Omega = 0.0;
        *sinTheta = 0.0;
        *cosTheta = 0.0;
        return 0;
    }
    else
    {

        if (reset == 1){
            omegaMax = 418.4;   // 66.6 Hz X 2 * pi
            omegaMin = 250.0;   // 40 Hz
            omega = 314.16;
            sine = 0.0;
            cosine = 1.0;
            phi = 0.0;
            theta = 0.0;
            // Variables related to DD-SRF PLL
            Kp = 100.0;
            Ki = 2000.0;
            vq_meas = 0;
            vd_meas = 0;
            vqe = 0;
            vde = 0;
            vqe_n = 0;
            vde_n = 0;
            vqe_f = 0;
            vde_f = 0;
            vqe_nf = 0;
            vde_nf = 0;
            vqedc = 0;
            vdedc = 0;
            vqe_ndc = 0;
            vde_ndc = 0;
            sine2 = 0;
            cosine2 = 1;

            DDSRFHarmonicOscillator(omega, &sine, &cosine, &sine2, &cosine2, &theta, 1);
            vqe_f = LPF1(sampleTime, vqedc, 555.0, 1);
            vde_f = LPF2(sampleTime, vdedc, 555.0, 1);
            vqe_nf = LPF3(sampleTime, vqe_ndc, 555.0, 1);
            vde_nf = LPF4(sampleTime, vde_ndc, 555.0, 1);
            omega = PIController1(sampleTime, phi, Kp, Ki, omegaMax, omegaMin, 0, 1000.0, 0, 1);

            return 1;
        }
        else{

        // *********************************************************************
        // DD-SRF PLL Code : START, inputs - ipSignalA, ipSignalB, ipSignalC
        // *********************************************************************

        // abc-qd transformation (three phase to stationary two phase transformation)
        // Assumption: Three phase three wire system
        abcToqdTransformation(ipSignalA, ipSignalB, ipSignalC, &vq_meas, &vd_meas);

        // VCO Code
        DDSRFHarmonicOscillator(omega, &sine, &cosine, &sine2, &cosine2, &theta, 0);

        // Transformation to positively rotating reference frame
        stationaryToPositiveRotatingTransformation(vq_meas, vd_meas, sine, cosine, &vqe, &vde);

        // Transformation to negatively rotating reference frame
        stationaryToNegativeRotatingTransformation(vq_meas, vd_meas, sine, cosine, &vqe_n, &vde_n);

        // Passing the decoupled quantities through LPF (Sample Time is 40 us, cut off frequency is 555 Hz)
        vqe_f = LPF1(sampleTime, vqedc, 555.0, 0);
        vde_f = LPF2(sampleTime, vdedc, 555.0, 0);
        vqe_nf = LPF3(sampleTime, vqe_ndc, 555.0, 0);
        vde_nf = LPF4(sampleTime, vde_ndc, 555.0, 0);


        // Canceling out 100 Hz components in both the reference frames
        vqedc = vqe - vqe_nf*cosine2 + vde_nf*sine2;
        vdedc = vde - vde_nf*cosine2  - vqe_nf*sine2;
        vqe_ndc = vqe_n - vqe_f*cosine2 - vde_f*sine2;
        vde_ndc = vde_n - vde_f*cosine2 + vqe_f*sine2;

        // applying four quadrant tan inverse: Start
        phi = fourQuadtanInverse(vqedc, vdedc);

        // applying four quadrant tan inverse: End

        omega = PIController1(sampleTime, phi, Kp, Ki, omegaMax, omegaMin, 0, 1000.0, 0, 0);
        //freq = omega/6.2832;

        // **********************************************************************
        // DD-SRF PLL Code : END, outputs : omega, vqe_f, vde_f, vqe_nf, vde_nf
        // **********************************************************************
        *fqePve = vqe_f;
        *fdePve = vde_f;
        *fqeNve = vqe_nf;
        *fdeNve = vde_nf;
        *Omega = omega;
        *sinTheta = sine;
        *cosTheta = cosine;
        *thetaReturn = theta;

        return 1;
        }
    }
}

Uint16 phaseSequenceDetector(float f12, float f23, Uint16 reset)
{
    static Uint16 SequencingComplete = 0;
    static Uint16 PositiveZeroCross = 0;
    static Uint16 NegativeZeroCross = 0;
    static float f12Prev = 0.0;
    static float f23Prev = 0.0;
    static Uint16 OneIsA_TwoisB = 1;
    static Uint16 OneIsC_TwoisB = 2;
    static Uint16 returnValue = 0;
    static Uint16 b1 = 0;
    static Uint16 c1 = 0;

    if (reset == 1){
        SequencingComplete = 0;
        PositiveZeroCross = 0;
        NegativeZeroCross = 0;
        f12Prev = 0.0;
        f23Prev = 0.0;
        OneIsA_TwoisB = 1;
        OneIsC_TwoisB = 2;
        returnValue = 0;
        b1 = 0;
        c1 = 0;


        return 0;
    }
    else{
    if (SequencingComplete == 0)
    {
       if (PositiveZeroCross == 0)
       {
           if (f12Prev <= 0 && f12 > 0)
           {
               PositiveZeroCross = 1;
           }
       }
       else if (PositiveZeroCross == 1 && NegativeZeroCross == 0)
       {
           if (f23Prev >= 0 && f23 < 0)
           {
               NegativeZeroCross = 1;
               c1 = c1 + 1;
               b1 = b1;
               PositiveZeroCross = 0;
               NegativeZeroCross = 0;
               if (c1 == 50)
               {
                 SequencingComplete = 1;
               }
           }
           else if (f23Prev <= 0 && f23 > 0)
           {
               NegativeZeroCross = 1;
               c1 = c1;
               b1 = b1 + 1;
               PositiveZeroCross = 0;
               NegativeZeroCross = 0;
               if (b1 == 50)
               {
                 SequencingComplete = 1;
               }
           }

       }
       returnValue = 0;

    }

    else
    {
        if (c1 == 50 && b1 < 50)
        {
            returnValue = OneIsC_TwoisB;

        }

        else if (b1 == 50 && c1 < 50)
        {
            returnValue =  OneIsA_TwoisB;
        }

    }

    // storing previous samples
    f12Prev = f12;
    f23Prev = f23;

    return returnValue;
    }
}

void SineTriangleToSVPWM(float fa, float fb, float fc, float *faSVPWM, float *fbSVPWM, float *fcSVPWM)
{
    static float Max = 0.0;
    static float Min = 0.0;
    static float commonMode = 0.0;

    //--------------------------- Finding Maximum Value ----------------------------

    if ((fa>=fb) && (fa>=fc))
    {
        Max = fa;
    }
    else if ((fb>=fa) && (fb>=fc))
    {
        Max = fb;
    }
    else
    {
        Max = fc;
    }

   //--------------------------- Finding Minimum Value ----------------------------

    if ((fa<=fb) && (fa<=fc))
    {
        Min = fa;
    }
    else if ((fb<=fa) && (fb<=fc))
    {
        Min = fb;
    }
    else
    {
        Min = fc;
    }

   //--------------- Generation of A, B, C Phase Space Vector Modulating Signals  -----------------------

    commonMode = -0.5*(Min + Max);     // Common mode voltage

    //commonMode  = 0;
    *faSVPWM = fa + commonMode;                // A-phase conventional space vector modulating signal
    *fbSVPWM = fb + commonMode;                // B-phase conventional space vector modulating signal
    *fcSVPWM = fc + commonMode;                // C-phase conventional space vector modulating signal
}

void stationary_qdToabcTransformation(float fq, float fd, float *fa, float *fb, float *fc)
{
    *fa = fq;
    *fb = (-1.0*((fq/2.0) + (sqrt(3.0)*(fd/2.0))));
    *fc = (((sqrt(3.0)*fd)/2.0) - (fq/2.0));
}

void positiveRotating_qd_To_stationary_qdTransformation(float fqe, float fde, float sine, float cosine, float *fq, float *fd)
{
    *fq = fqe*cosine + fde*sine;
    *fd = fde*cosine - fqe*sine;
}

void positiveRotatingSeventhHarmonic_qd_To_stationary_qdTransformation(float fq7e, float fd7e, float sine7, float cosine7, float *fq, float *fd)
{
    *fq = fq7e*cosine7 + fd7e*sine7;
    *fd = fd7e*cosine7 - fq7e*sine7;
}

void negativeRotating_qd_To_stationary_qdTransformation(float fqeNve, float fdeNve, float sine, float cosine, float *fq, float *fd)
{
    *fq = fqeNve*cosine - fdeNve*sine;
    *fd = fdeNve*cosine + fqeNve*sine;
}

void negativeRotatingFifthHarmonic_qd_To_stationary_qdTransformation(float fqe5Nve, float fde5Nve, float sine5, float cosine5, float *fq, float *fd)
{
    *fq = fqe5Nve*cosine5 - fde5Nve*sine5;
    *fd = fde5Nve*cosine5 + fqe5Nve*sine5;
}

void DDSRFConstantDcVoltageRefCurrentCalculator(float Pref, float vqe, float vde, float vqeNve, float vdeNve, float *iqeRef, float *ideRef, float *iqeRefNve, float *ideRefNve)
{
   static float D = 0.0;

   D = ((vde*vde) + (vqe*vqe)) - ((vdeNve*vdeNve) + (vqeNve*vqeNve));
   *iqeRef = (2.0*Pref*vqe)/(3.0*D);
   *ideRef = (2.0*Pref*vde)/(3.0*D);
   *iqeRefNve = (-2.0*Pref*vqeNve)/(3.0*D);
   *ideRefNve = (-2.0*Pref*vdeNve)/(3.0*D);
}

float VoltageController(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

float secondOrderLPF1(float sampleTime, float ipSignal, float wf, float tao, Uint16 reset)
{   // wf is the cut-off frequency in rad/s and tao is the damping factor
    static float opSignal = 0.0;
    static float opSignalPrev = 0.0;
    static float ipSignalPrev = 0.0;
    static float opSignalPrevToPrev = 0.0;
    static float ipSignalPrevToPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        opSignalPrev = 0.0;
        ipSignalPrev = 0.0;
        opSignalPrevToPrev = 0.0;
        ipSignalPrevToPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = (wf*wf*Ts*Ts);

    opSignal = ((opSignalPrev*(8.0-(2.0*af))) + (opSignalPrevToPrev*((4.0*tao*wf*Ts) - 4.0 - af)) + (af*(((2.0*ipSignalPrev) + ipSignal + ipSignalPrevToPrev))))/(4.0 + af + (4.0*tao*wf*Ts));
    opSignalPrevToPrev = opSignalPrev;
    opSignalPrev = opSignal;
    ipSignalPrevToPrev = ipSignalPrev;
    ipSignalPrev = ipSignal;


    }

    return opSignal;

}

float secondOrderLPF2(float sampleTime, float ipSignal, float wf, float tao, Uint16 reset)
{   // wf is the cut-off frequency in rad/s and tao is the damping factor
    static float opSignal = 0.0;
    static float opSignalPrev = 0.0;
    static float ipSignalPrev = 0.0;
    static float opSignalPrevToPrev = 0.0;
    static float ipSignalPrevToPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        opSignalPrev = 0.0;
        ipSignalPrev = 0.0;
        opSignalPrevToPrev = 0.0;
        ipSignalPrevToPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = (wf*wf*Ts*Ts);

    opSignal = ((opSignalPrev*(8.0-(2.0*af))) + (opSignalPrevToPrev*((4.0*tao*wf*Ts) - 4.0 - af)) + (af*(((2.0*ipSignalPrev) + ipSignal + ipSignalPrevToPrev))))/(4.0 + af + (4.0*tao*wf*Ts));
    opSignalPrevToPrev = opSignalPrev;
    opSignalPrev = opSignal;
    ipSignalPrevToPrev = ipSignalPrev;
    ipSignalPrev = ipSignal;

    }

    return opSignal;

}

float secondOrderLPF3(float sampleTime, float ipSignal, float wf, float tao, Uint16 reset)
{   // wf is the cut-off frequency in rad/s and tao is the damping factor
    static float opSignal = 0.0;
    static float opSignalPrev = 0.0;
    static float ipSignalPrev = 0.0;
    static float opSignalPrevToPrev = 0.0;
    static float ipSignalPrevToPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        opSignalPrev = 0.0;
        ipSignalPrev = 0.0;
        opSignalPrevToPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
        ipSignalPrevToPrev = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = (wf*wf*Ts*Ts);

    opSignal = ((opSignalPrev*(8.0-(2.0*af))) + (opSignalPrevToPrev*((4.0*tao*wf*Ts) - 4.0 - af)) + (af*(((2.0*ipSignalPrev) + ipSignal + ipSignalPrevToPrev))))/(4.0 + af + (4.0*tao*wf*Ts));
    opSignalPrevToPrev = opSignalPrev;
    opSignalPrev = opSignal;
    ipSignalPrevToPrev = ipSignalPrev;
    ipSignalPrev = ipSignal;

    }

    return opSignal;

}

float secondOrderLPF4(float sampleTime, float ipSignal, float wf, float tao, Uint16 reset)
{   // wf is the cut-off frequency in rad/s and tao is the damping factor
    static float opSignal = 0.0;
    static float opSignalPrev = 0.0;
    static float ipSignalPrev = 0.0;
    static float opSignalPrevToPrev = 0.0;
    static float ipSignalPrevToPrev = 0.0;
    static float Ts = 0.0;
    static float af = 0.0;

    if (reset == 1){
        opSignal = 0.0;
        opSignalPrev = 0.0;
        ipSignalPrev = 0.0;
        opSignalPrevToPrev = 0.0;
        Ts = 0.0;
        af = 0.0;
        ipSignalPrevToPrev = 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;
    af = (wf*wf*Ts*Ts);

    opSignal = ((opSignalPrev*(8.0-(2.0*af))) + (opSignalPrevToPrev*((4.0*tao*wf*Ts) - 4.0 - af)) + (af*(((2.0*ipSignalPrev) + ipSignal + ipSignalPrevToPrev))))/(4.0 + af + (4.0*tao*wf*Ts));
    opSignalPrevToPrev = opSignalPrev;
    opSignalPrev = opSignal;
    ipSignalPrevToPrev = ipSignalPrev;
    ipSignalPrev = ipSignal;

    }

    return opSignal;

}

float CurrentControllerDaxisPve(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

float CurrentControllerDaxisNve(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

float CurrentControllerQaxisPve(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

float CurrentControllerQaxisNve(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

void stationaryToNegativeRotatingFifthHarmonicTransformation(float fq, float fd, float sine5, float cosine5, float *fqe5Nve, float *fde5Nve)
{
    // Transformation to negatively rotating reference frame
    *fqe5Nve = fq*cosine5 + fd*sine5;
    *fde5Nve = fd*cosine5 - fq*sine5;
}

float fifthHarmonicCurrentControllerQ(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}


float fifthHarmonicCurrentControllerD(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

float seventhHarmonicCurrentControllerQ(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}


float seventhHarmonicCurrentControllerD(float sampleTime, float error, float Kp, float Ki, float UpperLimit, float LowerLimit, Uint16 resettable, float UpperLimitforReset, float resetValue, Uint16 reset)
{
    static float errPreviousValue = 0.0;
    static float Ts = 0.0;
    static float PIControllerOutput = 0.0;

    if (reset == 1){
        errPreviousValue = 0.0;
        Ts = 0.0;
        PIControllerOutput = 0.0;

        return 0.0;
    }
    else{

    Ts = 0.000001*sampleTime;    // micro-seconds to seconds conversion
    PIControllerOutput = PIControllerOutput + error*(Kp+Ki*(Ts/2)) + errPreviousValue*(0.0-Kp+Ki*(Ts/2));


    if (PIControllerOutput > UpperLimit)
    {
        PIControllerOutput = UpperLimit;
    }
    else if (PIControllerOutput < LowerLimit)
    {
        PIControllerOutput = LowerLimit;
    }

    if (resettable == 1)
    {
        if (PIControllerOutput >= UpperLimitforReset)
        {
            PIControllerOutput = resetValue;
        }
    }

    errPreviousValue = error;

    return PIControllerOutput;
    }
}

void resetControllers(){
    // phaseSequenceDetector
    // DDSRFPLL
    // OuterVoltageController
    // InnerPRControllers
    /*
    SequencingComplete = phaseSequenceDetector(0,0,1);
    PLLResult = DDSRFthreePhasePll(samplingTime, va, vb, vc, &vqe_f, &vde_f, &vqe_nf, &vde_nf, &omega, &sine, &cosine, &theta, 1);
    Pref = VoltageController(Ts, err_dc_gsc, Kp_dc_gsc, Ki_dc_gsc, Mmax_dc_gsc, Mmin_dc_gsc, 0, 0, 0, 1);
    Vinv_d = PRController1(samplingTime, omega, err_pr_id, Kpr, Kir, PRControlUpperLimit, PRControlLowerLimit, 1);
    Vinv_q = PRController2(samplingTime, omega, err_pr_iq, Kpr, Kir, PRControlUpperLimit, PRControlLowerLimit, 1);
    vInvDNve5e = fifthHarmonicCurrentControllerD(samplingTime, errDNve5e, KpFifthHarmonicControl, KiFifthHarmonicControl, vInvDNve5eUpperLimit, vInvDNve5eLowerLimit, 0, 0, 0, 1);
    vInvQNve5e = fifthHarmonicCurrentControllerQ(samplingTime, errQNve5e, KpFifthHarmonicControl, KiFifthHarmonicControl, vInvQNve5eUpperLimit, vInvQNve5eLowerLimit, 0, 0, 0, 1);
    vInvD7e = seventhHarmonicCurrentControllerD(samplingTime, errD7e, KpSeventhHarmonicControl, KiSeventhHarmonicControl, vInvD7eUpperLimit, vInvD7eLowerLimit, 0, 0, 0, 1);
    vInvQ7e = seventhHarmonicCurrentControllerQ(samplingTime, errQ7e, KpSeventhHarmonicControl, KiSeventhHarmonicControl, vInvQ7eUpperLimit, vInvQ7eLowerLimit, 0, 0, 0, 1);
    iq7eMeas_f = secondOrderLPF3(samplingTime, iq7eMeas, lpfCutOffFrequency, 0.5, 1);
    id7eMeas_f = secondOrderLPF4(samplingTime, id7eMeas, lpfCutOffFrequency, 0.5, 1);
    iqNve5eMeas_f = secondOrderLPF1(samplingTime, iqNve5eMeas, lpfCutOffFrequency, 0.5, 1);
    idNve5eMeas_f = secondOrderLPF2(samplingTime, idNve5eMeas, lpfCutOffFrequency, 0.5, 1);
    */

}

