#include "includes/main.h"
#include "includes/dasgip_state.h"
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

