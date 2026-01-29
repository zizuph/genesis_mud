inherit "/std/monster";

#include "default.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_monster()
{
    set_name("pilgrim");
    set_living_name("_mylos_pilgrim_");
    set_adj("old");
    set_race_name("elf");
    set_short("old pilgrim");
    set_long(break_string("This old man is wandering around the countryside "+
                "looking for people to talk to and places to stay.\n",76));

    set_base_stat(SS_STR, 30);
    set_base_stat(SS_DEX, 23);
    set_base_stat(SS_CON, 29);
    set_base_stat(SS_INT, 9);
    set_base_stat(SS_WIS, 8);
    set_base_stat(SS_DIS, 30);

    set_skill(SS_DEFENCE, 25);
    set_skill(SS_PARRY, 22);
    set_skill(SS_WEP_POLEARM, 15);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_AWARENESS, 45);

    set_hp(250);

    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(OBJ_S_WIZINFO, "/dThis pilgrim will wander around the domain of "+
		"Emerald and when asked,\nwill give out quest tips to the player "+
		"who asks him. He also will\nreact to players emotions such as "+
		"'smile', 'growl' and 'bow'. He also has the\nEmerald mage_soul "+
		"on him and will do actions from there as well as those\n "+
		"comon to players.\n");
    add_cmdsoul("/d/Emerald/soul/mage_soul");

    set_chat_time(10);                             /* Set speaking interval */
    add_chat("So you think you are up to the challenge, eh?");
    add_chat("Have you seen the wonderful tower in the village?"); /* A bit of random chat */
    add_chat("Faerie is mighty dangerous, sure you want to go there?");
    add_chat("Do you like this place?");
    add_chat("Ever been to faerie?");
    add_chat("Why, yes, I have done the Crystal Tower quest!");

    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("Stop this madness! Leave me alone!");            /* The usual combat talk */
    add_cchat("Do you really think that i'm alone?");

    set_act_time(10);                    /* Set action interval           */
    add_act("smile");              /* A few courteous actions       */
    add_act("daydream");
    add_act("murmur");
    add_act("chant");

    add_ask( ({ "faerie", "about faerie", "how do i enter faerie", "How do I enter faerie" }),
             VBFC_ME("ask_faerie"));
    add_ask( ({ "quest", "about quest", "challenge", "about challenge",
                "what is the quest", "what is the challenge" }),
             VBFC_ME("ask_quest"));
    trig_new("%w 'smiles.\n' %s", "react_smile");
    trig_new("%w 'smiles' %s", "react_smile");
    trig_new("%w 'growls' %s", "react_growl");
    trig_new("%w 'growls.\n' %s", "react_growl");
    trig_new("%w 'introduces' %s", "react_introduce");
    trig_new("%w 'shakes' %w 'head' %s", "react_shake");
    trig_new("%w 'giggles' %s", "react_giggle");
    trig_new("%w 'bows' %s", "react_bow");
    trig_new("%w 'sighs' %s", "react_sigh");
    trig_new("%w 'swears' 'loudly.\n' %s", "react_swear");
    call_out("arm_me", 1);
        set_random_move(20);
        set_restrain_path(({"/d/Emerald/room"}));
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 3, who);
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
         command("say Life is great, isn't it, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say It is great to see you smiling, " + obj->query_nonmet_name()
               + ".");
   }
}

int
react_introduce(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      return 1;
   }
}

void
return_introduce(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
      {
         command("say Nice to meet you, " + obj->query_name() + ".");
         command("bow to " + who);
      }
      if (ran == 1)
      {
         command("bow to " + who);
      }
      if (ran == 2)
      {
         command("say Be welcome, " + obj->query_race() + ".");
         command("bow to " + who);
      }
   }
}

int
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      call_out("return_shake", 3, who);
      return 1;
   }
}

void
return_shake(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say So you disagree, " + obj->query_race() + "?");
      if (ran == 1)
         command("say I agree with you, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
               + " always disagree?");
   }
}
int
react_giggle(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_giggle", 3, who);
      return 1;
   }
}

return_giggle(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Funny, eh " + obj->query_race() + "?");
      if (ran == 1)
         command("say Ah, " + LANG_PWORD(obj->query_race())
               + " are such merry people.");
      if (ran == 2)
         command("giggle");
   }
}



int
react_swear(string who, string dummy)
{
   if (who)
	{
	who = lower_case(who);
	call_out("return_swear", 3, who);
	return 1;
	}
}
void
return_swear(string who)
{
	object obj;
	int ran;
	if(obj = present(who, environment()))
	{
		ran = random(3);
		if(ran == 0)
		command("say Don't swear in front of young "+(obj->query_gender() ? "woman" : "man") +"!");
		if(ran == 1)
		command("eyebrow " +who);
		if(ran == 2)
		command("growl "+who);
	}
}

		

int
react_growl(string who, string dummy)
{
   if (who) {
      who = lower_case(who);
      call_out("return_growl", 3, who);
      return 1;
   }
}

void
return_growl(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You make me uneasy with your growling, " + obj->query_race()
               + "...");
      if (ran == 1)
         command("say Why so hostile, " + obj->query_race() + "?");
      if (ran == 2)
         command("eyebrow");
   }
}
int
react_sigh(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_sigh", 3, who);
      return 1;
   }
}

void
return_sigh(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Why are you depressed, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say Is life tough for you, " + obj->query_nonmet_name()
               + "?");
   }
}

int
react_bow(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_bow", 3, who);
      return 1;
   }
}

void
return_bow(string who) {
   command("bow " + who);
}


void
arm_me()
{
    object eq;

    eq = clone_object("/d/Emerald/mylos/obj/staff");
    if (eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/room/phase/tower/torque");
    if (eq)
        eq->move(this_object());
    command("wield all");
}

string
ask_faerie()
{
    return break_string("Now faerie, that is an interesting place... mighty "+
                        "dangerous though. You will have to find the Earl "+
                        "king hill, a faerie mound, and walk around it nine "+
                        "times widdershins. Then through the cave and you "+
                        "will behold a sight few have ever witnessed: The "+
                        "land of faerie! Be forewarned that faerie is "+
                        "not for the weak. Faerie creatures are not all "+
                        "beautiful sprites and nymphs, they can be evil and "+
                        "twisted as well. Even seemingly good creatures "+
                        "have their own values and agendas that might "+
                        "be dangerous to you. So do not take anything for "+
                        "granted in faerie. If you have a specific "+
                        "destination in mind, then I urge you to summon a "+
                        "guide at the entrance of faerie and tell it to "+
                        "guide you to your location. Do not stop on your "+
                        "journey when following the guide, for it will "+
                        "not stop to wait for you, and to get lost in "+
                        "faerie could mean death... or worse. So my "+
                        "friend, I urge you to heed my warnings and follow "+
                        "my advice, for I wish you aught but good journeys.\n", 76);
}

string
ask_quest()
{
    if (this_player()->query_stat(SS_DEX) < 51)
        return "You would not be quick enough for that.\n";
    if (this_player()->query_skill(SS_AWARENESS) < 26)
        return "You would not be able to complete that.\n";
    return break_string("The challenge you say. Well, it has been awhile "+
                        "but I do remember it distinctly. The Crystal "+
                        "Tower quest, originally made to weed out the "+
                        "mages who couldn't handle the highest magics. "+
                        "I remember when I was first told about it by "+
                        "a mage of considerable power whom I had "+
                        "befriended. He peered at me and said: \"So "+
                        "you seek to take the challenge, eh? Well, "+
                        "know ye this, that the first test is to find "+
                        "the tower and when you do, follow your "+
                        "instincts and we will see if you are up to "+
                        "it!\" He then cackled at me and would tell "+
                        "me no more. I however will share a few tips with "+
                        "you, as you seem competent enough. The tower "+
                        "is in the land of oldest magic, faerie itself. "+
                        "You must seek the Crystal Tower in the crystal "+
                        "canyon and wait until the tower chooses to "+
                        "reveal itself to you. Once inside the tower, "+
                        "seek to learn all that you can from a level "+
                        "before proceeding, and be alert and use your "+
                        "mind. Brawn has its place, but this is a test "+
                        "mostly of the mind. I can tell you no more, for "+
                        "it is a place to learn your limits and for "+
                        "another to solve it for you would be both "+
                        "unjust and unwise. Good luck, and be forewarned "+
                        "that this is a quest to be completed alone. "+
                        "For you must be able to solve the quest without "+
                        "another's help for it to have any meaning.\n", 76);
}
