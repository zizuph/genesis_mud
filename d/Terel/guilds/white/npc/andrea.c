/*
 * andrea.c
 * Herbalist for the Order of the White
 *
 * Original code taken and modified from Gondor's herbalist.c
 * Goldberry October 13, 1999
* Modified for use by Shinto, June 13, 2001
 */

#pragma strict_types
#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/lib/trade.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#define HERBAL_SAVE "/d/Terel/guilds/white/npc/herbalist_herbs"
#define MAX_HERBS 500 /* the maximum number of herbs Andrea will keep of one type */
#define NUM sizeof(MONEY_TYPES)
#define INTRODUCED_TO_ANDREA "introed_Andrea"
#define HERB_BUY "/d/Terel/guilds/white/log/herbs_bought"
#define HERB_SELL "/d/Terel/guilds/white/log/herbs_sold"

mixed  *herbs;

static string  pay_type, 
               get_type,
               coin_pay_text,
               coin_get_text,
              *sold_arr,
               log_str,
               book_str,
              *herb_buyer,
               name;
static int    *money_arr,
               no_report_flag,
               rem_flag_alarm_id,
               test_id_alarm_id;
static object  given_herb;

/* Prototypes */
int do_buy(int n);
void  restore_herbs();
void  remove_herb(int n);
int  can_afford(int price);
void not_herb(object herb, object from);
int test_identify(object herb, object from);
void give_back_immediately(object herb, object from);
public void do_pay(object player, int price);
public void add_herb(object herb);

public string
ask_herbs()
{
    command("say I will buy and sell herbs.");
    command("say I can also attempt to identify them if you wish me to.");
    command("say Just give the herb to me.");
    return "";
}


void
create_monster()
{
    set_name("andrea");
    add_name(({"herbalist"}));
    set_race_name("elf");
    set_gender(FEMALE);
    set_living_name("andrea");
    set_title("the Herbalist");
    set_adj("slim");
    set_adj("brown-haired");
    set_long("@@long_func");
    set_stats(({ 65, 105, 70, 99, 98, 65 }));
    set_hp(10000);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT,63000);
    add_prop(CONT_I_HEIGHT,184);
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");

    set_skill(SS_HERBALISM,98);
    set_skill(SS_AWARENESS, 87);
    set_skill(SS_WEP_POLEARM,65);
    set_skill(SS_WEP_KNIFE,90);
    set_skill(SS_WEP_SWORD,55);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_PARRY, 65);

    set_chat_time(7);
    add_chat("The gardens will need to be tended to soon.");
    add_chat("I've found some very interesting herbs in the Silver Forest.");
    add_chat("Walk in Peace.");
    add_chat("I might have something you might find useful.");


    set_act_time(4);
    add_act("@@announce_selling");

    add_ask(({"herbs","herb"}), ask_herbs,1);


    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));
    restore_herbs();
}


void
restore_herbs()
{
    seteuid(getuid(TO));
    restore_object(HERBAL_SAVE);
}

void
init_living()
{
    ::init_living();
    add_action("buy","purchase",0);
    add_action("sell","sell",0);
}

void
announce_selling()
{
    if (herbs) 
        command("say I have herbs for sale too, would you like some?");
    else 
        command("say I should go and search for more herbs.");
}

int
herb_filter(object ob)
{
    if (!function_exists("create_herb",ob)) 
        return 0;
    if (!ob->query_herb_name() || !ob->query_herb_value()) 
        return 0;
    return 1;
}

string
long_func()
{
    string long_str;
    long_str = "This sleepy looking halfling is the the herbalist of "+
               "Dabaay. From the greenish stains on his hands, to the "+
               "twigs and leaves stuck in his hair, he has the looks "+
               "of someone who gets into his work. He appears to have "+
               "some herbs for sale, and will probably list them if "+
               "you 'purchase herbs'. He would also probably be happy to "+
               "buy any herbs you have for sale.\n";
    return long_str;
}

string
wizinfo()
{
    int     n;
    string  str;
    if (!herbs) 
        return "The herbalist has no herbs for sale now.\n";
    str = "The herbalist has these herbs for sale:\n";
    while (n<sizeof(herbs)/4)
    {
        str = str + herbs[n * 4 + 2] + " " + herbs[n * 4] 
          + ": File " + herbs[n * 4 + 1] + ".\n";
        n++;
    }
    return str;
}

int
buy(string str)
{
    int     n;
    seteuid(getuid(TO));
    str = lower_case(str);
    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("say I cannot see, so I cannot help you.");
        return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
        command("say If you wish to buy or sell, then reveal thyself.");
        return 1;
    }
    if (str == "herbs" || str == "herb" || !stringp(str)) 
    {
        if (!sizeof(herbs)) 
        {
            command("say I have not herbs at the moment.");
            command("frown");
            return 1;
        }
        command("say These are the herbs I have available:\n");
        while (n < sizeof(herbs)/4) 
        {
            write("  " + herbs[n * 4 + 2] + " " 
              + LANG_PWORD(herbs[n * 4]) + " for " + herbs[n * 4 + 3]
              + " coppers each.\n");
            n++;
        }
        say(QCTNAME(TO) + " checks " + POSSESSIVE(TO) + " stores, "
          + "and lists the different herbs she has for "
          + QTNAME(TP) + ".\n", TP);
        write("That is all.\n");
        command("smile "+TP->query_real_name());
        return 1;
    }
    /* In case the player wanted to actually buy one of the herbs */
    n = 0;
    say(QCTNAME(TP) + " asks the herbalist for " + LANG_ADDART(str) 
      + ".\n", TP);
    write("The herbalist starts looking through her herb-storage.\n");
    say("The herbalist starts looking through her herb-storage.\n");
    while (n < sizeof(herbs) / 4) 
    {
        if ((str == herbs[n*4]) || (str == LANG_PWORD(herbs[n * 4]))) 
        {
            do_buy(n);
            return 1;
        }
        n++;
    }
    command("say I'm very sorry, "
      + ((TP->query_gender() == G_MALE) ? "sir" : "lady")
      + ", but I have no " + LANG_PWORD(str) + ".");
    command("sigh");
    return 1;
}

int
do_buy(int n)
{
    object  herb;
    string  hname;

    if (can_afford(herbs[n * 4 + 3])) 
    {
        if (!(herb = clone_object(herbs[n * 4 + 1]))) 
        {
            command("say It seems to have decayed.");
            command("frown");
            return 1;
        }
        hname = herb->query_herb_name(); 
        herb->move(TO, 1);
        tell_room(environment(), "The herbalist picks up a herb from "
          + "a little pouch.\n");
        command("say There you are, " +
          ((TP->query_gender() == G_MALE) ? "sir" : "lady") + "!");
        command("give " + OB_NAME(herb) + " to " + TP->query_real_name());
        if (environment(herb) == TO) 
        {
            command("peer");
            command("say I'll just put it here then.");
            command("drop " + OB_NAME(herb));
        }
        herbs[n * 4 + 2] -= 1;
        if (herbs[n * 4 + 2] <= 0)
            remove_herb(n);
        save_object(HERBAL_SAVE);
        write_file(HERB_BUY, TP->query_name() + " bought a " + hname + ", (" +
           ctime(time()) + ")\n"); 
    }
    else
    {
        command("sigh");
        command("say You don't seem to have enough, " +
          ((TP->query_gender() == G_MALE) ? "sir" : "lady") + ".");
    }
    return 1;
}

int
can_afford(int price)
{
    money_arr = pay(price, TP, 0, 0, 0, get_type);
    if (sizeof(money_arr) == 1)
        return 0;
    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
    write("You pay " + coin_pay_text + " to the Herbalist.\n");
    if (coin_get_text)
        write("You get "+coin_get_text+" back.\n");
    return 1;
}

void
remove_herb(int n)
{
    command("say That was my last " + herbs[n * 4] + ".");
    command("say I'll have to find more.");
    herbs = exclude_array(herbs, n * 4, n * 4 + 3);
}

int
do_sell_all(object player)
{
    object *herb;
    int     total_price,
            price,
            hn,
            max_n,
            no_h,
            n;

    string hnames;

    herb = filter(all_inventory(player), "herb_filter", TO);
    no_h = sizeof(herb);
    hnames = "";
    if (no_h <= 0)
    {
        command("say What herb did you want to sell?");
        command("shrug");
        return 1;
    }
    max_n = MIN(20, no_h);
    while (n < max_n)
    {
        if (herb[n]->do_id_check(TO))
            price = herb[n]->query_herb_value() / 2;
        else 
            price = herb[n]->query_herb_value();
        if ((hn = member_array(herb[n]->query_herb_name(), herbs)) 
          > -1)
        {
            if (herbs[hn + 2] > MAX_HERBS) 
                price = price / 2;
        }
        command("say One " + herb[n]->query_herb_name() + " - "
          + price + " coppers.");
        total_price += price;
        hnames = hnames + herb[n]->query_herb_name() + ", ";
        add_herb(herb[n]);
        n++;
    }
    if (max_n < no_h)
    {
        command("say Twenty at a time.");
    }
    do_pay(player, total_price);
    save_object(HERBAL_SAVE);
    write_file(HERB_SELL, TP->query_name() + " sold " + hnames + " for: " +
       total_price + ", (" + ctime(time()) + ")\n");
    return 1;
}

int
sell(string str)
{
    int     price,
            asked_for = 0,
            hn;
    object  herb,
            tp = TP,
           *obj;
    string  hname;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("say I cannot help you if I am unable to see.");
        return 1;
    }
    if (!CAN_SEE(TO, tp))
    {
        command("say You will have to reveal yourself if you wish for my help.");
        return 1;
    }
    if (!strlen(str))
    {
        command("say What did you want to sell?");
        command("eyebrow");
        return 1;
    }

    if (str == "all")
    {
        command("say I only buy and sell herbs.");
        return 1;
    }

    if (str == "all herbs")
    {
        do_sell_all(tp);
        return 1;
    }

    if (!sizeof(obj = FIND_STR_IN_ARR(str, all_inventory(tp))))
    {
        command("say What herbs did you want to sell?");
        command("eyebrow");
        return 1;
    }
    if (!sizeof(obj = filter(obj, herb_filter)) 
        || (!objectp(herb = obj[0])))
    {
        command("say You don't have that, "
          + ((tp->query_gender() == G_MALE) ? "sir" : "dear")+".");
        return 1;
    }

    if (herb->do_id_check(TO))
    {
        price = herb->query_herb_value() / 2;
        switch(random(4))
        {
            case 0: 
                command("say Nice, "
                  + LANG_ADDART(herb->query_herb_name()) + "!"); 
                break;
            case 1:
                command("say Ahh, a "
                  + herb->query_herb_name() + "!");
                break;
            case 2: 
                command("say Good, a "
                  + CAP(LANG_ADDART(herb->query_herb_name())) + "!"); 
                break;
            case 3:
                command("say By her song, a  "
                  + CAP(LANG_ADDART(herb->query_herb_name())) + "!");
                break;
        }
    }
    else
    {
        command("eyebrow");
        command("say I do not know what this herb is.");
        command("say I'd like to study this "+
           herb->query_name() + ".");
        command("ponder");
        command("say I'll give you " + herb->query_herb_value()
          + " coppers for this, "
          + ((TP->query_gender() == G_MALE) ? "sir" : "lady") +".");
        price = herb->query_herb_value();
    }
    if ((hn = member_array(herb->query_herb_name(),herbs)) > -1)
    {
        if (herbs[hn + 2] > MAX_HERBS)
        {
            price = price/2;
            command("say I can't give you the full price for the "
              + herb->query_herb_name() + ".");
            command("say I already have " + LANG_WNUM(herbs[hn+2]) 
              + " of the same in my supply.");
        }
    }
    do_pay(TP, price);
    hname = herb->query_herb_name();
    write_file(HERB_SELL, TP->query_name() + " sold " + hname + " for: " +
       price + ", (" + ctime(time()) + ")\n");
    add_herb(herb);
    save_object(HERBAL_SAVE);
    return 1;
}

public void
do_pay(object player, int price)
{
    object  gc, 
            sc, 
            cc;
    int     g, 
            s, 
            c;

    tell_room(environment(),"The herbalist counts some coins "
      + "from a pouch.\n");
    g = price / 144;
    s = (price - (g*144)) / 12;
    c = price - g*144 - s*12;
    cc = MONEY_MAKE_CC(c);
    if (g)
    {
        gc = MONEY_MAKE_GC(g);
        write("The herbalist gives you " + g + " gold coins.\n");
        gc->move(TP, 1);
    }
    if (s)
    {
        sc = MONEY_MAKE_SC(s);
        write("The herbalist gives you " + s + " silver coins.\n");
        sc->move(TP, 1);
    }
    if (c)
    {
        cc = MONEY_MAKE_CC(c);
        write("The herbalist gives you " + c + " copper coins.\n");
        cc->move(TP, 1);
    }
    command("smile");
}

public void
add_herb(object herb)
{
    string  herb_file,
            trash;
    int     n, s;

    seteuid(getuid(TO));

    if (!objectp(herb))
        return;
    herb_file = MASTER_OB(herb);

    s = sizeof(herbs) / 4;
    while (n < s)
    {
        if (herbs[n*4+1] == herb_file)
        {
            if (herbs[n*4+2] < MAX_HERBS)
                herbs[n*4+2]++;
            herb->remove_object();
            return;
        }
        n++;
    }
    command("say My thanks, I had run out of "
      + LANG_PWORD(herb->query_herb_name())+".");
    if (!herbs) 
        herbs = ({ herb->query_herb_name(), herb_file, 1, 
            herb->query_herb_value() });
    else
        herbs += ({ herb->query_herb_name(), herb_file, 1,
            herb->query_herb_value() });
    herb->remove_object();
    save_object(HERBAL_SAVE);
}

public void
enter_inv(object herb, object from)
{
    int     ran;

    ::enter_inv(herb, from);
    if (!objectp(from))
        return;

    if (!function_exists("create_herb",herb))
    {
        set_alarm(1.0, 0.0, &not_herb(herb, from));
        return;
    }
    if (given_herb || test_id_alarm_id)
    {
        set_alarm(1.0, 0.0, &give_back_immediately(herb, from));
        return;
    }
    test_id_alarm_id = set_alarm(5.0, 0.0, &test_identify(herb, from));
    return;
}


void
not_herb(object herb, object from)
{
    command("say What should I do with this?");
    switch(random(4))
    {
        case 0:
            command("say I've no interest in this "
              + herb->query_name() + "?");
            break;
        case 1:
            command("say I got too many things to do to be dealing with "
              + LANG_PWORD(herb->query_name()) + ", "
              + from->query_race_name() + ".");
            break;
        case 2:
            command("say I am a herbalist, " + from->query_race_name()
              + ", I don't know what this has to do with me.");
            break;
        case 3:
            command("say This is of no interest to me, "
              + ((from->query_gender() == G_MALE) ? "mister" : "madam")
              + ".");
            break;
    }
    command("give " + OB_NAME(herb) + " to " 
      + from->query_real_name());
}

void
give_back_immediately(object herb, object from)
{
    command("say A moment please, "
      + ((from->query_gender() == G_MALE) ? "sir" : "lady")+".");
    command("give " + OB_NAME(herb) + " to "
      + from->query_real_name());
}

int
test_identify(object herb, object from)
{
    object  player;
    string  id_str,
            find_str;

    given_herb = herb;
    player = from;
    tell_room("The herbalist looks closely at the "
      + given_herb->query_name() + ".\n");
    command("think");
    switch(given_herb->query_id_diff() / 10)
    {
        case 0:
            command("laugh");
            id_str = "Fairly common.";
            break;
        case 1:
            command("giggle");
            id_str = "I've found these quite easily.";
            break;
        case 2:
            command("giggle");
            id_str = "This one is interesting.";
            break;
        case 3:
            command("ponder");
            id_str = "I've seen this one around. Easy to mistake for another.";
            break;
        case 4:
            command("smile");
            id_str = "Most people can't recognize this one.";
            break;
        case 5:
            command("smile");
            id_str = "Very nice. This one is hard to tell from the "
              + "Crimbul herb.";
            break;
        case 6:
            command("think");
            id_str = "Now this, this is a hard one to identify.";
            break;
        case 7:
            command("eyebrow");
            id_str = "Yes, very interesting.";
            break;
        case 8:
            command("emote looks a bit confused.");
            id_str = "This one is quite rare.";
            break;
        case 9:
            command("emote taps her chin with a finger.");
            id_str = "None too sure about this one. Must be though.";
            break;
        case 10:
            command("confused");
            id_str = "Now this herb is just plain rude.";
    }
    command("say " + id_str);
    switch(given_herb->query_find_diff())
    {
        case 0:
            command("laugh");
            find_str = "Usually see these everywhere.";
            break;
        case 1:
            command("giggle");
            find_str = "This one is too common.";
            break;
        case 2:
            command("grin .");
            find_str = "Easy hard to find.";
            break;
        case 3:
            command("smile");
            find_str = "Interesting. Not everybody knows where to "
              + "find this one.";
            break;
        case 4:
            command("smile");
            find_str = "Nice! This one is hard to find.";
            break;
        case 5:
            command("smile");
            find_str = "Bet you spent some time looking "
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
    }
    command("say " + find_str);
    if (given_herb->do_id_check(TO))
        command("say " + given_herb->query_id_long());
    else
        command("say It is unknown to me what the effect of this "
          + given_herb->query_name() + " is.");
    command("give " + OB_NAME(given_herb) + " to "
      + player->query_real_name());
    command("say I hope my information has been useful, "
      + ((player->query_gender()==G_MALE) ? "sir" : "my lady") + ".");
    command("bow");
    given_herb = 0;
    test_id_alarm_id = 0;
    return 1;
}

void
intro_me(string str)
{
    object  pl;
    pl = find_player(lower_case(str));
    
    if (!present(pl, ENV(TO)))
    {
        pl->add_prop(INTRODUCED_TO_ANDREA, 1);
        return;
    }
    if (pl->query_prop(INTRODUCED_TO_ANDREA))
    {
        command("greet " + str);
        command("say Nice to see you again, " + pl->query_name() + "!");
        return;
    }
    pl->add_prop(INTRODUCED_TO_ANDREA, 1);
    command("hail " + str);
    command("say I'm Andrea, it is my pleasure to meet you.");
    command("introduce myself");
}

void
add_introduced(string str)
{   
    object  pl = TP;
    set_alarm(3.0, 0.0, &intro_me(str));
}


int
remove_herb_from_list(string herb)
{
    int     n,
            s;

    n = 0;
    s = sizeof(herbs);

    while(n < s / 4)
    {
        if (herb == herbs[n*4] || herb == LANG_PWORD(herbs[n*4]))
        {
            if (n == 0)
                herbs = herbs[4..s-1];
            else if(n == s/4-1)
                herbs = herbs[0..s-5];
            else 
                herbs = herbs[0..n*4-1] + herbs[(n+1)*4..s-1];
            return 1;
        }
        n++;
    }
    return 0;
}
