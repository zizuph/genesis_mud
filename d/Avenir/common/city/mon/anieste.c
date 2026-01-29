// file name:	anieste.c
// creator(s):	Lilith Feb 2003
// purpose:	      Gatekeeper for First Gate, inside
/*
 * Revisions:
 * 	Lucius, Sep 2017: Cleanups - add team support.
 */
#pragma strict_types
inherit "/d/Avenir/inherit/monster";

#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#define TP	this_player()
#define TO	this_object()

public object *transit;
public int alarm_id, gate_alarm;


public void
create_monster(void)
{
    set_name("anieste");
    add_name(({"priest","keeper","gatekeeper", "priestess", "anchorite"}));

    set_living_name("Anieste");
    set_title("dei Cha'rui, Anchorite of Salilus");
    set_race_name("elf");
    set_adj("dignified");
    add_adj("priestly");
    set_long("She is young, yet quite dignified.\n"+
        "She stands out amongst all the martial types "+
        "surrounding her as a priest or cleric of some sort.\n");

    set_stats(({95, 85, 90, 130, 130, 130}));
    set_alignment(0);
    set_appearance_offset(0);
    set_gender(G_FEMALE);

    set_knight_prestige(-1);
    MAKE_SYBARITE;
    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_WEIGHT, 35000);

    set_skill(SS_DEFENSE, 90);
    set_skill(SS_AWARENESS, 90);

    set_act_time(3);
    add_act("emote smoothes her burnous.");
    add_act("emote has an inward-looking stare.");
    add_act("emote smiles piously to herself.");
    add_act("emote appears to be rehearsing something in her mind.");
    add_act("emote stares up at the Source.");

    set_chat_time(10);
    set_cact_time(10);
    add_cact("shout Die for this! Die!");
    add_cact("snarl enemy");

    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	"say There are two markets: the one for outlanders, and "+
	"the one for sybarites.  You passed through the bazaar "+
	"to get here. That one is for outlanders. The merchantile "+
	"pale is what sybarites use most.", 1);
    add_ask(({"park","island", "holm"}),
	"say The Holm of the Icondite is where the shadow-elves Hunt. "+
	"They're pretty particular about who they let on that island "+
	"and when, but then I expect you know that by now.",1);
    add_ask(({"gate","key", "first gate"}),
	"say I am the key to this gate. If you want me to open the "+
	"gate, simply ask me to do so.",1);
    add_ask(({"coin", "sybarun coin", "token"}),
	"say The sybarun coin is a token which grants the bearer "+
	"(and usually only the bearer, mind you) access to restrict"+
	"ed areas of Sybarus, like the Holm, or the City.\n", 1);
    add_ask(({"give me the key","give key"}), "shout I am the key!", 1);
    add_ask(({"bath", "melchior's bath"}),
	"say It is nearby. A marvellous place.",1);
    add_ask(({"sybarus","bazaar"}),
	"say It is over the Bridge of Sighs.",1);
    add_ask(({"bridge","bridge of sighs"}),
	"say It is the link between the City and the Bazaar.",1);
    add_ask(({"forbidden city", "city"}),
	"say You stand just inside the gate to the Forbidden City.", 1);
    add_ask(({"name", "your name", "house"}), "introduce myself", 1);
    add_ask(({"task", "job", "quest", "help"}), "@@give_task@@");
    add_ask(({"infidel", "infidels"}),
	"say The wretched Infidels have a hideout somewhere "+
	"on Bazaar Island.",1);
    add_ask(({"faithful", "faithfuls"}),
	"say The Faithful serve the Will of the Gods.",1);
    add_ask(({"master", "god", "idrys"}), "say My master is Salilus.", 1);
    add_ask(({"salilus"}),
	"say Salilus is the God of the First Hour.", 1);
    add_ask(({"priest","priestess", "anchorite", "guild"}),
	"say I am an Anchorite of Salilus, a priestess who has dedicated "+
	"her life to serving His Will.", 1);
    add_ask(({"union", "shadow union", "shadow warrior"}), "@@union_ask@@");
    add_ask(({"dej-minha"}),
	"say They are the Hegemon's. They answer only to him. "+
	"I would not cross the dej-minha, were I you.", 1);
    add_ask(({"jadestone", "jadestone doll"}),
	"say Some say she angered the Hegemon and he lent her out to "+
	"the Inquisitors. So she's off in the Bazaar, cooling her heels.", 1);

    add_ask(({"leave","open the gate","to open the gate","open gate",
	    "to open gate","leave"}), "@@do_open@@");

    set_default_answer("@@what_me@@");

    MONEY_MAKE_SC(random(11))->move(TO);
    MONEY_MAKE_CC(random(5))->move(TO);
    equip(({HOLM + "obj/burnous"}));
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(2.0, 0.0, &command("shout You DARE attack ME?!"));
}

public int
query_not_attack_me(object who, int aid)
{
     /* This will block any and all attacks */
     who->catch_msg(QCTNAME(TO) +" is somehow immune to "+
	 "your attack.\n");
     command("emote seems to be quite pleased with herself.");
     return 1;
}

public void
do_sequence(string *seq)
{
    if (sizeof(seq) > 1)
        gate_alarm = set_alarm(2.0, 0.0, &do_sequence(seq[1..]));
    else
	gate_alarm = 0;

    command(seq[0]);
}

public void
open_sez_me(void)
{
    transit = filter(filter(transit, objectp),
	&operator(==)(environment(TO)) @ environment);

    transit->move_living("through the gate", BAZAAR+"admin/a18", 1, 0);
    transit = 0;
}

public string
do_open(void)
{
    if (IS_INFIDEL(TP))
    {
        command("say You have sinned against the Gods!");
        command("say Do you think would I put my own re-birth "+
            "at risk to help you?!");
        command("spit "+ TP->query_real_name());
        return "";
    }

    if (gate_alarm)
    {
	if (pointerp(transit) && !IN_ARRAY(TP, transit))
	{
	    transit += ({ TP });
	    command("nod slightly "+ TP->query_real_name());
	}
	return "";
    }

    transit = ({ TP }) + TP->query_team();

    gate_alarm = set_alarm(1.0, 0.0, &do_sequence(({
		"emote closes her eyes for a moment.",
		"emote pronounces a string of words and places "+
		"her hand against the granite slab of the gate.",
		"emote smiles at the hole that has suddenly appeared "+
		"in the solid stone.",
		"say Go in peace.",
		"",
		"emote waves her hand and the portal closes."
		})));
    set_alarm(8.0, 0.0, open_sez_me);
    return "";
}

/* default answer to questions */
public string
what_me(void)
{
    if (!CAN_SEE(TO, TP))
    {
	command("say My God speaks to me in another voice. "+
	    "What trickery are you about, that you would ask "+
	    "me questions when I cannot see whom I would asnwer?");
	return "";
    }

    if (IS_INFIDEL(TP))
    {
        command("frown pious");
        command("say You dare to address me, you filthy infidel?");
        return "";
    }

    switch(random(5))
    {
    case 0:
	command("laugh .");
	command("say You can't really be expecting me to answer that!");
	break;
    case 1:
	command("say I would not presume to offer an opinion on that.");
	command("smile tight");
	break;
    case 2:
	command("say I am not the person to ask that of. I am but "+
	    "a humble priestess, a servant of Salilus.");
	break;
    case 3:
	command("say It is the questions in life that motivate us. "+
	    "Do you really want an answer to that?");
	command("frown");
	break;
    case 4:
	command("say Knowledge is Power. Why should I empower you?");
	command("wave air");
	break;
    }
    return "";
}

public string
union_ask(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");
    }
    else if (IS_SYBARITE(TP))
    {
        command("whisper to "+ TP->query_real_name() +
	    " I can tell you nothing more than what is known to all:");
    }
    else
    {
	command("say It is a Union of Shadow Warriors, bound to serve "+
	    "Jazur and protect the interests of Sybarus.");
    }
    return "";
}

/*
 *   Code relating to quests
 */
public string
give_task(void)
{
    command("say That which I need done cannot be achieved by another.");
    command("say Ask again later, and perhaps I will have "+
        "need of you then.");
    return "";
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
public void
check_meet(object tp)
{
    int i = random(15);
    string occ = tp->query_guild_name_occ(),
	   name = tp->query_real_name();

    if (!present(tp, environment(TO)))
	return;

    if (IS_INFIDEL(tp))
    {
        command("shout Guards! We have an infidel amongst us!");
        return;
    }

    if (occ == OUNION)
    {
	if (i == 0)
	{
            command("say to "+ name +" Celebrate the Source!");
	}
	else if (i == 2)
	{
            command("greet "+ name);
	}
	else if (i == 5)
	{
            command("say to "+ name +
		" I have heard mention of your exploits.");
	}
    }
    else if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i < 4)
	{
            command("say to "+ name +" Are you on the roster "+
		"for the Ziggurat today?");
	}
    }
    else if (IS_SYBARITE(tp))
    {
        if (i < 7)
	{
            command("bow respect "+ name);
	}
	else if (i == 7)
	{
            command("smile joy "+ name);
	}
	else if (i > 7)
	{
            command("say to "+ name +
		" May the Gods smile upon you this day.");
	}
    }
    else if (i > 5)
    {
	command("say Celebrate the Source, Outlander.");
    }
}

public void
init_living(void)
{
    ::init_living();

    /* If the living is a player and I can see him ... */
    if (!alarm_id && interactive(TP) && CAN_SEE(TO, TP))
	alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
}
