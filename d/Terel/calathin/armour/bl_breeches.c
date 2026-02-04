/* 
 *  A breeches for Calathin citizens.
 *  By Shinto 11-2-98
 */
#include "/d/Terel/include/Terel.h"
inherit STDWEARABLE;

#include <wa_types.h>
#include <stdproperties.h>

public void
create_terel_wearable_item()
{
    set_name("breeches");
    set_short("pair of black breeches");
    set_pshort("pairs of black breeches");
    set_adj("black");
    set_long("A "+short()+" mostly worn by men.");

    /* The hat is worn on the head */
    set_slots(A_LEGS);
    set_terel_wearable_item_size(MEDIUM);

    /* The hat takes up two layers of space on the head.  That means
     * an item must have a looseness of at least two in order to be
     * worn over this hat.
     */
    set_layers(1);

    /* Only one layer of clothing can be worn under the hat. */
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,   50);
}

/*
 * We need to override leave_env() so that we can be sure to
 * remove the hat if it gets moved from the wearer while it
 * is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
