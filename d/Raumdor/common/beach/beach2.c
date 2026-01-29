/* beach room, sarr */
#include "defs.h"
inherit BEACH_ROOM;

object bountiful;

void
create_room()
{
    ::create_room();
    
    seteuid(getuid());
        
    set_short("On the beach off the coast");
    set_long(
      "You are on the beach off the coast. The sea is off to the west. " +
      "A tall wall runs south with large, jagged rocks piled where it " +
      "meets the water.\n");
    add_item("wall", "The wall runs from the south and into the water. " + 
      "It is made of well-aligned stone blocks. Looking closely, you can " +
      "see subtle carvings all over the surface.\n");
    add_item(({"rocks"}),
      "They are tall and jagged. You don't see a way around them.\n");
    add_item(({"beach"}), "It stretches out to the south.\n");
    add_cmd_item(({"wall", "stone wall"}), "climb",
      "It is too tall and smooth to climb.\n");
    add_exit(BEACH_DIR + "beach1", "south");
    
    room_add_object("/d/Raumdor/common/beach/bountiful/obj/bountiful.c");
    
    reset_room();
}


void
reset_room()
{
    /*if (!bountiful)
    {
        bountiful = clone_object("/d/Raumdor/common/beach/bountiful/obj/bountiful.c");
        bountiful->move_object(this_object(), 1);
    }*/
    
    return;
}
