inherit "/std/monster";

#include "/d/Rhovanion/lib/kill_log.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"
#include "/d/Kalad/common/guilds/angmar/guild.h"

#define GUARD_FILE "/d/Rhovanion/common/npcs/shield_guard"
#define AA_ENEMY   "_AA_enemy"
#define ARM_DIR   ARMOUR_DIR+"goblin/"
#define WEP_DIR   WEAPON_DIR
#define DEFAULT_ARMOURS ({ "shield", "mail", "helm" })
#define RANDOM_WEAPONS  ({ "club" })

#define SUP_LEVEL      120
#define HIGH_LEVEL      80
#define MEDIUM_LEVEL    50

#ifndef ALIGNLOOKS
#define ALIGNLOOKS ({"cruel","angry","mean","foul","brutal","sinister", \
                     "ugly","nasty","evil","savage","dangerous","strong" })
#endif

string race;                     /* set_guard_race(string arg) */
int base_stat = 30+random(110);  /* set_guard_base_stat(int i) */
int was_armed;
int cloned_from_do_die;
int bored;

/*
 * Solamnian knight prestige
 */
int
query_knight_prestige()
{
    return (4 * base_stat);
}

void
update_guard()
{
  string prace, big = "mean", adj = ONE_OF_LIST(ALIGNLOOKS);
  int STR, DEX, CON, INT, WIS, DIS;

  if (base_stat >= MEDIUM_LEVEL) big = "big"; 
  if (base_stat >= HIGH_LEVEL) big = "massive";
  if (base_stat >= SUP_LEVEL) big = "huge";

  set_race_name(race);
  remove_adj(query_adjs());
  set_adj(({big, adj}));

  set_alignment(-(4 * base_stat));

  switch(race)
  {
    case "goblin": prace = "goblins";
     STR = (110+random(40)) * base_stat / 100;
     DEX = (80+random(40)) * base_stat / 100;
     CON = (100+random(40)) * base_stat / 100;
     INT = (65+random(40)) * base_stat / 100;
     WIS = (70+random(40)) * base_stat / 100;
     DIS = (70+random(40)) * base_stat / 100;
            break;
    case "dwarf": prace = "dwarves";
     STR = (90+random(40)) * base_stat / 100;
     DEX = (70+random(40)) * base_stat / 100;
     CON = (100+random(40)) * base_stat / 100;
     INT = (70+random(40)) * base_stat / 100;
     WIS = (70+random(40)) * base_stat / 100;
     DIS = (90+random(40)) * base_stat / 100;
            break;
    case "orc": prace = "orcs";
     STR = (120+random(40)) * base_stat / 100;
     DEX = (80+random(40)) * base_stat / 100;
     CON = (100+random(40)) * base_stat / 100;
     INT = (60+random(40)) * base_stat / 100;
     WIS = (70+random(40)) * base_stat / 100;
     DIS = (80+random(40)) * base_stat / 100;
            break;
    case "troll": prace = "trolls";
     STR = (130+random(40)) * base_stat / 100;
     DEX = (50+random(40)) * base_stat / 100;
     CON = (120+random(40)) * base_stat / 100;
     INT = (30+random(40)) * base_stat / 100;
     WIS = (40+random(40)) * base_stat / 100;
     DIS = (100+random(40)) * base_stat / 100;
            break;
    default: prace = race+"s";
     STR = (80+random(40)) * base_stat / 100;
     DEX = (80+random(40)) * base_stat / 100;
     CON = (80+random(40)) * base_stat / 100;
     INT = (80+random(40)) * base_stat / 100;
     WIS = (80+random(40)) * base_stat / 100;
     DIS = (80+random(40)) * base_stat / 100;
            break;
  }
  set_stats(({ STR, DEX, CON, INT, WIS, DIS}));

  set_skill(SS_WEP_CLUB,     MIN(90, STR));
  set_skill(SS_SHIELD,       100);
  set_skill(SS_SMASH,        100);
  set_skill(SS_DEFENCE,      MIN(80,  DEX));
  set_skill(SS_PARRY,        MIN(50,  WIS));
  set_skill(SS_BLIND_COMBAT, MIN(60,  INT));
  set_skill(SS_AWARENESS,    MIN(75,  WIS));

  set_pname(prace);
  refresh_living();
}

/*
 *  these two functions are here for modifying 
 *  to be called before arm_me()
 */
void set_guard_race(string arg)
{
  race = arg;
  update_guard(); 
}
string query_guard_race() { return race; }

void set_guard_base_stat(int i)
{
  if(was_armed && (base_stat > i)) return;
  base_stat = i;
  update_guard(); 
}

void
create_monster()
{
  set_name(({"guard","_shield_guild_guard_"}));
  switch(random(5))
  {
    case 0: race = "human"; break;
    case 1: race = "goblin"; break;
    case 2: race = "orc"; break;
    case 3: race = "troll"; break;
    case 4: race = "dwarf"; break;
  }
  update_guard();

  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(LIVE_I_SEE_DARK, 5);
  add_prop(DO_I_TELL_RUMOURS, 1);

  set_aggressive(1);

  set_alarm(0.0, 0.0, "shad_soul");
  set_alarm(5.0, 0.0, "forgot_arm_me");

  set_cact_time(1);
  add_cact("@@do_cact@@");

  trig_new("'You' 'feel' 'relaxed' %s", "do_smash");
  trig_new("'You' 'drop' 'a' %s", "get_wield");

  set_alarm(itof(300+random(500)), 0.0, "go_away");
}

void
shad_soul()  /* this NPC will be proper member of the guild */
{
  mixed sh = "/d/Rhovanion/common/shield_guild/s_c_sh_occ";
  int err;

  seteuid(geteuid());

  sh = clone_object(sh);
  if((err = sh->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME)) != 1)
  {
    "secure/master"->do_debug("destroy",sh);
    tell_room(ENV(TO), "*** shadow_me error: "+err+" ***\n");
    return;
  }
  add_cmdsoul("/d/Rhovanion/common/shield_guild/s_c_soul");
  add_cmdsoul("/d/Rhovanion/common/shield_guild/soul_cmd");
  remove_cmdsoul("/cmd/std/soul_cmd");
  load_command_souls();
}

void
forgot_arm_me()
{
  if(was_armed) return;  /*** why arm him twice???? ***/

  command("oops");
  command("say I nearly forgot my equipment!");
  set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()   /*** to be called after NPC is cloned and base_stat set ***/
{
  int i;
  string type = "_low";
  object ob;

  if(was_armed) return;  /*** why arm him twice???? ***/

  was_armed = 1;  
  seteuid(getuid());

  if(base_stat > MEDIUM_LEVEL) type = "_med";
  if(base_stat > HIGH_LEVEL) type = "_high";
  if(base_stat > SUP_LEVEL) type = "_sup";

  ob = clone_object(WEP_DIR + "club"+type);
  ob->move(TO);
  for (i = 0; i < sizeof(DEFAULT_ARMOURS); i++)
  {
     ob = clone_object(ARM_DIR + DEFAULT_ARMOURS[i] + type);
     ob->move(TO);
  }

  command("wield all");
  command("wear all");

  ob = clone_object("/std/coins");
  ob->set_coin_type("copper");
  ob->set_heap_size(random(base_stat));
  ob->move(TO);
  if(base_stat > MEDIUM_LEVEL)
  {
    ob = clone_object("/std/coins");
    ob->set_coin_type("silver");
    ob->set_heap_size(random(base_stat / 2));
    ob->move(TO);
  }
  if(base_stat > HIGH_LEVEL)
  {
    ob = clone_object("/std/coins");
    ob->set_coin_type("gold");
    ob->set_heap_size(random(base_stat / 8));
    ob->move(TO);
  }
  if(base_stat > SUP_LEVEL)
  {
    ob = clone_object("/std/coins");
    ob->set_coin_type("platinum");
    ob->set_heap_size(random(base_stat / 16));
    ob->move(TO);
  }
}

void do_cact()
{
  switch(random(9))
  {
    case 0: command("knee "+query_attack()->query_real_name()); break;
    case 1: command("kick "+query_attack()->query_real_name()); break;
    case 2: command("tackle "+query_attack()->query_real_name()); break;
    case 3: command("scream"); break;
    case 4: command("grin at "+query_attack()->query_real_name()); break;
    case 5: command("snarl at "+query_attack()->query_real_name()); break;
    case 6: command("explode at "+query_attack()->query_real_name()); break;
    case 7: command("slap the "+query_attack()->query_real_name()); break;
    case 8: command("laugh at "+query_attack()->query_real_name()); break;
    case 9: command("cower"); break;
    case 10: command("bounce"); break;
    case 11: command("say You are dead meat!!!");
             command("point at "+query_attack()->query_real_name()); break;
  }
}

/************  triger functions  ********************************/

void
do_smash(string foo)
{
  if(!query_prop(SPEC_ATTACK_IS))
    set_alarm(0.0, 0.0, "command", "smash");
}

void
get_wield(string foo)
{
   set_alarm(0.0, 0.0, "command", "get club");
   set_alarm(1.0, 0.0, "command", "wield all");
}

/*************  agresive stuff  *********************************/
void
init_attack()
{
  if(!TP->check_seen(TO)) return;
  if(TP->query_prop(AA_ENEMY))
  {
    command("kill "+TP->query_real_name());
    do_smash("foo");
    return;
  }
  set_alarm(itof(random(10)), 0.0, "slow_init_attack", TP);
  if(TP->query_race_name()=="elf" && !TP->query_wiz_level())
  {
    command("kill "+TP->query_real_name());
    do_smash("foo");
    TP->add_prop(AA_ENEMY, 1);
  }
}

void
slow_init_attack(object tp)
{
  string rrr = tp->query_race_name();

  if(!tp || !present(tp, environment())) return;

  if(tp->query_guild_member(GUILD_NAME))
  {
    if(interactive(tp) && !tp->query_incognito())
     switch(random(6))
     {
      case 0: command("bow to "+tp->query_real_name()); break;
      case 1: command("greet "+tp->query_real_name()); break;
      case 2: command("say Hello "+tp->query_name()+"!"); break;
      case 3: command("say going to plunder some village?");
              command("poke "+tp->query_real_name()); break;
      case 4: command("hug "+tp->query_real_name()); break;
      case 5: command("squeeze "+tp->query_real_name()); break;
     }
    return;
  }

  if (rrr == "elf")
  {
    switch(random(6))
    {
      case 0: command("say I hate elves! Lets kill this one!");
              command("point at "+tp->query_real_name()); break;
      case 1: command("say Another elf will perish under my club!");
              command("grin at "+tp->query_real_name()); break;
      case 2: command("say Another elf - another death!");
              command("bounce"); break;
      case 3: command("snarl at elves"); break;
      case 4: command("knee "+tp->query_real_name()); break;
      case 5: command("kick "+tp->query_real_name()); break;
    }
    if(query_attack() || tp->query_wiz_level()) return; 
    command("kill "+tp->query_real_name());
    do_smash("foo");
    tp->add_prop(AA_ENEMY, 1);
    return;
  }
  if((rrr == "hobbit") || (rrr == "gnome"))
  {
    switch(random(6))
    {
      case 0: command("say Look at this tiny little thing!");
              command("point at "+tp->query_real_name());
              break;
      case 1: command("say What is this? A "+rrr+" here???");
              command("peer at "+tp->query_real_name());
              break;
      case 2: command("say A "+rrr+"!");
              command("laugh");
              break;
      case 3: command("laugh at "+tp->query_real_name());
              break;
      case 4: command("say What a nice little toy!");
              command("tickle "+tp->query_real_name());
              break;
      case 5: command("say Lets scare this little "+rrr+"!");
              command("scream");
              command("grin at "+tp->query_real_name());
              command("snarl at "+tp->query_real_name());
              command("laugh");
              break;
    }
  }
  if((tp->query_guild_style_occ() == "ranger") &&
     ((random(100) < tp->query_stat(SS_OCCUP)) ||
      present("ranger_guild_object", tp)->query_worn()))
  {
    switch(random(5))
    {
      case 0: command("hmm");
              command("say This one looks like a ranger!");
              command("point at "+tp->query_real_name());
              break;
      case 1: command("peer at "+tp->query_real_name());
              command("say Yes! This is a ranger!");
              break;
      case 2: command("say I hate rangers!");
              command("snarl at "+tp->query_real_name());
              break;
      case 3: command("ponder "+tp->query_real_name());
              break;
      case 4: command("say Now I have chance to repay some...");
              command("grin at "+tp->query_real_name());
              break;
    }
    if(query_attack() || tp->query_wiz_level()) return; 
    command("kill "+tp->query_real_name());
    do_smash("foo");
    tp->add_prop(AA_ENEMY, 1);
    return;
  }
  if(rrr == "goblin")
  {
    switch(random(6))
    {
      case 0: command("peer at "+tp->query_real_name());
              command("say Goblin and not in our army?");
              command("confused");
              break;
      case 1: command("say Don't you want to be one of us?");
              command("peer at "+tp->query_real_name());
              break;
      case 2: command("smile at "+tp->query_real_name());
              break;
      case 3: command("tickle "+tp->query_real_name());
              break;
      case 4: command("say Want to see how bad we are???");
              command("scream");
              command("poke "+tp->query_real_name());
              break;
      case 5: command("hug "+tp->query_real_name());
              command("say Come and join us!");
              break;
    }
  }
}

/*********  team stuff - they should help eachother  ****************/
void
call_for_help(object ob)
{
  object *arr = FILTER_LIVE(all_inventory(environment()));
  int i;

  ob->add_prop(AA_ENEMY, 1);
  do_smash("foo");
  for (i = 0; i < sizeof(arr); i++)
    if((member_array("_shield_guild_guard_", arr[i]->query_names()) != -1) && 
       (arr[i] != TO))
      arr[i]->notify_ob_attacked_me(ob);
}

void 
attacked_by(object ob)
{
  ::attacked_by(ob);
  call_for_help(ob); /* naturally we call for help when attacked */
  set_alarm(7.0, 0.0, "second_life", ob);
  set_alarm(13.0, 0.0, "second_life", ob);
  set_alarm(24.0, 0.0, "second_life", ob);
}

void
attack_object(object ob)
{
  ::attack_object(ob);
  call_for_help(ob);  /* well, we call for help even when we attack! */
}

int
special_attack(object ob)
{
  if(!random(5)) call_for_help(ob); 
  /* sometimes we call for help even during fight */
  return 0;
}

void
notify_ob_attacked_me(object ob)
{
    if(query_attack()) return;
    set_alarm(itof(5 + random(10)), 0.0, "help_friend", ob);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        if(random(2)) command("grin at " + ob->query_real_name());
        command("kill " + ob->query_real_name());
    }
}

/*****************   nasty do_die     ****************************/

void
was_cloned_from_do_die()
{
    cloned_from_do_die = 1;
}

int
second_life(object killer)
{
    object ob1, ob2, *arr = FILTER_LIVE(all_inventory(environment()));
    int i, n = 0;

    for (i = 0; i < sizeof(arr); i++)
	if (arr[i]->id("_shield_guild_guard_"))
	    n++;

    if (n < 5)
    {
	ob1 = clone_object(GUARD_FILE);
	ob1->set_guard_base_stat(base_stat+10+random(10));
	ob1->was_cloned_from_do_die();
	ob1->arm_me();
	ob1->move(ENV(TO));
	tell_room(ENV(TO), (ob1->query_guard_race() == "orc" ? "An " : "A ")+
		  ob1->query_guard_race()+" arrives attracted by the noise.\n");
	ob1->get_all();
	ob1->command("kill "+killer->query_real_name());
    }
    if (ob1 && !random(4))
    {
        ob2 = clone_object(GUARD_FILE);
	ob2->set_guard_base_stat(base_stat+10+random(10));
	ob2->was_cloned_from_do_die();
	ob2->arm_me();
	ob2->move(ENV(TO));
	tell_room(ENV(TO), (ob2->query_guard_race() == "orc" ? "An " : "A ")+
		  ob2->query_guard_race()+" arrives following the "+
		  ob1->query_guard_race()+".\n");
	ob2->get_all();
	ob2->command("kill "+killer->query_real_name());
    }
    return 0;
}

void
get_all()
{
  set_alarm(1.0, 0.0, "command", "get all from corpse");
  set_alarm(2.0, 0.0, "command", "get coins");
  set_alarm(3.0, 0.0, "command", "get weapons");
  set_alarm(4.0, 0.0, "command", "get armours");
}

void
go_away()
{
  if(cloned_from_do_die && !query_attack())
  {
    if(!bored)
    {
      bored = 1;
      command("yawn");
      command("say Will there be any action of should I rather go sleep?");
      command("grin all");      
      set_alarm(itof(60+random(120)), 0.0, "go_away");
      return;
    }
    command("yawn");
    command("say This is boring!!!");
    command("say There is no real fight going on here!");
    command("say Better go and take a nap...");
    command("wave lazily");
    command("emote leaves back where he has come from.");
    remove_object();
    return;
  }
  bored = 0;
  set_alarm(itof(300+random(1000)), 0.0, "go_away");
}

/******************************************************************/

