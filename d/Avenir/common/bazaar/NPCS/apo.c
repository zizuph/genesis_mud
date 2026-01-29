// Apothecarist  /d/Avenir/common/bazaar/NPCS/apo
// creator(s):   Lilith, 20 March 1997
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/givetask";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#define WOLF_QUEST "/d/Avenir/common/holm/wolf/"

int armed;
int bones;
int talking_about_bones;
int add_the_acts();
string def_answer();
string wolf_ask();

//string _i_asked_for_a_bone;

void
create_monster()
{
	 set_name("prumwil");
	 set_adj(({"merry", "portly"}));
	 set_title("icu Sabilis the Apothecarist");
	 set_living_name("prumwil");
	 add_name(({"shopkeeper","keeper", "apothecarist", "apo"}));
	 set_race_name("gnome");
	 set_long("A kindly-looking and rather talkative gnome with "+
		  "an ample girth and watchful eyes. He appears to be the "+
		  "proprietor of this place.\n");

	 set_all_hitloc_unarmed(50);
	 set_stats(({70,70,70,70,70}));

	 set_skill(SS_UNARM_COMBAT,50);
	 set_skill(SS_BLIND_COMBAT,100);
	 set_skill(SS_PARRY,50);
	 set_skill(SS_DEFENCE,65);
	 set_skill(SS_AWARENESS,30);
	 set_skill(SS_WEP_SWORD,50);
	 set_skill(SS_WEP_POLEARM,50);
	 set_skill(SS_WEP_CLUB,50);
	 set_skill(SS_WEP_KNIFE,50);

	 add_prop(NPC_I_NO_RUN_AWAY,1);
	 add_prop(CONT_I_WEIGHT, 163000);
	 add_prop(CONT_I_HEIGHT, 120);

	 set_alignment(100);
//    set_knight_prestige(-2);

	add_the_acts();

	 set_cchat_time(3);
		add_cchat("You won't profit by this!");
		add_cchat("Attacking poor defenseless shopkeepers!");
		add_cchat("May the doors of your home be eternally closed "+
			 "to you!");

	 set_cact_time(1);
		add_cact("slap enemy");
		add_cact("scream");

	 set_default_answer(VBFC_ME("def_answer"));
	 add_ask(({"bone", "wolf", "bones", "task", "quest","help", "job"}), VBFC_ME("wolf_ask"));

	 bones = 200;   //   Increased the number to 200 due to longer uptimes Ibun
}

int
add_the_acts()
{
	 set_chat_time(52);
		add_chat("Greetings, stranger!");
		add_chat("Bones are wise things. Ask me about them!");
		add_chat("Welcome to my apothecary shop!");
		add_chat("I've curiosities of all sorts.");
		add_chat("I know some things about bones and wolves.");
		add_chat("Business is booming! What a great day it was for "+
			 "Sybarus when the Edict of Isolation was lifted.");
		add_chat("It took a great deal of money to gain the Lord Commi"+
			 "sioner's permission to re-open this shop after the Lord "+
			 "Inquisitor closed it down.");
		return 1;
}

void
arm_me()
{
	seteuid(geteuid(this_object()));
	MONEY_MAKE_SC(random(40))->move(this_object());

	clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
	clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
	command("wear all");
}

void
react_attack()
{
	 clone_object(BAZAAR + "Obj/wield/bmace")->move(TO, 1);
	 command("emote grabs something from behind the counter.");
	 command("wield all");
	 command("grin danger");
	 armed=1;
}

void
attacked_by(object ob)
{
	 ::attacked_by(ob);
	 if(!armed)
		  react_attack();
}

string
race_sound()
{
	return "chirps";
}

string
def_answer()
{
	 command("say There are some things which I am not at liberty to "+
		  "discuss.");
	 return "";
}

void reset_talking_about_bones()
{
    talking_about_bones = 0;
}

string
wolf_ask()
{
	 if (!CAN_SEE(TO, TP))
	 {
	//Shut him up while do this.
	clear_act();
	command("scratch head");
	set_alarm(3.0, 0.0, &command("say I listen to the wind often... "
	+ "And strange voices I am accustomed to. However, never "
	+ "has the wind asked me to explain the medicinal "
	+ "value of bones, before."));

	set_alarm(6.0, 0.0, &command("say I am an old gnome. "
	+ "But, not a stupid one. "
	+ "Reveal yourself if you want to converse with me."));

	add_the_acts();
	return "";
	 }

	 if(  TP->test_bit("Avenir",0, 18) )
	 {
			check_group_two(TP, ({0,0,0,0}) );
			return "";
	 }

	 if(bones==0)
	 {
		//Shut him up while do this.
		clear_act();
		set_alarm(3.0, 0.0, &command("say I am very busy just now, "
		+ "and do not have time for lectures."));

		set_alarm(5.0, 0.0, &command("say Come back later."));

		set_alarm(8.0, 0.0, &command("emote scribbles irritably "
			+ "in a large bounded book."));
		add_the_acts();
		return "";
	 }
     if (talking_about_bones)
     {
         return "";
     }
     talking_about_bones = 1;

	 clear_act();
	 set_alarm(1.0, 0.0, &command("say Bones are the "
	+ "foundation for all of life, yet "
	+ "are the embodiment of death. Powerful medicines "
	+ "to accomplish both can be extracted from the marrow "
	+ "of certain animals."));

	 set_alarm(3.0, 0.0, &command("say Only the very "
	+ "wise, would ask me such a question."));

	 set_alarm(5.0, 0.0, &command("peer intensely "
	+ this_player()->query_real_name()) );

	 if(this_player()->query_skill(SS_ANI_HANDL)<20)
	 {
	set_alarm(8.0, 0.0, &command("say No. "
	+ "I was wrong. You lack the training "
	+ "needed to appreciate the fundamentals and beauty of an "
	+ "animal's soul bone."));

	set_alarm(10.0, 0.0, &command("shrug ."));

	set_alarm(12.0, 0.0, &command("emote mutters "
	+ "absentmindedly to himself."));

    set_alarm(14.0, 0.0, reset_talking_about_bones);

	add_the_acts();
		return "";
	 }

	 else
	 {

/*
	if(this_player()->query_prop("_i_asked_for_a_bone_")
	{
	command("emote pretends not to hear.");
	return "";
	}

	this_player()->add_prop("_i_asked_for_a_bone_");
*/


	set_alarm(8.0, 0.0, &command("hmm"));

	set_alarm(11.0, 0.0, &command("say I will "
	+ "help you. Listen closely."));

	set_alarm(13.0, 0.0, &command("whisper "
	+ this_player()->query_real_name()
	+ " Death is the fertile ground to life. The scattered bones "
	+ "and barren, desolate world of the starving are the "
	+ "disguised beginnings of a new life."));

	set_alarm(25.0, 0.0, &command("emote starts to search the bones."));
	set_alarm(30.0, 0.0, &command("emote finds something in the bones!"));

	clone_object(WOLF_QUEST + "vertebra.c")->move(this_object(),1);

	set_alarm(32.0, 0.0, &command("give vertebra to "
	+ this_player()->query_real_name()) );

	bones--;

	set_alarm(35.0, 0.0, &command("whisper "
	+ this_player()->query_real_name()
	+ " Take this. Find its place. Listen for its voice. "
	+ "You will put it all together."));

	set_alarm(42.0, 0.0, &command("whisper "
	+ this_player()->query_real_name()
	+ " Be warned! This is not an ordinary bone.  A spell has "
	+ "been placed on it that will be broken if it is taken "
	+ "out of bounds of its homeland."));


	set_alarm(52.0, 0.0, &command("emote twinkles his eyes merrily."));

    set_alarm(53.0, 0.0, reset_talking_about_bones);


	add_the_acts();
	return "";
	 }
	 add_the_acts();
	 return "";
}

 
int
query_int_bones()
{
    return bones;
}
