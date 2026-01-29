#include "../default.h"
 
inherit LAKEROAD;
 
 
void
create_road()
{
   add_exit(LROAD + "road02", "west");
    add_exit(OUT_DIR + "p1", "southeast");
   set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
