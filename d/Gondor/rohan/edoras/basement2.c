/*
 * /d/Gondor/rohan/edoras/basement2.c
 *
 * Modification history:
 *	16-April-1998, Gnadnar:	add culvert and grate, conformm
 *				to domain.rules
 *
 * XXX: what is failure message for "pick lock"?
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/rohan/edoras/grate_common";

#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	TUNNEL	(EDORAS_DIR + "under_wall")

/* prototypes */
public void	create_gondor();
public void	reset_room();
public void	init();
public int	do_dig(string arg);
//public int	do_unlock(string arg);
//public int	do_pick(string arg);
public string	look_floor();
public int	look_thru_grate(string arg);
int enter_grate(string str);

static int	Dug_here;


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("Stable basement");
    set_long(BSN("The basement is gloomy and damp. "+
	"Water flows along a stone culvert and out "+
	"through a grate in the north wall."));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_I_CONTAIN_WATER, -1);	/* infinite water */

    add_exit("basement", "south", 0);

    add_item( ({ "iron bar", "iron bars", "bar", "bars" }),
	check_bars);

    add_item( ({ "walls", "wall", }),
	"The walls are damp stone.\n");
    add_item( ({ "floor", "ground", "dirt", "earth" }), look_floor);
    add_item( ({ "north wall"}),
	BSN("Set low in the north wall is a sturdy metal grate, "+
	    "through which the culvert empties."));
    add_item( ({ "stone culvert", "culvert", "stone-lined channel",
	"channel", }),
	BSN("The culvert is just a narrow, stone-lined channel. "+
	    "It runs along the base of the east wall and empties "+
	    "its water through the grate."));
    add_item( ({ "water" }),
	BSN("The water flows along the culvert and out through "+
	    "a grate in the north wall. It seems to be quite clean."));
    add_item( ({ "stones", "stone" }),
	"The walls and culvert are built of dark gray stone.\n");
    /* no BSN here .. i want the "it is locked." to be on a line
     * by itself.
     */
    add_item( ({ "sturdy metal grate", "metal grate", "grate" }),
	"The grate is perhaps three feet high and two feet wide.\n");
//	"It is locked.\n");
    add_item( ({ "lock" }),
	BSN("Although slightly rusted, the lock is massive and "+
	    "holds the grate securely shut."));
/*
    add_cmd_item( ({ "sturdy metal grate", "metal grate", "grate",
    	"sturdy metal grating", "metal grating", "grating" }),
	({ "open", "close", "lock" }),
	({ "The grate is locked.\n",
	   "The grate is already closed.\n",
	   "The grate is already locked.\n",
	 }) );
*/
    add_cmd_item( ({ "air", "basement", "stone", "stones", }),
	({ "sniff", "smell" }),
	BSN("The basement has a dank, damp smell."));

    set_drink_from( ({ "stone culvert", "culvert",
	"stone-lined channel", "channel" }) );

} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	clear Dug_here flag
 */
public void
reset_room()
{
    ::reset_room();
    Dug_here = 0;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add drink, dig and unlock verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action("do_dig", "dig");
//    add_action("do_unlock", "unlock");
//    add_action("do_pick", "pick");
    add_action(look_thru_grate, "look");
    add_action(look_thru_grate, "examine");
    add_action(look_thru_grate, "exa");
    add_action(look_thru_grate, "peer");
    add_action(enter_grate, "wriggle");

} /* init */


/*
 * Function name:	do_dig
 * Description	:	handle attempts to dig here
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_dig(string arg)
{
    object	tp;

    if (!strlen(arg) ||
	!parse_command(arg, ({}), "[in] 'ground' / 'here' [with] [shovel]"))
    {
        return 0;
    }

    tp = TP;
    if (!objectp(present("shovel", tp)))
    {
        write("You find that digging in the firm ground without a shovel "+
	      "is impossible.\n");
        SAY(" tries to dig in the ground with "+
	    POSSESSIVE(tp)+" hands, but fails.");
        return 1;
    }
    write("You dig into the ground with the shovel.\n");
    SAY(" digs in the ground with a shovel.");
    Dug_here = 1;
    return 1;
} /* do_dig */


/*
 * Function name:	do_unlock
 * Description	:	handle attempts to unlock the grate
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if they're trying the grate, 0 otherwise
 */
public int
do_unlock(string arg)
{
    object	*key;

    if (strlen(arg))
    {
	if (parse_command(arg, all_inventory(TP),
		"[the] [sturdy] [metal] 'grate' / 'grating'  'with' %i",
		key) &&
	    sizeof(key = NORMAL_ACCESS(key, 0, 0)))
	{
	    write("The "+key[0]->short()+" doesn't fit.\n");
	    return 1;
	}
	if (parse_command(arg, ({ }),
		"[the] [sturdy] [metal] 'grate' / 'grating' "))
	{
	    write("Unlock "+arg+" with what?\n");
	    return 1;
	}
    }
    NF0("Unlock what?\n");
} /* do_unlock */


/*
 * Function name:	do_pick
 * Description	:	handle attempts to pick the grate
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if they're trying the grate, 0 otherwise
 */
public int
do_pick(string arg)
{
    string	grate;

    if (!strlen(arg))
    {
	NF0("Pick lock on what?\n");
    }
    if (sscanf(arg, "lock on %s", grate) != 1)
    {
	grate = arg;
    }
    if (parse_command(grate, ({}),
	"[the] [sturdy] [metal] 'grate' / 'grating'"))
    {
        write("You try to pick the lock.\n"+
              "You failed to pick the lock.\n");
	return 1;
    }
    NF0("No "+grate+" here.\n");
} /* do_pick */


/*
 * Function name:	look_floor
 * Description	:	VBFC for the floor state
 * Returns	:	string -- floor description
 */
public string
look_floor()
{
    if (!Dug_here)
	return "The floor is just bare dirt.\n";
    return "The earth underfoot seems to have been recently disturbed.\n";
} /* look_floor */


/*
 * Function name:	look_thru_grate
 * Description	:	show who's on the other side of the grate
 * Returns	:	1 on success, 0 on failure
 */
public int
look_thru_grate(string arg)
{
    object	tunnel,
		*in_tunnel;
    string	desc;
    int		lightlevel;

    if (!strlen(arg) ||
	!parse_command(arg, ({}),
	    "'through' [the] [sturdy] [metal] 'grate' / 'grating'"))
    {
	return 0;
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
	/* XXX strictly speaking if there is light on the other side
	 * of the grate, then it shouldn't be dark here -- but let's
	 * ignore that.
	 */
	write("It is too dark to see.\n");
	return 1;
    }

    write("You stoop and peer through the grate.\n");
    /* take the simple approach -- just check room light levels
     * to see if other people notice the person stooping, rather
     * than checking LIVE_I_SEE_DARK on each person present
     */
    if (query_prop(OBJ_I_LIGHT) > 0)
    {
	SAY(" stoops and peers through the grate.");
    }

    FIX_EUID;
    TUNNEL->short();
    if (!objectp(tunnel = find_object(TUNNEL)) ||
	((lightlevel = tunnel->query_prop(OBJ_I_LIGHT)) <= 0 &&
	 (lightlevel + TP->query_prop(LIVE_I_SEE_DARK)) <= 0))
    {
	desc = "All is dark on the other side of the grate.\n";
    }
    else
    {
	desc = "On the other side of the grate is a low tunnel.\n";
	in_tunnel = FILTER_LIVE(all_inventory(tunnel));
	switch (sizeof(in_tunnel))
	{
	case 0:
	    break;
	case 1:
	    desc += BSN(in_tunnel[0]->query_Art_name(TP)+
		" is standing in the tunnel.");
	    break;
	default:
	    desc +=  BSN(capitalize(COMPOSITE_LIVE(in_tunnel))+
		" are standing in the tunnel.");
	    break;
	}
    }
    write(desc);
    return 1;
} /* look_thru_grate */

int enter_grate(string str)
{
    if ((str == "between bars") || (str == "between iron bars"))
    {
        write("You squeeze between the iron bars and disappear.\n");
        say(QCTNAME(TP)+ " squeezes between the iron bars and disappears.\n");
        TP->move_living("M", "/d/Gondor/rohan/edoras/under_wall",1);
        return 1;
    }
    notify_fail("Wriggle between what, the iron bars?\n");
    return 0;
}
