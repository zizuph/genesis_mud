/*
 * drow/race/object.c
 *
 * This is the guild object for the Drow racial guild.
 */
#pragma no_inherit
#pragma no_shadow
#pragma save_binary
#pragma strict_types

#include "guild.h"

#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";

private void
create_object(void)
{
    config_wearable_item(A_CHEST, 1, 10, TO);

    add_prop(OBJ_I_WEIGHT,  10);
    add_prop(OBJ_I_VOLUME,  10);
    add_prop(OBJ_I_VALUE, 8640);

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_GIVE,  1);
    add_prop(OBJ_M_NO_SELL,  1);
    add_prop(OBJ_M_NO_BUY,   1);
    add_prop(OBJ_M_NO_INS,   1);
}

public void
config_object(string house)
{
    if (strlen(house))
    {
        set_name(({ "insignia", "badge" }));
        add_name(({ GOBJECT_NAME }), 1);
        set_short("house insignia");
        set_long("This is an insignia which all members of drow houses wear to denote their heritage. Inscribed into the back of the insignia is the word 'drhelp'.\n");
    }
    else
    {
        set_name(({ "brooch" }));
        add_name(({ GOBJECT_NAME }), 1);
        set_short("spider brooch");
        set_long("This is an elegant, yet masterfully crafted brooch of a spider. It is a common adornment for those drow who do not belong to one of the noble houses. Inscribed into the underbelly of the spider is the word 'drhelp'.\n");
    }
}

public int
query_may_recover(void)
{
    return 0;
}
