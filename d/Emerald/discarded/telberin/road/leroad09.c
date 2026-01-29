/*
 * Lakeside road that goes to the crossroad of Telberised on the kroad files
 * By Finwe
 * January 1997
 */
 
#include "../default.h"
 
inherit LEAHROAD;
 
 
void
create_road()
{
    add_my_desc("\n\n");
    add_exit(LROAD + "leroad08", "east");
    add_exit(LROAD + "leroad10", "southwest");
    set_alarm(1.0,0.0,"reset_room");
 
}
 
void
reset_room()
{
}
