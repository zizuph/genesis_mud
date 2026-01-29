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
 
    set_extraline("You stand outside the forge. The stone " +
        "building is solidly built and provides a means for " +
        "the elves to repair their broken armours and " +
        "weapons.");
    
    add_item("path",
        "The path is worn smooth by the many elves that travel " +
        "this way.\n");
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
    add_item("stable",
        "The stable is a wodden structure with a gate facing " +
        "the house. You hear the sounds of horses within it.\n");
    add_item("forge",
        "The forge is a stone building. Sounds of metal being " +
        "shaped can be heard echoing from it.\n");
 
    add_exit(VALLEY_DIR + "v_path07", "east");
    add_exit(VALLEY_DIR + "v_path05", "west");
 
}
 
string short_desc()
{
    return "A path in front of the forge";
}
