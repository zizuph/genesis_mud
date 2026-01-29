//  BEE - an angry aggressive bee
//  a swarm of these cloned when someone sticks their hand in the hive
//    in a bk_treeX.c room
//  player wearing bee keeper's suit is protected
//
//  Zima   May 18, 1998
//
//  Adapted to beekeeper suit becoming a wearable item
//  Tapakah, 07/2021
//

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <poison_types.h>
#include "/sys/stdproperties.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
#define  HP        -5
#define  FIGHT_MIN  3.0
#define  POISON_STR 5
 
//
// go_home - bee gets tired and goes home
//

void go_home ()
{
  string homerm=query_monster_home(); // set in cloning room
  object home;
  if (stringp(homerm)) home=((homerm)->query_pointer());
 
  tell_room(ENV(TO),"The honeybee quietens and flies off.\n");
  if (objectp(home))
    {
      tell_room(home,"A honeybee flies into the hive.\n");
      home->return_bee();
    }
  remove_object();
}
 
//
// create_creature
//
void
create_creature()
{
  set_adj(({"honey","angry"}));
  set_short("honeybee");
  set_pshort("honeybees in a swarm");
  set_name("bee");
  add_name("honeybee");
  set_race_name("bee");
  add_prop(BK_BEE,1); // i am a bk_bee
  add_prop(LIVE_I_NEVERKNOWN,1);
  set_long("It is a very small but very angry honeybee!\n");
  set_m_in("flies in buzzing angrily.");
  set_m_out("flies");
 
  set_gender(2); /* neuter */
  set_stats(({1,1,1,0,0,1}));
  set_skill(SS_DEFENCE, 70);                // hard to hit!
 
  set_attack_unarmed(W_IMPALE, 3, 3, W_IMPALE, 100, "stinger");
  set_hitloc_unarmed(A_BODY, 1, 100, "body");
  set_aggressive(1);
  set_attack_chance(100);
  add_prop(NPC_I_NO_FEAR,1);
  add_prop(CONT_I_WEIGHT,20);
  add_prop(CONT_I_VOLUME,20);
  set_alarm((FIGHT_MIN*60.0),0.0,&go_home());
}
 
//
// do_poison - bee stings are poison, increases fatigue
//

void
do_poison (object enemy)
{
  object poison = present("_tabor_honeybee_poison",enemy);
  if (!objectp(poison)) {
    poison = clone_object("/std/poison_effect");
    poison->move(enemy);
    poison->set_time(360);
    poison->set_interval(90);
    poison->set_strength(POISON_STR);
    poison->set_damage(({POISON_FATIGUE, 50}));
    poison->add_name("_tabor_honeybee_poison");
    poison->set_poison_type("tabor honeybee");
    poison->start_poison();
  }
  else {
    poison->set_time(360);
    poison->set_strength(((poison->query_strength())+POISON_STR));
    poison->start_poison();
  }
}
 
//
// bk_protected - is this player protected from bee stings?
//
public int bk_protected (object tp)
{
  string worn_objects = tp->show_worn();
  int res = wildmatch("*beekeepers suit*", worn_objects);
  return res;
}
 
//
// aggressive_attack - don't attack if protected
//
public void aggressive_attack(object victim)
{
  string lcname=lower_case(victim->query_name());
 
  /* go ahead and "attack", but won't sting
   */
  if (bk_protected(victim)) // if player is protected, don't attack him
    return;
  /*
   */
  if (query_follow() != lcname) // follow the victim wherever he goes!
    set_follow(lcname);
  ::aggressive_attack(victim);
}
 
//
// special_attack - special attack for honey bee
//
public int special_attack(object victim)
{
  string s;
 
  // only threatened attack 2/3 of time, or if victiem protected
  if (random(3)||bk_protected(victim))
    {
      switch(random(5))
        {
        case 0:s="A honeybee buzzes angrily around your head";    break;
        case 1:s="A honeybee flies angrily past your ear";    break;
        case 2:s="A honeybee swarms angrily in your face";   break;
        case 3:s="A honeybee dives angrily toward you then flies back";
        case 4:s="A honeybee dives, hits the back of your head and "+
            "flies off";
        }
      tell_room(ENV(TO),s+"!\n");
      return 1; // never do regular attack
    }
 
  // victim gets stung!
  victim->catch_msg("A honeybee stings you! Ouch!\n");
  tell_room(ENV(victim),QCTNAME(victim)+" is stung by a honeybee!\n",
            victim);
  victim->heal_hp(HP);
  if (victim->query_hp() <= 0)
    victim->do_die();
  do_poison(victim);
 
  return 1; // never do regular attack
}
 
//
// fly_back - go back to a bee room, closer to home
//
void
fly_back (object rm)
{
  tell_room(ENV(TO),"The honeybee flies away angrily.\n");
  move_living("M",rm);
  tell_room(rm,"A honeybee flies in and buzzes around angrily.\n");
}
 
//
// enter_env - don't go too far from home
//
void
enter_env (object to, object from)
{
  if (!(to->query_prop(BEE_ROOM))) {
    if (from->query_prop(BEE_ROOM))
      set_alarm(3.0,0.0,&fly_back(from));
    else
      set_alarm(3.0,0.0,&go_home());
  }
  ::enter_env(to,from);
}
