/*
 * /d/Gondor/common/dwarf_guild/belt.c
 *
 * Copyright (C) Stas van der Schaaf - January 10 1994
 *               Mercade @ Genesis
 *
 * This belt is the guild object of the Dwarven race guild. The name of the
 * bearer is is branded in/on it. It is the same as the npc version of the
 * belt with some extra's.
 *
 * 2021-04-07 - Cotillion
 * - Added #pragma no_shadow to prevent imbues
 */

#pragma save_binary
#pragma no_shadow   

inherit "/d/Gondor/common/dwarf_guild/arm/npc_belt";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define NO_DROP_TEXT BSN("Remove the belt before you can drop it somewhere.")
#define NO_GIVE_TEXT BSN("Remove the belt before you can give it away.")
#define TMP_I_INIT   ("_tmp_i_init")

void
create_armour()
{
    ::create_armour();

    set_af(TO);

    add_prop(OBJ_M_NO_SELL, BSN("The belt is not for sale."));
    add_prop(OBJ_M_NO_BUY,  BSN("The belt is not for sale."));

    // guild objects do not expire over time as normal equipment.
    // this should not be called in an object without AoB approval!
    remove_item_expiration();
}

/*
 * Stuff to let the player wear the belt on login.
 */

void
wear_belt()
{
    if ((!living(ENV())) ||
        ((!IS_MEMBER(ENV())) &&
         (!(ENV()->query_wiz_level()))))
    {
        return;
    }

    add_prop(TMP_I_INIT, 1);

    set_this_player(ENV());
    wear_me();

    remove_prop(TMP_I_INIT);
}

varargs int
wear(object to_wear)
{
    if (IS_MEMBER(ENV()))
    {
        ENV()->add_cmdsoul(DWARVEN_RACE_GUILD_SOUL);
        ENV()->update_hooks();
    }

    add_prop(OBJ_M_NO_DROP, NO_DROP_TEXT);
    add_prop(OBJ_M_NO_GIVE, NO_GIVE_TEXT);

    /* No wear-message if you wear it on login. */
    return query_prop(TMP_I_INIT);
}

varargs int
remove(object to_remove)
{
    remove_prop(OBJ_M_NO_DROP);
    remove_prop(OBJ_M_NO_GIVE);

    /* No remove-message when you log out. Only bother when the player actively
     * quits, and not when the player is kicked out due to idleness.
     */
    return (query_verb() == "quit");
}

/*
 * Autoloading stuff
 */

string
query_auto_load()
{
    /* only autoload if its owner is a member or a wizard. */
    if (!IS_MEMBER(ENV()) &&
        !(ENV()->query_wiz_level()))
    {
        return 0;
    }

    return ::query_recover();
}

void
init_arg(string arg)
{
    init_recover(arg);

    set_alarm(1.5, 0.0, wear_belt);
}

/*
 * Recovery stuff
 */

string
query_recover()
{
    /* only recover if the owner is not a member and not a wizard. */
    if (IS_MEMBER(ENV()) ||
        ENV()->query_wiz_level())
    {
        return 0;
    }

    return ::query_recover();
}

/*
 * We simulate keepability.
 */

int
query_keep()
{
    return 1;
}
