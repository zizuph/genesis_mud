/*
 * Mercenary Lord Armoury Keeper, by Morrigan 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 */
#include "../merc.h"

inherit MERC_KRYNN_NPC
inherit MERC_KRYNN_BRIBE 

#include "attackers.h"

string *gIntroduced = ({});

string bribe_level() {}

string reveal_item()
{
    return environment(this_object())->reveal_item(this_player());
}

string show_list()
{
    return environment(this_object())->show_list(this_player());
}

string get_random_item()
{
    return environment(this_object())->get_random_item(this_player());
}

string get_specific_item()
{
    return environment(this_object())->get_specific_item(this_player());
}

string enable_transfer()
{
    string name;

    name = this_player()->query_real_name();
    if(MCREST->query_crest_lord(name))
    {
        MCREST->set_private_rack_transfer(name, 1);
        return "say Very well, I will transfer your causes posessions to " +
            "the public racks five minutes before the world refreshes.";
    }
    else
    {
        return "say You will have to ask the lord of your cause to " +
            "enable transfers.";
    }
}

string disable_transfer()
{
    string name;

    name = this_player()->query_real_name();
    if(MCREST->query_crest_lord(name))
    {
        MCREST->set_private_rack_transfer(name, 0);
        return "say Very well, I will no longer transfer your causes " +
            "posessions to the public racks before the world refreshes.";
    }
    else
    {
        return "say You will have to ask the lord of your cause to " +
            "disable transfers.";
    }
}

void
create_krynn_monster()
{
    set_name("corwin");
    set_title("Goldfinger, the Armoury Master of the Mercenaries");
    add_name(({ "master", "keeper" }));
    set_race_name("dwarf");
    set_long("A strange looking little dwarf, with pale skin and large, "+
	"bulging dark eyes. His hair is almost white, although he does "+
	"not look extraordinarily old by dwarven standards. He is less "+
	"stocky than most dwarves, almost wiry by comparison. His dark "+
	"eyes appear very keen and alert, however, and more than a little "+
	"shifty.\n");
    set_adj(({"pale", "dark-eyed"}));
    set_stats(({ 130, 70, 140, 100, 100, 130}));
    set_skill(SS_AWARENESS,   65);
    set_skill(SS_HIDE,        25);
    set_skill(SS_DEFENCE,     74);
    set_skill(SS_PARRY,       74);
    set_skill(SS_WEP_CLUB,        90);
    set_alignment(-350);

    add_ask(({"enable transfer", "enable transfers"}), enable_transfer, 1);
    add_ask(({"disable transfer", "disable transfers"}), disable_transfer, 1);
    add_ask(({"refreshing", "transfers", "armageddon"}),
        "say At the refreshing of the lands, I transfer items from the " +
        "private racks to the public racks, if the lord of the cause " +
        "wishes so. Just ask me to enable or disable transfers.", 1);

    add_ask( ({ "morgan" }),
        "say They say she's left too. I care not.", 1);
    add_ask(({"mercenary", "mercenaries"}),
        "say If you don't know what a mercenary is, you're dumber than a "+
	    "miserable gully dwarf.", 1);
    add_ask(({ "money", "steal", "bribe" }), "asay quietly "+
	" I guess we could "+
	"come to some kind of arrangement. Money talks, as they say.", 1);
    add_ask(({ "maligant" }), "say Who needs him? He left. The camp is"
      + " ours now!", 1);
    add_ask(({ "dalizen" }), "say You can't ever trust a damned elf.", 1);
    add_ask("tarn", "say He's a fair enough smithy.", 1);
    add_ask(({"background", "history", "past" }), "say My past? Why "+
	"do you want to know, anyway? It wasn't all rose petals and ginger "+
	"snaps, so you know. I worked as hard as anyone else, the world "+
	"just didn't seem to notice when it came time for my rewards. So "+
	"I figured the world owed me one, and since then I've never had "+
	"any qualms with taking what isn't mine.", 1 );

    set_default_answer( ({ "say I am busy, go away.", "say Give me a break, will "+
	" ya?",
        "say Go pester Gnimpsh with your questions!", "emote looks at you angrily.",
        "say Money talks, as they say.", "emote totally ignores the question.",
	"emote checks his book of transactions." }), 1 );

    set_bribe( ({ 1, "You have got to be kidding me, do you think I'll risk my "+
                     "neck for that paltry sum??",
                  144, "Great Reorx! What are we up to now, two copper coins?",
                  1728, "We might be getting somewhere now, but I'm taking a "+
		     "big risk, and you have to make it worth my while!",
		  3456, reveal_item,
                  8640, show_list,
                  69120, get_random_item,
                  172800, get_specific_item }) );
}

void
init_living()
{
    ::init_living();
    init_bribe();
}

void
intro_me(object name)
{
    if (member_array(capitalize(name->query_real_name()), gIntroduced) == -1)
    {
        command("introduce me to " + OB_NAME(name));
        command("say to " + OB_NAME(name) + " How can I help you?");
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
