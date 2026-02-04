/*
 * Mostly a copy of the ranger guild herbalist.
 */
inherit "/std/monster";
inherit "/lib/trade";
#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#define PATH  "/d/Terel/common/town/garden/"

#define HERBAL_SAVE           PATH  + "herbalist_herbs" 
#define LOG_BUG               PATH  + "herbalist.errors"
#define MAX_ALLOW_BUY         20
#define MAX_XFER              20  /* buy/sell <= 20 at a time */
#define MAX_XFER_WORD         "twenty"
#define MAX_INV               75 
#define NUM                   sizeof(MONEY_TYPES)
/* indices into herb data */
#define H_FILE                0
#define H_COUNT               1
#define H_VALUE               2

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
public string ask_dark();
public string ask_menablix();
public int    herb_filter(object ob);
public int    out_of_stock_filter(string name);
public int    low_on_stock_filter(string name);


public void
create_monster()
{

    set_name("dibanasha");
    add_name(({"herbalist","herbwoman","witch", "woman", "crone"}));
	set_gender(G_FEMALE);
    set_race_name("half-elf");
    set_living_name("dibanasha");
    set_title("the Hedge Witch");
    set_adj(({ "blind", "wrinkled", "bent", "hedge", "old" }));
	set_short("blind old crone");
    set_long("This is an ancient woman, nearly bent in half with age. "+
        "Her eyes are completely white, as is her hair. Her clothes "+
        "are smudged with black filth.\nShe wears a belt with many "+
        "pouches containing herbs.\n");
    set_stats(({ 60, 60, 60, 100, 100, 100 }));
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_HEIGHT, 75);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK, "You should be ashamed of yourself! "+
        "What kind of person beats up old women??\n");
    set_skill(SS_HERBALISM, 105);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE, 50);

    set_chat_time(20);
    add_chat("I am old and alone, there is no one left to care for me.");
    add_chat("I helped banish the darkness that dwelled in this place, "+
       "and so long as I remain, it will stay banished.");
    add_chat("Buy some herbs from me, so I may get some food in Calathin.");
    add_chat("In darkness I live, and in darkness shall I remain for "+
        "the rest of my days.");
    add_chat("I lost my sight to the darkness.");
    add_chat("I'm proud to be a hedge witch. I've kept learning about "+
       "magic all my life.");

	set_act_time(5);
    add_act("emote rocks back and forth, back and forth.\n");
	add_act("shiver");
	add_act("emote rubs her hands together to try to keep them warm.");
    add_act("emote reveals a toothless smile.");
	add_act("moan");
	add_act("emote rubs her knee as though it pains her.");
	add_act("shout What more must I sacrifice?");

    add_ask(({"herbs", "herb"}), &ask_herbs());
	add_ask(({"[about] [the] 'darkness' [you] / [she] [fought] / [banished]"}),
        &ask_dark());
    add_ask(({"[about] [hedge] 'magic'"}),
        "say It is called hedge magic when you have natural abilities "+
        "with magic but aren't trained by anyone else, instead you "+
        "learn what you can do as you go along.", 1);
    add_ask(({"[about] [why] [are] [you] [a] [hedge] 'witch'"}),	
        "say I call myself a hedge witch because that is what I am. I have "+
        "innate magic and am self-taught. I never got to learn from no one "+
        "else. They all died fighting a great evil that once dwelt here.", 1);	
    add_ask(({"[about] [why] [are] [you] 'alone' / 'lonely'"}),
        "say I could find no one willing to stay with me here, to keep guard. "+
        "So I do it alone and have done so for many many many years.", 1);		
    add_ask(({"[about] [her] / [your] 'eyes' / 'blindness' / 'eyesight' "+
        "/ 'sacrifice'"}),
        "say I fought a great evil and it took my eyes from me. "+
        "I managed for decades without them, and I'm so old now "+
        "that most people my age can't see anyways.", 1);
    add_ask(({"[about] [why] [are] [you] 'blind'"}),
        "say I fought a great evil and it took my sight from me. "+
        "I managed for decades without them, and I'm so old now "+
        "that most people my age can't see anyways.", 1);		
    add_ask(({"[about] [the] [great] 'evil' [she] / [you] [fought]"}),
        "say He was an evil creature with perverted magic that threatened "+
        "all living things. Menablix, he was called.", 1);
    add_ask(({"[about] 'benton' / 'vercus' / 'necromancers'"}), 
	    "say There were three practitioners of evil and perverted "+
        "magic: Benton, Menablix, and Vercus. I will say no more about them.", 1);
    add_ask(({"[about] 'necromancy'"}),
        "say There is magic in the world that feeds life, and then there is "+
        "magic in the world that feeds on life. Some call it necromancy.", 1);			
    add_ask(({"[about] 'perverted' 'magic'"}),
        "say There is magic in the world that feeds life, and then there is "+
        "magic in the world that feeds on life. Some call it necromancy.", 1);			
    add_ask(({"[about] [the] 'necromantic' 'arts'"}), 
        "say There is magic in the world that feeds life, and then there is "+
        "magic in the world that feeds on life. Some call it necromancy.", 1);		
    add_ask(({"[about] / [who] [is] / [was] [the] [evil] [called] 'menablix'"}), 
        &ask_menablix());	
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

    tell_room(environment(TO), QCTNAME(TP) + " asks " + QTNAME(TO) + " a question.\n", TP);

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

    command("emote pats the pouches of herbs cluttering her waist.");
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
            command("say I can't sell you that many.");
            return 1;
        }
    }

    if (max_n < amount)
    {
        command("say I will sell you " + MAX_XFER_WORD + " right now.");
        command("say Without my eyes I can't keep track of more.");
        command("sigh");
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
        log_file(LOG_BUG, ctime(time()) + " witch failed to clone " +
            arg + " from " + hdata[H_FILE] + "\n");
        command("say Hmm I can't seem to sell it to you.");
        command("frown");
        hdata[H_COUNT] = 0;
        return 1;
    }

    herb_ob->set_heap_size(max_n);
    herb_ob->move(TO, 1);
    command("emote picks " + (max_n == 1 ? "a herb" : "some herbs") +
         " from a pouch at her waist.");
    command("say Good potent herb, this " + arg + " is.");

    /* this is clumsy, perhaps, but moving them one at a time using
     * NAMEQ is the safest way, so ...  */
    tname = "herbs" + OB_NUM(herb_ob);
    herb_ob->add_pname(tname);
    command("give " + tname + " to " + TP->query_name());
    if (environment(herb_ob) == TO)
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

    tell_room(environment(TO), QCTNAME(TP) + " murmurs something to " +
        QTNAME(TO)+".\n", TP);

    if (!strlen(arg))
    {
        command("say What herb do you want me to buy from you?");
        command("frown at "+ TP->query_real_name());
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

    tell_room(environment(TO), QCTNAME(TP) + " offers an herb to " +
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
            "say This "+ LANG_ADDART(hname) + " goes right here.",
            "say I'm always happy to have more "+ LANG_ADDART(hname) + "!",
            "emote smells the "+ hname +" and stuffs it in a pouch.",
            "emote smoothes the "+ hname +" between her gnarled fingers." })));
    }
    else
    {
        price = (herb_ob->num_heap() || 1) * herb_ob->query_herb_value();
        command("think");
        command("say I'll pay you " + price + " coppers for it.");

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

    tell_room(environment(TO), QCTNAME(TP) + " offers some herbs to " +
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
        command("say My hands can't hold much more at a time.");
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
    if (!objectp(from) || environment(from) != environment())
    {
       ob->remove_object();
       return;
    }

    command("give " + ob->query_name() + " to " + from->query_real_name());
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
    if (!objectp(from) || environment(from) != environment())
    {
        /* it's an herb .. keep it */
        add_herb(herb);
        return;
    }

    command("say Please wait until I am finished with this other herb, " +
        ((from->query_gender() == G_MALE) ? "boyo" : "girlie")+".");
    command("give herb to " + from->query_name());
    if (environment(herb) == TO)
        command("drop herb");
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
    if (!objectp(from) || environment(from) != environment())
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

    command("give " + Given_herb->query_name() + " to " + 
        from->query_real_name());
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
        command("say However, to old women like me...");
        tell_room(environment(), herb->query_id_long());
    }
    else
    {
        command("say " + CAP(hname) + " appears as " +
            LANG_ADDART(herb->short()) +".");
        command("say I don't know more.");
        command("emote rubs her forehead.");
    }

    command("emote starts looking through her pouches of herbs.");
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
    set_alarm(2.0, 0.0, &command("say I buy and sell herbs."));
    set_alarm(4.0, 0.0, &command("puffs out a breath."));	
    set_alarm(9.0, 0.0, &command("say If you have an unknown herb, give "
	    +"it to me so I can identify it."));
		return "";
}

/*
 * Function name: ask_dark
 * Description  : respond to questions about the darkness
 * Returns      : "" (answer is written before return)
 */
public string
ask_dark()
{
    set_alarm(1.0, 0.0, &command("emote sighs and stratches her forehead."));
    set_alarm(3.0, 0.0, &command("emote breathes: When I was much younger, "+
       "shortly after my last child married, an elf came to Last looking "+
       "for help with a great evil."));	
    set_alarm(5.0, 0.0, &command("emote puffs out her cheeks."));	
    set_alarm(9.0, 0.0, &command("say He gathered up all those who could "+
       "use magic and brought us to this tower."));
    set_alarm(10.0, 0.0, &command("emote pants like she can't catch her breath."));
    set_alarm(14.0, 0.0, &command("say We fought for three days and nights "+
        "we did. The darkness took my sight but I kept casting."));
    set_alarm(17.0, 0.0, &command("emote wipes a tear from her deeply "+
        "wrinkled cheek."));
    set_alarm(20.0, 0.0, &command("say Few survived and most of those were "+
        "mortally injured. I stayed to ease their passing."));
    set_alarm(22.0, 0.0, &command("say I stayed on to make sure the evil "+
        "does not return."));
	   
		return "";
}


/*
 * Function name: ask_menablix
 * Description  : respond to questions about Menablix the Necromancer
 * Returns      : "" (answer is written before return)
 */
public string
ask_menablix()
{
    set_alarm(2.0, 0.0, &command("say An evil man with an evil aim."));
    set_alarm(4.0, 0.0, &command("say Menablix had two brothers: Benton "+
        "and Vercus."));	
    set_alarm(6.0, 0.0, &command("say They all had a fascination with "+
        "the necromantic arts, and it took a gathering of all who could "+
        "use magic to stop Menablix from unleashing his evil upon the world."));
    set_alarm(8.0, 0.0, &command("say Thankfully the three were always "+
        "fighting each other...the world would succumb to their powers "+
        "if they ever joined forces."));	
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

