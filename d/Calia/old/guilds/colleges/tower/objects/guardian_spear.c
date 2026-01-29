/*
   This is the flame weapon that the guardian of the Marble Tower wields.
   
   Bishop of Calia, July 2003.
*/


#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

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
        " be feared in melee, impaling and burning a hapless enemy.\n");
 

    set_hit(50);
    set_pen(60);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);

    add_prop(OBJ_S_WIZINFO, "This extremely powerful polearm will likely" +
        " not fall into mortal hands. It is wielded by the guardian of" +
        " the Marble Tower, the guildhome for the Colleges of Elemental" +
        " Magic. It burns opponents additionally for up to 250 hp on" +
        " each hit unless the target succeeds in a difficult task.\n");
        
    add_prop(MAGIC_AM_ID_INFO, ({"This spear has been enchanted with" +
        " fire magic.\n", 10, "This weapon burns opponents in combat.\n", 25, 
        "This weapon will burn opponents in combat, but can only be" +
        " wielded by someone resistant to its flames.\n", 40}));        

    add_prop(MAGIC_AM_MAGIC, ({	50, "enchantment"}));
    add_prop(OBJ_I_VALUE, 50000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
}


public mixed
wield(object obj)
{
    object wielder = environment(TO);

    if (wielder->query_magic_res(MAGIC_I_RES_FIRE) < 30 &&
        wielder->query_name() != "Myam")
    {
        return "The spear is simply too hot for you to wield.\n";
    }
    
    wielder->catch_tell("You grasp the flaming spear.\n");
    tell_room(environment(wielder), QCTNAME(wielder) + " grasps" +
        " a great flaming spear in " + wielder->query_possessive() + 
        " hands.\n", wielder);
    
    return 1;
}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, 
        int phit, int dam)
{
    int damage;
    string how, how2, how3;
    object wielder;

    wielder = environment(TO);
    damage = 250;

    damage -= enemy->query_magic_res(MAGIC_I_RES_FIRE) * 
        (damage/100);
    damage -= enemy->query_magic_res(MAGIC_I_RES_MAGIC) * 
        (damage/100);

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


    if (enemy->resolve_task(TASK_DIFFICULT, ({TS_OCC, SS_DEFENCE}))
        < 0 && dam > 0)
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

