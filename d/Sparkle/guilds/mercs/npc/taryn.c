/*
 * Taryn the waitress
 * 	by Morrigan, 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_GONDOR_NPC

#include "attackers.h"
#include "assist.h"

void
create_gondor_monster()
{
    set_name("taryn");
    add_name("waitress");
    set_title("");
    set_race_name("human");
    set_gender(1);
    set_long("This young girl looks like she is in her early teens, "+
	"probably an orphan that was picked up along the way to serve "+
	"patrons of the inn.\n");
    set_adj(({"young", "blue-eyed"}));

    set_stats(({ 35, 45, 40, 40, 30, 20 }));
    set_skill(SS_WEP_SWORD, 43);
    set_skill(SS_AWARENESS,   20);
    set_skill(SS_DEFENCE,     38);
    set_skill(SS_PARRY,       38);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    set_money(({ random(20), random(9), random(0), random(0) }));

    add_ask_item("maligant", "say Maligant told me one day I can be "+
	"a mighty warrior like him, but not yet. Of course, then he"
      + " up and left. Now I don't know what to think.");
    add_ask_item("dalizen", "say Oh I like Dalizen, don't tell him I told "+
	"you, but he's been teaching me to use a sword in private!");
    add_ask_item("soren", "say I know he's mute, but it's weird the way he "+
	"just stares at you!");
    add_ask_item("tarn", "say Tarn is a teddy bear! He is forging me a magic "+
	"sword, too!");
    add_ask_item("morgan", "say Well of course I know her, she's my "+
	"mother! We used to live in Minas Tirith, but when she started "+
	"travelling with Maligant, I came along. She told me she left"
      + " to see if she can work something out for the Mercenaries. I"
      + " don't know what she's up to, but I'm sure it will all work"
      + " out!");
    add_ask_item("gnimpsh", "say Gnimpsh talks so fast, I can barely "+
	"understand him!");

    add_ask_item(({"goblins", "goblin"}), "say Eewww, they're kinda smelly.");
    add_ask_item(({"mercenary", "mercenaries", "guild", "join", "joining" }),
	"say I'm going to be a mercenary one day!");
    add_ask_item(({"halfling", "halflings", "hobbit", "hobbits", "kender"}),
	"say They're so fun to play with! Especially kender!");
    add_ask_item(({"dwarf", "dwarves" }), "say Maligant is a big teddy "+
	"bear, he just pretends to be mean all the time.");
    add_ask_item(({"elf", "elves"}), "say I don't know many elves, but I "+
	"like Dalizen, he's an elf.");
    add_ask_item(({"gnome", "gnomes"}), "say Gnomes are weird!");
    add_ask_item(({"human", "humans"}), "say What about them?");
        
    set_default_answer( ({ "say I wouldn't know that, I'm afraid.", "say I "+
	"am uncertain of that.", "say I must say, I have no idea!", "say I "+
	"think perhaps you should seek the guidance of another on that matter." }) );
}

void
intro_me(object name)
{
    command("smile brightly");
    command("introduce me" );
    command("say Hi, "+name->query_race_name()+
	", do you want to order any food?");
}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
