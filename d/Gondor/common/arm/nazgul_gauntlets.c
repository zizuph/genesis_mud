/*
 * nazgul_gaunlets.c
 * 
 * Ckrik, 10/6/2022 
 */

inherit "/std/unarmed_enhancer";
inherit "/lib/keep";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

void
create_unarmed_enhancer()
{
    set_name("gauntlets");
    set_adj("black");
    add_adj("scaled");
    set_short("pair of black scaled gauntlets"); 
    set_pshort("pairs of black scaled gauntlets"); 
    set_long("A pair of black scaled gauntlets forged with the malevolence " +
        "of its creator. The scales adorning the gauntlets feel smoldering " +
        "to the touch and reeks of malice of the purest form.\n");
    set_default_enhancer(50, 50, W_BLUDGEON, 45, A_HANDS, 0, this_object());
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"These gauntlets are enchanted.", 20,
        "These gauntlet enhances your fists with pure malevolence and " +
        "your skill with air, fire and death magics.", 40
    }));
    add_prop(OBJ_S_WIZINFO,"This pair of gauntlets is magically enhanced " +
        "with pen and hit. It also grants its wearer 10 levels of air, " +
        "fire, death and spellcraft. It is cloned by the black rider in " +
        "Gondor.\n");
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50 + random(5), 50 + random(5)));
    set_keep(1);
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
public mixed
wear(object obj)
{
    object wearer;

    wearer = environment(obj);

    if (wearer->query_stat(SS_DIS) < 120)
    {
        return "A sense of dread and despair beholds you as you attempt " +
            "to wear the " + short() + ". You fail to wear the " +
            short() + "!\n";
    }

    if (living(wearer))
    {
        wearer->set_skill_extra(SS_ELEMENT_AIR,
            wearer->query_skill_extra(SS_ELEMENT_AIR) + 10);
        wearer->set_skill_extra(SS_ELEMENT_FIRE,
            wearer->query_skill_extra(SS_ELEMENT_FIRE) + 10);
        wearer->set_skill_extra(SS_ELEMENT_DEATH,
            wearer->query_skill_extra(SS_ELEMENT_DEATH) + 10);
        wearer->set_skill_extra(SS_SPELLCRAFT,
            wearer->query_skill_extra(SS_SPELLCRAFT) + 10);

        wearer->catch_msg("A sense of dread and despair beholds you as you " +
            "attemp to wear the " + short() + ". However, steeling yourself " +
            "against your fears you manage to wear the " + short() + "!\n");
        return 1;
    }

    // Should never happen.    
    return 0;
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
public mixed
remove(object obj)
{
    object wearer;
    
    wearer = query_worn();
    if (objectp(wearer))
    {
        wearer->set_skill_extra(SS_ELEMENT_AIR,
            wearer->query_skill_extra(SS_ELEMENT_AIR) - 10);
        wearer->set_skill_extra(SS_ELEMENT_FIRE,
            wearer->query_skill_extra(SS_ELEMENT_FIRE) - 10);
        wearer->set_skill_extra(SS_ELEMENT_DEATH,
            wearer->query_skill_extra(SS_ELEMENT_DEATH) - 10);
        wearer->set_skill_extra(SS_SPELLCRAFT,
            wearer->query_skill_extra(SS_SPELLCRAFT) - 10);

        wearer->catch_msg(
            "You remove the " + short() + " and a sense of joyous relief takes you, " +
            "as if a great burden has been taken from you.\n");
        return 1;
    }
    
    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    string attack_desc, damage_desc, other_damage_desc;
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    object wearer = environment(this_object());

    if (phurt < 0)
    {
        // A miss, use regular message
        return 0;
    }

    attack_desc = (wearer->query_combat_object())->cb_attack_desc(aid);
    switch (phurt)
    {
    // Place holder for custom miss messages
    case -1:
    case -2:
    case -3:
        return 0;
    case 0..2:
        damage_desc = "lightly bruise";
        other_damage_desc = "lightly bruises";
    break;
    case 3..5:
        damage_desc = "batter";
        other_damage_desc = "batters";
    break;
    case 6..9:
        damage_desc = "pound";
        other_damage_desc = "pounds";
    break;
    case 10..19:
        damage_desc = "beat";
        other_damage_desc = "beats";
    break;
    case 20..39:
        damage_desc = "seriously beat";
        other_damage_desc = "seriously beats";
    break;
    case 40..59:
        damage_desc = "soundly beat";
        other_damage_desc = "soundly beats";
    break;
    case 60..90:
        damage_desc = "hammer";
        other_damage_desc = "hammers";
    break;
    default:
        damage_desc = "brutally pummel";
        other_damage_desc = "brutally pummels";
    break;
    }        

    wearer->catch_msg("You " + damage_desc + " " + QTPNAME(enemy) +
        " " + hdesc + " with your black scaled armoured " +
        attack_desc + ".\n");
    enemy->catch_msg(QCTNAME(wearer) + " " + other_damage_desc +
        " your " + hdesc + " with " + wearer->query_objective() +
        " black scaled armoured " +
        attack_desc + ".\n");
    wearer->tell_watcher(QCTNAME(wearer) + " " + other_damage_desc +
        " " + QTPNAME(enemy) + " " + hdesc + " with " +
        wearer->query_objective() + " black scaled " +
        "armoured " + attack_desc + ".\n", ({ enemy }));

    return 1;
}