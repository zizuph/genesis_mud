/* 
Citadel, Elite guards room.
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
   add_prop(ROOM_M_NO_TELEPORT, 1);
   hear_bell = 2;
   set_short("Citadel, elite guards room");
   set_long("You find yourself in a plain room with few noticeable "+
      "items in it except a table and some beds. This is where the "+
      "elite guards lives when they are not on duty, earning their pay.\n");

   add_exit(CENTRAL(citadel/cit20),"north",0,-1,-1);

   add_item ("table","It is a wooden table. Nothing special about "+
      "it at all.\n");

   add_item (({"bed","beds"}),"They are made of wood and "+
      "have nothing in them of interest. All they do is to give "+
      "the elite guards a place to sleep when off duty.\n");

}

