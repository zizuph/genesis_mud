/* vamp_combat.c created by Shiva@Genesis.
 * This file contains code related to vampire combat
 * This is a subpart of the vampire guild shadow.
 */

#include "../guild.h"
#include "../voptions.h"
#include "/d/Emerald/sys/skills.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#define SW shadow_who

#define COMBAT_ALARM_DELAY 30.0

static private object enemy;
static private int combat_alarm;
static private int celerity_lvl;

int query_celerity();

void do_combat_checks()
{
    if (!sizeof(SW->query_enemy(-1)))
    {
        remove_alarm(combat_alarm);
        combat_alarm = 0;
        return;
    }

    if (SW->query_attack())
    {
        add_thirst_random(10);
    }
}

void start_combat_alarm()
{
    if (!combat_alarm)
    {
        combat_alarm = set_alarm(COMBAT_ALARM_DELAY, COMBAT_ALARM_DELAY,
            do_combat_checks);
    }
}

void attack_object(object ob)
{
    SW->attack_object(ob);
    start_combat_alarm();
}

void attacked_by(object ob)
{
    SW->attacked_by(ob);
    start_combat_alarm();
}
    
void vamp_attack(object ob)
{
    if (ob)
    {
        if (ob != SW->query_attack())
        {
            attack_object(ob);
        }

        SW->reveal_me();
    }

    enemy = ob;
}

object query_vamp_attack() { return enemy; }

int set_celerity(int lvl)
{
    int prop;
 
    if (celerity_lvl && !lvl)
    {
        prop = -50;
    }
    else if (!celerity_lvl && lvl)
    {
        prop = 50;
    }
    else
    {
        celerity_lvl = lvl;
        return 0;
    }

    CP(SW, LIVE_I_QUICKNESS, prop);
    SW->query_combat_object()->cb_update_speed();
    celerity_lvl = lvl;
    return 1;
}

int query_celerity()
{
    return celerity_lvl;
}  

int query_not_attack_me(object attacker, int att_id)
{
    if (random(100) < celerity_lvl)
    {
        attacker->catch_tell(SW->query_the_name(attacker) + 
            " is moving with such celerity that you miss your chance to " +
            "strike at " + OBJ(SW) + ".\n");
        return 1;
    }

    return SW->query_not_attack_me(attacker, att_id);
}

int special_damage(int aid, string hdesc, int phurt, object enemy, int phit,
    int dam)
{
    int hurt, res, fire_dam;
    string with, where, how, what, owhat;

    SW->add_panic(-3 - (phurt / 5));
  
    /* give an attack description */
    with = "claws";
  
    where = " the " + hdesc + " of ";
  
    switch (phurt)
    {
      case 0..4:
          how = "";
          what = "tickle";
          owhat = "tickles";
          break;
      case 5..9:
          how = "";
          what = "graze";
          owhat = "grazes";
          break;
      case 10..19:
          how = "";
          what = "hurt";
          owhat = "hurts";
          break;
      case 20..29:
          how = ", rather bad";
          what = "hurt";
          owhat = "hurts";
          break;
      case 30..49:
          how = ", very bad";
          what = "hurt";
          owhat = "hurts";
          break;
      case 50..69:
          how = ", very hard";
          what = "smash";
          owhat = "smashes";
          break;
      case 70..89:
          how = ", with a bone crushing sound";
          what = "smash";
          owhat = "smashes";
          where = " ";
          break;
      default:
          how = "";
          what = "massacre";
          owhat = "massacres";
          where = " ";
    }
  
    SW->catch_tell("You " + what + where + enemy->query_the_name(SW) +
        " with your " + with + how + ".\n");
  
    if (interactive(enemy))
    {
        enemy->catch_tell(SW->query_The_name(enemy) + " " + owhat + 
            " your " + hdesc + " with " + SW->query_possessive() + " " +
            with + how + ".\n");
    }
  
    SW->tell_watcher(QCTNAME(SW) + " " + 
        owhat + where + QTNAME(enemy) + " with " + 
        SW->query_possessive() + " " + with + how + ".\n", enemy);
  
    return 1;
}

int cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
    int dt, int phit, int dam)
{
    if (!query_vamp_option(VOPT_VAMP_ATTACKS) || random(5))
    {
        return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    
    if ((phurt >= 0) && (aid & W_BOTH) && !SW->query_weapon(aid) &&
        special_damage(aid, hdesc, phurt, enemy, phit, dam))
    {
        return 1;
    }

    return SW->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
