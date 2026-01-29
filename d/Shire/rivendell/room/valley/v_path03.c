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
 
    set_extraline("You stand on the northwest end of the house. " +
        "North of you can be seen a pasture, while to the south " +
        "lies the porch of the house.");

    add_item(({"porch", "wide porch", "covered porch"}),
        "The porch runs along the front of the house. It is " +
        "covered and offers protection from the elements.\n");
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
    add_item("pasture",
        "The pasture is fenced with some horses grazing within. " +
        "The pasture looks green and well cared for.\n");
    
 
    add_exit(VALLEY_DIR + "v_path04", "northeast");
    add_exit(VALLEY_DIR + "v_path02", "southwest");
 
}
 
string short_desc()
{
    return "A path along the Last Homely House";
}
