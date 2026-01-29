/*
 *     Necklace - guild item for the smiths guild
 *     In this item I have placed all the abilities and emotes
 *     possible to use by both Smiths and Artificiers
 *     Morinir 1996
 *
 *     Emotes and abilites moved to Smith soul (~Shire/smiths/smiths_lay_soul)
 *     Necklace converted from a piece of armour to a wearable item.
 *     Glaurung, August 98
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

void
create_object()
{
    set_name(({"necklace","smiths_necklace"}));
    set_adj("iron");
    set_short("iron necklace");
    set_long("This "+short()+" is the token of membership in the Smiths "+
        "Guild. For guild related topics you can <help smiths>.\n");
    set_slots(A_NECK);
    set_layers(0);
    set_looseness(0);

    add_prop(OBJ_M_NO_STEAL, "That would be useless to you.\n");
    add_prop(OBJ_M_NO_DROP, "Why would you drop your iron necklace?\n");
    add_prop(OBJ_M_NO_GIVE, "Why would you give away your iron necklace?\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 25);
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

string query_auto_load() { return MASTER + ":"; }

public string query_recover() { return 0; }
