inherit "/std/room.c";

/*  Room in the graveyard.  Coded by Vader on 10/16/92
 *
 *  This particular room will have a neat little feature, so examine
 *  the tombstone....  ;)
 *
 */

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#define PATH "d/Terel/common/town/mansion/graveyard/"

init()
{
   ::init();
   add_action("read", "read");
}

create_room()
{

   set_short("A graveyard");
   set_long(break_string(
    "An eerie glow emanates from this place.  You notice that is has " +
    "also gotten about 10 degrees colder, and the wind has picked up.  " +
    "All of the daylight that once existed around you is gone, with just " +
    "the eerie glow to light your way.  You think you hear a scream, but " +
    "it might have been your imagination.\nA tombstone.\n", 70));

    add_item(({"glow", "eerie glow"}), "A strange glow, emanating from " +
     "all around the room, and particularly\nbright around the tombstone.\n");

   add_item(({"tombstone"}), "This tombstone, which was carved from stone " +
    "very recently, sits upon\na mound of freshly dug dirt.  On the " +
    "face of the tombstone stands an\ninscription.\n");
   add_item(({"inscription"}), "It was carved by a chisel.  You " +
    "could try reading it.\n");

   add_cmd_item("tombstone", "open", break_string("As you " +
      "start to open the tombstone, a shiver runs up your spin!  " +
      "You decide this might not be such a good idea.\n",70));

add_exit(MANSION + "graveyard/grvpath3.c", "west", 0);

}
read(str)
{
   if(!id(str))
    {
     write("Read what?\n");
     return 1;
    }
   
   write("The inscription on the tombstone reads:\n");
   write("                   Here lies\n");
   write("                    " + this_player()->query_name() + "\n");
   write("        Killed by the hand of a drunken Ogre.\n");
   return 1;
}
id(str)
{
   return str == "tombstone" || str == "inscription";
}
