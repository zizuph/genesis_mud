//-*-C++-*-
// file name: ~Avenir/common/dark/mon/give_get.c
// creator(s):  Boriska, Tepisch
// last update: Mar 2 1995
//              Feb 1996: Cirion - updated it with reward_quest
//		Denis, Aug'96: Updated to use /d/Avenir/inherit/intro.c
//			       for introduction.
//		Mar 2008: Zielia - removed penalties for players who 
//		haven't asked for quest or asked both NPCs. 
//      Zizuph Aug 2022 - fix for quest bug. Was using old form
//         of set_alarms that weren't properly identifying the 
//         player that objects were being received from so
//         questers were being ignored instead of rewarded.
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
#define D(x) find_player("zizuph")->catch_msg("GIVE_GET debug: " + (x))
#else
#define D(x) ;
#endif

object to = this_object();

void reject (object ob);
void remove_it (object ob);
void hand (object ob);
void accept_money(object ob);
void money_not_solved(object tp);
void xp_money(object tp);

int generate_sum();

string
give_quest_text()
{
  // Josen's story - Pro Hegemon
  if (query_alignment() >= 0 )
    {
      command ("emote glances at you as if considering something.");
      command ("sigh");
      command("say Well... you seem to be more resourceful than most I've "+
      "seen around here.");
      command("say The Hegemon showed me ancient manuscripts mentioning " + 
      "a magical artifact hidden somewhere in the tunnels. It brings great " +
      "power to whoever possesses it and the very thought of it falling into " +
      "the wrong hands is of great concern to the Hegemon of Sybarus...");
      command("shiver");
      command("say "+
      "The manuscripts say it is hidden above the depths, inside the square " +
      "of magic marked with blood. The magic ward can be dispelled only " +
      "with special stones of unknown origin.");
      command("say Danger and even death "+
      "await for anybody trying to break the wards, but what frightens me " +
      "more than death are corrupt hands already reaching out for the artifact."); 
      command("say If you are ready to risk your life trying to find it and " +
      "earn the gratitude of the Hegemon, ask me for stones.");    
      return "eyebrow";
    }
  else // Barmaley's Pro-Inquisitor story
    {
      command("say You look trustworthy enough... I think. Maybe. ");
	  command("emote looks around to see if anyone else is listening in.");
      command("say There are some old records in the Forbidden City museum "+
      "that make references to a magical artifact hidden somewhere in these "+
      "tunnels.");
      command("say This is an object of great power, and I am trying to "+
      "recover it before that fool Josen can nab it for the Hegemon. You "+
      "see, the Lord High Inquisitor thinks he can use it for the benefit "+
      "of Sybarite Society.");
      command("say He has asked me to procure it for him before the "+
      "locks it up in some vault where it won't be useful to anyone.");     
      command("say The manuscripts mention something about a 'square of "+
      "magic'... but I haven't been able to figure it out so far. I doubt "+
      "you can do better than me, but it's worth a shot.");
      command("say Maybe if you eavesdrop on that Josen-idiot you might "+
      "glean something useful from him? He shuts up anytime I'm around.\n");      
      command("emote curses colourfully.");
      command("say The Lord Inquisitor gave me a pouch with black stones "+
      "associated with the magical artifact. Some wretched soul gave them "+
      "out under torture, but I do not really care.");
      command("say If you want to help me and the Inquisitor instead of the "+
      "Hegemon and his lackey, ask me for stones.\n");
      return "grin";
    }
}

string
give_quest ()
{
  object tp = this_player();
  object stones, pouch;
  int align, sum;

  // + is for Hegemon and - is for Inquisitor
  align = query_alignment();
 
  // quest already done
  if (tp->test_bit("avenir", GROUP, BIT)) {
    tp->catch_msg("He whispers back: I do not need your help anymore.\n");
    return "shrug";
  }
  
  // player already asked for quest
  if (tp->query_prop(QUEST_VERSION) == align)
  {
    tp->catch_msg("He whispers back: You know already what to do!\n");
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

  tp->catch_msg(capitalize(short()) +
		 " produces small pouch and puts something in it.\n");
  command("close pouch");
  command("give pouch to " + tp->query_real_name());

  // expected number of stones in each row, column and diagonal.
  tp->add_prop(SQUARE_SUM, sum/3);  
  tp->add_prop(QUEST_VERSION, align);
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
  int my_align;
            
  ::enter_inv(ob, from);

  if(!ob || !from)
    return;

  if(from == environment()) { // something from the floor in my room
    set_alarm(5.0, 0.0, &hand(ob));
    return;
  }
  
  // it is not a player so dont react
  if (!interactive(from))  
    return;

  // always take money  
  if (ob->query_name() == "coin") {
    set_alarm (2.0, 0.0, &accept_money(ob));
    return;
  }
    
  // check for person completed the quest before
  if (from->test_bit("avenir", GROUP, BIT)) {
    command("say You've already helped find the artifact, you know.");
    set_alarm (2.0, 0.0, &reject(ob));
    return;
  } 

  // if not a vial reject it
  if (!ob->id("vial")) {
    set_alarm (2.0, 0.0, &reject(ob));
    return;
  }
  
  // there isn't anything I want in that vial
  if (!present(ARTIFACT_ID, ob)) {
    command("emote seems disappointed after looking inside the glass vial.");
    command("say What I want isn't in there.");	
    set_alarm (2.0, 0.0, &reject(ob));
    return;
  }	
  
  // okie... got a vial with flame inside... next:
  
  // Cannot just dest the thing inside enter_inv, it causes
  // run time error if 'give' function is not completed properly
  set_alarm (5.0, 0.0, &remove_it(ob));

  // SQUARE_SOLVED is set when player moves to ceiling.c
  // prop set means the player got the artifact on their own
  if(!from->query_prop(SQUARE_SOLVED)) {
    // somebody else gave the artifact to player
	// give them some money and let them try again
    set_alarm (4.0, 0.0, &money_not_solved(from));
    return;
  }
  
  from->remove_prop(SQUARE_SOLVED);
  set_alarm (4.0, 0.0,  &xp_money(from)); 
  return;
}  


void
remove_it (object ob) {ob->remove_object();}

private void
accept_money (object ob)
{
  command ("say My, thank you!");
  command ("say Your generosity helps my cause.");
// let people load us with money
//  ob->remove_object(); 
}

private void
reject (object ob)
{
  command ("think");
  command ("say I do not know what you expect me to do with this.");
  command("emote drops something.");
  ob->move(environment());
}

private void
hand(object ob)
{
  command("say That was not mine.");
  command("emote drops something.");
  ob->move(environment());
}

// Give the money to somebody who asked for quest but instead of completing
// it got the artifact from somebody else.
private void
money_not_solved(object tp)
{
  D("money_not_solved called for " + tp->query_real_name() + ".\n");
  
  MONEY_MAKE_GC(JUST_MONEY)->move(this_object());
  
  tp->catch_msg ("He whispers to you: A pity you didn't do the work to " +
  "get it yourself. Anyway, thank you. Here is some money for you.\n");
  command ("give coins to "+ tp->query_real_name());
  command ("drop coins"); // sanity check
// Let them try again  
//  tp->set_bit (GROUP, BIT);
//  tp->command("save");
  WRITE_LOG (" just money reward " + JUST_MONEY + " gold.\n");
  return;
}

// Give BIG_XP, BIG_MONEY
private void
xp_money (object tp)
{
  D("xp_money called\n");  

  command( query_alignment() > 0 ?
      "say Thank you, thank you! The Hegemon will be so pleased!" :
      "say Damn, you found it before I did! Well it's all the same to me--"+
      "and the Lord Inquisitor, of course.");
 
  reward_quest("Magic Square (Big)", tp, GROUP, BIT, BIG_XP);

  if (query_alignment() > 0)
  {	 // Josen is generous and backed by Hegemon's deep pockets 
     clone_object("/d/Avenir/common/obj/syb_coin")->move(this_object());
     MONEY_MAKE_GC (BIG_MONEY)->move(this_object());
	 WRITE_LOG (" full XP reward. " + BIG_XP + " XP " + BIG_MONEY +" gold.\n");
  }
  else 
  {  // Barmaley is greedy and doesn't share well
     MONEY_MAKE_GC (JUST_MONEY)->move(this_object());	  
     WRITE_LOG (" full XP reward. " + BIG_XP + " XP " + JUST_MONEY +" gold.\n");
  }
  
  command ("give coins to "+ tp->query_real_name());
  command ("drop coins"); // sanity check
  return;
}
