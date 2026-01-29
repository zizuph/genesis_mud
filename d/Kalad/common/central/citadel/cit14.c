/* 
Citadel, mess room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, mess room");
   set_long("This room is filled with long wooden tables, since a normal "+
      "dinner here involves feeding many guards. The room is fairly clean "+
      "and has several candles standing on the tables to provide light. "+
      "You feel pretty certain that this must be the best mess hall "+
      "that any guards in Kabal are using.\n");

   add_exit(CENTRAL(citadel/cit15),"northeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit13),"west",0,-1,-1);
}
