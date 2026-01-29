/*
 * staff.c
 *
 * The staff of the Traveller.
 * 
 * Khail - February 9, 2002
 */
#pragma strict_types

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <files.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

#define HIT 28
#define PEN 20

inherit "/d/Khalakhor/std/weapon";
inherit "/lib/keep";

public void
create_khalakhor_weapon()
{
    set_name("staff");
    set_adj("weathered");
    add_adj("ironwood");
    set_short("weathered ironwood staff");
    set_pshort("weathered ironwood staves");
    set_long("The curious staff appears to be very old, the " +
        "smooth ironwood surface has been deeply polished by " +
        "countless years of usage, the wood stained a deep brown " +
        "by oils absorbed over time from its wielder's hand. " +
        "The staff is unadorned, except for an intricate carving at " +
        "the top of the staff, resembling three teardrops circling " +
        "one another.\n");

    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_dt(W_BLUDGEON);
    set_hit(HIT);
    set_pen(PEN);
    set_keep(1);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

/*
 * Function name: weapon_recalled
 * Description:   Called when the Traveller resets and notices that
 *                his staff is gone.  Simply put, this function
 *                removes the staff from wherever it is, sends it
 *                back to the traveller.
 * Arguments:     object traveller - object pointer to the
 *                                   Traveller looking for his
 *                                   staff.
 * Returns:       0 - Weapon returned.
 *                1 - Weapon can't be returned.
 */
public int
weapon_recalled(object traveller)
{
    object my_env;
    int return_val;

   /* Does three things, depending on environment.  If the 
    * environment is living and wielding the staff, unwield
    * and delivery one kind of message.  If the environ is
    * a room or container, generate different kinds of
    * messages.*/

    my_env = environment(TO);

    add_prop(OBJ_I_LIGHT, 100);

    if(living(my_env))
    {
        my_env->catch_msg("Suddenly the " + short() +
            "erupts in a crackle of blue-green lightning, " +
            "forcing you to drop it in shock!\n");
        tell_room(environment(my_env), QCTNAME(my_env) +
            " gasps in shock and drops " + HIS_HER(my_env) +
            " " + short() + " as it erupts into a crackle " +
            "of blue-green lightning!\n",
            my_env);
	my_env->command("$drop ironwood staff");
        my_env = environment(TO);
    }
    else if (IS_RECEPTACLE_OBJECT(my_env))
    {
        if (living(environment(my_env)))
        {
            if (my_env->query_prop(CONT_I_CLOSED))
            {
                environment(my_env)->catch_msg("You hear " +
                    "a brief, muffled crackling sound "+
                    "from your " + my_env->short() + 
                    ", and when the sound stops it feels " +
                    "much lighter.\n");
                tell_room(environment(environment(my_env)),
                    "You hear a brief crackling sound from " +
                    QTNAME(environment(my_env)) + "'s " +
                    my_env->short() + ", and notice a " +
                    " puzzled look on " +
                    HIS_HER(environment(my_env)) + " face.\n",
                    environment(my_env));
            }
            else
            {
                environment(my_env)->catch_msg("You hear " +
                    "a brief, muffled crackling sound " +
                    "from your " + my_env->short() +
                    ", followed by a bright flash of " +
                    "blue-green light, and the " +
                    my_env->short() + " suddenly feels " +
                    "much lighter.\n");
                tell_room(environment(environment(my_env)),
                    "You hear a brief crackling sound from " +
                    QTNAME(environment(my_env)) + "'s " +
                    my_env->short() + ", followed by a " +
                    "bright flash of blue-green light, " +
                    "leaving a puzzled look on " +
                    HIS_HER(environment(my_env)) + 
                    " face.\n", environment(my_env));
            }
        }
        else if (IS_ROOM_OBJECT(environment(my_env)))
        {
            if (my_env->query_prop(CONT_I_CLOSED))
            {
                tell_room(environment(my_env), "You hear " +
                    "a brief crackling sound come from " +
                    " the " + my_env->short() + ".\n");
            }
            else
            {
                tell_room(environment(my_env), "You hear " +
                    "a brief crackling sound and see a " +
                    "bright flash of light coming from " +
                    " the " + my_env->short() + ".\n");
            }
        }
    }

    if (IS_ROOM_OBJECT(my_env))
    {
        tell_room(my_env, "You hear a crackling sound, and " +
            "suddenly the " + short() + " erupts into a " +
            "brilliant flash of blue-green lightning! " +
            "When the light fades, the " + short() + " is " +
            "gone!\n");
    }

    return_val = move(traveller, 1);

    if (return_val)
    {
        remove_object();
        return 1;
    }
    else
    {
        return 0;
    }
}    