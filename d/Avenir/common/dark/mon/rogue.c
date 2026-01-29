// file name: ~Avenir/common/dark/mon/rogue.c
// creator(s):  Boriska Nov 1994
// last update: Feb 28 1995
//		Denis, Aug'96: Removed triggers from intro process.
// purpose:     Magic Square quest, cloned in dark/l4/n14
//
// note:        make_twins() should be called from reset_room()
//              _after_ the rogue is moved to the room. This
//              clones two twin goblin workers and causes them
//              to say things and act sometimes. These are
//              added with add_twin_chat() and add_twin_act()
// Revisions:  Lilith Dec 2021: Moved the make_twins into the 
//             equip_me() function since I'm using add_npc in 
//             the room the rogue is cloned to.
// bug(s):
// to-do:     

inherit "/d/Avenir/common/dark/mon/give_get";

#include <money.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"
// definitions for magic square quest

static object *twins = ({0,0});
void make_twins();
private void add_twin_chat(string str);
private void add_twin_act(string str);

void
create_monster ()
{
  if(!IS_CLONE)
    return;
  set_name("barmaley");
  add_name("rogue");
  set_long(
  "This gnome is quite unlike the restless, talkative gnomes you are\n" + 
  "familiar with. His face is all planes and shadows, his intent, shifting\n" +
  "eyes seem to look everywhere at once, never resting for long on\n" +  
  "any one thing. His movements are deliberate and unhurried, yet there\n" +  
  "is about him an air of urgency, of tremendous energy kept under\n" + 
  "careful control.\n" );

  add_adj (({"gaunt", "beady-eyed"}));
  set_title ("the Freelance Treasure Collector");
  set_gender (G_MALE);
  set_race_name ("gnome");
  set_stats ( ({30,50,50,40,40,40}) );
  
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_AWARENESS, 30);
  
  set_whimpy (30);
  
  set_alignment (-500);

  set_chat_time (4);
  add_chat("They will pay me a lot for that flaming thing, " +
	   "I can share with you.");
  add_chat("Damn, I'm tired looking for that bloody square of magic.");
  add_chat("Burn you.");
  add_chat("@@point@@Stop eavesdropping, you there!\nYes, yes, you!");
  add_chat("Weeks of hunting, and what do I have to show for it? Nothing!");
  add_chat("A warm bed, a willing woman, a business of my own. What a fool" +  
	   " I was to leave them.");
  add_chat("Uncle was right. Doing business with the Lord Inquisitor is " +
	   "risky in more ways than one.");
  add_chat("I will find the artifact, I will give it to Him, and then " +
	   "collect my rightful reward.");
  add_chat("If you help me, you'll find it worth your while. Gold, " +
	    "and plenty of it!" );
  add_chat("You stupid goblin! Dig here, not there!");
  
  // here twins' chats go...
  add_twin_chat("Hey, why do you pay him more than me?");
  add_twin_chat("I am stronger than you!");
  add_twin_chat("I hate it here.");
  
  set_act_time (4);
  add_act ("emote glances furtively at you.");
  add_act ("emote wrings his hands slowly and deliberately, " +
	   "cracking his knuckles.");
  add_act ("grin");
  add_act ("emote curses.");
  add_act ("smile greed");

  add_twin_act("curse");
  add_twin_act("flip");
  add_twin_act("emote tries to sneak away but is stopped by the gnome.");

  remove_prop (NPC_M_NO_ACCEPT_GIVE);
  add_ask( ({"help", "quest", "artifact", "business"}),
	  "@@give_quest_text", 1);
  add_ask ("for stones", "@@give_quest", 1);
  set_alarm(2.0, 0.0, make_twins);
}

private void
add_twin_chat(string str)
{
  add_act("@@twin_act|" + "say " + str + "@@");
}

private void
add_twin_act(string str)
{
  add_act("@@twin_act|" + str + "@@");
}

string
twin_act(string str)
{
  if (!objectp(twins[0]) || !objectp(twins[1])) // both twins are dead
    return "say Damn goblin workers never miss a chance to flee!";
  twins[0]->command(str);
  twins[1]->command(str);
  return "say Be quiet you there!";
}

string
point()
{
  command ("emote points at you with his long-nailed finger.");
  return "";
}

void
make_twins()
{
  int i;
  
  if (!environment())
    return;
  seteuid(getuid());
  tell_room(environment(),
	    "Two identical twin goblins jump in from the rocks.\n");
  for (i = 0; i < 2; i++) 
    if (!objectp(twins[i])) {
      twins[i] = clone_object(MON + "t_goblin");
      twins[i]->equip_me();
      twins[i]->move_living("M", environment());
    }
}  


void
equip_me ()
{
  object purse;
  
  seteuid(getuid());
  clone_object(OBJ + "r_cape")->move(this_object());
  clone_object(OBJ + "r_pants")->move(this_object());
  clone_object(OBJ + "r_shirt")->move(this_object());
  clone_object(OBJ + "r_cravat")->move(this_object());
  purse = clone_object(OBJ + "r_purse");
  MONEY_MAKE_GC(3)->move(purse);
  purse->add_prop(CONT_I_CLOSED, 1);
  purse->move(this_object());
  command ("wear all");

}

  
void
do_die(object ob)
{
  int i;
  
  for (i = 0; i < 2; i++)
    if (objectp(twins[i]))
      twins[i]->flee();
  ::do_die();
}




