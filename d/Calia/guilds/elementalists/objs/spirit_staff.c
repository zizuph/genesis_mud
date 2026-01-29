/*
   This is the staff of sprit, a magical quarterstaff that's found in Calia.
   It is mediocre for someone with no skill in life magic, but for someone
   with skill 30 or over, it gets +1/+1 for every 10 skill. It also has a 
   1 in 8 chance of doing a short add_attack_delay on a hit.
   
   Bishop of Calia, July 2003.
*/

#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Calia/domain.h"

int skill;

string 
adj()
{
    object ob = TO->query_wielded();
    
    if (!objectp(ob) || ob->query_skill(SS_ELEMENT_LIFE) < 30)
    {
        return "painted";
    }
    else
    if (ob->query_skill(SS_ELEMENT_LIFE) < 60)
    {
        return "sculpted";
    }
    else
    {
        return "shadowy";
    }
}

string
extra_long()
{
    object ob = TO->query_wielded();
    
    if (!objectp(ob) || ob->query_skill(SS_ELEMENT_LIFE) < 30)
    {
        return "";
    }
    else
    if (TP->query_skill(SS_ELEMENT_LIFE) < 60)
    {
        return " The staff exudes energy, but you feel no discomfort" +
            " holding it in your hands.";
    }
    else
    {
        return " The staff radiates spiritual energy, but you are" +
            " unaffected by it.";
    }
}


void
create_weapon()
{
    set_name("quarterstaff");
    
    set_adj("@@adj@@");
    set_adj("black");
    set_short("@@adj@@ black quarterstaff");
    
    set_long("This solid quarterstaff must have been cut from a" +
        " stout branch. It has been expertly prepared, perfectly" +
        " smooth all around. What really catches your eye about this" +
        " weapon though is the marvelous paint job it has been given," +
        " covering the full length of the staff. The staff entire" +
        " has been painted with shades of black and dark grey. Thick"+
        " and thin lines snake their way around the weapon in"+
        " intricate patterns. It reminds you of the soul."+
        "@@extra_long@@\n");
  
    set_default_weapon(40, 35, W_POLEARM, W_BLUDGEON, W_BOTH);
    set_wf(TO);
  
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This staff has been enchanted with" +
        " life magic.\n", 10, "This staff has been enchanted to give" +
        " additional benefits to those who know life magic.\n", 25, 
        "This staff performs better for masters of life magic, in" +
        " addition to sometimes stunning opponents.\n", 40}));
    
    add_prop(OBJ_S_WIZINFO, "This staff gets higher hit/pen for a" +
        " wielder who has skill in life magic, and has a 1 in 8 chance" +
        " of doing a short attack delay on hit if that's the case.\n");
        
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 35) + 1000);
}


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, 
    int dam)
{
    if (phurt >= 0 && skill > 30 && !random(8))
    {
        TP->catch_msg(enemy->query_The_name(TP) + " was stunned by" +
            " the " + TO->short() + ".\n");
        enemy->catch_msg("You are stunned by the " 
            + TO->short() + "!\n");
        TP->tell_watcher(QCTNAME(enemy) + " was stunned by the " +
            TO->short() + "!\n", enemy);
            
        enemy->add_attack_delay(skill/10);
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);    
    
    return 0;
}


mixed
wield(object weapon)
{
    object wielder = query_wielded();
    skill = wielder->query_skill(SS_ELEMENT_LIFE);

    if (skill >= 30)
    {
        wielder->catch_msg("The quarterstaff feels alive as you" +
            " wield it.\n");
        TO->set_hit(TO->query_hit() + skill/10);
        TO->set_pen(TO->query_pen() + skill/10);
        tell_room(environment(wielder),QCTNAME(wielder)+" wields "+
            wielder->query_possessive()+" quarterstaff with both "+
            "hands.\n",wielder);
        return 1;
    }
    
    return 0;
}

mixed
unwield(object weapon)
{
    object wielder = query_wielded();
    skill = wielder->query_skill(SS_ELEMENT_LIFE);

    if (skill >= 30)
    {
        wielder->catch_msg("The quarterstaff returns to normal as you" +
            " unwield it.\n");
        TO->set_hit(TO->query_hit() - skill/10);
        TO->set_pen(TO->query_pen() - skill/10);
        tell_room(environment(wielder),QCTNAME(wielder) + " unwields "+
            wielder->query_possessive()+" quarterstaff.\n",wielder);
        return 1;
    }
    
    return 0;
}    
