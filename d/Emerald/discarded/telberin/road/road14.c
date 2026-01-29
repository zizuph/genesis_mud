/*
 * Lakeside road that goes to the crossroad of Telberin
 * Based on the kroad files
 * By Finwe
 * January 1997
 */
 
#include "../default.h"
 
inherit LAKEROAD;
 
 
void
create_road()
{
   add_exit(LROAD + "road15", "north");
   add_exit(LROAD + "road13", "southeast");
   set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
