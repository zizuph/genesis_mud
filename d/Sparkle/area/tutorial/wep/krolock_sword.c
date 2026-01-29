/*
 *  /d/Sparkle/area/tutorial/wep/krolock_sword.c
 *
 *  The sword of Baron von Krolock. An excellent weapon!
 *
 *  wielded by: /d/Sparkle/area/tutorial/npc/krolock.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this weapon is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
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
    set_name("longsword");
    add_adj( ({ "pearl", "pearl-handled", "handled" }) );
    add_name( ({ "sword" }) );

    set_short("pearl-handled longsword");
    set_long("This is one of the most advanced weapons you have ever"
      + " beheld. Every inch of its surface is polished and finely"
      + " crafted. The blade is razor sharp, and dangerous even to"
      + " touch. The handle is embedded with many dazzling pearls.\n");

    add_prop(OBJ_M_NO_SELL, "It is too valuable to sell.\n");
    add_prop(OBJ_M_NO_GIVE, "You don't feel like giving that away.\n");

    set_default_weapon(30, 30, W_SWORD, W_SLASH, W_ANYH, 0);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this weapon extra light.\n", 1}));
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_WEAPON(30, W_SWORD) / 3));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 30));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
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
        set_alarm(30.0, 0.0, &blow_away(from));
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

    from->catch_tell("The sword vanishes in a flash of light!\n");
    remove_object();
} /* blow_away */
