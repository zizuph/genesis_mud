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

void
create_gondor_monster()
{
    set_name("bryce");
    set_title("Hawthorn of Solanthus");
    add_name("herald");
    set_race_name("human");
    set_long("A tall, slender man of modest build and refined grace. His "+
	"eyes are dark, his nose rather sharp, and his jaw prominent. Dark "+
	"hair is cut short in the front, and hangs nearly to his collar "+
	"in the back.\n");
    set_short("tall dark-haired male human");
    set_adj(({"dark-haired", "tall", "slender"}));
    set_stats(({ 100, 100, 100, 100, 100, 100 }));
    set_skill(SS_AWARENESS,   65);
    set_skill(SS_DEFENCE,     75);
    set_skill(SS_PARRY,       75);
    set_alignment(750);

    add_ask_item(({"mercenary", "mercenaries"}),
        "say I never thought I would call myself a mercenary, but here "+
	    "I am, nonetheless.");
    add_ask_item(({"statue", "statues"}),
        "say The gnome who sculpts the statues is quite skilled at his "+
	   "art. I cannot recall his name, though?");
    add_ask_item(({"hire", "mercenaries for hire", "available mercenaries"}),
	"say Maligant's mercenaries has become so prosperous, there should "+
	    "never be a shortage of mercenaries for hire.");
    add_ask_item(({"background", "history", "past" }), "say I was an aspiring "+
	"Knight "+
	"of Solamnia long ago. I was a Squire to a ranking member of my "+
	"family, but he fell into disgrace because of his love of women. I "+
	"guess my future went down with him, at least in Solamnia. I always "+
	"had a love for heraldry, I guess that's why I'm here." );
    add_ask_item(({"crest", "crests" }), "say Once a mercenary becomes famous "+
	"enough, he or she can become an aspiring lord or lady by declaring "+
	"a crest here for their cause. The crests are symbolic of the lord "+
	"or the cause, generally.");
    add_ask_item(({"lord", "lady", "aspiring lord", "aspiring lady"}), "say "+
	"The process of becoming a Lord is fairly straight forward. One must "+
	"first establish a crest and a cause here in the book of heraldry, "+
	"and then it is simply a matter of enlisting a following. After all "+
	"one cannot be a lord over men, if there are no men to lord over. I "+
	"know the requirements that Maligant has decided upon, if you want "+
	"to ask me about them.");
    add_ask_item(({"warlord", "warlady"}), "say Very few Lords reach the level "+
	"of Warlord, which requires a much larger following than Lord level. "+
	"Warlords generally have more than "+WARLORD_FOLLOWING+" followers.");
    add_ask_item(({"requirement", "requirements"}), "say Currently, Maligant "+
	"has deemed that to be a Lord, one must have at least "+LORD_FOLLOWING+
	" dedicated followers, and be of sufficient level to establish a cause "+
	"or have been declared a successor to an already established cause.");
    add_ask_item(({"successor"}), "say Sometimes a Lord moves on, and for his "+
	"cause to continue to thrive, he must announce a successor.");

    add_ask_item(({ "maligant" }), "say Well, he left, didn't he? What"
      + " does that say about him? Hmmmph!");
    add_ask_item(({ "dalizen" }), "say I tend to be distrustful of elves, but "+
	"Dalizen seems to warrant suspicion even more than most.");
    add_ask_item("taryn", "say If she keeps up her practice, she'll be quite "+
	"the swordswoman when she grows up.");
    add_ask_item("tarn", "say Tarn is a fine smith, and a hard worker.");
    add_ask_item("soren", "say Soren is a quiet one, I don't know him very "+
	"well, but something tells me that there is more to him than just "+
	"tending a shop.");
    add_ask_item("morgan", "say I am very fond of Morgan, but who isn't? She "+
	"is all that an adventurous woman should be, in my opinion. If"
      + " only she would have stuck around.");

    set_default_answer( ({ "say I don't know much about that, why don't you "+
	"try asking someone else?", "say That's not for me to speak about.",
	"say I couldn't say one way or the other, honestly.", "say Who knows, "+
	"certainly not I!", "say I wonder the same things sometimes.", 
	"say I once met a kender but asked nearly as many questions as you!",
	"say I really couldn't say." }) );
}

void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
	command("emote bows with a refined grace.");
        command("introduce me to " + OB_NAME(name));
        command("say to " + OB_NAME(name) + " Good day to you, " +
	    (name->query_gender() == 1 ? "milady" : "milord")+".");

        if (name->query_gender() == 1)
	{
	    tell_room(environment(this_object()), QCTNAME(this_object())+
	        " takes "+QTNAME(name)+"'s hand and gently kisses it.\n", name);
	    name->catch_tell(this_object()->query_The_name(name)+" takes your "+
		"hand and gently kisses it.\n");
	}

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
