/*
 * /d/Gondor/pelargir/misc/bathhouse/obj/soap.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../bath.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h";

public void	create_object();
public string	long_desc();
public void	init();
public void	hook_smelled();
public int	do_bathe(string arg);


/*
 * Function name:	create_object
 * Description	:	set up the bar of soap
 */
public void
create_object()
{
    set_name( ({ "soap", "bar", "bar of soap", SOAP_NAME }) );
    set_pname( ({ "soaps", "bars", "bars of soap", (SOAP_NAME+"s") }) );
    set_short("bar of soap");
    set_pshort("bars of soap");
    set_long(long_desc);
    add_prop(OBJ_I_WEIGHT, 113);	/* 4 oz */
    add_prop(OBJ_I_VOLUME, 98);		/* 3x2x1 inches */
    add_prop(OBJ_I_VALUE, 0);
} /* create_object */


/*
 * Function name:	long_desc
 * Description	:	VBFC for soap desc
 * Returns	:	string -- the desc
 */
public string
long_desc()
{
    return BSN("The oblong bar of soap is fairly soft, and " +
	"sweetly scented.");
} /* long_desc */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(do_bathe,  "wash");
    add_action(do_bathe,  "clean");
    add_action(do_bathe,  "bathe");
    add_action(do_bathe,  "soap");
    add_action(do_bathe,  "lather");
    add_action(do_bathe,  "scrub");
} /* init */


public void
hook_smelled()
{
    write("The soap has a faint herbal fragrance.\n");
} /* hook_smelled */


/*
 * Function name:	do_bathe
 * Description	:	respond to attempts to bathe
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_bathe(string arg)
{
    int		tmp;
    object	dirtyob;

    if (strlen(arg))
    {
	arg = LOW(arg);
    }
    else
    {
	arg = "me";
    }

    if (arg == "me" ||
	arg == "myself" ||
	arg == TP->query_real_name())
    {
	if (TP->query_prop(LIVE_S_SITTING) != TUB_NAME)
	{
	    notify_fail("You cannot " + QVB + " until you are " +
		"in a bath tub.\n");
	    return 0;
	}
	if (!objectp(present("soap", TP)))
	{
	    notify_fail("You cannot bathe without soap!\n");
	    return 0;
	}

	tmp = random(3);
	WRITE( ({
	    "You cover yourself with soapy lather.",
	    "You soap yourself from head to toe.",
	    "You rub soap briskly over your body, working up " +
		"a fine froth of bubbles.",
	    })[tmp] );
	SAY( ({
	    " covers " + OBJECTIVE(TP) + "self with soapy lather.",
	    " soaps " + OBJECTIVE(TP) + "self from head to toe.",
	    " rubs soap briskly over " + POSSESSIVE(TP) +
		" body, working up a fine froth of bubbles.",
	    })[tmp] );

	if (TP->query_prop(PLAYER_I_BATH) == I_AM_WET_AND_DIRTY)
	{

	    /* this is the first time they've bathed, so
	     * remove all known dirty objects/shadows/sublocs/etc
	     * and restore a little fatigue.
	     */
	    if (objectp(dirtyob = present("dirty", TP)))
	    {
	        dirtyob->remove_object();
	    }
	    if (objectp(dirtyob = present(SIRITH_MUD, TP)))
	    {
	        dirtyob->remove_object();
	    }
	    if (objectp(dirtyob = present(GRUNT_STINK, TP)))
	    {
	        dirtyob->remove_object();
	    }
	    if (TP->query_dirty_shadow())
	    {
	        TP->remove_shire_dirty_shadow();
	    }
	    TP->remove_subloc(KALAD_DIRTY_SUBLOC);
	    TP->remove_subloc(GRUNT_STINK_SUBLOC);
	    TP->remove_prop(LIVE_I_DIRTY);

	    TP->add_fatigue(FATIGUE_RESTORED);
	    write("You feel refreshed.\n");
	}
	TP->add_prop(PLAYER_I_BATH, I_AM_SOAPY);
	return 1;
    }
    NF0(CAP(QVB) +" yourself, perhaps?\n");
} /* do_bathe */
