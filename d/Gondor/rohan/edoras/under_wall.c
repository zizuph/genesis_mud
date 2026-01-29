/*
 * /d/Gondor/rohan/edoras/under_wall.c
 *
 * Modification history:
 *	16-April-1998, Gnadnar:	make grating match grate in basement,
 *				conform to domain.rules
 *
 * XXX: what is failure message for "pick lock"?
 * Connects to /d/Gondor/rohan/edoras/basement2.c
 */

//#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/rohan/edoras/grate_common";

#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define	BASEMENT	(EDORAS_DIR + "basement2")

/* prototypes */
public void	create_gondor();
public void	init();
public int	splash();
public int	do_unlock(string arg);
public int	do_pick(string arg);
public int	look_thru_grate(string arg);
int enter_grate(string str);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a tunnel");
    set_long(BSN("This low tunnel runs beneath the city walls. "
      + "A cold, ankle-deep stream gushes forth through an "
      + "iron grate and flows through the tunnel to the northwest."));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);	/* infinite water */

    add_exit("by_stream", "northwest", splash, 2);

    add_item( ({ "low tunnel", "tunnel" }), long);
    add_item( ({"grate", "grating", "iron grate", "iron grating" }),
      "The grate is solidly constructed of iron bars.\n");
//      "It is locked.\n");
    add_item( ({ "iron bar", "iron bars", "bar", "bars" }),
	check_bars);
/*
    add_item( ({ "lock" }),
	BSN("Although slightly rusted, the lock is massive and "+
	    "holds the grate securely shut."));
*/
    add_item( ({ "floor", "ground", "ankle-deep water",
	"cold ankle-deep water", "water", "stream" }),
	BSN("Cold water flows around your ankles, completely covering "
	  + "the floor of the tunnel."));
    add_item( ({ "stone", "wall", "walls", "ceiling", "roof" }),
	BSN("The tunnel walls and ceiling are built of smooth "+
	    "gray stone."));
/*
    add_cmd_item( ({ "sturdy metal grate", "metal grate", "grate",
    	"sturdy metal grating", "metal grating", "grating" }),
	({ "open", "close", "lock" }),
	({ "The grate is locked.\n",
	   "The grate is already closed.\n",
	   "The grate is already locked.\n",
	 }) );
*/

/*
    add_cmd_item( ({ "iron bar", "iron bars", "bar", "bars" }),
	({ "bend", "twist", "move", }),
	bend_bars);
*/

    set_drink_from( ({ "ice-cold stream", "stream" }) );
    reset_room();
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add drink and unlock verbs
 */
public void
init()
{
    ::init();
    init_drink();
//    add_action(do_unlock, "unlock");
//    add_action(do_pick, "pick");
    add_action(look_thru_grate, "look");
    add_action(look_thru_grate, "examine");
    add_action(look_thru_grate, "exa");
    add_action(look_thru_grate, "peer");
    add_action(enter_grate, "wriggle");
} /* init */


/*
 * Function name:	splash
 * Description	:	write a nice msg as they go nw
 * Returns	:	0 (exit allowed)
 */
public int
splash()
{
    /* XXX don't say anything about them becoming wet until
     * we really make them so
     */
    WRITE("You splash northwest through the stream.");
    return 0;
} /* splash */


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
		"[the] [iron] 'grate' / 'grating'  'with' %i", key) &&
	     sizeof(key = NORMAL_ACCESS(key, 0, 0)))
	{
	    write("The "+key[0]->short()+" doesn't fit.\n");
	    return 1;
	}
	if (parse_command(arg, ({ }), "[the] [iron] 'grate' / 'grating' "))
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
    if (parse_command(grate, ({}), "[the] [iron] 'grate' / 'grating'"))
    {
        write("You try to pick the lock.\n"+
              "You failed to pick the lock.\n");
	return 1;
    }
    NF0("No "+grate+" here.\n");
} /* do_pick */


/*
 * Function name:	look_thru_grate
 * Description	:	show who's on the other side of the grate
 * Returns	:	1 on success, 0 on failure
 */
public int
look_thru_grate(string arg)
{
    object	basement,
		*in_basement;
    string	desc;
    int		lightlevel;

    if (!strlen(arg) ||
	!parse_command(arg, ({}),
	    "'through' [the] [iron] 'grate' / 'grating'"))
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
    BASEMENT->short();
    if (!objectp(basement = find_object(BASEMENT)) ||
	((lightlevel = basement->query_prop(OBJ_I_LIGHT)) <= 0 &&
	 (lightlevel + TP->query_prop(LIVE_I_SEE_DARK)) <= 0))
    {
	desc = "All is dark on the other side of the grate.\n";
    }
    else
    {
	desc = "On the other side of the grate is a dingy basement.\n";
	in_basement = FILTER_LIVE(all_inventory(basement));
	switch (sizeof(in_basement))
	{
	case 0:
	    break;
	case 1:
	    desc += BSN(in_basement[0]->query_Art_name(TP)+
		" is standing in the basement.");
	    break;
	default:
	    desc +=  BSN(capitalize(COMPOSITE_LIVE(in_basement))+
		" are standing in the basement.");
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
        TP->move_living("M", "/d/Gondor/rohan/edoras/basement2",1);
        return 1;
    }
    notify_fail("Wriggle between what, the iron bars?\n");
    return 0;
}
