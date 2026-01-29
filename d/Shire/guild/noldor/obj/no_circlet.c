/* The guild object for the Noldor elf racial guild.
 * June 1999 by Finwe
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/noldor/no_noldor.h"

// Global Vars

void
create_object()
{
    set_name("circlet");
    add_adj(({"finely" ,"hammered"}));
    add_name(CIRCLET_ID);
    set_short("finely hammered circlet");
    set_long("This circlet is made of finely hammered mithril. " +
        "It is shaped like a plain crown and rests on the " +
        "forehead, wrapping itself past the ears. A small gem, " +
        "carved in the shape of a star, is set in the center. " +
        "To learn more about the Noldor, type 'help noldor'.\n");

    add_item(({"gem"}),
        "The gem is a beryl. It is deep green in colour " +
        "and carved in the shape of a star.\n");
    add_item("beryl",
        "The stone is a deep green colour and set in the center " +
        "of the circlet. It has been carved in the shape of a " +
        "star.\n");

    /* The circlet can be worn on the head only*/
    set_slots(A_BROW);

    /* We won't make the circlet take up any space on the head.
     */
    set_layers(0);

    /* We allow no layers to be worn under the head */
    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);

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

    set_alarm(3.0, 0.0, "check_circlet", inv);
}


void
check_circlet(object ob)
{
    if (!IS_MEMBER(TP))
    {
    ob->catch_msg("\n\nA mournful voice echos in your mind saying: " +
        "You are no longer a Noldor and cannot possess your circlet.\n");
    ob->catch_msg("Your circlet melts before your eyes.\n\n");
    remove_object();
	return;
    }
}
