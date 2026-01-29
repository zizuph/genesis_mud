/*
 * Track in Evendim orc camp beyond the bushes
 * This track has no tents
 * By Finwe, May 2001
 */

#pragma strict_types

inherit "/d/Shire/lib/herbsearch.c";
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <macros.h>

inherit CAMP_BASE;

void
create_camp_room()
{
	set_extraline("Here the bushes are many, and the grasses " +
        "are sparse patches of tall grass. The grassy field is " +
        "being forced aside by dense bushes. The bushes seem " +
        "to block all exits except north and east.");
        
	add_item(({"track","depression"}),"The track is a well worn " +
        "depression in the ground where countless feet have " +
        "passed by.\n");
    add_item(({"bush","dense bush"}), 
        "The dense bushes block the view of whatever is behind " +
        "them. They look like the bushes that commonly grow in " +
        "the Shire.\n");
    add_item(({"tracks", "orc tracks"}),
        "They are heavy footprints made by many orcs that have " +
        "come this way. The orcs have trampled the grass, " +
        "leaving nothing but a depression in the ground.\n");

    add_item(({"grass","tall grass"}),
        "The grass is tall and green, a pleasure for the eye as " +
        "they wave in the breeze.\n");
    add_cmd_item("tent","enter","There are no tents to enter here.\n");
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    set_search_places(({"bush","bushes","trees", "flowers", "grass"}));
    add_herb_file(SHIRE_HERB_DIR + "huckleberry");
  
	add_exit(CAMP_DIR + "track17", "north");
    add_exit(CAMP_DIR + "track20", "east");

	reset_shire_room();
}

void reset_shire_room()
{
    clone_warning_orcs();
}

