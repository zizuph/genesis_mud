// Nisa ("nisa.c")
// creator(s):   Zielia 2006 (copied largely from Lucius' cheynal.c)
// last update:
// purpose:      Shopkeeper for clipshop.c
// note:
// bug(s):
// to-do:

#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "zigg.h"

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit ZIG_NPC;

#include "../obj/hair.h"

#define IVAL      5.0
#define ACT	(45 + random(15))

private static string *adj =  ({

  "alabaster",        "ghastly",          "narrow",           "silky",
  "black",            "glass",            "octagonal",        "silver",
  "blue",             "glossy",           "orange",           "silvery",
  "bright",           "gold",             "opaque",           "small",
  "bronze",           "golden",           "pale",             "smokey",
  "copper",           "green",            "peach",            "square",
  "colorful",         "grey",             "pink",             "star-shaped",
  "creepy",           "grisly",           "plain",            "sparkling",
  "crimson",          "gross",            "purple",           "tacky",
  "crystal",          "hair",             "platinum",         "teal",
  "cute",             "handsome",         "pretty",           "thick",
  "dark",             "hideous",          "rainbow",          "thin",
  "delicate",         "indigo",           "rectangular",      "tiny",
  "elegant",          "iridescent",       "red",              "triangular",
  "expensive",        "jade",             "round",            "translucent",
  "fancy",            "leather",          "rose",             "violet",
  "faceted",          "light",            "scarlet",          "ugly",
  "frumpy",           "long",             "scintillating",    "white",
  "gauzy",            "metallic",         "shimmering",       "wooden",
                      "mithril",          "shiny",            "yellow",

});

private static string *kind = ({

  "beads",            "clips",            "loops",            "sapphires",
  "bells",            "crystals",         "moonstones",       "sea-agates",
  "bloodstones",      "diamonds",         "opals",            "seashells",
  "blossoms",         "emeralds",         "onyxes",           "spikes",
  "blooms",           "fire-opals",       "orbs",             "spiderwebs",
  "bones",            "flowers",          "pearls",           "sticks",
  "bugs",             "feathers",         "ribbons",          "strings",
  "chips",            "gems",             "rings",            "strips",
  "chains",           "jewels",           "ropes",            "twigs",
  "leaves",           "rosettes",	  "rubies",

});

private static mapping m_sold, m_idle;
private static int am_busy, alarm, count, reset, copper, t_alarm;

public int f_order(string str);

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

public string
default_answer(void)
{
    if (am_busy)
    {
	command("emote appears too busy to answer.");
	return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(5))
    {
    case 0:
	command("say to "+ OB_NAME(TP) +" I'm sorry. I'm much too busy "+
	  "to try to answer that now.");
	break;
    case 1:
	command("emote looks at you blankly.");
	break;
    case 2:
	command("say to "+ OB_NAME(TP) +" I have no knowledge of that.");
	break;
    case 3:
	command("say I make hair adornments out of all sorts of things. "+
	  "If you'd like to order some, just let me know.");
    default:
	command("smile enigma");
	break;
    }

    return "";
}

private string
ask_help(void)
{
    if (am_busy)
	return "emote appears too busy to notice you.";

    return "say to "+ OB_NAME(TP) +" If you'd like to <order> some hair "+
        "clips just let me know.";
}

private string
ask_quest(void)
{
    if (am_busy)
	return "emote appears too busy to notice you.";

    return "say to "+ OB_NAME(TP) +" If you check back later, I might "+
        "have something.";
}

private string
ask_clips(void)
{
    if (am_busy)
	return "emote appears too busy to notice you.";

    return "say to "+ OB_NAME(TP) +" I make hair adornments out of all "+
        "sorts of things. If you'd like to order some, just let me know.";
}

private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("nisa");
    set_race_name("half-elf");
    set_adj(({"flustered", one_of_list(colors)}));
    set_title("Atrei dei Vyis the Accessory Crafter");
    set_syb_house("Vyis");

    /* Gender, outlook and buffness */

    set_gender(G_FEMALE);
    set_size_descs("very tall", "lean");
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 50, 80, 80, 70, 150, 50 }), 25);

    configure_eyes("gentle", "green", 2);
    configure_hair("long", "dark brown", "cascades down her back in soft "+
      "waves");

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_ACROBAT,    25);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LOC_SENSE,  40);
    set_skill(SS_LANGUAGE,80);

    /* Worn Stuff*/

    object crystal = clone_object(ZIG_OBJ +"clips.c");
    crystal->set_desc("small", "glowing", "source-crystals");
    crystal->open_box("box");
    crystal->move(TO, 1);
    crystal->do_weave("clips");

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({"clip", "clips", "barrettes", "barrette", "adornments",
	"hair adornments", "accessories", "accessory", "adornment",
	"hair adornment"}), ask_clips, 1);
    add_ask(({ "help", "order" }), ask_help, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	&ask_seq(({"say You won't find my clips for sale there.", 
	"say I honestly never thought I'd be selling them to Outlanders. "+
	"but if the Hegemon had not opened the Galleria to them, I might "+
	"have had to move my store there."})), 0);
    add_ask(({"park","island", "holm", "Holm"}), &ask_seq(({
	"say Sometimes the nobles who Hunt there bring me "+
	"back bones and leaves and things for my adornments."})), 0);
    add_ask(({"bath", "melchior's bath"}), &ask_seq(({
	"say There are bathing rooms on the "+
	"lower levels that are nearly as nice and closer if I need to "+
	"freshen up during the day, but usually I bathe at home."})), 0);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
	&ask_seq(({"say It doesn't seem as Forbidden anymore "+
	"does it? At least only nobles are allowed past the walls, but I "+
	"fear more changes."})), 0);
    add_ask(({"infidel", "infidels"}), &ask_seq(({
	"say I cannot understand them. Is it so hard to "+
	"serve, so hard to obey?,", "say The fate of Syb'arus rests on "+
	"the tips of our eyelashes and they seem to take pleasure in "+
	"winking.", "say Let them burn, I say."})), 0);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
	&ask_seq(({"say They call us the Faithful, but it's "+
	"not a matter of faith is it?", "say The Idrys are all around us, "+
	"watching, listening, touching."})), 0);
    add_ask(({"idrys", "Idrys"}), &ask_seq(({
	"say They are true Gods. I am sworn to "+
	"serve them, as was my mother and hers before, as will my children "+
	"be, for all time."})), 0);
    add_ask(({"ziggurat", "Ziggurat", "pleasure palace", "hegemon",
    	"Hegemon"}), &ask_seq(({"say Once, only the richest, "+
    	"most blessed nobles could seek their pleasure here. "+
    	"But as time went on, they grew bored with the upper levels "+
    	"where pleasures are considered simpler, more tame.", 
    	"say Days would pass and I'd have no customers. Two of the "+
    	"shops on this level closed, but finally the Hegemon "+
    	"decided to let in anyone willing to spend coin, at least to "+
    	"the top levels.", "say It was a controversial decision, "+
    	"but I have benefited."})), 0);

    set_act_time(ACT);
    add_act("@@do_act");

    set_cact_time(10);
    add_cact("scream");
    add_cact("pout");
    add_cact("panic");

    set_cchat_time(15);
    add_cchat("I have no fear of Mascarvin, but you should.");

    /* Restore variables */
    m_sold  = ([]);
    m_idle  = ([]);
}

public string
do_act(void)
{
    int num = random(8);

    if (am_busy)
    {
	return "";
    }

    switch(num)
    {
    case 0:
	command("toss hair");
	break;
    case 1:
	command("emote drills a tiny hole through a small bone.");
	break;
    case 2:
	command("emote works busily at her crafting table.");
	break;
    case 3:
	command("emote sorts and straightens some of her many boxes.");
	break;
    case 4:
	command("emote stamps another small box with her label.");
	break;
    case 5:
	command("emote paints a small bead with a delicate paint brush.");
	break;
    case 6:
	command("emote blows a loose strand of"+ COLOR(TO) +" hair out of "+
      "her face as she bends down to work on another clip.");
	break;
    case 7:
	command("smile faint");
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

    if ((attr & ACTION_OFFENSIVE) || (attr & ACTION_THREATENING)
      || (attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
	command("emote ignores you and continues about her work.");
    }
    else switch(random(3))
    {
    case 0:
	command("nod thought");
	break;
    case 1:
	command("smile enigma");
	break;
    default:
	/* No response. */
	break;
    }
}

/* React to introductions. */
static void
return_intro(object who, string oname)
{
    if (IS_INFIDEL(who))
	return;

    command("curtsey briefly");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Intios, "+
	who->query_name() +"! How may I help you?");
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
	  " I'm sorry, I'm much too busy to wait so long. Please "+
	  "let me know when you are ready.");
    }

    command("say I'm ready to help another customer.");
}

/* Tell people things while ordering. */
private void
tell_me(string what)
{
    tell_object(TP, this_object()->query_The_name(TP) +
	" tells you: "+ what +"\n");

    switch(random(3))
    {
    case 0:
	say(QCTNAME(this_object()) +" speaks privately with "+
	    QTNAME(TP) +".\n");
	break;
    case 1:
	say(QCTNAME(TP) +" speaks privately with "+
	    QTNAME(this_object()) +".\n");
	break;
    default:
	/* do nothing*/
	break;
    }
}

private int
query_cost()
{
    copper = (400 + random(200)) * MONEY_VALUES[MONEY_CC_INDEX];

    return copper;
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
	if (sizeof(data) <= m_sold[who][3])
	    continue;

	if ((time() - data[m_sold[who][3]]) >= 1800)
	    m_delkey(m_sold, who);
    }
}

/* Make the clips for order */
private void
make_clips(string rname, int max)
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

	command("emote seems to find the right drawer. She takes a handful "+
	  "of something out and puts it in a paper box nearby.");
	command("emote closes the paper box and sets it to the side.");

	who = find_player(rname);

	if (present(rname, environment()))
	{
	    command("say to "+ OB_NAME(who) +" Your order is completed.");
	}
	else if (objectp(who))
	{
	    who->catch_tell("\nYou feel that your order with "+ query_name() +
	      " has been completed.\n\n");
	}
	return;
    }

    switch(count++)
    {
    case 0:
	{
	    max  = 4 + random(7);

	    alarm = set_alarm(IVAL, IVAL, &make_clips(rname, max));

	    command("say Those will cost you "+ query_cost() +" copper "+
	      "coins. You may pay me when you claim them.");
	    command("say It will take me a few moments to find the clips.");
	}
	break;

    case 1:
	command("emote runs her finger along the chest of drawers, looking "+
	  "for the correct column.");
	break;
    case 2:
	command("emote finds the column of drawers she was looking for and "+
	  "begins opening each and looking inside.");
	break;
    case 3:
	command("emote mutters something to herself and continues searching.");
	break;
    default:
	switch(random(2))
	{
	case 0:
	    command("emote opens a drawer and looks inside. Seeming "+
	      "disappointed she quickly closes the drawer again.");
	    break;
	default:
	    command("emote opens another drawer and combs her fingers "+
	      "through the contents before shutting it again.");
	    break;
	}
	break;
    }
}

/* Handle odering information. */
private void
resolve_order(string opt, string *choice, int stage)
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
	write("\nYou may enter \"l\" to relist or \"q\" to cancel ordering.\n");

	write("Your choice? ");
	input_to(&resolve_order(, choice, stage));
	return;
    }

    /* Wants a new listing. */
    if (opt == "l")
    {
	tell_me("You have these choices:\n");

	write(sprintf("%-#75s\n", implode(choice, "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, stage));
	return;
    }

    /* Wants to cancel. */
    if (opt == "q")
    {
	m_delkey(m_sold, rname);
	seq_restart();
	timeout(1);

	tell_me("Very well then, perhaps another time.");
	command("smile enigmatic");
	return;
    }

    switch(stage)
    {
    case 0: /* Chose kind. */
	if (!IN_ARRAY(opt, kind))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, choice, stage));
	    break;
	}

	m_sold[rname] = ({ opt });

	/* Fallthru */

    case 1: /* Choose first adjective. */
	choice = sort_array(adj);
	tell_me(one_of_list(({"Excellent","Wonderful","Magnificent",
	      "Fabulous", "Splendid"})) +
	  "! Now that you've chosen what kind of adornments you'd like, "+
	  "we can decide how you'd like them to look.");

	tell_me("I have many different looking "+ m_sold[rname][0]+
	  ". What kind would you like? You may choose:\n");

	write(sprintf("%-#75s\n", implode(choice, "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, 2));
	break;

    case 2:

	if (!IN_ARRAY(opt, adj))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, choice, 2));
	    break;
	}

	m_sold[rname] += ({ opt });

	/* Fallthru */

    case 3: /* Choose second adjective. */
	tell_me("Okay. How else would you like your "+ m_sold[rname][1] +
	  " "+ m_sold[rname][0] +" to look? Select another from my options. "+
	  "If you'd like them to look very "+ m_sold[rname][1] +", just choose "+
	  "it again. Your choices are:\n");

	write(sprintf("%-#75s\n", implode(adj, "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, 4));
	break;

    case 4:
	if (!IN_ARRAY(opt, adj))
	{
	    tell_me("That wasn't among the choices I gave you, try again.");
	    write("\nYour choice? ");
	    input_to(&resolve_order(, choice, 4));
	    break;
	}

	m_sold[rname] += ({ opt });

	/* Fallthru */
	
    case 5: /* Choose first adjective. */
	tell_me("So you would like "+  m_sold[rname][1] +
	  " "+ m_sold[rname][2] +" "+ m_sold[rname][0] +". Is that "+
	  "correct?\n");

	write(sprintf("%-#75s\n", implode(({"yes", "no"}), "\n")));

	write("\nYour choice? ");
	input_to(&resolve_order(, choice, 6));
	break;

    case 6:
	if (opt == "no")
	{
	    m_delkey(m_sold, rname);
	    seq_restart();
	    timeout(1);		
		
	    tell_me("Alright... let's try again.");
	    f_order("clips");
	    return;
	}

	/* Fallthru */	

    case 5: /* Should have the order info we need */
	tell_me(one_of_list(({"Excellent","Wonderful","Magnificent",
	      "Fabulous", "Splendid"})) +"! I'll find your "+ m_sold[rname][1] +
	  " "+ m_sold[rname][2] +" "+ m_sold[rname][0]  +" right away!");

	m_sold[rname] += ({ time() });
	make_clips(rname, 99);
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
    string *choice;
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /* Can't order right now. */
    if (am_busy)
    {
	write(TO->query_The_name(TP) +" is too busy to take your order.\n");
	return 1;
    }

    if (IS_INFIDEL(TP))
    {
	command("say to "+ oname + "I will not serve you, Sin'ur. You "+
	  "should leave.");
	return 1;
    }

    if (m_sold[rname])
    {
	command("say to "+ oname +" You already have something "+
	  "on order, claim it before you place a new one.");
	return 1;
    }

    /* Need to order what we have. */
    if (strlen(str) && !IN_ARRAY(str, ({"clip", "clips", "barrettes",
	  "barrette", "adornments", "hair adornments", "accessories",
	  "accessory", "adornment", "hair adornment"})))
    {
	command("say to "+ oname +" What is it you'd like to order? Some "+
	  "hair adornments perhaps?");
	command("eyebrow wonderingly at "+ oname);
	return 1;
    }

    /* Okay, legit order. */

    choice = sort_array(kind);
    am_busy = 1;

    tell_me("So what is it you would like to order?");
    tell_me("We have the following kinds of hair adornments for sale:\n");

    write(sprintf("%-#75s\n", implode(choice, "\n")));
    resolve_order("", choice, 0);
    return 1;
}

/* Charge the player. */
private int
charge_me(string rname)
{
    if (!MONEY_ADD(this_player(), -copper))
	return 0;
    else
	return 1;
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
	command("emote is too busy to notice you right now.");
	return 1;
    }

    /* Need to claim something */
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

    /* Make sure we can clone the item in question. */
    if (!objectp(sale = clone_object(ZIG_OBJ +"clips.c")))
    {
	command("say Hmm, I seem to have misplaced your order, "+
	  "imagine that. You should contact a wizard about this.");
	return 1;
    }

    /* Set descriptions in clips */
    if (strlen(m_sold[rname][0]) && strlen(m_sold[rname][1]) &&
      strlen(m_sold[rname][2]))
	sale->set_desc(m_sold[rname][1], m_sold[rname][2], m_sold[rname][0]);

    if (!charge_me(rname))
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
	command("say to "+ oname +" Here you go. Pashat!");
    }

    return 1;
}

/* Cancel completed order. */
public int
f_cancel(string str)
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (str != "order")
    {
	command("say to "+ oname +" Cancel what? Your order?");

	return 0;
    }

    m_delkey(m_sold, rname);
    command("say to "+ oname +" Very well. Your order has been cancelled.");

    return 1;
}

/* Add our commands. */
public void
init_living(void)
{
    ::init_living();

    add_action( f_order, "order");
    add_action( f_claim, "claim");
    add_action(f_cancel, "cancel");
}

public void
seq_heartbeat(int steps)
{
    if (am_busy)
	return;

    ::seq_heartbeat(steps);
}
