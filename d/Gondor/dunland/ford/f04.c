/*
 *	/d/Gondor/dunland/ford/f04.c
 *
 *	Coded by Zephram.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin: Changed inheritance.
 *	5-Aug-98, Gnadnar: 	Make skills consistent so rooms
 *			   	aren't traps, general cleanup
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "ford.h"

// Prototypes:
public void	create_roads();
public int	descend();

/*
 * Function name:	create_roads
 * Description	:	set up the room
 */
public void
create_roads() 
{
    set_street("steep slope");
    set_where("southeast");
    set_county("Dunland");
    set_land("Rohan");
    set_mountain("Misty Mountains");
    set_vegetation("clinging green shrubbery");
    set_extraline(
	"The slope descends steeply towards a swiftly flowing river, "+
	"perhaps the river Angren.  To the northwest, an old paved road  "+
	"vanishes in the distance.");

    add_exit((DUN_DIR+"ford/f03"), "southeast",
	descend, HARD_TO_CLIMB);
    add_exit((DUN_DIR+"road/r01"), "northwest", 0, 3);

    add_item( ({ "slope", "path", }),
	"The path is steep but negotiable with a minimum of skill.\n");
    add_item("road",
	"The old road to Tharbad runs over cracked and worn paving stones.\n");
    add_item( ({ "river", "isen", "angren", "river isen", "river angren", }),
	BSN("Far below, at the foot of the slope, the river Isen "+
	    "or Angren flows swiftly around a small island."));
    add_item(({"eyot", "island", "isle"}), BSN(
	  "The eyot rises in the middle of the river."));
} /* create_roads */


/*
 * Function name:	descend
 * Description	:	check whether player has skill to descend
 *			safely.
 * Returns	:	0 if has skill, 1 if not 
 *
 * N.B. we do not allow them to descend if they have not the skill,
 * even tho logically they could just fall down the slope, because
 * if they also have poor swimming skill they'll then be trapped.
 * trapping newbies via obvious exits is carrying things a bit far.
 */
public int
descend()
{   
    int	difficulty, skill;

    difficulty = (HARD_TO_CLIMB / 2);
    skill = TP->query_skill(SS_CLIMB);

    if (skill >= difficulty)
    {
	write("You descend the path.\n");
	return 0;
    }

    write("This hill is too dangerous for you to descend safely.\n");
    return 1;
} /* descend */
