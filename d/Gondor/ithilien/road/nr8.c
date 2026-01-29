/*
 *	/d/Gondor/ithilien/road/nr8.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

/* how hard is it to climb the slope? */
#define HARD_TO_CLIMB  20 

public int     check_climb();

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road cleaves its way here through a stony ridge " +
        "in long cutting, deep, and sheer-sided in the middle. Large " +
        "thickets and a tumbled land of rocky ghylls and crags lie to " +
        "the east. The mountains are receding eastward in a great curve " +
        "and are lost in the distance. To the west, gentle slopes running " +
        "down towards the valley of the Anduin are covered with small " +
        "woods of resinous trees, fir and cedar and cypress and other " +
        "kinds, with wide glades between them.\n");
    add_mountains(1, "several miles");
    add_road(3);
    add_forest(3);
    add_item(({"cutting","ridge","banks","bank"}),
  	"The road cloves its way through a stony ridge running down from the " +
  	"slopes of the Ephel Duath here. In the middle of the ridge, the banks " +
  	"are sheer-sided, but towards the southern end, the westward bank seems " +
  	"climbable.\n");
    add_exit(ITH_DIR + "road/nr9",      "north", test_exit,    3);
    add_exit(ITH_DIR + "road/nr7",      "south", test_exit,    3);
    add_exit(ITH_DIR + "nforest/ridge", "west",  check_climb, 15, 1);
}

public int
check_climb()
{
    int     diff  = 2 * HARD_TO_CLIMB / 3,
            skill = TP->query_skill(SS_CLIMB);

    diff += random(HARD_TO_CLIMB) + 1;

    if (diff > skill)
    {
	write("You try to climb the western bank.\n" +
	      "Suddenly you lose your footing.\n" +
	      "You tumble down the bank, painfully hitting several " +
	      "boulders in the process.\n");
	say(QCTNAME(TP) + " tries to climb the bank and falls down again.\n");
	TP->reduce_hit_point((diff - skill) * 5);
	if (TP->query_hp() <= 0)
	{
	    write("You fall onto your head and are mortally wounded.\n");
	    say(CAP(TP->query_pronoun()) + " is mortally wounded.\n");
	    TP->do_die(TO);
	    log_file("traps", TP->query_name() + " killed by " +
		     file_name(TO) + " (" +
		     ((diff - skill) * 5) + "). " + 
		     ctime(time()) + ".\n");
	}
	return 1;
    }
    write("You manage to climb the western bank at the end of the cutting.\n");
    return 0;
}

public int
climb_slope(string str)
{
    if(!strlen(str))
    {
	NFN("Climb what?");
	return 0;
    }

    str = LOW(str);
    if (parse_command(str, ({ }), 
	" 'east' / 'eastern' 'bank' / 'slope' / 'ridge' "))
    { 
	write("The eastern bank is so steep that it is unclimable. \n");
	return 1;
    }
    if (parse_command(str, ({ }), 
	" 'west' / 'western' 'bank' / 'slope' / 'ridge' "))
    { 
	if (!check_climb()) 
	    TP->move_living("west", ITH_DIR + "nforest/ridge");
	return 1;
    }

    if ((str == "slope") || (str == "bank") || (str == "ridge"))
    {
	write("Which bank do you want to climb, the eastern bank or the western bank?\n");
	return 1;
    }
    NFN("Climb? Climb what?");
    return 0;
}

public void
init()
{
    ::init();
    add_action(climb_slope, "climb");
}
