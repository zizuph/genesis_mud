/* 2017-11-06 Malus: Modified did_hit override to always call ::did_hit */ 
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#define STUN_OBJECT "/d/Earthsea/lib/stun"

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#define WEAPON_HIT 58
#define WEAPON_PEN 60

private int extra_slow = 0, defence_extra = 0, parry_extra = 0;

public void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    add_name("broadsword");
    add_pname("broadswords");
    set_adj("gigantic");
    add_adj("steel");
    set_short("gigantic steel broadsword");
    set_pshort("gigantic steel broadswords");
    set_long("A gigantic steel broadsword. It is extraordinarily " +
        "long and has a blade wider than any sword you have " +
        "ever seen. It is extremely heavy and just holding it " +
	"takes some effort. This sword should be able " +
        "to inflict much damage on its victims. You gaze in awe, " +
        "for the blade seems to be pulsating with power.\n");
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(this_object());
    /* Too heavy to effectively parry */
    set_ac_modifier(-5);
    add_prop(OBJ_I_VALUE, 4500);
    add_prop(OBJ_I_WEIGHT, 45000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, 
        "A super heavy sword that inflicts a lot of damage " +
        "but at the expense of -(MAX(200-SS_STR, 175)) " + 
        "LIVE_I_QUICKNESS and -5 defence " +
        "and -5 parry. The AC modifier is also set to -5 because " +
        "parrying is more difficult due to the sword's weight. " +
        "A good hit will also stun and immobilize " +
        "the enemy for a brief time.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This weapon inflicts awesome damage at the expense of " +
        "quickness and defensive capabilities. A good blow " +
        "would probably send an enemy into shock.\n", 60}));
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    set_keep(1);
}

public mixed
wield(object sword)
{
    object tp = environment(sword);

    if(!living(tp))
    {
        return -1;
    }

    if(tp->query_stat(SS_STR) < 100)
    {
        return "You struggle with all your might, but you are " +
            "too weak to wield the gigantic steel broadsword.\n";
    }

    extra_slow = MAX(200 - tp->query_stat(SS_STR), 75);
    tp->add_prop(LIVE_I_QUICKNESS, tp->query_prop(LIVE_I_QUICKNESS)
                          - extra_slow);

    if(tp->query_skill(SS_DEFENCE) > 5)
    {
        tp->set_skill_extra(SS_DEFENCE,
            tp->query_skill_extra(SS_DEFENCE) - 5);
        defence_extra = -5;
    }

    if(tp->query_skill(SS_PARRY) > 5)
    {
        tp->set_skill_extra(SS_PARRY,
            tp->query_skill_extra(SS_PARRY) - 5);
        parry_extra = -5;
    }

    tell_room(environment(tp), "With all " +
        tp->query_possessive() + " might " + QCTNAME(tp) + 
	      " manages to wield the gigantic " +
	      "steel broadsword.\n", tp);
    write("With all your might you manage to wield the " +
        "the gigantic steel broadsword.\n");
    return 1;
}

public mixed
unwield(object sword)
{
    object tp = query_wielded();

    tp->add_prop(LIVE_I_QUICKNESS,
        tp->query_prop(LIVE_I_QUICKNESS) + extra_slow);
    extra_slow = 0;

    if(tp->query_skill(SS_DEFENCE) > 5)
    {
        tp->set_skill_extra(SS_DEFENCE,
            tp->query_skill_extra(SS_DEFENCE) - defence_extra);
        defence_extra = 0;
    }

    if(tp->query_skill(SS_PARRY) > 5)
    {
        tp->set_skill_extra(SS_PARRY,
            tp->query_skill_extra(SS_PARRY) - parry_extra);
        parry_extra = 0;
    }

    tell_room(environment(tp), QCTNAME(tp) + " looks relieved as " +
        tp->query_pronoun() + " unwields the gigantic steel " +
        "broadsword.\n", tp);
    tp->catch_tell("You arms feel relieved as you unwield the sword.\n");
    return 1;
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
	int dt, int phit, int dam)
{
  object tp = query_wielded();
  object stun;
  int result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
  if(random(4))
      return result;

  if (enemy->query_hp() <= 0)
    {
      tp->catch_msg("Your gigantic steel broadsword massacres " +
		    QTNAME(enemy) + " and a sudden chill sweeps by.\n");
      enemy->catch_msg(QTPNAME(enemy) + " gigantic steel broadsword " +
		       "massacres you and Death sweeps by.\n");
      tp->tell_watcher(QTPNAME(enemy) + " gigantic steel broadsword " +
		       "massacres " + QTNAME(enemy) + " and a sudden " +
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
		    hdesc + " as " + enemy->query_pronoun() +
		    " gulps uneasily at the sound of howling air " +
		    "attacked by your gigantic steel broadsword.\n");
      enemy->catch_msg(QCTNAME(tp) + " barely misses your " + hdesc +
		       " as you gulp uneasily at the sound of howling " +
		       "air attacked by " + tp->query_possessive() + 
		       " gigantic steel broadsword.\n");
      tp->tell_watcher(QCTNAME(tp) + " barely misses " +
		       QTPNAME(enemy) + " " + hdesc +
		       " as " + enemy->query_pronoun() + 
		       " gulps uneasily at the sound of howling " +
		       "air attacked by " + QTPNAME(tp) + 
		       " gigantic steel broadsword.\n", enemy);
      enemy->add_panic(5);
      break;
    case 1..50:
      tp->catch_msg("You arc your gigantic steel broadsword at " +
		    QTNAME(enemy) + " slightly grazing " +
		    enemy->query_possessive() + " " + hdesc + ".\n");
      enemy->catch_msg(QCTNAME(tp) + " arcs " + tp->query_possessive() + 
		       " gigantic steel broadsword at you, " +
		       "slightly grazing your " + hdesc + ".\n");
      tp->tell_watcher(QCTNAME(tp) + " arcs " + tp->query_possessive() +
		       " gigantic steel broadsword at " + QTNAME(enemy) +
		       " slightly grazing " + QTPNAME(enemy) + " " +
		       hdesc + ".\n", enemy);
      enemy->add_panic(10);
      break;
    case 51..150:
      tp->catch_msg("You swing your gigantic steel broadsword around " +
		    "widely and land a glancing blow on " +
		    QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg(QCTNAME(tp) + " swings " + tp->query_possessive() +
		       " gigantic steel broadsword around widely and " + 
		       "lands a glancing blow on your " + hdesc + ".\n");
      tp->tell_watcher(QCTNAME(tp) + " swings " + tp->query_possessive() +
		       " gigantic steel broadsword around widely and " + 
		       "lands a glancing blow on " + QTPNAME(enemy) + " " +
		       hdesc + ".\n", enemy);
      enemy->add_panic(15);
      break;
    case 151..250:
      tp->catch_msg("You drop the enormous blade of your gigantic " +
		    "steel broadsword down hard on " + QTNAME(enemy) +
		    ", crushing " + enemy->query_possessive() + " " +
		    hdesc + " with the immense weight of the sword.\n");
      enemy->catch_msg(QCTNAME(tp) + " drops the enormous blade of " + 
		       tp->query_possessive() +
		       " gigantic steel broadsword down hard on you, " +
		       "crushing your " + hdesc + " with the immense " +
		       "weight of the sword.\n");
      tp->tell_watcher(QCTNAME(tp) + " drops the enormous blade of " + 
		       tp->query_possessive() +
		       " gigantic steel broadsword down hard on " +
		       QTNAME(enemy) + " crushing " + QTPNAME(enemy) +
		       " " + hdesc + " with the immense " +
		       "weight of the sword.\n", enemy);
      enemy->add_panic(45);
      setuid();
      seteuid(getuid());
      stun = clone_object(STUN_OBJECT);
      stun->move(enemy);
      stun->set_restrict_movement(1);
      stun->stun_player(5 + random(phurt / 5));
      break;
    default:
      tp->catch_msg("You mightly cleave " + QTPNAME(enemy) + " " +
		    hdesc + ", wounding " + enemy->query_objective() +
		    " severely and the force of the tremendous impact " +
		    "from your gigantic steel broadsword sends " +
		    enemy->query_objective() + 
		    " into a stunning state of shock.\n");
      enemy->catch_msg(QCTNAME(tp) + " mightly cleaves your " +
		       hdesc + ", wounding you severely and the " +
		       "force of the tremendous impact from " + 
		       tp->query_possessive() +
		       "gigantic steel broadsword sends you into " +
		       "a stunning state of shock.\n");
      tp->tell_watcher(QCTNAME(tp) + " mightly cleaves " +
		       QTPNAME(enemy) + " " + hdesc + ", wounding " +
		       enemy->query_objective() + " severely and the " +
		       "force of the tremendous impact from " + 
		       QTPNAME(tp) + " " +
		       "gigantic steel broadsword sends " +
		       enemy->query_objective() + " into " +
		       "a stunning state of shock.\n", enemy);
      
      enemy->add_panic(60);
      setuid();
      seteuid(getuid());
      stun = clone_object(STUN_OBJECT);
      stun->move(enemy);
      stun->set_restrict_movement(1);
      stun->stun_player(10 + random(phurt / 5));
      break;
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
