/*
     A room in the 'monastery' of the Zintra BlackHands of Kalad
     Assassins guild.

				~Rico   11.04.96
*/

inherit "/d/Kalad/common/zintra/room_std";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/zintra/defs.h"

create_room()
{
   ::create_room();

   set_short("Dark, cramped chamber");
   set_long ("\n"+
      "   This room is incredibly dark, and quite small.  Hardly "+
      "enough room exists here for even a normal sized dwarf to "+
      "move around comfortably in.  "+
      "\n\n");

   add_exit(ZINT(rooms/z01), "northwest");
}

