/*
 *      /d/Gondor/ithilien/nforest/ridge.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 *	31-Aug-1998, Gnadnar: don't kill rabbits and the like in check_climb()
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

// how hard is it to climb the slope?
#define HARD_TO_CLIMB  20 

public int     check_climb();
public string  climb_bank();

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("stony ridge");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar and fir");
    set_extraline("A road cleaves its way here through the ridge. The " +
        "banks leading down to the road are sheer-sided in the middle. " +
        "On the other side of the cutting, one can make out large " +
        "thickets and a tumbled land of rocky ghylls and crags. To the " +
        "west, gentle slopes running down towards the valley of the " + 
        "Anduin are covered with small woods of resinous trees, fir " +
        "and cedar and cypress and other kinds, with wide glades " +
        "between them.");

    add_item( ({ "mountains", "mountain-range", "mountain", 
		 "ephel duath", }), BSN(
        "The mountains named Ephel Duath appear to be dark grey from " +
        "here. You judge the mountains to be between 5000 to 7000 feet " +
        "tall, and you guess they are several miles away now."));
    add_item("road", BSN(
        "The long straight road runs north towards the Morannon, the Black " +
        "Gates of Mordor. It was made in a long lost time, and it is in " +
        "bad repair. The handiwork of the Men of old can still be seen " +
        "in its straight sure flight and level course."));
    add_item( ({ "forest", "wood", "woods" }), BSN(
        "Small woods of resinous trees, fir and cedar and cypress and other " +
        "kinds cover the gentle slopes west of the road. Wide glades are among " +
        "them, and groves and thickets there are of tamarisk and pungent " + 
        "terebinth, of olive and bay. There are junipers and myrtles; and thymes " +
        "that grow in bushes, or with their woody creeping stems mantle in deep " +
  	"tapestries the hidden stones."));
    add_item( ({ "cutting", "ridge", "banks", "bank", }), BSN(
  	"The road cleaves its way through this ridge running down from the " +
  	"slopes of the Ephel Duath here. In the middle of the ridge, the banks " +
  	"are sheer-sided, but towards the southern end, the bank seems climbable."));

    add_cmd_item( ({ "ridge", "bank", "down", }), "climb",
		 climb_bank);
    set_up_herbs( ({ HERB_DIR + "astaldo", HERB_DIR + "basil", 
		     HERB_DIR + "garlic",  HERB_DIR + "oregano", 
		     HERB_DIR + "thyme",  }), 
		  ({ "forest", "ground", "field", "flowers", }), 3);

    add_exit(ITH_DIR + "nforest/ridge2",   "north",     0, 1);
    add_exit(ITH_DIR + "road/nr8",         "east",      check_climb, 15);
    add_exit(ITH_DIR + "nforest/downhill", "southwest", 0, 2);

    (ITH_DIR + "road/nr4")->load_me();
}

public int 
check_climb()
{
    int		try_climb,
		skill;

    if (!TP->query_humanoid())
    {
	return 0;
    }

    skill = TP->query_skill(SS_CLIMB);
    try_climb = 2 * HARD_TO_CLIMB / 3;
    try_climb += random(try_climb) + 1;

    if (skill < try_climb)
    {
	write("You try to climb down the bank.\n" +
	      "Suddenly you lose your footing.\n" +
	      "You tumble down the bank, painfully hitting several " +
	      "boulders in the process.\n");
	say(QCTNAME(TP) + " tries to climb down the bank, but falls down.\n");
	TP->reduce_hit_point((try_climb - skill) * 5);
	if (TP->query_hp() <= 0)
	{
	    write("You fall onto your head and are mortally wounded.\n");
	    say(CAP(TP->query_pronoun()) + " is mortally wounded.\n");
	    set_alarm(0.0, 0.0, &(TP)->do_die(TO));
	    log_file("traps", TP->query_name() + " killed by " +
		     file_name(TO) + " (" +
		     ((try_climb - skill) * 5) + "). " + 
		     ctime(time()) + ".\n");
	}
    }
    else
	write("You manage to climb down the bank.\n");
    write("\nYou are now on the road to the Morannon!\n" +
	  "The armies of the Dark Lord are using this road, too, " +
	  "and they do not like spies!\n\n");
    return 0;
}

public string
climb_bank()
{
    check_climb();
    TP->move_living("east", ITH_DIR + "road/nr8");
    return "";
}
