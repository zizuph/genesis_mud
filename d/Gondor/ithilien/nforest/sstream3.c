/*
 *	/d/Gondor/ithilien/nforest/sstream3.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *   04-Okt-2008, Eowul:    Added drinking support 
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Gondor/defs.h"

#include <stdproperties.h>

public int     cross_stream();

static object *Deer = allocate(2);

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("shallow dell");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("The small stream feeds a small clear lake here. The lake lies " +
    "in the broken ruins of an ancient stone basin, the carven rim of which " +
    "is almost wholly covered with mosses and rose-brambles. " +
    "To the north, there is a slope covered with brown ferns. Beyond it, a thicket " +
    "of dark-leaved bay-trees climbs a steep bank that is crowned with old cedars. " +
    "Close to the basin, several trees lie that have been hewn down. " +
    "Sweet odours from herbs and flowers are in the air everywhere.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
	"From here the mountains are hidden by trees and the stony ridge " +
        "to the east.\n");
    add_item(({"forest", "wood", "woods", "herbs", "groves", "thickets",
	       "thicket", "grove"}), BSN(
        "Many great trees and thick bushes are growing here, planted long " +
        "ago, falling into untended age amid a riot of careless descendants. " +
        "Between the bushes and under the trees, grasses and herbs are " +
        "growing in abundance. You can make out several parsleys and " +
        "myrtles, ginger and mints."));
    add_item(({"parsleys","myrtles","ginger","mints"}), 
	     "You will have to search for herbs to find them!\n");
    add_item( ({"stream"}), BSN("The small stream comes running down from the " +
	"east into this shallow dell. Here it enters the lake running over " +
        "the basin's rim in a small waterfall. The water is clear and fresh."));
    add_item(({"flower","flowers","iris-swords","iris","lily","water-lily"}), 
	BSN("Iris-swords are standing in ranks about the basin's rim, and " +
        "water-lily leaves are floating on the dark gently-rippling surface " +
        "of the lake."));
    add_item(({"lake","basin","pool","water"}), BSN("The small lake lies in " +
        "the broken ruins of an ancient stone basin. A small stream running " +
        "down from the east is feeding it. Water-lily leaves are floating " +
        "on the dark gently-rippling surface of the water; but it is deep " +
        "and fresh, and spills ever softly out over a stony lip at the " +
        "far end."));
    add_item(({"trees", "tree"}), BSN(
        "Several trees have been hewn down wantonly and left to die. " +
        "The fell sign of the Eye has been cut in rude strokes on their " +
        "bark. Behind them, there is a pit of uncovered filth and refuse."));
    add_item(({"pit","refuse","filth"}), BSN("It makes you sick looking " +
        "at it. Luckily it is at least partly hidden by the hewn trees. " +
        "You do not care to investigate it any further since closer by " +
        "the smell must be terrible."));
    add_cmd_item( ({ "pit", }), "enter", "The smell is so terrible " +
		 "that you do not want to go any closer to the pit!\n");

    add_exit(ITH_DIR + "nforest/slope",    "north",               0, 1);
    add_exit(ITH_DIR + "nforest/sstream2", "east",                0, 1);
    add_exit(ITH_DIR + "nforest/bank3",    "south",    cross_stream, 1);
    add_exit(ITH_DIR + "nforest/lake",     "northwest",           0, 1);

    set_drink_from( ({ "stream", "pool", }) );
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_up_herbs( ({ HERB_DIR+"chervil", HERB_DIR+"rosemary",
		     HERB_DIR+"ginger",  HERB_DIR+"clove",
		     HERB_DIR+"dill",    HERB_DIR+"tyelka", }),
 		  ({"thickets", "wood", "thicket", "forest", "ground",
		    "grove", "flowers", "forest"}), 3);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Deer, NPC_DIR + "deer", -1.0);
    Deer->set_restrain_path(ITH_DIR + "nforest/");
}

public int
cross_stream()
{
    write("You cross the small stream.\n");
    return 0;
}

public void
init()
{
    ::init();

    init_drink();
}