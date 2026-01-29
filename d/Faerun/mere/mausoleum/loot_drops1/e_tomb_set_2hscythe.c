/*
 *  /d/Ravenloft/droptables/fos_drops/e_tomb_set_2hscythe.c
 *
 *  Epic weapon from the Forest of Shadows, tomb.
 *
 *  Deals additional magical cold damage.
 *
 *
 *
 *  Nerull 2015
 *
 */


#pragma strict_types

#include "/d/Ravenloft/defs/magicalitems_stats.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/resist";

// Custom name.
string wname = "Jakredak";

/* 
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */ 
public void
create_weapon()
{
    set_name("_e_tomb_2hscythe");
    add_name( ({"scythe"}) );

    set_adj(wname);
    add_adj("bone");
	add_adj("large");

    set_short(wname+"'s large bone scythe"); 
    set_pshort(wname + "'s large bone scythes");

    set_long("Pulsing with necromantic powers this large scythe "
    +"fulfills " + wname + "'s prayer. " + wname + "'s femur "
    +"knee and "
    +"tibia have been mummified and cast in adamantine to "
    +"help protect his people. So as to be easy to "
    +"wield, an adamantine nub extends off the femur abit "
    +"less than halfway from the end and the blade is quite "
    +"massive for a giants tibia. Somehow, the magics in this "
    +"scythe still allow the knee to flex, which provides a "
    +"whip effect upon the blade. Blood somehow still oozes "
    +"from the bone blade. This scythe is extremely cold.\n");

    set_default_weapon(TOMB_E_2HSPEAR_HIT, TOMB_E_2HSPEAR_PEN,
    W_POLEARM, W_SLASH | W_IMPALE, W_BOTH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "potent magic.\n",1,
        "The enhancement makes the weapon deadlier than "
        + "normal weapons.\n",10,
        "The weapon contains potent cold magic.\n", 30,
        "The cold magic will occasionally lash out at anyone stricken "
        + "by the weapon.\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "This is en epic weapon dropping from the chest in "
        + "the ancient tomb, Forest of Shadows, Ravenloft. It procs magical "
        + "cold damage.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(TOMB_E_2HSPEAR_PEN, W_POLEARM));
    add_prop(OBJ_I_VOLUME, TOMB_E_2HSPEAR_VOLUME);
    add_prop(OBJ_I_VALUE, TOMB_E_2HSPEAR_VALUE);

    // Make it keepable by default.
    set_keep();
}


/*
* Function:    wield_mes()
* Description: The message and any extra functions/mechanics to
*              the weapon when it's wielded.
*/
void
wield_mes()
{
    if (environment(this_object()) != wielder)
        return;

    wielder->catch_msg("A frozen mist envelopes your arm "
        + "when you wield the " + short() + ".\n");

    tell_room(environment(wielder), "A frozen mist envelopes "
        + QTNAME(wielder) + "'s arm "
        + "from the " + short() + ".\n", wielder);
}



/*
* Function:    unwield_mes()
* Description: The message and any extra functions/mechanics to
*              the weapon when it's unwielded.
*/
void
unwield_mes()
{
    if (!objectp(wielder))
        return;

    wielder->catch_msg("The frozen mist around your arm quickly dissipates "
        + "as you unwield the " + short() + ".\n");

    tell_room(environment(wielder), "As " + QTNAME(wielder)
        + " unwields the " + short() + ", the frozen mist "
        + " dissipates from around " + wielder->query_pronoun()
        + " arm.\n", wielder);
}



/*
* Function name:        wield
* Description  :        we only allow players with sufficient
*                       sword skill to wield this weapon
* Arguments    :        object wep - this object
* Returns      :        -1 : cannot wield
*                        0 : okay to wield
*/
mixed
wield(object what)
{
    wielder = this_player();

    if (this_player()->query_skill(SS_WEP_POLEARM) < 50)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }

    set_alarm(0.1, 0.0, "wield_mes");
    return 0;
}



/*
* Function name: unwield
* Description  : This function might be called when someone tries to unwield
*                this weapon. To have this function called, use the function
*                set_wf().
* Arguments    : object obj - the weapon to stop wielding.
* Returns      : int  0 - the weapon can be unwielded normally.
*                     1 - unwield the weapon, but print no messages.
*                    -1 - do not unwield the weapon, print default messages.
*                string - do not unwield the weapon, use this fail message.
*/
mixed
unwield(object what)
{
    wielder = this_player();

    set_alarm(0.1, 0.0, "unwield_mes");
    return 0;
}



/*
* Function:    do_describe_extra_damage
* Description: This function should be masked by each weapon that wishes to
*              customize the damage description for the extra damage.
*              All the necessary info should be available in the arguments,
*              which are identical to did_hit, except for an extra argument
*              to pass the actual extra damage that was done.
*/
public void
do_describe_extra_damage(int aid, string hdesc, int phurt,
    object enemy, int dt, int phit, int dam, int extra_dam)
{
    // Cold damage
    wielder->catch_msg("As you strike " + QTNAME(enemy) + ", with "
        + "your " + short() + ", a powerful ray of cold "
        + "suddenly bursts from it, freezing into "
        + enemy->query_possessive() + " " + hdesc + ""
        + ", leaving a gruesome frostbite mark!\n");

    enemy->catch_msg("As " + QCTNAME(wielder) + " strikes you with "
        + "the " + short() + ", a powerful ray of cold "
        + "suddenly bursts from it, freezing into your "
        + hdesc + ", leaving a gruesome frostbite mark!\n");

    wielder->tell_watcher("As " + QCTNAME(wielder) + " strikes "
        + QTNAME(enemy) + " "
        + "with " + wielder->query_possessive() + " "
        + short() + ", a "
        + "powerful ray of cold suddenly bursts from it,  "
        + "freezing into " + enemy->query_possessive() + " "
        + hdesc + ", "
        + "leaving a gruesome frostbite mark!\n", enemy);
}



/*
* Function name: did_hit
* Description  : Special attack. What happens when the weapon hits
*                the target.
* Arguments    : int aid, string hdesc, int phurt, object enemy, int dt,
*                int phit, int dam.
*/
public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int
    dam)
{
    int extra_damage = 0;

    int dice = random(4);

    int did_hit_result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);


    // If we miss, we miss.
    if (phurt < 0 || dam == 0)
    {
        return did_hit_result;
    }


    if (query_prop(LAST_SPECIAL_HIT) + 5 > time())
    {
        // We limit the special attack to once every 5 seconds
        return did_hit_result;
    }


    // This weapon has a percentage chance of dealing out extra damage.
    if (random(100) < TOMB_E_2HSPEAR_DMG_PROC)
    {
        add_prop(LAST_SPECIAL_HIT, time());

        // The damage formula gives an extra 15-25% damage
        extra_damage = TOMB_E_2HSPEAR_DMG_MULTIPLIER * ((dam * 15 / 100) + random(dam / 10));

        // This damage is magical by nature, so we need to do some "
        // resistance checks
        int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC,
            MAGIC_I_RES_COLD }));

        extra_damage = extra_damage - ((extra_damage * resistance) / 100);
        enemy->heal_hp(-extra_damage);

        do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
            extra_damage);
    }

    return did_hit_result;
}