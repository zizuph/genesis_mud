//-*-C++-*-
// file name: ~Avenir/common/dark/mon/give_get.c
// creator(s):  Boriska, Tepisch
// last update: Mar 2 1995
//              Feb 1996: Cirion - updated it with reward_quest
//		Denis, Aug'96: Updated to use /d/Avenir/inherit/intro.c
//			       for introduction.
//		Mar 2008: Zielia - removed penalties for players who 
//		haven't asked for quest or asked both NPCs. 
// purpose: inheritable for archaelogist and rogue NPCs, part of
//          magic square quest.
//          This code gives out the quest and rewards.
// note:
// bug(s):
// to-do:     

inherit "/std/monster";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/intro";

#include <money.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Avenir/include/magic_square.h"

#undef DEBUG
#ifdef DEBUG
#define D(x) find_player("boriska")->catch_msg("GIVE_GET debug: " + (x))
#else
#define D(x) ;
#endif

object to = this_object();

void reject (object ob);
int generate_sum();

string
give_quest_text()
{
  object tp = this_player();
  
  if (query_alignment() >= 0 )
    {
      command ("emote glances at you considering something.");
      command ("sigh");
      say(QCTNAME(to) + " starts whispering.\n");
      tp->catch_msg (
     "Well... you seem to be as suitable as anybody else...\n" +
     "Ancient manuscripts in the City museum mention a mysterious\n" +
     "magical artifact hidden somewhere in the tunnels. It brings great\n" +
     "power to whoever possesses it, the very thought of it falling into\n" +
     "the wrong hands makes me shiver...\n");

      command("shiver");

      tp->catch_msg (
    "The manuscripts say it is hidden above the depth, inside the square\n" +
    "of magic marked with blood. The magic ward can be dispelled only\n" +
    "with special kind of stones of foreign origin. Danger and even death\n"+
    "wait for anybody trying to break the wards, but what frightens me\n" +
    "more than death are evil hands already reaching out for the artifact.\n"+ 
    "If you are ready to risk your life trying to find it and glorify \n" +
    "your name, ask me for stones.\n");
      
      return "eyebrow";
    }
  else // evil story
    {
      command ("emote coughs clearing his throat and starts whispering.");
      
      tp->catch_msg(
"You look trustworthy enough...I think.\n" + 
"There are some old records in the Forbidden City museum that make\n" +
"references to a magical artifact hidden somewhere in the tunnels.\n" +
"This is an object of great power, and I am trying to recover it before\n"+
"that fool Josen can nab it.  You see, the Lord High Inquisitor thinks he\n"+
"can use it for the benefit of the Society.  And that fool Commissioner\n"+
"probably wants to lock it up in some vault... where it won't do anyone\n"+
"any good at all!\n");
      
      command("emote mutters something under breath.");
      command("say Hey! Are you listening to me?!");
      
      tp->catch_msg(
"The manuscripts mention something about a 'square of magic'... but I\n" +
"haven't been able to figure it out so far. I doubt you can do better\n"+
"than me, but it's worth a shot. Maybe if you eavesdrop on that\n"+
"Josen-idiot you might glean something useful from him?  He's such\n"+
"a goodie-goodie he shuts up anytime I'm around.\n");
      
      command("emote curses violently.");

      tp->catch_msg(
"On my way here I have managed to acquire something from Lord Inquisitor's\n"+
"house. It is a pouch with strange stones which have to do something\n"+
"with that magic... Some wretched soul gave them out under torture, but\n"+
"I do not really care, there are matters more important than pitiful\n"+
"life of a commoner.\n" +
"If you want to help me instead of that self-righteous Commissioner\n" +
"and his flukey, ask me for stones.\n");
      
      return "grin";
    }
}

string
give_quest ()
{
  object tp = this_player();
  object stones,pouch;
  int align, sum;
  string align_descr;

  align = query_alignment();

  if (tp->test_bit("avenir", GROUP, BIT)) {
    tp->catch_msg( "I do not need your help anymore.\n");
    return "shrug";
  }
  
  // player already asked for quest
  if (tp->query_prop(QUEST_VERSION) == align) {
    tp->catch_msg ("You know already what to do!\n");
    return "wink";
  }
  
  pouch = clone_object (POUCH);
  pouch->set_color (align > 0 ? "white" : "black");

  stones = clone_object(QUEST_ITEM);
  stones->set_color (align > 0 ? "white" : "black");
  
  // Set solvable number here
  sum = generate_sum();
  stones->set_heap_size(sum);
  stones->set_quest_id(tp->query_real_name(), align);

  stones->move(pouch);
  pouch->move(to);

  tp->catch_msg(query_name() +
		 " produces small pouch and puts something in it.\n");
  command("close pouch");
  command("give pouch to " + tp->query_real_name());

  // expected number of stones in each row, column and diagonal.
  tp->add_prop(SQUARE_SUM, sum/3);  
  tp->add_prop(QUEST_VERSION, align);

  align_descr = align > 0 ? " good" : " evil";
  
  WRITE_LOG(align_descr + " accepted.\n");
  
  return align > 0 ? "smile hopefully" : "emote watches you suspiciously.";
}

// Generates number of stones that can be arranged in magic square 3x3
// Classic magic square uses integers between 1 and 9.
// Here we use 9 integers with constant difference between them
// (arithmetical progression).

int
generate_sum() { return 9*(random(START_MAX)+1 + 4*(random(INCR_MAX)+1)); }
  
// catch items given
void
enter_inv (object ob, object from)
{
  int ver;  // alignment version of quest given to player
  int my_align;
  int player_align;
  
  ::enter_inv(ob, from);

  if(!ob || !from)
    return;

  if(from == environment()) { // something from the floor in my room
    set_alarm(5.0, 0.0, "hand", ob);
    return;
  }
  
  if (!interactive(from))  // it is not a player whi gives us something
    return;
  
  if (ob->query_name() == "coin") {
    set_alarm (5.0, 0.0, "accept_money", ob);
    return;
  }
  
  // check for vial with flame inside 
  if (!ob->id(VIAL_ID) || !present (ARTIFACT_ID, ob)) {
    set_alarm (5.0, 0.0, "reject", ob);
    return;
  }
  
  // check for person completed the quest before
  if (from->test_bit("avenir", GROUP, BIT)) {
    set_alarm (5.0, 0.0, "reject", ob);
    return;
  } 
  
  // okie... got vial with flame inside
  // Three possibilities to check:
  // - player asked for quest before and alignment matches
  // - player asked for quest before and alignment is opposite
  // - player did not ask for quest (or did not complete it on
  //   his(her) own.

  // Cannot just dest the thing inside enter_inv, it causes
  // run time error if 'give' function is not completed properly
  set_alarm (2.0, 0.0, "remove_it", ob);

  // SQURE_SOLVED is set in pillar.c when player moves to ceiling.c
  // prop set means the player got up there on his own
  if(!from->query_prop(SQUARE_SOLVED)) {
    // somebody else gave the artifact to player
    set_alarm (5.0, 0.0, "money_not_solved", from);
    return;
  }
  from->remove_prop(SQUARE_SOLVED);
  my_align = query_alignment();
  player_align = from->query_alignment();
  
  if (player_align*my_align > 0 || ABS(player_align) < 100) {
    // player alignment matches npc alignment (or neutral player)
    set_alarm (5.0, 0.0,  "xp_money", from);  // big XP, low money
    return;
  }  

  if (player_align*ver < 0 ) {
    // player alignment doesn't match npc alignment	  
    set_alarm (5.0, 0.0, "money_xp", from);   // low XP, big money
    return;
  }
}

void
remove_it (object ob) {ob->remove_object();}

private void
accept_money (object ob)
{
  command ("say My, thank you!");
  command ("wink");
  
// let people load us with money
//  ob->remove_object(); 
}

private void
reject (object ob)
{
  command ("think");
  command ("say I do not know what to do with this.");
  if (ob->short())
    command ("drop " + ob->short());
  else {
    command("emote drops something.");
    ob->move(environment());
  }
}

private void
hand(object ob)
{
  command("say I do not need anyting that is thrown on the ground like that.");
  if (ob->short())
    command ("drop " + ob->short());
  else {
    command("emote drops something.");
    ob->move(environment());
  }
}

// Give the money to somebody who asked for quest but instead of completing
// it got the artifact from somebody else.
private void
money_not_solved(object tp)
{
  D("money_not_solved called for " + tp->query_real_name() + ".\n");
  
  MONEY_MAKE_GC(JUST_MONEY)->move(this_object());
  
  tp->catch_msg ("You have not accomplished it on your own...\n" +
		 "Anyway, thank you. Here is some money for you.\n");
  command ("drop coins");
  tp->set_bit (GROUP, BIT);
  tp->command("save");
  WRITE_LOG (" money reward " + JUST_MONEY + " gold.\n");
  return;
}

// Give BIG_XP, LOW_MONEY
private void
xp_money (object tp)
{
  D("xp_money called\n");  

  command( query_alignment() > 0 ?
      "say Thank you! You made my day!" :
      "say Damn, you've found it before me!" );
  
  reward_quest("Magic Square (Big)", tp, GROUP, BIT, BIG_XP);
  
  MONEY_MAKE_GC (LOW_MONEY)->move(this_object());
  command ("drop coins");
  WRITE_LOG (" full XP reward. " + BIG_XP + " XP " + LOW_MONEY+" gold.\n");
  return;
}

// Big money, low XP, alignment penalty
void
money_xp (object tp)
{
  int align = tp->query_alignment();

  D("money_xp called\n");

// So either way, you get an alignment 'penalty'
  if(align > 0)
     reward_quest("Magic Square (Low)", tp, GROUP, BIT, LOW_XP,
		  -ALIGN_PENALTY);  
  else
     reward_quest("Magic Square (Low)", tp, GROUP, BIT, LOW_XP,
		  ALIGN_PENALTY);  

  command( query_alignment() > 0 ?
      "say You wicked evil thing! How did you dare to approach me?!?" :
      "say Hehe, goodie... I fooled you..." );

  command( query_alignment() > 0 ?
      "say Get these damned gold coins and never show up here again!" :
      "say I will receive better reward for that, here's your share." );
  
  MONEY_MAKE_GC (BIG_MONEY)->move(this_object());
  command("drop coins");
  WRITE_LOG (" low XP reward. " + LOW_XP + " XP " + BIG_MONEY+" gold.\n");
  return;
}
