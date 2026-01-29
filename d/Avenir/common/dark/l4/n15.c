/*
n14.c is W
n16.c is S
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
reset_room()
{
  object glove;
  
  if (!present ("glove", this_object()))
    {
      glove = clone_object (OBJ + "r_glove");
      glove->move (this_object());
    }
}

void
create_room()
{
  set_short("corner");
  set_long("The wide underground passageway turns here, "+
      "going west and south.  Some rocks are strewn across "+
      "the floor here.\n");
  
  add_exit(L4 + "n14","west",0);
  add_exit(L4 + "n16","south",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
  add_item("rocks", "The rocks do not hold your interest.\n");
  
  AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
   "Very uninteresting stone.\n");
	add_npc(MON + "bat", 2);
  reset_room();
}

