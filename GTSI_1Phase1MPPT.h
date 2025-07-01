
/**********************************************************************
* File: Self Defined.h
  Self Defined Header File

**********************************************************************/
#include "f280013x_device.h"
#include "F28x_Project.h"
#include "f280013x_can.h"
#include "f280013x_device.h"
#include "f280013x_can.h"
#ifndef LAB_H
#define LAB_H

//---------------------------------------------------------------------------
// Constant Definitions
//
#define PWM_PERIOD_HERIC   30000                      // 300 = 100 kHz switching frequency with 60 MHz ePWM clock (Triangular)
#define PWM_PERIOD_BOOST    300                      // 300 = 100 kHz switching frequency with 60 MHz ePWM clock (Triangular)
#define PWM_FOR_ADC_SAMPLING 300                  // 2400 = 12.5 kHz sampling rate with 60 MHz ePWM clock (Triangular)
// Type-2 State Machine


//---------------------------------------------------------------------------
// Include Standard C Language Header Files
// (Header file <string.h> not supported by CLA compiler)
//
#if !defined(__TMS320C28XX_CLA__)
    #include <string.h>
#endif

#define FLT_MIN             1.175494351E-38F  /* MIN NORMALIZED POS VALUE  */
#define FLT_MAX             3.402823466E+38F  /* MAX POSITIVE VALUE        */


//---------------------------------------------------------------------------
// Include any other Header Files
//
//#include "F2837xD_Cla_typedefs.h"        // CLA type definitions
//#include "F2837xD_device.h"              // F2837xD header file peripheral address definitions
//#include "F2837xD_Adc_defines.h"         // ADC definitions
//#include "F2837xD_defaultisr.h"          // ISR definitions
//#include "F2837xD_Pie_defines.h"         // PIE definitions

#include "f280013x_examples.h"    // F280013x Examples Include File
#include "f280013x_device.h"      // f280013x Headerfile Include File


//---------------------------------------------------------------------------
// Function Prototypes
//
extern void Delay_us(Uint32);
extern void AdcSetMode(Uint16, Uint16, Uint16);
extern void CalAdcINL(Uint16);
extern void DelayUs(Uint16);
extern void initADC(void);
extern void MyInitADC(void);
extern void InitCla(void);
extern void InitDacb(void);
extern void InitDaca(void);
extern void InitDacc(void);
extern void InitDma(void);
extern void InitECap(void);
extern void InitEPwm(void);
extern void InitFlash(void);
extern void InitGpio(void);
extern void InitPieCtrl(void);
extern void InitSysCtrl(void);
extern void InitWatchdog(void);
extern void InitCanaChargerDriverLib(void);
extern void initCmpss(void);
extern void InitCpuTimer(Uint16 seconds);
extern Uint16 seconds;
extern Uint16 Result;
extern Uint32 Count;
extern float dutyCycle;
extern float epwmState;

//---------------------------------------------------------------------------
// CLA Function Prototypes
//
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


//---------------------------------------------------------------------------
// Global symbols defined in the linker command file
//
extern Uint16 cla1Funcs_loadstart;
extern Uint16 cla1Funcs_loadsize;
extern Uint16 cla1Funcs_runstart;
extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadsize;
extern Uint16 secureRamFuncs_runstart;
extern Uint16 Cla1Prog_Start;
extern volatile float tempSensRes;
extern volatile float actualTemp;
extern float beta;

//---------------------------------------------------------------------------
// Global Variables References
//
extern const struct PIE_VECT_TABLE PieVectTableInit;    // PieVectTableInit is always extern

//--- Global Variables ---
// Sampling Time for the Controller -> 80 us
extern float Ts;
extern float waveform1[400];
extern float waveform2[400];

typedef struct {
    float Sense;
    float Meas;
    float Multiplier;
    float Offset;
    float CalFactor;
    float DcOffset;
    float RMS;
    float Sum;
} acVariables;

typedef struct {
    float Sense;
    float Meas;
    float Multiplier;
    float CalFactor;
    float DcOffset;
    float Avg;
    float Sum;
} dcVariables;

typedef struct {
    float voltage;
    float resistance;
    float temperature;
} voltsToTemp;

typedef struct {
    float gridLowerVoltage;
    float gridUpperVoltage;
    float pvLowerVoltage;
    float pvUpperVoltage;
} startUp;


typedef struct {
    float gridUnderVoltage;
    float gridOverVoltage;
    float gridLowerFrequency;
    float gridUpperFrequency;
    float pvOverVoltage;
    float dcLinkOverVoltage;
    float pvSoftwareOverCurrent;
    float pvHardwareOverCurrent;
    float gridSoftwareOverCurrent;
    float gridHardwareOverCurrent;
    float deviceThermalTrip;
    float heatSinkThermalTrip;
    float magneticsThermalTrip;
} tripSettings;

typedef struct {
    float gridVoltageMultiplier;
    float gridCurrentMultiplier;
    float pvVoltageMultiplier;
    float pvVoltageOffset;
    float pvCurrentMultiplier;
    float pvCurrentOffset;
    float dcLinkVoltageMultiplier;
    float dcVoltageOffset;
    float pveDcLinkVoltageMultiplier;
    float pveDcLinkVoltageOffset;
    float nveDcLinkVoltageMultiplier;
    float nveDcLinkVoltageOffset;
} calibrationSettings;

//// Inverter Modes
//#define UnityPowerFactor 1
//#define ActivePowerControl 2
//#define RecativePowerControl 3
//#define FixedPowerFactor 4

typedef struct {
    Uint16 inverterMode;
    float activePowerSet;
    float reactivePowerSet;
    float fixedPFSet;
} inverterModeSettings;

typedef enum{
    oneseconddelaymode,
    offsetcalcmode,
    activemode,
    stateA,
    stateB,
    stateC,
    stateD,
    stateE,
    stateF
}offsetstatemachine;

extern float inverterRatedPower;
extern Uint16 inverterON_OFF;
extern Uint16 mpptMode;
extern float restartTimer;
extern calibrationSettings calibration;
extern inverterModeSettings inverterModeSetting;
extern tripSettings tripSetting;
extern startUp startUpSettings;
extern voltsToTemp IndGridCore;
extern voltsToTemp IndGridCopper;
extern voltsToTemp IndPvCore;
extern voltsToTemp IndPvCopper;
extern voltsToTemp heatSink;
extern offsetstatemachine currstate;
extern Uint32 transition_counter;
extern float sample_time;
extern float EvStateAvgVolt;
extern float cpSignalBuffer;

//#########################DEFINING THE STRUCTURES FOR THE TYPE TWO AC CHARGER#####################################
typedef enum {
    CP_STATE_A = 0,  // No vehicle connected (12V)
    CP_STATE_B,      // Vehicle connected but not requesting charging (9V)
    CP_STATE_C,      // Vehicle connected and requesting charging (6V)
    CP_STATE_D,      // Vehicle connected, charging with ventilation required (3V)
    CP_STATE_E,      // Error: short to ground or voltage < 3V
    CP_STATE_F       // Error: CP shorted to +12V
}states;

typedef struct {
    float grid_voltage_R;
    float grid_voltage_Y;
    float grid_voltage_B;
    float prot_earth;
    float vbatt;
    float residual_curr;
    float grid_curr_R;
    float grid_curr_Y;
    float grid_curr_B;
    float cp_signal;
    float temp_sens;
    float actualTemp;
} SENSEDVALUES;

typedef struct{
    Uint16 greaterThan10_A;
    Uint16 greaterThan7_B;
    Uint16 greaterThan4_C;
    Uint16 greaterThan1_D;
    Uint16 greaterThan_2_E;
}HIGHSTATERECORDER;

typedef struct{
    Uint16 maxCount;
    states maxState;
}PAIR;

typedef enum{
    gridvoltage,
    protearth,
    vbatt,
    residualcurr,
    gridcurr,
    cpsignal,
    tempsens
}sensedparams;

typedef struct{
    uint16_t Seq_number;
    uint16_t Upper_Byte_PhaseA;
    uint16_t Lower_Byte_PhaseA;
    uint16_t Upper_Byte_PhaseB;
    uint16_t Lower_Byte_PhaseB;
    uint16_t Upper_Byte_PhaseC;
    uint16_t Lower_Byte_PhaseC;
    uint16_t Reserved;
}CAN_SEQ;

typedef struct{
    uint16_t Seq_number;
    uint16_t Byte_RCMU;
    uint16_t Byte_NEvoltage;
    uint16_t Cp_state;
    uint16_t DutyCycle;
    uint16_t ConnectorState;
    uint32_t Reserved;
}CAN_SEQ3;

typedef struct{
    uint16_t rsgMsgObjSeq1[8];
    uint16_t rsgMsgObjSeq2[8];
    uint16_t rsgMsgObjSeq3[8];
}RXDATA;

typedef union{
    CAN_SEQ phase_seq;
    uint16_t can_seq[8];
}CANSEQUNION;

typedef union{
    CAN_SEQ3 phase_seq;
    uint16_t can_seq[8];
}CANSEQUNION3;

typedef enum{
    OFF,
    ON
}status;

//variables for the sensing for the type two ac charger
//STRUCTURES
extern SENSEDVALUES sensedAnalogADC;
extern SENSEDVALUES actualsensedvalues;
extern SENSEDVALUES multipliers;
extern SENSEDVALUES AvgOffsets;
extern CANSEQUNION can_message_seq1_phvolt;
extern CANSEQUNION can_message_seq2_phcurr;
extern CANSEQUNION3 can_message_seq3_info;
extern RXDATA getdata;
extern SENSEDVALUES sum_values;
extern SENSEDVALUES rmsvalues;
extern HIGHSTATERECORDER highStateRecord;
extern PAIR pair;
extern Uint16 EvseState;
extern Uint16 sendMessageNow;
extern Uint16 highStateDetect;
extern Uint16 epwmHighStateCounter;
extern Uint16 epwmLowStateCounter;
extern Uint16 stopCharging;

//VARIABLES
extern Uint32 count;
//extern Uint16 samples;
extern unsigned char transmit[8];
extern Uint32 canCount;
extern volatile Uint16* resultADCA;
extern volatile Uint16* resultADCC;
extern states EVSE_State_Detect;

//###############################END OF THE VARIABLES###############################

extern float R25;
extern float BValue;
extern float RoomTemperature;

// Variables for online calculation of offsets
extern Uint32 offsetSettingCount;
extern Uint16 offsetSettingDone;
extern float offsetSettingPeriod;
extern float offsetSettingCountComplete;
extern float hardCodedVgOffset;

// Variables for averaging/rms computation over one grid cycle period
extern float cycleCounter;
extern float gridFrequency;
extern float cycleCompleteCount;

extern bool_t startConditionsMet;

// AC variables
extern acVariables vg;
extern acVariables ig;
extern acVariables iRes;
extern acVariables iLoad;
// DC variables
extern dcVariables vPv;
extern dcVariables iPv;
extern dcVariables vDc;
extern dcVariables tempIndGridCore;
extern dcVariables tempIndGridCopper;
extern dcVariables tempIndPvCore;
extern dcVariables tempIndPvCopper;
extern dcVariables tempHeatSink;

// Variables for online calculation of hardware tripping for ac current
extern float igOCHVol;
extern float igOCLVol;
extern Uint16  igOCH;
extern Uint16  igOCL;
extern float ipvOCVol;
extern Uint16  ipvOC;

// Variables for tripping limits
extern float igHardwareTripLimit;
extern float igSoftwareTripLimit;
extern float ipvHardwareTripLimit;
extern float ipvSoftwareTripLimit;
extern Uint16 rmsSamples;

extern void Delay_ms(Uint16);


// Conversions
extern  char BCD2UpperCh( char );
extern char BCD2LowerCh( char );
extern Uint16 Binary2BCD(Uint16 );
extern Uint16 BCD2Binary(Uint16 );

// string functions
extern void ftoa(float, char *, Uint16);
extern void f64toa(float, char *, Uint16);
extern Uint16 intToStr(Uint16 , char [], Uint16);
extern Uint16 int32ToStr(Uint32 , char [], Uint16);
extern void int64ToStr(Uint64 , char [], Uint16);
extern void reverseString (char*, Uint16);
extern void clearString (char* );
extern float atof(const char* );

// CAN related variables start
typedef struct{
    Uint16 gridStatus : 1;
    Uint16 pvStatus : 1;
    Uint16 inverterStatus : 1;
    Uint16 inverterFault : 5;
}phaseIndependentDataStruct;

typedef struct{
    phaseIndependentDataStruct phaseIndependentData;
    // Grid Voltages
    float gridVoltageA;
    float gridVoltageB;
    float gridVoltageC;
    // Grid Currents
    float gridCurrentA;
    float gridCurrentB;
    float gridCurrentC;
    // Powers
    float solarPower;
    float gridPower;
    float reactivePower;
    // DC Link Voltage
    float dcLinkVoltage;
    // Residual Current
    float residualCurrent;
    // Vpv1 to Vpv10
    float vpv[10];
    // Ipv1 to Ipv10
    float ipv[10];
    Uint16 majorSWVersion : 8;
    Uint16 minorSWVersion : 8;
    Uint16 canSendMessage;
}pecParametersStruct;
extern pecParametersStruct pecParameters;

#define count100ms 1250
#define count4ms 50

extern uint16_t CANASendMessage(Uint16 objectID, Uint16 dlc, Uint16 *data);

extern uint16_t CANAFailure;
extern uint16_t multiframeFlag;
extern uint16_t CANRxData[];
extern uint16_t canTxMessage;

extern uint16_t testFlag;
// PGN values
typedef enum{
    startupMessagePGN = 1u,
    changeCfgPGN
}PGN;

//CANTXFlags
typedef enum{
    sendCTSStartupMessage = 1u,
    receiveDataStartupMessage,
    sendACKStartupMessage,
    sendCTSChangeCfg,
    receiveDataChangeCfg,
    sendACKChangeCfg
}canTxFlags;

// Configuration settings
typedef enum {
    basicConfigurations = 1u,
    startupSettingConfigurations,
    tripSettingsConfigurations,
    restartTimerConfigurations,
    calibrationSettingConfigurations,
    inverterModeSettingConfigurations
} ConfigurationSettings;

// Parameter values
typedef enum {
    inverterOnOffConfig = 1u,
    mpptModeConfig
} BasicConfiguration;

typedef enum {
    gridLowerStartConfig = 3u,
    gridUpperStartConfig,
    pvLowerStartConfig,
    pvUpperStartConfig
} StartupSettings;

typedef enum {
    gridUnderVoltageConfig = 7u,
    gridUpperVoltageConfig,
    gridLowerFreqConfig,
    gridUpperFreqConfig,
    pvOverVoltageConfig,
    dcLinkOverVoltageConfig,
    pvSoftwareOverCurrentConfig,
    pvHardwareOverCurrentConfig,
    gridSoftwareOverCurrentConfig,
    gridHardwareOverCurrentConfig,
    deviceThermalTripConfig,
    heatSinkThermalTripConfig,
    magneticsThermalTripConfig
} TripSettings;

typedef enum {
    restartTimerConfig = 20u
} RestartTimerSettings;

typedef enum {
    gridVoltageCalibrationConfig = 21u,
    gridCurrentCalibrationConfig,
    pvVoltageCalibrationConfig,
    pvVoltageOffsetCalibrationConfig,
    pvCurrentCalibrationConfig,
    pvCurrentOffsetCalibrationConfig,
    dcLinkVoltageCalibrationConfig,
    dcLinkVoltageOffsetCalibrationConfig,
    positiveDCLinkVoltageCalibrationConfig,
    positiveDCLinkVoltageOffsetCalibrationConfig,
    negativeDCLinkVoltageCalibrationConfig,
    negativeDCLinkVoltageOffsetCalibrationConfig
} CalibrationSettings;

typedef enum {
    upfModeConfig = 33u,
    activePowerControlConfig,
    reactivePowerControlConfig,
    fixedPowerFactorConfig,
    inverterRatedPowerConfig,
    invModeConfig = 44
} InverterModeSettings;

typedef enum {
    UnityPowerFactor = 1u,
    ActivePowerControl,
    ReactivePowerControl,
    FixedPowerFactor
} InverterModes;

enum {
    NotReady2Charge = 1,
    Ready2Charge = 2
};

// Added for testing
//#define ADCPeriodTestON  GpioDataRegs.GPASET.bit.GPIO23
//#define ADCPeriodTestOFF GpioDataRegs.GPACLEAR.bit.GPIO23
//
//#define CANPeriodTestON  GpioDataRegs.GPBSET.bit.GPIO37
//#define CANPeriodTestOFF GpioDataRegs.GPBCLEAR.bit.GPIO37
//---------------------------------------------------------------------------
// Macros
//

// The following pointer to a function call calibrates the ADC reference, 
// DAC offset, and internal oscillators
//#define Device_cal (void   (*)(void))0x070282

// The following pointers to functions calibrate the ADC linearity.  Use this
// in the AdcSetMode(...) function only
#define CalAdcaINL (void   (*)(void))0x0703B4
#define CalAdcbINL (void   (*)(void))0x0703B2
#define CalAdccINL (void   (*)(void))0x0703B0
#define CalAdcdINL (void   (*)(void))0x0703AE

//For the testing
#define turnMainRelayOn (GpioDataRegs.GPASET.bit.GPIO1 = 1)
#define turnMainRelayOff (GpioDataRegs.GPACLEAR.bit.GPIO1 = 1)
#define enableBuff (GpioDataRegs.GPACLEAR.bit.GPIO8 = 1)
#define disableBuff (GpioDataRegs.GPASET.bit.GPIO8 = 1)

//For the sensing purposes
#define oneSecDelayCounter 20000
#define canMessageSendCounter 2000
#define consecutiveMsgDelay 20000
#define samplingFreq 20000
#define signalFreq 50
#define pwmfreq 1000
extern float voltWaveForm[samplingFreq/signalFreq];
extern float currWaveForm[samplingFreq/signalFreq];
#define TBPRDEPWM1 30000
extern float inputCurrent;
extern Uint16 epwmSamples;
extern Uint16 canBufferSeq1[4];
extern Uint16 canBufferSeq2[4];
extern Uint16 canBufferSeq3[4];
extern Uint16 EVSE_Ready_To_Charge;
extern Uint16 SeqNumberReceived;
extern states EVSE_State_Detect;

// The following pointer to a function call looks up the ADC offset trim for a
// given condition. Use this in the AdcSetMode(...) function only.
#define GetAdcOffsetTrimOTP (Uint16 (*)(Uint16 OTPoffset))0x0703AC


//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
