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
 
    set_extraline("The path turns to the northeast here " +
        "running near the northern cliffs of the valley. The " +
        "river Bruinen rushes past you on the west side as it " +
        "tumbles over a waterfall. South returns you in front " +
        "of the House.");
    
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
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river is fast moving as it heads west out of the " +
        "valley. The water looks cool and clear. It must be icy " +
        "cold coming from the tops of the Misty Mountains.\n");
    add_item("waterfall",
        "The waterfall looks to be well worn from countless " +
        "ages of water. A rainbow colored mist rises from it.\n");
 
    add_exit(VALLEY_DIR + "v_path03", "northeast");
    add_exit(VALLEY_DIR + "v_path01", "south");
 
}
 
string short_desc()
{
    return "A path along the Last Homely House";
}
