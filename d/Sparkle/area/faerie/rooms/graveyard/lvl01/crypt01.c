/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_short("A dark crypt");
    set_long("The dark crypt rises omniously before you. It is an oversized " +
        "building with a rusting iron fence surrounding it. Graves surround " +
        "the building on both sides of the fence. A path leads to it and " +
        "some broken stairs lead up into the crypt.\n");

    add_item(({"building", "oversized building"}),
        "The building is round and made of blocks of gray stone. It has " +
        "a large dome, which is now cracked. The building is unadorned " +
        "and sits on a raised platform.\n");
    add_item(({"dome", "cracked dome"}),
        "The dome is round, and looks like it was once grand, but now " +
        "is cracked. It rests on top of the crypt.\n");
    add_item(({"fence", "iron fence", "rusting iron fence"}),
        "The fence surrounds the building. It is crooked and broken in " +
        "places. It looks like it was once a very nice fence, but has " +
        "fallen into disrepair over the years.\n");
    add_item(({"gray stone", "blocks of gray stone", "stone"}),
        "The blocks of gray stone are large and make up the crypt. They " +
        "are stacked in such a way so that the seams are barely noticeable. " +
        "The blocks of stone look like they were once very smooth, " +
        "but now are weathered and pock-marked; some are even cracked.\n");
    add_item(({"pock marks"}),
        "They are small, random pits in the stones, probably from dirt " +
        "and dust that has blown against them.\n");
    add_item(({"stairs", "broken stairs"}),
        "The stairs are wide and lead up into the crypt. They are made " +
        "of stone, and are cracked and uneven.\n");
    add_item(({"platform"}),
        "It is a square shaped area on which the crypt rests. It is " +
        "made of stones and acts as a foundation for the building.\n");
    add_item(({"graves"}),
        "The graves look old and unkept. They are both inside and outside " +
        "the iron fence. Some have headstones on them,\n");
    add_item(({"fog", "cold fog", "cold gray fog"}),
        "The fog hovers over the ground and covers the grave sites and " +
        "flows through the iron fence and around the crypt. It is dark " +
        "and looks of death. It moves about the graveyard even though " +
        "there isn't any wind.\n");
    

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_07", "southwest");
    add_exit(GRAVE1_DIR + "crypt01_in", "up");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}
