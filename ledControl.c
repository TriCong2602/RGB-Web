#include <wiringPi.h>
#include <mysql.h>
#include <stdio.h>
#include <softPwm.h>
#include <stdint.h>


uint8_t led[3] = {0, 1 , 2};

uint8_t r,g,b;

void xuly(uint8_t r, uint8_t g, uint8_t b){
    // cap nhat xung PWM
    softPwmCreate(led[0], 0, r);
    softPwmCreate(led[1], 0, g);
    softPwmCreate(led[2], 0, b);
}

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "cas";
    char *password = "123456"; /* set me first */
    char *database = "ledControl";
    // setup thu vien wiringPi
    wiringPiSetup();

    // Khai bao IO, interrupt, softPWM
    for (int i=0; i<3; i++) {
        pinMode (led[i], OUTPUT);
        softPwmCreate(led[i], 0, 100);
    }

    while(1){
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
        // kiem tra cot isUpdated
        char sql[200];
        sprintf(sql, "select * from rgbValues");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 
        row = mysql_fetch_row(res); //row[0]-> red; row[1]->green
        // NOTES: row la bien dang chuoi ky tu
        if( atoi(row[4])==1){
            r = atoi(row[0]);
            g = atoi(row[1]);
            b = atoi(row[2]);

        }

        xuly(r,g,b);

    }


    return 0;
}