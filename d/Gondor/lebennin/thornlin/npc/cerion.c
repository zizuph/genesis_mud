/*
 *	/d/Gondor/lebennin/thornlin/npc/cerion.c
 *
 *	Boromir stole this file from :
 *	The crook in the harbour, who hands out the drug for the drug-quest
 *	(Fredor)
 *
 *	Modification log:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
inherit "/std/monster.c";
inherit LIB_DIR + "logkill.c";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../ox_quest.h"
#include "attackers.c"

public void    walk_away();

int     report_c,
report_id;

void
create_monster()
{
    set_name("cerion");
    add_name(({"dunadan","farmer", "_thornlin_citizen"}));
    set_title("the learned farmer of Lossarnach");
    set_adj(({"grim-faced","short"}));
    set_race_name("human");
    set_living_name("cerion");
    set_long(BSN("This farmer of Lossarnach is shorter and "+
	"somewhat swarthier than the people of Gondor."));
    set_stats(({ 27, 32, 30, 24, 22, 25}));
    set_skill(SS_UNARM_COMBAT,56);
    set_skill(SS_WEP_KNIFE,70);
    set_skill(SS_DEFENCE,150);
    set_skill(SS_PARRY, 150);
    set_skill(SS_HIDE,   30);
    add_prop(CONT_I_WEIGHT,76000);
    add_prop(CONT_I_HEIGHT,179);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);

    set_act_time(7);
    add_act("say Greetings, stranger!");
    add_act("say Know anything about farming?");
    add_act("emote looks nervously at the clouds gathering in the east.");
    add_act("say I saw an orc once!! Aye, an orc!");
    add_act("say Lossarnach is beautiful country.");
    add_act("say They say Ithilien has good land for farming; too bad "+
      "no one uses it.");
    add_act("@@action_meet|say What brings you to Thornlin, |race|?@@");
    add_act("introduce me");
    add_act("Thornlin got lots of pigs...");
    add_act("@@action_meet|peer |name|@@");
    add_act("smile charm");
    add_act("laugh");
    add_act("emote looks at the sky as if he can read the weather.");

    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({"horn","hunting horn"}),VBFC_ME("inform_horn"));
    add_ask(({"ox","araw ox", "araw", }),VBFC_ME("inform_ox"));
    add_ask(({"hammer","your hammer"}),VBFC_ME("inform_hammer"));
    add_ask(({"home","your home"}),VBFC_ME("inform_home"));
    add_ask(({"for job","about job","job" }), VBFC_ME("tell_job"));
    add_ask(({"orc"}),VBFC_ME("tell_orc"));

    set_random_move(30);
}

string
action_meet(string txt, string what, string txt2)
{
    string  name;

    switch (what)
    {
    case "race":
	name = TP->query_race_name();
	break;
    case "name":
	name = TP->query_real_name();
	break;
    }

    return txt + name + txt2;
}

void
end_report()
{
    remove_alarm(report_id);
    report_id = 0;
    report_c = 0;
}

void
report_horn(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
	command("sigh");
	command("say I wasn't finished yet!");
	end_report();
    }

    switch(report_c++)
    {
    case 0:
	command("say A horn you say? As from an ox?");
	command("hmm");
	break;
    case 1:
	command("say Well, yes, you could say I have one, or rather my ox does.");
	command("say Have a horn that is...");
	command("think");
	break;
    case 2:
	command("say My ox should be slaughtered soon.");
	command("say But the butcher demands both horns of my ox just for killing it!");
	command("say That's outrageous, isn't it?");
	break;
    case 3:
	command("say But I don't dare to kill the ox myself!");
	command("say You have to be very quick, and you have to hit the right spot the first time!");
	command("emote trembles with fear at the thought.");
	break;
    case 4:
	command("say The last time I tried to kill an ox myself, the ox almost killed me.");
	command("sigh");
	break;
    case 5: break;
    case 6:
	command("peer "+tp->query_real_name());
	command("say Say, you look like you are strong and dexterous enough to do better than I did!");
	command("say Couldn't you kill the ox for me?");
	tp->add_prop(I_ASKED_HORN,1);
	break;
    case 7:
	command("say I would pay you with one of the horns!");
	command("say That's a very generous offer for just one little stroke, I think.");
	break;
    case 8:
	command("say Just hit the ox with a hammer and it will fall dead.");
	break;
    case 9:
	command("say If you are quick and hit the right place, that is.");
	break;
    case 10:
	command("say And please bring the second horn to me once you are finished.");
	command("say I'll go and talk to the butcher now.");
	command("say I'll still need him to cut up the meat.");
	command("wave " + tp->query_real_name());
	walk_away();
	set_alarm(3.0, 0.0, walk_away);
	break;
    default:
	end_report();
	break;
    }
}

string
inform_horn()
{
    if (report_id && sizeof(get_alarm(report_id)))
    {
	command("say Slowly, slowly, please don't interrupt me!");
	return "";
    }

    if (TP->query_prop(I_ASKED_HORN))
    {
	command("say I already told you what to do, didn't I?");
	command("say Just go and kill that ox for me, please!");
	command("say You may keep one of his horns, just bring the other one to me.");
	return "";
    }
    report_c = 0;
    report_id = set_alarm(1.0, 3.0, &report_horn(TP));
    return "";
}

string
inform_hammer()
{
    if (TP->query_prop(I_ASKED_HORN) || TP->query_prop(I_ASKED_HAMMER))
    {
	command("emote starts to search his equipment.");
	command("grumble");
	command("say Where did I leave my hammer?");
	command("scratch");
	command("think");
	command("say Can you find it for me? you will need it, too, I guess.");
	command("say I can't remember where I left it, maybe at home.");
	command("shrug");
	if (query_prop(I_ASKED_HORN))
	    TP->remove_prop(I_ASKED_HORN,1);
	TP->add_prop(I_ASKED_HAMMER,1);
	return "";
    }
    command("say A hammer?");
    command("say I don't know what you are talking about, please leave me in peace!"); 
    return "";
}

string
inform_home()
{
    if (TP->query_prop(I_ASKED_HAMMER))
    {
	command("say Questions, questions and questions!");
	command("grumble unhap");
	command("say When will I see some work done here ?");
	command("say The gods know I pay you well enough!");
	command("wink"+TP->query_real_name());
	command("shrug");
	command("emote think about how lazy the youth is nowadays.");
	command("emote shakes his head in disappointment.");
	return "";
    }
    command("say What is of your business ?");
    TO->walk_away(); 
    return "";
}

string
inform_ox()
{
    if (report_id && sizeof(get_alarm(report_id)))
    {
	command("say Slowly, slowly, please don't interrupt me!");
	return "";
    }

    command("ponder");
    command("say An ox?");
    command("say Yes, I own an Araw ox.");
    command("say They are actually rather rare so far south.");
    command("say You know, the heir of the Steward of Gondor has an ancient "
      + "hunting horn made from the horn of an Araw ox!");
    command("say My ox got some fine horns too, long as usual with Araw oxen.");
    command("say The Araw ox is said to be the most royal type of cattle "+
      "there is");
    report_c = 2;
    report_id = set_alarm(10.0 + 10.0*rnd(), 3.0, &report_horn(TP));
    return "";
}


string
tell_job()
{
    command("say My job? Well I am a farmer...");
    command("chuckle");
    return "";
}

string
tell_orc()
{
    command("close first door");
    command("say The orc..., it was a real living one...");
    command("say Come by for pork chops next week, say Sunday?");
    command("think");
    command("say Yes, Sunday it is at 'The Lost Pig'!");
    command("say You are buying!");
    command("close second door");
    TO->walk_away();
    return "";
}

string
def_answer()
{
    command("say I beg your pardon?");
    command("peer " + TP->query_real_name());
    command("say I'm afraid I didn't understand you.");
    command("say Perhaps you could repeat that in less and simpler words?");
    command("smile charmingly " + TP->query_real_name());
    return "";
}

void
return_object(object ob, object who)
{
    if (ob->id("coin"))
    {
	command("gasp");
	command("say Why, thank you, my dear "
	  + (who->query_gender() ? "Lady" : "Sir") + "!");
	command("thank "+who->query_real_name());
	command("say It will help my family!");
	command("smile");
	return;
    }
    if (ob->id("hammer"))
    {
	command("say Just a good whack between the horns.");
	command("say I think you can do it.");
	command("give "+ob->query_name()+" to "+who->query_real_name());
	command("wave");
	return;
    }

    if (objectp(who) && present(who, ENV(TO)))
    {
	command("give "+ob->query_name()+" to "+who->query_real_name());
	command("say What was that for?");
    }
    else
    {
	command("drop "+ob->query_name());
	command("shrug");
	command("say What should I do with it?");
    }
}

varargs void
check_horn(object horn, object tp, int damaged = 0)
{
    string  name;

    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
	command("shrug");
	return;
    }

    if (damaged)
    {
	command("say But the horn is damaged!");
	command("say What did you do?");
	command("say Can't you kill an ox without damaging the horns?");
	command("say Get out of my sight, you clumsy fool!");
    }
    else
    {
	if (!tp->query_prop(I_KILLED_OX))
	{
	    command("hmm");
	    command("say Where did you get this horn?");
	    command("say You didn't kill my ox, that much is certain!");
	    command("peer "+tp->query_real_name());
	    command("say What are you up to? Nothing good, I bet!");
	    command("say You'd better leave!");
	}
	else if (tp->query_prop(I_ASKED_HORN) || tp->query_prop(I_ASKED_HAMMER))
	{
	    command("smile "+(name = tp->query_real_name()));
	    command("say Ah, did you kill my ox?");
	    command("say Thank you for bringing me the horn!");
	    command("shake "+name);
	    command("thank "+name);
	    command("say As agreed, you may keep the other one!");
	    tp->add_prop(THORNLIN_I_SOLVED_OX_QUEST, 1);
	}
	else if (tp->query_prop(THORNLIN_I_SOLVED_OX_QUEST))
	{
	    command("say You do not want to keep the horn as payment?");
	    command("thank "+(name = tp->query_real_name()));
	    command("say You are a most generous and helpful "
	      + (tp->query_gender() ? "gentleman":"lady")+"!");
	    command("smile "+name);
	    command("say Thank you very much!");
	}
	else
	{
	    command("gasp");
	    command("say Where did you get that horn?");
	    command("say Did you kill my Araw ox?");
	    command("scream");
	    command("say That ox was worth a fortune!");
	    command("say You thief!");
	    command("kick "+tp->query_real_name());
	    command("shout Help! Help! Brigands! Thieves!");
	}
    }

    tp->remove_prop(I_ASKED_HORN);
    tp->remove_prop(I_ASKED_HAMMER);

    horn->remove_object();
    return;
}

void
check_hammer(object hammer, object tp)
{
    if (!present(tp, ENV(TO)))
	return;

    command("emote looks at the hammer.");
    command("say Why, thank you!");
    command("thank "+tp->query_real_name());
    command("say This looks like it's my hammer indeed.");

    if (!tp->query_prop(I_ASKED_HAMMER))
    {
	command("say Thank you very much.");
	command("wave");
	set_alarm(10.0, 0.0, walk_away);
	set_alarm(60.0 + 180.0 * rnd(), 0.0, &command("hide hammer"));
    }
    else
    {
	command("say You will need it to kill my ox, though.");
	set_alarm(2.0, 0.0, &return_object(hammer, tp));
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !interactive(from))
	return;

    if (ob->id(THORNLIN_OX_DAMAGED_HORN))
	set_alarm(2.0, 0.0, &check_horn(ob, from, 1));
    else if (ob->id(THORNLIN_OX_HORN))
	set_alarm(2.0, 0.0, &check_horn(ob, from));
    else if (ob->id("hammer"))
	set_alarm(2.0, 0.0, &check_hammer(ob, from));
    else
	set_alarm(2.0, 0.0, &return_object(ob, from));
}

mixed
oke_to_move(string exit)
{
    if (report_id && sizeof(get_alarm(report_id)))
	return 0;
    return ::oke_to_move(exit);
}

public void
walk_away()
{
    int     ndir;
    mixed   dirs;
    string  dir = query_prop(LIVE_S_LAST_MOVE);

    dirs = ENV(TO)->query_exit();
    if (!sizeof(dirs))
	return;

    if (!stringp(dir))
	dir = dirs[random(sizeof(dirs) / 3) * 3 + 1];
    else if (sizeof(dirs) == 3)
	dir = dirs[1];
    else if (member_array(dir, dirs) < 0)
    {
	while (sizeof(dirs))
	{
	    ndir = random(sizeof(dirs) / 3) * 3;
	    if (dirs[ndir] == file_name(query_prop(LIVE_O_LAST_ROOM)))
		dirs = exclude_array(dirs, ndir, ndir + 2);
	    else
	    {
		dir = dirs[ndir + 1];
		break;
	    }
	}
    }
    command(dir);
}
