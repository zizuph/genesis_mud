/*
 * /d/Gondor/minas/s3crc1.c
 *
 * Modification history:
 *	27-Feb-98, Gnadnar:	make door allow "pound" (just as
 *		a real door would), conform to domain.rules.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public void	create_street();
public void	init();
public int	doorclosed();
public int	knock_door(string str);
public void	no_reaction(object pl);
public int	no_unlock(string str);
public int	do_smash(string str);

/*
 * Function name:	create_street
 * Description	:	set up the room
 */
public void
create_street()
{
    set_streetname("Ithilien Street");
    set_circle("First");
    set_areaname("southern");
    set_streettype("dirty alley");
    set_activity(1);
    set_wealth(0);
    set_streetlight(1);
    add_exit(MINAS_DIR + "s2crc1", "east", 0, 1);
    add_exit(MINAS_DIR + "rooms/oldhouse", "north", doorclosed, 0);
    set_extraline("The alley continues east, turning into a street. "+
        "To the north lies an old, gloomy looking building. ");
    add_item("building",
       "The building looks as if it should have been torn down long ago.\n");
    add_item("door",
       "The door looks quite solid.\n");

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

/*
 * Function name:	init
 * Description	:	add the player verbs
 */
public void
init()
{
    ::init();
    add_action("knock_door","knock");
    add_action("knock_door","pound");
    add_action("no_unlock","unlock");
    add_action("do_smash","smash");
    add_action("do_smash","kick");
}    

/*
 * Function name:	doorclosed
 * Description	:	determine state of door and write msg
 * Returns	:	0 if open, 1 if closed
 */
public int
doorclosed()
{
    if (tod() != "night") 
    {
        write("The door to the old building seems to be locked "+
	     "from the inside.\n");
        return 1;
    }
    write("The door slides open with a slight creaking sound.\n");
    return 0;
}

/*
 * Function name:	knock_door
 * Description	:	handle attempts to knock/pound on door
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
knock_door(string str)
{
    string vb = QVB;
    object tp = TP;

    if (str != "door" &&
        str != "on door" &&
        str != "at door")
    {
	notify_fail(CAP(vb)+" on what?\n");
	return 0;
    }
    write("You "+vb+" on the door of the old building.\n");
    SAY(" "+vb+"s on the door of the old building.");
    set_alarm(10.0, 0.0, &no_reaction(tp));
    return 1;
}

/*
 * Function name:	no_reaction
 * Description	:	do the msgs to respond to knocking
 * Arguments	:	object pl -- person who knocked
 */
public void
no_reaction(object pl)
{
    if (present(pl, TO))
    {
        pl->catch_msg("There's no reaction.\n");
        if (tod() == "night")
	{
            pl->catch_msg(".... except for a soft 'click' from the lock.\n");
	}
    }
}

/*
 * Function name:	no_unlock
 * Description	:	respond to attempts to unlock door
 * Argument	:	string str -- whatever the player typed
 * Returns	:	0 (mgs handled via notify_fail)
 */
public int
no_unlock(string str)
{
    string s1, s2;
    if (strlen(str) &&
	(str == "door" ||
	 sscanf(str,"%soor %s", s1, s2) > 0))
    {
    	NF("You cannot find any lock on the door to unlock. \n");
    }
    return 0;
}

/*
 * Function name:	do_smash
 * Description	:	respond to attempts to smash door
 * Argument	:	string str -- whatever the player typed
 * Returns	:	1 if we understand str, 0 if not.
 */
public int
do_smash(string str)
{
    string vb = QVB, vbs;

    if (str != "door" &&
	str != "down door" &&
	str != "door down")
    {
	NF(CAP(vb)+" what?\n");
	return 0;
    }
    if (vb == "smash")
    {
	vb = "try to smash";
	vbs = "tries to smash";
    }
    else
    {
	vbs = vb+"s";
    }
    write("You "+vb+" the door.\n");
    SAY(" "+vbs+" the door.");
    if (tod() == "night")
    {
	tell_room(TO, "The door opens.\n");
    }
    else
    {
	tell_room(TO, "The door neither budges nor breaks.\n");
    }
    return 1;
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

