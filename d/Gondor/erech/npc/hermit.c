/*
 * hermit.c
 * By Skippern
 *
 * With Sterns servent.c and merged_soldier.c as examples and good
 * help from Rohim and Mrpr.
 *
 * In addition the following examples have been used:
 * /d/Gondor/common/guild/npc/herbalist.c by Elessar
 * /d/Gondor/pelargir/npc/carastur.c by Gnadnar/Elessar
 */
#pragma save_binary
#pragma strict_types

inherit "/std/act/action";    /* make it do things */
inherit "/std/act/chat";      /* make it talk */
inherit "/std/act/domove";    /* make it walk */
inherit "/lib/trade";         /* make it handle trading */
inherit "/lib/skill_raise";   /* make it raise skills */
inherit "/d/Shire/lib/training";

inherit "/d/Gondor/common/lib/binbit"; /* the binbit code */

#include "../erech.h"     /* for Erech definitions */

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#define HERM_ADJ1  ({ "sturdy", "humble", "noble", "tanned" })
#define HERM_ADJ2  ({ "black-haired", "dark-haired", \
                        "brown-haired", })

#define H_GENDER        G_MALE
#define H_ALIGN         200 + random(500)
#define MY_HEIGHT       150 + random(31)
#define MY_WEIGHT       1200 + random(200)
#define MY_VOLUME       MY_WEIGHT - 50 + random(100)

#define H_SS_MAX        60 + random(40)
#define H_SS_MID        40 + random(40)
#define H_SS_MED        30 + random(30)
#define H_SS_MIN        10 + random(10)

#define H_STR           50 + random(25)
#define H_DEX           70 + random(50)
#define H_CON           20 + random(90)
#define H_WIS           30 + random(95)
#define H_INT           30 + random(90)
#define H_DIS           75 + random(25)

#define TASK_ITEM       "Erech_Task_Item"

#define TASK            ({ "I want you to find a small cave that is " +\
                           "located on this field. It is a small cave " +\
                           "where bears dwells occational winters.",\
                           "Not far from here is a covenent rock. " +\
                           "This rock have a special place in our history.",\
                           "There is a farm not far from here. You should " +\
                           "check if all the animals there are fine." })

#define H_GOOD          ({ "thank", "compliment", "comfort", "congratulate", \
                           "excuse", "pat", "congrat" })
#define H_THANK         ({ "shake", "bow", "agree", "applaud", "apologize" })
#define H_NEUTRAL       ({ "kiss", "smile", "hug", "grin", "tickle", "poke", \
                           "admire", "beg", "blush", "bat", "blow", "bounce" })
#define H_BAD           ({ "curse", "swear", "french", "scowl", "puke", \
                           "avert", "back" })
#define H_WORST         ({ "knee", "slap", "kick", "spank", "fuck" })
#define H_POINT         ({ "point", "peer" })

#define H_GOOD_R        ({ "smile friendly", "smile thankfully", "giggle", \
                           "grin merrily", "blush" })
#define H_THANK_R       ({ "smile thank", "smile friendly", "blush", "smile", \
                           "giggle" })
#define H_NEUTRAL_R     ({ "nod", "smile", "giggle", "grin", "eyebrow" })
#define H_BAD_R         ({ "smile bitterly", "scowl", "jump", "swallow", \
                           "nod" })
#define H_WORST_R       ({ "sob", "cry angrily", "panic", "worry", "ouch" })
#define H_POINT_R       ({ })

#define H_GOOD_T        ({ "We certainly are in a good mood today", \
                           "And to you aswell", \
                           "I am happy" })
#define H_THANK_T       ({ "Thank you for haveing confidence in me", \
                           "I am glad for your support", \
                           "This is more than I desireve" })
#define H_NEUTRAL_T     ({ "Good mood today I see", \
                           "Thank you", \
                           "Having fun today I see" })
#define H_BAD_T         ({ "How rude you are", \
                           "You should be ashamed", \
                           "You better be sorry for that" })
#define H_WORST_T       ({ "Damn you doing this", \
                           "How dare you", \
                           "You will regrat this one day" })
#define H_POINT_T       ({ "What do you want with me", \
                           "What are your interests with me", \
                           "Anything you want" })

/* Variables */
mapping              All_herbs = ([]);
string               *Local_herbs = ({}),
                     *Important_herbs = ({});
int                  ran;
static string        Coin_pay_text,
                     Coin_get_text,
                     *Herb_buyer,
                     Log_str;
static int           Ask_help_alarm_id,
                     Test_id_alarm_id,
                     *Money_arr;
static object        Given_herb,
                     obj;

/* Prototypes */
public void          create_dunadan();
public string        gender_title(object living);
public void          handle_emotes(string emote, object actor);
public void          announce_selling();
public void          set_up_skills();
public string        ask_herbs();
public string        ask_lore();
public string        ask_history();
public string        task();
public void          restore_herbs();
public int           list(string arg);
public int           buy(string arg);
public int           sell(string arg);
public void          room_too_dark();
public void          cant_see();
public void          dont_know(object tp);
public int           can_afford(int price);
public void          do_sell_all(object player);
public void          do_pay(object player, int price);
public void          add_herb(object herb_ob);
string               tell_rock(int part);
string               tell_oath(int part);
string               tell_gwaedhel(int part);
public void          introduce_me(object pl, string name);
string               do_more();
public void          test_identify(object herb, object from);
public void          give_back_immediatly(object herb, object from);
void                 reward_task(object tp, int task);
void                 check_task(object item, object tp);
int                  accept_task(string str);

/*
 * Function name:    create_monster() or create_dunadan()
 * Definition   :    Creates the monster
 *
 * Remember     :    The `int' should be the first commands executed within
 *                   this function, since executing this command later is
 *                   illigal according to normal C codes and also for LPC.
 */
public void
create_dunadan()
{
    FIX_EUID;
    set_living_name("utmir");
    set_name("utmir");
    add_name( ({ "herbalist", "hermit", "questmaster" }) );
    set_race_name("human");
    set_title("lone herbalist of Erech");
    set_dunedain_house("Hurin");
    set_long("He looks like an old and wise person, aged with " +
	     "experience from long jurneys. He have a belt with " +
	     "several pouches on him, containing herbs and coins. " +
	     "\n");
  
    default_config_npc(70);

    set_adj(one_of_list(HERM_ADJ1));
    add_adj(one_of_list(HERM_ADJ2));
  
    set_gender(H_GENDER);
    set_alignment(H_ALIGN);
  
    add_prop(CONT_I_HEIGHT, MY_HEIGHT);
    add_prop(CONT_I_WEIGHT, MY_WEIGHT);
    add_prop(CONT_I_VOLUME, MY_VOLUME);
    add_prop(LIVE_I_MAX_DRINK, 100);
    add_prop(LIVE_I_MAX_EAT, 100);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(OBJ_S_WIZINFO, "wizinfo");

    set_act_time(18);
    add_act("think the tales of the Oathbreakers.");
    add_act("think the tales of the Gwaedhil.");
    add_act("think the tales of the Covenent rock.");
    add_act("smile");
    add_act("hum");
    add_act("emote hums an old gondorian folk tune.");
    add_act("emote looks into his pouches and counts their contents.");
    add_act("@@announce_selling");
    add_act("@@herb_searcher");
    add_act("@@herb_searcher");
    add_act("@@herb_searcher");
    add_act("search here for herbs");
    add_act("search here for herbs");
    set_cact_time(2);
    add_cact("knee enemy");
    add_cact("tackle enemy");
    add_cact("slap enemy");
    add_cact("kick enemy");
    add_cact("bcry");
    add_cact("takes up a herb from a small pouch and starts to chew on it.");
    set_chat_time(14);
    add_chat("I know much about the herbs from this area.");
    add_chat("I can tell you many stories.");
    add_chat("Only foolish herbalists stay all day indoors in their stores.");
    add_chat("I know the tales of the covenent rock.");
    add_chat("I know the tales of the Oathbreakers.");
    add_chat("I know the tales of the Gwaedhil.");
    set_cchat_time(3);
    add_cchat("You have violated me, and therefor you must die!");

    set_random_move(12, 1);
    set_restrain_path(E_FIELD);

    set_skill(SS_ACROBAT, H_SS_MAX);
    set_skill(SS_HERBALISM, H_SS_MAX);
    set_skill(SS_AWARENESS, H_SS_MAX);
    set_skill(SS_DEFENCE, H_SS_MAX);
    set_skill(SS_PARRY, H_SS_MAX);
    set_skill(SS_HUNTING, H_SS_MED);
    set_skill(SS_SWIM, H_SS_MED);
    set_skill(SS_ANI_HANDL, H_SS_MID);
    create_skill_raise();
    set_up_skills();
  
    set_base_stat(SS_STR, H_STR); 
    set_base_stat(SS_DEX, H_DEX); 
    set_base_stat(SS_CON, H_CON);
    set_base_stat(SS_WIS, H_WIS);
    set_base_stat(SS_INT, H_INT);
    set_base_stat(SS_DIS, H_DIS); 
  
    set_default_answer("say default_answer");
    add_ask("task", "@@task");
    add_ask( ({ "reward", "for reward", "about reward" }), "@@reward");
    add_ask( ({ "herbs", "herb" }), "@@ask_herbs");
    add_ask( ({ "herblore", "lore" }), "@@ask_lore");
    add_ask( ({ "story", "history" }), "@@ask_history");
    add_ask( ({ "more", "tell me more", "tell us more" }), "@@do_more");
    add_ask( ({ "rock", "rock of erech", "covenent rock", "black rock" }), 
	     "@@ask_rock");
    add_ask( ({ "oathbreakers", "oathbreaker" }), "@@ask_oath");
    add_ask( ({ "gwaedhil", "gwaedhel spear", "spear", "gwaedhel sword", 
		  "sword" }), "@@ask_gwaedhel");

    config_default_trade();
    set_money_give_out( ({ 1000,  500,    10,    10 }) );
    set_money_give_reduce( ({ 0,    0,     0,     0 }) );

    obj = clone_object(E_OBJ + "h_cloak");
    obj->move(this_object());
    obj = clone_object("/d/Gondor/common/arm/herb_gloves");
    obj->move(this_object());
    command("wear all");
    restore_herbs();
}

string
gender_title(object living)
{
    int gender;
    gender = living->query_gender();
    switch (gender)
    {
        case G_MALE     : return ("Sir");
        case G_FEMALE   : return ("Miss");
        default         : return ("Eh.... Thing");
    }
}

public void
add_introduced(string name)
{
    object    pl;
    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

public void
introduce_me(object pl, string name)
{

    if (IS_DUNADAN(pl))
    {
	command("wellmet " + name);
    }
    else if (pl->query_race() == "elf") 
    {
	command("elfhail " + name);
    }
    else
    {
	command("dsalute " + name);
    }

    command("say Greetings " + gender_title(find_player(name)) + " " +
	capitalize(name) + ".");
    command("introduce me to " + name);
    command("say to " + name + " How may I interest you " +
	gender_title(find_player(name)) + "?");
    return;
}

void
emote_hook(string emote, object actor, string adverb, int target)
{
    if (target)
    {
        set_alarm(1.0, 0.0, &handle_emotes(emote,actor));
    }
}

void
handle_emotes(string emote, object actor)
{
    if (member_array(emote, H_GOOD) != -1)
    {
        command(one_of_list(H_GOOD_R));
	command("say " + one_of_list(H_GOOD_T) + ", " +
	    gender_title(actor) + "." );
	return;
    }

    if (member_array(emote, H_THANK) != -1)
    {
	command(one_of_list(H_THANK_R));
	command("say " + one_of_list(H_THANK_T) + ".");
    }

    if (member_array(emote, H_NEUTRAL) != -1)
    {
        command(one_of_list(H_NEUTRAL_R));
	command("say " + one_of_list(H_NEUTRAL_T) + ".");
	return;
    }

    if (member_array(emote, H_BAD) != -1)
    {
        command(one_of_list(H_BAD_R));
	command("say " + one_of_list(H_BAD_T) + ".");
	return;
    }

    if (member_array(emote, H_WORST) != -1)
    {
        command(one_of_list(H_WORST_R));
	command("say " + one_of_list(H_WORST_T) + "!");
	return;
    }

    if (member_array(emote, H_POINT) != -1)
    {
	command("say " + one_of_list(H_POINT_T) + ", " +
	    gender_title(actor) + "?");
	return;
    }
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
    if (!sizeof(Important_herbs))
    {
	Important_herbs = ({ "basil", "dill", "mint" , "oregano", 
			       "red potato" });
    }
    if (!sizeof(Local_herbs))
    {
	Local_herbs = ({ "alfirin", "angurth", "athelas", "basil", 
			   "black potato", "caraway", "catnip", "chervil", 
			   "curugwath", "dill", "fennel", "green onion", 
			   "handasse", "hemlock", "holly berry", "ithilgil", 
			   "lissuin", "lothore", "marjoram", "mint", 
			   "oregano", "red potato", "redweed", "rosemary", 
			   "seregon", "simbelmyne", "tarragon", "thyme", 
			   "ungolstel" });
    }
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
    add_action(do_more, "more");
    add_action(accept_task, "accept");
}

public void
announce_selling()
{
    if (m_sizeof(All_herbs))
    {
        command("say I have some herbs for sale, would you like some?");
    }
    else
    {
        command("say hmm, I am out of stock, better look for some herbs " +
	    "then.");
	command("search here for herbs");
    }
}

/*
 * Function name:    herb_searcher()
 * Description  :    Finds out if it is need for searching for a specific
 *                   herb, and starts the search.
 */
void
herb_searcher()
{
    string      herb;
    string      herblist;
    string      *herbarr;
    string      *hnames;
    string      tempstr;
    string      *temp = ({});
    string      *tmp = ({});
    mixed       *hdata;
    int         i, n, sz;

    // For debugging
    herb = "herbs";

    if (STOCK_ME_UP == 1)
    {
	command("search here for herbs"); 
	return; 
    }

    // Do a check to see what herbs need to be searched for.
    hnames = m_indices(All_herbs);
    n = sizeof(hnames);
    hnames = sort_array(hnames);
    herblist = "";
    for ( i = 0; i < n; ++i )
    {
	if (pointerp(hdata = All_herbs[hnames[i]]) &&
	    hdata[H_COUNT] < MAX_INV)
	{
	    herblist += " "+hnames[i];
	}
    }
    herbarr = explode(herblist, " ");
    
    // Check if herbs needed to be searched for are important.
    for (i = 0, sz = sizeof(herbarr) ; i < sz ; i++)
    {
	if (member_array(herbarr[i], Important_herbs) >= 0)
	{
	    temp += ({herbarr[i]});
	}
    }

    // Check if herbs needed to be searched for are local.
    for (i = 0, sz = sizeof(herbarr) ; i < sz ; i++)
    {
        if (member_array(herbarr[i], Local_herbs) >= 0)
        {
            tmp += ({herbarr[i]});
	}
    }
    // Evaluate and find the right search.
    if (sizeof(temp))
    {
	herb = one_of_list(temp);
    }
    else if (sizeof(tmp))
    {
	herb = one_of_list(tmp);
    }
    else
    {
	return;
    }
    // Start the search.

    command("search here for " + herb);
    return;
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

    tell_room(ENV(thiso),
	      QCTNAME(tp)+" asks "+QCTNAME(thiso)+" a question.\n", tp);

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
	command("drop " + OB_NAME(herb));
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
    if (ob->id(TASK_ITEM))
    {
        set_alarm(1.0, 0.0, &check_task(ob, from));
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
 * Function name:    ask_herbs()
 * Description  :    respond to questions
 * Returns      :    "" (answer is writen before return)
 */
public string
ask_herbs()
{
    command("say So you are interested in herbs.");
    command("smile");
    command("say I know many of the herbs, and all common.");
    return "";
}

/*
 * Function name:    ask_lore()
 * Description  :    see ask_herbs
 */
public string
ask_lore()
{
    command("say Ah, you are interested in herb lore.");
    command("smile dream");
    command("say I can still remember when I was young and found my " +
        "first herb.");
    command("stare");
    command("say If you have time, I can try to teach you something " +
	"about herbs.");
    return "";
}

/*
 * Function name:    ask_history()
 * Description  :    see ask_herbs
 */
public string
ask_history()
{
    command("say Ah, you are interested in history, thats good.");
    command("say What story do you wan't to hear?");
    command("say I can tell you about the Oathbreakers, the covonent " +
	"rock, or maybe the Gwaedhel.");
    command("smile friendly");
    return "";
}

/*
 * Function name:    task()
 * Description  :    Gives tasks.
 */
public string
task()
{
    int      no;
    object   tp = this_player();
    string   str;

    if (objectp(present(TASK_ITEM, tp)))
    {
	command("say to " + tp->query_real_name() + " Do not hurry my " +
		"friend and complete one task at a time.");
	return "";
    }

    no = query_bin_bits(ERECH_TASK_GROUP, ERECH_FIRST_BIT, ERECH_NO_BITS, tp);

    if (no >= sizeof(TASK))
    {
	if (!tp->test_bit("Gondor", ERECH_FARM_GROUP, ERECH_FARM_BIT))
	{
	    command("say Please tell Skippern to complete this quest.");
	    return "";
	}
	command("say Sorry " + gender_title(tp) + ", but I don't have " +
		"any more tasks for you.");
	command("say I am sure you can find work elsewhere in Gondor, " +
		"or you can start your own business.");
	return "";
    }


    command("say To ensure me you are the right person for the " +
	    "jobs I have, you have to do this.");
    tell_object(tp, BSN(TASK[no]));
    command("say If you have understood the task, pleace 'accept task'.");
    tp->add_prop(ERECH_I_TASK, 1);
    command("emote waits hopefully.");
    return "";
}

int
accept_task(string str)
{
    int      no;
    object   item, 
             tp = this_player();

    if (str != "task")
    {
	return 0;
    }
    if (!tp->query_prop(ERECH_I_TASK))
    {
	command("say You have to ask first.");
	command("ponder don't even know what they accept....");
	return 1;
    }

    say(QCTNAME(tp) + " asks the lone hermit something.\n", tp);
    no = query_bin_bits(ERECH_TASK_GROUP, ERECH_FIRST_BIT, ERECH_NO_BITS, tp);

    if (no >= sizeof(TASK))
    {
	command("say No more tasks, " + gender_title(tp) + ".");
	return 1;
    }

    command("say Great! Please take this leaf as a token for what you " +
	    "are helping me with, and come back to me as soon as you " +
	    "have fulfilled your task.");
    item = clone_object(E_OBJ + "magic_leaf");
    item->set_task_no(no);
    item->set_task(TASK[no]);
    item->set_player_name(tp->query_real_name());
    tp->remove_prop(ERECH_I_TASK);
    if ((item->move(tp)))
    {
	command("say Oh, you are burdened. Well, I'll leave it here then.");
	item->move(ENV(TO));
    }
    return 1;
}

/*
 * Function name:    reward()
 * Description  :    checkes if the players have completed their tasks, 
 *                   and gives them the right reward for it.
 * Return       :    "" -- allways.
 *
 */
public string
reward()
{
  command("say If you want a reward, you must give me your leaf.");
  return "";
}


/*
 * Function name:    ask_rock()
 * Description  :    see ask_herbs()
 */
public string
ask_rock()
{
    TP->add_prop(ERECH_S_TALE, "rock");
    TP->add_prop(ERECH_I_PART, 1);
    command("say Ahh, I can tell you much of the covenent rock.");
    command("smile friendly");
    command("say The covenent rock was brought to Gondor by the first " +
	"Numenorians when they arrived here in S.A. 884.");
    command("say It is said that the rock was clear as a crystal back then.");
    command("say In S.A. 3320 Isildur, king of Gondor made King of the " +
	"Mountains to swear alligiance to him here.");
    command("sigh");
    command("say But in S.A 3434 when Morthec broke the alligiance, and " +
	"those following him was coursed to hount this valley, and the " +
	"mountains north of here.");
    command("say It was then the rock started to change color.");
    return "";
}

/*
 * Function name:    ask_oath()
 * Description  :    see ask_herbs()
 */
public string
ask_oath()
{
    TP->add_prop(ERECH_S_TALE, "oath");
    TP->add_prop(ERECH_I_PART, 1);
    command("say Ahh, so you want to hear about the Oathbreakers.");
    command("smile know");
    command("say Those who followed Morthec was subject for the course " +
	"set by Isildur back in S.A. 3434, and was ever after called " +
	"Oathbreakers.");
    command("say They was doomed to roam the world as undead ghosts until " +
	"oath can be fulfilled.");
    command("shudder");
    return "";
}

/*
 * Function name:    ask_gwaedhel()
 * Description  :    see ask_herbs
 */
public string
ask_gwaedhel()
{
    TP->add_prop(ERECH_S_TALE, "gwaedhel");
    TP->add_prop(ERECH_I_PART, 1);
    command("say Ahh, so you are interested in the Gwaedhil?");
    command("say Gwaedhil means Oath-sisters in Sindarin, and " +
	    "is the plural form of Gwaedhel.");
    command("say The Gwaedhil contains of a sword and a spear.");
    command("smile .");
    return "";
}

/*
 * Function name:    do_more()
 * Description  :    controles the more function in stories.
 */
string
do_more()
{
    string tale;
    int    part;

    tale = TP->query_prop(ERECH_S_TALE);
    part = TP->query_prop(ERECH_I_PART);

    switch(tale)
      {
      case "rock":
	tell_rock(part);
	break;
      case "oath":
	tell_oath(part);
	break;
      case "gwaedhel":
	tell_gwaedhel(part);
	break;
      default:
	command("say I am not telling you any stories.");
	break;
      }
    return "";
}

/*
 * Function name:    tell_rock()
 * Description  :    telling the rest of the stories.
 * Arguments    :    int part -- what part of the story have we come to
 */
string
tell_rock(int part)
{
  switch(part)
    {
    case 1:
      TP->add_prop(ERECH_I_PART, 2);
      command("say The name Erech is dunael, meaning place of Terror, " +
	  "and this have been a place of terror since the oath was broaken.");
      command("say While the force of the undead grew, and the remaining " +
	  "of the Oathbreakers vanished slowly, the rock became darker and " +
	  "darker.");
      command("sigh");
      break;
    case 2:
      TP->add_prop(ERECH_I_PART, 3);
      command("say It is said that it is possible to climb up on the " +
	      "top of the rock, and that you can hear even the faintest " +
	      "whispering while you stand there.");
      command("smile friendly");
      TP->remove_prop(ERECH_S_TALE);
      TP->remove_prop(ERECH_I_PART);
      break;
    default:
      TP->remove_prop(ERECH_S_TALE);
      TP->remove_prop(ERECH_I_PART);
      command("say something wrong happened");
      break;
    }
  return "";
}
string
tell_oath(int part)
{
  switch(part)
    {
    case 1:
      TP->add_prop(ERECH_I_PART, 2);
      command("say The Oathbreakers haunted the valley, driving people " +
	  "and animals to fear the area.");
      command("say After living alone for some hundred years, they retired " +
	  "to the mountains where they buildt homes for their undead bodies.");
      command("sigh");
      break;
    case 2:
      TP->add_prop(ERECH_I_PART, 3);
      command("say It is said that the last of the living Oathbreakers had " +
	  "a mark on their forehead, deaming them to be left alone also " +
	  "before they died.");
      command("smile friendly");
      TP->remove_prop(ERECH_S_TALE);
      TP->remove_prop(ERECH_I_PART);
      break;
    default:
      TP->remove_prop(ERECH_S_TALE);
      TP->remove_prop(ERECH_I_PART);
      command("say something wrong happened");
      break;
    }
  return "";
}
string
tell_gwaedhel(int part)
{  switch(part)
  {
  case 1:
    TP->add_prop(ERECH_I_PART, 2);
    command("say The Gwaedhil was given to Merro, the King of the " +
	"Mountains, as visible tokens of the oath that Merro swore to " +
	"Isildur upon the covenant rock of Erech.");
    command("say These arms were forged by the Elves in Tirith Aear, as a " +
	"gift to aid Elendil's sons in the securing of their newly-founded " +
	"realm.");
    command("think");
    break;
  case 2:
    TP->add_prop(ERECH_I_PART, 3);
    command("say When Merro's oath was spoken, Isildur presented the spear " +
	"Morached, Merro's son.");
    command("say But the sword he entrusted to Edhelion, who was the " +
	"Captain of the Faithful in Pelargir.");
    command("say He was appointed to wardent of the covenent rock.");
    command("emote fingers abit with his belt.");
    command("say The arms was bright back then, but it is said they have " +
	"changed in color after the oath was broken.");
    command("smile .");
    break;
  case 3:
    TP->add_prop(ERECH_I_PART, 4);
    command("say The sword, a twin-bladed broadsword, ended in the " +
	"possession of the prince of Belfalas until the time of " +
        "Lothirion whom it is said bestowed the sword to Gundor, " +
	"who was choosen to be Prince of Mornan in T.A. 831.");
    command("emote drows his breath.");
    command("say This is the last know recording of the sword.");
    break;
  case 4:
    TP->add_prop(ERECH_I_PART, 5);
    command("say The spear's recording is much easier.");
    command("smile thank");
    command("say Morthec kept the spear even after he died, and it is " +
	"said that he still wields this spear.");
    command("smile friendly");
    TP->remove_prop(ERECH_S_TALE);
    TP->remove_prop(ERECH_I_PART);
    break;
  default:
    TP->remove_prop(ERECH_S_TALE);
    TP->remove_prop(ERECH_I_PART);
    command("say something wrong happened");
    break;
  }
 return "";
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


void
check_task(object item, object tp)
{
    if (item->query_task_no() == query_bin_bits(ERECH_TASK_GROUP, 
	ERECH_FIRST_BIT, ERECH_NO_BITS, tp))
    {
      if (item->query_task_done())
      {
	  reward_task(tp, item->query_task_no()+1);
	  item->remove_object();
      }
      else
      {
	  command("say to "+tp->query_real_name()+" You need to complete " +
		  "the task first.");
	  command("sigh");
	  command("give leaf to "+tp->query_real_name());
      }
      return;
    }
}

void
reward_task(object tp, int task)
{
    int    reward;
    string sreward;

    set_bin_bits(ERECH_TASK_GROUP, ERECH_FIRST_BIT, ERECH_NO_BITS, tp, task);
    command("say to " + tp->query_real_name() + " Well done, " + 
	    gender_title(tp) + ".");

    switch(task)
    {
    case 0:
      reward = 100;
      sreward = REWARD_LITTLE;
      break;
    case 1:
      reward = 100;
      sreward = REWARD_LITTLE;
      break;
    case 2:
      reward = 100;
      sreward = REWARD_LITTLE;
      break;
    case 3:
      reward = 200;
      sreward = REWARD_SOME;
      break;
    }

    tp->add_exp_quest(reward);
    log_file("e-tasks", tp->query_cap_name()+" did Erech task " + task +
	     ", and got "+reward+" in xp. " + ctime(time()) +"\n");
    write(sreward);
    return;
}

