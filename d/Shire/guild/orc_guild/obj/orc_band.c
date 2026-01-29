/* The guild object for the orc racial guild.
	* Altrus, May 2005
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/orc_guild/orc.h"

// Global Vars

void
create_object()
{
    set_name("band");
    add_adj(({"iron" ,"arm", "thick"}));
    add_name(BAND_ID);
    set_short("thick iron arm band");
    set_long("The arm band is made of thick iron; it is scratched and dented, but still intact. There is a small inscription etched on it.\n");

    add_item(({"inscription", "small inscription"}), "The inscription simply reads 'help orc'.\n");
    
    /* The band is to be worn on the left arm*/
    set_slots(A_L_ARM);

    /* We won't make it take up space.
     */
    set_layers(0);

    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  100);
    add_prop(OBJ_I_VOLUME,   50);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

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

/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
}

void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
    if (inv->query_ghost())
	return;

    set_alarm(3.0, 0.0, "check_band", inv);
}


void
check_band(object ob)
{
    if (!IS_MEMBER(TP))
    {
    ob->catch_msg("\n\nYou are no longer an orc!\n");
    ob->catch_msg("Your iron arm band bursts into flames for a moment, and then is gone.\n\n");
    remove_object();
	return;
    }
}
