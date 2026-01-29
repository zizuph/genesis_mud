/*
 * Dalizen, guild trainer of the Mercenaries Guild
 * 	by Morrigan, 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_GONDOR_NPC

#include "attackers.h"

void
create_gondor_monster()
{
    set_name("dalizen");
    add_name("trainer");
    set_title("the Dark, the Mercenary Lord");
    set_race_name("elf");
    set_long("Tall and slender, he moves with incredible grace and "+
	"precision. He regards those around him with keen eyes, and "+
    "looks like he is an important person.\n");
    set_adj(({"quiet", "calculating"}));

    set_stats(({ 120, 185, 140, 155, 140, 130 }));
    set_skill(SS_WEP_SWORD, 93);
    set_skill(SS_AWARENESS,   70);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "Are you out of your mind? Attacking him "+
	"in the middle of his own camp? You would be slaughtered for sure!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Are you out of your mind? Attacking him "+
	"in the middle of his own camp? You would be slaughtered for sure!\n");
    set_money(({ random(20), random(10), random(5), random(2) }));

    add_ask_item("maligant", "say Well, he left, so I guess that means that"
      + " I'm in charge now. I don't know if I'll stick around either,"
      + " though. Things are looking bad.");
    add_ask_item("gnimpsh", "say He serves his purpose well enough, but he is "+
	"far too chatty for my taste.");
    add_ask_item("morgan", "say She left, it seems. I don't miss her"
      + " much, but then again I think she disliked me because I'm an elf.");
    add_ask_item("tarn", "say Tarn makes wonderful swords, I use nothing else.");
    add_ask_item("taryn", "say What of Taryn? She's just a child.");
    add_ask_item("soren", "say I know nothing about him.");
    add_ask_item(({"background", "history", "past" }), "say My past is my own "+
	"concern, not yours. But I am feeling benevolent, so I'll share a small "+
	"piece. My homeland is Silvanesti, or was, until I was cast from the "+
	"light and called a renegade for dabbling in the arcane arts without "+
	"the permission of the mages. So this is now my home, what I know of "+
	"the sword I was taught by the master swordsmen of Silvanesti. What "+
	"I know of the arcane arts, well... I'll keep that to myself, for now."); 

    add_ask_item(({"orcs", "goblins", "goblin", "orc"}), "say I put up with "+
	"them only because Maligant commands it. I will not train them "+
	"to be skilled with the sword.");
    add_ask_item(({"skill", "skills", "training", "train" }), "say Mercenaries "+
	"are adept fighters who have a knack for surviving on their own terms. "+
	"Most can choose whether to specialize in the sword or the club, all are "+
	"veterans of defensive skills and appraising their enemies.");
    add_ask_item(({"sword", "swords"}), "say Swords are, quite simply, the "+
	"weapons of choice for the refined warrior. Which is why I don't train "+
	"goblins in them. I train others to be masters with the blade.");
    add_ask_item(({"club", "clubs"}), "say Any dolt can crush something to a "+
	"pulp with a club. If it's mindless smashing that you crave, be my "+
	"guest.");
    add_ask_item(({"mercenary", "mercenaries", "guild", "join", "joining" }),
	"say I used to send people who asked about that to Maligant. Now,"
      + " well ... I guess you'll have to figure it out for yourself.");
    add_ask_item(({"halfling", "halflings", "hobbit", "hobbits", "kender"}),
	"say I am honour-bound to train these diminutive things to use a "+
	"sword. I guess life has its ups and downs.");
    add_ask_item(({"dwarf", "dwarves" }), "say Dwarves are strong, but I have "+
	"found that they lack the grace to use a sword as effectively as elves.");
    add_ask_item(({"elf", "elves"}), "say I enjoy teaching elves above all "+
	"others, "+
	"they are naturally graceful and intelligent, and thus excel at "+
	"swordplay.");
    add_ask_item(({"gnome", "gnomes"}), "say I will train gnomes, though I see "+
	"fewer and fewer of them these days.");
    add_ask_item(({"human", "humans"}), "say Some humans possess the discipline "+
	"and will to become excellent swordsmen, so I will let them choose for "+
	"themselves.");
        
    set_default_answer( ({ "say I'm not interested in that.", "say I don't "+
	"have time to talk about that.", "say Go chat with Gnimpsh instead, "+
	"I am busy.", "say Do not pester me with this mindless babble anymore." }) );
}

void
intro_me(object name)
{
    command("emote bows with grace and dignity.");
    command("present me to " + OB_NAME(name));

}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
