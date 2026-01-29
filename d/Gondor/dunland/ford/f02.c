/*
 *      /d/Gondor/dunland/ford/f02.c
 *
 *      Modification log:
 *      26-Jan-1997, Olorin:    Changed inheritance,
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
    set_street("small rocky island");
    set_where("northwest");
    set_county("Westfold");
    set_land("Rohan");
    set_mountain("Misty Mountains");
    set_vegetation("clinging green shrubbery");
    set_river_name("Isen");
    set_extraline(
	"From this south shore, a steep rocky path climbs north to "
      + "the higher end of the island.  Water rushes over wide rocky "
      + "fords to the northwest and southeast.  Beyond the ford to "
      + "the northwest, a distant path leads up a steep grade. "
      + "On the far side of the river to the southeast, long green "
      + "grass covers the land of Rohan.");

    add_exit((DUN_DIR+"ford/f01"),  "southeast",
	&swim(HARD_TO_SWIM, 5), 5);
    add_exit((DUN_DIR+"ford/f03"),  "northwest",
	&swim(HARD_TO_SWIM, 6), 6);
    add_exit((DUN_DIR+"ford/eyot"), "north",     climb, 8);

    add_item( ({ "river", "isen", "angren", "river isen", "river angren", }),
	BSN("The river Isen or Angren flows from the north to "+
	    "wash swiftly around both sides of the island."));
    add_item(({"shallows", "ford","fords", "fords of isen"}), BSN(
        "The river Isen or Angren runs swiftly over wide shallows. "+
	"It appears relatively easy to swim across here."));
    add_item("water",
        "The water is cool and clear, shallow but swiftly flowing.\n");
    add_item("path",
        "The path is gravelly but negotiable with a minimum of skill.\n");
    add_item(({"eyot", "island", "isle"}), BSN(
	  "The eyot is a small rocky island, rising from a sandy sloping "+
	  "beach on its south side to a stony mass to the north."));
    add_prop(OBJ_I_CONTAIN_WATER,-1);
    set_drink_from("river");
} /* create_roads */


/*
 * Function name:	climb
 * Description	:	check whether player has skill to climb
 *			safely.
 * Returns	:	0 if has skill, 1 if not 
 */
public int
climb()
{   
    int	difficulty, skill;

    difficulty = ((HARD_TO_CLIMB_EYOT / 2) + random(HARD_TO_CLIMB_EYOT) + 1);
    difficulty += random(difficulty) + 1;
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
