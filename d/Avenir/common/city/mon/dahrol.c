// file name:	dahrol.c
// creator(s):	Lilith Feb 2003
// purpose:	      Gatekeeper for First Gate, outside
/*
 * Revisions:
 * 	Lucius, Sep 2017: Cleanups - add team support.
 */
#pragma strict_types

inherit "/d/Avenir/inherit/monster";

#include <ss_types.h>
#include <money.h>
#include <macros.h>

#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/relation.h"

#define NO_SYB_COIN 0

#define TP	this_player()
#define TO	this_object()

public object *transit;
public int alarm_id, gate_alarm;


public void
create_monster(void)
{
    set_name("dahrol");
    add_name(({"keeper", "gatekeeper", "priest", "anchorite"}));

    set_living_name("Dahrol");
    set_title("icu Wer'a, Anchorite of Salilus");
    set_race_name("human");
    set_adj("majestic");
    add_adj("priestly");
    set_long("He is a dignified fellow, who stands out "+
       "amongst all the martial types as a priest or cleric "+
       "of some sort.\n");

    set_stats(({95, 85, 90, 130, 130, 130}));
    add_prop(OBJ_M_NO_MAGIC, "The Idrys protect those who serve.\n");
    set_alignment(0);
    set_knight_prestige(-1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    MAKE_SYBARITE;
    KILL_THIEF;

    set_skill(SS_DEFENSE, 90 );
    set_skill(SS_AWARENESS, 90);

    set_act_time(3);
    add_act("emote smoothes his robe.");
    add_act("emote has an inward-looking stare.");
    add_act("emote smiles piously to himself.");
    add_act("emote appears to be rehearsing something in his mind.");
    add_act("emote stares up at the Source.");

    set_chat_time(10);
    set_cact_time(10);
    add_cact("shout Die for this! Die!");
    add_cact("snarl enemy");

    set_default_answer("@@what_me@@");
    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	"say There are two markets: the one for outlanders, and "+
	"the one for sybarites.  You passed through the bazaar "+
	"to get here. That one is for outlanders. The merchantile "+
	"pale is what sybarites use most.", 1);
    add_ask(({"park","island", "holm"}),
	"say The Holm of the Icondite is where the shadow-elves Hunt. "+
         "They're pretty particular about who they let on that island "+
         "and when, but then I expect you know that by now.", 1);
    add_ask(({"gate","key", "first gate"}),
         "say I am the key to this gate. If you want me to open the "+
         "gate, you must give me proof that you have earned it: "+
         "a sybarun coin.",1);
    add_ask(({"coin", "sybarun coin", "token"}),
         "say The sybarun coin is a token which grants the bearer "+
         "(and usually only the bearer, mind you) access to restrict"+
         "ed areas of Sybarus, like the Holm, or the City.", 1);
    add_ask(({"open the gate","to open the gate","open gate",
         "to open gate","enter","enter gate"}),
         "say If you have earned access to the City, you have upon "+
         "your person a sybarun coin. Give it to me and I shall "+
         "open the way for you, and you alone.", 1);
    add_ask(({"give me the key","give key"}), "shout I am the key!",1);
    add_ask(({"bath", "melchior's bath"}),
        "say It is just through the gate. A marvellous place.",1);
    add_ask(({"sybarus","bazaar"}),
        "say It is over the Bridge of Sighs.",1);
    add_ask(({"forbidden city", "city"}), 
        "say You stand just outside the gate to the Forbidden City.", 1);
    add_ask(({"name", "your name", "house"}), "introduce myself", 1); 
    add_ask(({"task", "job", "quest", "help"}), "@@give_task@@");
    add_ask(({"infidel", "infidels"}),
        "say The wretched Infidels have a hideout somewhere "+
        "on Bazaar Island.",1);
    add_ask(({"faithful","faithfuls",}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"master", "god"}), "say My master is Salilus.", 1);
    add_ask(({"salilus"}),
        "say Salilus is the God of the First Hour.", 1);
    add_ask(({"dej-minha", "dej", "minha", "dej minha"}), 
        "say They are the Hegemon's. They answer only to him. "+
        "I would not cross the dej-minha, were I you.", 1);
    add_ask(({"priest", "anchorite"}),
        "say I am an Anchorite of Salilus, a priest who has dedicated "+
        "his life to serving His Will.", 1);

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

    transit->move_living("through the gate",
	CITY+"entry/courtyard", 1, 0);
    transit = 0;
}

public void 
drop_unwanted(object what, object who)
{
    if (!what)
	return;

    command("peer "+ who->query_real_name());
    if (!command("give "+ OB_NAME(what) +" to "+ who->query_real_name()))
        what->remove_object();  
}

public void
remove_tokens(void)
{
    present("_sybarun_token")->remove_object();
}

public void
open_gate(object who, object ob)
{
    set_alarm(3.0, 0.0, remove_tokens);

    if (IS_INFIDEL(who))
    {
        command("growl");
        command("say You have one of these, yet you are marked by "+
            "Plalgus? Did you think you could get by me??");
        command("shout Guards! We've an infidel on the loose!");
        return;
    }

    if (gate_alarm)
    {
	if (pointerp(transit) && !IN_ARRAY(who, transit))
	    transit += ({ who });

	set_alarm(0.5, 0.0,
	    &command("emote silently pockets a sybarun coin."));
	return;
    }

    transit = ({ who }) + who->query_team();

    gate_alarm = set_alarm(1.0, 0.0, &do_sequence(({
                 "emote subtly smells the sybarun coin.",
                 "say How fortunate you are, to have such a token "+
                 "of approval.",
                 "emote pronounces a string of words and places "+
                 "his hand against the granite slab of the gate.",
                 "emote smiles at the hole that has suddenly appeared "+
                 "in the solid stone.",
                 "",
                 "emote waves his hand and the opening closes." 
		})));
    set_alarm(9.0, 0.0, open_sez_me);
}

public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (!interactive(from))
	return;

    if (!to->id("_sybarun_token"))
        set_alarm(2.0, 0.0, &drop_unwanted(to, from));
    else
	set_alarm(1.0, 0.0, &open_gate(from, to));
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
