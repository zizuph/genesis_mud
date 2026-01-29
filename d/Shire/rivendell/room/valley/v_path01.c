/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
 
    set_extraline("You stand before the Last Homely " +
        "House. It is tall and strong yet comfortable " +
        "looking. A wide porch offers entrance into the " +
        "house. The path heads north and south, west towards " +
        "the forest and east into the house.");
    
    add_item("path",
        "The path is worn smooth by the many elves that travel " +
        "this way.\n");
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams form a criss-cross and diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item(({"porch", "wide porch", "covered porch"}),
        "The porch runs alongth the front of the house. It is " +
        "covered and offers protection from the elements.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river rushes in a northwest direction. It passes " +
        "under a bridge as it heads out of the mountains.\n");
    add_item(({"stone bridge", "bridge"}),
        "The bridge is large and made of stone. It is arched " +
        "and spans the river, connecting the valley with the " +
        "forest.\n");
    add_item("forest",
        "The forest grows along the ridge above you. It's a " +
        "distance away so the details aren't very clear.\n");

    add_exit(VALLEY_DIR + "v_path02", "north");
    add_exit(VALLEY_DIR + "t_path01", "south");
    add_exit(VALLEY_DIR + "w_porch",  "east");
    add_exit(VALLEY_DIR + "bridge",   "west");
 
}
 
string short_desc()
{
    return "A path in the valley of Imladris";
}
