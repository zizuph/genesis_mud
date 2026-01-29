/*
 * Copyright (C) 24-December-2000 by Shadow deForest.
 *
 * Creator  : Shadowlynx
 * Date     : 24-December-2000
 * Filename : w_stick.c
 * Purpose  : Description
 * Credits  : Modified from the original file of
 *              1. </d/Earthsea/travellers/obj/walking_stick.c>
 * Includes : Walking stick now holdable.
 *            Customized emotes for the walking stick.
 *            Random generated short desc adjectives.
 *            Choose specific adjectives based on guild level.
 *            Walking stick can be personalized with engravings.
 *            Guild object with help intructions.
 * Updates  :
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>

#define TRAV_SUB "traveller_subloc"

public void
create_object()
{
    set_name("stick");
    add_name(TRAVELLERS_GUILD_EMBLEM_ID);
    set_adj("long");
    add_adj("crooked");
    set_long("This is what weary travellers use to rest their tired " +
        "bodies while walking. Carved into the top portion of the " +
        "stick is a symbol of two crossed axes over a map of the " +
        "world.\nFor help on travellers, type 'help travellers'.\n");

    add_prop(OBJ_M_NO_DROP, "You consider dropping your stick, but realize " +
        "you could not lean on it without it!\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 250);
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (env && living(env))
    {
        env->add_subloc(TRAV_SUB, this_object());

    }
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    env->remove_subloc(TRAV_SUB);
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (subloc != TRAV_SUB)
    {
        "";
    }

    str = ((for_obj == me) ? 
        "You are " : capitalize(me->query_pronoun()) + " is ");

    return str + "carrying a weather beaten walking stick.\n";
}
