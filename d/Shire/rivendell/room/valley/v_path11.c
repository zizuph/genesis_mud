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
 
    set_extraline("You stand outside the house on eastern side. " +
        "The path wanders in all directions. The path east " +
        "heads through a small forest towards the mountains " +
        "while west takes through an open gate and into the " +
        "house. North seems to head through a small stand of " +
        "trees while south looks to run along the river Bruinen.");
 
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
    add_item(({"gate", "garden gate"}),
        "The gate is simple in design. It is as high as the " +
        "fence, made of split rails and allows visitors " +
        "entrance into the house and garden. The gate is open.\n");
    set_fence("They are secured to posts that have " +
        "been sunk into the ground. A gate stands open letting " +
        "elves and visitors pass through the garden and into " +
        "the house.\n");
     
    add_exit(VALLEY_DIR + "v_path10",  "north");
    add_exit(VALLEY_DIR + "t_path11",  "south");
    add_exit(VALLEY_DIR + "t_path12",  "east");
    add_exit(VALLEY_DIR + "e_porch",   "west");
 
}
 
string short_desc()
{
    return ("A path along the east side of the house");
}
