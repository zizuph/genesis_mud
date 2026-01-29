#pragma strict_types
/* Temporarily disabled bee-cloner--too many bees! > 45
*/

inherit "/d/Gondor/common/lib/area_room.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define MAX_BEE		12

static int     gBee,
	       gNum;

public void
create_area_room()
{
    int     i, s,
	    seed;
    string  name = explode(file_name(TO), "/")[5];

    set_areatype(7);
    set_areadesc("green-shadowed woodland");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("To the west, the land is falling down in a steep "
      + "slope towards the great valleys along the Anduin. Through the "
      + "last trees between here and the edge of the forest, the sky "
      + "is visible. In the distance lies the river Anduin. The air is "
      + "filled with the sweet and pungent smell of herbs and flowers.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        "From here the mountains in the east are hidden by many tree tops.\n");
    add_item(({"forest","wood","woodlands","herbs"}), BSN(
	"The forest is less dense here than further to the north, the trees "
      + "are larger and less scattered. Large oaks, cedars, and ash trees "
      + "are growing here, but all are dwarved by a giatn linden growing "
      + "right at the edge of the forest. The ground is covered by many different herbs "
      + "and flowers filling the air with sweet and pungent smells."));
    add_item(({"lime-tree", "linden", "linden tree", }), BSN(
	"The linden is the larger than any other tree here, with boughs "
      + "extending for many feet in all direction. It is growing right on "
      + "the edge of the forest, on top of the slope, dominating the "
      + "landscape for many miles. On the east side of the trunk, protected "
      + "by its wide girth from rain and wind, you notice a small hole."));
    add_item(({"trunk", "hole", }), BSN(
	"The little hole in the trunk of the linden is too high to look "
      + "into it. But you might be able to poke into it with your hand."));
    add_item(({"brink", "forest edge", "edge", "edge of the forest", }), BSN(
        "Just west of here is an edge where the hill country ends in a "
      + "steep slope that is falling down to the great vales. The edge "
      + "continues to the south and to the north, sometimes falling "
      + "suddenly and sheer, sometimes in long hillsides."));
    add_item(({"anduin", "great vales", "vales", "river", }), BSN(
        "Far west, beyond the vales that stretch from the brink of the "
      + "hills towards to bank of the river, the river Anduin itself can "
      + "be seen, flowing gently southwards, like a broad band of blue "
      + "dividing the green lands on both banks."));
    add_item(({"vales", "valleys", "vale", }), BSN(
	"The steep slope west of here leads into one of the great vales "
      + "of Ithilien that are on the east bank of the mighty river Anduin "
      + "between Cair Andros in the north and Emyn Arnen in the south. "
      + "At the bottom of the valley are green meadows and fields."));
    add_exit(ITH_DIR + "nforest/forest2", "north", 0, 4);
    add_exit(ITH_DIR + "nforest/forest4", "south", 0, 4);

    for (i = 0, s = strlen(name); i < s; i++)
	seed += name[i];

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("ithilien"), seed),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("middle earth"), seed + 1),
                     ONE_OF_LIST_WITH_SEED(HERB_MASTER->query_herbs("forest"), seed + 2), }),
                  ({ "ground", "field", "flowers", "forest", }), 3);

}

string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

static void
clone_bee()
{
    object  bee;

    if ((gNum >= MAX_BEE) || (random(MAX_BEE) < gNum))
    {
	remove_alarm(gBee);
	gBee = 0;
	return;
    }

    gNum++;
    bee = clone_object(NPC_DIR + "bee");
    bee->move_living("M", TO);
    tell_room(TO, "A bee comes flying out of the hole, buzzing angrily.\n");
}

public int
do_poke(string str)
{
    object  obj;

    NFN("Poke into what?");
    if (!strlen(str))
        return 0;

    str = LOW(str);
    if ((str != "hole") && (str != "into hole") &&
	(!parse_command(str, TP, "[into] [in] 'hole' 'with' %o", obj)))
        return 0;

    if (objectp(obj) &&
	((function_exists("create_object", obj) != "/std/weapon") ||
	!(obj->query_wt() & W_IMPALE)))
    {
	write("You cannot poke into the hole with that "
	  + obj->query_name() + ".\n");
	return 1;
    }
    write("You poke into the hole in the trunk of the linden with your "
      + (objectp(obj) ? obj->short() : "hand") + ".\n");
    say(QCTNAME(TP) + " pokes into a hole in the trunk of the linden "
      + "tree with "+LANG_ADDART(obj->short())+".\n");
/*
    tell_room(TO, "There is an angry buzzing coming from the linden tree.\n");

    if (!gBee || !sizeof(get_alarm(gBee)))
        gBee = set_alarm(2.0, 5.0, clone_bee);
*/
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_poke, "poke");
/*

    if (random(MAX_BEE) > (gNum + MAX_BEE/2))
        set_alarm(10.0 + rnd() * 20.0, 0.0, clone_bee);
*/
}

public void
reset_room()
{
    set_searched(-2);
    gNum = 0;
}

