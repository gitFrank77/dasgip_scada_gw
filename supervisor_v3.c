

#include "includes/main.h"
#include "includes/dasgip_state.h"
#include "includes/mysql_utils_v2.h"
#include "includes/dasgip_utils_v2.h"
#include <pthread.h>



typedef struct _thread_args
{
	int vessel_id;
	const char *read_path;
	const char *write_path;
	DasgipState state_old;
	DasgipState state_new;

	MYSQL *con;

}thread_args_t;


 DasgipState state8_old = {0};
 DasgipState state8_new = {0};

 DasgipState state7_old = {0};
 DasgipState state7_new = {0};

 DasgipState state6_old = {0};
 DasgipState state6_new = {0};

 DasgipState state5_old = {0};
 DasgipState state5_new = {0};

 DasgipState state4_old = {0};
 DasgipState state4_new = {0};

 DasgipState state3_old = {0}; // to so compare the with s_new , if mismatch for any varibale is found, update 'set update flag'
 DasgipState state3_new = {0}; // new is used to update the 'action.txt' file

 DasgipState state2_old = {0};
 DasgipState state2_new = {0};

 DasgipState state1_old = {0};
 DasgipState state1_new = {0};

	MYSQL *con_8 =NULL;
	MYSQL *con_7 = NULL;
	MYSQL *con_6 =NULL;
	MYSQL *con_5 = NULL;
	MYSQL *con_4 =NULL;
	MYSQL *con_3 = NULL;
	MYSQL *con_2 =NULL;
	MYSQL *con_1 =NULL;


void *pthread_1_callback(void *arg)
{

       thread_args_t *_arg = (thread_args_t*)arg;


       //	int unit_id = *(int*)arg;
       int unit_id = _arg->vessel_id;
       const char *read_path = _arg->read_path;
       const char *write_path = _arg->write_path;
	
	DasgipState _state_old = _arg->state_old;
	DasgipState _state_new = _arg->state_new;

	MYSQL *_con = _arg->con;

char query[QUERY_SIZE];

int sp_update_flag =0;
while(1)
{

//--[write vessel status to DB]yes
update_vessel_status(&_state_old, query, QUERY_SIZE, unit_id);
//update_vessel_status(_state_old, query, sizeof(query), unit_id);
mysql_check_send_query(_con, query);


usleep(500000); // change to usleep

//--[keep reading state variables from VBA file so they can be appened to s
/*if (read_dasgip_state("vessel_3_state.txt", &s) != 0) {
        printf("Failed to read state file\n");
       // return 1;
    }
*/
read_assign_state(read_path, &_state_old);


//--[read the control variables from DB]
update_vessel_actions(query, QUERY_SIZE, unit_id);
//update_vessel_actions(query, sizeof(query), unit_id);
mysql_check_send_query(_con, query);

//--[save row results]
MYSQL_RES *res = results_query_handle(_con);
//printf("res ptr = %p, num_rows = %llu\n",(void*)res, res ? mysql_num_rows(res) : 0);

//--[assign row result to s_new]
results_assign_value_handle(&_state_new, res);

//--[debug print out values for comparison]
//print_old_new_values(_state_new, _state_old);

	mysql_free_result(res);// free buff
//--[ update actions.txt]
write_vessel_actions(write_path,&_state_new);

//--[compare row results of s_new with s aka. 'prev sp state'
sp_update_flag = DasgipState_SetPointChanged(&_state_old,&_state_new, epsilon);


//--[if a differene from the state file SP' is detected, error out]
	if( sp_update_flag == 1) // changed detected, update the SPs
	{
//		printf("\n SP update not assigned %s \r\n", __func__);
	
	}

	else if ( sp_update_flag ==0)
	{

		
//	mysql_free_result(res);// free buff
	}
    }

}






int main(void) {

	/*
    	if (read_dasgip_state("vessel_3_state.txt", &s) != 0) {
        printf("Failed to read state file\n");
        return 1;
    }
	*/

	

	con_8 = mysql_con_init();
	con_7 = mysql_con_init();
	con_6 = mysql_con_init();
	con_5 = mysql_con_init();
	con_4 = mysql_con_init();
	con_3 = mysql_con_init();
	con_2 = mysql_con_init();
	con_1 = mysql_con_init();
	
	mysql_con_connect(con_8);
	mysql_con_connect(con_7);
	mysql_con_connect(con_6);
	mysql_con_connect(con_5);
	mysql_con_connect(con_4);
	mysql_con_connect(con_3);
	mysql_con_connect(con_2);
	mysql_con_connect(con_1);
	
	
	//int vessel_3 = 3;

	thread_args_t vessel_8 = {8, "vessel_8_state.txt", "vessel_8_actions.txt", state8_old, state8_new, con_8};
	thread_args_t vessel_7 = {7, "vessel_7_state.txt", "vessel_7_actions.txt", state7_old, state7_new, con_7};
	thread_args_t vessel_6 = {6, "vessel_6_state.txt", "vessel_6_actions.txt", state6_old, state6_new, con_6};
	thread_args_t vessel_5 = {5, "vessel_5_state.txt", "vessel_5_actions.txt", state5_old, state5_new, con_5};
	thread_args_t vessel_4 = {4, "vessel_4_state.txt", "vessel_4_actions.txt", state4_old, state4_new, con_4};
	thread_args_t vessel_3 = {3, "vessel_3_state.txt", "vessel_3_actions.txt", state3_old, state3_new, con_3};
	thread_args_t vessel_2 = {2, "vessel_2_state.txt", "vessel_2_actions.txt", state2_old, state2_new, con_2};
	thread_args_t vessel_1 = {1, "vessel_1_state.txt", "vessel_1_actions.txt", state1_old, state1_new, con_1};



	pthread_t pthread_08, pthread_07, pthread_06, pthread_05, pthread_04, pthread_03, pthread_02, pthread_01;
	pthread_create(&pthread_08, NULL, pthread_1_callback, (void*)&vessel_8);
	pthread_create(&pthread_07, NULL, pthread_1_callback, (void*)&vessel_7);
	pthread_create(&pthread_06, NULL, pthread_1_callback, (void*)&vessel_6);
	pthread_create(&pthread_05, NULL, pthread_1_callback, (void*)&vessel_5);
	pthread_create(&pthread_04, NULL, pthread_1_callback, (void*)&vessel_4);
	pthread_create(&pthread_03, NULL, pthread_1_callback, (void*)&vessel_3);
	pthread_create(&pthread_02, NULL, pthread_1_callback, (void*)&vessel_2);
//	pthread_create(&pthread_01, NULL, pthread_1_callback, (void*)&vessel_1);



	pthread_join(pthread_08, NULL);
	pthread_join(pthread_07, NULL);
	pthread_join(pthread_06, NULL);
	pthread_join(pthread_05, NULL);

	pthread_join(pthread_04, NULL);
	pthread_join(pthread_03, NULL);
	pthread_join(pthread_02, NULL);
//	pthread_join(pthread_01, NULL);






	return 0;

}
