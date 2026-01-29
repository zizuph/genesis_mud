/*
 *  /d/Sparkle/area/city/wep/church_weapon.c
 *
 *  New players to the game are able to request a weapon, and are
 *  given one with these basic properties.
 *
 *  given at: /d/Genesis/start/human/town/church.c
 *
 *  Created May 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* prototypes */
public void        create_weapon();
public void        leave_env(object from, object to);
public void        blow_away(object from);
public string      wizinfo();


/*
 * Function name:        create_church_weapon
 * Description  :        dummy constructor function for inheriting
 *                       objects to redefine
 */
public void
create_church_weapon()
{
} /* create_church_weapon */


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
nomask void
create_weapon()
{
    set_name("mist-weapon");
    add_adj( ({ "hazy", "misty", "mistform", "mist", "form" }) );
    add_name("_sparkle_church_mistform_weapon");

    add_prop(OBJ_M_NO_SELL, "It will likely dissolve into thin air"
      + " soon after leaving your possession, and therefore has no"
      + " value to anyone but you.\n");

    add_prop(OBJ_S_WIZINFO,
        "This weapon can be obtained by any player at the Sparkle"
      + " church who wishes to <pray> and <request> it. It is a way"
      + " to make the game a bit more friendly to new players. As such,"
      + " it is much lighter than normal weapons.\n");

    create_church_weapon();
} /* create_weapon */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(5.0, 0.0, &blow_away(from));
        return;
    }

    return;
} /* leave_env */


/*
 * Function name:        blow_away
 * Description  :        Get rid of the item when it is dropped. Also
 *                       check to see if anyone has picked it up first.
 * Arguments    :        object from - the player who dropped it
 */
public void
blow_away(object from)
{
    if (interactive(environment(this_object())))
    {
        return;
    }

    tell_room(environment(this_object()), "The " + short()
      + " dissolves suddenly into a cloud of mist which blows away in"
      + " the breeze.\n");
    remove_object();
} /* blow_away */


/*
 * Function name:        wizinfo
 * Description  :        provide some special info on this weapon
 * Returns      :        string - the info
 */
public string
wizinfo()
{
    return "This weapon can be obtained by any player at the Sparkle"
      + " church who wishes to <pray> and <request> it. It is a way"
      + " to make the game a bit more friendly to new players. As such,"
      + " it is much lighter than normal weapons.\n";
} /* wizinfo */
