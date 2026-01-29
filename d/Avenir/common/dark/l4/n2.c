/*
n1.c is west
n3.c is east
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  
  set_short("eastern tunnel branch");
  set_long(
      "This branch of the stone tunnel leads northeastward, into " +
      "more darkness. You can hear the squeak of rats and the "+
	  "overwelming stench of ogres.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n");   
  add_exit("/d/Avenir/common/dark/l4/n1","west",0);
  add_exit("/d/Avenir/common/dark/l4/w2","northeast", 0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  add_npc(MON + "rat", 1);
}

int
block()
{
  if (!this_player()->query_wiz_level())
    {
      write (
     "You decide that it is too dangerous to go in the unfinished tunnel.\n");
      return 1;
    }
  else
    {
      write ("Further rooms are discared. Look in l4.discarded/ dir.\n");
      return 1;
    }
}

