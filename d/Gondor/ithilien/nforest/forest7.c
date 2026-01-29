#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  crow;

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("at a forest edge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("The forest covers the hills and slopes to the north. "
      + "Here, at the edge of the forest, the trees are larger and "
      + "stand far apart. Between them, ferns and brambles are growing. "
      + "To the south lies a deep valley, with a road and a river "
      + "running westwards at its bottom.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "Behind the tree tops to the east loom the dark mountains of "
      + "Mordor like a black shadow. They rise for many thousand feet, "
      + "guarding the borders of the Black Land."));
    add_item(({"hills", "slopes", "slope", }), BSN(
	"The land between the mountains to the east and the river to the "
      + "west is falling gently down towards the river. The higher, "
      + "eastern slopes are covered by green woodlands. West of the "
      + "forests and the hills the great vales of Ithilien open, with "
      + "the green meadows and fields between tree-covered ridges."
      + "Here you are on the northern bank of one of these vales that "
      + "is reaching farther east than most of the others."));
    add_item(({"forest","wood","woodlands","trees",}), BSN(
	"The forest here is made up of large trees standing in small "
      + "groups with wide glades and brambles in between. Further north "
      + "the trees are smaller and grow closer to each other, casting "
      + "the land there into shadows."));
    add_item(({"thicket", "ferns", "brambles", "bushes", }), BSN(
	"Large ferns and wastes of brambles grow in the wide glades "
      + "between the trees. They seem to get thicker to the east."));
    add_item(({"valley", "road", "river", }), BSN(
	"The valley comes running out of the mountains rising in the "
      + "east, falling steeply in an ever-widening trough towards the "
      + "Annduin. At its bottom runs a hurrying stream, sending its silent "
      + "murmur even up to this place high on the banks of the valley. "
      + "Beside the stream, on this side of it, a road winds down like "
      + "a pale ribbon."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "The Anduin can just barely be seen beyond the green lands to the "
      + "west as a broad band of blue. On this bank of the river, the great "
      + "green vales of Ithilien stretch westwards from the forests towards "
      + "the river."));
//  add_exit(ITH_DIR + "nforest/forest8", "east",      0, 4);
    add_exit(ITH_DIR + "nforest/hill",    "southwest", 0, 4);
    add_exit(ITH_DIR + "nforest/forest6", "west",      0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "ground", "field", "flowers", "forest", }), 3);

    reset_room();
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

public void
reset_room()
{
    set_searched(-2);

    if (objectp(crow))
	return;

    crow = clone_object(NPC_DIR + "crow");
    crow->set_restrain_path(ITH_DIR);
    crow->set_random_move(5);
    crow->move_living("down", TO);
}

