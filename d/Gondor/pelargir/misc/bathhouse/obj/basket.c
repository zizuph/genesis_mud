/*
 * /d/Gondor/pelargir/misc/bathhouse/obj/basket.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * A basket to hold used towels.
 */

#pragma strict_types

inherit "/std/container";

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
 * Description	:	set up the basket
 */
public void
create_container()
{
    set_name( ({ "basket", "hamper", BASKET_NAME }) );
    add_adj( ({ "large", "towel", "reed" }) );
    set_short("basket"); /* the "contains" msg uses short */
    set_no_show_composite(1);	/* will be in room desc */
    set_long(BSN("The large basket is made of reeds woven " +
	"in an intricate pattern."));

    add_item( ({ "finger-thick reed", "reed", "finger-thick reeds",
	"reeds" }),
	BSN("The finger-thick reeds are wine-coloured and quite " +
	    "smooth.") );
    add_item( ({ "intricate pattern", "pattern", }),
	BSN("The reeds are woven in an intricate pattern of " +
	    "large and small diamonds.") );
    add_item( ({ "large diamond pattern", "large diamond patterns",
	"small diamond pattern", "small diamond patterns",
	"diamond pattern", "diamond patterns", "large diamond",
	"large diamonds", "small diamond", "small diamonds",
	"diamond", "diamonds", }),
	BSN("The large diamond patterns are perhaps four inches " +
	    "tall, and the smaller ones roughly two."));

    /* since we're only gonna accept towels, and no one can
     * take the basket, don't sweat the numbers
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
 * Description	:	only accept towels
 * Returns	:	mixed -- 0 if prev object was a towel
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
	obj->id("towel"))
    {
	return 0;
    }
    return "The basket is intended to hold only towels.\n";
} /* check_insert */


/*
 * Function name:	no_get
 * Description	:	prevent getting basket
 * Returns	:	mixed -- string "" (msgs written here)
 */
static mixed
no_get()
{
    object	att = ENV()->query_attendant();
    if (TP->query_met(att))
    {
	return att->query_name() +
	    " says to you: Please leave the basket alone.\n";
    }
    return "The " + att->query_nonmet_name() +
	" says to you: Please leave the basket alone.\n";
} /* no_get */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to destruct towel if have too many
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
 * Description	:	if hold too many towels, delete some
 */
public void
trim_inv()
{
    object	*towels = all_inventory(TO);
    int		s = sizeof(towels);

    Alarm_id = 0;
    while (--s >= MAX_ITEMS)
    {
	towels[s]->remove_object();
    }
} /* trim_inv */
