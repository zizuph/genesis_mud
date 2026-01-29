/*
 * /d/Gondor/pelargir/misc/bathhouse/obj/pot.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * A copper pot to hold used soap.
 */

#pragma strict_types

inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../bath.h"

static int	Alarm_id;

public void	create_container();
static mixed	check_insert();
static mixed	no_get();
public void	enter_inv(object ob, object from);
public void	trim_inv();

/*
 * Function name:	create_container
 * Description	:	set up the pot
 */
public void
create_container()
{
    set_name( ({ "pot", POT_NAME }) );
    add_adj( ({ "copper", "soap", }) );
    set_short("pot"); /* the "contains" msg uses short */
    set_no_show_composite(1);	/* will be in room desc */
    set_long(BSN("The surface of the copper pot gleams "+
	"under a light coating of steam."));

    add_item( ({ "surface of pot", "pot surface", "surface of the pot",
	"surface of the copper pot", "surface", "copper surface", "copper" }),
	BSN("Evidently the pot is polished regularly -- its " +
	    "copper surface is completely free of tarnish."));
    add_item( ({ "mist", "coating", "steam" }),
	BSN("A faint mist of steam glistens on the surface of " +
	    "the pot.") );

    /* since we're only gonna accept soap, and no one can
     * take the pot, don't sweat the numbers
     */
    add_prop(CONT_M_NO_INS, check_insert);
    add_prop(OBJ_M_NO_GET, no_get);
    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_MAX_WEIGHT, 10000000000);
    add_prop(CONT_I_VOLUME, 1);
    add_prop(CONT_I_MAX_VOLUME, 10000000000);
    add_prop(CONT_I_RIGID, 0);
} /* create_container */


/*
 * Function name:	check_insert
 * Description	:	only accept soap
 * Returns	:	mixed -- 0 if prev object was a soap
 *				 string to display if was not
 */
static mixed
check_insert()
{
    int		i;
    object	obj;

    while (objectp(obj = previous_object(i)) &&
	   obj != TO)
    {
	--i;
    }
    if (obj == TO &&
	objectp(obj = previous_object(--i)) &&
	obj->id("soap"))
    {
	return 0;
    }
    return "The pot is intended to hold only soap.\n";
} /* check_insert */


/*
 * Function name:	no_get
 * Description	:	prevent getting pot
 * Returns	:	mixed -- string "" (msgs written here)
 */
static mixed
no_get()
{
    object	att = ENV()->query_attendant();
    if (TP->query_met(att))
    {
	return att->query_name() +
	    " says to you: Please leave the pot alone.\n";
    }
    return "The " + att->query_nonmet_name() +
	" says to you: Please leave the pot alone.\n";
} /* no_get */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to destruct soap if have too many
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!Alarm_id &&
	sizeof(all_inventory(TO)) > MAX_ITEMS)
    {
	Alarm_id = set_alarm(3.0, 0.0, trim_inv);
    }
} /* enter_inv */


/*
 * Function name:	trim_inv
 * Description	:	if hold too many soaps, delete some
 */
public void
trim_inv()
{
    object	*soaps = all_inventory(TO);
    int		s = sizeof(soaps);

    Alarm_id = 0;
    while (--s >= MAX_ITEMS)
    {
	soaps[s]->remove_object();
    }
} /* trim_inv */
