/*
 *	/d/Gondor/dunland/ford/f03.c
 *
 *	Coded by Zephram.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin: Changed inheritance.
 *	5-Aug-98, Gnadnar: 	Make skills consistent so rooms
 *			   	aren't traps, general cleanup
 *      17-Mar-00, Stern:       added OBJ_I_CONTAIN_WATER property and drink.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "ford.h"

// Prototypes:
public void	create_roads();
public int	climb();

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
    set_vegetation("sparse green grass and willow shoots");
    set_river_name("Isen");
    set_extraline(
	"A rocky path climbs the slope to the northwest, and water "+
	"rushes over wide rocky shallows to the southeast. "+
	"On the far side of the river, a small island rises in "+
	"the middle of the river.");

    add_exit((DUN_DIR + "ford/f02"), "southeast",
	&swim(HARD_TO_SWIM, HARD_TO_SWIM), HARD_TO_SWIM);
    add_exit((DUN_DIR + "ford/f04"), "northwest",
	climb, HARD_TO_CLIMB);

    add_item( ({ "river", "isen", "angren", "river isen", "river angren", }),
	BSN("The river Isen or Angren flows swiftly around "+
	    "the small rocky island."));
    add_item(({"shallows", "ford","fords", "fords of isen"}), BSN(
        "The river Isen or Angren runs swiftly over wide shallows to "+
	"the southeast. It appears relatively easy to swim across here."));
    add_item("water",
        "The water is cool and clear, shallow but swiftly flowing.\n");
    add_item( ({ "path", "slope", }),
        "The path is rocky, but negotiable with a minimum of skill.\n");
    add_item(({"eyot", "island", "isle"}), BSN(
	  "The eyot rises steeply from the middle of the "+
	  "rushing waters."));
    add_prop(OBJ_I_CONTAIN_WATER,-1);
    set_drink_from("river");
} /* create_roads */


/*
 * Function name:	climb
 * Description	:	check whether player has skill to climb
 *			safely.
 * Returns	:	0 if has skill, 1 if not 
 *
 * N.B. this difficulty should be the same as for descending the
 * path from f04, even tho that's not realistic.  if we let them
 * fall down the path from f04 to here with poor climbing skill
 * and they also have poor swimming skill, they'll then be trapped.
 * trapping newbies via obvious exits is carrying things a bit far.
 */
public int
climb()
{   
    int	difficulty, skill;

    difficulty = (HARD_TO_CLIMB / 2);
    skill = TP->query_skill(SS_CLIMB);

    if (skill >= difficulty)
    {
	write("You climb up the path.\n");
	return 0;
    }

    write("This hill is too dangerous for you to climb safely.\n"+
	"You lose your footing.\n"+
	"You fall down in a shower of small rocks and gravel!\n"+
	"Your body tumbles to a stop near your starting point.\n");
    TP->reduce_hit_point(difficulty - skill);
    SAY(" fails to make it up the slope.");
    return 1;
} /* climb */

public void
init()
{
    ::init();
    init_drink();
}
