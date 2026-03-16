/* read_state.c */
#include "includes/main.h" 
#include "includes/dasgip_state.h"

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

