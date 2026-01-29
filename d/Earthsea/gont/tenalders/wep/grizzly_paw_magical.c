/*
 * T
 * 
 */

#pragma strict_types
#pragma no_inherit

inherit "/std/unarmed_enhancer";

#include <wa_types.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

public void
create_unarmed_enhancer()
{
    set_name("paw");
    set_pname("paws");
    set_adj(({"large", "grizzly", "paw"}));
    set_short("large grizzly bear paw");
    set_pshort("large grizzly bear paws");
    set_long("A " + short() + ". You can see " +
        "several large claws that the former owner of this paw " +
        "used in self defense. They are quite sharp. " +
        "The thick skin and fur of this paw would provide " +
        "excellent protection. You sense some magical energy " +
        "emanating from the paw.\n");
    set_keep();
    set_default_enhancer(42, 38, W_BLUDGEON | W_SLASH, 30, A_ANY_HAND, 0, this_object());
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({ 30, "enchantment", 20, "earth" }));
    add_prop(MAGIC_AM_ID_INFO,({
        "The paw seems to be enchanted.", 20,
        "Earth elemental magic seems to be emanating from the paw. It is " +
        "almost as if its former owner was skilled in earth magic!", 40
        })
    );
    add_prop(OBJ_S_WIZINFO,
        "The grizzly bear that the paw comes from was a wizard that " +
        "changed into a bear and forgot his wizard self. " +
        "The paw does 10% extra earth damage on top of the physical damage.");
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, 1100);
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    object me = query_worn();
    string wep = short();
    string extra_dam_desc = "unaffected";

    if (dam > 0)
    {
        int extra_dam = 10 * dam / 100;
        extra_dam = (100 - enemy->query_magic_res(MAGIC_I_RES_EARTH)) *
            extra_dam / 100;
        if (extra_dam > 0)
        {
            enemy->heal_hp(-extra_dam);
        }

        switch (extra_dam)
        {
        case 0..10:
            extra_dam_desc = "mildly irritated from the paw's magical effect";
            break;
        case 11..20:
            extra_dam_desc = "blasted from the paw's magical effect";
            break;
        default:
            extra_dam_desc = "crushed from the paw's magical effect";
            break;
        }
    }

    switch(phurt)
    {
    case -1:
        if(!me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("Your " + wep + " flies right by " + 
                QTPNAME(enemy) + 
                " " + hdesc + " as " + enemy->query_pronoun() +
                " dodges.\n");
        }
        if(!enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(me) + "'s " + wep + " flies right by your " +
                hdesc + " as you dodge.\n");
        }
        me->tell_watcher_miss(QCTNAME(me) + "'s " + wep + " flies right by " +
                QTPNAME(enemy) + " " + hdesc + " as " + enemy->query_pronoun() +
                " dodges.\n");
        break;
    case -2:
        object parry_weapon = one_of_list(enemy->query_weapon(-1));
        if(!me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("Your " + wep + " flies right by " + 
                QTPNAME(enemy) + 
                " " + hdesc + " as " + enemy->query_pronoun() +
                " parries with " + enemy->query_possessive() +
                " " + parry_weapon->short() +
                ".\n");
        }
        if(!enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(me) + "'s " + wep + " flies right by your " +
                hdesc + " as you parry with your " + parry_weapon->short() +
                ".\n");
        }
        me->tell_watcher_miss(QCTNAME(me) + "'s " + wep + " flies right by " +
                QTPNAME(enemy) + " " + hdesc + " as " + enemy->query_pronoun() +
                " parries with " + enemy->query_possessive() +
                " " + parry_weapon->short() +
                ".\n");
        break;
    case -3:
        if(!me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("Your " + wep + " flies right by " + 
                QTPNAME(enemy) + 
                " " + hdesc + " as " + enemy->query_pronoun() +
                " backflips away.\n");
        }
        if(!enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(QCTNAME(me) + "'s " + wep + " flies right by your " +
                hdesc + " as you backflip away.\n");
        }
        me->tell_watcher_miss(QCTNAME(me) + "'s " + wep + " flies right by " +
                QTPNAME(enemy) + " " + hdesc + " as " + enemy->query_pronoun() +
                " backflips away.\n");
        break;
    break;
    case 0..10:
        if((dt == W_SLASH))
        {
            me->catch_msg("You lightly scratch " + QTPNAME(enemy) + " " +
                hdesc + " with your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " lightly scratches " +
                "your " + hdesc + " with " +
                me->query_possessive() + " " + wep + " and " +
                "you feel " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " lightly scratches " +
                QTPNAME(enemy) + " " + hdesc + " with " +
                me->query_possessive() + " " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n",
                enemy);
        } else {
            me->catch_msg("You lightly tap " + QTPNAME(enemy) + " " +
                hdesc + " with your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " lightly taps " +
                "your " + hdesc + " with " +
                me->query_possessive() + " " + wep + " and " +
                "you feel " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " lightly taps " +
                QTPNAME(enemy) + " " + hdesc + " with " +
                me->query_possessive() + " " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n",
                enemy);
        }
    break;
    case 11..30:
        if((dt == W_SLASH))
        {
            me->catch_msg("You wound " + QTPNAME(enemy) + " " + hdesc +
                " slightly as you swipe your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " wounds your " + hdesc +
                " slightly as " + me->query_pronoun() +
                " swipes " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " wounds " + 
                QTPNAME(enemy) + " " + hdesc + " slightly as " + 
                me->query_pronoun() +
                " swipes " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n", enemy);
        } else {
            me->catch_msg("You bruise " + QTPNAME(enemy) + " " + hdesc +
                " slightly as you lunge your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " bruises your " + hdesc +
                " slightly as " + me->query_pronoun() +
                " lunges " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " bruises " + 
                QTPNAME(enemy) +
                " " + hdesc + " slightly as " + 
                me->query_pronoun() +
                " lunges " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n", enemy);
        }
    break;
    case 31..60:
        if((dt == W_SLASH))
        {
            me->catch_msg("Your " + wep + " rips open " + QTPNAME(enemy) +
                " " + hdesc + " as you furiously " +
                "swing your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + "'s " + wep + " rips open " +
                "your " + hdesc + " as " + me->query_pronoun() +
                " furiously swings " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + "'s " + wep + " rips open " +
                QTPNAME(enemy) + " " + hdesc + " as " + 
                me->query_pronoun() +
                " furiously swings " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n", enemy); 
        } else {
            me->catch_msg("You pummel " + QTPNAME(enemy) + " " +
                hdesc + " severly with your " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " pummels your " +
                hdesc + " severly with " +
                me->query_possessive() + " " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " pummels " + 
                QTPNAME(enemy) + " " +
                hdesc + " severly with " +
                me->query_possessive() + " " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n", enemy);
        }
    break;
    default:
        if((dt == W_SLASH))
        {
            me->catch_msg("You remove a chunk of " + QTPNAME(enemy) +
                " " + hdesc + " with a powerful swing " +
                "of your " + wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " removes a chunk of your " +
                hdesc + " with a powerful swing " +
                "of " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " removes a chunk of " + 
                QTPNAME(enemy) + " " +
                hdesc + " with a powerful swing " +
                "of " + me->query_possessive() + " " +
                wep + " and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n", enemy);
        } else {
            me->catch_msg("You smack " + QTPNAME(enemy) + " " +
                hdesc + " with a thundering sound " +
                "as you strike " + enemy->query_possessive() +
                " " + hdesc + ", leaving " +
                enemy->query_objective() + " reeling " +
                "from the force of the impact and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            enemy->catch_msg(QCTNAME(me) + " smacks your " +
                hdesc + " with a thundering sound " +
                " as " + me->query_pronoun() + " strikes " +
                "your " + hdesc + ", leaving you reeling " +
                "from the force " +
                "of the impact and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n");
            me->tell_watcher(QCTNAME(me) + " smacks " + QTPNAME(enemy) +
                hdesc + " with a thundering sound " +
                " as " + me->query_pronoun() + " strikes " +
                QTPNAME(enemy) + " " + hdesc +
                ", leaving " + enemy->query_objective() +
                " reeling from the force " +
                "of the impact and " +
                QTNAME(enemy) + " seems " + extra_dam_desc + ".\n",
                enemy);
        }
    break;
    }

    return 1;
}
