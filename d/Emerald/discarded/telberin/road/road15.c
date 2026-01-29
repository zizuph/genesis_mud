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
   add_exit(LROAD + "road16", "northwest");
   add_exit(LROAD + "road14", "south");
   set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
