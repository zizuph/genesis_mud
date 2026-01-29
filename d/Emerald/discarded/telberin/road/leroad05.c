/*
 * Lakeside road that goes to the crossroad of Telberin
 * Based on the kroad files
 * By Finwe
 * January 1997
 */
 
#include "../default.h"
 
inherit LEAHROAD;
 
 
void
create_road()
{
    add_my_desc("\n\n");
    add_exit(LROAD + "leroad04", "northeast");
    add_exit(LROAD + "leroad06", "southwest");
    set_alarm(1.0,0.0,"reset_room");
 
}
 
void
reset_room()
{
}
