/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith May 2014: Added some chats and add-asks. Changed the adj
 *                  and long desc so they seem less menacing to little
 *                  players. Modified align to be on the good rather 
 *                  than evil side since dark elves are evil.
 */
#pragma strict_types

inherit "/std/monster";
#include "../dark.h"

public void
create_monster(void)
{
    setuid();
    seteuid(getuid());

    string str = one_of_list(({
	"smiling", "stinky", "pinkish", "sturdy", "massive",
	"sensitive", "battered", "scarred", "ugly", "puzzled",
	"shivering", "blinking", "dazed-looking", "timid",
    }));

    set_adj(str);
    add_name("goblin");
    set_race_name("hobgoblin"); 
    set_short(str + " hobgoblin");
    set_pshort(str + " hobgoblins");
    set_long("A "+ str +" goblin of the white-horned tribe, they are "+
      "simple and harmless creatures who keep to themselves in this "+
	  "dark and unkind environment.\n");

    set_base_stat(SS_STR, random(20)+15);
    set_base_stat(SS_DEX, 25);
    set_base_stat(SS_CON, random(30)+15);
    set_base_stat(SS_INT, 3);
    set_base_stat(SS_WIS, 3);
    set_base_stat(SS_DIS, 25);

    set_alignment(50 + random(50));
 
    set_skill(SS_PARRY,		30);
    set_skill(SS_DEFENCE,	25);
    set_skill(SS_WEP_POLEARM,	35);
    set_skill(SS_WEP_SWORD,	40);
    set_skill(SS_WEP_KNIFE,	25);
    set_skill(SS_WEP_CLUB,	15);

    set_all_hitloc_unarmed(22);
	
    set_chat_time(30 + random(30));
	add_chat("The dark elves scare me.");
	add_chat("The ogres scare me more, though.");
	add_chat("I wish we dared approach the sybarites for help.");
	add_chat("The life of a scavenger is a hard one.");
	add_chat("I've never seen the Source. I hear it is beautiful.");
	add_chat("It's not much, but it's home.");
	add_chat("We're tucked away in a spot few bother with.");
	add_chat("I heard there are wolves with wings living down here.");
	add_chat("I heard there are albi, too. Some kind of cousins of ours.");
	add_chat("The imps seem to be hiding something. Or guarding something.");
	add_chat("The tooth of the great worm is very sharp, they say.");
	add_chat("The trolls down here aren't much of a threat. I wonder if "+
			 "I could take one?");
	add_chat("The dwarves guarding the Fort are very vigilant.");
	add_chat("Have you ever thought of going beyond the pool and out "+
			 "to the Surface?");

	set_default_answer(VBFC_ME("what_me"));
	add_ask(({"[where] [is] [the] 'bazaar'"}), 
			"say I hear if you go to the edge of the sea and hit the pipe "+
			"a boat will take you to the Bazaar.", 1);
	add_ask(({"[where] [is] [the] 'boat'"}), 
			"say I've heard if you go deep into the fort until you reach "+
			"the sea you will see a pipe. Hit it with something and "+
			"the boat will come.", 1);
	add_ask(({"[who] [are] [the] 'shadow-elves' / 'shadow' 'elves' / 'sybarites'"}), 
			"say They are the rules of Sybarus, those who have the "+
			"Gods' Favor.", 1);
	add_ask(({"[where] [is] [the] [shadow] 'union'"}), 
			"say It's somewhere deep in the Utterdark, that's all I know.", 1);
						
	
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, ({ random(25)+5, random(8) }));

    str = "hob_" + one_of_list(({ "dagger", "scimitar", "spear" }));
    clone_object(OBJ + str)->move(this_object());
    command("wield all");
}

string
what_me()
{
	switch(random(7))
	{
		case 0:
			command("say How would I know?! I've never been anywhere.");
			break;
		case 1:
			command("say So many questions, no real answers.");
			break;
		case 2:
			command("emote shrugs.");
			break;
		case 3:
			command("say That tickles!");
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
