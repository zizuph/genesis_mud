#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
   set_short("Fortress hallway");
   set_long("You have arrived at a bend in the hallway, it turns gently\n"
      + "to the north. It seems that someone has feebly attempted to \n"
      + "grow some sort of plant here. It is decaying in this dark and\n"
      + "dank atmosphere. The stones on the floor are letting weeds as \n"
      + "well as insects in from the earth below. You can faintly hear\n"
      + "laughing as well as some rather nauseating noises coming from\n"
      + "the north.\n");

   add_item(({"plant", "decaying plant"}),
      "It seems to be dead, judging from the fact that the roots are "+
      "totally decayed and there are insects all over it.\n");
   add_item(({"insects", "insect"}), "They seem rather disgusting.\n");
   add_item(({"stones", "stone"}), "They are all cut the wrong way, "+
      "and are the incorrect size.\n");
   add_item(({"weeds", "weed"}), "Even these parasites seem to be dying "+
      "in this rancid place.\n");


   add_prop(ROOM_I_INSIDE, 1);

   add_exit("r2", "east");
   add_exit("r4", "north");
}

