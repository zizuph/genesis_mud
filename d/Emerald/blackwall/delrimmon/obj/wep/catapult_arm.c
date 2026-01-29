/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/catapult_arm.c
 *
 *  This weapon is created when the catapult at Del Rimmon is fired
 *  and subsequently destroyed. The player must kill or fool the orcs
 *  who come running to get it, and it then is a very decent weapon.
 *
 *  Copyright 1997 by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/lib/keep";
inherit "/std/weapon.c";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

void
create_weapon()
{
    set_name("beam");
    add_name( ({ "arm", "club" }) );
    add_adj( ({ "devastating", "splintered", "massive", "wooden",
                "long" }) );
    set_short("massive wooden beam");
    set_long(BSN("Connected to the end of this long splintered beam is"
               + " a cupped metal basin which looks to have once been"
               + " been the launching arm of a medium sized catapult."
               + " Though it is obviously no longer useful for major"
               + " artillery, it may not have completely outlived its"
               + " usefulness. It looks like it could be a devastating"
               + " weapon if in the right hands."));

    add_prop(OBJ_M_NO_GET,
             "@@check_get:/d/Emerald/blackwall/delrimmon/del_rimmon@@");
    set_default_weapon(35, 50, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 26600);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 50) + random(75));
    set_wf(this_object());
}


/*
 * Function name:        wield
 * Description  :        redefine to see if the player is strong
 *                       enough
 * Arguments    :        object wep - the weapon object
 * Returns      :        int 1: wield it,
 *                          -1: don't wield it
 */
public int
wield(object wep)
{
    int     min_str = 110 + random(11) - 5;

    if (TP->query_stat(SS_STR) < min_str)
    {
        write(BSN("You attempt to heft the " +short()+ " into a"
          + " battle-ready position, but realize that you are not"
          + " strong enough to handle it well."));
        say(QCTNAME(TP) + " attempts to wield the " +short()+ ", but"
          + " does not seem to be able to lift it properly.\n");
        return -1;
    }

    write("Mustering your strength, you heft the " +short()+ " into"
      + " a battle-ready position.\n");
    say(QCTNAME(TP) + " grunts as " +PRONOUN(TP)+ " wields the "
      +short()+ ".\n");
    return 1;
} /* wield */
