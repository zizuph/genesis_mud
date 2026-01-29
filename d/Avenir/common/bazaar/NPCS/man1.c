// Street man   #1 (/d/Avenir/common/bazaar/NPCS/man1.c)
// creator(s):   Tepisch & Grace
// last update:  Tepisch Sept 1994, Ilyian May 1995, Glinda May - 95
//               Cirion, March 95: Fixed typos
//               Cirion, May 30 1996: Fixed bugs due to new mudlib
// purpose:      men to make part of the crowd, adds ambiance to bazaar
//
// note:
// bug(s):
// to - do:

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/guilds.h"
#include <language.h>
#include <money.h>

string  randadj();
string  randrace();
string  randdesc();

int alarm_id;

void 
create_monster()
{
    if (!IS_CLONE)
        return;
    ::create_monster();

    set_name("male");
    add_name(({"elder", "bondsman", "thrall", "adolescent", "slave"}));
    set_race_name(randrace());
    add_adj(randadj());
	set_short(randadj() +" "+ randdesc());
    set_long("He is well-trained and polite, resigned to his "+
        "fate as a slave. You notice in him the same dignity "+
        "unique to most of the slaves of Sybarus.\n");

    set_stats(({70 + random(20), 70 + random(30), 60 + random(30),
		40 + random(10), 30 + random(20), 50 + random(10)}));
    set_skill(SS_UNARM_COMBAT, 50 + random(20));
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_WEP_CLUB, 40 + random(30));
    set_skill(SS_DEFENCE, 40 + random(30));
    set_skill(SS_BLIND_COMBAT, 40 + random(30));
    set_all_hitloc_unarmed(10 + random(30));
    set_scar(random(20));
    set_alignment(0);
    set_pick_up(1);

    KILL_THIEF;
    NEVERKNOWN;

    set_act_time(2);
    add_act("emote rubs the small of his back.");
    add_act("say The Shadow-elves of Sybarus will see that the " +
	    "Gods are appeased.");
    add_act("say I do not believe in hobbits.");
    add_act("say The Holm is where the Shadow Elves Hunt. Its a "+
            "lawless, chaotic place. You invite death there.");
    add_act("emote eyes you curiously.");
    add_act("emote tries to move out of your way.");
    add_act("emote looks longingly in the direction of the " +
	    "gates to the City.");
    add_act(({"emote shudders.", "say I've been to the pillory. " +
	      "It took 10 days for the skin on my back to heal."}));
    add_act("emote hacks up some phlegm and spits it out.");
    add_act("say Children today can be so rude.");
    add_act("spank child");
    add_act("say If I am late my master will have me beaten.");
    add_act("say Don't give the Protectors a reason to kill you.");

    set_cact_time(2);
    add_cact("emote mumbles: Death is impermanent. In the cycle " +
	     "of the Source I will always be a slave.");
    add_cact(({"say Isn't this just like you surface-dwellers?" +
	       " Killing defenseless people!", "emote blows spittle " +
	       "into your face"}));
    add_cact("say Damn you to the Source-less depths of the" +
	     "Utterdark!");
    add_cact("say I hope the demons take you!");
    add_cact("shout You are cruel, even for an Outlander!");
    add_cact("say Upon your head the fate of my orphaned children!");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"library"}), "say The library is up north, right across " +
	    "the street from the bank.", 1);
    add_ask(({"bank"}), "say The bank is up north, right across " +
	    "the street from the library.", 1);
    add_ask(({"holm", "park", "Holm"}), "say It can be reached through the "+
        "garden. A gatekeeper guards the way.",1);
    add_ask(({"post office", "post"}), "say The postoffice is up north, " +
	    "right across the street from the smith.", 1);
    add_ask(({"smith", "forge"}), "say The smith is up north, " +
	    "right across the street from the postoffice.", 1);
    add_ask(({"inn"}), "say The inn is up in the northwest.", 1);
    add_ask(({"pier"}), "say The pier is up northwest.", 1);
    add_ask(({"guild"}), "say The guild is on the west side of the bazaar.", 1);
    add_ask(({"pub"}), "say The pub is on the east side of the bazaar.", 1);
    add_ask(({"garden"}), "say Yes there is a garden south of the bazaar.", 1);
    add_ask("help", "shrug", 1);

}

void
arm_me()
{
    seteuid(geteuid(this_object()));
    refresh_living();

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
    command("wield all");

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");
}
void equip_me() {  arm_me();  }

string
randadj()
{
    string         *randadj;
    randadj = ({"burdened", "sad-eyed", "tall", "strong", "muscular",
		"handsome", "filthy", "angry", "busy", "bent", "quick",
		"stupid", "irritable", "smiling", "odd", "lame",
		"wild-eyed", "injured", "bent-nosed", "deformed", 
                "dreamy-eyed", "indignant", "careful"});
    return randadj[random(sizeof(randadj))];
}
string
what_me()
{
    switch(random(4))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say You're asking me?");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
    }
    return "";    
}

string
randrace()
{
    string         *randrace;
    randrace = ({"human", "gnome", "dwarf", "halfling"});
    return randrace[random(sizeof(randrace))];
}

string
randdesc()
{
    string         *randdesc;
    randdesc = ({"adolescent", "elder", "bondsman", "thrall", "slave"});
    return randdesc[random(sizeof(randdesc))];
}

int
special_attack(object victim)
{
    int             punch;
    string          who;
    object          me = this_object();

    if (random(3))
	return 0;		/* normal attack */

    who = lower_case(victim->query_name());
    punch = random(3);

    if (punch == 0) {
	victim->catch_msg(QCTNAME(me) +
			  " punches you in the " +
			  "face with his fist! Blood clouds your vision.\n");
	tell_room(environment(victim), QCTNAME(me) +
		  " punches " + QCTNAME(victim) + " in the face with " +
		  "his fist!\n", victim);
	victim->heal_hp(-35);
	me->command("say I hope I broke your nose!");
	me->command("frown");
    }
    if (punch == 1) {
	victim->catch_msg(QCTNAME(me) +
			  " kicks your legs " +
			  "out from under you.\nYou land on your ass, " +
			"bruising your dignity more than anything else.\n");
	tell_room(environment(victim), QCTNAME(me) +
		  " kicks " + QTNAME(victim) + "'s legs out from under " +
		  victim->query_objective() + ".\n" + QCTNAME(victim) +
	     " lands on " + victim->query_possessive() + " ass!\n", victim);
	victim->heal_hp(-10);
	me->command("chortle");
    }
    return 1;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(10);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
		  return;

	 if(tp->query_prop("_is_cat_"))
	 {
		if(i<3)
		{
			command("kick "+tp->query_real_name()+" .");
			return;
		}

		if(i<6)
		{
			command("pat "+tp->query_real_name()+" head");
			return;
		}
		return;
	 }

	 occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 0)           
            command("say to "+ tp->query_real_name() +" Celebrate "+
                "the Source!");
        if (i == 4)
            command("bow deep "+ tp->query_real_name());
        if (i == 8)
            command("say to "+ tp->query_real_name() +" Greetings "+
                "in the name of Jazur!");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i == 0)
            command("whistle meaning "+ tp->query_real_name());
        if (i == 3)
            command("say to "+ tp->query_real_name() +
                " Thou art truly the image of perfection!");
        if (i == 6)
            command("say to "+ tp->query_real_name() +
                " Qalita has chosen well. You have beauty"+
                " and grace.");
        return;
    }       
    else
    {
        if (i == 1)
           command("grin impud "+ tp->query_real_name());
        if (i == 5)
           command("smile respect "+ tp->query_real_name());
        if (i == 9)
           command("emote bows to you, eyes lowered subserviantly.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        else
            alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  
