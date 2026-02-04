/*
   Caravan member base class
   by Udana, 03/06
 * 
 * Cotilllion - 2016-12-05
 * - Fixed too many alarms
 */

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include <filter_funs.h>
#include "../include/defs.h"

#define PLAYER_I_ATTACKED_CARAVAN "_player_i_attacked_caravan"
#ifndef MONSTER_I_NOT_BOUNCED
#define MONSTER_I_NOT_BOUNCED "_monster_i_not_bounced"
#endif

inherit STDMONSTER;

public int is_caravan();

string colour;

/* 0 is guard, 1 is merchant, 2 is coachman */
int type;

/* Masked in inherited objects */
public void create_caravan_member();

/* Called on caravan disbanding, simply removes this object */
public void remove_caravan_object();

public string query_colour();

/* Also arms the given caravan member */
public void set_colour(string new_colour);

public int query_type();

/* Request help is called when attacked, then it calls help_friend in all friend objects */
public void request_help(object enemy);
public void help_friend(object enemy, object victim);

static int help_alarm;

public void create_monster(){
  ::create_monster();
  set_aggressive("@@aggressive");
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(NPC_I_NO_UNARMED, 1);
	remove_prop(MONSTER_I_NOT_BOUNCED);
  set_default_answer("say Quiet! I think I saw something in the forest!\n", 1);
  create_caravan_member();
}

int aggressive()
{
	return TP->query_prop(PLAYER_I_ATTACKED_CARAVAN);
}

public int query_type()
{
  return type;
}

public void attacked_by(object enemy)
{
    ::attacked_by(enemy);
    enemy->add_prop(PLAYER_I_ATTACKED_CARAVAN, 1);
    remove_prop(OBJ_M_NO_ATTACK);

    if (!get_alarm(help_alarm))
        help_alarm = set_alarm(1.0, 0.0, &request_help(enemy));
    remove_prop(LIVE_S_EXTRA_SHORT);
}

public void request_help(object enemy)
{
  object *friends = filter(all_inventory(E(TO)), &->is_caravan());
  friends = FILTER_LIVE(friends);
  friends = friends - ({TO});
  for(int i = 0; i < sizeof(friends); ++i)
  {
    friends[i]->help_friend(enemy, TO);
  }
  if(query_attack() == enemy)
	return;
   if(type)
  {
    command("shout Bandits! Guards! Alarm!");
  }
  else
  {
    command("say You gonna pay for this scum!");
  }
}

/* overloaded in inherited methods. */
public void help_friend(object enemy, object victim)
{
}

public string query_colour()
{
  return colour;
}

public void set_colour(string new_colour)
{
  object to_set;
  colour = new_colour;
  FIX_EUID;
  /* coachman */
  if(type == 2)
  {
    clone_object(ARMOUR + "vest")->move(TO);
    clone_object(ARMOUR + "boots")->move(TO);
    clone_object(WEAPON + "whip")->move(TO);
  }
  /* merchant */
  if(type == 1)
  {
    clone_object(ARMOUR + "robe")->move(TO);
    clone_object(ARMOUR + "shoes")->move(TO);
    clone_object(WEAPON + "dagger")->move(TO);
    to_set = clone_object(ARMOUR + "ring");
    to_set->set_colour(colour);
    to_set->move(TO);
  }
  /* guard */
  if(!type)
  {
	add_adj(colour + "-uniformed");
    to_set = clone_object(ARMOUR + "chainmail");
    to_set->set_colour(colour);
    to_set->move(TO);
    to_set = clone_object(ARMOUR + "helmet");
    to_set->set_colour(colour);
    to_set->move(TO);
    to_set = clone_object(ARMOUR + "cloak");
    to_set->set_colour(colour);
    to_set->move(TO);
    to_set = clone_object(ARMOUR + "greaves");
    to_set->set_colour(colour);
    to_set->move(TO);
    clone_object(ARMOUR + "boots")->move(TO);
    if(random(2))
    {
      clone_object(WEAPON + "broadsword")->move(TO);
      to_set = clone_object(ARMOUR + "shield");
      to_set->move(TO);
    }
    else
      clone_object(WEAPON + "partisan")->move(TO);
    set_adj(colour + " uniformed");
  }
  command("wield all");
  command("wear all");
}

public void create_caravan_member()
{

}

public int is_caravan()
{
  return 1;
}

public void remove_caravan_object()
{
  remove_object();
}

public void do_die(object killer)
{
  if(query_prop(IS_CARAVAN_COACHMAN))
    E(TO)->get_new_coachman();
  ::do_die(killer);
}
