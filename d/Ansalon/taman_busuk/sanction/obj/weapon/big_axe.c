#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";


#define WEAPON_HIT 45+random(10)
#define WEAPON_PEN 45+random(10)

varargs void
produce_msg(object enemy, string hdesc, int phurt, int dt, string short);

private int defence_extra = 0, parry_extra = 0;

public void
create_weapon()
{
    set_name("axe");
    add_name("waraxe");
    set_adj("enormous");
    add_adj("steel");
    set_short("enormous steel waraxe");
    set_pshort("enormous steel waraxes");
    set_long("An enormour steel waraxe. It is longer " +
             "than a regular axe, and has a wider blade and shaft that any "+
             "axe you have ever seen. It is very heavy and holding it takes "+
             "a great deal of effort. This axe would cause unspeakable damage " +
             "on its victims if you could hit them. As heavy as this weapon is, " +
             "quick movements will be impossible.\n");
    
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(this_object());

    add_prop(OBJ_I_VALUE, 4500);
    add_prop(OBJ_I_WEIGHT, 37000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_S_WIZINFO, 
             "A very heavy axe that inflicts additional damage due to its weight, "+
             "but at the expense of greatly lowered defensive skills. "+
             "A good hit will also stun the enemy for a brief time.\n");
}

public mixed
wield(object axe)
{
    object tp = environment(axe);

    if(!living(tp))
    {
        return -1;
    }

    if(tp->query_stat(SS_STR) < 130)
    {
        return "You struggle with the incredible weight of the weapon, " +
               "and realize that you are simply too weak to wield the enormous steel waraxe.\n";
    }

    if(tp->query_skill(SS_DEFENCE) > 30)
    {
        tp->set_skill_extra(SS_DEFENCE,
            tp->query_skill_extra(SS_DEFENCE) - 30);
        defence_extra = -30;
    }

    if(tp->query_skill(SS_PARRY) > 30)
    {
        tp->set_skill_extra(SS_PARRY,
            tp->query_skill_extra(SS_PARRY) - 30);
        parry_extra = -30;
    }

    tell_room(environment(tp), QCTNAME(tp) + 
              " manages to wield the enormous " +
              "steel waraxe.\n", tp);
    write("With some effort you manage to wield the the enormous steel waraxe.\n");
    tp->add_fatigue(-20);
    return 1;
}

public mixed
unwield(object axe)
{
    object tp = query_wielded();

    if(tp->query_skill(SS_DEFENCE) > 30)
    {
        tp->set_skill_extra(SS_DEFENCE,
            tp->query_skill_extra(SS_DEFENCE) - defence_extra);
        defence_extra = 0;
    }

    if(tp->query_skill(SS_PARRY) > 30)
    {
        tp->set_skill_extra(SS_PARRY,
            tp->query_skill_extra(SS_PARRY) - parry_extra);
        parry_extra = 0;
    }

    tell_room(environment(tp), QCTNAME(tp) + " releases the enormous steel waraxe "+
              "with a sigh of relief.\n", tp);
    tp->catch_tell("You let out a sigh of relief as you unwield the enormous steel waraxe.\n");
    return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  object tp = query_wielded();
  object stun;
  int real_dam;

  if(random(4))
  {
      produce_msg(enemy,hdesc,phurt,dt);
      return 1;
  }
  
  if(dam > 0)
      real_dam = 2*dam; // (3 * dam) / 2;
  
  //  ::did_hit(aid, hdesc, phurt, enemy, dt, phit, real_dam);
  
  if (enemy->query_hp() <= 0)
    {
      tp->catch_msg("Your enormous steel waraxe pulverizes " +
                    QTNAME(enemy) + " and a sudden chill sweeps by.\n");
      enemy->catch_msg(QTPNAME(enemy) + " enormous steel waraxe pulverizes " +
                       "you and Death sweeps by.\n");
      tp->tell_watcher(QTPNAME(enemy) + " enormous steel waraxe " +
                       "pulverizes " + QTNAME(enemy) + " and a sudden " +
                       "chill sweeps by.\n");
      enemy->do_die(tp);
      return 1;
    }
  switch(dam)
    {
    case -1:
    case -2:
    case 0:
      tp->catch_msg("You barely miss " + QTPNAME(enemy) + " " +
                    hdesc + " making " + HIM(enemy) +
                    " shudder at the sound of whistling air " +
                    "caused by your enormous steel waraxe.\n");
      enemy->catch_msg(QCTNAME(tp) + " barely misses your " + hdesc +
                       " making you shudder at the sound of whistling " +
                       "air caused by " + tp->query_possessive() + 
                       " enormous steel waraxe.\n");
      tp->tell_watcher(QCTNAME(tp) + " barely misses " +
                       QTPNAME(enemy) + " " + hdesc +
                       " making " + HIM(enemy) + 
                       " shudders at the sound of whistling " +
                       "air caused by " + QTPNAME(tp) + 
                       " enormous steel waraxe.\n", enemy);
      enemy->add_panic(5);
      break;
    case 1..50:
      tp->catch_msg("You arc your enormous steel waraxe at " +
                    QTNAME(enemy) + " hurting " +
                    enemy->query_possessive() + " " + hdesc + ".\n");
      enemy->catch_msg(QCTNAME(tp) + " arcs " + tp->query_possessive() + 
                       " enormous steel waraxe at you, " +
                       "hurting your " + hdesc + ".\n");
      tp->tell_watcher(QCTNAME(tp) + " arcs " + tp->query_possessive() +
                       " enormous steel waraxe at " + QTNAME(enemy) +
                       " hurting " + QTPNAME(enemy) + " " +
                       hdesc + ".\n", enemy);
      enemy->add_panic(10);
      break;
    case 51..225:
      tp->catch_msg("You swing your enormous steel waraxe around " +
                    "widely and cut a deep wound on " +
                    QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg(QCTNAME(tp) + " swings " + tp->query_possessive() +
                       " enormous steel waraxe around widely and " + 
                       "cuts a deep wound on your " + hdesc + ".\n");
      tp->tell_watcher(QCTNAME(tp) + " swings " + tp->query_possessive() +
                       " enormous steel waraxe around widely and " + 
                       "cuts a deep wound on " + QTPNAME(enemy) + " " +
                       hdesc + ".\n", enemy);
      enemy->add_panic(15);
      break;
    default:
      tp->catch_msg("You drop the enormous steel " +
                    "waraxe down on " + QTNAME(enemy) +
                    " with deadly precision, crushing " + enemy->query_possessive() + " " +
                    hdesc + ".\n");
      enemy->catch_msg(QCTNAME(tp) + " drops "+tp->query_possessive()+
                       "enormous steel waraxe down on you with deadly precision, " + 
                       "crushing your " + hdesc + ".\n");
      tp->tell_watcher(QCTNAME(tp) + " drops " + 
                       tp->query_possessive() +
                       " enormous steel waraxe down on " +
                       QTNAME(enemy) + " with deadly precision, crushing " + QTPNAME(enemy) +
                       " " + hdesc + ".\n", enemy);
      enemy->add_panic(45);

      setuid();
      seteuid(getuid());
      enemy->add_attack_delay(5+random(phurt/5));
    }
  return 1;
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}

varargs void
produce_msg(object enemy, string hdesc, int phurt, int dt, string short)
{
    object tp = this_object()->query_wielded();

    if (!short)
    {
	short = this_object()->query_short();
    }

    if (enemy->query_hp() <= 0)
    {
	switch (dt)
	{
	    case W_SLASH:
	        tp->catch_msg("With great momentum you swing your "+short+" into "+QTNAME(enemy)+
	                      "'s "+hdesc+" ending all resistance. "+
                              QCTNAME(enemy)+" falls lifeless to the ground as you tuck your weapon free.\n");

                enemy->catch_msg("With great momentum "+QTNAME(tp)+" swings "+HIS(tp)+" "+short+
                                 " into your "+hdesc+" ending all your resistance. "+
                                 "You feel a sharp pain as "+QTNAME(tp)+" pulls "+HIS(tp)+" "+short+" free.\n"); 

                tp->tell_watcher("With great momentum "+QTNAME(tp)+" swings "+HIS(tp)+" "+short+
	                         " into "+QTNAME(enemy)+"'s "+hdesc+" ending all resistance. "+
                                 QCTNAME(enemy)+" falls lifeless to the ground as "+QTNAME(tp)+" tucks "+HIS(tp)+" "+short+" free.\n", enemy);
	    break;
	case W_BLUDGEON:
	    tp->catch_msg("Determined to end this struggle, you put all your strength into one last swing. Your "+short+" crushes "+QTNAME(enemy)+"'s "+
	                  hdesc+" with an unmatched force. "+QCTNAME(enemy)+" is thrown across the room where "+HIS(enemy)+" body lands in a barely recognizable puddle.\n");
            

            enemy->catch_msg("Determined to end this struggle, "+QTNAME(tp)+" seems to put all "+HIS(tp)+" strength into one last swing. "+
                             HIS(tp)+" "+short+" crushes your "+hdesc+" with an unmatched force. You are thrown across the room as you are killed.\n");
            
            tp->tell_watcher("Determined to end this struggle, "+QTNAME(tp)+" seems to put all "+HIS(tp)+" strength into one last swing. "+HIS(tp)+" "+short+
                             "crushes "+QTNAME(enemy)+"'s "+hdesc+" with an unmatched force. "+QCTNAME(enemy)+" is thrown across the room where "+
                             HIS(enemy)+" body lands in a barely recognizable puddle.\n", enemy);
            break;
	}
	enemy->do_die(tp);
	return;
    }

    switch(phurt)
    {
        case -2:
        // parries hit
            tp->catch_msg("You block "+QTNAME(enemy)+" attack with your "+short+".\n");
            enemy->catch_msg(QCTNAME(tp)+" blocks your attack with "+HIS(tp)+" "+short+".\n");
            tp->tell_watcher_miss(QCTNAME(tp)+" blocks "+QTNAME(enemy)+
                                  "'s attack with "+HIS(tp)+" "+short+".\n",enemy);
            break;
            
        case -1:
            // dodges hit
            tp->catch_msg("You swing your "+short+" at "+QTNAME(enemy)+
                          " but "+HE(enemy)+" evades your slow attack.\n");
            
            enemy->catch_msg(QCTNAME(tp)+" swings "+HIS(tp)+" "+short+" at you, but you evade "+HIS(tp)+" slow attack.\n");
            
            tp->tell_watcher_miss(QCTNAME(tp)+" swings "+HIS(tp)+" "+short+" at "+QTNAME(enemy)+
                                  ", but "+QTNAME(enemy)+" evades the attack.\n",enemy);
            break;
	case 0:
	    tp->catch_msg("Due to the strain of swinging your heavy weapon, you barely manage to bump the "+short+" into "+QTNAME(enemy)+"'s "+hdesc+".\n");
            
	    enemy->catch_msg(QCTNAME(tp)+" bumps "+HIS(tp)+" "+short+" into your "+hdesc+" weakly.\n");
            
	    tp->tell_watcher(QCTNAME(tp)+" bumps "+HIS(tp)+" "+short+" into "+QTNAME(enemy)+"'s "+hdesc+" weakly.\n", enemy);
            break;
	case 1..20:
            tp->catch_msg("You crush "+QTNAME(enemy)+"'s "+hdesc+" with "+ 
                          "your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" crushes your "+hdesc+" with "+
                             HIS(tp)+" "+short+".\n");
	    tp->tell_watcher(QCTNAME(tp)+" crushes "+QTNAME(enemy)+"'s "+hdesc+
                             " with "+HIS(tp)+" "+short+".\n",enemy);
	    break;
	case 21..45:
	    tp->catch_msg("You pulverize "+QTNAME(enemy)+"'s "+hdesc+" with "+
                          "your "+short+".\n");
	    enemy->catch_msg(QCTNAME(tp)+" pulverizes your "+hdesc+" with "+
                             HIS(tp)+" "+short+".\n");
	    tp->tell_watcher(QCTNAME(tp)+" pulverizes "+QTNAME(enemy)+"'s "+hdesc+
                             " with "+HIS(tp)+" "+short+".\n",enemy);
	    break;
	default: 
	    tp->catch_msg("You cripple "+QTNAME(enemy)+" as you cut "+HIS(enemy)+" "+hdesc+" deeply with your "+short+".\n");
            
	    enemy->catch_msg(QCTNAME(tp)+" cripples you as he cut your "+hdesc+" deeply with "+HIS(tp)+
                             " "+short+".\n");
            
	    tp->tell_watcher(QCTNAME(tp)+" cripples "+QTNAME(enemy)+" as "+HE(tp)+" cuts " +QTNAME(enemy)+"'s "+hdesc+ 
                             " deeply with "+HIS(tp)+" "+short+".\n",enemy);
	    break;
    }
}

