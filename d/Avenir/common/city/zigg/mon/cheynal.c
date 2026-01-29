/*
 * - cheynal.c
 *
 */
#pragma no_inherit
#pragma strict_types

#include "zigg.h"

inherit ZIG_NPC;
inherit QUEST;

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../obj/perfume.h"

private static mapping m_sold, m_idle;
private static int am_busy, alarm, count, reset, t_alarm;

#define CHECK_QUEST(x) \
    (x)->test_bit("Avenir", ZQ_GROUP, ZQB_PERFUME)

private static mapping questors = ([]);

/* Indices into the m_sold mapping arrays. */
#define ORDER      0
#define OSCENT     1
#define BOTTLE     2
#define ODESIGN    3
#define SCRIPT     4
#define OTIME      5

#define IVAL      5.0

/*
 * Npc questions are located here.
 *
 * - The questions should first check the am_busy flag and most likely
 *   refuse to answer any questions.
 */

public string
ask_seq(string *ask, int count = 0, object tp = TP)
{
    set_this_player(tp);  
  
    if (count == 0 && am_busy)
    {
        command("emote is too busy to answer right now.");
        return "";
    }
        
    am_busy = 0;

    if (ENV(TO) != ENV(tp))
        return "";
    	
    command(ask[count]);
    
    if (++count != sizeof(ask))
	am_busy = set_alarm(2.5, 0.0, &ask_seq(ask, count, tp));
    
    return "";
} 

/* Player looking for a quest. */
private string
ask_quest(void)
{
    string oname = OB_NAME(TP);

    if (am_busy)
    {
        command("emote is too busy to answer right now.");
        return "";
    }

    if (CHECK_QUEST(TP))
    {
        command("say to "+ oname +" You have already helped me.");
        return "";
    }

    ask_seq(({"hmm", "say I am short on some ingredients and herbs...",
        "say to "+ oname +" Help me gather them and I'll do "+
	"something special for you."}));
    return "";	
}

/* Used by a map() call to prepend articles to object names. */
private string
article(string str)	{ return LANG_ADDART(str); }

/* Generate a random list of ingredients for a player. */
public string *
gen_quest_items(void)
{
    mapping items = filter(perfumes, &operator([])(,PSPECIAL));
    string *left = ({}), *user = ({});
    int num = 5 + random(4);

    /* Generate list of potential ingredients. */
    foreach(string key, mixed data : items)
	left += data[COMPONENT];

    /* Now generate our shopping list. */
    while(num--)
    {
	string what = one_of_list(left);

	left -= ({ what });
	user += ({ what });
    }

    return user;
}

private string
ask_herbs(void)
{
    string name, *items;

    if (am_busy)
	return "emote appears too busy to answer.";

    name = OB_NAME(TP);

    if (CHECK_QUEST(TP))
	return "say to "+ name +" You have already helped me.";

    name = TP->query_cap_name();

    if (!questors[name])
    {
	items = gen_quest_items();
	questors[name] = ({ items, items });

	items = sort_array(map(items, article));
	return "say The items I need from you are: "+
	    COMPOSITE_WORDS(items) +".";
    }

    items = (string *)questors[name][0];
    items = sort_array(map(items, article));

    return "say I still need you to bring me: "+
	COMPOSITE_WORDS(items) +".";
}

/* Toss stuff. */
private void
toss_it(object what, int quiet)
{
    set_alarm(1.0, 0.0, &(what)->remove_object());

    if (!quiet)
    {
	command("eyebrow confused");
	command("emote tosses away "+ LANG_THESHORT(what) +".");
    }
}

/* Check for wanted items. */
private int
wanted_item(object ob, object from)
{
    string who = from->query_cap_name();

    if (CHECK_QUEST(from))
    {
	/* Already finished quest. */
	set_alarm(1.0, 0.0, &command("say I don't require anything "+
		"more from you."));

	return 1;
    }

    if (!questors[who])
    {
	set_alarm(1.0, 0.0, &command("say If you're in the mood "+
		"to give me things, I may have a task for you."));

	return 1;
    }

    foreach(string id : questors[who][1])
    {
	int size;

	if (!ob->id(id) && (id != ob->query_herb_name()))
	    continue;

	if (!IN_ARRAY(id, questors[who][0]))
	{
	    /* Already brought this item this reboot. */
	    set_alarm(1.0, 0.0, &command("say Splendid, "+
		    "I can always use more ingredients."));

	    return 1;
	}

	questors[who][0] -= ({ id });
	size = sizeof(questors[who][0]);

	/* First ingredient for the quest. */
	if ((size + 1) == sizeof(questors[who][1]))
	{
	    /* New questor. */
	    questors[who][0] -= ({ id });
	    set_alarm(1.0, 0.0, &command("say Marvellous, "+
		    "bring me the rest and I'll reward you."));
	}
	/* A new ingredient for the quest. */
	else if (size)
	{
	    /* Still need more to finish. */
	    set_alarm(1.0, 0.0, &command("say Ahh, "+
		    "you've brought me another."));
	    set_alarm(1.5, 0.0, &command("say Only "+
		    size + " ingredients left."));
	}
	/* They have brought all the ingredients! */
	else
	{
	    set_alarm(0.0, 0.0, &reward_quest(
		    ZQN_PERFUME, from, ZQ_GROUP,
		    ZQB_PERFUME, ZQE_PERFUME, 0, 0));
	    set_alarm(0.5, 0.0, &command("smile bright"));
	    set_alarm(1.0, 0.0, &command("say That was the "+
		    "last ingredient, thank you."));
	    set_alarm(2.0, 0.0, &command("say Since you've "+
		    "taken the time to help me, I'll make my "+
		    "special stock of perfumes and colognes "+
		    "available to you."));
	}

	/* Keep a seperate log of delivered items. */
	logrotate(ZIG_LOGS + "cheynal_perfumes",
	    time2format(time(), "dd mmm yyyy tt: ") +
	    who +" brought item: "+ id +"\n  Short: "+ ob->short() +
	    "\n   File: "+ file_name(ob) +"\n" +
	    (size ? "" : "**** Quest completed.\n"),
	    200000, 3);

	return 1;
    }

    return 0;
}

/* Check for wanted items. */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_interactive(from))
	return;

    if (!wanted_item(ob, from))
	set_alarm(1.0, 0.0, &toss_it(ob, 0));
    else
	set_alarm(1.0, 0.0, &toss_it(ob, 1));
}

private void
change_scent(void)
{
    string oil = one_of_list(m_indexes(perfumes));

    this_object()->set_perfume_oil(oil, perfumes[oil]);
    say(QCTNAME(this_object()) +" dabs some perfume onto her "+
	one_of_list(FEMALE_LOCS) +".\n");
}


/* Creation routines. */
private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("cheynal");
    set_race_name("elf");
    set_adj(({"graceful", "pleasant-smelling"}));
    set_syb_house("Xisis");
    set_title("dei Xisis the Perfume Maker");

    /* Gender, outlook and buffness */
    set_opinion(90);
    set_appearance(90);
    set_gender(G_FEMALE);
    set_alignment(ALIGN_TRUSTWORTHY);
    set_size_descs("of normal length", "plump");
    set_stats(({ 60, 80, 60, 150, 150, 50 }), 25);

    configure_eyes("sparkling", "green", 2);
    configure_hair("long", "sable", "gathered in a loose bun atop "+
	"her head");

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_ACROBAT,       25);
    set_skill(SS_TRADING,       60);
    set_skill(SS_APPR_OBJ,      70);
    set_skill(SS_APPR_VAL,      70);
    set_skill(SS_LANGUAGE,      80);
    set_skill(SS_AWARENESS,     80);
    set_skill(SS_LOC_SENSE,     40);
    set_skill(SS_LANGUAGE,   80);

    set_skill(SS_ALCHEMY,      100);
    set_skill(SS_HERBALISM,    100);
    set_skill(SS_SPELLCRAFT,    80);

    set_skill(SS_ELEMENT_AIR,   60);
    set_skill(SS_ELEMENT_LIFE,  60);
    set_skill(SS_ELEMENT_EARTH, 60);
    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_DEATH, 60);
    set_skill(SS_FORM_ENCHANTMENT,   75);
    set_skill(SS_FORM_TRANSMUTATION, 75);

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({"help"}), &ask_seq(({"say I think we all need a bit of help, "+
	"but I'm doing my part by giving everyone the chance "+
	"to smell better."})), 0);
    add_ask(({"quest","work","task"}), ask_quest, 1);
    add_ask(({"herbs","ingredients"}), ask_herbs, 1);
    add_ask(({"ziggurat","Ziggurat"}), &ask_seq(({
	"say There is no where I'd rather work. Duty and pleasure are "+
    	"one in the same here."})), 0);
    add_ask(({"order","buy","purchase"}), &ask_seq(({
	"say I create perfumes, colognes and provide refills.", 
        "say Simply let me know what you'd like to 'order' and I'll take "+
        "it from there."})), 0);
    add_ask(({"refill","refills",}), &ask_seq(({
	"say Refills..  right, first off, make sure you have an "+
	"empty perfume or cologne bottle available...", 
	"say Then simply 'order' a perfume or cologne as normal.",
	"say However, I won't put perfumes in a cologne "+
	"bottle and vice versa, mixing the oils like that is not "+
	"something I recommend or am willing to do."})), 0);
    add_ask(({"claim","claimed","claiming"}), &ask_seq(({
	"say To retrieve an order, you need only 'claim order'."})), 0);
    add_ask(({"pleasure","scent"}), &ask_seq(({
	"say Pleasure comes in many forms and may cater to each of "+
    	"our senses.", "say I think the pleasure scent brings is the most "+
    	"difficult, delicate and delightful."})), 0);
    add_ask(({"perfume","perfumes","cologne","colognes"}), &ask_seq(({
	"say Using a variety of herbs and essences, I am able to "+
	"concoct a modest variety of perfumes and colognes.", 
	"say They are my specialty in fact, so if you'd like to "+
	"place an order, do let me know!"})), 0);
    add_ask(({"list","menu","items","items for sale","sale",
	"inventory","price","prices","cost"}), &ask_seq(({
        "say You may order colognes and perfumes from me and there "+
	"might be other items of interest about the shop for "+
	"you."})), 0);

    clone_object(PERFUME_SHADOW)->shadow_me(this_object());
    change_scent();

    set_act_time(60);
    add_act("@@do_act");

    /* Restore variables */
    m_idle  = ([]);
    m_sold  = ([]);

    /* Needed for quests. */
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

/* Don't answer to the unseen. */
public void
unseen_hook(void)
{
    if (am_busy)
	return;

    command("wonder hearing things again.");
}

public string
do_act(void)
{
    int num = random(12);

    if (am_busy)
    {
	return "";
    }

    switch(num)
    {
    case 0:
    case 1:
    case 2:
	command("waft");
	break;
    case 3:
    case 4:
    case 5:
	change_scent();
	break;
    case 6:
	command("say My bottles are all handcrafted here in Sybarus.");
	break;
    case 7:
	command("say I manufacture all my own scented oils.");
	break;
    case 8:
	command("say Don't forget, I do refills as well.");
	break;
    case 9:
	command("say My perfumes and colognes make wonderful gifts.");
	break;
    case 10:
	command("say I have scents to match all tastes.");
	break;
    case 11:
	command("say For the best scented oils money can buy, "+
	"refer your friends to Scentiments!");
	break;
    }

    return "";
}

/* Answer stupid questions. */
public string
default_answer(void)
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
    {
        command("emote is too busy to answer right now.");
        return "";
    }    

    if (IS_INFIDEL(TP))
    {
	command("glare "+ oname);
	return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(4))
    {
    case 0:
	command("say to "+ oname +" I have no knowledge of that, sorry.");
	break;
    case 1:
	command("say to "+ oname +" Perhaps you should ask someone else about that.");
	break;
    case 2:
	command("say to "+ oname +" I cannot spend my time answering questions.");
	command("say to "+ oname +" There are always duties to attend to.");
	command("smile politely "+ oname);
	break;
    default:
	command("say to "+ oname +" I have no idea, nor do I really care.");
	break;
    }
    return "";
}

/* React to emotes. */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
  int attr, int target)
{
    string oname;

    if (!target)
	return;

    oname = OB_NAME(actor);

    if (IS_INFIDEL(actor))
    {
	command("glare "+ oname);
	return;
    }

    if ((attr & ACTION_OFFENSIVE) || (attr & ACTION_THREATENING))
    {
	switch(random(3))
	{
	case 0:
	    command("gasp");
	    command("say to "+ oname +" Why I never!");
	    break;
	case 1:
	    command("say to "+ oname +" How crude!");
	    command("emote gestures dismissively.");
	    break;
	case 2:
	    command("say to "+ oname +" Must you act like such a barbarian?");
	    command("peer wondering at "+ oname);
	    break;
	}
    }
    else if ((attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
	switch(random(3))
	{
	case 0:
	    if (actor->query_perfume_oil())
		command("swoon "+ oname);
	    else
		command("say to "+ oname +" Nice try, but it needs work.");
	    break;
	case 1:
	    if (actor->query_perfume_oil())
		command("bat "+ oname);
	    else
		command("say to "+ oname +" Oh, you almost made my heart flutter.");
	    break;
	case 2:
	    if (actor->query_perfume_oil())
		command("sigh wistful");
	    else
	    {
		command("say to "+ oname +" Just think how much more effective "+
		  "that would be wearing my "+ (actor->query_gender() ?
		    "perfumes" : "colognes") +".");
	    }
	    break;
	}
    }
    else switch(random(4))
    {
    case 0:
	command("smile thoughtful");
	break;
    case 1:
	command("nod thoughtful");
	break;
    default:
	/* No response. */
	break;
    }
}

/*
 * React to introductions.
 */
static void
return_intro(object who, string oname)
{
    if (am_busy)
	return;

    if (IS_INFIDEL(who))
	return;

    command("curtsey gracef");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Ta'haveth, "+ who->query_name() +
      "! How may I assist you?");
}

/* Remove abandoned orders. */
private void
clean_up(void)
{
    reset = 0;

    if (!m_sizeof(m_sold))
	return;

    foreach(string who, mixed data : m_sold)
    {
	if (sizeof(data) <= OTIME)
	    continue;

	if ((time() - data[OTIME]) >= 1800)
	    m_delkey(m_sold, who);
    }
}

private void
timeout(mixed arg)
{
    if (intp(arg))
    {
	remove_alarm(t_alarm);
	am_busy = t_alarm = 0;
	return;
    }

    if (strlen(arg))
	m_delkey(m_sold, arg);

    m_idle[arg] = 1;
    count = am_busy = alarm = t_alarm = 0;

    if (objectp(arg = present(arg, environment())))
    {
	command("say to "+ OB_NAME(arg) +
	  " You are taking too long, order cancelled.");
    }

    command("say I'm ready to help another customer.");
}

/* Craft the scented oils. */
private void
make_oil(string rname, int max)
{
    if (count >= max)
    {
	object who;

	remove_alarm(alarm);
	count = alarm = 0;
	timeout(1);

	if (reset)
	    remove_alarm(reset);

	seq_restart();
	reset = set_alarm(1800.0, 0.0, &clean_up());

	command("emote checks the blended oils one more time then "+
	  "smiles with satisfaction.");
	command("emote sets the finished order off to the side.");

	who = find_player(rname);

	if (present(rname, environment()))
	{
	    command("say to "+ OB_NAME(who) +" Your order is completed "+
	       "and ready to be claimed.");
	}
	else if (objectp(who))
	{
	    who->catch_tell("\nYou feel that your order with "+ query_name() +
	      " has been completed and is ready for claiming.\n\n");
	}
	return;
    }

    switch(count++)
    {
    case 0:
	{
	    mapping data = perfumes[m_sold[rname][OSCENT]];

	    max  = data[PCOST] + random(data[PCOST] * 2);
	    max += random(sizeof(explode(data[PDESC], " ")));
	    max += sizeof(data[AROMA]) + sizeof(data[COMPONENT]);
	    max += sizeof(explode(data[SCENT], " "));

	    max = efun::max(7, ftoi(itof(max) / IVAL));
	    alarm = set_alarm(IVAL, IVAL, &make_oil(rname, max));

	    if (objectp(m_sold[rname][BOTTLE]))
		command("say I'll have your refill ready shortly.");
	    else
		command("emote finishes working on the bottle and turns her "+
		  "attention to the oil.");

//	    command("say This oil will be ready in about "+
//	      ftoi(itof(max) * IVAL) +" seconds.");
	}
	break;

    case 1:
	command("emote produces a large, brown glass jug from behind the counter.");
	break;
    case 2:
	command("emote pours a clear base oil into the bottle from the brown jug.");
	break;
    case 3:
	command("emote sorts through some tiny essence vials until she finds "+
	  "the one she wants.");
	break;
    case 4:
	command("emote carefully measures several drops from the essence "+
	  "vial into the bottle.");
	break;
    case 5:
	command("emote stoppers the bottle and vigorously shakes it, thoroughly "+
	  "blending the oils.");
	break;

    default:
	switch(random(2))
	{
	case 0:
	    command("emote shakes the bottle some more then checks the "+
	      "blending of the oils.");
	    break;
	default:
	    command("emote unstoppers the bottle and adds another drop of "+
	      "essence, then seals it and shakes it some more.");
	    break;
	}
	break;
    }
}

/* Construct the bottles for scented oils. */
private void
make_bottle(string rname, int max)
{
    if (count >= max)
    {
	count = 0;
	remove_alarm(alarm);
	alarm = set_alarm(IVAL, 0.0, &make_oil(rname, 99));

	command("emote goes over the bottle a final time with the lint cloth, "+
	  "giving it a final bit of polishing.");

	return;
    }

    switch(count++)
    {
    case 0:
	{
	    mapping data = bottles[m_sold[rname][BOTTLE]];

	    max  = data[BCOST] + data[USES];
	    max += random(sizeof(explode(data[LONG], " ")) / 2);

	    if (strlen(m_sold[rname][ODESIGN]))
		max += sizeof(data[DESIGN][m_sold[rname][ODESIGN]]);
	    if (strlen(m_sold[rname][SCRIPT]))
		max += random(sizeof(explode(m_sold[rname][SCRIPT], " ")) / 2);

	    max = efun::max(7, ftoi(itof(max) / IVAL));
	    alarm = set_alarm(IVAL, IVAL, &make_bottle(rname, max));

	    command("say Seems I best get working on that order then!");
//	    command("say It will take me about "+ ftoi(itof(max) * IVAL) +
//	      " seconds to ready the bottle.");
	}
	break;

    case 1:
	command("emote steps over to her crafting table and begins "+
	    "rummaging through several boxes of various bottle designs.");
	break;
    case 2:
	command("emote finds an appropriate bottle from one of the boxes "+
	    "and carefully goes over it with a lint cloth.");
	break;
    case 3:
	command("emote unstoppers the bottle and pours a cleaning "+
	    "solution into it from a nearby black bottle.");
	break;
    case 4:
	command("emote swishes the sterilizing liquid around the insides "+
	    "of the bottle then empties it into a large, metal flask.");
	break;
    case 5:
	if (strlen(m_sold[rname][SCRIPT]))
	{
	    command("emote picks up an etching tool and inscribes "+
		"some words onto the bottle, burnishing then buffing "+
		"it afterwards.");
	}
	else
	{
	    command("emote goes over the bottle again with a piece of "+
		"cloth, buffing it.");
	}
	break;
    default:
	switch(random(2))
	{
	case 0:
	    command("emote examines the bottle carefully, "+
		"looking for defects.");
	    break;
	default:
	    command("emote buffs out a smudge on the bottle.");
	    break;
	}
	break;
    }
}

/* Tell people things while ordering. */
private void
tell_me(string what)
{
    tell_object(this_player(),
	this_object()->query_The_name(this_player()) +
	" tells you: "+ what +"\n");

    switch(random(3))
    {
    case 0:
	say(QCTNAME(this_object()) +" speaks privately with "+
	    QTNAME(this_player()) +".\n");
	break;
    case 1:
	say(QCTNAME(this_player()) +" speaks privately with "+
	    QTNAME(this_object()) +".\n");
	break;
    default:
	/* do nothing. */
	break;
    }
}

/* Handle odering information. */
private void
resolve_order(string opt, int order, mapping choice, int stage)
{
    string rname = this_player()->query_real_name();

    if (m_idle[rname])
    {
	m_delkey(m_idle, rname);
	return;
    }

    remove_alarm(t_alarm);
    t_alarm = set_alarm(60.0, 0.0, &timeout(rname));

    /* No argument given, give options and prompt. */
    if (!strlen(opt))
    {
	write("\nYou may enter \"l\" to relist, \"h <item>\" for help, "+
	  "or \"q\" to cancel ordering.\n");

	write("Your choice? ");
	input_to(&resolve_order(, order, choice, stage));
	return;
    }

    /* Wants a new listing. */
    if (opt == "l")
    {
	tell_me("You have these "+
	  one_of_list(({"fine","wonderful","splendid"})) +" choices:\n");

	write(sprintf("%-#75s\n",
		implode(sort_array(m_indexes(choice)), "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, order, choice, stage));
	return;
    }

    /* Wants to cancel. */
    if (opt == "q" || opt == "quit")
    {
	timeout(1);
	m_delkey(m_sold, rname);
	seq_restart();

	tell_me("Very well then, I shall hope to benefit from your patronage "+
	  "in the future then.");
	command("smile polite");
	return;
    }

    /* They want help on a choice. */
    if ((opt == "h") || sscanf(opt, "h %s", opt))
    {
	/* No info available for these stages. */
	if (stage > 4)
	{
	    tell_me("Alas, there isn't anything I can tell you about that.");

	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, stage));
	    return;
	}

	/* Not a valid item for this order. */
	if (!pointerp(choice[opt]) && !objectp(choice[opt]))
	{
	    if (opt == "h")
	    {
		resolve_order("", order, choice, stage);
		return;
	    }

	    tell_me("I cannot offer help on that, it isn't "+
	      "pertinent to your order.");
	    command("gesture vague");

	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, stage));
	    return;
	}

	/* Give them the info. */
	if (!stage)
	{
	    tell_me("I can tell you this much: It is "+
	      LANG_ADDART(choice[opt][PDESC]) +" that has "+
	      LANG_ADDART(choice[opt][SCENT]) +" scent.");

	    if (choice[opt][PSPECIAL])
	    {
		tell_me("I only offer this one to clients "+
		    "who have helped me gather ingredients.");
	    }
	}
	else if (stage == 3)
	{
	    tell_me("I can tell you this much, it is: "+
		choice[opt]->long());
	}
	else if (stage == 4)
	{
	    tell_me("I can tell you this much, it is: "+
	      implode(explode(choice[opt][LONG], "%s"), "<design>"));

	    if (m_sizeof(choice[opt][DESIGN]))
	    {
		write("\n");
		tell_me("This bottle supports varying design schemes.");
	    }
	}

	write("\nYour choice? ");
	input_to(&resolve_order(, order, choice, stage));
	return;
    }

    switch(stage)
    {
    case 0: /* Chose an oil. */
	if (!pointerp(choice[opt]))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, stage));
	    break;
	}

	m_sold[rname] = ({ order, opt });

	/* Fallthru */

    case 1: /* Choose a bottle. */
	/* Oil has been resolved, proceed with next stage. */
	tell_me(one_of_list(({"Excellent","Wonderful","Magnificent"})) +
	  "! Now that you've chosen a scented oil, we need to talk about "+
	  "a bottle to put it in.");

	/* See if they have a suitable bottle. */
	{
	    object *obs = all_inventory(this_player());

	    obs = filter(obs, &->perfume_bottle());
	    obs = filter(obs, &operator(==)(0) @ &->query_uses());

	    if (order)
		obs = filter(obs, &->query_cologne());

	    if (!sizeof(obs))
		choice = ([]);
	    else
		choice = mkmapping(map(obs, &->query_bottle_type()), obs);
	}

	/* Ask if they want to refill a bottle. */
	if (m_sizeof(choice))
	{
	    write("\n");
	    tell_me("You appear to have a suitable bottle already, I can use "+
	      "that or you can choose \"none\" and pick a new one.");

	    write(sprintf("\n%-#75s\n",
		implode(({ "none" }) + m_indexes(choice), "\n")));

	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, 3));
	    break;
	}

	/* Fallthru */

    case 2: /* Make bottle. */
	if (order)
	    choice = filter(bottles, &operator([])(,BCOLOGNE));
	else
	    choice = bottles;

	if (!m_sizeof(choice))
	{
	    command("say Oh my! I don't seem to have any bottles for sale!");
	    command("apologize profuse");

	    timeout(1);
	    seq_restart();
	    m_delkey(m_sold, rname);
	    break;
	}

	tell_me("I have many "+ one_of_list(({"fine","suitable","auspicious"})) +
	  " bottles for sale, amongst them are these to choose from:\n");

	write(sprintf("%-#75s\n", implode(m_indexes(choice), "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, order, choice, 4));
	break;

    case 3: /* Chose own bottle. */
	if (opt == "none")
	{
	    command("nod thoughtful");
	    tell_me("Okay, I won't refill any of your bottles.");
	    resolve_order(opt, order, ([]), 2);
	    break;
	}

	if (!objectp(choice[opt]))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, 3));
	    break;
	}

	/* They are doing a refill, skip straight to processing. */
	count = 0;
	remove_alarm(t_alarm);
	m_sold[rname] += ({ choice[opt], 0, 0, time() });
	make_oil(rname, 99);
	break;

    case 4: /* Chose new bottle. */
	if (!pointerp(choice[opt]))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, 4));
	    break;
	}

	m_sold[rname] += ({ opt });

	/* Fallthru */

    case 5: /* Choose a design. */
	/* Pick a design, if there are some available. */
	if (!m_sizeof(choice[opt][DESIGN]))
	{
	    m_sold[rname] += ({ 0 });
	    resolve_order(opt, order, ([]), 7);
	    break;
	}

	tell_me("This bottle can be customized more to your liking, "+
	  "choose from amongst the following:\n");

	choice = choice[opt][DESIGN];
	write(sprintf("%-#75s\n", implode(m_indexes(choice), "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, order, choice, 6));
	break;

    case 6: /* Chose a design. */
	if (!choice[opt])
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, order, choice, 6));
	    break;
	}

	m_sold[rname] += ({ opt });

	/* Fallthru */

    case 7: /* Choose an inscription. */
	tell_me("Now then, the final part of constructing a bottle is choosing "+
	  "an inscription.");
	tell_me("Anything will do, though it can't be that long. Just choose "+
	  "\"none\" if you don't wish one.");

	write("\nYour inscription: ");
	input_to(&resolve_order(, order, choice, 8));
	break;

    case 8: /* Finalize order. */
	if (opt == "none")
	{
	    m_sold[rname] += ({ 0, time() });
	    tell_me(one_of_list(({"Okay","Alright"})) +", I won't include "+
	      "an inscription.");
	}
	else if (strlen(opt) > 70)
	{
	    tell_me("That is alot of verbage, unfortunately the bottle is much "+
	      "to small for it, do try and think of something more compact.");

	    write("\nYour inscription: ");
	    input_to(&resolve_order(, order, choice, 8));
	    break;
	}
	else
	{
	    m_sold[rname] += ({ opt, time() });
	}

	count = 0;
	remove_alarm(t_alarm);
	make_bottle(rname, 99);
	break;
    default:
	write("ERROR ENCOUNTERED, notify a wizard.\n");
	seq_restart();
	timeout(1);
	break;
    }
}

/* Begin the order process. */
public int
f_order(string str)
{
    mapping choice;
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /* Do not disturb */
    if (am_busy)
    {
        write(TO->query_The_name(TP) +" is too busy to take your order.\n");
        return 1;
    }

    if (IS_INFIDEL(TP))
    {
	command("glare "+ oname);
	return 1;
    }

    if (m_sold[rname])
    {
	command("say to "+ oname +" You already have something "+
	  "on order, claim it before you place a new one.");
	return 1;
    }

    /* Need to order something */
    if ((str != "perfume") && (str != "cologne"))
    {
	command("say to "+ oname +" I have several things for sale, just ask "+
	  "if you require help.");
	command("smile patient "+ oname);
	return 1;
    }

    if (str == "cologne")
	choice = filter(perfumes, &operator([])(,PCOLOGNE));
    else
	choice = perfumes;

    /* Filter out special perfumes unless they did the quest. */
    if (!CHECK_QUEST(TP))
	choice = filter(choice, not @ &operator([])(,PSPECIAL));

    if (!m_sizeof(choice))
    {
	command("say to "+ oname +" I'm terribly sorry, but that particular "+
	  "item seems to be unavailable at the present.");
	command("smile apologet "+ oname);
	return 1;
    }

    /* Okay, legit order. */
    am_busy = 1;

    tell_me("So what is it you would like to order?");
    tell_me("We have the following "+
      one_of_list(({"fine","wonderful","splendid"})) +" "+ LANG_PWORD(str) +
      " for sale:\n");

    write(sprintf("%-#75s\n",
	    implode(sort_array(m_indexes(choice)), "\n")));

    resolve_order("", str == "cologne", choice, 0);
    return 1;
}

/* Charge the player. */
private int
charge_me(string rname, int flag)
{
    int cost, copper;

    if (flag)
    {
	cost  = perfumes[m_sold[rname][OSCENT]][PCOST];
	cost += m_sold[rname][BOTTLE]->query_max_uses() / 2;
    }
    else
    {
	cost  = bottles[m_sold[rname][BOTTLE]][BCOST];
	cost += perfumes[m_sold[rname][OSCENT]][PCOST];
	cost += perfumes[m_sold[rname][OSCENT]][USES] / 2;

	if (strlen(m_sold[rname][SCRIPT]))
	    cost += sizeof(explode(m_sold[rname][SCRIPT], " ")) / 3;

	if (strlen(m_sold[rname][ODESIGN]))
	    cost += sizeof(bottles[m_sold[rname][BOTTLE]][ODESIGN]) * 2;
    }

    copper = cost * MONEY_VALUES[MONEY_GC_INDEX];

    if (!MONEY_ADD(this_player(), -copper))
	return 0;
    else
	return 1;

    /* We are haughty and do not disclose our price. */
}

/* Claim a finished order.  */
public int
f_claim(string str)
{
    object sale;
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /* Do not disturb */
    if (am_busy)
    {
        write(TO->query_The_name(TP) +" is too busy to notice your "+
        "clamouring.");
	return 1;
    }

    /* Need to order something */
    if (str != "order")
    {
	command("say to "+ oname +" Just 'claim order' will do.");
	return 1;
    }

    /* Make sure they actually have ordered one. */
    if (!m_sold[rname])
    {
	command("say to "+ oname +" I have no items on order for you.");
	return 1;
    }

    /* Using existing bottle. */
    if (objectp(sale = m_sold[rname][BOTTLE]))
    {
	/* Make sure they are present and have the bottle. */
	if (!present(sale, this_player()))
	{
	    command("say Something fishy is going on here, and I don't like it.");
	    m_delkey(m_sold, rname);
	    return 1;
	}

	if (!sale->set_perfume_oil(m_sold[rname][OSCENT]) ||
	  !sale->config_bottle(m_sold[rname][ORDER]))
	{
	    command("say I don't seem able to refill your "+ sale->short() +
	      ", my apologies. You might wish to consult a wizard as well.");
	}
	else if (!charge_me(rname, 1))
	{
	    command("say Really now! Come back when you can pay "+
	      one_of_list(({"pauper","rake","scoundrel"})) +".");
	    return 1;
	}
	else
	{
	    this_player()->catch_tell(
	      this_object()->query_The_name(this_player()) +" takes your "+
	      sale->short() +" and fills it with a scented oil then "+
	      "hands it back.\n");
	    say(QCTNAME(this_object()) +" takes "+ LANG_ADDART(sale->short()) +
	      " from "+ QTNAME(this_player()) +" and fills it with a scented "+
	      "oil before handing it back.\n", ({ this_player() }));
	}

	m_delkey(m_sold, rname);
	return 1;
    }

    /* Make sure we can clone the item in question. */
    if (!objectp(sale = clone_object(PERFUME_BOTTLE)))
    {
	command("say Hmm, I seem to have misplaced your order, "+
	  "imagine that. You should contact a wizard about this.");
	return 1;
    }

    /* Do optionals first. */
    if (strlen(m_sold[rname][ODESIGN]))
	sale->set_bottle_design(m_sold[rname][ODESIGN]);
    if (strlen(m_sold[rname][SCRIPT]))
	sale->set_bottle_script(m_sold[rname][SCRIPT]);

    /* Now see if we can configure the bottle. */
    if (!sale->set_bottle_type(m_sold[rname][BOTTLE]) ||
      !sale->set_perfume_oil(m_sold[rname][OSCENT]) ||
      !sale->config_bottle(m_sold[rname][ORDER]))
    {
	sale->remove_object();
	m_delkey(m_sold, rname);

	command("say Hmm, I seem unable to complete your order, "+
	  "imagine that. You should contact a wizard about this.");
	return 1;
    }

    if (!charge_me(rname, 0))
    {
	sale->remove_object();
	command("say Really now! Come back when you can pay "+
	  one_of_list(({"pauper","deadbeat","scoundrel"})) +".");
	return 1;
    }

    /* Okay, item cloned and setup, lets give it to the player. */
    if (sale->move(this_player()))
    {
	sale->remove_object();
	command("say to "+ oname +" You can't seem to carry that, "+
	  "come back when you have more room.");
    }
    else
    {
	m_delkey(m_sold, rname);
	command("say to "+ oname +" Here you go, our business is now "+
	  "complete.");
    }

    return 1;
}

/* Add our commands. */
public void
init_living(void)
{
    ::init_living();

    add_action(f_order, "order");
    add_action(f_claim, "claim");
}

public void
seq_heartbeat(int steps)
{
    if (am_busy)
	return;

    ::seq_heartbeat(steps);
}

