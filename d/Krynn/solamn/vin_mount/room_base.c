/*
 * File likely started by Terminator, possibly edited
 * or finished by Aridor.  I have updated it to handle
 * the cave expansion.
 *
 * Mortis 10.2006
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
/* Added by Lunatari, the old one included ../local.h
 * This file should probably be in room/ or it is a 
 * replacement for room/room_base that has not been
 * put into use yet.
 */
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include CLOCKH

/* Inherit the Krynn room */
inherit R_FILE
inherit PARENT + "palanthas/smell_world";
inherit CAVE + "cave_noises";

#define CREATE "create_vin_mount_room"
#define RESET  "reset_vin_mount_room"

public void			init();
public int			do_smell(string arg);

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room.  It checks
 * whether or not the room should be reset.  The function returns
 * TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
	if (function_exists(RESET, TO))
		return 1;
	return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
	ITEM(({"wall", "walls", "floor", "ground", "ceiling"}), "The walls of "
	+ "these natural caveways have been smoothed into bulbous and odd "
	+ "shapes by millenia of dripping water.  Overhead, twisted formations "
	+ "and stalactites droop and curve down from the ceiling meeting in some "
	+ "places with stalagmites rising from the floor to form brittle pillars "
	+ "of white, yellow, and brown deposits.\n");
	ITEM(({"stalactite", "stalactites", "stalagmite", "stalagmites",
	"formation", "formations", "pillar", "pillars"}), "Overhead, twisted "
	+ "formations and stalactites droop and curve down from the ceiling "
	+ "meeting in some places with stalagmites rising from the floor to "
	+ "form brittle pillars of white, yellow, and brown deposits.\n");

	set_tell_time(45);
	add_tell("@@get_tells@@" + "\n");

	add_smell("vampire", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  The scent of hobgoblin blood is strong here.");
	add_smell("morgul", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("human", "The damp air is heavy with the musky smell of "
	+ "animals living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("elf", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("goblin", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash...  a good cave.");
	add_smell("dwarf", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  This is no dwarven cave to be sure.");
	add_smell("hobbit", "The damp air is heavy with the musky smell of "
	+ "animals living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  What filth!");
	add_smell("gnome", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  Air quality is dangerously compromised.  Very old "
	+ "or very young gnomes should not sustain exposure to these vapors "
	+ "for long.");
	add_smell("minotaur", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("halfhuman", "The damp air is heavy with the musky smell of "
	+ "animals living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("halfelf", "The damp air is heavy with the musky smell of "
	+ "animals living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.");
	add_smell("orc", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash...  a good cave if the scum living here could be "
	+ "cleaned out.");
	add_smell("hobgoblin", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  Not clean at the moment but a good cave.");
	add_smell("kender", "The damp air is heavy with the musky smell of "
	+ "animals living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  Any thought of goodies to eat suddenly diminishes... "
	+ "Shortly after you wonder if there is anything edible around here.");
	add_smell("drow", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  The mold seems to be feeding off a large "
	+ "concentration of refuse nearby.  These humanoids live like filth.");
	add_smell("noldor", "The damp air is heavy with the musky smell of "
	+ "humanoids living in close confinement with occasional wafts of mold, "
	+ "rot, and trash.  Only foul animals would choose to live this way.");
	add_smell("uruk", "The damp air is heavy with the musky smell of "
	+ "hobgoblins living in close confinement with occasional wafts of mold, "
	+ "rot, and trash...  a good cave if the scum living here were to be "
	+ "annihilated.");
	add_smell("presence", "This is not the best form for experiencing the "
	+ "damp, rotten cave air.");
	add_smell("unknown", "You smell the damp air heavy with the musky smells "
	+ "of animals, mold, rot, and trash, but what the heck race are you?  "
	+ "Why not mail Krynn for fun?");

	call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
	call_other(TO, RESET);
}

public void
init()
{
    ::init();  /* vitally important! never forget this line! */

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/
} /* init */


/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}),
		"[the] 'air' / 'here' / 'area' [of] [the] [cave] [caves]"))
	{
		return 0; /* the player used syntax we don't agree with */
	}

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
	 *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


	smell_world(this_player());
	return 1;
} /* do_smell */

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
