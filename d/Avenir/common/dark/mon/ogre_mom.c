// -*-C++-*- is the best mode to edit LPC in emacs
// file name: ~Avenir/common/dark/mon/ogre_mom.c
// creator(s):  Boriska Nov 1994 
// last update: Jan 28 1995 
//              Feb 1996, Cirion: redid quest reward.
//
// purpose:     Inhabitant of dark/l4 tunnels. Quest NPC, rewards for
//              rat hunting quest. See ~Avenir/QUESTS/rat_hunting.doc
// note:
// bug(s):
// to-do:     

#include <const.h>
#include <money.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/rat_trap.h"

inherit "/std/monster";
inherit "/d/Avenir/inherit/insult";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/givetask";

static object to = this_object();

private void accept(object rat);
private void reject(object obj);
private void manners(object obj);
string give_task();

void
create_monster()
{
  
  if (!IS_CLONE)
    return;
  
  set_name ("ogre");
  add_name ("mom");
  set_short ("stout ogre mom");

  set_race_name( "ogre mom");
  add_adj ("stout");
  set_long ("The stout ogre mom stares back at you while cooking something\n" +
	    "or somebody...\n");

  set_stats ( ({70,70,90,40,40,70}) );

  set_chat_time (5);
  add_chat ("You" + insult());
  add_chat ("Bring me rat alive, I will reward you.");
  add_chat ("Rats! I am tired!");
  add_chat ("Bring me rat alive, I will reward you.");
  add_chat ("There is nothing left to eat here, we have to eat rats!");
  add_chat ("Bring me rat alive, I will reward you.");

  set_cchat_time (1);
  add_cchat ("Dinner time!");
  add_cchat ("My pot is waiting for you!");

  add_ask(({"task", "job", "for task", "for job", "help", "quest", "rats", "rat"}),
	&give_task());

  set_skill (SS_DEFENSE, 50);
  set_skill (SS_PARRY, 30);
  set_skill (SS_WEP_KNIFE, 50);
  set_skill (SS_WEP_CLUB, 50);
  set_skill (SS_2H_COMBAT, 70);

  set_gender (G_FEMALE);
  set_alignment (0);

  remove_prop (NPC_M_NO_ACCEPT_GIVE);
}

void
equip_me ()
{
  seteuid(getuid());
  clone_object( OBJ + "o_fork")->move(to);
  clone_object( OBJ + "o_spoon")->move(to);
  clone_object( OBJ + "o_apron")->move(to);
  MONEY_MAKE_CC(300)->move(to);
  command ("wear all");
  command ("wield all");
}

void
enter_inv (object ob, object from)
{
  ::enter_inv (ob, from);

  if (!from || !ob)
	 return;

  if (from == environment()) // something from the floor in my room
	 {
		set_alarm (2.0, 0.0, "manners", ob);
		return;
	 }

  if (!interactive(from))
	 return;

  if (ob->id(RAT_ID))
	 set_alarm (2.0, 0.0, "accept", ob);
  else
	 set_alarm (2.0, 0.0, "reject", ob);
}

private void
manners (object obj)
{
  command ("say Nobody knows nowdays what the good manners are.");
  command ("grumble");
  command ("say Would you hand it to me like polite people do?");
  command ("drop " + obj->short());
}

private void
reject (object obj)
{
  command ("say What I am supposed to do with that?");
  command ("think");
  command ("drop " + obj->short());
}

private void
accept (object rat)
{
  object tp = this_player();

  if (rat->query_prop(RAT_CAUGHT_BY) != tp->query_real_name())
	 {
		command ("say You have not caught this rat on your own, darling.");
		rat->remove_object();
		return;
	 }

  if (!rat->adjectiv_id("fat") && !rat->adjectiv_id("plump"))
	 {
		command ("say Who do you think I am?");
		command ("say I do not consume " + rat->query_adj() +
			 " rats.");
		command ("drop rat");
		command ("spit");
		return;
	 }

  // ok, we've got fat or plump rat caught by this player
  command ("say Thank you! What a delicious " + rat->query_adj() +
		" rat you have brought to me!");
  if (!tp->test_bit("Avenir", GROUP, BIT))
	 {
		reward_quest("Rat Catching", tp, GROUP, BIT, XP, 0, 15);
			 // Small prestige award for being helpful...

		WRITE_LOG(tp, "completed the quest.\n");
	 }
  command ("emote drops the rat in her cooking pot!!!");
  rat->remove_object();
}

string give_task()
{
	if (this_player()->test_bit("Avenir", GROUP, BIT))
	{
		check_group_one(this_player(), ({0, 0, 0, 0}));
		return "";
	}

	command("say Bring me rat alive, I will reward you.");
	return "";
}

