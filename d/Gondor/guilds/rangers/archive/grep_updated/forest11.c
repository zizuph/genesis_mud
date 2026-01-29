/*
 *	/d/Gondor/anorien/druedain/forest11.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:  Changed inheritance,
 *                        general revision.
 &
 *   14-April-2004, Tigerlily: Added entrance to ranger tunnel
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

string see_ranger_exit();
int ranger_exit();

public void
create_area_room()
{
    string *herbs = HERB_MASTER->query_herbs("forest");

    set_areatype(7);
    set_areadesc("thicket");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("tall oak");
    set_forest_density(50);
    set_extraline("You are standing in a thicket of large trees and underbrush, " +
        "wondering where to go next. To the north the forest seems to grow " +
        "thinner, while to the east the forest grows thicker.");

    add_exit(COMMON_DIR + "quest/enchant_seed/garden", "north", 0, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest11", "south", test_loc, 2, 1);
    add_exit(DRUEDAIN_DIR + "forest10", "west",  test_loc, 2, 1);
#ifndef NEW_RANGERS_OPEN
    add_exit(DRUEDAIN_DIR + "forest13", "east",  test_loc, 2, 1);
#endif

#ifdef NEW_RANGERS_OPEN
    add_item(({"thicket", "forest"}), &see_ranger_exit());
    add_exit(RANGERS_ITH_TUNNEL + "thicket_entrance", "east", &ranger_exit(),
        0, 1);
#endif

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 1101),
		     ONE_OF_LIST_WITH_SEED(herbs, 1102),
		     ONE_OF_LIST_WITH_SEED(herbs, 1103), }),
		  ({ "forest", "ground", }), 8);
}

string
see_ranger_exit()
{
    object tp = this_player();

    if (!RANGERS_FULL_MEMBER(tp))
    {
        return "The thicket of trees and shrubbery is dense and " +
            "makes it difficult to find your way.\n";
    }
    //else
    return "The thicket of trees and shrubbery is dense and " +
        "makes it difficult to find your way. Your keen eyes notice " +
        "that some branches are bent, creating a place where you can " +
        "enter the thicket to the east.\n";
}
int
ranger_exit()
{
    object tp = this_player();

    if (!RANGERS_FULL_MEMBER(tp) || 
        (MANAGER->query_banished(tp->query_real_name())))
    {
        tp->catch_msg("You feel disoriented as to what " +
            "is the correct direction, so you stop in fear " +
            "of getting lost.\n");
        return 1;
    }
    //else
    return 0;
}


