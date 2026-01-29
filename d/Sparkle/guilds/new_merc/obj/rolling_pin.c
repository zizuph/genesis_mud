/*
 *  /d/Sparkle/guilds/new_merc/obj/rolling pin.c
 *
 *  A rolling pin. One of numerous items that can be found in the kitchen of
 *  the Mercenary guild.
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

/* prototypes */
public void        create_weapon();
public void        init();
public int         do_spin(string arg);

/*
 * Function name:        create_weapon
 * Description  :        set up the broom
 */
public void
create_weapon()
{
    set_name("roller");
    add_name( ({ "pin" }) );
    set_short("rolling pin");
    add_adj( ({ "rolling" }) );

    set_long("Children often like to hold rolling pins like this on end and"
      + " spin the roller as fast as they can. But you're too old for"
      + " that, surely!\n");

    set_default_weapon(10, 20, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10, 20) + random(20));
} /* create weapon */


/*
 * Function name:        init
 * Description  :        Add a silly emote to this thing
 */
public void
init()
{
    ::init();

    add_action(do_spin, "spin");
} /* init */


/*
 * Function name:        do_spin
 * Description  :        Let players spin the roller. Aw, special.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_spin(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you want to spin?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [rolling] 'pin' / 'roller'"))
    {
        notify_fail("You can't spin that.\n");
        return 0;
    }

    if (this_object()->query_wielded() != this_player())
    {
        notify_fail("You'll need to wield the rolling pin first.\n");
        return 0;
    }

    write("Grasping the spindle, you hold the rolling pin aloft and spin"
      + " the roller with all your might! Whrrrrrrrrrrrrrr ......\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " holds aloft a rolling pin and spins the"
      + " roller with all of " + this_player()->query_possessive() 
      + " might! Whrrrrrrrrrrrrrrrr ......\n", this_player());

    return 1;
} /* do_spin */