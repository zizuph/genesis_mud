/*
 * Hammerhand guild attacks routine
 * TAPAKAH, 02/2006
 */

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Khalakhor/sys/defs.h"
#include "../../daenbraigh.h"
#include "../hhands.h"
#include "hh_guild.h"
#include "hh_formulas.h"

inherit HHANDS_DIR + "hh_common";

int hh_check_attack();
int hh_can_use_weapon(object weapon);

varargs mixed *
hh_attack(string type, string str)
{
  object *att_ob,weapon,enemy;
  int a,atts, wepskill;

  if(! hh_check_attack())
    NF0("You are not ready to perform the " + type + " attack.\n");
 
  att_ob = hh_parse_command(str);
  atts = sizeof(att_ob);
  enemy = TP->query_attack();
  if(atts == 0)
    NF0("You do not have a weapon to " + type + "with.\n");

  if(atts == 1) {
    if(enemy)
      weapon = att_ob[0];
    else 
      NF0("You are not fighting anyone!\n");
  }
  else 
    if(enemy && enemy == att_ob[1])
      weapon = att_ob[0];
    else 
      if(att_ob[1])
	notify_fail("You are not fighting " + att_ob[1]->query_The_name() + "!\n");
      else
	notify_fail("You are not fighting anyone!\n");
      return 0;

  wepskill = hh_can_use_weapon(weapon);
  if(! wepskill)
    NF0("You are not skillfull enough to perform the " + type + " attack.\n");
  write("blah blah\n");
  return ({wepskill,enemy,weapon});
}

int
hh_check_attack()
{
  int hh_attack;
  
  hh_attack = TP->query_prop(HH_ATTACK);
  if(hh_attack && hh_attack != HH_ATTACK_WHIRLWIND) {
    if(TP->query_prop(HH_ATTACK_STATE) == HH_ATTACK_PREPARE)
      notify_fail("You are already preparing an attack!\n");
    else if(TP->query_prop(HH_ATTACK_STATE) == HH_ATTACK_RELAX)
      notify_fail("You are not ready to attack again yet!\n");
    return 0;
  }
  if(hh_attack == HH_ATTACK_WHIRLWIND)
    write("You stop whirling your club to protect yourself.\n");

  return 1;
}

int
hh_can_use_weapon(object weapon)
{
  int wepskill;

  wepskill = TP->query_skill(weapon->query_wt());
  if(TP->query_skill(weapon->query_wt()) < HH_SKILL) {
    notify_fail("You are not skilled enough to attack with this weapon!\n");
    return 0;
  }
  return wepskill;
}

mixed *
hh_get_hitloc(object enemy, int request_hitloc)
{
  object o_combat;
  int *hitloc_id, h_id_s, th_s, total_chance, hitloc_chance, h, *hi;
  mixed *fit_hitloc,*this_hitloc;
  
  o_combat = enemy->query_combat_object();
  if(! o_combat)
    return ({});
  hitloc_id = o_combat->query_hitloc_id();
  h_id_s = sizeof(hitloc_id);
  if(! h_id_s)
    return ({});

  fit_hitloc = ({});
  for(h=0;h<h_id_s;h++) {
    this_hitloc = o_combat->query_hitloc(hitloc_id[h]);
    if(hitloc_id[h] & request_hitloc) {
      fit_hitloc += ({this_hitloc});
      total_chance += this_hitloc[1];
    }
  }
  th_s = sizeof(fit_hitloc);
  write("HT " + th_s + "\n");
  for(h=0;h<th_s;h++)
    write(fit_hitloc[h][2] + " HITLOC\n");
  if(! th_s)
    return ({});
  if(th_s == 1)
    return fit_hitloc[0];

  hitloc_chance = random(total_chance);
  for(h=0;h<th_s;h++)
    if(hitloc_chance < fit_hitloc[h][1])
      return fit_hitloc[h];
    else
      hitloc_chance -= fit_hitloc[h][1];
  return fit_hitloc[0]; // parachute, shouldn't reach here.
}
void
hh_relax()
{
  TP->add_prop(HH_ATTACK_STATE,HH_ATTACK_READY);
  write("You feel ready to attack again!\n");
  return;
}
void
hh_jab_attackit(object weapon, object enemy, int wepskill)
{
  int hitrating, damrating, jabchance, damchance, jabskill;
  mixed jab_hitloc;
  
  jabskill = HH_F_SCALE_SKILL(TP->query_skill(SS_HH_JAB_SKILL));
  hitrating = HH_F_JAB_HIT(wepskill,
			   enemy->query_stat(SS_DEX),
			   TP->query_stat(SS_STR),
			   enemy->query_skill(SS_PARRY),
			   enemy->query_skill(SS_DEFENSE),
			   jabskill);
  jabchance = random(HH_ATTACK_CHANCE_BASE);
  write("Jab HIT: " +
	wepskill + " " +
	enemy->query_stat(SS_DEX) + " " +
	TP->query_stat(SS_STR) + " " +
	enemy->query_skill(SS_PARRY) + " " +
	enemy->query_skill(SS_DEFENSE) + " " +
	jabchance + " " +
	jabskill + "\n");
  if(hitrating > jabchance) {
    jab_hitloc = hh_get_hitloc(enemy,A_BODY);
    if(! sizeof(jab_hitloc)) {
      write("Your opponent does not have a body to jab at.\n");
      return;
    }
    write("You jab at your opponent's body.\n");
    write("Jabbing at " + jab_hitloc[2] + "\n");
    if (! jab_hitloc[0][2])
      jab_hitloc[0][2] = 1;
    damrating =
      random(HH_JAB_DAMAGE(jabskill,
			   TP->query_stat(SS_STR),
			   weapon->query_hit(),
			   weapon->query_modified_pen()[2],
			   jab_hitloc[0][2]));
    write("Jab DAM: " +
	  damrating + " " + 
	  jabskill + " " +
	  TP->query_stat(SS_STR) + " " +
	  weapon->query_hit() + " " +
	  weapon->query_modified_pen()[2] + " " +
	  jab_hitloc[0][2]+
	  "\n");
    switch(damrating) {
    case 1..5:
      write("You only manage to gently poke your opponent.\n");
      break;
    case 6..15:
      write("You mildly jab at your opponent.\n");
      break;
    case 16..35:
      write("You visibly push your opponent back with your jab.\n");
      break;
    case 36..60:
      write("Your opponent staggers as the result of your jab.\n");
      break;
    default:
      write("You produce a bonecrushing jab.\n");
    }
    enemy->heal_hp(-damrating);
    TP->set_skill(SS_HH_JAB_SKILL,TP->query_skill(SS_HH_JAB_SKILL)+4);
  }
  else {
    if(jabchance - hitrating > 20)
      write("Your opponent easily avoids your jab.\n");
    else
      write("Your opponent narrowly avoids your jab.\n");
    TP->set_skill(SS_HH_JAB_SKILL,TP->query_skill(SS_HH_JAB_SKILL)+1);
  }
  TP->add_prop(HH_ATTACK_STATE,HH_ATTACK_RELAX);
  set_alarm(HH_ATTACK_RELAX_TIME,0.0,&hh_relax());
  
  return;
}
/*
 * Jab is a straghtforward lunge for opponent's body.
 * Depends on: strength, bludgeon value, opponent's defence/parry,
 *             opponent's dexterity, weapon skill, weapon condition,
 *             accumulated attack skill.
 */
int
hh_jab(string str)
{
  mixed *cbdata;

  cbdata = hh_attack("jab",str);
  if(! cbdata[0])
    return 0;
  write("You prepare a jab at your enemy.\n");
  TP->add_prop(HH_ATTACK_STATE,HH_ATTACK_PREPARE);
  set_alarm(HH_ATTACK_PREPARE_TIME,0.0,&hh_jab_attackit(cbdata));
  return 1;
}

void
hh_hook_attackit(object weapon, object enemy, int wepskill)
{
  int hitrating, damrating, mendamrating, hookchance, damchance, hookskill;
  mixed hook_hitloc;

  hookskill = HH_F_SCALE_SKILL(TP->query_skill(SS_HH_HOOK_SKILL));
  hitrating = HH_F_HOOK_HIT(wepskill,
			    enemy->query_stat(SS_DEX),
			    TP->query_stat(SS_DEX),
			    enemy->query_skill(SS_PARRY),
			    enemy->query_skill(SS_DEFENSE),
			    weapon->query_prop(OBJ_I_WEIGHT),
			    hookskill);

  hookchance = random(HH_ATTACK_CHANCE_BASE);
  write("Hook HIT: " +
	wepskill + " " +
	enemy->query_stat(SS_DEX) + " " +
	TP->query_stat(SS_DEX) + " " +
	enemy->query_skill(SS_PARRY) + " " +
	enemy->query_skill(SS_DEFENSE) + " " +
	weapon->query_prop(OBJ_I_WEIGHT) + " " +
	hookchance + " " +
	hookskill + "\n");
  if(hitrating > hookchance) {
    hook_hitloc = hh_get_hitloc(enemy,A_HEAD);
    if(! sizeof(hook_hitloc)) {
      write("Your opponent does not have a head to aim a hook at.\n");
      return;
    }
    write("You get an arced hook at your opponent's head.\n");
    if(! hook_hitloc[0][2])
      hook_hitloc[0][2] = 1;
    damrating =
      random(HH_F_HOOK_DAMAGE(hookskill,
			      weapon->query_modified_pen()[2],
			      weapon->query_prop(OBJ_I_WEIGHT),
			      hook_hitloc[0][2]));
    write("Hook DAM: " +
	  hookskill + " " + 
	  weapon->query_modified_pen()[2] + " " +
	  weapon->query_prop(OBJ_I_WEIGHT)  + " " +
	  hook_hitloc[0][2] +
	  "\n");
    switch(damrating) {
    case 1..4:
      write("You only manage to gently tap your opponent's " + hook_hitloc[2] + ".\n");
      break;
    case 5..10:
      write("You bonk your opponent on " +  hook_hitloc[2] + "with your hook.\n");
      break;
    case 11..25:
      write("Your opponent is slightly shaken and pushed back from your hook.\n");
      break;
    case 26..45:
      write("Your opponent falters, as his " +  hook_hitloc[2] + " sustains your hook.\n");
      break;
    default:
      write("You hear cracking bones as you land your hook on your opponent's " + hook_hitloc[2] + ".\n");
    }
    enemy->heal_hp(-damrating);
    TP->set_skill(SS_HH_HOOK_SKILL,TP->query_skill(SS_HH_HOOK_SKILL)+4);
    if(damrating > 5 && random(damrating) > damrating/2) {
      write("You see dizziness in the eyes of your opponent.\n");
      TP->set_skill(SS_HH_HOOK_SKILL,TP->query_skill(SS_HH_HOOK_SKILL)+1);
      enemy->add_mana(-damrating/3);
    }
  }
  else {
    if(hookchance - hitrating > 20)
      write("Your opponent easily avoids your hook.\n");
    else
      write("Your opponent narrowly avoids your hook.\n");
  }
  TP->add_prop(HH_ATTACK_STATE,HH_ATTACK_RELAX);
  set_alarm(HH_ATTACK_RELAX_TIME,0.0,&hh_relax());

  return;
}
/*
 * Hook is a arced hit for opponent's head.
 * Depends on: dexterity, weapon's weight, opponent's defence/parry,
 *             opponent's dexterity, opponent's awareness, weapon skill,
 *             accumulated attack skill.
 */
int
hh_hook(string str)
{
  mixed *cbdata;

  cbdata = hh_attack("hook",str);
  if(! cbdata[0])
    return 0;
  write("You prepare a hook at your enemy.\n");
  TP->add_prop(HH_ATTACK_STATE,HH_ATTACK_PREPARE);
  set_alarm(HH_ATTACK_PREPARE_TIME,0.0,&hh_hook_attackit(cbdata));
  return 1;
}
/*
 * Joint is a slashed hit for opponent's arms and legs.
 * Depends on: strength, weapon bludgeon value, opponent's defence/parry,
 *             opponent's dexterity, weapon skill, accumulated attack skill.
 */
int
hh_joint(string str)
{
  write("You joint at your opponent.\n");
  return 1;
}

int
hh_wwind(string str)
{
  write("You whirlwind at your opponent.\n");
  return 1;
}
