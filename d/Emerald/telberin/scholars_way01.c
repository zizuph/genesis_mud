#include "defs.h"

inherit TELBERIN_SCHOLARS_WAY;

public void
create_scholars_way()
{
    set_em_long("Curving out from the southwest, Scholars Way travels"
      + " north of here in a narrow ellipse which rings a long and"
      + " beautiful reflecting pool. This street navigates the Science"
      + " Quarter of Telberin, where the great thinkers among the elves"
      + " record their accomplishments. Just to the south, the Royal"
      + " Magic Garden blossoms in its sanctuary. One can access"
      + " Cantors Way, and the Arts Quarter by travelling southeast.\n");

    add_item( ({ "border", "borders", "border of the garden",
                 "borders of the garden", "sanctuary" }),
        "The garden is well protected, and kept separate from the"
      + " street-level of the city by stone walls.\n");
    add_item( ({ "stone wall", "stone walls", "walls of stone",
                 "garden wall", "garden walls", "walls of the garden",
                 "wall of the garden" }),
        "The wall of the garden is rather tall, allowing only small"
      + " glimpses of what lies beyond.\n");

    add_exit("scholars_way02", "north");
    add_exit("royal_circle02", "southwest");
    add_exit("cantors_way07", "southeast");
}
