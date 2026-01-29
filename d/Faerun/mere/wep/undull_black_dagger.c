/*
 * Rare magical swingblade.
 * 
 * This weapon deals additional magical light, electricity, acid 
 * and cold damage, and adds a portion of haste to the wielder.
 
 * This weapon is inspired by the rust-red weaponset I coded
 * for Raumdor in 2010 and uses the same formula.
 *
 * This swingblade is for left hand only, so you can only 
 * wield one at a time.
 *
 * by Nerull, 2019
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;
inherit "/lib/keep";
inherit "/d/Genesis/specials/resist";

#define LAST_SPECIAL_HIT        "_last_special_hit"
#define HASTE_VALUE             50


void
create_faerun_weapon()
{
    seteuid(getuid());

    set_name("swingblade");
    add_name("ulak");   
    add_pname(({"swingblades", "ulaks"}));
    
    set_adj("gleaming");
    set_adj("meteorite");
    
    set_short("gleaming meteorite swingblade");
    set_pshort("gleaming meteorite swingblades");
   
    set_long("This swingblade, also known as an ulak is made "
    +"of a dark gleaming metal known as starmetal or meteorite, "
    +"a metal so hard to work with that only the best smiths are "
    +"able to forge items with it. From the hilt, the blade extends "
    +"about an inch up and almost wraps over the hand before extending "
    +"into a sharp blade. The blades themselves are only adorned with "
    +"a barely noticable engraving.\n");
    
    add_item(({"engraving", "words"}),
    "With elegant letters the words 'The Fury is Ours' is written.\n");
    
    add_item(({"hilt"}),
    "The hilt is made of tightly wrapped leather strips around an oaken grip.\n");
    

    set_default_weapon(40, 40, 
    W_KNIFE, W_SLASH | W_IMPALE, W_LEFT, this_object());
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    
    add_prop(MAGIC_AM_MAGIC,({ 60, "enchantment" }));
    
    add_prop(MAGIC_AM_ID_INFO, ({ "This weapon has been enhanced by "
        + "strong magic.\n",1,
        "The enhancement makes the weapon much deadlier than "
        + "normal weapons, and "
        + "will hasten the wielder.\n",10,
        "The weapon contains strong magical energies.\n", 20,
        "The energies will occasionally lash out at anyone stricken "
        + "by the weapon.\n", 30,
        "Which magical energy that dominates the weapon "
        + "during combat will vary.\n", 50 }));
        
    add_prop(OBJ_S_WIZINFO, "This is a weapon dropping from "
        +"assassin boss from the cave in Mere of Dead "
        +"Men.\nThe weapon deals additional damage, randomly "
        +"(light, electricity, acid and cold) and in addition "
        +"hastens the wielder.\n");
        
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_KNIFE));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 15000);
    
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
    wielder->catch_msg("Many colours suddenly spark for a "
        + "brief moment from "
        + "your " + short() + " when you wield it. You also feel quicker.\n");
        
    tell_room(environment(wielder), "Many colours spark for a "
        + "brief moment from the " + short() + " wielded "
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
        + "colourful flash when you unwield it. You feel slower.\n");
        
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
    
    if (this_player()->query_skill(SS_WEP_KNIFE) < 80)
    {
        write("The " + short() + " refuses you as its wielder!\n");
        return -1;
    }
    
    this_player()->add_prop(LIVE_I_QUICKNESS, 
    this_player()->query_prop(LIVE_I_QUICKNESS) 
    + HASTE_VALUE);
    
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
    
    this_player()->add_prop(LIVE_I_QUICKNESS, 
    this_player()->query_prop(LIVE_I_QUICKNESS) 
    - HASTE_VALUE);
    
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
            + "of white light "
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
            + "burning into " + enemy->query_possessive() + " " + hdesc + ", "
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
    if (random(100) < 20)
    {
        add_prop(LAST_SPECIAL_HIT, time());
        // The damage formula gives an extra 15-25% damage
        extra_damage = 5 * ((dam * 15 / 100) + random(dam / 10));
        
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

    
    
    
    
    
    
    
    
    
    
    
    
    

