/*
 * pants.c
 *
 * A pair of pants to be sold in Dol Amroth.
 *
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

private nomask void
create_object()
{
    set_name("pants");
    add_adj("woolen");
    set_short("pair of woolen pants");
    set_pshort("pairs of woolen pants");
    set_long("This is a pair of woolen pants. They are colourfull " +
	     "and striped.\n");

    set_slots(A_LEGS);
    set_layers(1);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,  350);
}

/*
 * We need to override leave_env() so that we can be sure to remove
 * the anklet if it gets moved from the wearer while it is still worn.
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
