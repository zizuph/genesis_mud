/*
 *  /d/Terel/mountains/ghastly_keep/arm/gkeep_wizhat.c
 *
 *  Wizard hat.
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth
 *  26/04-17                   Fixed a bug when removing the item      Znagsnuf
 *  29/05-17                   Fixed a bug with resolve_task           Znagsnuf 
 *  25/12-20                   Cache the task resolves so its meaningful Cotillion
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h";


#define ATTEMPT_CACHE_TIME      (3600 * 2) /* Time between rolls */

int HAT_AC = 10;
mapping attempts = ([ ]);

/*
* Function name: set_hatac()
* Description  : Setting up the right AC.
*/
void
set_hatac()
{
    string hatter = TP->query_real_name();

    if (!attempts[hatter] || attempts[hatter][1] < time()) {
        attempts[hatter] = ({ 
            TP->resolve_task(TASK_DIFFICULT, ({ &min(this_player()->query_stat(SS_WIS), 150), SS_SPELLCRAFT})) > 0,
            time() + ATTEMPT_CACHE_TIME
            });
    }

    // Sabine would always be able to use it.
    if (TP->query_real_name() == "sabine" || attempts[hatter][0] > 0)
    {
        HAT_AC = 50;
        set_ac(HAT_AC);
    }
    else
    {
        HAT_AC = 10;
        set_ac(HAT_AC);
    }
}

void
create_armour()
{
    set_name("hat");
    set_adj( ({"crumpled", "sparkling"}) );
    set_short("crumpled sparkling hat");
    set_long( "This hat is a dark blue, almost the color of "
            + "midnight, and has been cut from a soft cloth. "
            + "The wide brim of the hat seems to flop down "
            + "while the rest of the hat rises up in a cone "
            + "that is rather crumpled at the tip.\n@@hat_longdesc@@");

    set_ac(HAT_AC);
    set_at(A_HEAD);
    set_wf(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(MAGIC_AM_MAGIC,({70,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({
        "You sense a great barrier around this "+TO->short()+", protecting "
        + "you in combat.\n", 20,
        "The golden stars and crescent moons will sparkle for the "
        + "worthy.\n", 50,
        "Only those who are practiced in spellcraft may harness the true "
        + "powers kept within this " + TO->short() + ".\n", 70 }));

    add_prop(OBJ_S_WIZINFO, "This "+TO->short()+" is worn by Sabine in the "
             + "basement of the Ghastly Keep. :\n"
             + "    /d/Terel/mountains/ghastly_keep/npc/g_witch.c\n"
             + "This " +TO->short()+ " can be worn on your head, and provides "
             + "great AC for the worthy.\n");

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)
                        + random(100) + 100);
}

string
hat_longdesc()
{
    
    if (HAT_AC > 11)
    {
        return "Dozens of sparkling golden stars and crescent moons "
              +"decorate the hat, each one shimmering as they catch "
              +"the light.\n";
    }
    else
    {
        return "";
    }
}


/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int 
got_hit(int hid, int ph, object att, int dt, int dam)
{

    ::got_hit(hid, ph, att, dt, dam);

    int damage_split;
    object wearer;
    string hard;

    // Only hits to the head that will count.
    if (hid != A_HEAD)
        return 0;

    // Need to be a solid hit.
    if(ph < 1) 
        return 0;

    // Only the worthy will get the benefits from the hat.
    if (HAT_AC < 11)
        return 0;

    // 25% damage migration on hits to head.
    damage_split = (dam / 4);

    wearer = TO->query_worn();
    wearer->heal_hp(damage_split);
    
    switch (damage_split)
    {
    case  0..25:
            hard = "the damage slightly";
            break;
    case 26..50:
            hard = "some of the damage";
            break;
    case 51..100:
            hard = "a large portion of the damage";
            break;
    case 101..10000:
            hard = "a great amount of the damage";
            break;
    }

    if (damage_split > 0)
    {
         wearer->catch_msg("A protective barrier forms around "
                +"the " + TO->short() + ". Absorbing " + hard + ".\n");

         tell_room(ENV(wearer), "A protective barrier forms around "
            +"the " + TO->short() + " worn by " + QTNAME(wearer) + ". "
            +"Absorbing " + hard + ".\n", wearer);
    }      
    
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */

mixed
wear(object ob)
{
    wearer = ENV(TO);
    set_hatac();

    if (HAT_AC > 11)
    {
        wearer->catch_msg("As you place the " + TO->short() + " on top of "
            + "your head each of the sparkling golden stars and crescent " 
            + "moons decorating the " + TO->short() + " begin to shimmer as "
            + "they catch the light.\n");

        tell_room(ENV(wearer), "As " + QTNAME(wearer) + " wears the "
            +TO->short()+" on top of " + wearer->query_possessive() + " head "
            + "each of the sparkling golden stars and crescent moons "
            + "decorating the " + TO->short() + " begin to shimmer as they "
            + "catch the light.\n", wearer);
    }
    else
    {
        wearer->catch_msg("You place the " + TO->short() + " on your head.\n");
        tell_room(ENV(wearer), QCTNAME(wearer) + " places" +
            " the " + TO->short() + " on " + wearer->query_possessive()+" head"
           +".\n", wearer);
    }
    return 1;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */

mixed
remove(object ob)
{
    wearer = query_worn();

    if (HAT_AC > 11)
    {
        wearer->catch_msg("As you remove the "+TO->short()+" from the top of "
            + "your head each of the sparkling golden stars and crescent "
            + "moons decorating the " + TO->short() + " fade out.\n");

        tell_room(ENV(wearer), "As "+ QTNAME(wearer) + " removes the "
            +TO->short()+" from the top of " + wearer->query_possessive()+" "
            + "head, each of the sparkling golden stars and crescent moons "
            + "decorating the " +TO->short()+ " begin to fade out.\n", wearer);
    }
    else
    {
        wearer->catch_msg("You remove the "+TO->short()+" from your head.\n");
        tell_room(ENV(wearer), QCTNAME(wearer) + " removes " +
            "the " +TO->short() + " from " +wearer->query_possessive()+" head"
           + ".\n", wearer);
    }
    return 1;
}
