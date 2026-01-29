/*
 * /d/Gondor/common/guild/obj/chess_medal.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * The "Chess Master of Gondor" medal, awarded to the current
 * champion.  
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	CHESS_MEDAL_SUBLOC	"_chess_medal_subloc"
#define	CURRENT_CHAMPION	"ecila"
#define	CHESS_MEDAL_FILE	(RANGER_DIR + "obj/chess_medal")

public void	create_object();
public void	init();
public int	wear(string arg);
public int	remove(string arg);
public string	show_subloc(string subloc, object on, object for_obj);
public void	enter_env(object inv, object from);
public string	query_auto_load();

static int	Worn;	/* we fake "wear" so as not to consume a slot */


/*
 * Function name:	create_object
 * Description	:	set up the medal
 */
public void
create_object()
{
    set_name( ({ "medallion", "medal", "_gondor_chess_medal" }) );
    set_adj( ({ "gleaming", "gold" }) );
    set_long(BSN("The gleaming gold medallion is engraved with " +
	"the symbol of a rook."));

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_SELL,
	"You cannot bear to part with the gleaming gold medallion.\n");
    add_prop(OBJ_M_NO_DROP,
	"You cannot bear to part with the gleaming gold medallion.\n");
} /* create_object */


/*
 * Function name:	init
 * Description	:	add 'wear' and 'remove'
 */
public void
init()
{
    ::init();
    add_action(wear, "wear");
    add_action(remove, "remove");
} /* init */


/*
 * Function name:	wear
 * Descrtipion	:	wear the medal
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
wear(string arg)
{
    if (!strlen(arg) ||
	member_array(TO, FIND_STR_IN_OBJECT(LOW(arg), TP)) < 0)
    {
	NF0("Wear what?\n");
    }
    if (Worn)
    {
	NF0("You already are wearing the gleaming gold medallion.\n");
    }
    Worn = 1;
    write("You wear the gleaming gold medallion.\n");
    SAYBB(" wears a gleaming gold medallion.");
    set_no_show_composite(1);	/* don't show in inventory */
    TP->add_subloc(CHESS_MEDAL_SUBLOC, TO);
    return 1;
} /* wear */


/*
 * Function name:	remove
 * Description	:	remove the medal
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
remove(string arg)
{
    if (!strlen(arg) ||
	member_array(TO, FIND_STR_IN_OBJECT(LOW(arg), TP)) < 0)
    {
	NF0("Remove what?\n");
    }
    if (!Worn)
    {
	NF0("You are not wearing the gleaming gold medallion.\n");
    }
    Worn = 0;
    write("You remove the gleaming gold medallion.\n");
    SAYBB(" removes a gleaming gold medallion.");
    set_no_show_composite(0);	/* show in inventory */
    TP->remove_subloc(CHESS_MEDAL_SUBLOC);
    return 1;
} /* remove */


/*
 * Function name:	show_subloc
 * Description	:	show the medal on player
 * Arguments	:	string subloc -- the subloc of interest
 *			object on -- the objet to which the subloc
 *				     is linked
 *			object for_obj -- the object that's looking
 * Returns	:	string -- the description
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != CHESS_MEDAL_SUBLOC)
    {
	return "";
    }
    if (for_obj != on)
    {
	return CAP(PRONOUN(on))+" is wearing a gleaming gold medallion "+
	    "engraved with the symbol of a rook.\n";
    }
    /* N.B. return this even if they are doing 'inventory' */
    return "You are wearing a gleaming gold medallion "+
	"engraved with the symbol of a rook.\n";
} /* show_subloc */


/*
 * Function name:	enter_env
 * Description	:	mask parent to be sure we're where we belong
 * Arguments	:	object inv -- the new environment
 *			object from -- the old environment
 */
public void
enter_env(object inv, object from)
{
    string	name;
    ::enter_inv(inv, from);

    if (objectp(ENV()))
    {
	name = ENV()->query_real_name();
	if (name != CURRENT_CHAMPION &&
	    SECURITY->query_wiz_dom(name) != "Gondor" &&
	    SECURITY->query_wiz_rank(name) < WIZ_ARCH)
	{
	    set_alarm(1.0, 0.0, remove_object);
	}
    }
} /* enter_env */


/*
 * Function name:	query_auto_load
 * Description	:	make the medal autoloadi
 * Returns	:	string -- the medal filename
 */
public string
query_auto_load()
{
    return CHESS_MEDAL_FILE + ":";
} /* query_auto_load */
