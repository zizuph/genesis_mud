inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
   set_short("A road heading westwards");
   set_long(break_string("This snowy road heads in a westwards direction "
    + "towards a range of mountains high in the sky.  Far to the south, you "
    + "can barely make out a river, with chunks of broken up ice flowing "
    + "slowly in an eastern direction.  There are a few trees around here, "
    + "but not many.  This area was extensively logged to build houses.  "
    + "\n", 70));

   add_item(({"river", "icy river"}), "It brings cold icy water from the "
    + "mountains to Calathin.\n");

   add_item(({"trees"}), "These pine trees are tall and straight.  Perfect "
    + "for building\nlog cabins and houses.\n");

   add_item(({"mountain", "mountains", "mountain range"}), 
      "These mountains are beautiful.  Snow capped and majestic.  "
    + "Breathtaking.\n");

   add_item(({"snow"}), "The snow in these parts reflects a silver color.\n");

   add_exit(TOWNDIR + "road_w7", "southeast", 0);
   add_exit(TOWNDIR + "road_w5", "west", 0);
}
