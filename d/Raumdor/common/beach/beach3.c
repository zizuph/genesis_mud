/* beach room, sarr */
#include "defs.h"
inherit BEACH_ROOM;

void
create_room()
{
    ::create_room();
    set_short("On the beach off the coast");
    set_long(
      "You are on the beach off the coast. The sea is off to the west. " +
      "A tall wall runs north with large, jagged rocks piled where it " +
      "meets the water.\n");
    add_item("wall", "The wall runs from the south and into the water. " + 
      "It is made of well-aligned stone blocks. Looking closely, you can " +
      "see subtle carvings all over the surface.\n");
    add_item(({"beach"}), "It stretches out to the north.\n");
    add_item(({"rocks"}),
      "They are tall and jagged. You don't see a way around them.\n");
    add_cmd_item(({"wall", "stone wall"}), "climb",
      "It is too tall and smooth to climb.\n");
    add_exit(BEACH_DIR + "beach1", "north");
}
