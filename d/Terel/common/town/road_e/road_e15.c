/*
This is a standard east road. Mortricia 920723
*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define TO              this_object()
#define BS(message)     break_string(message, 70)

reset_room()
{
   object axeman;
   
   if (present("axeman")) return;
   axeman = clone_object(TOWNDIR + "road_e/axeman");
   axeman -> move(TO);
   axeman = clone_object(TOWNDIR + "road_e/axeman");
   axeman -> move(TO);
}

create_room()
{
   set_short("The east road");
   
   set_long(BS(
         "This icy and snowy road will take you eastwards. There are some " +
         "trees here and there. The road goes along a river.\n"));
   
   add_item(({"tree", "trees"}), BS("These pine trees are all tall and " +
         "straight. Perfect for building cabins and houses.\n"));
   
   add_item(({"snow"}), BS("The snow never disappears in this part of " +
         "the world. Here it's damn cold unless you have warm clothes.\n"));
   
   add_item(({"river", "water"}), BS("The river streams fast, otherwise " +
         "it would have been covered with an ice layer. The water is real " +
         "cold.\n"));
   
   add_exit(TOWNDIR + "road_e/road_e14", "west", 0);
   add_exit(TOWNDIR + "road_e/road_e16", "southeast", 0);
   
   reset_room();
}
