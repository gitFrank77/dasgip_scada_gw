#include "../includes/dasgip_utils_v1.h"
#include "../includes/main.h"


int DasgipState_SetPointChanged(const DasgipState *pre,
                               const DasgipState *new,
                               double sp_epsilon)
{
    if (fabs(pre->TSP    - new->TSP)    > sp_epsilon) return 1;
    if (fabs(pre->PHSP   - new->PHSP)   > sp_epsilon) return 1;
    if (fabs(pre->DOSP   - new->DOSP)   > sp_epsilon) return 1;
    if (fabs(pre->RDSP   - new->RDSP)   > sp_epsilon) return 1;
    if (fabs(pre->FSP    - new->FSP)    > sp_epsilon) return 1;
    if (fabs(pre->XO2SP  - new->XO2SP)  > sp_epsilon) return 1;
    if (fabs(pre->XCO2SP - new->XCO2SP) > sp_epsilon) return 1;
    if (fabs(pre->NSP    - new->NSP)    > sp_epsilon) return 1;
   return 0;
}

void print_old_new_values(DasgipState my_new, DasgipState my_old)
{

#ifdef DEBUG0
    printf("Parsed values:\n");
    printf("TSPnew    = %.6f\t TSPold %.6f\n", my_new.TSP, my_old.TSP);
    printf("PHSPnew   = %.6f\t PHSPold = %.6f\n", my_new.PHSP, my_old.PHSP);
    printf("DOSPnew   = %.6f\t DOSPold = %.6f\n", my_new.DOSP, my_old.DOSP);
    printf("RDSPnew   = %.6f\t RDSPold = %.6f\n", my_new.RDSP, my_old.RDSP);
    printf("FSPnew    = %.6f\t FSPold = %6f\n", my_new.FSP, my_old.FSP);
    printf("XO2SPnew  = %.6f\t XO2SPold = %.6f\n", my_new.XO2SP, my_old.XO2SP);
    printf("XCO2SPnew = %.6f\t XCO2SPold = %.6f\n", my_new.XCO2SP, my_old.XCO2SP);
    printf("NSPnew    = %.6f\t NSPold = %.6f\n", my_new.NSP, my_old.NSP);
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
    fprintf(fp, "TSP,%.7f\r\n", s->TSP);
    fprintf(fp, "PHSP,%.7f\r\n", s->PHSP);
    fprintf(fp, "DOSP,%.7f\r\n", s->DOSP);
    fprintf(fp, "RDSP,%.7f\r\n", s->RDSP);
    fprintf(fp, "FSP,%.7f\r\n", s->FSP);
    fprintf(fp, "XO2SP,%.7f\r\n",s->XO2SP);
    fprintf(fp, "XCO2SP,%.7f\r\n",s->XCO2SP);
    fprintf(fp, "NSP,%.7f\r\n", s->NSP);

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
	{  // printf("Line: '%s'\n", line);
	   // printf("Key: '%s'\n", key);	
            continue;
	}
	    /* ---- map keys to struct fields ---- */
        if      (strcmp(key, "Runtime_H") == 0) s->Runtime_H = val;
        else if (strcmp(key, "VPV") == 0) s->VPV = val;
        else if (strcmp(key, "AU") == 0) s->AU = (int)val;

        else if (strcmp(key, "ODSensorState") == 0) s->ODSensorState = (int)val;

        else if (strcmp(key, "TSP") == 0) s->TSP = val;
        else if (strcmp(key, "TPV") == 0) s->TPV = val;
        else if (strcmp(key, "TSensorState") == 0) s->TSensorState = (int)val;

        else if (strcmp(key, "PHSP") == 0) s->PHSP = val;
        else if (strcmp(key, "PHPV") == 0) s->PHPV = val;
        else if (strcmp(key, "PHSensorState") == 0) s->PHSensorState = (int)val;

        else if (strcmp(key, "DOSP") == 0) s->DOSP = val;
        else if (strcmp(key, "DOPV") == 0) s->DOPV = val;
        else if (strcmp(key, "DOSensorState") == 0) s->DOSensorState = (int)val;

        else if (strcmp(key, "RDSP") == 0) s->RDSP = val;
        else if (strcmp(key, "RDPV") == 0) s->RDPV = val;
        else if (strcmp(key, "RDSensorState") == 0) s->RDSensorState = (int)val;

        else if (strcmp(key, "FSP") == 0) s->FSP = val;
        else if (strcmp(key, "FPV") == 0) s->FPV = val;

        else if (strcmp(key, "XO2SP") == 0) s->XO2SP = val;
        else if (strcmp(key, "XO2PV") == 0) s->XO2PV = val;
        else if (strcmp(key, "XCO2SP") == 0) s->XCO2SP = val;
        else if (strcmp(key, "XCO2PV") == 0) s->XCO2PV = val;

        else if (strcmp(key, "GassingState") == 0) s->GassingState = (int)val;

        else if (strcmp(key, "NSP") == 0) s->NSP = val;
        else if (strcmp(key, "NPV") == 0) s->NPV = val;

        else if (strcmp(key, "TorquePV") == 0) s->TorquePV = val;
        else if (strcmp(key, "AgitationState") == 0) s->AgitationState = (int)val;
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
