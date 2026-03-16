#include "../includes/mysql_utils_v2.h"


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//--[create and intialize db connection]
MYSQL * mysql_con_init()
{
       	MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

printf("Connecting to host=%s port=%u user=%s db=%s\n", WIN_HOST, MY_PORT, MYSQL_USER, MYSQL_PW);
  return con;
}

//--[verify connection to db]
void mysql_con_connect( MYSQL *con)
{
if (!mysql_real_connect(con, WIN_HOST,MYSQL_USER,MYSQL_PW,MYSQL_DB,MY_PORT,NULL, 0))
{
    fprintf(stderr, "Connect failed: %s\n", mysql_error(con));
    exit(1);
}

if (mysql_query(con, "SELECT @@version, @@version_comment")) {
  fprintf(stderr, "Query failed: %s\n", mysql_error(con));
} 
else {
  MYSQL_RES *res = mysql_store_result(con);
  MYSQL_ROW row = mysql_fetch_row(res);
  printf("Connected MySQL: %s | %s\n", row[0], row[1]);
  mysql_free_result(res);
	}
}


void update_vessel_status(DasgipState *s, char *my_query, int query_size, int unit_id)
{
int  write = snprintf(my_query, query_size,
    "UPDATE vessel_state SET "
    "runtime_h = %.6f, vpv = %.3f, phase = %d, phasestart_h = %.6f, au = %d, odsensorstate = %d, "
    "nsp = %.3f, npv = %.3f, torquepv = %.3f, agitationactive = %d, agitationstate = %d, "
    "fasp = %.3f, fapv = %.3f, vapv = %.3f, facal = %d, diraccw = %d, pumpaactive = %d, pumpastate = %d, fasource = %d, "
    "fbsp = %.3f, fbpv = %.3f, vbpv = %.3f, fbcal = %d, dirbccw = %d, pumpbactive = %d, pumpbstate = %d, fbsource = %d, "
    "fcsp = %.3f, fcpv = %.3f, vcpv = %.3f, fccal = %d, dircccw = %d, pumpcactive = %d, pumpcstate = %d, fcsource = %d, "
    "fdsp = %.3f, fdpv = %.3f, vdpv = %.3f, fdcal = %d, dirdccw = %d, pumpdactive = %d, pumpdstate = %d, fdsource = %d, "
    "tsp = %.3f, tpv = %.3f, tenabled = %d, tsensorstate = %d, "
    "phsp = %.3f, phpv = %.3f, phenabled = %d, phdeadband = %.6f, phsensorstate = %d, php = %.3f, "
    "dosp = %.3f, dopv = %.3f, dosensorstate = %d, "
    "rdsp = %.3f, rdpv = %.3f, rdsensorstate = %d, "
    "lvlpv = %.3f, lvlsensorstate = %d, "
    "fsp = %.3f, fpv = %.3f, gassingstate = %d, "
    "xo2sp = %.3f, xo2pv = %.3f, xco2sp = %.3f, xco2pv = %.3f, oxco2pv = %.3f, "
    "psp = %.3f, ppv = %.3f, "
    "inta_val = %d, intb_val = %d, intc_val = %d, intd_val = %d, inte_val = %d, intf_val = %d, intg_val = %d, inth_val = %d, inti_val = %d, intj_val = %d, "
    "intk_val = %d, intl_val = %d, intm_val = %d, intn_val = %d, into_val = %d, intp_val = %d, intq_val = %d, intr_val = %d, ints_val = %d, intt_val = %d, "
    "intu_val = %d, intv_val = %d, intw_val = %d, intx_val = %d, inty_val = %d, intz_val = %d, "
    "t_stamp = NOW(3) "
    "WHERE unit = %d",
    s->Runtime_H, s->VPV, s->Phase, s->PhaseStart_H, s->AU, s->ODSensorState,
    s->NSP, s->NPV, s->TorquePV, s->AgitationActive, s->AgitationState,
    s->FASP, s->FAPV, s->VAPV, s->FACal, s->DirACCW, s->PumpAActive, s->PumpAState, s->FASource,
    s->FBSP, s->FBPV, s->VBPV, s->FBCal, s->DirBCCW, s->PumpBActive, s->PumpBState, s->FBSource,
    s->FCSP, s->FCPV, s->VCPV, s->FCCal, s->DirCCCW, s->PumpCActive, s->PumpCState, s->FCSource,
    s->FDSP, s->FDPV, s->VDPV, s->FDCal, s->DirDCCW, s->PumpDActive, s->PumpDState, s->FDSource,
    s->TSP, s->TPV, s->TEnabled, s->TSensorState,
    s->PHSP, s->PHPV, s->PHEnabled, s->PHDeadband, s->PHSensorState, s->PHP,
    s->DOSP, s->DOPV, s->DOSensorState,
    s->RDSP, s->RDPV, s->RDSensorState,
    s->LvlPV, s->LvlSensorState,
    s->FSP, s->FPV, s->GassingState,
    s->XO2SP, s->XO2PV, s->XCO2SP, s->XCO2PV, s->OXCO2PV,
    s->PSP, s->PPV,
    s->IntA, s->IntB, s->IntC, s->IntD, s->IntE, s->IntF, s->IntG, s->IntH, s->IntI, s->IntJ,
    s->IntK, s->IntL, s->IntM, s->IntN, s->IntO, s->IntP, s->IntQ, s->IntR, s->IntS, s->IntT,
    s->IntU, s->IntV, s->IntW, s->IntX, s->IntY, s->IntZ,
    unit_id
);
    if (write < 0 || write >= query_size)
    {
        printf("Error with query. Check : %d , %s \n", __LINE__, __func__);
        fprintf(stderr, "Query truncated! \n");
    }
}

//--[prep query to write DB value to vessel actions.txt]
void update_vessel_actions(char *my_query, int query_size, int unit_id)
{
    int write = snprintf(my_query, query_size,
        "SELECT tsp, phsp, php, dosp, rdsp, fsp, xo2sp, xco2sp, nsp, "
        "fasp, fbsp, fcsp, fdsp, psp, "
        "agitationactive, "
        "pumpaactive, "
        "pumpbactive, "
        "pumpcactive, "
        "pumpdactive "
        "FROM vessel_control WHERE unit = %d", unit_id);
        
     //   printf("write=%d query_size=%d\n", write, query_size);
        
    if (write < 0 || write >= query_size)
    
    {    printf("Error with query. Check : %d , %s \n", __LINE__, __func__);
        fprintf(stderr, "Query truncated! \n");
        
    }
}


//--[send results query/request]

MYSQL_RES *results_query_handle( MYSQL *con)
{
	MYSQL_RES *res = mysql_store_result(con);
if (!res) {
    // handle error
    printf("Error with query. Check : %d , %s \n", __LINE__, __func__);
}
	return res;
}


//--[send results query/request]
void results_assign_value_handle(DasgipState *my_new, MYSQL_RES *results)
{
    if (results == NULL)
    {
        printf("results is NULL, skipping assign\n");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(results);
    if (row == NULL)
    {
        printf("Error on mysql row return\n");
        return;
    }

    my_new->TSP             = row[0]  ? atof(row[0])  : 0.0;
    my_new->PHSP            = row[1]  ? atof(row[1])  : 0.0;
    my_new->PHP             = row[2]  ? atof(row[2])  : 0.0;
    my_new->DOSP            = row[3]  ? atof(row[3])  : 0.0;
    my_new->RDSP            = row[4]  ? atof(row[4])  : 0.0;
    my_new->FSP             = row[5]  ? atof(row[5])  : 0.0;
    my_new->XO2SP           = row[6]  ? atof(row[6])  : 0.0;
    my_new->XCO2SP          = row[7]  ? atof(row[7])  : 0.0;
    my_new->NSP             = row[8]  ? atof(row[8])  : 0.0;
    my_new->FASP            = row[9]  ? atof(row[9])  : 0.0;
    my_new->FBSP            = row[10] ? atof(row[10]) : 0.0;
    my_new->FCSP            = row[11] ? atof(row[11]) : 0.0;
    my_new->FDSP            = row[12] ? atof(row[12]) : 0.0;
    my_new->PSP             = row[13] ? atof(row[13]) : 0.0;
    my_new->AgitationActive = row[14] ? atoi(row[14]) : 0;
    my_new->PumpAActive     = row[15] ? atoi(row[15]) : 0;
    my_new->PumpBActive     = row[16] ? atoi(row[16]) : 0;
    my_new->PumpCActive     = row[17] ? atoi(row[17]) : 0;
    my_new->PumpDActive     = row[18] ? atoi(row[18]) : 0;
}
void mysql_check_send_query(MYSQL *con, char *my_query)
{
if (mysql_query(con, my_query)) {
    printf("Error with query. Check : %d , %s \n", __LINE__, __func__);
    finish_with_error(con);
}
}


/*
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
*/
