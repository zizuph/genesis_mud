/* 
Citadel, Hallway to the Bell room.
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
   hear_bell = 3;
   set_short("hallway towards the bell-tower");
   set_long("The walls in this low hallway show signs of "+
      "decay. The plaster on them is cracked and has "+
      "fallen down in several places, filling the floor with "+
      "grey dust, except along the middle of the hallway where "+
      "heavy traffic has made a small path leading from "+
      "the door in the north and towards a room west "+
      "of you. You can see some ropes in there.\n");
   
   add_item("ropes","You cannot see what they hang from, but "+
      "they end up coiled on the floor in the room west of you.\n");
   add_item("walls","They are decaying, no doubt about it.\n");
   add_item(({"plaster","dust"}),"Its all over the floor, and some still "+
      "hanging on the walls.\n");
   
   add_exit(CENTRAL(tower/base),"west",0,0,0);
   clone_object(CENTRAL(doors/citadel_belldoor1))->move(TO);
}

