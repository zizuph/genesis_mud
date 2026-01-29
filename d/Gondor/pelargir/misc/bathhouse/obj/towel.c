/*
 * /d/Gondor/pelargir/misc/bathhouse/obj/towel.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../bath.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h";
#include "../bath.h"


static int	Wet,
		Dry_alarm_id;

public void	create_object();
public string	long_desc();
public void	init();
public int	do_dry(string str);
public void	dry_towel();
public int	query_wet();
public void	set_wet(int w);


/*
 * Function name:	create_object
 * Description	:	set up the towel
 */
public void
create_object()
{
    set_name( ({ "towel", TOWEL_NAME }) );
    set_adj( ({ "soft", "white", "bath", "large" }) );
    set_short("white towel");
    set_long(long_desc);
    add_prop(OBJ_I_WEIGHT, 125 + random(100));
    add_prop(OBJ_I_VOLUME, 100 + random(50));
    add_prop(OBJ_I_VALUE, 0);

} /* create_object */


/*
 * Function name:	long_desc
 * Description	:	VBFC for towel desc
 * Returns	:	string -- the desc
 */
public string
long_desc()
{
    if (Wet)
    {
	return BSN("The soft white towel is large, quite absorbent, and " +
	    "rather wet.");
    }
    return BSN("The soft white towel is large and quite absorbent. " +
	    "It feels dry and pleasant.");
} /* long_desc */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(do_dry,	"dry");
    add_action(do_dry,	"towel");
} /* init */


/*
 * Function name:	do_dry
 * Description	:	handle attempts to dry off
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_dry(string arg)
{
    int		bathprop;

    if (strlen(arg))
    {
	/* dry off, dry me, dry myself off, ... */
	if (!parse_command(LOW(arg), ({ }),
	    "'me' / 'myself' / '" + TP->query_real_name() +
	    "' / 'off' [off]"))
	{
	    NF0("Dry yourself, perhaps?\n");
	}
    }

    bathprop = TP->query_prop(PLAYER_I_BATH);
    if (bathprop != I_AM_WET_AND_CLEAN &&
	bathprop != I_AM_SOAPY &&
	bathprop != I_AM_WET_AND_DIRTY)
    {
        write("You are not wet.\n");
        return 1;
    }
    if (TP->query_prop(LIVE_S_SITTING) == TUB_NAME)
    {
	WRITE("There's not much point in drying off while you're " +
	    "still in a tub.");
	return 1;
    }

    if (Wet)
    {
	NF0("This towel is too wet to be useful.\n");
    }

    if (bathprop == I_AM_WET_AND_CLEAN)
    {
	TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_CLEAN);
    }
    else
    {
	TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_DIRTY);
    }
	
    write("You dry yourself off with the towel.\n");
    SAY(" dries " + OBJECTIVE(TP) + "self off with a towel.");

    Wet = 1;
    if (!Dry_alarm_id)
    {
        Dry_alarm_id = set_alarm(150.0, 0.0, "dry_towel");
    }
    return 1;
} /* do_dry */


/*
 * Function name:	dry_towel
 * Description	:	reset towel state to dry
 */
public void
dry_towel()
{
    Wet = 0;
    Dry_alarm_id = 0;
} /* dry_towel */

public int	query_wet()	{ return Wet; }
public void	set_wet(int w)	{ Wet = w; }
