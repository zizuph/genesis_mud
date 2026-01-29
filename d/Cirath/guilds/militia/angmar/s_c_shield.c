#pragma save_binary

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <options.h>
#include "defs.h"
#include "guild.h"


/*
 * These variables will be set every time player wear/remove something
 * We will use them in function query_not_attack_me() which is called
 * from combat object every time enemy tries to hit shadow_who
 * Better have them ready - saves CPU
 */
static int shield_red = 79;  /* laymans have 50 - efficiency 60%     */

static int shield_skill;     /* what is SS_SHIELD of shadow_who    */
static int shield_worn;      /* does he wear a shield              */
static string *shields_desc; /* short desc of worn shields         */
static int shield_bonus;     /* what is the shield_bonus           */
static object *shields;      /* shields worn			   */
static int s_c_pun;         /* is player punished?                */

static int defend_value;     /* overall defend value used           */

static object *list_of_defenders = ({ }); /* players that help defend */
static object who_defend;		  /* I am helping to defend   */

int alarm_is_set;

void
add_defender(object who,int for_time)
{
  list_of_defenders += ({ who });
  set_alarm(itof(for_time), 0.0, "remove_defender", who);
}
void
remove_defender(object who)
{
  list_of_defenders -= ({ who });
}
object *
query_list_of_defenders()
{
   return list_of_defenders;
}

void
set_defend(object who)
{
  who_defend = who;  
}
void
clear_defend()
{
  who_defend = 0;
}
object
query_defend()
{
  return who_defend;
}


void
set_shield_bonus(int i) 
{ 
  shield_bonus = i * shield_red / 100;
}

static void
make_messages(object attacker, string attack_desc, string shield)
{
  shadow_who->catch_msg("You cover "+QTNAME(attacker)+"'s "+
                        attack_desc+" with your "+shield+".\n");
  attacker->catch_msg(QCTNAME(shadow_who)+" covers your "+
                  attack_desc+" with "+HIS(shadow_who)+" "+shield+".\n");
  shadow_who->tell_watcher(QCTNAME(shadow_who)+" covers "+QTNAME(attacker)+
                "'s "+attack_desc+" with "+HIS(shadow_who)+
                " "+shield+".\n", attacker);
}


/*
 * function called from other player when we are trying to defend
 * him with a shield
 * Returns: 0 - failed to help
 *	    1 - covered attack
 */
int
defend_with_shield(object attacker, int attack_value, string attack_desc)
{
  int i;
  string shield;

  if(!shield_worn)
    return 0;

  if((random(attack_value) > random(defend_value*shield_red/100))
     || (random(100) > shield_skill)
    )
    return 0;

  i = random(sizeof(shields));
  if((!shields[i]) || (shields[i]->query_worn() != shadow_who))
  {
    if(!alarm_is_set)
    {
      set_alarm(5.0, 0.0, "update_shield_variables", shadow_who);
      alarm_is_set = 1;
    }
    return 0;
  }

  shield = shields_desc[i];
  make_messages(attacker, attack_desc, shield);
  shields[i]->got_hit(0,0,attacker,0,1);
  return 1;  /* no hit - attack was covered */
}

/*
 * function called when attacker tries to hit us
 * returns: 0 - allow to hit,  1 - don't allow to hit
 */
int
query_not_attack_me(object attacker, int att_id)
{
  object combat_object;
  mixed *attack;
  string attack_desc, shield;
  int i,d,attack_value,shield_mod;

  combat_object = attacker->query_combat_object();
  attack = combat_object->query_attack(att_id);

  if(!attack)
    return shadow_who->query_not_attack_me(attacker, att_id);
		/* what if att_id was spell or spec. attack? */

  attack_value = 2 * ((attacker->query_stat(SS_DEX) / 5) + attack[4]);
  attack_desc = combat_object->cb_attack_desc(att_id);

  d = sizeof(list_of_defenders);
  if(d && (ENV(list_of_defenders[0]) == ENV(shadow_who)) &&
     list_of_defenders[0]->defend_with_shield(attacker,
                                              attack_value,
                                              attack_desc))
    return 1; /* no hit - attack was covered */

  if((d==2) && (ENV(list_of_defenders[1]) == ENV(shadow_who))&&
     list_of_defenders[1]->defend_with_shield(attacker,
                                              attack_value,
                                              attack_desc))
    return 1; /* no hit - attack was covered */


  if((!shield_worn) || (s_c_pun > 2))
    return shadow_who->query_not_attack_me(attacker, att_id);

  if(who_defend) 
    shield_mod = shield_bonus;
  else
    shield_mod = shield_red + shield_bonus;
  if(s_c_pun > 1) shield_mod = shield_mod / 2;

  if((random(attack_value) > random(defend_value*shield_mod/100))
     || (random(100) > (shield_skill+15))
    )
    return shadow_who->query_not_attack_me(attacker, att_id); 
  /* haven't succeded to cover attack with shield but maybe something else */

  i = random(sizeof(shields));
  if((!shields[i]) || (shields[i]->query_worn() != shadow_who))
  {
    if(!alarm_is_set)
    {
      set_alarm(5.0, 0.0, "update_shield_variables", shadow_who);
      alarm_is_set = 1;
    }
    return shadow_who->query_not_attack_me(attacker, att_id);
  }

  shield = shields_desc[i];
  make_messages(attacker, attack_desc, shield);
  shields[i]->got_hit(0,0,attacker,0,1);
  return 1;  /* no hit - attack was covered */
}

nomask int *
query_shield_variables()  /* only for debug reasons */
{
  return ({ shield_skill, shield_worn, shield_bonus });
}

nomask int
query_shield_worn()
{
  return shield_worn;
}

/*
 * this should be called every time player tries to wear/remove something
 * we use it for setting our variables
 */
varargs public mixed 
query_armour(int which)
{
  if(!alarm_is_set)
  {
    set_alarm(5.0, 0.0, "update_shield_variables", shadow_who);
    alarm_is_set = 1;
  }
  return shadow_who->query_armour(which);
}

nomask void
update_shield_variables(object who)
{
  object sh;

  alarm_is_set = 0;

  s_c_pun = who->query_prop(S_C_PUN);
  shield_skill = who->query_skill(SS_SHIELD);

  shields_desc = ({ });
  shields = ({ });
  shield_worn = 0;
  if((sh = who->query_armour(W_LEFT)) && 
     (sh->query_at() == A_SHIELD))
  {
    shield_worn = 1;
    shields_desc += ({ sh->short() });
    shields += ({ sh });
  }
  if((sh = who->query_armour(W_RIGHT)) && 
     (sh->query_at() == A_SHIELD))
  {
    shield_worn = 1;
    shields_desc += ({ sh->short() });
    shields += ({ sh });
  }

  defend_value = ((shadow_who->query_stat(SS_DEX) / 5) + shield_skill);
}
 
