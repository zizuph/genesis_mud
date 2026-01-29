//
//   A room in the 'monastery' of the Zintra BlackHands of Kalad
//   Assassins guild.
//
//					~Rico   11.04.96
//

inherit "/d/Kalad/common/zintra/room_std";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/zintra/defs.h"

create_room()
{
   ::create_room();

   set_short("Monastery Hallway");
   set_long ("\n"+
      "   This hallway is rather poorly lighted.  The torches mounted "+
      "upon the stone walls cast eerie shadows, which dance as though "+
      "possessed with a soul of their own.  "+
      "\n\n");

   add_item(({ "torch", "torches" }), "\n"+
      "The torches are securely mounted upon the stone wall.  They "+
      "look to be very old, but very plain looking.  They get the "+
      "job done, though, so you can't complain.  "+
      "\n\n");
   add_item(({ "shadow", "shadows", "eerie shadow", "eerie shadows" }),
      "\n"+
      "The shadows flicker all around.  Strange shadows dance upon "+
      "the walls.  You feel a bit uneasy... some of those shadows "+
      "seem to have a more humanoid appearance than seems normal.  "+
      "It must be the lighting playing tricks on your eyes... you "+
      "hope.  "+
      "\n\n");
   add_item(({ "wall", "walls", "stone wall", "stone walls" }), "\n"+
      "These stone walls are thick and sturdy.  They seem to be a "+
      "tad moist, though.  It would probably take the best dwarven "+
      "miners days to tunnel through these walls.  The torches are "+
      "mounted solidly, but you wonder who ensures that they have "+
      "enough fuel to burn constantly...  "+
      "\n\n");

   add_exit(ZINT(rooms/z02), "north");
   add_exit(ZINT(rooms/entrance), "southeast");
}

