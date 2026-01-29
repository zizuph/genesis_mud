//-*-C++-*-
// Infidel guard
// creator(s): Ilyian, October 1995
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/inherit/helper";

#include "../infidel.h"
#include <ss_types.h>

int do_this_check();
void do_slay(object victim);
void do_greet(object who);

void
create_monster()
{
  string *randadjl = ({"tall", "large", "swarthy", "blue-eyed",
		       "short", "long-haired", "slender",
		       "long-legged", "blonde-haired",
		       "heavyset"});
  
  string *randadjs = ({"worried", "jovial", "grim", "sad", "calm",
		       "unhappy", "nervous", "tired"});
  
  ::create_monster();
  set_name("infidel");
  add_name("guard");
  add_name("avenir_infidel_id"); 
  set_race_name("human");
  set_gender(G_MALE);
  set_adj(randadjl[random(sizeof(randadjl))]);
  add_adj(randadjs[random(sizeof(randadjs))]);

  set_long("This grim man stands tall and strong, with a " 
           +"rebellious and proud bearing.\n");
  set_stats(({ 80+random(20), 90+random(20), 80+random(30),
	       50+random(10), 50+random(10), 80+random(30) }));

  set_knight_prestige(-1); 

  set_skill(SS_WEP_CLUB, 60 + random (30));
  set_skill(SS_DEFENCE, 60 + random (30));
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_WEP_AXE, 60 + random (30) );
  set_skill(SS_WEP_POLEARM, 60 + random (30) );
  set_skill(SS_BLIND_COMBAT, 50 );
  
  NEVERKNOWN;
  
    remove_leftover("scalp");
    add_leftover(OBJ +"scalp", "scalp", 1, 0, 0, 1);

  set_act_time(5);
  add_act("say I'm tired of skulkung around here, waiting "
	  +"all the time.");
  add_act("whisper infidel Who are these people?");
  add_act("nod brief infidel");
  add_act("peer hobbit");
  add_act("peer goblin");
  add_act("peer elf");
  add_act("say We will overthrow those wretched "
	  +"Faithful soon!");
  
  set_aggressive(1);  // Using my special aggressive...
  set_cact_time(9);
  add_cact("emote curses loudly."); 
  add_cact("shout You will pay for this with your life!");
  add_cact("shout Spawn of the Faithful! Die!");
  add_cact("glare enemy");
  
  set_helper_friends( ({}) );
  set_helper_actions(({"shout Intruders! Help me!",
		       "shout Hold strong! I'm coming!",
		       "say Die Faithful scum!"}));
  seteuid(getuid());
}

void
arm_me()
{
  switch(random(3))
    {
    case 0: clone_object (OBJ+"hammer")->move(TO);
      break;
    case 1: clone_object (OBJ+"polearm")->move(TO);
      break;
    default: clone_object (OBJ+"axe")->move(TO);
      break;
    }
  command ("wield all");

  clone_object(OBJ+"armour")->move(TO);
  clone_object(OBJ+"boots")->move(TO);
  clone_object(OBJ+"helm")->move(TO);

  command("wear all");
  command("wimpy at death's door");
}



/* Shoul I attack this guy? */
int
do_this_check()
{
  if(query_attack())
    { return 0; }  // always concentrate on fighting

  if (TP->query_npc())
    { return 0; } // don't kill each other

  if (TP->query_prop("_live_i_killed_infidel_guard"))
    { 
      set_alarm(itof(random(8)), 0.0,
		&command("shout Here's the murdering Faithful!"));
      return 1; 
    }
  
  if (TP->query_prop("_live_i_attacked_infidel_guard"))
    { 
      set_alarm(itof(random(8)), 0.0,
		&command("shout I found one of the Intruders!"));
      return 1; 
    }

  set_alarm(itof(random(5) + 3), 0.0, &do_greet(TP));
  return 0;
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
  int i = check_call(monster_aggressive);
  if ((!i) || (this_player()->query_npc()))
    return;
  if (do_this_check() &&
      (monster_attack_chance == 0) || (random(100) < monster_attack_chance))
    set_alarm(itof(random(4)), 0.0, &do_slay(TP));
}

/*
 * Ok, I'll attack, but only if I'm not busy killing
 * someone else right now.
 */
void
do_slay(object victim)
{
  if(query_attack())
    { return; }  // always concentrate on fighting

  command("shout You will pay for your crimes, Faithful "
          +capitalize(victim->query_race_name())+"!");
  command("kill "+victim->query_real_name());
}

/*
 * Greet strangers
 */
void
do_greet(object who)
{
  string *ways = ({"confident","corag","caut","dubiou","inquir",
                   "thought"});
  string *emots = ({"bow","peer","eyebrow","glare","nod"});
  string *says = ({"Hello stranger...", "What are you doing here?",
                   "Don't hang around here too long",
                   "How did you get in here?",
                   "You better leave. This is no place for you.",
                   "Hmm.... better tell Nochipa that we have company.",
                   "Don't tell anyone you came here.",
                   "Things get a little rough around here. "
		     +"You better leave."});
  
  if(random(2))
    command(emots[random(sizeof(emots))]+" "
	    +ways[random(sizeof(ways))]+" "+TP->query_real_name());
  if(random(2))
    command("say "+says[random(sizeof(says))]);
  return;
}

void
attacked_by(object who)
{
  who->add_prop("_live_i_attacked_infidel_guard",1);
  if(random(2) && !query_attack())  
    set_alarm(3.0, 0.0, &command("shout Intruder alert! "
				 +"They have found us!"));
  ::attacked_by(who);
}

void
do_die(object killer)
{
  command("emote falls dead to the floor.");
  killer->add_prop("_live_i_killed_infidel_guard",1);
  ::do_die(killer);
}

