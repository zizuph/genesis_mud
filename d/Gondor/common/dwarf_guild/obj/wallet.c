/*
 * /d/Gondor/common/dwarf_guild/obj/wallet.c
 *
 * Copyright (C) Stas van der Schaaf - Januari 10 1994
 *               Mercade @ Genesis
 *
 * This is a wallet. A nice feature about this wallet is that if you put
 * any money in it, it will autoload. This is done by making a call to
 * WALLET_RECOVER when the player logs in again.
 *
 * Revision history:
 *     November 6, 1998, outcommented the query_auto_load() function as
 *         the mudlib currently does a deep_inventory() on autoloading
 *         items. There is no need to use the wallet-recover.
 *     November 1, 2001, changed to standard keeping on by default.
 */

#pragma save_binary

inherit "/std/receptacle.c";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define WALLET_RECOVER (DWARVEN_RACE_GUILD_OBJECTS + "wallet_recover")
#define WALLET_ID      (DWARVEN_RACE_GUILD_PREFIX + "wallet")
#define NO_SELL_PROP   ("@@contents@@")

/*
 * Prototype.
 */
void set_keep(int keep = 1);

void
create_container()
{
    set_name("wallet");
    add_name("portfolio");
    add_name(WALLET_ID);

    set_pname("wallets");
    add_pname("portfolios");

    set_adj("leather");
    add_adj("supple");

    set_short("supple leather wallet");
    set_pshort("leather wallets");

    set_long(BSN("It is a leather wallet, used to carry money in. The " +
	"leather is very flexible and it looks like a real piece of " +
	"craftmanship."));

    /* We 'unset' the keep protection in order to set our own protection. */
    /* Set the standard keep protection. */
    set_keep(1);

    add_prop(OBJ_I_VALUE,         250);
    add_prop(CONT_I_VOLUME,       300);
    add_prop(CONT_I_WEIGHT,       300);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_CLOSED,         1);
}

/*
 * If the wallet is not empty you cannot sell it.
 */
mixed
contents()
{
    if (sizeof(all_inventory()))
    {
        return "The " + short() + " is not empty.\n";
    }

    return 0;
}

/*
 * Since we have our own no-sell stuff, we must mask these functions.
 */
void
set_keep(int keep = 1)
{
    if (keep)
    {
	::set_keep();
    }
    else
    {
	add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
    }
}

int
query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != NO_SELL_PROP);
}

/*
 * Recovery
 */

string
query_recover()
{
    return MASTER + ":" + query_keep_recover() + query_container_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_container_recover(arg);
}

/*
 * Autoloading
 */

/*
 * I agree that this is not the most beautiful function imaginable, but it
 * works and I have no intention of altering it for the sake of readability
 * or its aesthetic value. What it does is the following. It checks all
 * items in the inventory of this wallet and if they are a coin of a type
 * that I know, it will be added to the list. Then it composes a string of
 * the type
 *
 * arg = "#a#b#c#d#";
 *
 * in which a, b, c and d are the respective numbers of copper, silver, gold
 * and platinum coins in the deep_inventory of the wallet are. This string
 * will be passed along with the name of the WALLET_RECOVERY object.
 */
#if 0
string
query_auto_load()
{
    mapping coins = ([ "copper" : 0, "silver"   : 0,
                       "gold"   : 0, "platinum" : 0 ]);
    object  *inv  = deep_inventory();
    int     i, j;

    for (i = 0; i < sizeof(inv); i++)
    {
        for (j = 0; j < sizeof(m_indices(coins)); j++)
        {
            if (inv[i]->query_prop(HEAP_S_UNIQUE_ID) ==
                ("_coin_" + m_indices(coins)[j]))
            {
                coins[m_indices(coins)[j]] += (int)inv[i]->num_heap();
            }
        }
    }

    return (WALLET_RECOVER + ":#" +
        coins["copper"]    +  "#" +
        coins["silver"]    +  "#" +
        coins["gold"]      +  "#" +
        coins["platinum"]  +  "#");
}
#endif
