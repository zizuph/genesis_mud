#include "/d/Emerald/defs.h"

inherit EMERALD_MONSTER;
inherit "/d/Genesis/lib/intro";

#include "../default.h"
#include <money.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define DEBUG_WHO find_player("shiva")
#define DEBUG_ON
#undef  DEBUG_ON
#include DEBUGFILE

int stun_and_strike(object enemy);
int trip(object enemy);

void create_emerald_monster()
{
  set_living_name("lilac");
  set_name(({ "lilac", "royal_guardian_lilac" }));
  set_race_name("elf");
  set_adj(({ "mysterious", "pallid" }));
  
  set_title("Royal Guardian of Emerald");

  set_alignment(400);
  
  set_gender(G_FEMALE);

  set_stats(({ 180, 300, 150, 200, 100, 250 }));
  
  set_all_hitloc_unarmed(60);
  set_all_attack_unarmed(70, 70);

  set_skill(SS_UNARM_COMBAT, 100);
  set_skill(SS_BLIND_COMBAT, 100);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_AWARENESS, 100);

  add_prop(LIVE_I_QUICKNESS, 100); // double attack rate
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NON_REMEMBER, 1);

  set_appearance_offset(-45); // good looking :)

  add_equipment(({ ARM_DIR + "fire_gloves", ARM_DIR + "emerald_ring", }));

  log_my_deaths(TELBERIN_DIR + "log/lilac_deaths.log");
  log_my_kills(TELBERIN_DIR + "log/lilac_kills.log");

#ifndef NO_WANDER
  set_monster_home(TELBERIN_DIR + "telberin_npc_handler");
  set_restrain_path(TELBERIN_DIR); 
  set_random_move(7); 
#endif

  add_act("@@do_something@@");
  add_cact("@@do_something_in_combat@@");
  set_act_time(8);
  set_cact_time(10);

  setuid();
  seteuid(getuid());

  MONEY_ADD(this_object(), 800 + random(1000));

  set_special_attack_percent(10);
  add_special_attack(stun_and_strike, 15, "stun and strike");
  add_special_attack(trip, 85, "trip");
}

string do_something()
{
  object *who = FILTER_LIVE(all_inventory(environment()));
  object *bad = ({ });
  string target;
  int i = 0;
  
  while (i < sizeof(who))
  {
    if (IS_WIZ(who[i]))
    {
      who = exclude_array(who, i, i);
      continue;
    }
 
    if ((who[i]->query_alignment() < -100) ||
        who[i]->query_prop(LIVE_I_UNDEAD))
    {
      bad += ({ who[i] });
    }

    i++;
  }

  if (!sizeof(who))
  {
    return "";
  }
  if (sizeof(bad))
  {
    target = bad[random(sizeof(bad))]->query_real_name();
    return ({
              "peer " + target,
              "elcurl " + target,
           })[random(2)];
  }

  target = who[random(sizeof(who))]->query_real_name();
  
  return ({
            "smile " + target,
            "pat " + target,
            "sigh contentedly",  
         })[random(3)];
}

// perform some random actions when in combat
string do_something_in_combat()
{
  return ({
            "say Flee now, and you might be spared.\n",
            "say You were foolish to have forced my hand.\n",
         })[random(2)];
}

int query_knight_prestige() { return -3; }

int stun_and_strike(object enemy)
{
  object *enemies_present = query_enemy(-1) & 
      FILTER_LIVE(all_inventory(environment()));

  if (command("stun enemies"))
  {   
    enemies_present->hit_me(800, W_BLUDGEON, this_object(), W_RIGHT);
    enemies_present->catch_msg(QCTNAME(this_object()) + 
        " strikes you while you are stunned!\n");
  }

  return 1;
}

int trip(object enemy)
{
  int hitsuc;

  if ((hitsuc = query_combat_object()->cb_tohit(-1, 120, enemy)) > 0)
  {
    enemy->catch_msg(query_The_name(enemy) + " does a leg-sweep, sending " +
        "you crashing to the ground.\n");
    tell_watcher(QCTNAME(this_object()) + " does a leg-sweep on " +
        QTNAME(enemy) + ", sending " + POS(enemy) + " crashing to the " +
        "ground.\n", enemy);
    enemy->add_stun();
    set_alarm(5.0, 0.0, &enemy->remove_stun());
  }
  else
  {
    // I missed
  }

  return 1;
}

void toss_weapon(object wep, object where, string direction)
{
  object owner;

  if (!wep || !where)
  {
    return;
  }

  owner = environment(wep);

  tell_watcher(QCTNAME(this_object()) + " grabs " + QTNAME(owner) + "'s " +
      wep->short() + " and tosses it " + direction + ".\n", owner);
  owner->catch_msg(query_The_name(owner) + " grabs your " + wep->short() +
      " and tosses it " + direction + "!\n");
  wep->move(where);
}

void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
  int ran;
  string ran_room, *rooms, direction;
  object target_room, wep;

  ::cr_got_hit(hid, ph, att, aid, dt, dam);

  if ((ph < 0) && random(3) && (wep = att->query_weapon(aid)) &&
      (att->resolve_task(TASK_DIFFICULT, ({ TS_DEX, TS_STR, 
      SS_WEP_FIRST + wep->query_wt() - W_FIRST }), this_object(), 
      ({ TS_DEX, TS_STR, SS_UNARM_COMBAT })) <= 0))

  {
    rooms = environment()->query_exit_rooms();
    while (sizeof(rooms))
    {
      ran = random(sizeof(rooms));
      ran_room = rooms[ran];
      if (!(target_room = find_object(ran_room)))
      {
        catch(call_other(target_room, "??"));
        if (!(target_room = find_object(ran_room)))
        {
          rooms = exclude_array(rooms, ran, ran);
          continue;
        }
      }
  
      break;
    }

    if (!target_room)
    {
      return;
    }

    DEBUG(ran_room);

    direction = environment()->query_exit_cmds()[ran];
    set_alarm(0.2, 0.0, &toss_weapon(wep, target_room, direction));
  }

  // throw
}

