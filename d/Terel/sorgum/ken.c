/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/action";     
inherit "/std/act/seqaction";
inherit "/std/act/domove";     
     
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

#define ARM_DIR  SORGUMDIR + "armour/"
#define WEP_DIR  SORGUMDIR + "weapon/"

/*
 * Global variables
 */

string *chats = ({
"I'll slit your throat!",
});

string *cchats = ({
"Yes!  That was almost a critical hit!  Next time you'll eat crow for sure!",
"You should have never came back!",
"Keep it up and I'LL SLIT YOUR THROAT!!!",
"I know more ways to kill you than you know ways to die!",
"I hope you brought a body bag!  You'll need it.",
});

     
create_monster()
{
    int i;
    
    set_name("Ken");
    add_name("ken");
    set_short("Ken Savage");
    set_long("A psycho with a chunky ass.  He is wearing red sweats.  One " +
	     "of his ears sticks ouit further than the other.\n");

    set_race_name("human");
    set_gender(0);

    set_all_hitloc_unarmed(35);
    set_all_attack_unarmed(20, 20);

    set_whimpy(63);
    set_act_time(7);
    set_chat_time(1);
    set_cchat_time(1);

    for (i = 0; i < sizeof(chats); i++) {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }

    for (i = 0; i < sizeof(cchats); i++) {
	add_cchat(cchats[i]);
    }

    set_spell_prop(TO);

/*     trig_new("%w 'falls' 'down' %s", "react_laugh");
     trig_new("%w 'growls.\n' %s", "react_growl"); */
     trig_new("%s 'says:' %s", "react_say");
/*     trig_new("%w 'slaps' %s", "react_slap");
     trig_new("%w 'giggles' %s", "react_giggle");
     trig_new("%w 'burps' %s", "react_burp");
     trig_new("%w 'smiles' %s", "react_smile");
     trig_new("%w 'smirks.\n' %s", "react_smirk");
     trig_new("%w 'cackles'  %s", "react_cackle");    
     trig_new("%w 'grins' %s", "react_grin");    
     trig_new("%w 'lets' 'off' 'a' 'real' %s", "react_fart");    
   trig_new("%w 'throws' %w 'head' 'back' 'and' 'cackles' 'with' 'glee!\n' %s",
	    "react_cackle");
    trig_new("%w 'drops' %s", "react_drop");
    trig_new("%s 'attacks' 'you!\n' %s","react_attacked");
    trig_new("%s 'died.\n' %s","react_death");     */

    
}
    
react_death(s,ss)
{
    if (s == "The decayed dweller") {
	command("scream");
	command("shout You killed me brother!  Now I'm gonna kill you!");
	command("get all from corpse");
    }
    return 1;
}

react_attacked(s,ss)
{
  set_alarmv(1.0, -1.0, "att",({TP}));
  return 1;

}

att(object tp)
{
    string msg;

    switch (random(10)) {
     case 0:
	msg = "You just made the biggest mistake of your life!";
	break;
     case 1:
	msg = "I didn't think you had the balls to attack me.";
	break;
     case 2:
	msg = "Now I'm goging to take your head off.";
	break;
     case 3:
	msg = "I can't believe you had the dis to attack me.";
	break;
     case 4:
	msg = "You are in truble now!";
	break;
     case 5:
	msg = "I will destroy you now!";
	break;
     case 6:
	msg = "Now I am going to crush you like the bug you are.";
	break;
     case 7:
	msg = "You are going to regret this.";
	break;
     case 8:
	msg = "I'll make you wish you were never born.";
	break;
     case 9:
	msg = "What a puny attack!  This is going to be a joke.";
	break;
    }
	

    command("shout " + msg);

    switch (random(4)) {
     case 0:
	command("kick " + tp->query_real_name());
	break;
     case 1:
	command("slap " + tp->query_real_name());
	break;
     case 2:
	command("say Your are so wimpy it makes me sick!");
	command("puke " + tp->query_real_name());
	break;
     case 3:
	command("poke " + tp->query_real_name() + " eye");
	break;
    }
  return 1;
}

int
react_drop(string who, string dummy1)
{
    command("get coins");
    command("get armours");
    command("get weapons");
    command("get all from sack");
    command("get all from backpack");
    command("say Thanks!");
}

int
react_cackle(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      set_alarmv(3.0, -1.0, "return_cackle", ({who}));
      return 1;
   }
}

void
return_cackle(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You cackle like a duck, " + obj->query_race() + ".");
      if (ran == 1)
         command("say throw your head back again, it gives me a better " +
		 "shot at your neck.");
      if (ran == 2)
         command("say You remind me of the wicked witch when you cackle " +
		 "like that.");
   }
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_smile", ({who}));
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I'll be the one smiling when you are on the " +
                 "ground dying.");
      if (ran == 1)
         command("say Look at that--- a verticle smile!");
      if (ran == 2)
         command("say smile while you can, " + obj->query_nonmet_name()+ ".");
   }
}

int
react_smirk(string who) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_smirk", ({who}));
      return 1;
   }
}

void
return_smirk(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Wipe that stupid smirk off your ugly face, " +
                 obj->query_nonmet_name() + "...");
      if (ran == 1)
         command("say What's with the stupid smirking?");
      if (ran == 2)
         command("grin at " + who);
   }
}

int
react_grin(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_grin", ({who}));
      return 1;
   }
}

void
return_grin(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say What's with that shit-eating grin, " +
                 obj->query_nonmet_name());
      if (ran == 1)
         command("grin");
      if (ran == 2)
         command("say I'll knock that grin off your face, "+
                 obj->query_race() + ".");
   }
}

int
react_burp(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_burp", ({who}));
      return 1;
   }
}

void
return_burp(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You woulnd't burp so much if you stopped eating " +
                 "dogshit.");
      if (ran == 1)
         command("say Knock it off, you burping wanker.");
      if (ran == 2)
         command("say Nice burp!  That was almost puke, eh?");
   }
}

int
react_laugh(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_laugh", ({who}));
      return 1;
   }
}

void
return_laugh(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You won't be laughing when I chop your head off!"); 
      if (ran == 1)
         command("say What the hell is so funny?");
      if (ran == 2)
         command("say What are you laughing at?");
   }
}

int
react_fart(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_fart", ({who}));
      return 1;
   }
}

void
return_fart(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(4);
      if (ran == 0)
         command("say You are a real class act, you farting wanker!");
      if (ran == 1)
         command("say Clearing your throat, eh?");
      if (ran == 2)
         tell_room(environment(), "The dweller fans the fart-cloud in your " +
                   "general direction.");
      if (ran == 3)
	  command("say Your voice has changed, but I see your breath is " +
		  "still the same!");

   }
}

int
react_giggle(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      set_alarmv(2.0, -1.0, "return_giggle", ({who}));
      return 1;
   }
}

void
return_giggle(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You giggle like a wuss!");
      if (ran == 1)
         command("say Why are giggling when I am going to kick your ass?");
      if (ran == 2)
         command("say Hey, I'll give you something to giggle about?");
   }
}

int
react_say(string who, string str)
{
   if (who) {
       who = lower_case(who);
      if (str == "twelve dollars\n" || str == "12 dollars\n")
	   set_alarmv(2.0, -1.0, "return_bill", ({who}));
      return 1;
   }
}

void
return_bill(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
         command("say AGAIN?!?.");
   }
}

int
react_slap(string who, string dummy1)
{
    if (who && (dummy1[0..3] == "you!")) {
	who = lower_case(who);
	set_alarmv(2.0, -1.0, "return_slap", ({who}));
	return 1;
    }
}

void
return_slap(string who)
{
   object obj;
   int ran;

   if (obj = present(who, environment())) {
       command("say Dont EVER slap me again you " +
	       obj->query_race() + " bastard!");
       obj->catch_msg("The decayed dweller punches your face VERY hard!\n");
       tell_room(environment(this_object()), "The decayed dweller punches " +
		 QCTNAME(obj) + " in the face, VERY hard!\n", obj);
   }
}



