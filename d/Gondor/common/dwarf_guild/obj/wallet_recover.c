/*
 * /d/Gondor/common/dwarf_guild/obj/wallet_recover.c
 *
 * Copyright (C) Stas van der Schaaf - January 10 1994
 *               Mercade @ Genesis
 *
 * This object is used in complyance with the wallet.c to autoload the
 * money that was in the wallet when the player quit. This will take
 * care of his autoload stuff.
 *
 * What it does is a little trick with the autoloading string of a player
 * to let him autoload money that he put in his wallet. The autoload string
 * only allows an object to generate one object, as it should indeed.
 *
 * Revision history:
 *     November 6, 1998, this object is no longer used, as the coins are
 *         now autoloaded even in the deep_inventory() of the player.
 */

#pragma save_binary

inherit "/std/object";

#include <money.h>
#include "../dwarf.h"

#define WALLET_ID DWARVEN_RACE_GUILD_PREFIX + "wallet"

/*
 * Global variables
 */
static private int a1 = 0;
static private int a2 = 0;
static private int a3 = 0;
static private int a4 = 0;

nomask void
create_object()
{
    set_no_show();

    /* should be enough to let it do its job */
    set_alarm(3.0, 0.0, remove_object);
}

nomask static void
return_money(object to)
{
    object wallet;

    if (objectp(to) &&
	interactive(to))
    {
        if (objectp(wallet = present(WALLET_ID, to)))
        {
            to = wallet;
        }

        if (a1)
            MONEY_MAKE_CC(a1)->move(to, 1);
        if (a2)
            MONEY_MAKE_SC(a2)->move(to, 1);
        if (a3)
            MONEY_MAKE_GC(a3)->move(to, 1);
        if (a4)
            MONEY_MAKE_PC(a4)->move(to, 1);
    }

    remove_object();
}

nomask void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    set_alarm(1.0, 0.0, &return_money(to));
}

/*
 * This function should be called with the following string:
 *
 * arg = "#a#b#c#d#"
 *
 * where a, b, c and d are the respective amounts of copper,
 * silver, gold and platinum coins that the player should get.
 */
nomask void
init_arg(string arg)
{
    string foobar;

    if (sscanf(("!" + arg + "!"), "%s#%d#%d#%d#%d#%s",
        foobar, a1, a2, a3, a4, foobar) != 6)
    {
        a1 = 0;
        a2 = 0;
        a3 = 0;
        a4 = 0;
    }
}