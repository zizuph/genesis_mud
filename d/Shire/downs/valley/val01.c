/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("valley");
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");


    set_extraline("The valley spreads out to the north of you " +
        "while a dark forest spreads out to the south. In the " +
        "distance, the roaring sound of water can be heard as a " +
        "river spills over some falls at the edge of the Barrow " +
        "Downs.");
    add_item(({"falls"}),
        "They can't be seen, though they can be heard. Obviously " +
        "it is from a great river.\n");
    add_item(({"river", "great river"}),
        "The river can't be seen, though it can be heard spilling " +
        "over some falls nearby.\n");
    set_add_valley_descrs();
    add_item(({"dark forest", "forest", "old forest"}),
        "This is an old forest and has an air of distrust to " +
        "travellers and seems to be watching your every move. " +
        "The forest marks the western edge of the Downs.\n");

    add_exit(VAL_DIR + "val02", "north");
    add_exit("/d/Shire/bombadil/rooms/path01", "southwest");
}

