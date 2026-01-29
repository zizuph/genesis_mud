/* Coronet in Barrows for Halloween
 * September 2003 by Finwe
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"


void
create_object()
{
    seteuid(getuid());
    set_name("coronet");
    add_adj(({"ancient" ,"battered"}));
    add_name("_shire_coronet_");
    set_short("ancient battered coronet");
    set_long("This is an ancient coronet that has been battered from " +
        "years of misuse. It is a wide band of metal, covered with gold " +
        "and decorated with gems. On the front, the center rises to a " +
        "point, where a large gem was once set, but now there is only " +
        "an empty hole. The " + short() + " once decorated the brow " +
        "of an ancient ruler, but now it's dented terribly.\n");

    /* The crown can be worn on the head only*/
    set_slots(A_BROW);

    /* We won't make the crown take up any space on the head.
     */
    set_layers(0);

    /* We allow layers to be worn under the head */
    set_looseness(2);

    set_keep(1); 

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_VALUE,   25);
}


/*
 * We need to override leave_env() so that we can be sure to remove
 * the item if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}


void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
    return;
}

