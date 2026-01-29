/*
 * Path around the Last Homely House
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit VALLEY_BASE;

object celeia;
 
void
create_valley_room()
{
 
    set_extraline("The path here wanders south along the garden " +
        "on your west. A sturdy fence runs between you and the " +
        "garden. The mountains from the valley north of you.  A " +
        "medium size stand of trees grow to your east, " +
        "obstructing your view of that region. The path wanders " +
        "south and north from here.");
 
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
    add_item(({"fence", "wooden fence", "split-rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have been " +
        "sunk into the ground.\n");
     
    add_exit(VALLEY_DIR + "v_path09", "north");
    add_exit(VALLEY_DIR + "v_path11",  "south");
    reset_shire_room();
 
}
 
string short_desc()
{
    return ("A path behind the house");
}


void reset_shire_room()
{
   if (!objectp(celeia))
    {
	celeia = clone_object(RNPC_DIR + "celeia");
     celeia->set_restrain_path("/d/Shire/rivendell/room/valley");
     celeia->set_random_move(2);
	celeia->move(this_object());
    }
}
