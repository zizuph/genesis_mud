/*
 * /d/Gondor/ithilien/nforest/forest6.c
 *
 * Coded by Olorin, 1996
 *
 * Modification log:
 * Added random rangers.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define LOCATIONS ({ ITH_DIR + "nforest/forest6", \
		     ITH_DIR + "nforest/fernbed", \
		     ITH_DIR + "road/rr3",        \
		     ITH_DIR + "nforest/fpath/fpath7", })

static object  Ranger;

public void
reset_room()
{
    string  dest;

    ::reset_room();
    if (objectp(Ranger))
	return;

    dest = ONE_OF_LIST(LOCATIONS);
    catch(dest->load_me());
    if (!objectp(find_object(dest)))
	return;

    Ranger = clone_object(NPC_DIR + "i_ranger");
    Ranger->arm_me();
    Ranger->set_random_move(60);
    Ranger->move_living("down", dest);
}

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("hill top");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("In all directions, the flanks of the hill are sloping "
      + "down gently, with trees covering them everywhere but to the west. "
      + "There a narrow valley opens, quickly delving deep into the land. "
      + "Out of it, the murmur of a small spring rises to the hill top.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "Behind the tree tops to the east loom the dark mountains of "
      + "Mordor like a black shadow. They rise for many thousand feet, "
      + "guarding the borders of the Black Land."));
    add_item(({"forest","wood","woodlands","trees","thicket"}), BSN(
        "The forest opens to the south, going over into glades in which "
      + "grow scattered groups of large trees. To the north and the east, "
      + "however, the trees grow closer to each other, and between them "
      + "are ferns and brambles."));
    add_item(({"valley", "spring", }), BSN(
	"The valley begins just west of here, cutting deep into the land "
      + "so that after just a few hundred feet it is almost a gorge, with "
      + "sheer cliffs rising to both sides. The spring that feeds the "
      + "stream running through the valley can be heard from here, but not "
      + "seen."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_item(({"hill", "hill top", }), BSN(
	"The hill rises gently above the surrounding land, and the "
      + "long hill-sides are falling down slowly in all directions under "
      + "the eaves of the forest, save to the west, where the valley cuts "
      + "deep into the land."));
    add_exit(ITH_DIR + "nforest/forest7", "east",      0, 4);
    add_exit(ITH_DIR + "nforest/hill",    "southeast", 0, 4);
    add_exit(ITH_DIR + "nforest/forest5", "northwest", 0, 4);


    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")), 
                    ONE_OF_LIST(HERB_MASTER->query_herbs("middle earth")),
                    ONE_OF_LIST(HERB_MASTER->query_herbs("forest")),
                    (HERB_DIR + "attanar"), }),
                  ({ "ground", "field", "flowers", "forest", }), 5);

    reset_room();
}

public string
query_ranger_loc()
{
    if (!objectp(Ranger))
	return "None.\n";

    return file_name(ENV(Ranger));
}
