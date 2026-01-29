// Magdala. ("maddy.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Shopkeeper for fetish.c
// note:         Creates custom corsets.
// bug(s):
// to-do:
#pragma no_inherit
#pragma strict_types

#include "zigg.h"

inherit ZIG_NPC;

#define CORSET_MAKER
#include "../obj/corset.h"

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TIMER  90.0
#define ACT   (45 + random(15))
#define MAKEOVER_SHADOW    (ZIG_OBJ + "makeover_shadow")

private static mixed data;
private static int timer, am_busy, value;
private static object order, orderer;

private void process_order(string proc);
private void prompt(string proc, string *arr, int skip = 0);

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
        command("emote is too busy to answer.");
        return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(4))
    {
    case 0:
        ask_seq(({"say to "+ OB_NAME(TP) +" I can think of more interesting "+
            "questions.", "smile coquettish"}));
        break;
    case 1:
        ask_seq(({"emote twists a lock of her coppery hair thoughtfully.", 
            "say to "+ OB_NAME(TP) +" I thought I'd heard of it all, but "+
	    "I can't say I know that one...."}));
        break;
    case 2:
        command("say to "+ OB_NAME(TP) +" Maybe you should ask someone in "+
	    "our sister-store on the ninth level.");
        break;
    default:
        ask_seq(({"bite", "say Perhaps one of the slaves can help you "+
        "with that."}));
        break;
    }

    return "";
}

private string
ask_help(void)
{
    if (am_busy)
    {
        command("emote is too busy to answer.");
        return "";
    }
	
    return "say to "+ OB_NAME(TP) +" I'm okay, thanks.";
}

private string
ask_quest(void)
{
    if (am_busy)
    {
        command("emote is too busy to answer.");
        return "";
    }
	
    return "say to "+ OB_NAME(TP) +" If you check back later, I might have "+
	"something.";
}

private string
ask_rynal(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" The things he can do with that "+
        "mist....", "shiver reminis", "say to "+ OB_NAME(TP) +" but he's "+
        "decided to charm Lyrelle and a wise elf treads carefully around "+
        "that one.", "say Or so say the eunuchs."}));
    return "";
}

private string
ask_corset(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" I can make exquisite custom corsets "+
	"for the female figure if you would like to 'order' one.", 
	"say to "+ OB_NAME(TP) +" If you are looking for one for a male "+
	"though, you will have to visit our other store on the ninth level, "+
	"or make due with what we have."}));
    return "";
}

private string
ask_ninth(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" My House has a second store on the "+
	"ninth level. There you can find much more interesting novelties.", 
	"say to "+ OB_NAME(TP) +" Much better than these boring things.", 
	"gesture expansively", "say and none of the interesting customers "+
	"shop above level five.", "say to "+ OB_NAME(TP) +" Besides you, "+
	"T'cael...", "smile teasing", "say I wish I could work there "+
	"instead, but it is my Duty , to work here."}));
    return "";
}

private string
ask_zig(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" Every fantasy, every dark desire or "+
	"gentle dream can be found in these stone walls.", "say to "+ 
	OB_NAME(TP) +" Simple pleasures are on the upper "+
	"levels. They grow more exotic with each level of decent.", 
	"say to "+ OB_NAME(TP) +" Sadly the upper levels were all "+
	"but empty since the nobles seek their pleasure farther down, "+
	"and so the Hegemon decided not to waste good coin and opened "+
	"them to the lower races and even Outlanders.", "brood", 
	"say to "+ OB_NAME(TP) +" I have profitted, it's true, but "+
	"I rather wish I could be below myself."}));
    return "";
}

private string
ask_whimpering(void)
{
    ask_seq(({"bite", "say to "+ OB_NAME(TP) +" I can give as good as "+
        "I get."}));
    return "";
}

private string
ask_bath(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" If that is an invitation, I decline. "+
	"But thank you.", "smile reservedly"}));
    return "";
}

private string
ask_faithful(void)
{
    ask_seq(({"eyegaze thought at "+ OB_NAME(TP), "say to "+ OB_NAME(TP) +
        " Even those of us whose blood burns with fierce cruelty submit "+
	"fully and find the sweetest bliss in abandoning our "+
	"own will to that of the Idrys.", "say For we who are Faithful, "+
	"it is always so."}));
    return "";
}

private string
ask_mistress(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" I once trained the best of the "+
	"pleasure slaves, you know. I have earned the title.", "But just "+
	"Maddy will do."}));
    return "";
}

private void
zig_npc(void)
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("maddy");
    add_name(({"magdala", "mistress"}));
    set_race_name("elf");
    set_adj(({"spirited", "lithe"}));
    set_title("Ardura dei Mort, Apprentice Purveyor of Peculiarities");
    set_syb_house("Mort");

    /* Gender, outlook and buffness */
    set_opinion(90);
    set_appearance(99);
    set_gender(G_FEMALE);
    set_size_descs("short", "lean");
    set_alignment(ALIGN_TRUSTWORTHY);
    set_stats(({ 100, 170, 100, 90, 90, 150 }), 25);

    configure_eyes("confident", "dark gold", 2);
    configure_hair("shoulder length", "coppery red", "falls about her "+
	"shoulders in a wild, lustrous mane");

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_ACROBAT,    100);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LOC_SENSE,  40);
    set_skill(SS_LANGUAGE,80);

    clone_object(MAKEOVER_SHADOW)->shadow_me(TO);
    TO->set_unique_look("tantalizingly torrid");

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer("@@default_answer@@");

    add_ask(({ "help",}), ask_help, 1);
    add_ask(({ "quest", "task", "job" }), ask_quest, 1);
    add_ask(({ "rynal", "ry'nal"}), ask_rynal, 1);
    add_ask(({ "corset", "corsets"}), ask_corset, 1);
    add_ask(({ "sister store", "ninth level"}), ask_ninth, 1);
    add_ask(({"ziggurat", "Ziggurat"}), ask_zig, 1);
    add_ask(({ "union", "shadow union", "warrior", "warriors"}), 
        &ask_seq(({"emote tosses back her coppery red mane.", "say "+ 
        "The less said about them the better, though I will say I ne'er "+
	"since heard such whimpering."})), 0);
    add_ask(({ "whimpering", "whimper", "whimpers"}), ask_whimpering, 1);
    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	&ask_seq(({"say I saw some thumbscrews from there once.", 
	"say I liked them."})), 0);
    add_ask(({"park", "island", "holm", "Holm"}), &ask_seq(({
	"say I'd like to go Hunting on the Holm one day, if ever I "+
	"have the chance."})), 0);
    add_ask(({"bath", "melchior's bath"}), ask_bath, 1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
	&ask_seq(({"say There is no place more beautiful than the "+
	"home of the Faithful."})), 0);
    add_ask(({"infidel", "infidels"}), &ask_seq(({"say The Inquisitors are "+
        "too kind oft times.", "say Perhaps I'll be allowed to serve one "+
        "day. Wouldn't that be wonderful?"})), 0);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
	ask_faithful, 1);
    add_ask(({"idrys", "Idrys"}), &ask_seq(({"say They are true Gods. "+
        "I live for Their pleasure."})), 0);
    add_ask(({"order", "orders"}), &ask_seq(({"say just 'order corset' "+
        "will do."})), 0);        
    add_ask(({"mistress", "Mistress"}), ask_mistress, 1);

    set_act_time(ACT);
    add_act("@@do_act");

    set_cact_time(15);
    add_cact("smile dark");
    add_cact("emote cries out loudly.");
    add_cact("emote 's golden eyes flash with fury.");

    set_cchat_time(5);
    add_cchat("Your suffering has just begun.");
    add_cchat("Plalgus curse you!");
    add_cchat("I'll show you how to play rough.");

}

static void
add_clothing(void)
{
    string color = one_of_list(({"golden", "amber", "scarlet", "crimson",
	"black",}));

    clone_object(ZIG_OBJ +"lashes")->move(TO, 1);
    object gloss = clone_object(ZIG_OBJ +"pomade");
    gloss->set_tint("scarlet");
    gloss->move(TO, 1);
    gloss->f_apply("pomade");

    object corset = clone_object(ZIG_OBJ +"corset");
	corset->make_random(1);
	corset->set_mat_colour(color);
	corset->make_desc();
	corset->move(TO, 1);
    object boots = clone_object(ZIG_OBJ +"th_boots");
	boots->set_color(corset->query_mat_colour());
	boots->move(TO, 1);
    clone_object(ZIG_OBJ +"lskirt")->move(TO, 1);
    clone_object(ZIG_OBJ +"whip")->move(TO, 1);
    command("wear boots");
    command("wear garments");
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
	command("htwist");
	break;
    case 1:
	command("hstroke");
	break;
    case 2:
	command("emote mentions: I can make lovely custom corsets.");
	break;
    case 3:
	command("emote looks around and stifles a yawn.");
	break;
    case 4:
	command("say The third level is so mundane. If only I could work on "+
	"the lower levels");
	break;
    case 5:
	command("boottug");
	break;
    case 6:
	command("eyestare");
	break;
    case 7:
	command("htoss");
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

    if (am_busy)
        return;

    oname = OB_NAME(actor);

    if (IS_INFIDEL(actor))
    {
        command("glare "+ oname);
        return;
    }

    if ((attr & ACTION_OFFENSIVE) || (attr & ACTION_THREATENING))
    {
        switch(random(7))
        {
        case 0:
            command("frown");
            command("say to "+ oname +" Perhaps some proper training will "+
		"improve your manners.");
            break;
        case 1:
	    actor->catch_msg(QCTNAME(TO) +" watches you with "+
		"a calculating gaze as though keeping track of your "+
		"every transgression.\n");
	    tell_room(ENV(TO), QCTNAME(TO) +" watches "+ QTNAME(actor) +
		" with a calculating gaze as though keeping track of "+
		HIS(actor) +" every transgression.\n", actor, TO);
            break;
        case 2:
            command("say to "+ oname +" You degrade only yourself with such "+
		"behavior.");
            break;
        case 3:
	    command("emote appears completely unimpressed.");
            break;
        case 4:
	    command("emote 's golden eyes flash with temper.");
            break;
        case 5:
	    command("bootoffer");
            break;
        case 6:
	    command("eyeglare derisive "+ oname);
            break;
        }
    }
    else if ((attr & ACTION_INTIMATE) || (attr & ACTION_INGRATIATORY))
    {
        switch(random(6))
        {
        case 0:
            command("eyebrow amused");
            break;
        case 1:
            command("frown disdainfully");
            command("say to "+ oname +" Perhaps one of the pleasure slaves "+
                "can feign interest better.");
            break;
        case 2:
            command("say to "+ oname +" Keep that up and I might let you "+
		"lick my boots later.");
            break;
        case 3:
            command("dchew");
            command("say to "+ oname +" Well, I have been considering taking "+
		"another lover while my others are recovering.");
            command("smile tantalizing at "+ oname);
            break;
        case 4:
	    actor->catch_msg(QCTNAME(TO) +" catches your eyes with "+
		"her steady, golden gaze, holding it until you finally "+
		"look away.\n");
	    tell_room(ENV(TO), QCTNAME(TO) +" catches "+ QTPNAME(actor) +
		" gaze with her steady, golden eyes, holding it until "+
		HE(actor) +" finally looks away.\n", actor, TO);
	    set_alarm(1.0, 0.0, &command("smile amuse"));
            break;
        default:
            command("smile dark");
            break;
        }
    }
    else switch(random(3))
    {
    case 0:
        command("emote examines her nails with a bored expression.");
        break;
    case 1:
        command("emote stiffles a yawn.");
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
    if (IS_INFIDEL(who))
        return;

    command("emote inclines her head politely.");
    command("say to "+ oname +" Ta'haveth, "+
	who->query_name() +".");
    command("introduce me to "+ oname);
    command("emote mentions: Most people just call me Maddy.");
}

public string
query_presentation(void)
{
    string a, b;

    a = query_title();
    b = this_object()->query_exp_title();

    return "Mistress Magdala" +
        (strlen(a) ? (" " + a + ",") : "") +
        (strlen(b) ? (" " + b + ",") : "") + " " +
        this_object()->query_gender_string() + " " +
        this_object()->query_race_name();
}

/* Tell people things while ordering. */
private void
tell_me(string what)
{
    tell_object(orderer, this_object()->query_The_name(orderer) +
	" tells you: "+ what +"\n");

    switch(random(3))
    {
    case 0:
	say(QCTNAME(this_object()) +" speaks privately with "+
	    QTNAME(orderer) +".\n");
	break;
    case 1:
	say(QCTNAME(orderer) +" speaks privately with "+
	    QTNAME(this_object()) +".\n");
	break;
    default:
	/* do nothing*/
	break;
    }
}

private void
cleanup(void)
{
    if (timer)
	remove_alarm(timer);

    if (order)
	order->remove_object();

    timer = 0;
    value = 0;
    order = 0;
    orderer = 0;
    am_busy = 0;
}

private void
timeout(void)
{
    tell_me("It's seldom wise to keep me waiting.");
    command("emote sighs disgustedly.");
    command("say It seems I'm free to take another order.");

    cleanup();
}

/* Confidence building speech after making a choice. */
private void
placate(void)
{
    string *applaud = ({
	"Surely thine eye is as fine as any for spotting such a %s choice.",
	"I heartily agree, that was a %s decision.",
	"Such a %s selection, I could not have done better myself.",
	"You've a keen sense of style to make such a %s selection.",
    }), *exclaim = ({
	"worthy", "splendid", "remarkable", "stylish",
    });

    tell_me(sprintf(one_of_list(applaud) + "\n",
	    one_of_list(exclaim)));
}

/* Spew out some fluffy random preface text before choice listings. */
private void
preface(string proc)
{
    string *exclaim = ({
	"marvelous", "splendid", "amazing", "magnificent",
    }),    *spoken = ({
	"Before we move on, you must decide from these %s %s:",
	"You must select from amongst these %s %s before continuing:",
	"For your selective pleasure, I have these %s %s:",
    });

    tell_me(sprintf(one_of_list(spoken) +"\n",
	    one_of_list(exclaim), proc_text[proc]));
}

/* Test the placate string combo's. */
public void
placate_test(void)
{
    object old = orderer;
    orderer = TP;
    placate();
    orderer = old;
}

/* Test the preface string combo's. */
public void
preface_test(string str)
{
    object old = orderer;
    orderer = TP;

    if (!strlen(str))
    {
	foreach(string k, string d : proc_text)
	{
	    write(">> preface == \""+ k +"\"\n");
	    preface(k);
	}
    }
    else
    {
	if (!proc_text[str])
	{
	    write("Invalid choice, use one of these:\n");
	    write(sprintf("%-#75s\n",
		    implode(sort_array(m_indexes(proc_text)), "\n")));
	}
	else
	{
	    preface(str);
	}
    }

    orderer = old;
}

private void
find_help(string what)
{
    /* General help. */
    if (!strlen(what))
    {
	tell_me("I have the following bits of advice:\n\n"+
	    "  q, ~q, quit, cancel -- Will cancel your present order.\n"+
	    "  list, items         -- Will repeat the current choices.\n"+
	    "  h, help <item>      -- Help on a choice, if I have any.\n");
	return;
    }

    if (pointerp(data) || !data[what])
    {
	tell_me("Alas, there is no help I can offer you for that.");
	return;
    }

    if (sizeof(data[what]) > 3)
	what = data[what][3];
    else
	what = data[what][2];

    if (strlen(what))
	tell_me(what);
    else
	tell_me("Alas, I have no help for that at present.");
}

/* Parse and resolve ordering input. */
private void
resolve_choice(string str, string proc, string *choice)
{
    if (!timer || !order || (orderer != TP))
	return;

    if (!strlen(str))
    {
	prompt(proc, choice);
	return;
    }

    remove_alarm(timer);
    timer = set_alarm(TIMER, 0.0, timeout);

    switch(str)
    {
    case "q": case "~q":
    case "quit": case "cancel":
	command("say T'cael, your order is cancelled.");
        cleanup();
	return;

    case "list": case "items":
	prompt(proc, choice);
        return;

    case "h": case "help":
	find_help("");
	prompt(proc, choice, 1);
        return;
    }

    mixed tmp;

    if ((sscanf(str, "h %s", tmp) == 1) ||
	(sscanf(str, "help %s", tmp) == 1))
    {
	find_help(tmp);
	prompt(proc, choice, 1);
        return;
    }

    if (!IN_ARRAY(str, choice))
    {
	tell_me("That was not a choice I offered you.");
	prompt(proc, choice, 1);
	return;
    }

    placate();

    /* Call the set function. */
    function fun = mkfunction("set_"+ proc, order);

    if (pointerp(data))
	fun(str);
    else if (mappingp(data))
	fun(data[str][0]);
    else
    {
	/* Should never arrive here. */
	tell_me("How odd.. I cannot continue this order.");
	cleanup();
	return;
    }

    /* Get next process. */
    tmp = process[proc];

    if (pointerp(tmp))
    {
	tmp = tmp[1];
    }
    else
    {
	value += tmp[str][1];
	tmp = tmp[str][2];
    }

    /* Continue to next process. */
    if (strlen(tmp))
    {
	process_order(tmp);
	return;
    }

    /* No more processes, finish order. */

    /* Set the value of the object (gold -> copper) */
    order->set_value(value * 144);
    order->make_desc();

    /* Move to the storeroom. */
    tmp = (ZIG_RL3 + "fetish");
    order->move(tmp->get_store_object());

    /* Reset or it will get nuked during cleanup. */
    order = orderer = 0;

    command("say Your order is complete and available for purchase.");
    cleanup();
}

/* Preface and prompt. */
private void
prompt(string proc, string *arr, int skip = 0)
{
    if (!skip)
    {
	preface(proc);
	tell_object(orderer, sprintf("%-#75s\n\n",
		implode(sort_array(arr), "\n")));
    }

    tell_object(orderer, "What shall your choice be? ");
    input_to(&resolve_choice(, proc, arr));
}

/* Process part of the ordering chain. */
private void
process_order(string proc)
{
    mixed item;

    if (!orderer || !present(orderer, environment()))
    {
	cleanup();
	command("say I am free to receive new orders.");
	return;
    }

    remove_alarm(timer);
    timer = set_alarm(TIMER, 0.0, timeout);
    item  = process[proc];

    if (pointerp(item))
    {
	item = item[0];
	item = item[1..];
	item = call_other(order, "query_"+ item);
	data = secure_var(item);

	if (mappingp(item))
	{
	    value += item[1];
	    item = m_indexes(item);
	}
    }
    else
    {
	data = secure_var(item);
	item = m_indexes(item);
    }

    prompt(proc, item);
}

public int
f_order(string str)
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /* Can't order right now. */
    if (am_busy)
    {
	write(TO->query_The_name(TP) +
	    " is too busy to take your order.\n");
	return 1;
    }

    if (IS_INFIDEL(TP))
    {
	command("say to "+ oname + "I will not serve you, Sin'ur. You "+
	  "should leave.");
	return 1;
    }

    if (str != "corset")
    {
	command("say I only create custom corsets, if you don't wish "+
	    "one of them or my regular wares, I suggest you look "+
	    "elsewhere.");
	return 1;
    }

    say(QCTNAME(TP) +" approaches "+ QTNAME(TO) +" and they begin "+
	"speaking privately.\n");

    am_busy = 1;
    orderer = this_player();
    order = clone_object(ZIG_OBJ + "corset");

    tell_me("Very well, than let us begin, shall we?");

    process_order(BEGIN_PROCESS);
    return 1;
}

/* Add our commands. */
public void
init_living(void)
{
    ::init_living();
    add_action( f_order, "order" );
}

public void
seq_heartbeat(int steps)
{
    if (am_busy)
	return;

    ::seq_heartbeat(steps);
}
