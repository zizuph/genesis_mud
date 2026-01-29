inherit "/std/room";
inherit "/d/Calia/sea/water_base";

#include <macros.h>
#include <stdproperties.h>

void
create_room()
{

	::create_surface_room();
   add_item((({"rocks", "boulders", "line of boulders",
      "rock", "boulder"})),
      "Directly to your north a line of granite boulders blocks "+
      "swimming in that direction. Here the rocks are too jagged "+
      "and rough to climb however.\n");

   add_tell("A beautiful, haunting melody floats over "+
      "the sound of the waves...\n");

}
string
long_msg1()
{
    return "To the north you see a barrier of large granite "+
        "boulders that block swimming in that direction.\n";
}
