/*
 * /d/Gondor/pelargir/obj/pel_surcoat.c
 *
 * Surcoat for the Pelargir garrison
 *
 * Modification history:
 * 16 Oct 98, Gnadnar: change inheritance, fix bug that allowed wearing
 *	multiple surcoats, conform to domain.rules.
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
    set_adj( ({ "embroidered", "blue", "pelargir" }) );
    set_short("embroidered blue surcoat");
    set_long(BSN(
	"This blue surcoat is commonly worn by the soldiers of the " +
	"Pelargir garrison. On the front is embroidered in white three "+
    	"ships blossoming like snow, surmounted by a silver crown."));

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
