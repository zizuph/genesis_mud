/*
 * Morgan, guild trainer of the Mercenaries Guild
 * 	by Morrigan, 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 * Updated again and used in the New Merc camp by Gorboth, 2009.
 */
#include "../merc_defs.h"

inherit "/d/Gondor/std/monster";

#include <ss_types.h>
#include <stdproperties.h>

void
create_gondor_monster()
{
    set_name("morgan");
    add_name("trainer");
    set_gender(1);
    set_title("the Wanderer, Recruiting Overseer of the Free Mercenary"
      + " Guild");
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

    add_ask_item("mellok", "say He agreed to be part of our operation"
      + " after we saved Sparkle from the goblins. You can find him"
      + " in the training yard.");
    add_ask_item("maligant", "say Maligant was our leader before he up"
      + " and abandoned us. If I see him I'll slit his throat myself.");
    add_ask_item("tarn", "say I think he was one of Maligant's friends, but "+
	"was definitely a skilled blacksmith. I haven't seen him for"
      + " a while now.");
    add_ask_item("dalizen", "say Dalizen? I don't miss him and I'm sure"
      + " he doesn't miss me.");
    add_ask_item("gnimpsh", "say Gnimpsh, the poor fellow ... he never got"
      + " over Maligant leaving. Unfortunately, he and I got into a bit"
      + " of a disagreement, and he seems to think I hate him now. He"
      + " sits back at the old camp and broods. Its a real pity.");
    add_ask_item("soren", "say I haven't seen Soren in years. I wonder"
      + " what became of him.");
    add_ask_item("taryn", "say I'm proud to say she finally got smart" 
      + " and sought a higher calling than being a Mercenary. Don't get"
      + " me wrong, but some people just shouldn't settle for this life.");

    add_ask_item(({"goblins", "goblin"}), "say I suppose they cannot help "+
	"what they are.");
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
    add_ask_item( ({ "guild", "mercs", "merc", "mercenary",
                     "mercenaries", "mercenary guild", "free mercenary",
                     "free mercenaries", "free mercenary guild" }),
        "say The Free Mercenary guild is ideal for those of us who wish to"
      + " take life into our own hands, and master those things which"
      + " interest us on our own terms. If you'd like to be one of us"
      + " you can <register> here. Members can <unregister> if they"
      + " wish to try their luck elsewhere.");
    add_ask_item( ({ "job" }),
        "say My job is to look over the registry and keep track of who"
      + " comes and goes from our membership.");
    add_ask_item( ({ "registry", "registration" }),
        "say The registry is right there on the table.");
    add_ask_item( ({ "desk" }),
        "say What about it? Never seen a table before?");
    add_ask_item( ({ "join", "joining", "joining the guild", }),
        "say To join the Free Mercenaries, one must <register> here.");
    add_ask_item( ({ "leave", "leaving", "leaving the guild" }),
        "say To leave the Free Mercenary Guild, one can simply, <unregister>"
      + " and go their own way. There is no penalty for doing so.");
    add_ask_item( ({ "register", "registry" }),
        "point large book");        

    add_ask_item(({"background", "history", "past" }), "say What is my "+
	"history? My story is one of adventure and tragedy, like most, I "+
	"guess. I come from the faraway land of Gondor. My brother was a "+
	"soldier in the Army there, until his death. It took me a few years, "+
	"but I became a Ranger and tracked the one responsible down. He was "+
	"a treacherous officer in the Army. He had taken my brother away "+
	"from me, but I settled the debt at last. It cost me my position and "+
	"standing in Gondor, but I wouldn't change things even if I could."
      + " I served for years under Maligant, helping to train his band"
      + " of Mercenaries. Once he showed his true colors and abandoned"
      + " us, I struck a deal with the Sparkle Magistrate who gave us this"
      + " place to use for our new operation. I'm no leader here, but I"
      + " do help oversee the registry." );

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
