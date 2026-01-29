// file name:	shopkeeper.c
// creator(s):	Ilyian
// last update:	Denis, May'97
//              Lilith May 2014  Updated shopkeeper desc for outpost, added asks
// purpose:	Shopkeeper
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/outpost/outpost.h"
# include <money.h>

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

int armed;

void
create_monster()
{
    set_name("melnox");
    set_adj(({"pale", "alert"}));
    set_title("icu Wer'a, Proprietor");
    set_living_name("Melnox");
    add_name(({"shopkeeper","keeper"}));
    set_race_name("gnome");
    set_gender(0);

    set_long("This gnome looks like he is alert for a good deal. " +
             "He seems friendly enough, and eager for your business.\n");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);

    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(100);
    set_knight_prestige(-2);

    set_chat_time(15);
    add_chat("Greetings!");
    add_chat("Welcome to my shop!");
	add_chat("If you're headed for the Bazaar, watch your manners. "+
			 "If you're headed for the Utterdark, watch your back!");
    add_chat("Lets get down to business.");
	add_chat("It is as black as an ogre's bowels down there.");
	add_chat("We gnomes are the merchants of Sybarus.");
	add_chat("The Shadow Union guild hall is down here somewhere. "+
			 "I found it once.");
	add_chat("Sair and Salilus guide all who venture into the Deep.");
	
	set_default_answer(VBFC_ME("what_me"));
	add_ask(({"[where] [is] [the] 'bazaar'"}), 
			"say Go to the edge of the sea and hit the pipe. A boat will "+
			"take you to the Bazaar.", 1);
	add_ask(({"[where] [is] [the] 'boat'"}), 
			"say Follow the path deeper into the fort until you reach "+
			"the sea. You will see a pipe. Hit it with something and "+
			"the boat will come.", 1);
	add_ask(({"[how] [to] [summon] / [call] / [catch] [the] 'boat'"}), 
			"say Follow the path deeper into the fort until you reach "+
			"the sea. You will see a pipe. Hit it with something and "+
			"the boat will come.", 1);
	add_ask(({"[where] [is] [the] 'pipe'"}), 
			"say Follow the path deeper into the fort until you reach "+
			"the sea. You will see a pipe. Hit it with something and "+
			"the boat will come.", 1);
	add_ask(({"[who] [are] [the] 'shadow-elves' / 'shadow' 'elves'"}), 
			"say They are the rules of Sybarus, those who have the "+
			"Gods' Favor.", 1);
	add_ask(({"[where] [is] [the] [shadow] 'union'"}), 
			"say It's somewhere deep in the Utterdark. I always get "+
			"lost when I go looking for the guild. It is worth a "+
			"visit, though. The Halls are beautiful.", 1);
	
    set_cchat_time(3);
    add_cchat("Get outta here!");
    add_cchat("Attacking poor defenseless shopkeepers, sheesh!");
    add_cchat("Shame on you!");

    set_cact_time(1);
    add_cact("slap enemy");
    add_cact("scream");
}

string
what_me()
{
	switch(random(7))
	{
		case 0:
			command("say I am not permitted to answer that.");
			break;
		case 1:
			command("say I am a simple merchant, I do not know.");
			break;
		case 2:
			command("emote struggles to answer, but does not seem able "+
					"to get the words out.");
			break;
		case 3:
			command("say There are questions I cannot answer. Try elsewhere.");
			break;
		case 4:
			command("emote looks anxiously around.");
			break;
		case 5:
			command("say Ask someone else, please.");
			break;
		case 6:
			command("emote pretends not to hear.");
			break;
	}
	return "";
}
