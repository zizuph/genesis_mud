/*
 *  /d/Emerald/north_shore/village/wep/tree.c
 *
 *  This is a tree that an Ogre has ripped out of the ground. It
 *  is a very weak weapon, since it is essentially free. It can
 *  be ripped by an Ogre at:
 *
 *      /d/Emerald/north_shore/village/fort_room.c
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/lib/keep";
inherit "/std/weapon.c";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/common/guild/aod/defs.h"

/* Prototypes */
public void        create_weapon();
public int         wield(object wep);
public mixed       check_ogre();


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("tree");
    add_name( ({ "oak", "club" }) );
    add_adj( ({ "young", "small", "uprooted", }) );
    set_short("uprooted oak tree");
    set_long("This young oak tree looks to have recently been"
      + " ripped from the earth. Its exposed roots are torn and"
      + " caked with dried soil.\n");

    add_prop(OBJ_M_NO_GET, "@@check_ogre@@");
    set_default_weapon(15, 15, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 26600);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "A tree ripped from the ground? It is"
      + " quite worthless to a merchant!\n");
    set_wf(this_object());
} /* create_weapon */


/*
 * Function name:        wield
 * Description  :        redefine to see if the player is an Ogre
 * Arguments    :        object wep - the weapon object
 * Returns      :        int 1: wield it,
 *                          -1: don't wield it
 */
public int
wield(object wep)
{
    if (!IS_OGRE(this_player()))
    {
        write("Huh? Wield a tree? Maybe if you were an Ogre or"
          + " something.\n");
        return -1;
    }

    write("You wield the " + short() + " in one of your free"
      + " hands.\n");
    say(QCTNAME(this_player()) + " wields the " + short() 
      + " in one of " + this_player()->query_possessive() + " free"
      + " hands.\n");
    return 1;
} /* wield */


/*
 * Function name:        check_ogre
 * Description  :        Check to see if this is an ogre or not.
 *                       If it isn't an ogre, they can't lift it.
 * Returns      :        mixed: 0 - let them get it
 *                            : string - fail message
 */
public mixed
check_ogre()
{
    if (IS_OGRE(this_player()))
    {
        return 0;
    }

    return "It is too big for you to lift!\n";
} /* check_ogre */