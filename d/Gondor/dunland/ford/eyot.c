/*
 * /d/Gondor/dunland/ford/eyot.c
 *
 *      Modification log:
 *	5-Aug-98, Gnadnar: 	Make skills consistent so rooms
 *			   	aren't traps, general cleanup
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "ford.h"


#define	EYOT_BOTTOM	(DUN_DIR+"ford/f02")


// Prototypes:
public void	create_gondor();
public int	descend();


/*
 * Function name:	create_gondor()
 * Description	:	Create the room.
 */
public void
create_gondor()
{
    set_short("Eyot");
    set_long(BSN(
	"Rough-hewn standing stones circle the high point of a "+
	"small rocky island.  Boiling rapids surge and foam all "+
	"around the north of the eyot, and a small steep path descends "+
	"the rocky slope to the south."));

    add_exit(EYOT_BOTTOM, "south", descend, 3);
    add_exit(EYOT_BOTTOM, "down", descend, 3, 1);

    add_item( ({"peak", "eyot", "island"}), BSN(
        "This is the north high point of a small rocky island."));
    add_item( ({"ford", "fords", "fords of Isen", "Fords of Isen",
	"fords of isen"}), 
	"The fords are not visible from here.\n");
    add_item( ({"rocky sloep", "slope", "cliff", "cliffs"}), BSN(
	"The ground falls sharply away from the peak of the "+
	"eyot. It looks impossible to climb down the cliffs in any "+
	"direction but south."));
    add_item( ({"stone", "stones", "standing stone", "standing stones",
                "peak", "monolith", "monoliths"}), BSN(
        "These are upright monoliths as big as ten men, made of hard"+
	" white stone. You cannot seem to discern any writing or"+
	" other clue as to their nature."));
    add_item( ({"water", "rapids"}), BSN(
        "The water is boiling and foaming madly all around the"+
	" rocky isle."));
    add_item( ({"path", "ground"}), BSN(
        "The path is steep and gravelly, but negotiable with a "+
	"minimum of skill."));
} /* create_gondor */



/*
 * Function name:	descend
 * Description	:	check whether player has skill to descend
 *			safely.
 * Returns	:	0 if has skill, 1 if not (but we move them
 *			anyway)
 */
public int
descend()
{   
    int	difficulty, skill;

    difficulty = (random(HARD_TO_CLIMB_EYOT) - 2);
    skill = TP->query_skill(SS_CLIMB);

    if (skill >= difficulty)
    {
	write("You climb down the path.\n");
	return 0;
    }

    write("This hill is too dangerous for you to descend safely.\n"+
	"You lose your footing.\n"+
	"You fall down in a shower of small rocks and gravel!\n"+
	"Your body tumbles to a stop.\n");
    SAY(" tumbles down the hill.");
    TP->reduce_hit_point(difficulty - skill);
    TP->move_living("M", EYOT_BOTTOM);
    tell_room(ENV(TP), QCNAME(TP)+
	" tumbles down the rocky path and lands in a heap.\n",
	TP);
    return 1;
} /* descend */
