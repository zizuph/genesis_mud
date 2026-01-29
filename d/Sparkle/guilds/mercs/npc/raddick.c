/*
 * Mercenary guild recruiter, by Morrigan 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_GONDOR_NPC

#include "attackers.h"

string *gIntroduced = ({});

string attack_func()
{
    write("The arena is filled with the deafening sound of "+
        this_object()->query_the_name(this_player())+"'s laughter.\n");
    tell_room(environment(this_object()), "The arena is filled with the "+
	"deafening sound of "+QTNAME(this_object())+"'s laughter.\n", 
	this_player());
    command("asay mock Perhaps another time... For now, I must focus "+
	"on my duties of not letting people die.");
    return "";
}

void
create_gondor_monster()
{
    set_name("raddick");
    set_title("Rockjaw, Overseer of the Battlegrounds");
    add_name("overseer");
    set_race_name("half-ogre");
    set_long("A huge, muscular man, only he's not a man. He looks almost "+
	"human, but his features are a bit more crude, and his build too "+
	"impossibly big to be a human's. He is nearly bald, with only a "+
	"few whisps of reddish brown hair left. His eyes are a medium brown, "+
	"and very alert. Taller than the average man, he is as stocky as a "+
	"well-built dwarf. Long, powerful legs carry him as he patrols "+
	"the arena, swinging his great, hulking arms with his long strides.\n");
    set_short("mighty male half-ogre");
    set_adj(({"huge", "tall", "mighty"}));
    set_stats(({ 200, 160, 200, 75, 75, 140 }));
    set_skill(SS_AWARENESS,   65);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       75);

    set_alignment(0);

    add_prop(OBJ_M_NO_ATTACK, &attack_func());
    add_prop(OBJ_M_NO_MAGIC_ATTACK, &attack_func());

    add_ask_item(({"mercenary", "mercenaries", "others", "guests", "enter" }),
        "say Mercenaries may come here to fight, or may lead others here in "+
	   "their teams.");
    add_ask_item(({"arena", "fight", "fights", "fighting" }), 
	"say All fights in this "+
	"arena are under my discretion. When I say stop, you stop, or I stop "+	
	"you. Take your pick.");
    add_ask_item(({"discretion", "death", "kill", "kills", "killed" }), 
	"say I don't care if you get beat half to death, it's just my job "+
	"to keep you alive. That's the way Maligant wants it.");

    add_ask_item(({ "maligant" }), "say If he doesn't want to stick"
      + " around, I say let him go and forget the bastard!");
    add_ask_item(({ "dalizen" }), "say I'd like to meet him in here, and "+
	"see how graceful he is when I'm crushing his puny elven skull.");
    add_ask_item("taryn", "say I like Taryn, I hope she doesn't get hurt.");
    add_ask_item("tarn", "say Tarn makes me big clubs to smash things with.");
    add_ask_item("soren", "say He never talks, so I don't know anything about "+
	"him.");
    add_ask_item("morgan", "say Gone. I don't care. She never did any of"
      + " the REAL work anyway. Fighters we need ... scouts? Bah.");

    add_ask_item(({"background", "history", "past" }), "say I was a mighty "+
	"gladiator of Athas for many years. Sometimes I still miss the life "+
	"but for now this is my home. I won my freedom in the arena there, "+
	"defeating three monsters that resembled overgrown scorpions. I "+
	"left the life and happened upon Maligant, who offered me a job "+
	"here as his overseer. I get to do some fun things on the side "+
	"for him, too. Hope that you won't ever learn just what those are." );

    set_default_answer( ({ "say If it's not about fighting, I don't care.",
	"say Only ask me about arena stuff!", "say Quit talking and fight.",
	"say Too much talk, too little violence.", "say Let's get a fight "+
	"started here.", "say This is my arena."  }) );
}

void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
	command("emote strikes his chest with his mighty fist.");
        command("introduce me to " + OB_NAME(name));

        gIntroduced += ({ capitalize(name->query_real_name()) });
    }
}

void
add_introduced(string str)
{
    object who = find_living(str);
    string name = capitalize(who->query_real_name());

    if (member_array(name, gIntroduced) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}
