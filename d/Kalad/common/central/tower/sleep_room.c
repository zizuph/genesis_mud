/* 
Bell tower, sleeping room for the bell-man.
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
set_short("A room west of the bell tower");
   set_long("The walls in this room show signs of "+
      "decay; The plaster on them is cracked up and has "+
      "fallen down several places, filling the floor with "+
      "grey dust. Except from a small bed in the corner and towards "+
      "the exit east, where some dragging feet have made a small "+
      "path in the thin layer of sand that covers the floor. "+
      "In the eastern room you can see some ropes.\n");
   
   add_item("ropes","You cannot see what they hang from, but "+
      "they end up coiled on the floor.\n");
   add_item("bed","Its a plain wooden bed that looks "+
      "fairly unused.\n");
   add_item("sand","Its fine-grained and soft beneath your feet.\n");
   add_item("walls","The walls are decaying. No doubt about it.\n");
   add_item(({"plaster","dust"}),"Its all over the floor, and some still hanging on the wall.\n");
   
   add_exit(CENTRAL(tower/base),"east",0,-1,-1);
}

