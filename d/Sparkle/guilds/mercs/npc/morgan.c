/*
 * Morgan, guild trainer of the Mercenaries Guild
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
    set_name("morgan");
    add_name("trainer");
    set_gender(1);
    set_title("the Wanderer, the Pathfinder of Maligant's Mercenaries");
    set_race_name("human");
    set_long("Auburn hair, loosely gathered, falls in winding streams "+
	"down the back of "+
	"this small woman. She observes her surroundings with intense "+
	"icy blue eyes, that seem to take in every minute detail. She "+
	"is dressed in soft leathers, and wears a dark green cloak. "+
	"A short sword hangs at her side, and a thin dagger is sheathed "+
    "in her boot.\n");
    set_adj(({"auburn-haired", "blue-eyed"}));

    set_stats(({ 120, 135, 130, 135, 150, 130 }));
    set_skill(SS_WEP_SWORD, 93);
    set_skill(SS_AWARENESS,   70);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "Are you out of your mind? Attacking her "+
	"in the middle of her own camp? You would be slaughtered for sure!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Are you out of your mind? Attacking her "+
	"in the middle of her own camp? You would be slaughtered for sure!\n");
    set_money(({ random(20), random(10), random(5), random(2) }));

    add_ask_item("maligant", "say Maligant was our leader before he up"
      + " and abandoned us. If I see him I'll slit his throat myself.");
    add_ask_item("tarn", "say I think he is one of Maligant's friends, but "+
	"he seems to be a skilled blacksmith.");
    add_ask_item("dalizen", "say Dalizen is somewhat aloof, he stays to "+
	"himself quite a bit. I don't think he likes me much.");
    add_ask_item("gnimpsh", "say Oh, I love dear Gnimpsh. Sometimes I think "+
	"Maligant is taking advantage of him.");
    add_ask_item("soren", "say I know Soren, he is a mute. I do not know if "+
	"he was born that way, or made that way, but he is a nice man.");
    add_ask_item("taryn", "say I wish she did not aspire to be a mercenary "+
	"like me. She could do so much more.");

    add_ask_item(({"goblins", "goblin"}), "say I suppose they cannot help "+
	"what they are.");
    add_ask_item(({"skill", "skills", "training", "train" }), "say I can "+
	"train you in the ways of the world, both the wild and civilized.");
    add_ask_item(({"mercenary", "mercenaries", "guild", "join", "joining" }),
	"say It is Maligant that you seek on that matter, not I.");
    add_ask_item(({"halfling", "halflings", "hobbit", "hobbits", "kender"}),
	"say I think the child-like creatures are delightful, if a bit "+
	"mischievous.");
    add_ask_item(({"dwarf", "dwarves" }), "say I'll never understand why "+
	"dwarves try so hard to appear gruff.");
    add_ask_item(({"elf", "elves"}), "say I love the company of elves, they "+
	"share my respect and admiration for nature like no other race does.");
    add_ask_item(({"gnome", "gnomes"}), "say To be such bright little creatures "+
	"they sure do act foolishly at times.");
    add_ask_item(({"human", "humans"}), "say What of them? They are just "+
	"humans.");
        
    add_ask_item(({"background", "history", "past" }), "say What is my "+
	"history? My story is one of adventure and tragedy, like most, I "+
	"guess. I come from the faraway land of Gondor. My brother was a "+
	"soldier in the Army there, until his death. It took me a few years, "+
	"but I became a Ranger and tracked the one responsible down. He was "+
	"a treacherous officer in the Army. He had taken my brother away "+
	"from me, but I settled the debt at last. It cost me my position and "+
	"standing in Gondor, but I wouldn't change things even if I could." );

    set_default_answer( ({ "say I wouldn't know that, I'm afraid.", "say I "+
	"am uncertain of that.", "say I must say, I have no idea!", "say I "+
	"think perhaps you should seek the guidance of another on that matter."}));
}

void
intro_me(object name)
{
    command("smile soft");
    command("introduce me" );
    command("say It is a lovely day, good "+name->query_race_name()+
	". What can I do for you?");

}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
