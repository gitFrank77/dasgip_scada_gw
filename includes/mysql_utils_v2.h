#ifndef __MYSQL_UTILS_V1_H
#define __MYSQL_UTILS_V1_H
#include "mysql.h"
#include "main.h"
#include "dasgip_state.h"

#define MYSQL_USER	"ignition_user"
#define MYSQL_PW	"myPi333"
#define MYSQL_DB	"dasgip_db"
#define MY_PORT	         3306
#define WIN_HOST	"10.3.0.54" // from  /etc/rresolv.conf nameserver

#define QUERY_SIZE	2048
void finish_with_error(MYSQL *con);

MYSQL * mysql_con_init();
void mysql_con_connect( MYSQL *con);
void update_vessel_status(DasgipState *s, char *my_query, int query_size, int unit_id);
//void update_vessel_status(DasgipState me, char *my_query,int query_size, int uint_id );
void update_vessel_actions(char *my_query, int query_size, int unit_id);
void mysql_check_send_query(MYSQL*con, char *my_query);

MYSQL_RES * results_query_handle(MYSQL *con);
void results_assign_value_handle(DasgipState *my_new, MYSQL_RES *results);


#endif /* end of file */
