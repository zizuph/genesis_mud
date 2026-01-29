/*
 * /d/Gondor/rohan/edoras/obj/roh_surcoat.c
 *
 * Surcoat for the Rohirrim soldiers
 *
 * Modification history:
 */

#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_object();
public void	leave_env(object from, object to);
public void	appraise_object(int num);


/*
 * Function name:	create_object
 * Description	:	set up the surcoat
 */
public void
create_object()
{
    set_name( ({ "surcoat", "coat", "clothing", }) );
    set_pname("surcoats");
    add_pname("coats");
    add_pname("clothings");
    set_adj( ({ "embroidered", "green", "rohan", "rohirrim" }) );
    set_short("embroidered green surcoat");
    set_pshort("embroidered green surcoats");
    set_long(BSN(
	"This green surcoat is commonly worn by the Riders of " +
	"Rohan. On the front is embroidered in white a prancing "+
           "stallion on a green field."));

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 864);

    /* slot, layers, looseness, object defining wear() and remove()
     * 6 seems to be the default # of layers for armour, and we
     * want to allow wearing this over 1 piece of armour.
     */
    config_wearable_item(A_BODY, 3, 6, TO);
} /* create_object */


/*
 * Function name:	leave_env
 * Description	:	remove surcoat if dropped
 * Arguments	:	object from -- old env
 *			object to -- new env
 */
public void
leave_env(object from, object to)
{
     ::leave_env(from, to);
     wearable_item_leave_env(from, to);
} /* leave_env */


/*
 * Function name:	appraise_object
 * Description	:	called when someone tries to appraise this object
 * Arguments	:	int num -- use this instead of skill, if given
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
} /* appraise_object */
