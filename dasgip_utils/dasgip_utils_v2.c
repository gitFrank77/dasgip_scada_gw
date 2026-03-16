#include "../includes/dasgip_utils_v2.h"
#include "../includes/main.h"


int DasgipState_SetPointChanged(const DasgipState *pre,
                               const DasgipState *new,
                               double sp_epsilon)
{
    if (fabs(pre->TSP    - new->TSP)    > sp_epsilon) return 1;//
    if (fabs(pre->PHSP   - new->PHSP)   > sp_epsilon) return 1;//
    if (fabs(pre->DOSP   - new->DOSP)   > sp_epsilon) return 1;//
    if (fabs(pre->RDSP   - new->RDSP)   > sp_epsilon) return 1;//
    if (fabs(pre->FSP    - new->FSP)    > sp_epsilon) return 1;//
    if (fabs(pre->XO2SP  - new->XO2SP)  > sp_epsilon) return 1;//
    if (fabs(pre->XCO2SP - new->XCO2SP) > sp_epsilon) return 1;//
    if (fabs(pre->NSP    - new->NSP)    > sp_epsilon) return 1;//
    if (fabs(pre->FASP   - new->FASP)   > sp_epsilon) return 1;//
    if (fabs(pre->FBSP   - new->FBSP)   > sp_epsilon) return 1;//
    if (fabs(pre->FCSP   - new->FCSP)   > sp_epsilon) return 1;//
    if (fabs(pre->FDSP   - new->FDSP)   > sp_epsilon) return 1;//
    if (fabs(pre->PSP    - new->PSP)    > sp_epsilon) return 1;//
    if (fabs(pre->PHP    - new->PHP)    > sp_epsilon) return 1;//
    if (pre->AgitationActive != new->AgitationActive) return 1;//
  
    if (pre->PumpAActive     != new->PumpAActive)     return 1;//
    if (pre->PumpBActive     != new->PumpBActive)     return 1;//
    if (pre->PumpCActive     != new->PumpCActive)     return 1;//
    if (pre->PumpDActive     != new->PumpDActive)     return 1;//
    

    return 0;
}

void print_old_new_values(DasgipState my_new, DasgipState my_old)
{
#ifdef DEBUG0
    printf("Parsed values:\n");
    printf("TSPnew    = %.6f\t TSPold = %.6f\n",    my_new.TSP,    my_old.TSP);
    printf("PHSPnew   = %.6f\t PHSPold = %.6f\n",   my_new.PHSP,   my_old.PHSP);
    printf("DOSPnew   = %.6f\t DOSPold = %.6f\n",   my_new.DOSP,   my_old.DOSP);
    printf("RDSPnew   = %.6f\t RDSPold = %.6f\n",   my_new.RDSP,   my_old.RDSP);
    printf("FSPnew    = %.6f\t FSPold = %.6f\n",    my_new.FSP,    my_old.FSP);
    printf("XO2SPnew  = %.6f\t XO2SPold = %.6f\n",  my_new.XO2SP,  my_old.XO2SP);
    printf("XCO2SPnew = %.6f\t XCO2SPold = %.6f\n", my_new.XCO2SP, my_old.XCO2SP);
    printf("NSPnew    = %.6f\t NSPold = %.6f\n",    my_new.NSP,    my_old.NSP);
    printf("FASPnew   = %.6f\t FASPold = %.6f\n",   my_new.FASP,   my_old.FASP);
    printf("FBSPnew   = %.6f\t FBSPold = %.6f\n",   my_new.FBSP,   my_old.FBSP);
    printf("FCSPnew   = %.6f\t FCSPold = %.6f\n",   my_new.FCSP,   my_old.FCSP);
    printf("FDSPnew   = %.6f\t FDSPold = %.6f\n",   my_new.FDSP,   my_old.FDSP);
    printf("PSPnew    = %.6f\t PSPold = %.6f\n",    my_new.PSP,    my_old.PSP);
    printf("PHPnew    = %.6f\t PHPold = %.6f\n",    my_new.PHP,    my_old.PHP);
    printf("AgitationActivenew = %d\t AgitationActiveold = %d\n", my_new.AgitationActive, my_old.AgitationActive);
    printf("AgitationStatenew  = %d\t AgitationStateold = %d\n",  my_new.AgitationState,  my_old.AgitationState);
    printf("FACalnew           = %d\t FACalold = %d\n",           my_new.FACal,           my_old.FACal);
    printf("DirACCWnew         = %d\t DirACCWold = %d\n",         my_new.DirACCW,         my_old.DirACCW);
    printf("PumpAActivenew     = %d\t PumpAActiveold = %d\n",     my_new.PumpAActive,     my_old.PumpAActive);
    printf("PumpAStatenew      = %d\t PumpAStateold = %d\n",      my_new.PumpAState,      my_old.PumpAState);
    printf("FBCalnew           = %d\t FBCalold = %d\n",           my_new.FBCal,           my_old.FBCal);
    printf("DirBCCWnew         = %d\t DirBCCWold = %d\n",         my_new.DirBCCW,         my_old.DirBCCW);
    printf("PumpBActivenew     = %d\t PumpBActiveold = %d\n",     my_new.PumpBActive,     my_old.PumpBActive);
    printf("PumpBStatenew      = %d\t PumpBStateold = %d\n",      my_new.PumpBState,      my_old.PumpBState);
    printf("FCCalnew           = %d\t FCCalold = %d\n",           my_new.FCCal,           my_old.FCCal);
    printf("DirCCCWnew         = %d\t DirCCCWold = %d\n",         my_new.DirCCCW,         my_old.DirCCCW);
    printf("PumpCActivenew     = %d\t PumpCActiveold = %d\n",     my_new.PumpCActive,     my_old.PumpCActive);
    printf("PumpCStatenew      = %d\t PumpCStateold = %d\n",      my_new.PumpCState,      my_old.PumpCState);
    printf("FDCalnew           = %d\t FDCalold = %d\n",           my_new.FDCal,           my_old.FDCal);
    printf("DirDCCWnew         = %d\t DirDCCWold = %d\n",         my_new.DirDCCW,         my_old.DirDCCW);
    printf("PumpDActivenew     = %d\t PumpDActiveold = %d\n",     my_new.PumpDActive,     my_old.PumpDActive);
    printf("PumpDStatenew      = %d\t PumpDStateold = %d\n",      my_new.PumpDState,      my_old.PumpDState);
    printf("IntAnew = %d\t IntAold = %d\n", my_new.IntA, my_old.IntA);
    printf("IntBnew = %d\t IntBold = %d\n", my_new.IntB, my_old.IntB);
    printf("IntCnew = %d\t IntCold = %d\n", my_new.IntC, my_old.IntC);
    printf("IntDnew = %d\t IntDold = %d\n", my_new.IntD, my_old.IntD);
    printf("IntEnew = %d\t IntEold = %d\n", my_new.IntE, my_old.IntE);
    printf("IntFnew = %d\t IntFold = %d\n", my_new.IntF, my_old.IntF);
    printf("IntGnew = %d\t IntGold = %d\n", my_new.IntG, my_old.IntG);
    printf("IntHnew = %d\t IntHold = %d\n", my_new.IntH, my_old.IntH);
    printf("IntInew = %d\t IntIold = %d\n", my_new.IntI, my_old.IntI);
    printf("IntJnew = %d\t IntJold = %d\n", my_new.IntJ, my_old.IntJ);
    printf("IntKnew = %d\t IntKold = %d\n", my_new.IntK, my_old.IntK);
    printf("IntLnew = %d\t IntLold = %d\n", my_new.IntL, my_old.IntL);
    printf("IntMnew = %d\t IntMold = %d\n", my_new.IntM, my_old.IntM);
    printf("IntNnew = %d\t IntNold = %d\n", my_new.IntN, my_old.IntN);
    printf("IntOnew = %d\t IntOold = %d\n", my_new.IntO, my_old.IntO);
    printf("IntPnew = %d\t IntPold = %d\n", my_new.IntP, my_old.IntP);
    printf("IntQnew = %d\t IntQold = %d\n", my_new.IntQ, my_old.IntQ);
    printf("IntRnew = %d\t IntRold = %d\n", my_new.IntR, my_old.IntR);
    printf("IntSnew = %d\t IntSold = %d\n", my_new.IntS, my_old.IntS);
    printf("IntTnew = %d\t IntTold = %d\n", my_new.IntT, my_old.IntT);
    printf("IntUnew = %d\t IntUold = %d\n", my_new.IntU, my_old.IntU);
    printf("IntVnew = %d\t IntVold = %d\n", my_new.IntV, my_old.IntV);
    printf("IntWnew = %d\t IntWold = %d\n", my_new.IntW, my_old.IntW);
    printf("IntXnew = %d\t IntXold = %d\n", my_new.IntX, my_old.IntX);
    printf("IntYnew = %d\t IntYold = %d\n", my_new.IntY, my_old.IntY);
    printf("IntZnew = %d\t IntZold = %d\n", my_new.IntZ, my_old.IntZ);
#endif
}

void write_vessel_actions(const char *filename, DasgipState *s)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
  //  fprintf(fp,"\n");
    fprintf(fp, "TSP,%.7f\r\n",    s->TSP);
    fprintf(fp, "PHSP,%.7f\r\n",   s->PHSP);
    fprintf(fp, "DOSP,%.7f\r\n",   s->DOSP);
    fprintf(fp, "RDSP,%.7f\r\n",   s->RDSP);
    fprintf(fp, "FSP,%.7f\r\n",    s->FSP);
    fprintf(fp, "XO2SP,%.7f\r\n",  s->XO2SP);
    fprintf(fp, "XCO2SP,%.7f\r\n", s->XCO2SP);
    fprintf(fp, "NSP,%.7f\r\n",    s->NSP);
    fprintf(fp, "FASP,%.7f\r\n",   s->FASP);
    fprintf(fp, "FBSP,%.7f\r\n",   s->FBSP);
    fprintf(fp, "FCSP,%.7f\r\n",   s->FCSP);
    fprintf(fp, "FDSP,%.7f\r\n",   s->FDSP);
    fprintf(fp, "PSP,%.7f\r\n",    s->PSP);
    fprintf(fp, "PHP,%.7f\r\n",   s->PHP);
    fprintf(fp, "AgitationActive,%d\r\n", s->AgitationActive);
   // fprintf(fp, "FACal,%d\r\n",        s->FACal);
    fprintf(fp, "PumpAActive,%d\r\n",     s->PumpAActive);
    fprintf(fp, "PumpBActive,%d\r\n",     s->PumpBActive);
    fprintf(fp, "PumpCActive,%d\r\n",     s->PumpCActive);
    fprintf(fp, "PumpDActive,%d\r\n",     s->PumpDActive);
  //  fprintf(fp, "PressureActive,%d\r\n",  s->PressureActive);


    fclose(fp);
}



int read_dasgip_state(const char *path, DasgipState *s) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;

    char line[256];
    char key[64];
    double val;

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, " %63[^,],%lf", key, &val) != 2)
        {
            continue;
        }
        /* ---- map keys to struct fields ---- */
        if      (strcmp(key, "Runtime_H") == 0) s->Runtime_H = val;
        else if (strcmp(key, "VPV") == 0) s->VPV = val;
        else if (strcmp(key, "Phase") == 0) s->Phase = (int)val;
        else if (strcmp(key, "PhaseStart_H") == 0) s->PhaseStart_H = val;
        else if (strcmp(key, "AU") == 0) s->AU = (int)val;

        else if (strcmp(key, "ODSensorState") == 0) s->ODSensorState = (int)val;

        else if (strcmp(key, "NSP") == 0) s->NSP = val;
        else if (strcmp(key, "NPV") == 0) s->NPV = val;
        else if (strcmp(key, "TorquePV") == 0) s->TorquePV = val;
        else if (strcmp(key, "AgitationActive") == 0) s->AgitationActive = (int)val;
        else if (strcmp(key, "AgitationState") == 0) s->AgitationState = (int)val;

        else if (strcmp(key, "FASP") == 0) s->FASP = val;
        else if (strcmp(key, "FAPV") == 0) s->FAPV = val;
        else if (strcmp(key, "VAPV") == 0) s->VAPV = val;
        else if (strcmp(key, "FACal") == 0) s->FACal = (int)val;
        else if (strcmp(key, "DirACCW") == 0) s->DirACCW = (int)val;
        else if (strcmp(key, "PumpAActive") == 0) s->PumpAActive = (int)val;
        else if (strcmp(key, "PumpAState") == 0) s->PumpAState = (int)val;
        else if (strcmp(key, "FASource") == 0) s->FASource = (int)val;

        else if (strcmp(key, "FBSP") == 0) s->FBSP = val;
        else if (strcmp(key, "FBPV") == 0) s->FBPV = val;
        else if (strcmp(key, "VBPV") == 0) s->VBPV = val;
        else if (strcmp(key, "FBCal") == 0) s->FBCal = (int)val;
        else if (strcmp(key, "DirBCCW") == 0) s->DirBCCW = (int)val;
        else if (strcmp(key, "PumpBActive") == 0) s->PumpBActive = (int)val;
        else if (strcmp(key, "PumpBState") == 0) s->PumpBState = (int)val;
        else if (strcmp(key, "FBSource") == 0) s->FBSource = (int)val;

        else if (strcmp(key, "FCSP") == 0) s->FCSP = val;
        else if (strcmp(key, "FCPV") == 0) s->FCPV = val;
        else if (strcmp(key, "VCPV") == 0) s->VCPV = val;
        else if (strcmp(key, "FCCal") == 0) s->FCCal = (int)val;
        else if (strcmp(key, "DirCCCW") == 0) s->DirCCCW = (int)val;
        else if (strcmp(key, "PumpCActive") == 0) s->PumpCActive = (int)val;
        else if (strcmp(key, "PumpCState") == 0) s->PumpCState = (int)val;
        else if (strcmp(key, "FCSource") == 0) s->FCSource = (int)val;

        else if (strcmp(key, "FDSP") == 0) s->FDSP = val;
        else if (strcmp(key, "FDPV") == 0) s->FDPV = val;
        else if (strcmp(key, "VDPV") == 0) s->VDPV = val;
        else if (strcmp(key, "FDCal") == 0) s->FDCal = (int)val;
        else if (strcmp(key, "DirDCCW") == 0) s->DirDCCW = (int)val;
        else if (strcmp(key, "PumpDActive") == 0) s->PumpDActive = (int)val;
        else if (strcmp(key, "PumpDState") == 0) s->PumpDState = (int)val;
        else if (strcmp(key, "FDSource") == 0) s->FDSource = (int)val;

        else if (strcmp(key, "TSP") == 0) s->TSP = val;
        else if (strcmp(key, "TPV") == 0) s->TPV = val;
        else if (strcmp(key, "TEnabled") == 0) s->TEnabled = (int)val;
        else if (strcmp(key, "TSensorState") == 0) s->TSensorState = (int)val;

        else if (strcmp(key, "PHSP") == 0) s->PHSP = val;
        else if (strcmp(key, "PHPV") == 0) s->PHPV = val;
        else if (strcmp(key, "PHEnabled") == 0) s->PHEnabled = (int)val;
        else if (strcmp(key, "PHDeadband") == 0) s->PHDeadband = val;
        else if (strcmp(key, "PHSensorState") == 0) s->PHSensorState = (int)val;
        else if (strcmp(key, "PHP") == 0) s->PHP = val;

        else if (strcmp(key, "DOSP") == 0) s->DOSP = val;
        else if (strcmp(key, "DOPV") == 0) s->DOPV = val;
        else if (strcmp(key, "DOSensorState") == 0) s->DOSensorState = (int)val;

        else if (strcmp(key, "RDSP") == 0) s->RDSP = val;
        else if (strcmp(key, "RDPV") == 0) s->RDPV = val;
        else if (strcmp(key, "RDSensorState") == 0) s->RDSensorState = (int)val;

        else if (strcmp(key, "LvlPV") == 0) s->LvlPV = val;
        else if (strcmp(key, "LvlSensorState") == 0) s->LvlSensorState = (int)val;

        else if (strcmp(key, "FSP") == 0) s->FSP = val;
        else if (strcmp(key, "FPV") == 0) s->FPV = val;
        else if (strcmp(key, "GassingState") == 0) s->GassingState = (int)val;

        else if (strcmp(key, "XO2SP") == 0) s->XO2SP = val;
        else if (strcmp(key, "XO2PV") == 0) s->XO2PV = val;
        else if (strcmp(key, "XCO2SP") == 0) s->XCO2SP = val;
        else if (strcmp(key, "XCO2PV") == 0) s->XCO2PV = val;
        else if (strcmp(key, "OXCO2PV") == 0) s->OXCO2PV = val;

        else if (strcmp(key, "PSP") == 0) s->PSP = val;
        else if (strcmp(key, "PPV") == 0) s->PPV = val;

        else if (strcmp(key, "IntA") == 0) s->IntA = (int)val;
        else if (strcmp(key, "IntB") == 0) s->IntB = (int)val;
        else if (strcmp(key, "IntC") == 0) s->IntC = (int)val;
        else if (strcmp(key, "IntD") == 0) s->IntD = (int)val;
        else if (strcmp(key, "IntE") == 0) s->IntE = (int)val;
        else if (strcmp(key, "IntF") == 0) s->IntF = (int)val;
        else if (strcmp(key, "IntG") == 0) s->IntG = (int)val;
        else if (strcmp(key, "IntH") == 0) s->IntH = (int)val;
        else if (strcmp(key, "IntI") == 0) s->IntI = (int)val;
        else if (strcmp(key, "IntJ") == 0) s->IntJ = (int)val;
        else if (strcmp(key, "IntK") == 0) s->IntK = (int)val;
        else if (strcmp(key, "IntL") == 0) s->IntL = (int)val;
        else if (strcmp(key, "IntM") == 0) s->IntM = (int)val;
        else if (strcmp(key, "IntN") == 0) s->IntN = (int)val;
        else if (strcmp(key, "IntO") == 0) s->IntO = (int)val;
        else if (strcmp(key, "IntP") == 0) s->IntP = (int)val;
        else if (strcmp(key, "IntQ") == 0) s->IntQ = (int)val;
        else if (strcmp(key, "IntR") == 0) s->IntR = (int)val;
        else if (strcmp(key, "IntS") == 0) s->IntS = (int)val;
        else if (strcmp(key, "IntT") == 0) s->IntT = (int)val;
        else if (strcmp(key, "IntU") == 0) s->IntU = (int)val;
        else if (strcmp(key, "IntV") == 0) s->IntV = (int)val;
        else if (strcmp(key, "IntW") == 0) s->IntW = (int)val;
        else if (strcmp(key, "IntX") == 0) s->IntX = (int)val;
        else if (strcmp(key, "IntY") == 0) s->IntY = (int)val;
        else if (strcmp(key, "IntZ") == 0) s->IntZ = (int)val;
    }

    fclose(f);
    return 0;
}


void read_assign_state(const char *file, DasgipState *s)
{

if (read_dasgip_state(file, s) != 0) {
        printf("Failed to read state file\n");
       // return 1;
    }
}
