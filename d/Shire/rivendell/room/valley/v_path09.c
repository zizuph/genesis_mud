/*
 * Path around the Last Homely House
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
 
    set_extraline("You are on a path on the northeast side of " +
        "the house. The valley dips slightly south towards the " +
        "house. North of you the walls of the of the mountains " +
        "rise up in the distance. West is the garden that " +
        "surrounds this part of the house. A stout fence " +
        "surrounds the garden. The path wanders south and " +
        "northwest.");
 
    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");  
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams  for a criss-cross and diamond " +
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
    add_item("garden",
        "The garden surrounds the house. Many fruit trees, " +
        "vegetables, and edible plants can be seen growing " +
        "there. a split-rail fence surrounds the garden.\n"); 
    set_fence("They are secured to posts that have " +
        "been sunk into the ground.\n");
     
    add_exit(VALLEY_DIR + "v_path10", "south");
    add_exit(VALLEY_DIR + "v_path08",  "northwest");
 
}
 
string short_desc()
{
    return "A path alongside the gardens";
}
