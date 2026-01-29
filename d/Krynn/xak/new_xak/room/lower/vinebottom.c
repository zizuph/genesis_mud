/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit INROOM;

public void
create_xak_room()
{
    set_short("An old deserted street");
    set_long("You are standing at the southern end of the street. " +
	     "The waters draining from above through this level " +
	     "plungs like a waterfall over a precipice to the " +
	     "structures far below. From the precipice the grandeur " +
	     "of fallen Xak Tsaroth is visible to you. Here you can see " +
	     "to the lowest level several hundred feet below. But the roof " +
	     "of the caverna soars about two hundered feet above the cliff, " +
	     "revealing a chain of a lift and the broken base of a " +
	     "great well, through which a dragon can ascend. The side " +
	     "of the cliff face is overgrown with many vines.\n");

    add_exit(LOWER + "sidestreet2", "north");
    
    add_item(({"water", "cliff", "vine", "vines", "cliff face"}), 
	     "Water cascades down the cliff face through the vines. " +
	     "You think you could maybe climb down that cliff face " +
	     "using the vines but it would be very slippery and " +
	     "probably quite dangerous if you aren't a good climber.\n");
}

public int
do_climb(string str)
{
    int skill = TP->query_skill(SS_CLIMB);

    NF("Climb what?\n");

    if (parse_command(str, ({}), "'vine' / 'vines'"))
        return 0;

    if (skill < 25)
    {
        write("You start to climb down the vines but suddenly you lose " +
	      "your grip and fall all the way to the bottom! You slam " +
	      "into the ground with a bonecrushing sound.\n");
	tell_room(TO, QCTNAME(TP) + " trys to climb down the cliff face " +
		  "but loses " + POSSESSIVE(TP) + " grip on a vine and " +
		  "falls down into the darkness below. You hear a " +
		  "sickening bonecrushing sound as " + PRONOUN(TP) + 
		  " hits the ground below.\n");

	TP->move_living("M", CITY + "vinebottom", 1);
        tell_room(E(TP), QCTNAME(TP) + " loses " + POSSESSIVE(TP) +
		  " grip on a vine and falls down, hitting the ground " +
		  "with a bonecrushing sound.\n");

	TP->reduce_hit_point(ftoi((1.0 - (itof(skill) / 30.0)) * 
			      itof(TP->query_max_hp())) + 100); 
	if (!TP->query_hp())
	    TP->do_die(this_object());
	return 1;
    }

    write("You skillfully climb down the cliff face using the vines " +
	  "for handholds. You climb down through the roof and into an " +
	  "old building.\n");
    tell_room(TO, QCTNAME(TP) + " skillfully climbs down the cliff face.\n");
    TP->move_living("M", CITY + "vinebottom", 1);
    tell_room(E(TP), QCTNAME(TP) + " arrives from above climbing the " +
	      "vines.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}







