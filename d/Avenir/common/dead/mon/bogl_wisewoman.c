/*
 * Mostly a copy of the ranger guild herbalist.
 *
 * Lilith Oct 2021: updated path for logging errors.
 */
inherit "/std/monster";
inherit "/lib/trade";
inherit "/d/Avenir/inherit/intro";
#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "../dead.h"

#define HERBAL_SAVE           MON  + "herbalist_herbs" 
#define LOG_BUG               "misc/dead.herbs.bug"
#define MAX_ALLOW_BUY         20
#define MAX_XFER              20  /* buy/sell <= 20 at a time */
#define MAX_XFER_WORD         "twenty"
#define MAX_INV               75 
#define NUM                   sizeof(MONEY_TYPES)
/* indices into herb data */
#define H_FILE                0
#define H_COUNT               1
#define H_VALUE               2
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
#define ZOBJ "/d/Avenir/common/city/zigg/obj/"


/* Global variables. All static except All_herbs which saves in a .o */
mapping         All_herbs = ([]);
static mapping  Num_herbs = ([]);
static string   Coin_pay_text,
                Coin_get_text,
                Log_str;
static string * Herb_buyer;
static int      Test_id_alarm_id,
                gAlarm = 0,
                gShdwnAlarm = 0;
static int *    Money_arr;
static object   Given_herb;


/* Prototypes */
public void   restore_herbs();
public void   init_living();
public void   herb_save();
public int    list(string arg);
public int    buy(string arg);
public int    can_afford(int price);
public int    sell(string arg);
public void   do_sell_all(object player);
public void   do_pay(object player, int price);
public void   add_herb(object herb);
public void   enter_inv(object ob, object from);
public void   not_herb(object ob, object from);
public void   give_back_immediately(object herb, object from);
public void   test_identify(object herb, object from);
public void   show_herb(string hname, mixed *hdata);
public void   introduce(object pl);
public string def_answer();
public string ask_herbs();
public int    herb_filter(object ob);
public int    out_of_stock_filter(string name);
public int    low_on_stock_filter(string name);


void
equip_me()
{
	
    seteuid(getuid());

    clone_object(ZOBJ+"soap")->move(TO,1);
	clone_object(BOBJ+"worn/trouser")->move(TO, 1);
    clone_object(BOBJ+"worn/blouse")->move(TO, 1);
    clone_object(ZOBJ+"glotion")->move(TO, 1);

    command("wear all");	
}


string 
my_long()
{
	string str;
    string horns = one_of_list(({"dyed green","dyed pink","dyed purple","dyed blue",
			   "tied with ribbons","sanded flat","painted with stripes",
			   "inset with pyrite","inset with garnets","inset with "+
               "pearls","inset with quartz","inset with onyx"}));

    str = "She is a wrinkled bent female goblin who seems to be "
	    + query_exp_title() +" in size.\n";
    str += "She is a proud member of B.O.G.L. and the wise-woman herbalist "
	    +"of this tribe.\n" 
		+ "Her hands are stained by herbs.\n"
        + "She appears to be remarkably mild-mannered for a "
		+"goblin.\n"
		+ "She seems to take pride in her horns, "
		+"which are "+horns+".\n"
		+ "She has a smile on her face, showing old, "
		+"yellowed fangs.\n"
		+ "Her eyes are wise and rheumy.\n"
		+ "Her skin is wrinkled and brown and surprisingly clean "
		+"for a goblin.\n";
    return str;
}	


public void
create_monster()
{

    set_name("eavriz");
    add_name(({"herbalist", "wise woman", "herbwoman"}));
    add_name("wisewoman");
	set_gender(G_FEMALE);
    set_race_name("goblin");
    set_living_name("eavriz");
    set_title("the Wisewoman");
    set_adj(({ "wrinkled", "bent" }));
    set_long(my_long);
    set_stats(({ 40, 45, 60, 100, 100, 50 }));
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 43000);
    add_prop(CONT_I_HEIGHT, 84);
    add_prop(OBJ_M_NO_ATTACK, "You have little interest in beating "
	    +"up old women.\n");
    set_skill(SS_HERBALISM, 105);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE, 50);

    set_chat_time(20);
    add_chat("I am Eavriz, the wise woman of this tribe.");
    add_chat("I help with herbs.");
    add_chat("I haven't seen an herb I cound not identify in a long time.");
    add_chat("I have seen most herbs in the world by now.");

    add_ask(({"herbs", "herb"}), &ask_herbs());
    set_default_answer(&def_answer());

    config_default_trade();
    set_money_give_out(({ 10000, 500, 10, 10 }));
    set_money_give_reduce(({  0,   0,  0,  0 }));
    restore_herbs();
}
/*
 * Function name: herb_save
 * Description  : save to the .o file.
 */
public void
herb_save()
{
    save_map( ([ "all_herbs" : All_herbs ]), HERBAL_SAVE );
    return;
}

/*
 * Function name: restore_herbs
 * Description  : restore our inventory of herbs
 */
public void
restore_herbs()
{
    //Uncomment the next line, and comment out the line after that
    //to convert the herbalist_herbs.o file once we transfer. Load
    //and clone the herbalist (or update the room) and then do:
    //Call herbalist do_herb_save ... Now you can switch the comment
    //out again, or simply remove this.
    //restore_object(HERBAL_SAVE);
    All_herbs = restore_map(HERBAL_SAVE)["all_herbs"];
}

/*
 * Function name: init_living
 * Description  : Add verbs for selling, buying and listing. Also
 *                initiate skill raising.
 */
public void
init_living()
{
    ::init_living();
    add_action(list, "list");
    add_action(buy,  "buy");
    add_action(sell, "sell");
}



/*
 * Function name: list
 * Description  : handle attempts to list herbs
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 -- always
 */
public int
list(string arg)
{
    string *hnames, hlist = "";
    mixed *hdata;
    int i, n;

    tell_room(ENV(TO), QCTNAME(TP) + " asks " + QTNAME(TO) + " a question.\n", TP);

    if (!strlen(arg))
    {
        notify_fail("List what?\n");
        return 0;
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

        for ( i = 0; i < n; ++i )
        {
            if (pointerp(hdata = All_herbs[hnames[i]]) && hdata[H_COUNT] > 0)
            {
                hlist += sprintf(" %=21s\t%3d at %4d coppers each\n",
                    hnames[i], hdata[H_COUNT], hdata[H_VALUE]);
            }
        }

        command("say I have these herbs for sale:");
        TP->more(hlist);
        return 1;
    }

    command("say " + CAP(arg) + ", " + arg + " ... let me see ...");

    if ((pointerp(hdata = All_herbs[arg]) ||
       pointerp(hdata = All_herbs[LANG_SWORD(arg)])) &&
      (hdata[H_COUNT] > 0))
    {
        command("say I have " + hdata[H_COUNT] + " in stock.");
        command("say The going price is " + hdata[H_VALUE] +
            " copper coins apiece.");
    }
    else
    {
        command("sigh");
        command("say I can't find " + arg + " anywhere in my stock.");
    }

    return 1;
}

/*
 * Function name: buy
 * Description  : handle attempts to buy herbs
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 -- always
 */
public int
buy(string arg)
{
    mixed *hdata;
    object herb_ob;
    int amount, i, max_n;
    string *words;
    string tname;

    if (!strlen(arg))
    {
        command("say What herb did you want to buy?");
        return 1;
    }

    arg = lower_case(arg);

    /* Treat 'buy herbs' or 'buy herb' as 'list herbs' */
    if (arg == "herbs" || arg == "herb")
    {
        list("herbs");
        return 1;
    }

    words = explode(arg, " ");
    if (sizeof(words))
    {
        sscanf(words[0], "%d", amount);
        if ( amount > 0)
            arg = implode(words[1..], " ");
        else
            amount = 1;
    }

    command("emote paws through the bundles of herbs piled around her.");
    if (!pointerp(hdata = All_herbs[arg]) || !hdata[H_COUNT])
    {
        command("say I have no " + arg + ".");
        command("scratch");
        return 1;
    }

    max_n = MIN(MAX_XFER, amount);

    if (member_array(TP->query_real_name(), m_indexes(Num_herbs)) != -1)
    {
        if((max_n + Num_herbs[TP->query_real_name()]) > MAX_ALLOW_BUY)
        {
            command("say I can only sell one person so many herbs so "
			    +"I don't run out.");
            return 1;
        }
    }

    if (max_n < amount)
    {
        command("say I will sell you " + MAX_XFER_WORD + " right now.");
        command("say I can only count so high...");
        command("blush");
    } 

    if (hdata[H_COUNT] < max_n)
    {
        command("sigh");
        command("say I don't have " + LANG_WNUM(max_n) +
            " of that herb in my stores.");
        return 1;
    }

    if (!can_afford(hdata[H_VALUE] * max_n))
    {
        command("say I cannot sell you my herbs for less than they "
		    +"are worth.");
        return 1;
    }

    if (!(herb_ob = clone_object(hdata[H_FILE])))
    {
        log_file(LOG_BUG, ctime(time()) + " wisewoman failed to clone " +
            arg + " from " + hdata[H_FILE] + "\n");
        command("say Hmm ... Sachluph doesn't seem to want me to sell it "
		    +"to you.");
        command("frown");
        hdata[H_COUNT] = 0;
        return 1;
    }

    herb_ob->set_heap_size(max_n);
    herb_ob->move(TO, 1);
    command("emote picks " + (max_n == 1 ? "a herb" : "some herbs") +
         " from a bundle beside her.");
    command("say Good potent herb, this " + arg + "is.");

    /* this is clumsy, perhaps, but moving them one at a time using
     * NAMEQ is the safest way, so ...  */
    tname = "herbs" + OB_NUM(herb_ob);
    herb_ob->add_pname(tname);
    command("give " + tname + " to " + NAMEQ(TP));
    if (ENV(herb_ob) == TO)
    {
         command("frown");
         command("say I'll just put " +
             ((herb_ob->num_heap() == 1) ? "it" : "them") + " here, "
			 +"and you can get it yourself.");
         command("drop " + tname);
    }
    herb_ob->remove_pname(tname);

    hdata[H_COUNT] -= max_n;
    if (hdata[H_COUNT] < 0)
    {
        hdata[H_COUNT] = 0;
    }
    if (!hdata[H_COUNT])
    {
        command("say I do think that was my last " + arg + ".");
    }
    herb_save();
    return 1;
}

/*
 * Function name: can_afford
 * Description  : pay for the herb, if can afford it
 * Arguments    : int price -- price in copper
 * Returns      : 1 if player pays for the herb, 0 if not
 */
public int
can_afford(int price)
{
    Money_arr = pay(price, TP, 0, 0, 0, 0);
    if (sizeof(Money_arr) == 1)
        return 0;

    Coin_pay_text = text(exclude_array(Money_arr, NUM, NUM*2-1));
    Coin_get_text = text(exclude_array(Money_arr, 0, NUM-1));
    write("You pay " + Coin_pay_text + " to " +
        TO->query_The_name(TP) + ".\n");

    if (Coin_get_text)
        write("You get " + Coin_get_text + " back.\n");

    return 1;
}

/*
 * Function name: sell
 * Description  : handle attempts to sell herbs
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 -- always
 */
public int
sell(string arg)
{
    int price, asked_for, hn;
    object herb_ob, *obj;
    mixed *hdata, nosell;
    string hname;

    tell_room(ENV(TO), QCTNAME(TP) + " murmurs something to " +
        QTNAME(TO)+".\n", TP);

    if (!strlen(arg))
    {
        command("say What herb do you want me to buy from you?");
        command("stare at "+ NAMEQ(TP));
        return 1;
    }

    arg = lower_case(arg);

    if (arg == "all herbs" || arg == "all")
    {
        do_sell_all(TP);
        return 1;
    }
    else if (!sizeof(obj = FIND_STR_IN_ARR(arg, all_inventory(TP))))
    {
        command("say What herb do you want to sell?");
        command("smile");
        return 1;
    }
    else if (!sizeof(obj = filter(obj, herb_filter)) ||
      (!objectp(herb_ob = obj[0])))
    {
        command("say You have no herb of that kind.");
        return 1;
    }

    tell_room(ENV(TO), QCTNAME(TP) + " offers an herb to " +
        QTNAME(TO) + ".\n", TP);

    nosell = herb_ob->query_prop(OBJ_M_NO_SELL);
    if (nosell)
    {
        if (stringp(nosell))
            write(nosell);

        command("say I'm sorry, but I cannot accept that herb.");
        return 1;
    }

    hname = herb_ob->query_herb_name();
    if (herb_ob->do_id_check(TO))
    {
        price = (herb_ob->num_heap() || 1) * herb_ob->query_herb_value() / 2;

        command(one_of_list(({
            "say One less herb to go searching for, now that you've " 
			+"sold me "+ LANG_ADDART(hname) + "!",
            "say Sachluph's tears, its "+ LANG_ADDART(hname) + "!",
            "say This is a special one, this "+ hname + " is!",
            "say I'm always happy to see more "+ hname+ "." })));
    }
    else
    {
        price = (herb_ob->num_heap() || 1) * herb_ob->query_herb_value();
        command("think");
        command("say I'll pay you " + price + " coppers for this!");

    }

    if (pointerp(hdata = All_herbs[hname]) && hdata[H_COUNT] > MAX_INV)
    {
        price = price / 2;
        command("say I cannot give you the full price for the " + hname + ".");
        command("say I already have " + LANG_WNUM(hdata[H_COUNT]) +
            " of the same.");
    }

    do_pay(TP, price);
    add_herb(herb_ob);
	herb_save();
	
    return 1;
}

/*
 * Function name: do_sell_all
 * Description  : handle "sell all herbs"
 * Arguments    : object player -- the person selling
 */
public void
do_sell_all(object player)
{
    object *herb_obs;
    mixed hdata;
    string hname, sherb;
    int total_price, price, hn, max_n, no_h, n, amount;

    herb_obs = filter(filter(all_inventory(player), herb_filter),
        &operator(==)(0) @ &->query_prop(OBJ_M_NO_SELL));
    no_h = sizeof(herb_obs);

    if (no_h <= 0)
    {
        command("say But you have no herbs to sell!");
        command("shrug");
        return;
    }

    tell_room(ENV(TO), QCTNAME(TP) + " offers some herbs to " +
        QTNAME(TO) + ".\n", TP);
    max_n = MIN(MAX_XFER, no_h);
 
    while (n < max_n)
    {
        hname = herb_obs[n]->query_herb_name();
        amount = herb_obs[n]->num_heap() || 1;

        if (herb_obs[n]->do_id_check(TO))
            price = amount * herb_obs[n]->query_herb_value() / 2;
        else
            price = amount * herb_obs[n]->query_herb_value();

        if (pointerp(hdata = All_herbs[hname]) && hdata[H_COUNT] > MAX_INV)
            price = price / 2;

        command("say " + capitalize(LANG_WNUM(amount)) + " " + hname +
            " - " + price + " coppers.");

        total_price += price;

        add_herb(herb_obs[n]);
        n++;
    }

    if (max_n < no_h)
    {
        command("say I'll just take the first " + MAX_XFER_WORD +
            " of your herbs.");
        command("say I can't count higher than that.");
        command("blush");
    }

    do_pay(player, total_price);
}

/*
 * Function name: do_pay
 * Description  : Pay the player. Maybe this should be changed one of
 *                these days to something in /lib/trade.c.
 * Arguments    : object player -- person to pay
 *                int price -- price in coppers
 */
public void
do_pay(object player, int price)
{
    string myname;
    object gc, sc, cc;
    int gold, silver, copper;

    command("emote counts some coins from a pouch.");
    gold = price / 144;
    silver = (price - (gold * 144)) / 12;
    copper = price - gold*144 - silver*12;
    cc = MONEY_MAKE_CC(copper);
    myname = TO->query_The_name(player);

    if (gold)
    {
        gc = MONEY_MAKE_GC(gold);
        write(myname + " gives you " + gold + " gold coins.\n");
        gc->move(TP, 1);
    }
    if (silver)
    {
        sc = MONEY_MAKE_SC(silver);
        write(myname+" gives you " + silver + " silver coins.\n");
        sc->move(TP, 1);
    }
    if (copper)
    {
        cc = MONEY_MAKE_CC(copper);
        write(myname+" gives you " + copper + " copper coins.\n");
        cc->move(TP, 1);
    }

    command("smile");
}

/*
 * Function name: add_herb
 * Description  : add herb to inventory
 * Arguments    : object herb_ob -- the one to add
 */
public void
add_herb(object herb_ob)
{
    string herb_file, hname;
    int    i, n, amount;
    mixed *hdata;

    if (!objectp(herb_ob))
    {
        return;
    }

    hname = herb_ob->query_herb_name();
    herb_file = MASTER_OB(herb_ob);
    amount = herb_ob->num_heap() || 1;

    if (pointerp(hdata = All_herbs[hname]))
    {
        hdata[H_COUNT] += amount;

        if (herb_file != hdata[H_FILE])
        {
            /* paranoia? */
            log_file(LOG_BUG, ctime(time()) + " Conflicting files " +
                herb_file + " and " + hdata[H_FILE] + " for '" + hname +
                "'.\n");
        }

        if (IS_HEAP_OBJECT(herb_ob))
        {
            herb_ob->restore_heap();
            herb_ob->set_heap_size(herb_ob->num_heap() - amount);
        }
        else
        {
            herb_ob->remove_object();
        }

        return;
    }

    hdata = allocate(3);
    hdata[H_FILE] = herb_file;
    hdata[H_COUNT] = amount;
    hdata[H_VALUE] = herb_ob->query_herb_value();
    All_herbs[hname] = hdata;

    if (IS_HEAP_OBJECT(herb_ob))
    {
        herb_ob->restore_heap();
        herb_ob->set_heap_size(herb_ob->num_heap() - amount);
    }
    else
    {
        herb_ob->remove_object();
    }

    herb_save();
}

/*
 * Function name: enter_inv
 * Description  : Mask parent to catch gifts of herbs.
 * Arguments    : object ob -- the entering object
 *                object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    int ran;

    ::enter_inv(ob, from);

    if (!living(from))
        return;
    else if (!function_exists("create_herb", ob))
        set_alarm(1.0, 0.0, &not_herb(ob, from));
    else if (Given_herb || Test_id_alarm_id)
        set_alarm(1.0, 0.0, &give_back_immediately(ob, from));
    else
        Test_id_alarm_id = set_alarm(5.0, 0.0, &test_identify(ob, from));

    return;
}

/*
 * Function name: not_herb
 * Description  : Return gifts that are not herbs.
 * Arguments    : object ob -- the object
 *                object from -- its source
 */
public void
not_herb(object ob, object from)
{
    if (!objectp(from) || ENV(from) != ENV())
    {
       ob->remove_object();
       return;
    }

    command("give " + NAMEQ(ob) + " to " + from->query_real_name());
}

/*
 * Function name: give_back_immediately
 * Description  : return herb when are busy with another one
 * Arguments    : object herb -- the one to return
 *                object from -- its source
 */
public void
give_back_immediately(object herb, object from)
{
    if (!objectp(from) || ENV(from) != ENV())
    {
        /* it's an herb .. keep it */
        add_herb(herb);
        return;
    }

    command("say Please wait until I am finished with this other herb, " +
        ((from->query_gender() == G_MALE) ? "sir" : "my lady")+".");
    command("give " + NAMEQ(herb) + " to " + NAMEQ(from));
    if (ENV(herb) == TO)
        command("drop " + NAMEQ(herb));
}

/*
 * Function name : test_identify
 * Description   : identify an herb
 * Arguments     : object herb -- the one to identify
 *                 object from -- its source
 */
public void
test_identify(object herb, object from)
{
    string id_str, find_str;

    Test_id_alarm_id = 0;
    if (!objectp(from) || ENV(from) != ENV())
    {
        /* it's an herb .. keep it */
        add_herb(herb);
        return;
    }
    Given_herb = herb;
    command("emote sniffs at " + Given_herb->query_name() + ".");
    command("think");
    if (Given_herb->do_id_check(TO))
        command("say " + Given_herb->query_id_long());
    else
        command("say I do not know what this " +
            Given_herb->query_name() + " does.");

    command("give " + NAMEQ(Given_herb) + " to " + from->query_real_name());
    command("say That is all I can tell you.");
    Given_herb = 0;
}

/*
 * Function name : show_herb
 * Description   : respond to a question about a specific herb
 * Arguments     : string hname -- the herb name
 *                 mixed *hdata -- the data for this herb
 * Returns       : 1 on success, 0 on failure
 */
public int
show_herb(string hname, mixed *hdata)
{
    object herb;

    if (!(herb = clone_object(hdata[H_FILE])))
        return 0;

    command("say Ahhh, " + hname + ".");
    command("ponder");
    if (herb->do_id_check(TO))
    {
        command("say To those unfamiliar with herbs " + hname + " looks " +
            "like "+LANG_ADDART(herb->short())+".");
        command("say However, to old women like me....");
        tell_room(ENV(), herb->query_id_long());
    }
    else
    {
        command("say " + CAP(hname) + " appears as " +
            LANG_ADDART(herb->short()) +".");
        command("say I don't know more.");
        command("boggle");
    }

    command("emote starts looking through her bundles of herbs.");
    if (hdata[H_COUNT] > 0)
        command("say I have " + LANG_WNUM(hdata[H_COUNT]) + " in stock.");
    else
        command("say I don't have that.");

    herb->remove_object();
    return 1;
}

/*
 * Function name: introduce
 * Description  : respond to introductions
 * Arguments    : string name -- name of the introduced living
 */
public void
introduce(object pl)
{
    if (!objectp(pl))
        return;
    command("introduce me");
}

/*
 * Function name: def_answer
 * Description  : answer to questions we don't understand
 * Returns      : "" (answer is written before return)
 */
public string
def_answer()
{
    mixed *hdata;
    string *prep, hname, q;

    prep =  ({ "about", "for", "show", });
    q = query_question();

    /* "ask" insists on having a question, so no need to check strlen */
    if (!parse_command(q, ({}), "%p %s", prep, hname))
        hname = q;

    if ((!pointerp(hdata = All_herbs[hname]) &&
       !pointerp(hdata = All_herbs[LANG_SWORD(hname)])) ||
       !show_herb(hname, hdata))
    {
        command("say I don't know what you are talking about!");
		command("boggle");
    }

    return "";
}

/*
 * Function name: ask_herbs
 * Description  : respond to questions about "herb" or "herbs"
 * Returns      : "" (answer is written before return)
 */
public string
ask_herbs()
{
    set_alarm(3.0, 0.0, &command("say I buy and sell herbs."));
    set_alarm(9.0, 0.0, &command("say If you have an unknown herb, give "
	    +"it to me so I can identify it."));
		return "";
}
/*
 * Function name: herb_filter
 * Description  : decide if argument is a herb
 * Arguments    : object ob -- the object of interest
 * Returns      : 1 if is herb, 0 if not
 */
public int
herb_filter(object ob)
{
    return (IS_HERB_OBJECT(ob) &&
        strlen(ob->query_herb_name()) && ob->query_herb_value());
}

/*
 * Function name: out_of_stock_filter
 * Description  : decide if we are out of this herb
 * Arguments    : string name -- name of the herb
 * Returns      : 1 if out of stock, 0 if not
 */
public int
out_of_stock_filter(string name)
{
   mixed *hdata = All_herbs[name];

   return (!pointerp(hdata) || !hdata[H_COUNT]);
}

/*
 * Function name: low_on_stock_filter
 * Description  : decide if we are low on this herb
 * Arguments    : string name -- name of the herb
 * Returns      : 1 if low, 0 if not
 */
public int
low_on_stock_filter(string name)
{
   mixed *hdata = All_herbs[name];

   return (!pointerp(hdata) || hdata[H_COUNT] < (MAX_INV / 2));
}

