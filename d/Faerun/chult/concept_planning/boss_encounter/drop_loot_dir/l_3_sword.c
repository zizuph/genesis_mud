/*
 *  Legendary weapon from the Red Cliffs, Faerun.
 *
 *  Chromatic magical damage (light, acid, cold, lightning).
 *
 *  Nerull 2018
 *
 */


#pragma strict_types

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define LAST_SPECIAL_HIT              "_last_special_hit"
#define LEGENDARY_DROP_VALUE           15000
#define L_WEAPON_HIT                   60
#define L_WEAPON_PEN                   60
#define L_WEAPON_VALUE                 LEGENDARY_DROP_VALUE
#define L_WEAPON_VOLUME                1000
#define L_WEAPON_DMG_MULTIPLIER         5
#define L_WEAPON_DMG_PROC              50

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/resist";


/* 
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */ 
public void
create_weapon()
{
    set_name("_l_sword");
    add_name( ({"blade","sword", "beam"}) );
    set_adj("iridicent");
    set_adj("golden-hilted");

    set_short("iridicent golden-hilted sword"); 
    set_pshort("iridicent golden-hilted swords");

    set_long("An iridecent beam of light extends from the "
    +"sword to about 1.5 meters. The colours of the beam "
    +"changes to any imaginable colour as rapidly as you can "
    +"blink your eyes. The crossguard of the golden hilt is "
    +"decorated with small perfectly cut diamonds that rapidly "
    +"change colours to correspond with the blade.\n");


    add_item(({ "colour", "colours" }), "The blade consisting "
    +"of a beam of light and changes colour every second.\n");

    set_default_weapon(L_WEAPON_HIT, L_WEAPON_PEN, 
    W_SWORD, W_SLASH | W_IMPALE, W_ANYH, this_object());

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "strong magic.\n",1,
        "The enhancement makes the weapon much deadlier than "
        + "normal weapons, and "
        + "resistant to wear and tear from usage.\n",10,
        "The weapon contains strong magical energies.\n", 20,
        "The energies will occasionally lash out at anyone stricken "
        + "by the weapon.\n", 30,
        "Which magical energy that dominates the weapon "
        + "during combat will vary.\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "This is a Legendary weapon dropping from "
        + "loot chest in Red Cliffs, Faerun. "
        + "This is an extremely rare weapon to obtain.\nThe weapon "
        + "deals additional damage, randomly (light, electricity, "
        + "acid and cold), and the weapon does not dull or break.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(L_WEAPON_PEN, W_SWORD));
    add_prop(OBJ_I_VOLUME, L_WEAPON_VOLUME);
    add_prop(OBJ_I_VALUE, L_WEAPON_VALUE);

    // Make it keepable by default.
    set_keep();

    // Undullable
    set_likely_dull(0);
    set_likely_corr(0);
}



/*
* Function name: set_dull
* Description  : Use this to increases the dull status on weapons.
* Arguments    : int cond - The new condition we want (can only be raised)
* Returns      : int - 1 if new condition accepted, 0 if not.
*/
int
set_dull(int i)
{
    return 0;
}



/*
* Function name: set_corroded
* Description  : Use this to increases the corroded status on weapons.
* Arguments    : int cond - The new condition we want (can only be raised)
* Returns      : int - 1 if new condition accepted, 0 if no corrosion.
*/
int
set_corroded(int i)
{
    return 0;
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

    wielder->catch_msg("Many colours suddenly spark for a "
    +"brief moment from "
    +"your "+short()+" when you wield it.\n");

    tell_room(environment(wielder), "Many colours spark for a "
    +"brief moment from the "+short()+" wielded "
    + "by " + QTNAME(wielder) + ".\n", wielder);
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

    wielder->catch_msg("The " + short() + " gives away a tiny "
        + "colourful flash when you unwield it.\n");

    tell_room(environment(wielder), "The " + short() + " wielded "
        + "by " + QTNAME(wielder) + " gives away a tiny "
        + "colourful flash when "
        + wielder->query_pronoun()
        + " unwields it.\n", wielder);
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

    if (this_player()->query_skill(SS_WEP_SWORD) < 80)
    {
        write("The "+short()+" refuses you as its wielder!\n");
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
  object enemy, int dt, int phit, int dam, int extra_dam, int dice)
{

    int d = dice;

    if (d == 0)
    {
        // Light /radiant damage
        wielder->catch_msg("As you strike " + QTNAME(enemy) + ", with "
            + "your " + short() + ", a powerful focused beam "
            +"of white light "
            + "suddenly bursts from it, burning into " 
            + enemy->query_possessive() + " " + hdesc + ""
            + ", leaving a terribly scorched hole!\n");

        enemy->catch_msg("As " + QCTNAME(wielder) + " strikes you with "
            + "the " + short() + ", a powerful focused beam of white "
            + "light suddenly bursts from it, burning into your " 
            + hdesc + ", leaving a terribly scorched hole!\n");

        wielder->tell_watcher("As " + QCTNAME(wielder) + " strikes " 
            + QTNAME(enemy) + " "
            + "with " + wielder->query_possessive() + " " 
            + short() + ", a "
            + "powerful focused beam of white light suddenly bursts "
            + "from it, "
            + "burning into " + enemy->query_possessive() + " "+hdesc+", " 
            + "leaving a terribly scorched hole!\n", enemy);
    }

    if (d == 1)
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

    if (d == 2)
    {
        // Acid damage
        wielder->catch_msg("As you strike " + QTNAME(enemy) + ", with "
            + "your " + short() + ", a powerful jet of acid "
            + "suddenly bursts from it, burning into "
            + enemy->query_possessive() + " " + hdesc + ""
            + ", leaving painful acid burns!\n");

        enemy->catch_msg("As " + QCTNAME(wielder) + " strikes you with "
            + "the " + short() + ", a powerful jet of acid "
            + "suddenly bursts from it, burning into your "
            + hdesc + ", leaving painful acid burns!\n");

        wielder->tell_watcher("As " + QCTNAME(wielder) + " strikes "
            + QTNAME(enemy) + " "
            + "with " + wielder->query_possessive() + " "
            + short() + ", a "
            + "powerful jet of acid suddenly bursts from it,  "
            + "burning into " + enemy->query_possessive() + " "
            + hdesc + ", "
            + "leaving painful acid burns!\n", enemy);
    }

    if (d == 3)
    {
        // Lightning damage
        wielder->catch_msg("As you strike " + QTNAME(enemy) + ", with "
            + "your " + short() + ", a powerful bolt of lightning "
            + "suddenly leaps from it and into "
            + enemy->query_possessive() + " " + hdesc + ""
            + ", frying flesh and bone.\n");

        enemy->catch_msg("As " + QCTNAME(wielder) + " strikes you with "
            + "the " + short() + ", a powerful bolt of lightning "
            + "suddenly leaps from it and into your "
            + hdesc + "!\nYou are terribly electrocuted!\n");

        wielder->tell_watcher("As " + QCTNAME(wielder) + " strikes " 
            + QTNAME(enemy) + " "
            + "with " + wielder->query_possessive() + " " + short() + ", a "
            + "powerful focused beam of white light suddenly leaps from it  "
            + "and into " + enemy->query_possessive() + " " + hdesc + ", "
            + "frying flesh, tissue and bone!\n", enemy);
    }
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
    if (random(100) < L_WEAPON_DMG_PROC)
    {
        add_prop(LAST_SPECIAL_HIT, time());

        // The damage formula gives an extra 15-25% damage
        extra_damage = L_WEAPON_DMG_MULTIPLIER * ((dam * 15 / 100) + random(dam / 10));

        if (dice == 0)
        {
            // This damage is magical by nature, so we need to do some "
            // resistance checks
            int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC,
                MAGIC_I_RES_LIGHT }));

            extra_damage = extra_damage - ((extra_damage * resistance) / 100);
            enemy->heal_hp(-extra_damage);

            do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
            extra_damage, dice);
        }

        if (dice == 1)
        {
            // This damage is magical by nature, so we need to do some "
            // resistance checks
            int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC,
            MAGIC_I_RES_COLD }));

            extra_damage = extra_damage - ((extra_damage * resistance) / 100);
            enemy->heal_hp(-extra_damage);

            do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
            extra_damage, dice);
        }

        if (dice == 2)
        {
            // This damage is magical by nature, so we need to do some "
            // resistance checks
            int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC,
            MAGIC_I_RES_ACID }));

            extra_damage = extra_damage - ((extra_damage * resistance) / 100);
            enemy->heal_hp(-extra_damage);

            do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
            extra_damage, dice);
        }

        if (dice == 3)
        {
            // This damage is magical by nature, so we need to do some "
            // resistance checks
            int resistance = combine_resistances(enemy, ({ MAGIC_I_RES_MAGIC,
                MAGIC_I_RES_ELECTRICITY }));

            extra_damage = extra_damage - ((extra_damage * resistance) / 100);
            enemy->heal_hp(-extra_damage);

            do_describe_extra_damage(aid, hdesc, phurt, enemy, dt, phit, dam,
            extra_damage, dice);
        }
    }

    return did_hit_result;
}
