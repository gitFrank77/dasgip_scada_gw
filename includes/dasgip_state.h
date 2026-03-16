/* dasgip_state.h */
#ifndef DASGIP_STATE_H
#define DASGIP_STATE_H


/*
#ifndef DASGIP_STATE_EXTENDED

// Original struct 
typedef struct {
    double Runtime_H;
    double VPV;
    int    AU;
    int    ODSensorState;
    double TSP;
    double TPV;
    int    TSensorState;
    double PHSP;
    double PHPV;
    int    PHSensorState;
    double DOSP;
    double DOPV;
    int    DOSensorState;
    double RDSP;
    double RDPV;
    int    RDSensorState;
    double FSP;
    double FPV;
    double XO2SP;
    double XO2PV;
    double XCO2SP;
    double XCO2PV;
    int    GassingState;
    double NSP;
    double NPV;
    double TorquePV;
    int    AgitationState;
} DasgipState;

#else
*/
/* Extended struct */
typedef struct {
    double Runtime_H;
    double VPV;
    int    Phase;
    double PhaseStart_H;
    int    AU;
    int    ODSensorState;
    double NSP;
    double NPV;
    double TorquePV;
    int    AgitationActive;
    int    AgitationState;
    double FASP;
    double FAPV;
    double VAPV;
    int    FACal;
    int    DirACCW;
    int    PumpAActive;
    int    PumpAState;
    int    FASource;
    double FBSP;
    double FBPV;
    double VBPV;
    int    FBCal;
    int    DirBCCW;
    int    PumpBActive;
    int    PumpBState;
    int    FBSource;
    double FCSP;
    double FCPV;
    double VCPV;
    int    FCCal;
    int    DirCCCW;
    int    PumpCActive;
    int    PumpCState;
    int    FCSource;
    double FDSP;
    double FDPV;
    double VDPV;
    int    FDCal;
    int    DirDCCW;
    int    PumpDActive;
    int    PumpDState;
    int    FDSource;
    double TSP;
    double TPV;
    int    TEnabled;
    int    TSensorState;
    double PHSP;
    double PHPV;
    int    PHEnabled;
    double PHDeadband;
    int    PHSensorState;
    double PHP;
    double DOSP;
    double DOPV;
    int    DOSensorState;
    double RDSP;
    double RDPV;
    int    RDSensorState;
    double LvlPV;
    int    LvlSensorState;
    double FSP;
    double FPV;
    int    GassingState;
    double XO2SP;
    double XO2PV;
    double XCO2SP;
    double XCO2PV;
    double OXCO2PV;
    double PSP;
    double PPV;
    int    IntA;
    int    IntB;
    int    IntC;
    int    IntD;
    int    IntE;
    int    IntF;
    int    IntG;
    int    IntH;
    int    IntI;
    int    IntJ;
    int    IntK;
    int    IntL;
    int    IntM;
    int    IntN;
    int    IntO;
    int    IntP;
    int    IntQ;
    int    IntR;
    int    IntS;
    int    IntT;
    int    IntU;
    int    IntV;
    int    IntW;
    int    IntX;
    int    IntY;
    int    IntZ;
} DasgipState;

//#endif  DASGIP_STATE_EXTENDED 

#endif /* DASGIP_STATE_H */
