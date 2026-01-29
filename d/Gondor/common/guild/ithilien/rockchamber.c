/*
 *	/d/Gondor/common/guild/ithilien/rockchamber.c
 *
 *	The company office of the Rangers of Ithilien.
 *
 *	Modification log:
 *	19-Feb-1997, Olorin:	Changed includes to inherits.
 *	12-Oct-1998, Gnadnar:   Add some items.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/office.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define GUILD_NUMBER 2
#define DID_VISIT_HENNETH_ANNUN "_ranger_visited_henneth"

/*
 *	Prototypes:
 */
public void	create_office();
public string	long_func();
public string	exa_window();
public void	reset_room();

static object	Door,
                Eqrack,
		Tstand;

/*
 * Function name:	create_office
 * Description	:	set up the room
 */
public void
create_office()
{
    set_short("the rock chamber");
    set_long(long_func);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit((RANGER_ITH_DIR + "erockchamber"), "east", 0, 0);
    add_exit((RANGER_ITH_DIR + "window"),       "west", 0, 0);
    add_exit((RANGER_ITH_DIR + "shop"),         "north", 0, 0);

    add_item( ({ "waters", "water", "waterfall", "curtain",
	"veil", "window", }), exa_window);
    add_item( ({ "archway", "gate" }),
	"A forbidding archway opens west onto a veil of water.\n");
    add_item( ({ "rock-chamber", "cave", "chamber", }),
	BSN("The cave is wide and roughly hewn, with an uneven " +
            "roof. It extends east, and you see an opening west."));
    add_item( ({ "opening", "openings", }),
	BSN("Three openings pierce the rough walls of the cave: an " +
	    "archway to the west, a dark narrow door to the south, " +
	    "and a low open doorway to the north."));
    add_item( ({ "low doorway", "doorway", }),
	"A low unframed opening leads north from the cave.\n");
    add_item("floor",
	"The floor is simply bare rough rock.\n");
    add_item( ({ "wall", "walls" }), BSN(
	"The chamber walls are dark grey rock, rough and unadorned. " +
	"They glisten faintly with moisture."));
    add_item( ({ "moisture" }), BSN(
	"The walls glisten with a thin layer of moisture, as if " +
	"mist from the waterfall sometimes drifts into this chamber."));
    add_item( ({ "ceiling", "roof" }), BSN(
	"The uneven chamber roof does not seem to have been shaped by " +
	"hammer and chisel, but rather by the forces of water and time."));
    add_item( ({ "stone", "rock" }),
	BSN("The rough-surfaced rock is dark grey, almost black. It " +
	"shows no sign of having been smoothed or polished."));

    set_company_number(GUILD_NUMBER);

    reset_room();
} /* create_office */


/*
 * Function name:	long_func
 * Description	:	VBFC for room desc, dependant on time of day
 * Returns	:	string -- the desc
 */
public string
long_func()
{
    string longtxt;

    if (objectp(Tstand) &&
	Tstand->query_torch_is_lit())
    {
    	longtxt = "This wide chamber is roughly shaped from dark grey " +
	    "rock, and the uneven roof stoops low overhead. A torch has " +
	    "been kindled, casting a dim light on the glistening walls. " +
	    "The cave extends inwards to the east, a low doorway " +
	    "opens to the north, and a poster and a plaque hang to " +
	    "one side of a narrow door leading south. ";

    }
    else
    {
    	longtxt = "This wide chamber is roughly shaped from dark grey " +
	    "rock, and the uneven roof stoops low overhead. " +
	    "The cave extends inwards to the east, a low doorway " +
	    "opens to the north, and a poster and a plaque hang to " +
	    "one side of a narrow door leading south. ";
    }

    switch (tod())
    {
    case "night":
	longtxt += "The grey veil of a waterfall is dimly visible " +
	    "through the archway to the west. ";
	break;
    case "early morning":
	longtxt += "To the west, a faint light shines through the " +
	    "grey veil of the waterfall. Day is arising outside. ";
	break;
    case "morning":
    case "noon":
    case "afternoon":
	longtxt += "From the west archway, daylight enters the " +
	    "chamber through the clear curtain of a waterfall. ";
	break;
    case "evening":
	longtxt += "To the west opens a rough-hewn gate of rock, beyond " +
	    "which a thin veil of water shimmers. The level shafts of the " +
	    "setting sun behind beats upon the veil, and the red light " +
	    "breaks into many flickering beams of ever-changing colour. ";
	break;
    }
    return BSN(longtxt);
} /* long_func */


/*
 * Function name:	exa_window
 * Description	:	VBFC for window desc, dependant on time of day
 * Returns	:	string -- the desc
 */
public string
exa_window()
{
    string  desc = "";
    switch (tod())
    {
    case "evening":
	desc = "The waterfall is to the west, and level rays from " +
	    "the setting sun behind it beat upon it, red light being " +
	    "broken into many flickering beams of ever-changing colour. " +
	    "It is as if you are standing at the window of some " +
	    "elven-tower, curtained with threaded jewels of silver " +
	    "and gold, and ruby, sapphire and amethyst, all kindled " +
	    "with an unconsuming fire.";
	break;
    case "night":
    case "early morning":
	desc = "The veil of water is hardly visible now in the " +
	    "darkness of night.";
	break;
    case "morning":
    case "noon":
    case "afternoon":
	desc = "The veil of the waterfall is clearly visible " +
	    "through the archway to the west, and the plash of " +
	    "falling waters echoes gently off the rock walls. " +
	    "Diffuse daylight enters through the veil.";
	break;
    }
    return BSN(desc);
} /* exa_window */


/*
 * Function name:	reset_room
 * Description	:	be sure it has door and torchstand
 */
public void
reset_room()
{
    if (!objectp(Door))
    {
	Door = clone_object(RANGER_ITH_DIR + "rdoor1");
	Door->move(TO);
    }
    if (!objectp(Tstand))
    {
        Tstand = clone_object(OBJ_DIR + "torchstand");
        Tstand->set_lit(1);
        Tstand->set_replace_msg(BSN(
	    "A green-clad ranger arrives, carrying a few torches. " +
	    "She replaces the burned-out torch in the iron stand with " +
	    "a fresh one, lights it, and walks away."));
        Tstand->move(TO);
    }
    if (!objectp(Eqrack))
    {
        Eqrack = clone_object(RANGER_DIR + "obj/eq_rack");
        Eqrack->set_adj("tall");
        Eqrack->set_short("tall equipment rack");
        Eqrack->set_long(Eqrack->query_long()
          + "This rack holds equipment that might not last for long.\n");
        Eqrack->move(TO);
    }
} /* reset_room */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!living(ob))
        return;
    ob->add_prop(DID_VISIT_HENNETH_ANNUN, 1);
}
