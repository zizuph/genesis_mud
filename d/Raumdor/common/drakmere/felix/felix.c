/*
 * - felix.c
 *
 * Felix Cardoza - The npc that sells cosmetic remedies to players.
 *
 * Coded by Lucius@Genesis
 *
 * NOTES:
 * ~~~~~
 * Felix remembers people that piss him off, so beware, as it will
 * cost you for his forgiveness.  You cannot use his wares if he is
 * pissed off at you.  He can be bribed for removal from the list.
 *
 * Money: Money handling is very simple with Felix.  If you need something
 * more complex, you can have him use the /lib/trade module but that contains
 * a lot of overhead that he doesn't really need.
 */
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

inherit "/std/monster";

#include <alignment.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "felix.h"

private mapping m_blacklist;
private static mapping m_annoy, m_intro;
private static mapping m_describe, m_extras, m_orders, m_sold;
private static int am_busy, alarm, count, interval;
private static object ordering;
private static string *msgs;

/*
 * Npc questions are located here.
 * 
 * - The questions should first check the am_busy flag and most likely
 *   refuse to answer any questions.
 * - You may also wish to check the m_annoy or m_blacklist level of the
 *   questioner as well and refuse to answer or provide a different answer.
 */

/* Player wants to know if we're annoyed. */
private string
ask_annoyed()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	return "say to "+ oname +" No, I'm not annoyed, I'm pissed, "+
	    "so either make amends or get lost.";
    }

    if (m_annoy[rname])
    {
	return "say to "+ oname +" Yes, as a matter of fact I am "+
	    "annoyed with you. Annoy me some more and I may just "+
	    "get pissed off.";
    }

    return "say to "+ oname +" Surprisingly I'm not annoyed with you. "+
	"Keep it that way, aye?";
}

/* Player is asking about forgiveness. */
private string
ask_forgive()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	return "say to "+ oname +" I might forgive you your "+
	    "foolhardy transgressions for the sum of "+ m_blacklist[rname] +
	    " platinum. Otherwise get lost, loser.";
    }

    if (m_annoy[rname])
    {
	return "say to "+ oname +" 'Tis true, you've managed to annoy me. "+
	    "I might forget you have for, oh, say 10 platinum?";
    }

    return "say to "+ oname +" Amazingly, you have nothing to seek my "+
	"forgiveness for, try to keep it that way.";
}

/* Player is asking about bribes. */
private string
ask_bribes()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_annoy[rname] || m_blacklist[rname])
    {
	return "say to "+ oname +" A bit of coin might soothe my "+
	    "ruffled feathers, if you know what I mean.";
    }

    return "say to "+ oname +" You've no reason to bribe me, "+
	"see that it stays that way.";
}

/* Player needs help, what else is new? */
private string
ask_help()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	command("sneer "+ oname);
	command("say to "+ oname +" You'll not get any help from me!");
	return "say to "+ oname +" At least not without a bribe "+
	    "to help me forgive your transgressions.";
    }

    return "say to "+ oname +" There is not much I can help you with, "+
	"if you want to know what I can make, ask me for a list.  When "+
	"you are ready to order something, 'order' it.  When you are "+
	"ready to collect an order, you may 'claim' it.  If, perchance, "+
	"you have forgotten what you ordered, 'claim orders' and I shall "+
	"let you know what you might claim, if anything.";
}

/* Player is asking about orders. */
private string
ask_order()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	command("smirk "+ oname);
	command("say to "+ oname +" I'm not about to sell anything "+
	    "to the likes of you.");
	return "say to "+ oname +" At least not without a bribe "+
	    "to help me forgive your transgressions.";
    }

    return "say to "+ oname +" If you see something you'd like to order, "+
	"simply 'order' it.";
}

/*
 * Player is asking what we have for sale.
 * Spit out the list and a short description of them.
 */
private string
ask_list()
{
    int ix, sz;
    string *arr;
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	command("smirk "+ oname);
	command("say to "+ oname +" I'm not about to sell anything "+
	    "to the likes of you.");
	return "say to "+ oname +" At least not without a bribe "+
	    "to help me forgive your transgressions.";
    }

    ix  = -1;
    sz  = m_sizeof(m_orders);
    arr = sort_array(m_indices(m_orders));

    if (!sz)
    {
	command("boggle");
	return "say I'm not sure why I'm here as I seem to have "+
	    "nothing for sale!";
    }

    command("say to "+ oname +" Currently, I have these items for sale.");
    while(++ix < sz)
    {
	command("say I have "+ LANG_ADDART(arr[ix]) +", which is "+ 
	    LANG_ADDART(m_orders[arr[ix]][O_DESC]) + " for "+
	    m_orders[arr[ix]][O_COST] +" platinum.");
    }

    return "say to "+ oname +" If you see something you'd like to order, "+
	"simply 'order' it and if you wish more information about an item, "+
	"just ask me about it.";
}

/* Player asking about a specific item, rattle off the long desc. */
private string
ask_inventory()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	command("growl "+ oname);
	return "say to "+ oname +" Until I have forgiven you, you'll "+
	    "not be able to order it anyways, so go pester someone else.";
    }

    return "say to "+ oname +" "+ m_orders[posed_question][O_LDESC];
}

/* Player looking for a quest, we have none. */
private string
ask_quest()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
	return "emote looks busy and seems to ignore you.";

    if (m_blacklist[rname])
    {
	command("grimace . "+ oname);
	return "say to "+ oname +" I have nothing available for one as "+
	    "rude as you.";
    }

    return "say to "+ oname +" Bah!  What do I look like, a charity?";
}

/* Creation routines. */
private void
create_monster()
{
    setuid();
    seteuid(getuid());

    /* Name, rank and serial number */
    set_name("felix");
    add_name("cardoza");
    set_race_name("human");
    set_adj(({"fidgety", "long-fingered"}));
    set_title("Cardoza, the Cosmetic Remederi");

    /* Gender, outlook and buffness */
    set_gender(G_MALE);
    set_appearance(-1);
    set_random_size_descs();
    set_alignment(ALIGN_UNTRUSTWORTHY);
    set_stats(({ 60, 80, 60, 150, 150, 50 }), 25);

    /* Properties */
    add_prop(LIVE_I_NON_REMEMBER, 1);

    /* Skills */
    set_skill(SS_HIDE,       40);
    set_skill(SS_SNEAK,      40);
    set_skill(SS_ACROBAT,    25);
    set_skill(SS_DEFENCE,    50);
    set_skill(SS_TRADING,    60);
    set_skill(SS_APPR_OBJ,   70);
    set_skill(SS_APPR_VAL,   70);
    set_skill(SS_APPR_MON,   40);
    set_skill(SS_LANGUAGE,   80);
    set_skill(SS_AWARENESS,  80);
    set_skill(SS_LOC_SENSE,  40);

    set_skill(SS_ALCHEMY,   100);
    set_skill(SS_HERBALISM, 100);
    set_skill(SS_SPELLCRAFT, 80);

    set_skill(SS_ELEMENT_AIR,   60);
    set_skill(SS_ELEMENT_LIFE,  60);
    set_skill(SS_ELEMENT_EARTH, 60);
    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_DEATH, 60);
    set_skill(SS_FORM_ENCHANTMENT,   75);
    set_skill(SS_FORM_TRANSMUTATION, 75);

    /* Questions and answers */
    set_dont_answer_unseen(1);
    set_default_answer(query_default_answer);

    add_ask(({"amends","forgive","forgiveness"}), ask_forgive, 1);
    add_ask(({"bribe","bribes","bribing"}), ask_bribes, 1);
    add_ask(({"annoy","annoyed","pissed","pissed off"}), ask_annoyed, 1);

    add_ask(({"help"}), ask_help, 1);
    add_ask(({"quest","work","task"}), ask_quest, 1);
    add_ask(({"order","buy","purchase"}), ask_order, 1);
    add_ask(({"list","menu","items","items for sale","sale",
	    "inventory","price","prices","cost"}), ask_list, 1);

    /* Restore variables */
    m_sold  	= ([]);
    m_annoy 	= ([]);
    m_intro 	= ([]);
    m_orders    = M_ORDERS;
    m_extras    = M_EXTRAS;
    m_describe  = M_DESCRIBE;
    m_blacklist = restore_map(SAVE);

    /* Let people ask about individual inventory items. */
    add_ask(m_indices(m_orders), ask_inventory, 1);
}

/* See if this person has annoyed us, and possibly pissed us off. */
private varargs int
check_annoyed(object who, int vocal)
{
    string oname = OB_NAME(who), rname = who->query_real_name();

    if (!m_annoy[rname])
	return 0;

    if (m_annoy[rname] < THRESHOLD)
	return 1;

    if (vocal)
    {
	command("say to "+ oname +" I hope you know you've managed "+
	    "to piss me off, "+ capitalize(rname) +".");
	command("say to "+ oname +" Until you seek forgivness you will "+
	    "not be able to partake of my services.");
    }

    /* Reset */
    m_annoy[rname] = 0;

    /* Repeat offenders get charged more */
    if (m_blacklist[rname])
	m_blacklist[rname] += 50;
    else
	m_blacklist[rname] += 25;

    /* Cap how much they can owe */
    if (m_blacklist[rname] > 500)
	m_blacklist[rname] = 500;

    /* Save for later */
    save_map(m_blacklist, SAVE);
    return 2;
}

/* Don't answer to the unseen. */
public void
unseen_hook()
{
    if (am_busy)
	return;

    command("say I won't talk to someone I can't see.");
    command("mumble something about invisible imbeciles.");
}

/* Answer stupid questions. */
public string
query_default_answer()
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
    {
	command("emote looks too busy to answer.");
	return "";
    }

    if (m_blacklist[rname])
    {
	command("say to "+ oname +" I'm still mad at you, "+
	    capitalize(rname) +". Until I'm not, ask your questions "+
	    "elsewhere.");
	return "";
    }

#ifdef LOG_QUESTIONS
    write_file(LOG_QUESTIONS, capitalize(rname) +" asked about "+
	query_question() +".\n");
#endif

    switch(random(4))
    {
    case 0:
	command("say to "+ oname +" I have no knowledge of that, sorry.");
	break;
    case 1:
	command("peer "+ oname);
	command("say to "+ oname +" What do I look like?  A library?");
	command("say to "+ oname +" Get lost before you annoy me.");
	break;
    case 2:
	command("say to "+ oname +" Are you always this daft?");
	command("say to "+ oname +" Or are you trying extra hard today?");
	command("smile wryly "+ oname);
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
    string oname, rname;

    if (!target)
	return;

    oname = OB_NAME(actor);
    rname = actor->query_real_name();

    if (attr & ACTION_OFFENSIVE ||
	attr & ACTION_THREATENING)
    {
	command("say to "+ oname +" If you ever wish to be able "+
	    "to purchase my wares again, you will desist.");
	command("sneer "+ oname);

	m_annoy[rname] += (2 + am_busy);
    }
    else if (attr & ACTION_INTIMATE ||
	     attr & ACTION_INGRATIATORY)
    {
	command("say to "+ oname +" I don't give discounts "+
	    "for special favours so piss off.");

	m_annoy[rname] += (1 + am_busy);
    }
    else 
    {
	command("glare "+ oname);

	if (am_busy)
	    m_annoy[rname] += am_busy;
    }

    check_annoyed(actor, 1);
}

/*
 * React to introductions.
 * He remembers people names (but not across reboots).
 * He will also refuse to intro to people who have been blacklisted.
 */
public void
add_introduced(string name)
{
    if (am_busy)
    {
	command("emote looks too busy to notice the introduction.");
	return;
    }

    if (m_blacklist[name])
    {
	command("say to "+ name +" It'll be a cold day in hell "+
	    "before you get any introductions from me, "+
	    capitalize(name) +".");
	return;
    }

    if (m_intro[name])
    {
	command("say to "+ name +" I know thy name, "+
	    capitalize(name) +", I don't need it again.");
	return;
    }

    m_intro[name] = 1;
    command("bow fluidly");
    command("introduce me to "+ name);
    command("say to "+ name +" Greetings, "+ capitalize(name) +
	"!  How might I help you today?");
}

/*
 * Player wants to bribe for forgiveness.
 * This is the only way to be removed from the blacklist
 * without divine intervention.
 */
public int
f_bribe(string str)
{
    int cost;
    object me;
    string verb  = query_verb();
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    if (am_busy)
    {
	m_annoy[rname] += am_busy;
	command("say to "+ oname +" Can't you see I'm busy here!?");

	if (check_annoyed(this_player(), 1) != 2)
	    command("say to "+ oname +" Buzz off before you piss me off!");

	return 1;
    }

    if (!strlen(str))
    {
	command("say to "+ oname +" Be more specific about what "+
	    "you're trying to do.");
	return 1;
    }

    if (!parse_command(str, ({ this_object() }),
	    "[off] %o [for] / [from] %w", me, str) ||
	(str != "forgiveness" && str != "annoyance") || (me != this_object()))
    {
	command("say to "+ oname +" Look, either "+ verb +
	    " me for forgiveness or annoyance.");
	return 1;
    }

    switch(str)
    {
    case "annoyance":
	if (m_annoy[rname])
	    cost = 10;
        break;
    case "forgiveness":
	cost = m_blacklist[rname];
        break;
    default:
	command("say to "+ oname +" What exactly are you trying to do here?");
	return 1;
    }

    if (!cost)
    {
	command("say to "+ oname +" You don't owe me anything for that.");
	return 1;
    }

    cost *= MONEY_VALUES[3];
    if ((TOTAL_MONEY(this_player()) < cost) ||
	(MONEY_ADD(this_player(), -cost) == 0))
    {
	command("sneer "+ oname);
	command("say to "+ oname +" Come back when you have the cash idiot.");
	return 1;
    }

    write("You hand over the coins to "+
	me->query_the_name(this_player()) +".\n");
    say(QCTNAME(this_player()) +" hands some coins over to "+
	QTNAME(me) +".\n");

    command("grin greed "+ oname);
    command("forgive "+ oname +" sins");
    command("asay contempt to "+ oname +" Thank you for your patronage.");

    m_annoy[rname] = 0;
    if (str == "forgiveness")
    {
	m_blacklist = m_delete(m_blacklist, rname);
	save_map(m_blacklist, SAVE);
    }
    return 1;
}

/*
 * So that we can remove deleted_players so punishments
 * aren't carried over.  Should be called from the delete_player()
 * fun inside the domain_link object of the domain.
 */
public int
absolve_player(string name)
{
    m_blacklist = m_delete(m_blacklist, name);
    save_map(m_blacklist, SAVE);
    return 1;
}

/* Final processing of the order. */
private varargs void
process_order(string item, string *extra, string name)
{
    /*
     * If the alarm loop hasn't been started, we begin here
     * and start it up and do the initial setup of the variables.
     */
    if (!alarm)
    {
	float aval;
	string oname = OB_NAME(ordering);
	string rname = ordering->query_real_name();
	int cost = (m_orders[item][O_COST] * MONEY_VALUES[3]);

	/*
	 * The money is actually removed here, make sure they
	 * still have it and didn't drop it while placing the order.
	 */
	if (MONEY_ADD(ordering, -cost) == 0)
	{
	    command("growl "+ oname);
	    command("asay angrily to "+ oname +" Ya damn thief, "+
		"suddenly can't pay aye?  Well, no more service for you!");

	    m_annoy[rname] += THRESHOLD;
	    m_blacklist[rname] += m_orders[item][O_COST];
	    save_map(m_blacklist, SAVE);
    	    am_busy = count = msgs = alarm = interval = 0;
	    return;
	}

	/*
	 * Sets the alarm based on # of text descripts to print
	 * and then starts it up and exits.
	 */
	interval  = m_orders[item][O_TIME];
	interval /= sizeof(m_describe[item]);
	msgs = m_describe[item];
	aval = itof(interval);

	command("say Okay, let me get started on this order.");
	command("say to "+ oname +" You can claim it anytime "+
	    "after I'm finished.");

	alarm = set_alarm(aval, aval, &process_order(item, extra, rname));
	return;
    }

    /*
     * The alarm is still looping at this point and printing
     * textual messages.
     */
    if ((interval * count++) < m_orders[item][O_TIME])
    {
	int tmp = count - 1;

	command(pointerp(msgs[tmp]) ?
	    one_of_list(msgs[tmp]) : msgs[tmp]);

	return;
    }

    /*
     * The order has been completed, setup an entry for the item in
     * the players 'claim' listing so they might retrieve it.
     */
    if (!m_sold[name])
	m_sold[name] = ([]);

    if (m_sold[name][item])
        m_sold[name][item] = ({ 1, extra, ++m_sold[name][item][2] });
    else
        m_sold[name][item] = ({ 1, extra, 1 });

    if (objectp(ordering))
    {
	/* They are still present, let them know. */
        if (present(ordering, environment()))
        {
	    command("say to "+ OB_NAME(ordering) +
		" Your order is complete. You may claim it at any time.");
        }
	/* Not present, let them know anyhow? */
	else
	{
	    tell_object(ordering, "You feel a mental jab and realize "+
		"the order you placed with Felix Cardoza is complete.\n");
	    say(QCTNAME(this_object()) +" closes his eyes and "+
		"concentrates for a brief moment.\n");
	}
    }

    /* Halt and clear the alarm and associated variables. */
    remove_alarm(alarm);
    am_busy = count = msgs = alarm = interval = ordering = 0;
}

/*
 * This is where the 'extras' optionals get processed.
 * It loops through till it finds an error or there are no
 * more options to choose from, then the order is processed.
 */
private void
resolve_choice(string str, string item, int idx, string *extra)
{
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /*
     * This lets us know if we are on the initial call or not
     * so we can set things up for the processing.
     */
    if (idx == -1)
    {
	/* No extras to choose from, just continue on. */
	if (!pointerp(m_extras[item]))
	{
	    process_order(item, extra);
	    return;
	}

	idx = 0;
	extra = ({});

	/* Give them the list of choices and loop back with a prompt. */
	command("say to "+ oname +" "+ m_extras[item][idx]);
	command("say "+ COMPOSITE_WORDS(m_extras[item][idx + 1]) +".");
	write("Choose one: ");
	input_to(&resolve_choice(, item, idx, extra));
	return;
    }

    /* Need to specify a choice. */
    if (!strlen(str))
    {
	write("Choose one: ");
	input_to(&resolve_choice(, item, idx, extra));
	return;
    }

    /* They want to halt the order, let them. */
    if (member_array(str, ({ "stop","quit","cancel","~q" })) != -1)
    {
	am_busy = ordering = 0;
	command("say Bah, fine, I'll cancel your order.");
	return;
    }

    /* They want the choices listed again, do so. */
    if (member_array(str, ({ "list","choice","choices" })) != -1)
    {
	command("say to "+ oname +" "+ m_extras[item][idx]);
	command("say "+ COMPOSITE_WORDS(m_extras[item][idx + 1]) +".");
	write("Choose one: ");
	input_to(&resolve_choice(, item, idx, extra));
	return;
    }

    /* They gave an invalid choice, tell them and ask again. */
    if (member_array(str, m_extras[item][idx + 1]) == -1)
    {
	command("say Bah, that wasn't in the list, if you need "+
	    "to see it again, just type 'list' or you can 'cancel'.");
	write("Choose one: ");
	input_to(&resolve_choice(, item, idx, extra));
	return;
    }

    idx += 2;
    extra += ({ str });

    /*
     * If there are other options yet to process do so.
     * Otherwise begin processing the order.
     */
    if (sizeof(m_extras[item]) > idx)
    {
	command("say to "+ oname +" "+ m_extras[item][idx]);
	command("say "+ COMPOSITE_WORDS(m_extras[item][idx + 1]) +".");
	write("Choose one: ");
	input_to(&resolve_choice(, item, idx, extra));
    }
    else
    {
	process_order(item, extra);
    }
}

/* Begin the order process. */
public int
f_order(string str)
{
    int cost;
    string oname = OB_NAME(this_player());
    string rname = this_player()->query_real_name();

    /* Do Not disturb */
    if (am_busy)
    {
	m_annoy[rname] += am_busy;
	command("say to "+ oname +" Can't you see I'm busy here!?");

	if (check_annoyed(this_player(), 1) != 2)
	    command("say to "+ oname +" Buzz off before you piss me off!");

	return 1;
    }

    /* If your blacklisted, you cannot order. */
    if (m_blacklist[rname])
    {
	command("say to "+ oname +" You won't be placing any orders with "+
	    "me until you have made amends with me.");
	return 1;
    }

    /* Need to order something */
    if (!strlen(str))
    {
	command("rolleyes");
	command("say to "+ oname +" If you don't know what you want to "+
	    "order I can't help you.");
	command("say to "+ oname +" Ask what I have for sale if you need "+
	    "a clue.");
	command("smile derisively "+ oname);
	return 1;
    }

    /* Make sure it's a valid item */
    if (!m_orders[str = lower_case(str)])
    {
	command("sigh soft");
	command("say to "+ oname +" I have no idea what '"+ str +
	    "' is, let alone have it for sale.");
	return 1;
    }

    /* Sanity check. */
    if (!m_describe[str])
    {
	command("scratch");
	command("say I can't for the life of me remember how to make "+
	    "those. You might want to contact a wizard about this.");
	return 1;
    }

    if (m_sold[rname] && m_sold[rname][str])
    {
	/* Do we already have one on claim? */
	if (m_sold[rname][str][0])
	{
	    command("say to "+ oname +" You already have one "+
		"on order, claim it before you order another.");
	    return 1;
	}
#if 0
        /* Check if there is a limit and we are over it. */
	if (m_sold[rname][str][2] >= m_orders[str][O_LIMIT])
        {
	    command("say to "+ oname +" That item is in short supply "+
	      "and I have already supplied you with all I'm going to, "+
	      "you'll not get another this day.");
	    return 1;
        }
#endif
    }

    /* See if we have the cash before going further. */
    cost = (m_orders[str][O_COST] * MONEY_VALUES[3]);
    if (TOTAL_MONEY(this_player()) < cost)
    {
	command("say to "+ oname +" That item costs "+
	    m_orders[str][O_COST] +" platinum.");
	command("say to "+ oname +" I require full cash payment "+
	    "up front, no excuses.  Come back when you have it.");
	return 1;
    }

    /* Okay, legit order, check if there is more we need to do */
    am_busy  = 1;
    ordering = this_player();
    resolve_choice("", str, -1, 0);
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
	m_annoy[rname] += am_busy;
	command("say to "+ oname +" Can't you see I'm busy here!?");

	if (check_annoyed(this_player(), 1) != 2)
	{
	    command("say to "+ oname +" Claim your items at a more "+
		"convenient time, now shoo!");
	}

	return 1;
    }

    /* Can't claim an order if your blacklisted. */
    if (m_blacklist[rname])
    {
	command("say to "+ oname +" You won't be claiming any orders "+
	    "until you have made amends with me.");
	return 1;
    }

    /* Need to order something */
    if (!strlen(str))
    {
	command("sigh deeply");
	command("say to "+ oname +" If you don't know what you are "+
	    "here to claim, then just go away.");
	return 1;
    }

    /* Lets be kind and list what items they have yet to claim. */
    str = lower_case(str);
    if (str == "order" || str == "orders")
    {
	string *items;

	if (!m_sold[rname])
	{
	    command("say to "+ oname +" You have no items on order.");
	    return 1;
	}

	items = sort_array(m_indices(m_sold[rname]));
	items = map(items, LANG_FILE->add_article);

	command("say to "+ oname +" You have the following items on order:");
	command("say "+ COMPOSITE_WORDS(items) +".");
	command("say to "+ oname +" Simply 'claim <item>' to receive it.");
	return 1;
    }

    /* Make sure it's a valid item */
    if (!m_orders[str])
    {
	command("say I don't even offer such items for sale!");
        return 1;
    }

    /* Make sure they actually have ordered one. */
    if (!m_sold[rname] || !m_sold[rname][str] || !m_sold[rname][str][0])
    {
	command("say to "+ oname +" I have no such item on order for you.");
	return 1;
    }

    /* Make sure we can clone the item in question. */
    if (catch(sale = clone_object(m_orders[str][O_PATH])) || !objectp(sale))
    {
#ifdef LOG_ERRORS
	write_file(LOG_ERRORS, ctime(time()) +": "+ rname +
	    " > "+ str + "[clone] ("+ m_orders[str][O_PATH] +")\n");
#endif
	command("say Hmm, I seem to have misplaced your order, "+
	    "imagine that.  You should contact a wizard about this.");
	return 1;
    }

    /* Make sure it can handle processing the extra's. */
    if (catch(sale->setup_extra(m_sold[rname][str][1], this_player())))
    {
#ifdef LOG_ERRORS
	write_file(LOG_ERRORS, ctime(time()) +": "+ rname +
	    " > "+ str + "[setup] ("+ m_orders[str][O_PATH] +")\n");
#endif
	command("say Hmm, I seem unable to complete your order, "+
	    "imagine that.  You should contact a wizard about this.");
	return 1;
    }

    /*
     * Okay, item cloned and setup, lets give it to the player.
     * If they can't hold it, Felix will put it on the ground.
     *
     * The reason Felix doesn't use 'give' and 'drop' is because
     * you may wish to have those props on the items sold. And it
     * would be kludgy to work around it for a silly npc.
     */
    if (sale->move(this_player()))
    {
	sale->move(environment());
	command("say to "+ oname +" You can't seem to carry that, "+
	    "I'll just place it on the ground here for you.");
    }
    else
    {
	command("say to "+ oname +" Here you go, our business is now "+
	    "complete.");
    }

    /* This clears the 'read to claim' flag. */
    m_sold[rname][str][0] = 0;
    return 1;
}

/* Add our commands. */
public void
init_living()
{
    ::init_living();

    add_action(f_bribe, "bribe");
    add_action(f_order, "order");
    add_action(f_claim, "claim");
}
