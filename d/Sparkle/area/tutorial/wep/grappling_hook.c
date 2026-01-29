/*
 *  /d/Sparkle/area/tutorial/wep/grappling_hook.c
 *
 *  This is the grappling hook that players can make to help
 *  them climb up to Krolock's castle.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
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


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("hook");
    add_name( ({ "rope", "_tutorial_hook", "_tutorial_item" }) );
    add_adj( ({ "grappling" }) );

    set_short("grappling hook");
    set_long("This is a grappling hook which has been constructed of"
      + " rope and animal claws. It looks like it would be very useful"
      + " when trying to climb up a steep cliff. You can <wield> it"
      + " to equip this item. It probably would serve as a type of"
      + " knife weapon if you needed it to.\n");

    add_prop(OBJ_M_NO_SELL, "The grappling hook cannot be sold.\n");
    add_prop(OBJ_M_NO_GIVE, "You don't feel like giving that away.\n");

    set_default_weapon(5, 5, W_KNIFE, W_SLASH|W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(5, W_KNIFE));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5, 5));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
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
        set_alarm(0.0, 0.0, &blow_away(from));
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

    from->catch_tell("You toss the hook away, and it is lost from"
      + " view.\n");
    remove_object();
} /* blow_away */


/* Autoloads, doesn't recover */
public string
query_recover()
{
    return 0;
}

/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      :        string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */
