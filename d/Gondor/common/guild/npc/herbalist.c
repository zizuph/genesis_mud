/*
 * /d/Gondor/common/guild/npc/herbalist.c
 *
 * The Herb-master of the Rangers.
 * By Elessar, July 17th 1992.
 *
 * Modification log:
 *
 * Sep 1993, Olorin: added training of herbalism
 * The teaching routines were added following an example by Mortricia.
 * May 1996, Elessar: Code updated and beautified 
 * 3-Dec-1996, Olorin: Moved from Elessar's private directory.
 * 6-Jun-1998, Gnadnar: Moved skills code from herbalist.h to here,
 *	changed to use a mapping of herbs (instead of array) so
 *	we can list herbs alphabetically, allow buying more than one of
 *	of a herb, removed the "closed" flag (which could be set, but
 *	was never used), and generally tidied up. 
 *	My thanks to Igneous for letting me look at the Shire herbalist.
 * 28-Aug-1998, Gnadnar: allow asking lothmir about specific herb,
 * 10-Sep-1998, Gnadnar: only sell to members of good guilds, lie to others.
 * 30-Apr-2000, Gwyneth: Removed only selling to members of good guilds.
 * 30-Apr-2000, Gwyneth: Added only selling a limited number of herbs
 *      to each player. A non-ranger can buy 30 attanars or 20 attanars
 *      and 10 sages etc, but no more.
 */

#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/lib/trade.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "herbalist.h"


mapping		All_herbs = ([]);
string		*Log_herbs = ({}),
		*Ranger_herbs = ({});
static string	Book_str,
		Report_name,
		Coin_pay_text,
		Coin_get_text,
		*Herb_buyer,
		Log_str;
static int	Ask_help_alarm_id,
		*Money_arr,
		No_report_flag,
		Rem_flag_alarm_id,
		Test_id_alarm_id;
static object	Given_herb;


/* Prototypes */
public void	create_gondor_monster();
public void	arm_me();
public void	restore_herbs();
public void	init_living();
public void	announce_selling();
public int	herb_filter(object ob);
public int	out_of_stock_filter(string name);
public int	low_on_stock_filter(string name);
public string	wizinfo();
public int	list(string arg);
public int	buy(string arg);
public void	log_purchase(object tp, int flag, string hname);
public int	can_afford(int price);
public int	sell(string arg);
public void	do_sell_all(object player);
public void	do_pay(object player, int price);
public void	add_herb(object herb);
public void	enter_inv(object ob, object from);
public void	not_herb(object ob, object from);
public void	give_back_immediately(object herb, object from);
public void	test_identify(object herb, object from);
public void	show_herb(string hname, mixed *hdata);
public void	intro_me(string name);
public void	add_introduced(string name);
public void	do_bow(object pl);
public void	react_bow();
public void	remove_tmp_flag();
public void	ask_help_herb_book(object player);
public void	catch_question(string question);
public void	answer_question(mixed msg, int cmd);
public string	default_answer();
public string	ask_herbs();
public string	ask_lore();
public string	ask_rabbit();
public string	ask_stew();
public string	ask_garlic();
public string	ask_buyers();
public int	do_report(string arg);
public void	write_more(string arg);
public void	set_up_skills();
public int	remove_herb_from_list(string hname);
public int	add_ranger_herb(string hname);
public int	remove_ranger_herb(string hname);
public int	check_allowed(string action);
public int	second_life(object killer);
public void	room_too_dark();
public void	cant_see();
public void	dont_know(object tp);
public int	sk_improve(string arg);
public void	sk_hook_raise_rank(int snum, int to_lev, int cost);
public void	sk_hook_write_header(int lessons);
public int	sk_hook_no_list_learn();
public int	sk_hook_no_list_improve();
public int	sk_hook_improved_max(string skill);
public void	tell_herb(object player);
public string	missing_herb();
public string	low_herb();
public int      good_guild_test(object pl);

/*
 * Function name:	create_gondor_monster
 * Description	:	set up the herbalist
 */
public void
create_gondor_monster()
{
    FIX_EUID;
    set_name("lothmir");
    add_name(({"herbalist", "teacher"}));
    add_name("ranger");
    set_race_name("human");
    set_living_name("lothmir");
    set_title("the Herbalist");
    set_adj(({ "old", "friendly" }));
    set_long(BSN(
	"Lothmir is the herb-master of the Rangers.  He is said to "+
	"know a great deal about herbs and plants and their virtues. "+
	"If you give him a herb, he will try to identify it for you. "+
	"He will also list for you any herbs he might have to sell. "+
	"If you have herbs to sell, Lothmir will probably be happy to "+
	"buy them. Sometimes he even teaches his skill to others, but "+
	"he might ask a favour of you before he reveals parts of his "+
	"wisdom."));

    set_stats(({ 55, 55, 60, 99, 98, 55 }));
    set_base_stat(SS_OCCUP, 75);
    set_hp(10000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 63000);
    add_prop(CONT_I_HEIGHT, 184);
    add_prop(OBJ_S_WIZINFO, wizinfo);
add_prop(OBJ_M_NO_ATTACK,"Given the amount of Rangers nearby, attacking him would surely be suicide.\n");

    set_skill(SS_BRAWLING, 80 + random(10));
    set_skill(SS_HEARING, 60 + random(10));
    set_skill(SS_HERBALISM,96);
    set_skill(SS_AWARENESS, 87);
    set_skill(SS_WEP_POLEARM,85);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_PARRY, 48);
    create_skill_raise();
    set_up_skills();

    set_chat_time(7);
    add_chat("I am Lothmir, the best herbalist in Gondor!");
    add_chat("You would not have any unknown herbs, would you?");
    add_chat("You know the old saying: There is an herb for "+
	"every occasion.");
    add_chat("I think I have seen most herbs in the world by now.");
    add_chat("If you have an unknown herb, you can let me identify "+
	"it for you.");
    add_chat("I still have not discovered the virtues of kingsfoil.");
    add_chat("You never know when a herb might come in handy.");
    add_chat("I've heard that the rangers have books on herbs in "+
	"their library.");
    add_chat("The rangers are looking for help to write a book about herbs.");
    add_chat("Too bad that there is no book where to find which "+
	"herbs in Gondor!");
    add_chat("If you ask me, I can tell you about herbs and lore.");

    set_cchat_time(2);
    add_cchat("But what have I ever done to hurt you?!?");
    add_cchat("I am a poor old man, my eyes are grey, my legs are "+
	"old and bent!");
    add_cchat("Beware! Or I shall taunt you a second time!");
    set_act_time(4);
    add_act("listen south");
    add_act(announce_selling);
    set_cact_time(2);
    add_cact("brawl");

    trig_new("%s 'bows' %s", "react_bow");
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs", "herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore", "lore"}), VBFC_ME("ask_lore"));
    add_ask(({"rabbit"}), VBFC_ME("ask_rabbit"));
    add_ask(({"stew", "rabbit stew"}), VBFC_ME("ask_stew"));
    add_ask(({"garlic"}), VBFC_ME("ask_garlic"));
    add_ask(({"herbalism", "lesson", "lessons", "train", "training"}),
      "say Why don't you try to learn or improve?",1);
    add_ask(({"buyers", "customers",}), VBFC_ME("ask_buyers"));
    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

    set_equipment( ({ (ARM_DIR + "drcloak"), (RANGER_DIR + "rring") }) );
} /* create_gondor_monster */

/* Function name: good_guild_test
 * Description  : Masks good_guild_test inherited by
 *                /d/Gondor/common/lib/friend_or_foe.c to remove
 *                the herbalist's bias towards selling. Remove this
 *                function and the above prototype to enable it again.
 * Arguments    : object pl, the person being tested
 * Returns      : Always 1
*/
public int
good_guild_test(object pl)
{
    return 1;
}

/*
 * Function name:	arm_me
 * Description	:	mask parent so we also restore herbs.
 */
public varargs void
arm_me()
{
    ::arm_me();
    restore_herbs();
    FIX_EUID
    add_cmdsoul("/cmd/live/speech");
    update_hooks();
} /* arm_me */


/*
 * Function name:	restore_herbs
 * Description	:	restore our inventory of herbs
 *
 * N.B. this used to contain the filenames, not just the herb name.
 *      however, that meant that attempts to purchase reserved or
 *	logged herbs were recorded only if the herb were in stock.
 *	by using the name, all such attempts get recorded.
 */
public void
restore_herbs()
{
    restore_object(HERBAL_SAVE);
    if (!sizeof(Ranger_herbs))
    {
	Ranger_herbs = ({ "athelas", "lothore", "redweed", "suranie", 
	    "curugwath", "alfirin", "ungolestel", "foxglove",
	    "red_pepper", "handasse", "morgurth", });
    }
    if (!sizeof(Log_herbs))
    {
        Log_herbs = ({ "curugwath", "coccinea", "foxglove",
	    "handasse", "seregon", "red_pepper", "morgurth",
	    "angurth", "bpotato", "garlic", });
    }
} /* restore_herbs */


/*
 * Function name:	init_living
 * Description	:	add the herb verbs
 */
public void
init_living()
{
    ::init_living();
    init_skill_raise();
    add_action(list, "list");
    add_action(buy, "buy");
    add_action(sell, "sell");
    add_action(do_report, "report");
    No_report_flag = 0;
} /* init_living */


/*
 * Function name:	announce_selling
 * Description	:	chat to announce herbs (or their lack)
 */
public void
announce_selling()
{
    if (m_sizeof(All_herbs))
    {
        command("say I have herbs for sale too, would you like some?");
    }
    else 
    {
        command("say I should go and search for more herbs.");
    }
} /* announce_selling */


/*
 * Function name:	herb_filter
 * Description	:	decide if argument is a herb
 * Arguments	:	object ob -- the object of interest
 * Returns	:	1 if is herb, 0 if not
 */
public int
herb_filter(object ob)
{
    return (function_exists("create_herb", ob) &&
	    strlen(ob->query_herb_name()) &&
	    ob->query_herb_value());
} /* herb_filter */


/*
 * Function name:	out_of_stock_filter
 * Description	:	decide if we are out of this herb
 * Arguments	:	string name -- name of the herb
 * Returns	:	1 if out of stock, 0 if not
 */
public int
out_of_stock_filter(string name)
{
   mixed *hdata = All_herbs[name];
   return (!pointerp(hdata) ||
	   !hdata[H_COUNT]);
} /* out_of_stock */


/*
 * Function name:	low_on_stock_filter
 * Description	:	decide if we are low on this herb
 * Arguments	:	string name -- name of the herb
 * Returns	:	1 if low, 0 if not
 */
public int
low_on_stock_filter(string name)
{
   mixed *hdata = All_herbs[name];
   return (!pointerp(hdata) ||
	   hdata[H_COUNT] < (MAX_INV / 2));
} /* low_on_stock */


/*
 * Function name:	wizinfo
 * Description	:	list files of inventory
 * Returns	:	string -- the info
 */
public string
wizinfo()
{
    int		i,
		n;
    string	tmpstr,
   		*hnames;
    mixed	*hdata;

    hnames = m_indices(All_herbs);
    n = sizeof(hnames);
    if (n)
    {
	hnames = sort_array(hnames);
	tmpstr = "The herbalist has these herbs for sale:\n";
	for (i = 0; i < n; ++i)
	{
	    if (pointerp(hdata = All_herbs[hnames[i]]))
	    {
		tmpstr += hnames[i]+"\t"+hdata[H_COUNT]+
			  "\t"+hdata[H_FILE]+"\n";
	    }
	}
    }
    else
    {
	tmpstr = "The herbalist has no herbs for sale just now.\n";
    }
    return tmpstr;
} /* wizinfo */


/*
 * Function name:	list
 * Description	:	handle attempts to list herbs
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 -- always
 */
public int
list(string arg)
{
    string	*hnames,
		hlist;
    mixed	*hdata;
    object	tp = TP,
		thiso = TO;
    int		i, n;

    if (!CAN_SEE_IN_ROOM(thiso))
    {
	room_too_dark();
        return 1;
    }
    if (!CAN_SEE(thiso, tp))
    {
	cant_see();
        return 1;
    }

    tell_room(ENV(thiso),
	QCTNAME(tp)+" asks "+QTNAME(thiso)+" a question.\n", tp);

    if (!tp->query_prop(LOTHMIR_I_INTROD))
    {
	dont_know(tp);
	return 1;
    }

    if (!strlen(arg))
    {
	NF0("List what?\n");
    }
    if (arg == "herbs" ||
	arg == "all herbs")
    {
	if (!good_guild_test(tp))
	{
	    command("say I'm sorry, I have no more herbs for sale.");
	    command("sigh");
	    return 1;
	}
	hnames = m_indices(All_herbs);
	n = sizeof(hnames);
	if (!n)
	{
	    command("say I'm sorry, I have no more herbs for sale.");
	    command("sigh");
	    return 1;
	}
	command("say Hmm ... let me see now ...");
	hnames = sort_array(hnames);
	hlist = "";
	for ( i = 0; i < n; ++i )
	{
	    if (pointerp(hdata = All_herbs[hnames[i]]) &&
		hdata[H_COUNT] > 0)
	    {
		hlist += sprintf(" %=21s\t%3d at %4d coppers each\n",
				 hnames[i], hdata[H_COUNT], hdata[H_VALUE]);
	    }
        }
        command("say I have these herbs for sale:");
	tp->more(hlist);
        tell_room(ENV(thiso),
	    QCTNAME(thiso) + " checks his stores, "
          + "and recites a list of different herbs for "
          + QTNAME(tp) + ".\n", tp);
        return 1;
    }
    command("say "+CAP(arg)+", "+arg+" ... let me see ...");
    if (good_guild_test(tp) &&
	(pointerp(hdata = All_herbs[arg]) ||
	 pointerp(hdata = All_herbs[LANG_SWORD(arg)])) &&
	hdata[H_COUNT] > 0)
    {
	command("say I have "+hdata[H_COUNT]+" in stock.");
	command("say The going price is "+hdata[H_VALUE]+
	    " copper coins apiece.");
    }
    else
    {
	command("sigh");
	command("say I can't find "+arg+" anywhere in my stock.");
    }
    return 1;
} /* list */


/*
 * Function name:	buy
 * Description	:	handle attempts to buy herbs
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 -- always
 */
public int
buy(string arg)
{
    mixed	*hdata;
    object	*herb_ob,
		tp = TP,
		thiso = TO;
    int		amount,
		unknown,
		i,
		max_n;
    string	*words;

    if (!CAN_SEE_IN_ROOM(thiso))
    {
	room_too_dark();
        return 1;
    }
    if (!CAN_SEE(thiso, tp))
    {
	cant_see();
        return 1;
    }
    if (!tp->query_prop(LOTHMIR_I_INTROD))
    {
	/* postpone the dont-know-you responses
	 * so can log attempts to buy ranger herbs
	 */
	unknown = 1;
    }

    if (!strlen(arg))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
	if (unknown)
	{
	    dont_know(tp);
	}
	else
	{
	    command("say What did you want to buy?");
	}
	return 1;
    }

    arg = LOW(arg);
    if (arg == "herbs" ||
	arg == "herb")
    {
	/* allow "buy herbs" to behave like "list" for 
	 * backwards compatibility
	 */
	list("herbs");
	return 1;
    }

    words = explode(arg, " ");
    if (sizeof(words))
    {
	sscanf(words[0], "%d", amount);
	if ( amount > 0)
	{
	    arg = implode(words[1..], " ");
	}
	else
	{
	    amount = 1;
	}
    }

    tell_room(ENV(thiso),
	QCTNAME(tp)+" asks "+QTNAME(thiso)+" for "+
	( amount == 1 ? LANG_ADDART(arg) : "some "+arg )+
	".\n", tp);

    if (member_array(arg, Ranger_herbs) >= 0 &&
        !IS_RANGER(tp))
    {
	if (unknown)
	{
	    dont_know(tp);
	}
	else
	{
            command("say Sorry, the " + arg + " is reserved "
              + "for the Rangers.");
            command("say I cannot sell it to you.");
	}
        return 1;
    }

    if (unknown)
    {
	dont_know(tp);
	return 1;
    }

    command("emote starts looking through his herb-storage.");
    if (!good_guild_test(tp) ||
        !pointerp(hdata = All_herbs[arg]) ||
	!hdata[H_COUNT])
    {
	command("say I'm deeply sorry, "
	    + ((tp->query_gender() == G_MALE) ? "sir" : "my lady")
	    + ", but I have no " + arg + ".");
	command("sigh");
	return 1;
    }

    max_n = MIN(MAX_XFER, amount);

    if((max_n + tp->query_prop(RANGER_HERBS_I_BOUGHT)) > MAX_ALLOW_BUY &&
        !IS_RANGER(tp))
    {
        command("say I'm deeply sorry, " +
            ((tp->query_gender() == G_MALE) ? "sir" : "my lady") +
            ", but I can only sell you so many herbs.");
        return 1;
    }

    if (max_n < amount)
    {
        command("say I'll just sell you "+MAX_XFER_WORD+" for now.");
        command("say Any more and my old brain might forget how much I "+
	    "am supposed to charge you!");
	command("blush");
    }

    if (hdata[H_COUNT] < max_n)
    {
	command("sigh");
	command("say I am sorry, but I don't have "+LANG_WNUM(max_n)+
		" of that herb in stock.");
	return 1;
    }

    if (can_afford(hdata[H_VALUE] * max_n)) 
    {
	herb_ob = allocate(max_n);
	for (i = 0; i < max_n; ++i)
	{
            if (!(herb_ob[i] = clone_object(hdata[H_FILE]))) 
            {
		log_file(LOG_BUG,
		    ctime(time())+" lothmir failed to clone "+
		    arg+" from "+hdata[H_FILE]+"\n");
        	command("say Hmm ... I'm deeply sorry ... "+
		    (max_n == 1 ? "it seems" : "they seem")+
		    " to have decayed.");
        	command("frown");
		hdata[H_COUNT] = 0;
        	return 1;
            }
	}

        tp->add_prop(RANGER_HERBS_I_BOUGHT,
            tp->query_prop(RANGER_HERBS_I_BOUGHT) + max_n);
        herb_ob->move(thiso, 1);
        herb_ob->force_dry();
        command("emote picks "+(max_n == 1 ? "a herb" : "some herbs")+
	    " from a little pouch.");
        command("say I hope the "+arg+" will be useful, " +
	    ((tp->query_gender() == G_MALE) ? "sir" : "my lady")+"!");

	/* this is clumsy, perhaps, but moving them one at a time using
	 * OB_NAME is the safest way, so ...
	 */
	for (i = 0; i < max_n; ++i)
	{
            command("give "+OB_NAME(herb_ob[i])+" to "+
		tp->query_real_name());
            if (ENV(herb_ob[i]) == thiso) 
            {
		/* assume that if we can't give one, we can't
		 * give any others
		 */
        	command("frown");
		command("say I'll just put "+
		    (i == (max_n - 1) ? "it" : "them")+" here, then.");
		command("drop "+OB_NAME(herb_ob[i]));
		while (++i < max_n)
		{
		    command("drop "+OB_NAME(herb_ob[i]));
		}
	   }
	}
        hdata[H_COUNT] -= max_n;
	if (hdata[H_COUNT] < 0)
	{
		/* "cannot happen" */
		hdata[H_COUNT] = 0;
	}
	if (!hdata[H_COUNT])
	{
	    command("say Hmmpf. That was my last "+arg+".");
	    command("say I guess I will have to go searching again.");
	}
        save_object(HERBAL_SAVE);
    }
    else
    {
        command("frown");
        command("say Why bother asking when you cannot afford it, " +
          ((tp->query_gender() == G_MALE) ? "mister" : "madam") + "?");
    }
    return 1;
} /* buy */


/*
 * Function name:	log_purchase
 * Description	:	log attempts to purchase ranger herbs by
 *			non-rangers, and the purchase of herbs in
 *			Log_herbs list by anyone.
 * Arguments	:	object tp -- the would-be buyer
 *			int flag -- status of purchase
 *			string hname -- the herb name
 */
public void
log_purchase(object tp, int flag, string hname)
{
    string ltxt;

    ltxt = tp->query_name()+" ";
    switch(flag)
    {
    case LOG_RESTRICTED:
        ltxt += "tried to buy (restricted) ";
	break;
    case LOG_OUT_OF_STOCK:
        ltxt += "tried to buy (out of stock) ";
	break;
    case LOG_CANT_AFFORD:
        ltxt += "tried to buy (can't afford) ";
	break;
    default:
	ltxt += "bought ";
	break;
    }
    ltxt += hname+" from Lothmir, "+ctime(time())+".\n";
    log_file(LOG_PURCHASE, ltxt);

    if (IS_RANGER(tp) ||
        tp->query_prop(LOTHMIR_I_INTROD))
    {
        ltxt = tp->query_name()+" ";
    }
    else
    {
        ltxt = CAP(LANG_ADDART(tp->query_nonmet_name()))+" ";
    }
    switch(flag)
    {
    case LOG_RESTRICTED:
        ltxt += "asked for "+hname+", but I refused to sell.";
	break;
    case LOG_OUT_OF_STOCK:
        ltxt += "asked for "+hname+", but I didn't have it in stock.";
	break;
    case LOG_CANT_AFFORD:
        ltxt += "asked for "+hname+", but could not afford it.";
	break;
    default:
        ltxt += "bought "+hname+".";
	break;
    }
    if (Herb_buyer)
    {
        Herb_buyer += ({ ltxt });
    }
    else
    {
        Herb_buyer = ({ ltxt });
    }
} /* log_purchase */


/*
 * Function name:	can_afford
 * Description	:	pay for the herb, if can afford it
 * Arguments	:	int price -- price in copper
 * Returns	:	1 if player pays for the herb, 0 if not
 */
public int
can_afford(int price)
{
    Money_arr = pay(price, TP, 0, 0, 0, 0);
    if (sizeof(Money_arr) == 1)
    {
        return 0;
    }
    Coin_pay_text = text(exclude_array(Money_arr, NUM, NUM*2-1));
    Coin_get_text = text(exclude_array(Money_arr, 0, NUM-1));
    write("You pay "+Coin_pay_text+" to "+process_string(QCTNAME(TO))+".\n");
    if (Coin_get_text)
    {
        write("You get "+Coin_get_text+" back.\n");
    }
    return 1;
} /* can_afford */



/*
 * Function name:	sell
 * Description	:	handle attempts to sell herbs
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 -- always
 */
public int
sell(string arg)
{
    int		price,
		asked_for,
		hn;
    object	herb_ob,
		tp = TP,
		thiso = TO,
		*obj;
    mixed	*hdata,
		nosell;
    string	hname;

    if (!CAN_SEE_IN_ROOM(thiso))
    {
	room_too_dark();
        return 1;
    }
    if (!CAN_SEE(thiso, tp))
    {
	cant_see();
        return 1;
    }
    if (!tp->query_prop(LOTHMIR_I_INTROD))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
	dont_know(tp);
	return 1;
    }
    if (!strlen(arg))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
        command("say What herb do you want to sell?");
        command("chuckle");
        return 1;
    }

    arg = LOW(arg);
    if (arg == "all")
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
        command("say Sorry, but I will only buy herbs.");
        return 1;
    }

    if (arg == "all herbs")
    {
        do_sell_all(tp);
        return 1;
    }


    if (!sizeof(obj = FIND_STR_IN_ARR(arg, all_inventory(tp))))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
        command("say What herb do you want to sell?");
        command("smile");
        return 1;
    }
    if (!sizeof(obj = filter(obj, herb_filter)) ||
        (!objectp(herb_ob = obj[0])))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
        command("say You have no herb of that kind, "
          + ((tp->query_gender() == G_MALE) ? "sir" : "my lady")+".");
        return 1;
    }

    tell_room(ENV(thiso),
	QCTNAME(tp)+" offers a herb to "+QTNAME(thiso)+".\n", tp);

    if (nosell = herb_ob->query_prop(OBJ_M_NO_SELL))
    {
	if (stringp(nosell))
	{
	    write(nosell);
	}
	command("say I'm sorry, but I cannot accept that herb.");
	return 1;
    }

    hname = herb_ob->query_herb_name();
    // added for training, Olorin
    if (tp->query_prop(LOTHMIR_S_HERB) == hname)
    {
        asked_for = 1;
        tp->add_prop(LOTHMIR_S_HERB, LOTHMIR_S_HERB_SOLD);
    }
    if (herb_ob->do_id_check(thiso))
    {
        price = herb_ob->query_herb_value() / 2;
        switch(random(4))
        {
            case 0: 
                command("say I'm amazed, it is "+LANG_ADDART(hname)+"!"); 
                break;
            case 1:
                command("say Oh dear, if it isn't a genuine "+hname+"!");
                break;
            case 2: 
                command("say Hmm ... oh yes! "+CAP(LANG_ADDART(hname))+"!"); 
                break;
            case 3:
                command("say Most interesting! "+CAP(LANG_ADDART(hname))+"!");
                break;
        }
    }
    else
    {
        command("gasp");
        command("say By the Holy Beard of Eru! This is unknown to me!");
        command("blush");
        command("say 87 years of gathering herbs, but yet another "
          + "unknown "+herb_ob->query_name()+"!");
        command("think");
        command("say I'll pay you " + herb_ob->query_herb_value()
          + " coppers for this, "
          + ((tp->query_gender() == G_MALE) ? "sir" : "my lady") +"!");
        price = herb_ob->query_herb_value();
    }
    if (pointerp(hdata = All_herbs[hname]) &&
        hdata[H_COUNT] > MAX_INV)
    {
        price = price/2;
        command("say I cannot give you the full price for the "
              + hname + ".");
        command("say I already have " + LANG_WNUM(hdata[H_COUNT]) 
              + " of the same.");
    }
    do_pay(tp, price);
    add_herb(herb_ob);
    if (asked_for)
    {
        command("say I will now teach you, if you ask me to.");
        asked_for = 0;
    }
    if (Ask_help_alarm_id)
    {
    	remove_alarm(Ask_help_alarm_id);
    }
    Ask_help_alarm_id = set_alarm(itof(random(8) + 4), 0.0,
	&ask_help_herb_book(tp));
    return 1;
} /* do_sell */


/*
 * Function name:	do_sell_all
 * Description	:	handle "sell all herbs"
 * Arguments	:	object player -- the person selling
 */
public void
do_sell_all(object player)
{
    object	*herb_obs,
		tp = TP,
		thiso = TO;
    mixed	hdata;
    string	hname,
		sherb;
    int		total_price,
		price,
		hn,
		max_n,
		no_h,
		n;

    herb_obs = filter(filter(all_inventory(player), herb_filter),
	&operator(==)(0) @ &->query_prop(OBJ_M_NO_SELL));
    no_h = sizeof(herb_obs);
    if (no_h <= 0)
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
        command("say But you have no herbs to sell!");
        command("shrug");
        return;
    }
    tell_room(ENV(thiso),
	QCTNAME(tp)+" offers some herbs to "+QTNAME(thiso)+".\n", tp);
    max_n = MIN(MAX_XFER, no_h);
    sherb = player->query_prop(LOTHMIR_S_HERB);
    while (n < max_n)
    {
	hname = herb_obs[n]->query_herb_name();
        if (herb_obs[n]->do_id_check(thiso))
	{
            price = herb_obs[n]->query_herb_value() / 2;
	}
        else 
	{
            price = herb_obs[n]->query_herb_value();
	}
	if (pointerp(hdata = All_herbs[hname]) &&
	    hdata[H_COUNT] > MAX_INV)
	{
            price = price / 2;
        }
        command("say One " + hname + " - " + price + " coppers.");
        total_price += price;
        if (hname == sherb)
        {
            tp->add_prop(LOTHMIR_S_HERB, LOTHMIR_S_HERB_SOLD);
	    sherb = "";
            command("say Thanks for bringing a " + hname +
		" as I asked you to.");
            command("say I will now teach you, if you ask me to.");
        }
        add_herb(herb_obs[n]);
        n++;
    }
    if (max_n < no_h)
    {
        command("say I'll just take the first "+MAX_XFER_WORD+
	   " of your herbs.");
        command("say Any more and my old brain might forget how much I "
          + "am supposed to pay you!");
        command("blush");
    }
    do_pay(player, total_price);
} /* do_sell_all */


/*
 * Function name:	do_pay
 * Description	:	pay the player
 * Arguments	:	object player -- person to pay
 *			int price -- price in coppers
 */
public void
do_pay(object player, int price)
{
    string	myname;
    object	gc, 
		sc, 
		cc;
    int		g, 
		s, 
		c;

    command("emote counts some coins from a pouch.");
    g = price / 144;
    s = (price - (g*144)) / 12;
    c = price - g*144 - s*12;
    cc = MONEY_MAKE_CC(c);
    myname = (player->query_met(TO) ? 
	      query_name() : "The "+query_nonmet_name());
    if (g)
    {
        gc = MONEY_MAKE_GC(g);
        write(myname+" gives you " + g + " gold coins.\n");
        gc->move(TP, 1);
    }
    if (s)
    {
        sc = MONEY_MAKE_SC(s);
        write(myname+" gives you " + s + " silver coins.\n");
        sc->move(TP, 1);
    }
    if (c)
    {
        cc = MONEY_MAKE_CC(c);
        write(myname+" gives you " + c + " copper coins.\n");
        cc->move(TP, 1);
    }
    command("smile");
} /* do_pay */


/*
 * Function name:	add_herb
 * Description	:	add herb to inventory
 * Arguments	:	object herb_ob -- the one to add
 */
public void
add_herb(object herb_ob)
{
    string	herb_file,
		hname;
    int		i,
		n;
    mixed	*hdata;

    if (!objectp(herb_ob))
    {
        return;
    }
    hname = herb_ob->query_herb_name();
    herb_file = MASTER_OB(herb_ob);
    if (pointerp(hdata = All_herbs[hname]))
    {
	++hdata[H_COUNT];
	if (herb_file != hdata[H_FILE])
	{
	    /* paranoia? */
	    log_file(LOG_BUG,
		ctime(time())+" Conflicting files "+
		herb_file+" and "+hdata[H_FILE]+" for '"+hname+"'.\n");
	}
        herb_ob->remove_object();
        return;
    }
    command("say Excellent! I had run out of "+hname+".");
    hdata = allocate(3);
    hdata[H_FILE] = herb_file;
    hdata[H_COUNT] = 1;
    hdata[H_VALUE] = herb_ob->query_herb_value();
    All_herbs[hname] = hdata;
    herb_ob->remove_object();
    save_object(HERBAL_SAVE);
} /* add_herb */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to catch gifts of herbs
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    int     ran;

    ::enter_inv(ob, from);

    if (!living(from))
    {
        return;
    }
    if (!function_exists("create_herb", ob))
    {
        set_alarm(1.0, 0.0, &not_herb(ob, from));
    }
    else if (Given_herb ||
	     Test_id_alarm_id)
    {
        set_alarm(1.0, 0.0, &give_back_immediately(ob, from));
    }
    else
    {
    	Test_id_alarm_id = set_alarm(5.0, 0.0, &test_identify(ob, from));
    }
    return;
} /* enter_inv */


/*
 * Function name:	not_herb
 * Description	:	return gifts that are not herbs
 * Arguments	:	object ob -- the object
 *			object from -- its source
 */
public void
not_herb(object ob, object from)
{
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
	command("shrug");
	command("drop "+OB_NAME(ob));
	return;
    }
    if (!CAN_SEE(TO, from))
    {
	command("say Who gave me this?");
	cant_see();
	command("drop "+OB_NAME(ob));
	return;
    }
    if (!good_guild_test(from))
    {
        command("say I am too busy to be disturbed with "
	  + LANG_PWORD(ob->query_name()) + ", "
          + from->query_race_name()+".");
	command("drop "+OB_NAME(ob));
	return;
    }
    command("say I do not care for anything but herbs!");
    switch(random(4))
    {
        case 0:
            command("say Why should I care about a silly "
              + ob->query_name()+"?");
            break;
        case 1:
            command("say I am too busy to be disturbed with "
              + LANG_PWORD(ob->query_name())+", "
              + from->query_race_name()+".");
            break;
        case 2:
            command("say I am a herbalist, "+from->query_race_name()
              + ", not a pawnshop owner!");
            break;
        case 3:
            command("say This is of no interest to me, "
              + ((from->query_gender() == G_MALE) ? "mister" : "madam")
              + ".");
            break;
    }
    command("give "+OB_NAME(ob)+" to "+from->query_real_name());
} /* not_herb */


/*
 * Function name:	give_back_immediately
 * Description	:	return herb when are busy with another one
 * Arguments	:	object herb -- the one to return
 *			object from -- its source
 */
public void
give_back_immediately(object herb, object from)
{
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
	/* it's a herb .. keep it */
        add_herb(herb);
	return;
    }
    if (!CAN_SEE(TO, from))
    {
	command("say Who gave me this?");
	cant_see();
	command("drop "+OB_NAME(herb));
	return;
    }
    command("say Please wait till I am finished with this other herb, "
      + ((from->query_gender() == G_MALE) ? "sir" : "my lady")+".");
    command("give " + OB_NAME(herb) + " to "
      + from->query_real_name());
    if (ENV(herb) == TO)
    {
	command("drop "+OB_NAME(herb));
    }
} /* give_back_immediately */


/*
 * Function name:	test_identify
 * Description	:	identify an herb
 * Arguments	:	object herb -- the one to identify
 *			object from -- its source
 */
public void
test_identify(object herb, object from)
{
    string	id_str,
		find_str;

    Test_id_alarm_id = 0;
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
	/* it's a herb .. keep it */
        add_herb(herb);
	return;
    }
    if (!CAN_SEE(TO, from))
    {
	command("say Who gave me this?");
	cant_see();
	command("drop "+OB_NAME(herb));
	return;
    }
    if (!from->query_prop(LOTHMIR_I_INTROD))
    {
	dont_know(from);
	command("give " + OB_NAME(herb) + " to "
	    + from->query_real_name());
	if (ENV(herb) == TO)
	{
	    command("drop "+OB_NAME(herb));
	}
	return;
    }
    Given_herb = herb;
    command("emote looks closely at the "+Given_herb->query_name()+".\n");
    command("think");
    switch(Given_herb->query_id_diff() / 10)
    {
        case 0:
            command("laugh");
            id_str = "Even the children can recognize this one.";
            break;
        case 1:
            command("giggle");
            id_str = "Hmm ... one of the easiest recognizable herbs.";
            break;
        case 2:
            command("giggle");
            id_str = "Ahh ... a nice one. Some people often mistake "
                   + "this for another.";
            break;
        case 3:
            command("frown");
            id_str = "I've seen this one a lot. Easily mistaken though.";
            break;
        case 4:
            command("smile");
            id_str = "Ah - I can't blame you for not recognizing "
                   + "this one.";
            break;
        case 5:
            command("smile");
            id_str = "Exciting! This one is hard to tell from the "
                   + "Crimbul herb.";
            break;
        case 6:
            command("think");
            id_str = "My dear friend - you need to be quite skilled "
                   + "to identify this one.";
            break;
        case 7:
            command("eyebrow");
            id_str = "Oh! Can it really be ... ? Ah ... yes it is.";
            break;
        case 8:
            command("emote looks baffled.");
            id_str = "By the Holy Beard of Eru!! This is one of "
                   + "the most difficult herbs!";
            break;
        case 9:
            command("gasp");
            id_str = "Oh dear. Not even I am sure about this ... "
		   + "but ... it must be.";
            break;
        case 10:
            command("confused");
            id_str = "Impossible! Absolutely impossible! "
		   + "It just can't be ... ?!";
            break;
        default:
            log_file(LOG_BUG,
                ctime(time())+" bad id_diff of " +
                Given_herb->query_id_diff() + " for " +
                Given_herb->query_herb_name() + " (" +
                file_name(Given_herb) + ")\n");
            command("confused");
            id_str = "Impossible! Absolutely impossible! "
                   + "It just can't be ... ?!";
            break;
    }
    command("say "+id_str);
    switch(Given_herb->query_find_diff())
    {
        case 0:
            command("laugh");
            find_str = "Ah ... this is as normal as ordinary grass.";
            break;
        case 1:
            command("giggle");
            find_str = "This one is quite a usual sight.";
            break;
        case 2:
            command("grin .");
            find_str = "Not so hard to find.";
            break;
        case 3:
            command("smile");
            find_str = "Interesting. Not everybody knows where to "
                     + "find this one.";
            break;
        case 4:
            command("smile");
            find_str = "Good work! This one is not easy to locate.";
            break;
        case 5:
            command("smile");
            find_str = "Ah! I guess you spent some time looking "
                     + "for this one!";
            break;
        case 6:
            command("think");
            find_str = "Hmmm. I wonder where you found this one?";
            break;
        case 7:
            command("whistle");
            find_str = "You must have been quite lucky to find this "
                     + "herb!";
            break;
        case 8:
            command("gasp");
            find_str = "I am absolutely astonished! This is "
                     + "extremely rare!";
            break;
        case 9:
            command("emote looks totally flabbergasted.");
            find_str = "How can this be?? I have only seen this "
                     + "herb about twice in my life!";
            break;
        case 10:
            command("confused");
            find_str = "I cannot believe it! You have actually "
                     + "found it! I have only read about this in old "
                     + "books of herblore!";
            break;
        default:
            log_file(LOG_BUG,
                ctime(time())+" bad find_diff of " +
                Given_herb->query_find_diff() + " for " +
                Given_herb->query_herb_name() + " (" +
                file_name(Given_herb) + ")\n");
            command("confused");
            find_str = "I cannot believe it! You have actually "
                     + "found it! I have only read about this in old "
                     + "books of herblore!";
            break;
    }
    command("say "+find_str);
    if (Given_herb->do_id_check(TO))
    {
        command("say "+Given_herb->query_id_long());
    }
    else
    {
        command("say I do not know what effect this "
              + Given_herb->query_name()+" might have.");
    }
    command("give "+OB_NAME(Given_herb)+" to "+from->query_real_name());
    command("say I hope my information has been useful, "
      + ((from->query_gender()==G_MALE) ? "sir" : "my lady")+".");
    command("bow");
    Given_herb = 0;
} /* test_identify */


/*
 * Function name:	show_herb
 * Description	:	respond to a question about a specific herb
 * Arguments	:	string hname -- the herb name
 *			mixed *hdata -- the data for this herb
 * Returns	:	1 on success, 0 on failure
 */
public int
show_herb(string hname, mixed *hdata)
{
    object	herb;

    if (!(herb = clone_object(hdata[H_FILE]))) 
    {
	return 0;
    }
    command("say Ahhh, "+hname+".");
    command("ponder");
    if (herb->do_id_check(TO))
    {
	command("say To the uninitiated, "+hname+" appears as "+
	    LANG_ADDART(herb->short())+".");
	command("say However, the accomplished herbalist sees:");
        tell_room(ENV(),  herb->query_id_long());
    }
    else
    {
	command("say "+CAP(hname)+" appears as "+
	    LANG_ADDART(herb->short())+".");
        command("say I really cannot tell you more.");
	command("shrug ruefully");
    }
    command("emote starts looking through his herb-storage.");
    if (hdata[H_COUNT] > 0)
    {
	command("say I have "+LANG_WNUM(hdata[H_COUNT])+" in stock.");
    }
    else
    {
	command("say I have none in stock.");
    }
    herb->remove_object();
    return 1;
} /* show_herb */

/*
 * Function name:	intro_me
 * Description	:	respond to introductions
 * Arguments	:	string name -- name of the introduced living
 */
public void
intro_me(string name)
{
    object	pl = find_player(lower_case(name));
    
    if (!objectp(pl))
    {
	return;
    }
    if (ENV(pl) != ENV())
    {
        pl->add_prop(LOTHMIR_I_INTROD, 1);
        return;
    }
    if (pl->query_prop(LOTHMIR_I_INTROD))
    {
        command("greet " + name);
        command("say Nice to see you again, " + pl->query_name() + "!");
        return;
    }
    pl->add_prop(LOTHMIR_I_INTROD, 1);
    command("hail " + name);
    command("say My name is Lothmir. I'm the herb-master of the "
      + "Rangers of Gondor.");
    command("present me");
} /* intro_me */


/*
 * Function name:	add_introduced
 * Description	:	Set an alarm to respond to an introduction
 * Arguments	:	string name -- name of the introduced living
 */
public void
add_introduced(string name)
{   
    set_alarm(3.0, 0.0, &intro_me(name));
} /* add_introduced */



/*
 * Function name:	do_bow
 * Description	:	respond to a bow
 * Arguments	:	object pl -- the person who bowed
 */
public void
do_bow(object pl)
{
    if (objectp(pl) &&
	ENV(pl) == ENV())
    {
        command("bow " + pl->query_real_name());
	command("say What can I do for you?");
	command("say If you have an unknown herb, you can let me "
	      + "identify it for you.");
    }
} /* do_bow */


/*
 * Function name:	respond_bow
 * Description	:	set an alarm to respond to a bow
 */
public void
react_bow()
{
    set_alarm(3.0, 0.0, &do_bow(TP));
} /* react_bow */


/*
 * Function name:	remove_tmp_flag
 * Description	:	clear the No_report_flag (called via alarm)
 */
public void
remove_tmp_flag()
{
    No_report_flag = 0;
} /* remove_tmp_flag */


/*
 * Function name:	ask_help_herb_book
 * Description	:	ask for help with herb book
 * Arguments	:	object player -- the person to ask
 */
public void
ask_help_herb_book(object player)
{
    command("hmm");
    if (ENV(player) != ENV(this_object()) ||
	No_report_flag)
    {
        return;
    }
    command("ponder");
    command("peer " + player->query_real_name());
    command("say The rangers want to write a book about herbs in Gondor ");
    command("say and elsewhere in the world.");
    command("say It should tell where one can find which herbs, ");
    command("say and other things about herbs. ");
    command("say You can contribute by reporting here where you "+
	"found a herb.");
    command("say You can also <report> here if you are ");
    command("say interested in making a book out of all the reports!");
    No_report_flag = 1;
    if (Rem_flag_alarm_id)
    {
	remove_alarm(Rem_flag_alarm_id);
    }
    Rem_flag_alarm_id = set_alarm(120.0, 0.0, remove_tmp_flag);
} /* ask_help_herb_book */

/*
 * Function name:	catch_question
 * Description	:	mask /std/act/asking.c's catch_question()
 *			so we can strip leading "about " and trailing "?"
 * Arguments:		string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string tmpstr;

    if (objectp(query_attack()))
    {
	return;	/* no answers if fighting */
    }

    if (strlen(question))
    {
	question = LOW(question);
	/* strip off leading "about " and trailing " ?" */
	if (sscanf(question, "about %s", tmpstr))
	{
	    question = tmpstr;
	}
	if (sscanf(question, "%s ?", tmpstr) ||
	    sscanf(question, "%s?", tmpstr))
	{
	    question = tmpstr;
	}
    }
    ::catch_question(question);
} /* catch_question */


/*
 * Function name:	answer_question
 * Description	:	React to a question
 * Arguments	:	mixed msg -- string to reply, or function to call
 *			int cmd -- flag if this answer is a command
 */
public void
answer_question(mixed msg, int cmd)
{
    if (!CAN_SEE(TO, TP))
    {
	cant_see();
    }
    else if (!TP->query_prop(LOTHMIR_I_INTROD))
    {
	dont_know(TP);
    }
    else
    {
	::answer_question(msg, cmd);
    }
} /* answer_question */


/*
 * Function name:	default_answer
 * Description	:	answer to questions we don't understand
 * Returns	:	"" (answer is written before return)
 */
public string
default_answer()
{
    mixed	*hdata;
    string	*prep = ({ "about", "for", "show", }),
		hname,
		q = query_question();

    /* "ask" insists on having a question, so no need to
     * check strlen
     */
    if (!parse_command(q, ({}), "%p %s", prep, hname))
    {
	hname = q;
    }
    if (!good_guild_test(TP) ||
	(!pointerp(hdata = All_herbs[hname]) && 
	 !pointerp(hdata = All_herbs[LANG_SWORD(hname)])) ||
	!show_herb(hname, hdata))
    {
	command("say I don't know what you are talking about!");
    }
    return "";
} /* default_answer */


/*
 * Function name:	ask_herbs
 * Description	:	respond to questions about "herb" or "herbs"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_herbs()
{
    command("say Herbs?");
    command("say Well, I know most of them!");
    command("say You can buy some from me, and I sell herbs, too!");
    command("say If you have an unknown herb, I can try to identify");
    command("say it for you, if you give it to me.");
    command("say If you want to learn about herblore, ask me about it.");
    return "";
} /* ask_herbs */


/*
 * Function name:	ask_lore
 * Description	:	respond to questions about "herblore" or "lore"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_lore()
{
    command("say Herb lore?");
    command("say Well, there are only few who know as much about "+
	    "herbs as I do!");
    command("say But even I do not know all the places where herbs grow!");
    command("say You might check in the library in the rangers' guild.");
    command("say But the books there are ancient.");
    if (query_question() == "lore")
    {
	command("peer "+TP->query_real_name());
        command("say Or did you mean the herb named lore?");
        default_answer();
    }
    if (Ask_help_alarm_id)
    {
	remove_alarm(Ask_help_alarm_id);
    }
    Ask_help_alarm_id = set_alarm(10.0, 0.0, &ask_help_herb_book(TP));
    return "";
} /* ask_lore */


/*
 * Function name:	ask_rabbit
 * Description	:	respond to questions about "rabbit"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_rabbit()
{
    command("say Rabbit?");
    command("peer " + TP->query_real_name());
    command("say If you want to make a meal from a rabbit, ");
    command("say you should never fail to use appropriate herbs!");
    command("say You could use basil, savory, or tarragon!");
    return "";
} /* rabbit */


/*
 * Function name:	ask_stew
 * Description	:	respond to questions about "stew" or "rabbit stew"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_stew()
{
    command("say Stew?");
    command("peer " + TP->query_real_name());
    command("say Well, if you want to make a tasty stew, ");
    command("say don't forget to add a few herbs!");
    command("say I can recommend chervil, ginger, and laurel!");
    command("emote licks his lips thinking of a tasty stew.");
    return "";
} /* ask_stew */


/*
 * Function name:	ask_garlic
 * Description	:	respond to questions about "garlic"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_garlic()
{
    command("say Garlic?");
    command("peer " + TP->query_real_name());
    command("hmm");
    command("say Well, if you meet some, you will recognize it "+
	    "from the stench.");
    command("say It's mainly used to flavour dishes, ");
    command("say but some rhymes of old claim that it has "+
	    "magical properties, ");
    command("say protecting against some kinds of undead.");
    command("shrug");
    command("say Well, I don't know if that's true.");
    return "";
} /* ask_garlic */


/*
 * Function name:	ask_buyers
 * Description	:	respond to questions about "buyers" or "customers"
 * Returns	:	"" (answer is written before return)
 */
public string
ask_buyers()
{
    int		i,
		j,
		m,
		n;
    object	tp = TP;
    string	name,
		*tmpbuyers;

    if (!IS_RANGER(tp))
    {
        command("say Why would I tell you?");
        return "";
    }
    /* XXX need to replace this magic number with #define'd names */
    if (tp->query_ranger_rank(1) >= 980 ||
        tp->query_wiz_level())
    {
        m = n = sizeof(Herb_buyer);
        if (n <= 0)
        {
            command("say Hmm, nobody has bought anything worth "+
		    "mentioning yet today.");
            command("say Maybe that is good for the Rangers, but "+
		    "it's bad for business.");
            command("smile grim");
            return "";
        }
        command("say Hmm, let's see what I can remember ...");
	name = tp->query_real_name();
	tmpbuyers = Herb_buyer;
        i = MIN(5, n);
	while (i-- > 1)
        {
	    /* chose buyer at random, and remove from tmp list
	     * so we don't repeat ourselves.
	     */
	    j = random(m);
            command("whisper "+name+" "+tmpbuyers[j]);
	    tmpbuyers = exclude_array(tmpbuyers, j, j);
	    --m;
            if (!random(2))
	    {
                command(ONE_OF_LIST(({"ponder","think","scratch chin"})));
	    }
        }
        command("whisper "+name+" "+tmpbuyers[0]);
        if (n > 5) 
	{
            command("say Hmm ... if you ask me again later, "+
		    "I may remember more.");
	}
    }
    else
    {
        command("say I will only answer to a Ranger Officer.");
    }
    return "";
} /* ask_buyers */


/*
 * Function name:	do_report
 * Description	:	make a herb report
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 (always)
 */
public int
do_report(string arg)
{
    string name;

    Report_name = TP->query_name() + ": ";
    if (!TP->query_prop(LOTHMIR_I_INTROD))
    {
	dont_know(TP);
	return 1;
    }
    if (!arg)
    {
        Log_str = "";
        Book_str = "";
        write("Please report where you found which herb: \n"
          + "(** to end, ~q to abort, ~l to redraw) \n"
          + "    Herb name	Location and remarks\n--> ");
        input_to("write_more");
    }
    else
    {
	write("Thanks for your contribution!\n");
    }
    return 1;
} /* do_report */


/*
 * Function name:	write_more
 * Description	:	continue writing herb report
 * Arguments	:	string arg -- the line written
 */
public void
write_more(string arg)
{
    string text;

    if (arg == "**")
    {
	text = extract(ctime(time()), 4, 10) +
	       extract(ctime(time()), -4) +
	       " "+file_name(ENV())+" ("+Report_name+")\n"+
	       Log_str+"\n";
        write("Thanks for your contribution!\n");
    }
    else if (arg == "~q")
    {
        write("Report aborted!\n");
    }
    else if (arg == "~l")
    {
        write(Log_str+"\n");
        input_to("write_more");
    }
    else
    {
        Log_str += (arg+"\n");
        Book_str += (Report_name+arg+"\n");
        write("--> ");
        input_to("write_more");
    }
} /* write_more */


/*
 * Function name:	set_up_skills
 * Description	:	set lothmir up to train herbalism
 */
public void
set_up_skills()
{
    string  me = "to recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM, ({me, me}), 0, 0, 30);
} /* set_up_skills */


/*
 * Function name:	remove_herb_from_list
 * Description	:	remove a herb from our inventory list
 * Argument	:	string hname -- the name of the herb
 * Returns	:	1 if removed herb, 0 if not found,
 *			-1 if bad arg or not allowed
 *
 * this is not used by any code here.  i assume it exists for
 * wizardly convenience.
 */
public int
remove_herb_from_list(string hname)
{
    if (!strlen(hname) ||
	!check_allowed("remove all "+hname+" from Lothmir"))
    {
	return -1;
    }

    if (!pointerp(All_herbs[hname]))
    {
	hname = LANG_SWORD(hname);
	if (!pointerp(All_herbs[hname]))
	{
	    return 0;
	}
    }
    All_herbs = m_delete(All_herbs, hname);
    save_object(HERBAL_SAVE);
    return 1;
} /* remove_herb_from_list */


/*
 * Function name:	add_ranger_herb
 * Description	:	add a herb to the list of ranger herbs
 * Arguments	:	string hname -- herb_name of the herb to add
 * Returns	:	1 if added herb, 0 if already in list,
 *			-1 if bad arg or not allowed
 *
 * this is not used by any code here.  i assume it exists for
 * wizardly convenience.
 */
public int
add_ranger_herb(string hname)
{
    if (!strlen(hname) ||
	!check_allowed("add "+hname+" to Lothmir's ranger herbs"))
    {
        return -1;
    }
    if (member_array(hname, Ranger_herbs) >= 0)
    {
	return 0;
    }
    if (pointerp(Ranger_herbs))
    {
        Ranger_herbs += ({ hname });
    }
    else
    {
        Ranger_herbs = ({ hname });
    }
    save_object(HERBAL_SAVE);
    return 1;
} /* add_ranger_herb */


/*
 * Function name:	remove_ranger_herb
 * Description	:	remove a herb from the list of ranger herbs
 * Arguments	:	string hname -- herb_name of the herb to remove
 * Returns	:	1 if removed herb, 0 if not in list,
 *			-1 if bad arg or not allowed
 *
 * this is not used by any code here.  i assume it exists for
 * wizardly convenience.
 */
public int
remove_ranger_herb(string hname)
{
    int i;

    if (!strlen(hname) ||
	!check_allowed("remove "+hname+" from Lothmir's ranger herbs"))
    {
        return -1;
    }
    i = member_array(hname, Ranger_herbs);
    if (i < 0)
    {
        return 0;
    }
    Ranger_herbs = exclude_array(Ranger_herbs, i, i);
    save_object(HERBAL_SAVE);
    return 1;
} /* remove_ranger_herb */


/*
 * Function name:	check_allowed
 * Description	:	check that person calling routines
 *			to mess with inventory is a gondor 
 *			wizard or an arch
 * Arguments	:	string action -- what they tried to do
 * Returns	:	1 if allowed, 0 if not
 */
public int
check_allowed(string action)
{
    int		i;
    object	prev;
    string	name,
		prev_chain = "";

    for (i = 0; objectp(prev = previous_object(i)); --i)
    {
	if (interactive(prev))
	{
	    name = prev->query_real_name();
            if (prev->query_wiz_level() &&
		(SECURITY->query_wiz_dom(name) == "Gondor" ||
		 SECURITY->query_wiz_rank(name) >= WIZ_ARCH))
	    {
		return 1;
	    }
	    log_file(LOG_VIOLATIONS,
		ctime(time())+" "+name+" tried to "+action+".\n");
	    return 0;
	}
	prev_chain += "\t"+file_name(prev)+" "+prev->query_name()+"\n";
    }
    /* could not find interactive who called us */
    log_file(LOG_VIOLATIONS,
	ctime(time())+" someone tried to "+action+". Called by:\n"+
	    prev_chain);
    return 0;
} /* check_allowed */


/*
 * Function name:	second_life
 * Description	:	outlaw killer
 * Arguments	:	object killer -- our murderer
 * Returns	:	0 (always ... we die)
 */
public int
second_life(object killer)
{
    (R_OUTLAW)->add_outlaw(killer->query_real_name());
    write_file("/d/Gondor/log/rangerpunish", killer->query_name()
      + " was outlawed for the murder of "+TO->query_name()+", on "
      + ctime(time())+".\n");
    return 0;
} /* second_life */


/*
 * Function name:	room_too_dark
 * Description	:	refuse to deal w players when room is dark
 */
public void
room_too_dark()
{
    command("say Uhmm, you wouldn't by any chance have a "
	+ "torch handy?");
    command("say It's too dark for me to do business.");
} /* room_too_dark */


/*
 * Function name:	cant_see
 * Description	:	refuse to deal w players when can't see them
 */
public void
cant_see()
{
    command("say Uhmm, where are you hiding? I can't see you!");
    command("suspicious");
} /* cant_see */


/*
 * Function name:	dont_know
 * Description	:	refuse to deal w players who don't intro
 */
public void
dont_know(object tp)
{
    command("peer suspiciously "+tp->query_real_name());
    command("say We haven't met, have we?");
    command("say I can't do business with people I don't know.");
} /* dont_know */


/*******	skill code follows			******/


/*
 * Function name:	sk_improve
 * Description	:	handle attempts to "improve"
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
int
sk_improve(string arg)
{
    object	tp = TP,
		thiso = TO;
    string	*tmp,
		sherb;
    int		n,
		steps,
		success,
		old_skill;

    if (!CAN_SEE_IN_ROOM(thiso))
    {
	room_too_dark();
        return 1;
    }
    if (!CAN_SEE(thiso, tp))
    {
	cant_see();
        return 1;
    }
    if (!tp->query_prop(LOTHMIR_I_INTROD))
    {
	tell_room(ENV(thiso),
	    QCTNAME(tp)+" murmurs something to "+QTNAME(thiso)+".\n", tp);
	dont_know(tp);
	return 1;
    }

    if (tp->query_guild_name_occ() == RANGER_S_GUILD_NAME &&
        RECRUITHALL->query_ranger(capitalize(tp->query_real_name())))
    {
	command("peer " + tp->query_name());
	command("say Why don't you train in the Rangers' Guild?");
	command("shrug");
	return 1;
    }

    if (tp->query_skill(SS_HERBALISM) > 10)
    {
	sherb = tp->query_prop(LOTHMIR_S_HERB);
	if (!strlen(sherb))
	{
	    tell_herb(tp);
	    return 1;
	}
	if (sherb != LOTHMIR_S_HERB_SOLD)
	{
	    command("peer " + tp->query_name());
	    command("say Go and bring me some "+sherb+".");
	    command("say You sell me that herb, I teach you something.");
	    command("say You don't, I don't.");
	    command("say Understood?");
	    command("peer " + tp->query_name());
	    return 1;
	}
    }

    /* Lothmir teaches only one level at a time */
    if (strlen(arg))
    {
	n = sizeof(tmp = explode(arg, " "));
	if (n > 1 &&
	    sscanf(tmp[n - 1], "%d", steps) == 1 &&
	    steps > 1)
	{
	    command("smile " + tp->query_name());
	    command("say I teach only one lesson at a time.");
	    command("say Don't be so hasty, my friend!");
	    command("say It took me a long time to learn what I know!");
	    return 1;
	}
    }

    old_skill = tp->query_skill(SS_HERBALISM);
    success = ::sk_improve(arg);
    if (success &&
	tp->query_skill(SS_HERBALISM) > old_skill)
    {
	tp->remove_prop(LOTHMIR_S_HERB);
    }
    return success;
} /* sk_improve */


/*
 * Function name:	sk_hook_raise_rank
 * Description	:	player trained successfully -- write/say msgs
 * Arguments	:	int snum -- skill trained
 *			int to_lev -- level reached
 *			int cost -- how much paid
 */
public void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string	rank,
		long_str;

    rank = sk_rank(to_lev);
    command("smile "+TP->query_name());
    write(process_string(QCTNAME(TO))+" teaches you " +
	sk_tdesc[snum][0]+".\n");
    write("You achieve the rank of "+rank+".\n");
    LSAY(process_string(QCTNAME(TO))+" teaches ",
	" "+sk_tdesc[snum][1]+" and helps "+OBJECTIVE(TP)+
	" to reach the rank of "+rank+".");
} /* sk_hook_raise_rank */


/*
 * Function name:	sk_hook_write_header
 * Description	:	Write the header to the improve or learn list
 * Arguments	:	int lessons - How many steps we are talking about
 */
public void
sk_hook_write_header(int lessons)
{
    object	thiso = TO, tp = TP;
    if (!lessons)
    {
        lessons = 1;
    }
    command("smile "+tp->query_name());
    command("say These are the skills in which I can teach you");
    command("say "+LANG_WNUM(lessons)+
	(lessons == 1 ? " lesson" : " lessons")+" or more.");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
    tell_room(ENV(thiso),
	QCTNAME(thiso) + " recites a list of skills for "
          + QTNAME(tp) + ".\n", tp);
} /* sk_hook_write_header */


/*
 * Function name:	sk_hook_no_list_learn
 * Description	:	write the "No more unknown skills" msg
 * Returns	:	1 (always)
 */
public int
sk_hook_no_list_learn()
{
    command("smile "+TP->query_name());
    command("say I cannot teach you any new skill!");
    command("say You might try to improve skills that you have.");
    command("say Or you will have to seek other teachers elsewhere.");
    return 1;
} /* sk_hook_no_list_learn */


/*
 * Function name:	sk_hook_no_list_improve
 * Description	:	write the "no more skills to teach" msg
 * Returns	:	1 (always)
 */
public int
sk_hook_no_list_improve()
{
    command("smile "+TP->query_name());
    command("say There are no more skills that I can help you improve.");
    command("say Perhaps you would feel like learning a new skill?");
    command("say Or you will have to seek other teachers elsewhere.");
    return 1;
} /* sk_hook_no_list_improve */


/*
 * Function name:	sk_hook_improved_max
 * Description	:	write the "cannot raise further" msg
 * Arguments	:	string skill -- the skill attempted
 * Returns	:	1 (always)
 */
public int
sk_hook_improved_max(string skill)
{
    command("smile ruefully "+TP->query_name());
    command("say I cannot teach you any more "+skill+".");
    command("say You will have to seek knowledge elsewhere.");
    return 1;
} /* sk_hook_improved_max */



/*
 * Function name:	tell_herb
 * Description	:	tell player what herb to bring in order
 *			to improve SS_HERBALISM
 * Arguments	:	object player -- the trainee
 */
public void
tell_herb(object player)
{
    string sherb;

    command("hmm");
    command("peer " + player->query_name());
    command("say Why should I teach you anything?");
    command("say I'm a busy man!");
    if (!strlen(sherb = missing_herb()))
    {
	sherb = low_herb();
    }
    if (strlen(sherb))
    {
	command("say On the other hand, I need "+sherb+".");
	command("say Sell me some, and I will teach you one lesson.");
	player->add_prop(LOTHMIR_S_HERB, sherb);
    }
} /* tell_herb */


/*
 * Function name:	missing_herb
 * Description	:	find a herb that we need to restock
 * Returns	:	string -- the name of a herb to restock
 *				  or "" if no need to restock.
 */
public string
missing_herb()
{
    string	*missing;
    int		s;

    missing = filter(HERB_LIST, out_of_stock_filter);
    if ((s = sizeof(missing)))
    {
	return missing[random(s)];
    }
    return "";
} /* missing_herb */


/*
 * Function name:	low_herb
 * Description	:	find a herb that we need to restock
 * Returns	:	string -- the name of a herb to restock
 *				  or "" if no need to restock.
 */
public string
low_herb()
{
    string	*low;
    int		s;

    low = filter(HERB_LIST, low_on_stock_filter);
    if ((s = sizeof(low)))
    {
	return low[random(s)];
    }
    return "";
} /* low_herb */
