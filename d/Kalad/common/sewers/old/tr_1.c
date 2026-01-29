#include "/d/Kalad/defs.h"
inherit SEWERS(sewer_std.c);

void
create_room()
{
   ::create_room();
   set_short("A dark old and brick room");
   set_long("You are stating in a black chamber. You get an "+
   "uneasy feeling here. You hear a loud rumble... Oh no! The "+
   "floor beneath you crumbles away! You fall into the darkness "+
   "below...\n");
   add_exit("/d/Kalad/common/sewers/sr_1.c","sr_1");
}
