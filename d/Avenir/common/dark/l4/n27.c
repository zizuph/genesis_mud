/*
n21.c is E
n28.c is W
n29.c is S
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("rocky tunnel");
  set_long(
   "The uneven floor grows extremely rocky here, making it"
+" difficult to keep your footing.  The tunnel turns, heading east and south,"
+" and to the west there appears to be a large chamber.\n");


  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

  AI("dust", "It is thick on the floor. Your footsteps stir " +
   "it up and cloud the air.\n");

  AI(({"dirt","stone","stones","rock","rocks","rubble","debris"}),
   "It partially blocks the passage.  There is too much to bother "+ 
   "trying to dig past or through it, just step over it.\n");

  ACI(({"dirt","stone","stones","rubble","debris"}), "dig",
   "You start digging, but soon tire.\n");

  AE(L4+"n21","east",0,DIRT);
  AE(L4+"n29","south",0,DIRT);
  AE(L4+"n28","west",0,DIRT);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;

  add_npc(MON + "archaelogist", 1,&->equip_me());	  

}


