#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_CLIMB	20

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("the steep bank of a valley");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("An old gnarled oak extends its roots twisting like snakes "
      + "down the steep crumbling bank. A deep valley lies to the south. "
      + "At its bottom runs a hurrying stream, and beside it on the hither "
      + "side a road goes winding down like a pale ribbon.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "The towering walls of Mordor lie to the east. Out of those walls "
      + "the long valley comes in an ever-widening through towards the "
      + "Anduin."));
    add_item(({"forest","wood","woodlands","herbs","thicket"}), BSN(
        "The trees are large and scatttered. Great ilexes of huge girth "
      + "stand in wide glades with here and there among them hoary "
      + "ash-trees, and giant oaks."));
    add_item(({"valley", "vale", "road", "stream", }), BSN(
        "The valley comes out of the mountains to the east in an "
      + "ever-widening trough towards the Anduin. On its further side "
      + "the woods gather again, blue and grey, marching on southwards. "
      + "At the bottom of the valley a hurrying stream is running towards "
      + "the Anduin, its stony voice coming up the bank. One the hither "
      + "side a road goes winding down towards Osgiliath."));
    add_item(({"bank", }), BSN(
        "The old gnarled oak grows on the top of the northern bank of "
      + "the valley. The bank falls down steeply, over rocks and crevices, "
      + "towards the bottom of the valley. With a little skill, it might "
      + "be possible to climb down the bank to the road."));
    add_item(({"anduin", "river", }), BSN(
        "In the west, the blue wide band of the Anduin is visible, flowing "
      + "gently southwards to the Sea, cutting through the green lands on "
      + "both shores."));
    add_cmd_item(({"bank", "down", }), "climb", "@@climb_bank@@");
    add_exit(ITH_DIR + "nforest/forest7", "northeast", 0, 4);
    add_exit(ITH_DIR + "road/er5",        "southeast", "@@climb_bank_msg@@", 5);
    add_exit(ITH_DIR + "nforest/forest6", "northwest", 0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "bank", "ground", "field", "flowers", "forest", }), 3);
}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

int
climb_bank_msg()
{
    int     skill = (TP->query_skill(SS_CLIMB) - MIN_CLIMB);

    write("You climb down the bank.\n");
    if (skill < 0)
    {
        write("Halfway down the steep slope, you suddenly slip and fall.\n"
          +   "You land at the bottom of the bank, hurting yourself in the fall.\n");
        say(QCTNAME(TP)+" slips, and falls down.\n");
        TP->heal_hp(MIN_CLIMB * 5);
        if (TP->query_hp() < 0)
        {
            TP->do_die(TO);
            log_file("climb", TP->query_name()+" died climbing down a bank "
              + "in Ithilien. "+ctime(time())+".\n");
        }
    }
    return 0;
}
        
string
climb_bank()
{
    set_dircmd("bank");
    climb_bank_msg();
    TP->move_living("climbing down the bank", ITH_DIR + "road/er5");
    return "";
}

