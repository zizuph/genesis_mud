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
 
//    set_extraline("You are outside the forge and the smith.");
    set_extraline("You are at the north end of the path. A bowery is to " +
        "the west, and a blacksmith to the east.");

    
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
    add_item("bowery",
        "The bank stands to the west of here where elves visit to purchase " +
        "bows, arrows, and other similar supplies.\n");
    add_item("shop",
        "The inhabitants and visitors of the valley may buy an " +
        "sell things at the shop. As a result, it is one of the " +
        "busier places in the valley.\n");
//    add_exit(VALLEY_DIR + "n_path03", "north");
    add_exit(VALLEY_DIR + "n_path02",   "south");
    add_exit(VALLEY_DIR + "smith",      "east");
    add_exit(VALLEY_DIR + "bowery", "west");

}
 
string short_desc()
{
    return "A northern path in the Valley";
}
