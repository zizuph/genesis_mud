/*  Basement room in the Mansion.  Coded by Vader on 8/21/92    */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
   set_short("Evil worshiping room");
   set_long(break_string(
    "You can smell the evil in this room.  You have entered a dark and " +
    "terrifying room.  There are various signs of evil all around.  Blood "
   +"covers a small circle in the middle of this room.  It is probably " +
    "where the evil worshipers sacrifice small animals.....At least you " +
    "hope they are small animals.  There is an altar here.  You can pray " +
    "here, if you so desire.  The room is lighted by candles, some dripping " +
    "with fresh blood.  There must have been a sacrifice held here recently." +
    "\n", 70));

   add_item(({"blood"}), "It looks relatively fresh.\n");

   add_item(({"altar"}), break_string(
    "This altar is constructed of a black rock that does not seem to reflect " +
    "any light at all.  It seems to suck in all light, rather than just " +
    "absorb it.  It is decorated in a strange symbol, the likes of which " +
    "you have never seen.\n", 70));

   add_item(({"symbol", "strange symbol"}), break_string(
    "It looks like it might be a representation of a large bird of prey, " +
    "only this one seems to have glowing red eyes, and a rather large, " +   
    "spiked, serpent-like tail.\n", 70));

   add_item(({"circle", "small circle"}), "It is covered in fresh blood.  " +
    "You are unable to tell the type of\nliving thing that the blood came " +
    "from.\n");


   add_exit(BASE + "hall3", "east", 0);

}

init()
{
   ::init();
   add_action("do_pray", "pray");
}

do_pray()
{
   write("You kneel before the altar and pray to the Master of Darkness.\n");
   say(QCTNAME(this_player()) + " kneels before the altar and prays.\n");
    if (this_player()->query_alignment() < -100)
   write("You can feel the presence of the Dark One within you.\n");
   return 1;
}
