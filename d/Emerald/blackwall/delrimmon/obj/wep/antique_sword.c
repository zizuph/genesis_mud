/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/antique_sword.c
 *
 *  This sword has been sealed for centuries in a very secure barrel in
 *  the store rooms which Formandil and his men used at Del Rimmon
 *  during the their occupation of the region. It is considered a valuable
 *  antique to some weapon experts in Telberin.
 * 
 *  Thanks and appreciation to Gnadnar for all her help making
 *  this sword feel like an antique to the sword persons of Telberin!
 *
 *  Copyright (c) December 1998, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <cmdparse.h>      /* for NORMAL_ACCESS */
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */
public mixed     Found = 0;

/* prototypes */
public void    create_weapon();
public int     do_trade(string arg);
public void    init();

public mixed     query_found() { return Found; }


/*
 * function name:    create_weapon
 * description  :    set up the weapon
 */
public void
create_weapon()
{
    set_name("antique sword");
    add_name( ({ "sword", "_del_rimmon_antique_sword" }) );
    add_adj( ({ "old", "rusty", "rusted", "ancient", "antique" }) );
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("old rusty sword");
    set_long(BSN(
        "A thin layer of reddish rust covers the entire blade of"
      + " this sword, which appears to be very, very old. The"
      + " hilt, however, gleams untarnished by time."));

    add_item( ({"blade", "reddish rust"}), BSN(
        "The entire length of the blade is covered by the thin"
      + " layer of rust, which does not appear to have damaged"
      + " the metal."));
    add_item( ({"hilt", "emblem", "emblem of telberin"}), BSN(
        "The hilt of the old rusty sword boldly bears the"
      + " emblem of Telberin."));

    set_default_weapon(25, 25, W_SWORD, W_SLASH | W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(25, W_SWORD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25, 25));

    add_prop(OBJ_M_NO_SELL,
        "This simply isn't the kind of sword a shopkeeper would"
      + " put up for sale. Perhaps if you found some kind of"
      + " antique dealer, you'd have a trade on your hands.\n");
} /* create_weapon */

/*
 * function name:        do_trade
 * description  :        we check to see if an antique dealer is around
 *                       and if they are, we might trade this sword
 *                       to them.
 * arguments    :        arg - what the player typed
 * returns      :        1 - success, 0 - failure
 */
public int
do_trade(string arg)
{
    mixed   *offered,    /* objects offering to trade */
            *traders;    /* to whom we offer */
    string   tmpstr;
    int      s;

    if (!TP->query_prop("_del_rimmon_antique_trade"))
    {
        NF0("You have not been offered any trade.\n");
    }

    /* two calls to parse_command() to avoid bug when have
     * %i and %l in same format string
     */
    if (!strlen(arg) ||
        !parse_command(LOW(arg), all_inventory(TP),
            "%i 'with' / 'to' %s", offered, tmpstr) ||
        !strlen(tmpstr) ||
        !parse_command(tmpstr, all_inventory(ENV(TP)), "%l",
            traders))
    {
        NF0("Trade what with whom?\n");
    }

    s = sizeof(traders = NORMAL_ACCESS(traders, 0, 0));
    if (s == 0)
    {
        NF0("Trade what with whom?\n");
    }

    if (s > 1)
    {
        NF0("You can only trade with one person at a time.\n");
    }

    s = sizeof(offered = NORMAL_ACCESS(offered, 0, 0));

    if (s == 0)
    {
        NF0("Trade what with whom?\n");
    }

    if (s > 1)
    {
        NF0("You can only trade one object at a time.\n");
    }

    if (offered[0] != TO)
    {
        /* offered to trade something, but not this object */
        NF0("That does not seem to be an acceptable trade.\n");
    }

    if (!strlen(function_exists("trade_antique", traders[0])))
    {
    NF0("That person has not offered you a trade.\n");
    }
    traders[0]->trade_antique(TO, TP);
    return 1;
} /* do_trade */

/*
 * function name:        init
 * description  :        set up some actions for the player
 */
public void
init()
{
    ::init();

    add_action(do_trade, "trade");
} /* init */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. The first player to pick up the sword
 *                gets credit for finding it, and only they can complete
 *                the quest.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!interactive(dest))
    {
        return 0;
    }

    if (Found)
    {
        return 0;
    }

    Found = dest;
} /* enter_env */
