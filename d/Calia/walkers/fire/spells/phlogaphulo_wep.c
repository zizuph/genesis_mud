/* 
   This is the flame weapon that is conjured by the Phlogaphulo spell.
   Coded by Bishop, June 12th 1999. 

*/


#pragma strict_types

inherit "/std/weapon";
inherit "/d/Genesis/magic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "defs.h"
#include FIRE_HEADER

public int hurl_weapon(string str);
public int do_wdispel(string str);

public int damage;
public int unwieldable = 1;

void 
create_weapon()
{
    set_name("spear");
    set_adj("great");
    set_adj("flaming");

    set_short("great flaming spear");
    set_long("This great flaming spear, half again as long as your" +
        " own height, feels light as a feather in your hands. The flames" +
        " do not harm you, and even though it is made out of pure fire," +
        " this weapon feels solid. With this spear you are an opponent to" +
        " be feared in melee, impaling and burning a hapless enemy. You feel" +
        " that it can be hurled at a target, as well.\n");
 

    set_hit(45);
    set_pen(45);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);

    add_prop(OBJ_S_WIZINFO,"This polearm is conjured by the phlogaphulo" +
        " spell of the Firewalkers. Trying to clone it without using the" +
        " spell will result in errors. It ranges from 40/40 to 50/50" +
        " depending on the success in spellcasting, and will sometimes" +
        " inflict extra burning damage from 0-140 hits. Additionally," +
        " it can be hurled in combat, inflicting fairly high damage.\n");

    add_prop(MAGIC_AM_MAGIC, ({	20, "enchantment"}));
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
}

public int
start()
{
    int task, hit, pen;

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    task = spell_caster->resolve_task(TASK_DIFFICULT, ({SKILL_WEIGHT, 25,
        TS_WIS, SKILL_END, SKILL_WEIGHT, 75, TS_OCC, SKILL_END, SKILL_AVG, 
        SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SKILL_END}));
    hit = query_hit() + task/20;
    pen = query_pen() + task/20;
    damage = 50 + max(task, 0);

    set_hit(hit);
    set_pen(pen);

    set_alarm(1200.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The flaming spear vanishes.\n");
    tell_room(environment(spell_target), "The flaming spear " + 
        "vanishes.\n", ({ spell_target }));

    unwieldable = 0;
    unwield_me();
    remove_spell_effect_object();

    return 1;
}

void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
    set_this_player(spell_target);
    wield_me();
    set_this_player(TP);
}

public mixed
wield(object obj)
{
    return 1;
}

public mixed
unwield(object obj)
{
    if (unwieldable == 1)
    {
        return "You are unable to unwield the flaming spear. If you wish to" +
            " be rid of it, you must either wait out the duration, or " +
            " <wdispel> it.\n";
    }
    else
    {
        return 1;
    }
}

int
query_recover()
{
    return 0;
}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

varargs void
remove_broken(int silent = 0)
{
    return;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, 
        int phit, int dam)
{
    int thispen;
    string how, how2, how3;
    object wielder;

    wielder = environment(TO);
    thispen = damage;

    thispen -= enemy->query_magic_res(MAGIC_I_RES_FIRE) * 
        (thispen/100);
    thispen -= enemy->query_magic_res(MAGIC_I_RES_MAGIC) * 
        (thispen/100);

    switch(phurt)
    {
        case -1:
            how = "but miss.";
            how2 = "but misses.";
            how3 = "but misses.";
            break;
        case 0:
            how = "but miss narrowly.";
            how2 = "but misses narrowly.";
            how3 = "but misses narrowly.";
            break;
        case 1..3:
            how = "brushing against " + enemy->query_possessive() +
                " " + hdesc + ", singing " + enemy->query_objective() +
                " slightly.";
            how2 = "brushing against " + enemy->query_possessive() +
                " " + hdesc + ", singing " + enemy->query_objective() +
                " slightly.";
            how3 = "brushing against your " + hdesc + ", singing you" +
                " slightly.";
            break;
        case 4..7:
            how = "scoring a hit on " + enemy->query_possessive() +
                " " + hdesc + ". An unsightly burn mark is left where" +
                " the spear struck.";
            how2 = "scoring a hit on " + enemy->query_possessive() +
                " " + hdesc + ". An unsightly burn mark is left where" +
                " the spear struck.";
            how3 = "scoring a hit on your " + hdesc + ". An unsightly burn" +
                " mark is left where the spear struck.";
            break;
        case 8..14:
            how = "leaving a charred and slowly bleeding wound in " +
                enemy->query_possessive() + " " + hdesc + ".";
            how2 = "leaving a charred and slowly bleeding wound in " +
                enemy->query_possessive() + " " + hdesc + ".";
            how3 = "leaving a charred and slowly bleeding wound in" +
                " your " + hdesc + ".";
            break;
        case 15..24:
            how = "stabbing it deeply into " + enemy->query_possessive()
                + " " + hdesc + ". An angry hiss is heard as the flaming" +
                " spear is pulled out of the fresh wound and the blood" +
                " it comes into contact with evaporates.";
            how2 = "stabbing it deeply into " + enemy->query_possessive()
                + " " + hdesc + ". An angry hiss is heard as the flaming" +
                " spear is pulled out of the fresh wound and the blood" +
                " it comes into contact with evaporates.";
            how3 = "stabbing it deeply into your " + hdesc + ". An angry" +
                " hiss is heard as the flaming spear is pulled out of the" +
                " fresh wound and the blood it comes into contact with" +
                " evaporates.";
            break;
        case 25..43:
            how = "inflicting a gory wound on " + enemy->query_possessive()
                + " " + hdesc + ". Blood spurts out of the open and" +
                " blackened wound at intervals.";
            how2 = "inflicting a gory wound on " + enemy->query_possessive()
                + " " + hdesc + ". Blood spurts out of the open and" +
                " blackened wound at intervals.";
            how3 = "inflicting a gory wound on your " + hdesc + ". Blood" +
                " spurts out of the open and blackened wound at intervals.";
            break;
        case 44..70:
            how = "penetrating far into " + enemy->query_possessive()
                + " " + hdesc + ", leaving a clean but extremely deep" +
                " wound.";
            how2 = "penetrating far into " + enemy->query_possessive()
                + " " + hdesc + ", leaving a clean but extremely deep" +
                " wound.";
            how3 = "penetrating far into your " + hdesc + ", leaving a" +
                " clean but extremely deep wound.";
            break;
        default:
            how = "driving it into " + enemy->query_possessive()
                + " " + hdesc + ". A look of despair flashes across " +
                enemy->query_possessive() + " features as you withdraw" +
                " the spear and ram it home once again.";
            how2 = "driving it into " + enemy->query_possessive()
                + " " + hdesc + ". A look of despair flashes across " +
                enemy->query_possessive() + " features as " + QTNAME(wielder)
                + " withdraws the spear and rams it home once again.";
            how3 = "driving it into your " + hdesc + ". " + QTNAME(wielder)
                + " withdraws the spear and you despair as " +
                wielder->query_pronoun() + " rams it home once again.";
            break;
    }


    if (wielder->resolve_task(TASK_DIFFICULT, ({SKILL_WEIGHT,
        50, TS_OCC, SKILL_END, SKILL_WEIGHT, 50, TS_WIS, SKILL_END,
        SS_ELEMENT_FIRE})) > 0 && dam > 0)
    {
        enemy->heal_hp(-random(damage));
        how += " Flames leap from the spear, burning " +
            enemy->query_objective() + " additionally.";
        how2 += " Flames leap from the spear, burning " +
            enemy->query_objective() + " additionally.";
        how3 += " Flames leap from the spear, burning you additionally.";
    }

    if (enemy->query_hp() <= 0)
    {
        how = "impaling " + enemy->query_objective() + ". " +
            capitalize(enemy->query_pronoun()) + " slides off the" +
            " flaming spear with a sizzle, lifeless.";
        how2 = "impaling " + enemy->query_objective() + ". " +
            capitalize(enemy->query_pronoun()) + " slides off the" +
            " flaming spear with a sizzle, lifeless.";
        how3 = "impaling you. You slide off the flaming spear with a" +
            " sizzle, your life draining away.";
    }        

    wielder->catch_msg("You thrust at " + QTNAME(enemy) + " with your" +
        " great flaming spear, " + how + "\n");
    wielder->tell_watcher(QCTNAME(wielder) + " thrusts at " + QTNAME(enemy) + 
        " with " + wielder->query_possessive() + " great flaming spear, " +
        how2 + "\n", enemy);
    enemy->catch_msg(QCTNAME(wielder) + " thrusts at you with " +
        wielder->query_possessive() + " great flaming spear, " + how3 + "\n"); 

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(wielder);
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    return 1;
}


int
hurl_weapon(string str)
{
    mixed *hitresult;
    object *target;
    string one, two, how, how2;
    int pen;

    pen = 15 * query_pen();

    if (!strlen(str))
    {
        notify_fail("Hurl what at whom?\n");
        return 0;
    }

    if (sscanf(str, "%s %s", one, two) == 2)
    {
        target = PARSE_THIS(two, "[at] [the] %l");

        if(one == "spear")
        {
            if (sizeof(target) > 1)
            {
                notify_fail("You can only hurl the spear at one target.\n");
                return 0;
            }
            else
            if (sizeof(target) == 0)
            {
                notify_fail("Hurl the flaming spear at whom?\n");
                return 0;
            }
            else
            {
                if (spell_caster->resolve_task(TASK_ROUTINE, ({TS_DEX,
                    SS_ELEMENT_FIRE}), target[0], ({TS_DEX, SS_DEFENCE})) > 0)
                {
                    pen -= target[0]->query_magic_res(MAGIC_I_RES_FIRE) * 
                        (pen/100);
                    pen -= target[0]->query_magic_res(MAGIC_I_RES_MAGIC) * 
                        (pen/100);

                    hitresult = target[0]->hit_me(pen, MAGIC_DT, spell_caster,
                        -1);

                    switch(hitresult[0])
                    {
                        case 0:
                            how = "The flaming spear hits you squarely, but" +
                                " you don't feel anything more than a gust of"+
                                " hot wind.\n";
                            how2 = "The flaming spear hits " + 
                                QTNAME(target[0]) + " squarely, but " +
                                target[0]->query_pronoun() + " is" +
                                " unaffected.\n";
                            break;
                        case 1..25:
                            how = "The flaming spear hits you squarely," +
                                " leaving a large burn wound.\n";
                            how2 = "The flaming spear hits " + 
                                QTNAME(target[0]) + " squarely, leaving" +
                                " a large burn wound.\n";
                            break;
                        case 26..60:
                            how = "The flaming spear hits you squarely," +
                                " penetrating your flesh and burning you" +
                                " horribly.\n";
                            how2 = "The flaming spear hits " +
                                QTNAME(target[0]) + " squarely, penetrating "+
                                target[0]->query_possessive() + " flesh and" +
                                " burning " + target[0]->query_objective() +
                                " horribly.\n";
                            break;
                        default:
                            how = "The flaming spear hits you squarely," +
                                " impaling you. The tip of the spear comes" +
                                " out on the other side, its flames instantly"+
                                " cauterizing the wound. The massive pain" +
                                " is enough to bring you to your knees.\n";                             
                            how2 = "The flaming spear hits " +
                                QTNAME(target[0]) + " squarely, impaling " +
                                target[0]->query_objective() + ". The tip of" +
                                " the spear comes out on the other side, its" +
                                " flames instantly cauterizing the wound. " +
                                capitalize(target[0]->query_pronoun()) +
                                " is brought to " + 
                                target[0]->query_possessive() + " knees by" +
                                " the violent impact.\n"; 
                            break;
                    }

                    if (target[0]->query_hp() <= 0)
                    {
                        how = "The flaming spear hits you squarely, skewering"+
                            " you and throwing you into the ground. A brief" +
                            " moment of terrific pain is followed by" +
                            " darkness.\n";
                        how2 = "The flaming spear hits "+ QTNAME(target[0])
                            + " squarely, skewering " + 
                            target[0]->query_objective() + " and throwing " +
                            target[0]->query_objective() +" into the ground. "+
                            capitalize(target[0]->query_pronoun()) + 
                            " thrashes violently a few times then lies very" +
                            " still.\n";
                    }

                    tell_room(environment(spell_caster), QCTNAME(spell_caster)+
                        " hurls " + spell_caster->query_possessive() +
                        " flaming spear at " + QTNAME(target[0]) + "!\n" +
                        how2, ({spell_caster, target[0]}));
                    target[0]->catch_msg(QCTNAME(spell_caster) + " hurls " +
                        spell_caster->query_possessive() + " flaming spear" +
                        " at you!\n" + how);
                    spell_caster->catch_msg("You hurl your flaming spear at " +
                         QTNAME(target[0]) + ".\n" + how2);
                    
                    if (target[0]->query_hp() <= 0)
                    {
                        target[0]->do_die(spell_caster);
                    }
                    remove_object();
                    return 1;
                }
                else
                {
                    tell_room(environment(spell_caster), QCTNAME(spell_caster)+
                        " hurls " + spell_caster->query_possessive() +
                        " flaming spear at " + QTNAME(target[0]) + ", but" +
                        " it misses narrowly.\n", ({spell_caster, target[0]}));
                    target[0]->catch_msg(QCTNAME(spell_caster) + " hurls " +
                        spell_caster->query_possessive() + " flaming spear" +
                        " at you, but it misses narrowly.\n");
                    spell_caster->catch_msg("You hurl your flaming spear at " +
                        QTNAME(target[0]) + ", but it misses narrowly.\n");
                    remove_object();
                    return 1;
                }
                
            }
        }
        else
        {
            notify_fail("Hurl what at whom?\n");
            return 0;
        }
    }
    else
    {
        notify_fail("Hurl what at whom?\n");
        return 0;
    }

}      

int
do_wdispel(string str)
{
    dispel_spell_effect();
    return 1;
}

void
init()
{
    add_action(hurl_weapon, "hurl");
    add_action(do_wdispel, "wdispel");
    ::init();
}