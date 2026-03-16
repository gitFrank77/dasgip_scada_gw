#include "../includes/mysql_utils_v1.h"


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
if (!mysql_real_connect(con, WIN_HOST,MYSQL_USER,MYSQL_PW,MYSQL_DB,MY_PORT,NULL, 0)) // NULL no socket?
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


//--[prep query to send vessel state.txt values to DB]	
void update_vessel_status(DasgipState s, char *my_query, int query_size, int unit_id)
{
	

int  write =snprintf(my_query, query_size,
    "UPDATE vessel_state SET "
    "runtime_h = %.6f, vpv = %.3f, au = %d, odsensorsstate = %d, "
    "tsp = %.3f, tpv = %.3f, tsensorstate = %d, "
    "phsp = %.3f, phpv = %.3f, phsensorstate = %d, "
    "dosp = %.3f, dopv = %.3f, dosensorstate = %d, "
    "rdsp = %.3f, rdpv = %.3f, rdsensorstate = %d, "
    "fsp = %.3f, fpv = %.3f, "
    "xo2sp = %.3f, xo2pv = %.3f, xco2sp = %.3f, xco2pv = %.3f, "
    "gassingstate = %d, nsp = %.3f, npv = %.3f, torquepv = %.3f, "
    "agitationstate = %d, t_stamp = NOW(3) "
    "WHERE unit = %d",
    s.Runtime_H, s.VPV, s.AU, s.ODSensorState,
    s.TSP, s.TPV, s.TSensorState,
    s.PHSP, s.PHPV, s.PHSensorState,
    s.DOSP, s.DOPV, s.DOSensorState,
    s.RDSP, s.RDPV, s.RDSensorState,
    s.FSP, s.FPV,
    s.XO2SP, s.XO2PV, s.XCO2SP, s.XCO2PV,
    s.GassingState, s.NSP, s.NPV, s.TorquePV,
    s.AgitationState,unit_id

);

    if ( write < 0 || write >= query_size)
      {
		fprintf(stderr, "Query truncated! \n");
	}
}


//--[prep query to write DB value to vessel actions.txt]

void update_vessel_actions(char *my_query, int query_size, int unit_id)
{
	int write =  snprintf(my_query, query_size,
    	"SELECT tsp, phsp, dosp, rdsp, fsp, xo2sp, xco2sp, nsp "
    	"FROM vessel_control WHERE unit = %d", unit_id);

    if ( write < 0 || write >= query_size)
      {
		fprintf(stderr, "Query truncated! \n");
	}
}
	
/*
if (mysql_query(con_1, query) != 0) {
    // handle error
}
*/

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

//--[assign results values recieved from query]
void results_assign_value_handle(DasgipState *my_new, MYSQL_RES *results)
{	
	MYSQL_ROW row = mysql_fetch_row(results);
       if ( row == NULL)
       {
		printf("Error on mysql row return\n");
       }

	//--[assign row result to s_new]
	if (row) {
    	my_new->TSP   = atof(row[0]);
    	my_new->PHSP  = atof(row[1]);
    	my_new->DOSP  = atof(row[2]);
    	my_new->RDSP  = atof(row[3]);
    	my_new->FSP   = atof(row[4]);
    	my_new->XO2SP = atof(row[5]);
    	my_new->XCO2SP= atof(row[6]);
    	my_new->NSP   = atof(row[7]);
}
}





void mysql_check_send_query(MYSQL *con, char*my_query)
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
