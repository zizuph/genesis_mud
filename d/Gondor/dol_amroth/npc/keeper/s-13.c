/* -*- Mode: C -*-
 *
 * npc/keeper/s-13.c
 * 
 * Skippern 20(c)01
 *
 * The shopkeeper of the store in s-13.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/lib/trade";         /* make it handle trading */
inherit "/lib/skill_raise";   /* make it raise skills */
inherit "/std/act/action";    /* make it do things */
inherit "/std/act/chat";      /* make it talk */

#include "../../defs.h"
#include <cmdparse.h>
#include <const.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>

#define HERBAL_SAVE           (DOL_OTHER + "store/s-13")
#define LOG_BUG               "Dol_shop"
#define NUM                   10
#define MAX_INV               30
#define MAX_XFER              10
#define MAX_XFER_WORD         "ten"
#define H_COUNT                1
#define H_VALUE                2
#define H_FILE                 0


/* Global variables */
mapping              All_herbs = ([]);
static int           Ask_help_alarm_id,
                     Test_id_alarm_id,
                     *Money_arr;
static string        Coin_pay_text,
                     Coin_get_text,
                     *Herb_buyer,
                     Log_str;
static object        Given_herb;

/* Prototypes */
public void     set_up_skills();
public void     restore_herbs();
public int      list(string arg);
public int      buy(string arg);
public int      sell(string arg);
public void     add_herb(object herb_ob);
public void     do_pay(object player, int price);
public void     test_identify(object herb, object from);
public void     cant_see();


public void
create_dunadan()
{
    set_living_name("karem");
    set_name("karem");
    add_name( ({ "dunandan", "keeper", "shopkeeper", "herbalist" }) );
    set_race_name("human");
    set_gender(G_FEMALE);
    set_title("Herblover");
    set_dunedain_house("Hador");
    set_long("This lady wears a green robe, and you can smell the scient " +
	     "of any known herb.\n");
    default_config_npc(65);

    set_base_stat(SS_WIS, 78);

    set_skill(SS_APPR_OBJ, 85);
    set_skill(SS_HERBALISM, 85);
    set_skill(SS_APPR_VAL, 85);
    create_skill_raise();
    set_up_skills();

    set_alignment(350);

    set_chat_time(75);
    add_chat("Suranie is an important herb.");
    add_chat("A friend of me said her sex life was improved with some " +
	     "pepper.");

    restore_herbs();
}

string
gender_title(object living)
{
    int gender;
    gender = living->query_gender();
    switch (gender)
    {
    case G_FEMALE   : return ("Miss");
    default         : return ("Sir");
    }
}

/*
 * Function name:    not_herb
 * Description  :    Returns the object to whom gave it or drop it on the
 *                   ground.
 */
public void
not_herb(object herb, object from)
{
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
	command("say Where did this come from?");
	command("drop " + OB_NAME(herb));
	return;
    }
    if (!CAN_SEE(TO, from))
    {
        command("say Who gave me this?");
	cant_see();
	command("drop " + OB_NAME(herb));
	return;
    }
    command("say This is no herb, " + gender_title(from) + ".");
    command("give " + OB_NAME(herb) + " to " + from->query_real_name());
    if (ENV(herb) == TO)
    {
        command("drop " + OB_NAME(herb));
    }
}

/*
 * Function name:    dont_know()
 * Description  :    refuse to deal with people I don't know
 * Arguments    :    object tp -- the people I don't know
 */
public void
dont_know(object tp)
{
    command("peer suspiciously " + tp->query_real_name());
    command("say I don't know you, please introduce, " + gender_title(tp));
}

/*
 * Function name:    room_too_dark()
 * description  :    refuse to deal with players in the dark
 */
public void
room_too_dark()
{
    command("say Uhmm, you wouldn't by any chance have any light sources?");
    command("say I can't see a thing here.");
}

/*
 * Function name:    cant_see()
 * Description  :    refuse to deal with players I can't see
 */
public void
cant_see()
{
    command("say Uhmm, why are you hiding from me?");
    command("suspicious");
    command("say Come out, come out wherever you are....");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("wink");
    command("say You have learned the secret of herbs?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

/*
 * Function name:    restore_herbs()
 * Description  :    restore our inventory of herbs
 *
 * N.B. this used to contain the filenames, not just the herb name.
 *      however, that meant that attempts to rpurchase reserved or
 *      logged herbs were recorded only if the herbs were in stock.
 *      by using the name, all such attempts get recorded.
 *            I need to rewrite this to fit my hermit.
 */
public void
restore_herbs()
{
    restore_object(HERBAL_SAVE);
}

/*
 * Function name:    init_living()
 * Descroption  :    add the verbs for the hermit
 */
public void
init_living()
{
    ::init_living();
    init_skill_raise();
    add_action(list, "list");
    add_action(buy, "buy");
    add_action(sell, "sell");
}

/*
 * Function name:    can_afford
 * Description  :    pay for the herb, if can afford it
 * Arguments    :    int price -- price in copper
 * Returns      :    1 if player pays for the herb, 0 if not
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
    write("You pay " + Coin_pay_text + " to " + process_string(QCTNAME(TO)) +
	  ".\n");
    if (Coin_get_text)
    {
	write("You get " + Coin_get_text + " back.\n");
    }
    return 1;
}

/*
 * Function name:    herb_filter
 * Description  :    decide if argument is a herb
 * Arguments    :    object ob -- the object of interest
 * Returns      :    1 if is herb, 0 if not
 */
public int
herb_filter(object ob)
{
    return (function_exists("create_herb", ob) &&
	    strlen(ob->query_herb_name()) &&
	    ob->query_herb_value());
}

/*
 * Function name:    out_of_stock_filter
 * Description  :    decide if we are out of this herb
 * Arguments    :    string name -- name of the herb
 * Returns      :    1 if out of stock, 0 if not
 */
public int
out_of_stock_filter(string name)
{
    mixed *hdata = All_herbs[name];
    return (!pointerp(hdata) ||
	    !hdata[H_COUNT]);
}

/*
 * Function name:    low_on_stock_filter()
 * Description  :    decide if we are low on this herb
 * Arguments    :    string name -- name of the herb
 * Returns      :    1 if low, 0 if not
 */
public int
low_on_stock_filter(string name)
{
    mixed *hdata = All_herbs[name];
    return (!pointerp(hdata) ||
	    hdata[H_COUNT] < (MAX_INV / 2));
}

/*
 * Function name:    list()
 * Description  :    handle attempts to list herbs
 * Arguments    :    string arg -- whatever the player typed
 * Returns      :    1 -- always
 */
public int
list(string arg)
{
    string     *hnames,
               hlist;
    mixed      *hdata;
    object     tp = TP,
               thiso = TO;
    int        i, n;

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

    tell_room(ENV(thiso), QCTNAME(tp)+" asks "+QCTNAME(thiso)+" a question.\n", tp);

    if (!strlen(arg))
    {
        NF0("List what?\n");
    }
    if (arg == "herbs" || arg == "all herbs")
    {
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
		  QCTNAME(thiso) + " checks his stores, " +
                  "and recites a list of different herbs for " +
		  QCTNAME(tp) + ".\n", tp);
	return 1;
    }
    command("say "+CAP(arg)+", "+arg+" ... let me see ...");
    if (pointerp(hdata = All_herbs[arg]) ||
	pointerp(hdata = All_herbs[LANG_SWORD(arg)]) &&
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
}

/*
 * Funnction name:    buy
 * Description   :    handle attemts to buy herbs
 * Argumnets     :    string arg -- whatever the player typed
 * Returns       :    1 -- always
 */
public int
buy(string arg)
{
    mixed        *hdata;
    object       *herb_ob,
                 tp = TP,
                 thiso = TO;
    int          amount,
                 unknown,
                 i,
                 max_n;
    string       *words;

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
    if (!strlen(arg))
    {
        tell_room(ENV(thiso),
		  QCTNAME(tp) + " murmurs something to " + QTNAME(thiso) +
		  ".\n", tp);
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
	/* allows "buy herbs to behave like "list" for
	 * backwards compability
	 */
	list("herbs");
	return 1;
    }
    /*
    if (arg == "jar")
    {
	return 1;
    }
    if (arg == "pouch")
    {
        return 1;
    }
    if (arg == "glove" ||
        arg == "gloves")
    {
        return 1;
    }
    */
    words = explode(arg, " ");
    if (sizeof(words))
    {
	sscanf(words[0], "%d", amount);
	if (amount > 0)
        {
	    arg = implode(words[1..], " ");
        }
        else
	{
            amount = 1;
	}
    }
    tell_room(ENV(thiso),
	      QCTNAME(tp) + " asks " + QTNAME(thiso) + " for " +
	      ( amount == 1 ? LANG_ADDART(arg) : "some " + arg ) +
	      ".\n", tp);
    command("emote starts looking through his pouches.");
    if (!pointerp(hdata = All_herbs[arg]) ||
	!hdata[H_COUNT])
    {
	command("say Hmm.... I seem to be out of " + arg + ", " +
		gender_title(tp) + ".");
	command("sigh");
	return 1;
    }

    max_n = MIN(MAX_XFER, amount);
    if (max_n < amount)
    {
        command("say I will not sell you more than " + MAX_XFER_WORD +
		" herbs at thew time.");
	command("ponder no need to rush it....");
    }

    if (hdata[H_COUNT] < max_n)
    {
        command("sigh");
	command("say If I only had " + LANG_WNUM(max_n) + " of " + arg + ".");
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
			 ctime(time()) + " Utmir failed to clone " +
			 arg + " from " + hdata[H_FILE] + "\n");
		command("hmm");
		command("say It seems like " +
			(max_n == 1 ? "it" : "they") +
			" have decayed.");
		command("frown");
		hdata[H_COUNT] = 0;
		return 1;
            }
        }

	herb_ob->move(thiso, 1);
	herb_ob->force_dry();
	command("emote picks " + (max_n == 1 ? "a herb" : "some herbs") +
		"from a little pouch.");
	command("say I hope the " + arg + " will be useful to you, " +
		gender_title(tp) + ".");
	for (i = 0; i < max_n; ++i)
        {
 	    command("give " + OB_NAME(herb_ob[i]) + " to " +
		    tp->query_real_name());
	    if (ENV(herb_ob[i]) == thiso)
	    {
		command("frown");
		command("say I'll just drop the " +
			(i == (max_n - 1) ? "herb" : "herbs") + "here.");
		command("drop " + OB_NAME(herb_ob[i]));
		while (++i < max_n)
		{
		    command("drop " + OB_NAME(herb_ob[i]));
                }
            }
        }
	hdata[H_COUNT] -= max_n;
	if (hdata[H_COUNT] < 0)
	{
	    hdata[H_COUNT] = 0;
        }
	if (!hdata[H_COUNT])
        {
	    command("say Thats my last " + arg + ".");
	    command("hmm");
	    command("say I think I need to search for some more " + arg + ".");
        }
	save_object(HERBAL_SAVE);
    }
    else
    {
        command("say You don't have enough money " + gender_title(tp) + ".");
        command("frown");
    }
    return 1;
}

/*
 * Function name:    do_sell_all
 * Description  :    handle "sell all herbs"
 * Arguments    :    object player -- the seller
 */
public void
do_sell_all(object player)
{
    object     *herb_obs,
               tp = TP,
               thiso = TO;
    mixed      hdata;
    string     hname,
               sherb;
    int        total_price,
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
		  QCTNAME(tp) + " murmurs something to " + QTNAME(thiso) + ".\n",
		  tp);
	command("say But you have no herbs to sell!");
	command("shrug");
	return;
    }
    tell_room(ENV(thiso),
	      QCTNAME(tp) + " offers some herbs to " + QTNAME(thiso) + ".\n", tp);
    max_n = MIN(MAX_XFER, no_h);
    while (n < max_n)
    {
        hname = herb_obs[n]->query_herb_name();
	if (herb_obs[n]->do_id_check(thiso))
        {
	    price = herb_obs[n]->query_herb_value() /2;
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
	command("say I'll pay you " + price + " copper coins for each " +
		hname + ".");
	total_price += price;
	
	add_herb(herb_obs[n]);
	n++;
    }
    if (max_n < no_h)
    {
        command("say I'll just take the first " + MAX_XFER_WORD +
		" off your hands.");
    }
    do_pay(player, total_price);
}

/*
 * Function name:    sell
 * Description  :    handle attempts to sell herbs
 * Arguments    :    string arg -- whatever the player wants to sell
 * Returns      :    1 -- allways
 */
public int
sell(string arg)
{
    int        price,
      //               asked_for,
               hn;
    object     herb_ob,
               tp = TP,
               thiso = TO,
               *obj;
    mixed      *hdata,
               nosell;
    string     hname;

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
    if (!strlen(arg))
    {
        tell_room(ENV(thiso),
		  QCTNAME(tp) + " murmurs something to " + QTNAME(thiso) + ".\n",
		  tp);
	command("say What herb do you want to sell?");
	command("chuckle");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "all")
    {
        tell_room(ENV(thiso),
		  QCTNAME(tp) + " murmurs something to " + QTNAME(thiso) + ".\n",
		  tp);
	command("say Sorry, but I deal only in herbs.");
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
		  QCTNAME(tp) + " murmurs something to " + QTNAME(thiso) + "./n",
		  tp);
	command("say What herb do you want to sell?");
	command("smile friendly");
	return 1;
    }
    if (!sizeof(obj = filter(obj, herb_filter)) ||
	(!objectp(herb_ob = obj[0])))
    {
	tell_room(ENV(thiso),
		  QCTNAME(tp) + "murmurs something to " + QTNAME(thiso) + ".\n", tp);
	command("say You have no herb called " + arg + ", " +
		gender_title(tp) + ".");
	return 1;
    }

    tell_room(ENV(thiso),
	      QCTNAME(tp) + " offers a herb to " + QTNAME(thiso) + ".\n", tp);
    
    if (nosell = herb_ob->query_prop(OBJ_M_NO_SELL))
    {
	if (stringp(nosell))
	{
	    write(nosell);
        }
	command("say I cannot accept that herb, " + gender_title(tp) + ".");
	return 1;
    }

    hname = herb_ob->query_herb_name();

    if (herb_ob->do_id_check(thiso))
    {
	switch(random(4))
	{
	case 0:
	  command("say I'm amazed, it is " + LANG_ADDART(hname)+"!");
	  break;
	case 1:
	  command("say Oh dear, if it isn't a genuine " + hname + "!");
	  break;
	case 2:
	  command("say Hmm ... oh yes! " + CAP(LANG_ADDART(hname)) + "!");
	  break;
	case 3:
	  command("say Most interesting! " + CAP(LANG_ADDART(hname)) + "!");
	  break;
	default:
	  command("say Yes, thats " + LANG_ADDART(hname) + ".");
	  break;
	}
    }

    price = herb_ob->query_herb_value() / 2;

    do_pay(tp, price);
    add_herb(herb_ob);

    return 1;
}

/*
 * Function name:    do_pay
 * description  :    pay the player
 * Arguments    :    object player -- person to pay
 *                   int price -- price in copper
 */
public void
do_pay(object player, int price)
{
    string       myname;
    object       gc,
                 sc,
                 cc;
    int          g,
                 s,
                 c;

    command("emote digs his hand deep into a pocket and retrives some " +
	    "coins from it.");
    command("emote counts some coins and puts the rest back into the pocket.");
    g = (price / 144);
    s = ((price -(g*144)) / 12);
    c = (price - (g*144) - (s*12));
    gc = MONEY_MAKE_GC(g);
    sc = MONEY_MAKE_SC(s);
    cc = MONEY_MAKE_CC(c);
    myname = (player->query_met(TO) ?
	      query_name() : "The " + query_nonmet_name());

    if (g) write(myname + " gives you " + g + " gold coins.\n");
    if (g) gc->move(TP, 1);
    
    if (s) write(myname + " gives you " + s + " silver coins.\n");
    if (s) sc->move(TP, 1);

    if (c) write(myname + " gives you " + c + " copper coins.\n");
    if (c) cc->move(TP, 1);

    command("smile");
}

/*
 * Function name:    add_herb
 * Description  :    add a herb to inventory
 * Arguments    :    object herb_ob -- the herb ;)
 */
public void
add_herb(object herb_ob)
{
    string      herb_file,
                hname;
    int         i, n;
    mixed       *hdata;

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
	    log_file(LOG_BUG,
		     ctime(time())+" Conflicting files " +
		     herb_file + " and " + hdata[H_FILE] + "for '" + hname + "'.\n");
        }
	herb_ob->remove_object();
	return;
    }
    command("say Aaah, " + LANG_ADDART(hname) + ". I was looking for one of " +
	    "those.");
    hdata = allocate(3);
    hdata[H_FILE] = herb_file;
    hdata[H_COUNT] = 1;
    hdata[H_VALUE] = herb_ob->query_herb_value();
    All_herbs[hname] = hdata;
    herb_ob->remove_object();
    save_object(HERBAL_SAVE);
}

/*
 * Function name:    give_back_immediately()
 * Description  :    return herb when busy with another one
 * Arguments    :    object herb -- the one to rreturn
 *                   object from -- who
 */
public void
give_back_immediatly(object herb, object from)
{
    if (!objectp(from) ||
	ENV(from) != ENV())
    {
        add_herb(herb);
	return;
    }
    if (!CAN_SEE(TO, from))
    {
        command("say Who gave me this?");
	cant_see();
	add_herb(herb);
	return;
    }
    command("say Do not hurry so much, and let me finish with this " +
	    "other herb, " + gender_title(from) + ".");
    command("give " + OB_NAME(herb) + " to " + from->query_real_name());
    if (ENV(herb) == TO)
    {
        command("drop " + OB_NAME(herb));
    }
}

/*
 * Function name:    enter_inv
 * Description  :    mask parent to catch herbs.
 * Arguments    :    object ob -- the entering object
 *                   object from -- source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (Given_herb || Test_id_alarm_id)
    {
        set_alarm(1.0, 0.0, &give_back_immediatly(ob, from));
	return;
    }
    if (!living(from))
    {
        if (function_exists("create_herb", ob))
	    add_herb(ob);
	return;
    }
    if (function_exists("create_herb", ob))
    {
        Test_id_alarm_id = set_alarm(5.0, 0.0, &test_identify(ob, from));
	return;
    }
    else
    {
        set_alarm(1.0, 0.0, &not_herb(ob, from));
        return;
    }
    return;
}

/*
 * Function name:    test_identify()
 * Description  :    indentify an herb
 * Arguments    :    object herb -- herb to identify
 *                   object from -- who
 */
public void
test_identify(object herb, object from)
{
    string       id_str,
                 find_str;

    Test_id_alarm_id = 0;

    if (!objectp(from) ||
	ENV(from) != ENV())
    {
        add_herb(herb);
	return;
    }
    if (!CAN_SEE(TO, from))
    {
        command("say Who gave me this?");
	cant_see();
	command("say I'll keep this for my store then.");
	add_herb(herb);
	return;
    }
    Given_herb = herb;
    command("emote looks closely at the " + Given_herb->query_name() + ".\n");

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
	id_str = "Ahh ... a nice one. Some peaople often mistake " +
	  "this for another.";
	break;
    case 3:
        command("frown");
	id_str = "I've seen this one a lot. Easily mistaken though.";
	break;
    case 4:
        command("smile");
	id_str = "Ah - I can't blame you for not recognizing this one.";
	break;
    case 5:
        command("smile");
	id_str = "Exiting! This one can be real hard to recognize.";
	break;
    case 6:
        command("think");
	id_str = "My dear friend - you need to be quite skilled to " +
	  "identify this one.";
	break;
    case 7:
        command("eyebrow");
	id_str = "Oh! Can it realy be ... ? Ah ... yes it is.";
	break;
    case 8:
        command("emote looks impressed.");
	id_str = "Eru must be pulling my leg! This one is very " +
	  "difficult to identify!";
	break;
    case 9:
        command("gasp");
	id_str = "Oh dear, oh dear. This is a tough one even for me.";
	break;
    case 10:
        command("confused");
	id_str = "Impossible! Absolutly impossible! " +
	  "It just can't be ... ?!";
	break;
    default:
        log_file(LOG_BUG,
		 ctime(time()) + " bad id_diff of " +
		 Given_herb->query_id_diff() + " for " +
		 Given_herb->query_herb_name() + " (" +
		 file_name(Given_herb) + ")\n");
	command("confused");
	id_str = "Impossible! Absolutly impossible! " +
	  "It just can't be ... ?!";
	break;
    }
    command("say " + id_str);
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
	find_str = "Interesting. Not everybody knows where to find " +
	  "this one.";
	break;
    case 4:
        command("smile");
	find_str = "Good work! This one is not easy to locate.";
	break;
    case 5:
        command("smile");
	find_str = "Ah! I guess you spent some time looking for this one!";
	break;
    case 6:
        command("think");
	find_str = "Hmmm. I wonder where you found this one?";
	break;
    case 7:
        command("whistle");
	find_str = "You must have been quite lucky to find this herb!";
	break;
    case 8:
        command("gasp");
	find_str = "I am absolutely astonished! This is one is " +
	  "extremely rare!";
	break;
    case 9:
        command("emote looks totally flabbergasted.");
	find_str = "Congratulations! I have seen this herb only " +
	  "a couple of times.";
	break;
    case 10:
        command("confused");
	find_str = "I cannot believe it! I can't remember seeing this " +
	  "herb. I have only read about this in old dusty books!";
	break;
    default:
        log_file(LOG_BUG,
		 ctime(time()) + " bad find_diff of " +
		 Given_herb->query_find_diff() + " for " +
		 Given_herb->query_herb_name() + " (" +
		 file_name(Given_herb) + ")\n");
	command("confused");
	find_str = "I cannot believe it! I can't remember seeing this " +
	  "herb. I have only read about this in old dusty books!";
	break;
    }
    command("say " + find_str);
    if (Given_herb->do_id_check(TO))
    {
        command("say " + Given_herb->query_id_long());
    }
    else
    {
        command("say I do not know what effect this " +
		Given_herb->query_name() + " might have.");
    }
    command("give " + OB_NAME(Given_herb) + " to " + from->query_real_name());
    command("say I hope my information has been useful, " +
	    gender_title(from) + ".");
    command("bow");
    Given_herb = 0;
}

/*
 * Function name:    show_herb()
 * Description  :    respond to a question about a specific herb
 * Arguments    :    string hname -- the herb name
 *                   mixed *hdata -- the data for this herb
 * Returns      :    1 on success, 0 on failure
 */
public int
show_herb(string hname, mixed *hdata)
{
    object      herb;

    if (!(herb = clone_object(hdata[H_FILE])))
    {
        return 0;
    }
    command("say Ahhh, " + hname + ".");
    command("think " + hname);
    if (herb->do_id_check(TO))
    {
        command("say To the uninitiated, " + hname + " appears as " +
		LANG_ADDART(herb->short()) + ".");
	command("say However, the accomplished herbalist sees:");
	tell_room(ENV(), herb->query_id_long());
    }
    else
    {
        command("say " + CAP(hname) + " appears as " +
		LANG_ADDART(herb->short()) + ".");
        command("say I really cannot tell you more.");
        command("shrug ruefully");
    }
    command("emote starts looking through his pouches.");
    if (hdata[H_COUNT] > 0)
    {
        command("say I have " + LANG_WNUM(hdata[H_COUNT]) + " in stock.");
    }
    else
    {
        command("say I am currently out of " + hname + ".");
    }
    herb->remove_object();
    return 1;
}

/*
 * Function name:    set_up_skills()
 * Description  :    set Utmir up to train skills
 */
public void
set_up_skills()
{
    string herbm = "recognize and handle herbs and plants";
    string locm = "find locations and directions";
    string trackm = "find hidden paths";
    string awarm = "detect hidden dangers";

    sk_add_train(SS_HERBALISM, ({ herbm, herbm }), 0, 0, 30);
    sk_add_train(SS_LOC_SENSE, ({ locm, locm }), 0, 0, 30);
    sk_add_train(SS_TRACKING, ({ trackm, trackm }), 0, 0, 30);
    sk_add_train(SS_AWARENESS, ({ awarm, awarm }), 0, 0, 30);
}


