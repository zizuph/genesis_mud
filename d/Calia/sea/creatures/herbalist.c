
/* 
 * The Herb-master of Calia, based on the Herb-master of Minas Tirith.
 * By Elessar, July 17th 1992.
 * added training of herbalism, Olorin, Sep 1993
 * The teaching routines were added following an example by Mortricia.
 * Upgraded for use in Calia to current code standards, Khail, Nov 8/96
 * Specifically, strict_typed, remove trigs & call_outs, removed
 * references to gondor rangers herb book & quests, and prototyped
 * where required for direct addressing rather than string function
 * references.
 * Introduced MAX_SELL_ALL, it seems there can be a too long evaluation
 * if one tries to sell a huge amount, Maniac, 10/12/96 
 *
 * Added the 'reply_moss' function for the Calian Sup. Guru quest,
 * Khail, Feb 8/97
 * 
 * Inaccuracy in naming of herbs corrected, Maniac, 17/2/99
 * Switched to save herbs using save_map instead of save_object,
 * it cuts out saving all the npc state variables, Maniac, 
 * 1/8/99 
 * 
 * No longer buys OBJ_M_NO_BUY herbs or sells OBJ_M_NO_SELL ones, 
 * Maniac, 23/12/00
 * 
 * Added Academy of Elemental Arts task 2 code to gather herbs
 * Petros, December 2009
 */
#pragma strict_types

#define MAX_SELL_ALL 40

#include <composite.h>

inherit "/std/monster";
inherit "/lib/trade";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Calia/std/npc_receive";
inherit "/d/Sparkle/area/city/lib/utility_functions";

/* Global Vars */
mixed  *herbs;

static string pay_type,
              get_type,
              coin_pay_text,
              coin_get_text,
              *sold_arr,
              log_str,
              book_str,
              name;
static int money_arr,
           closed,
           herb_book_id,
           no_report_flag;
static object given_herb;
static mixed tmp; // helps speed up some functions called a lot 

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include <files.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "/d/Calia/sea/creatures/herbalist.h"
#include "/d/Calia/eldoral/guru_quest.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define HERBAL_SAVE     "/d/Calia/sea/creatures/misc/herbalist_herbs"
#define LOG_REPORT_FILE "/herbs"
#define HERB_BOOK       "/d/Gondor/common/library/books/herb-guide.txt"
#define MAX_HERBS       500 /* Max number per herb carried */
#define NUM             sizeof(MONEY_TYPES)
#define CLOSED          0 
#define SS_PATRON_ELEMENTAL 114052
// Defines for Academics
#define ACADEMIC_MANAGER     "/d/Calia/guilds/academics/lib/academy_manager"
#define IS_ACADEMIC(x)       ACADEMIC_MANAGER->query_is_member(x)
#define TASK_TWO_GIVEN       "_academic_task_two_given"
#define LOBAR_ACADEMIC_TASK_GIVEN   "_lobar_academic_task_given"

/* Some prototypes */
public void arm_me(); 
public void do_pay(object player, int price);
varargs public void add_herb(object herb, int nosave);
public void set_up_skills();
public int my_buy(string str);
public int do_buy(int n);
public int my_sell(string str);
public void not_herb(mixed hf);
public void give_back_immediately(mixed hf);
public int test_identify(mixed h_arr);
public void restore_herbs();
public void save_herbs(); 
public int can_afford(int price);
public int remove_herb(int n);
public string reply_academic();
public void report_task_2_progress(object player);

// Global Variables
public int      identify_alarm;

/*
 * Function name: reply_moss
 * Description  : Replies when a player asks about vampiric moss.
 * Arguments    : n/a
 * Returns      : String to execute in a command() function in
 *                response.
 */
public string
reply_moss()
{
    object who;
    string name;

    who = this_player();
    name = lower_case(who->query_real_name());

    command("whisper " + name + " Vampiric moss? Nasty stuff, " +
        "nasty stuff. Fortunately you rarely, if ever, see " +
        "it.");
    command("ponder");
    return ("whisper " + name + " All I can really tell you " +
        "about it off the top of my head, is that it's usually " +
        "found growing at the tops of dead trees.");
}

public void
create_monster()
{
    if (!herbs)
        herbs = ({});
    closed = CLOSED;

    set_name("lobar");
    add_name(({"herbalist","teacher"}));
    add_name("ranger");
    set_race_name("human");
    set_living_name("lobar");
    set_title("the Herbalist of Calia");
    set_adj("old");
    set_adj("friendly");
    set_long("@@long_func");
    set_stats(({ 55, 55, 60, 99, 98, 55 }));
    set_base_stat(SS_OCCUP, 75);
    set_base_stat(SS_LAYMAN, 50);
    set_hp(10000);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT,63000);
    add_prop(CONT_I_HEIGHT,174);
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");

    set_skill(SS_BRAWLING, 60 + random(10));
    set_skill(SS_HEARING, 60 + random(10));
    set_skill(SS_HERBALISM,96);
    set_skill(SS_WEP_POLEARM,85);
    set_skill(SS_DEFENCE,52);
    set_skill(SS_PATRON_ELEMENTAL,2);

    create_skill_raise();
    set_up_skills();

    set_chat_time(7);
    add_chat("I am Lobar, brother of Lothmir, the best herbalist in Gondor!");
    add_chat("You would not have any unknown herbs, would you?");
    add_chat("You know the old saying: There is an herb for every occasion.");
    add_chat("I think I have seen most herbs in the world by now.");
    add_chat("If you have an unknown herb, you can let me identify it for you.");
    add_chat("You never know when a herb might come in handy.");
    add_chat("If you ask me, I can tell you about herbs and lore.");
    set_cchat_time(2);
    add_cchat("But what have I ever done to hurt you?!?");
    add_cchat("I am a poor old man, my eyes are grey, my legs are old and bent!");
    add_cchat("Beware! Or I shall taunt you a second time!");
    set_act_time(4);
    add_act("@@announce_selling");
    set_cact_time(2);
    add_cact("brawl");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));
    add_ask(({"garlic"}), VBFC_ME("ask_garlic"));
    add_ask(({"herbalism","lesson","lessons","train","training"}),
        "say Why don't you try to learn or improve?",1);
    add_ask( ({ "amjal" }), "@@reply_academic");

#ifdef GURU_OPEN
    add_ask(({"vampiric moss", "about vampiric moss"}),
        VBFC_ME("reply_moss"), 1);
#endif

    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

    set_alarm(0.0, 0.0, arm_me); 
}

public void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM_DIR + "drcloak");
    arm->move(TO);
    command("wear cloak");
    arm = clone_object("/d/Gondor/common/guild/rring");
    arm->move(TO);
    command("wear all");
    clone_object("/d/Calia/worshippers/specials/worshipshadow")->shadow_me(TO,
        "layman", "cleric", "Elemental Worshippers of Calia", "");
    clone_object("/d/Calia/worshippers/objects/sceptre")->move(TO); 
    restore_herbs();
}


/*
 * Function:     restore_herbs
 * Description:  restore the herbalist's herb stock from file
 */ 
public void
restore_herbs()
{
    mapping tmpmap; 
    seteuid(getuid(TO));
    tmpmap = restore_map(HERBAL_SAVE); 
    herbs = tmpmap["herbs"]; 
}

/*
 * Function:     save_herbs
 * Description:  save the herbalist's herb stock to file
 */ 
public void
save_herbs() 
{
    mapping tmpmap; 
    seteuid(getuid(TO));
    tmpmap = ([ "herbs" : herbs ]); 
    save_map(tmpmap, HERBAL_SAVE); 
}


public void
init_living()
{
    ::init_living();
    init_skill_raise();
    add_action(my_buy,"buy");
    add_action(my_sell,"sell");
    no_report_flag = 0;
}

public void
announce_selling()
{
    if (herbs) 
        command("say I have herbs for sale too, would you like some?");
    else
        command("say I should go and search for more herbs.");
}

public int
herb_filter(object ob)
{
    if (!function_exists("create_herb",ob))
        return 0;
    if (!ob->query_herb_name() || !ob->query_herb_value())
        return 0;
    return 1;
}

public string
long_func()
{
    string long_str;
    long_str = "This is Lobar, brother of Lothmir, the herb-master of the "+
        "Rangers. He is said to "+
        "know a great deal about herbs and plants and their virtues. If " +
        "you give him a herb, he will try to identify it for you. He " +
        "might also have some herbs to sell, and will tell you what he " +
        "has if you 'buy herbs'. If you have herbs to sell, Lobar will " +
        "probably be happy to buy it. Sometimes he even teaches his " +
        "skill to others, but he might ask a favour of you before he " +
        "reveals parts of his wisdom. ";
    if (TP->query_wiz_level())
        return break_string(long_str+" Type 'Info herbalist' for more " +
            "info.\n",75);
    return break_string(long_str+"\n",75);
}

public string
wizinfo()
{
    int n;
    string str;
    if (!herbs)
        return "The herbalist has no herbs for sale now.\n";
    str = "The herbalist has these herbs for sale:\n";
    while (n < (sizeof(herbs)/4))
    {
        str = str+herbs[n*4]+": File "+herbs[n*4+1]+" - "+herbs[n*4+2]+
            " for sale, "+herbs[n*4+3]+" cc each.\n";
        n++;
    }
    str +=  "\n" +
        "If there should be due cause to stop the herbalist from " +
        "teaching,\n do so by typing:  Call lobar close_open\n"+
        "This will temporarily prevent mortals from learning. After a\n"+
        "reboot, Lobar will be open by default. Please send me some\n"+
        "mail if there is anything that needs to be fixed.\n\n  Jaacar.\n";
    return str;
}

public int
my_buy(string str)
{
    int n;
    seteuid(getuid(TO));
    str = lower_case(str);

    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("say Uhmm, you wouldn't by any chance have a torch handy?");
        command("say It's too dark for me to do business.");
        return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
        command("say Uhmm, where are you hiding? I can't see you?");
        command("suspicious");
        return 1;
    }
    if (str == "herbs" || str == "herb" || !str)
    {
        write("The herbalist says: ");
        if (!herbs)
        {
           write("I'm sorry, I have no more herbs for sale.\n");
           command("sigh");
           return 1;
        }
        write("I have:\n");
        while (n < (sizeof(herbs)/4))
        {
            write("  "+herbs[n*4+2]+" "+LANG_PWORD(herbs[n*4])+" for "+
                herbs[n*4+3]+" coppers each.\n");
            n++;
        }
        write("That was all.\n");
        command("smile "+OB_NAME(TP));
        return 1;
    }

  /* In case the player wanted to actually buy one of the herbs */
    n = 0;
    say(QCTNAME(TP)+" asks the herbalist for " + LANG_ADDART(str) + 
        ".\n",TP);
    write("The herbalist starts looking through his herb-storage.\n");
    say("The herbalist starts looking through his herb-storage.\n");
    while (n < (sizeof(herbs)/4))
    {
        if (str == herbs[n*4] || str == LANG_PWORD(herbs[n*4]))
        {
            do_buy(n);
            return 1;
        }
        n++;
    }
    command("say I'm deeply sorry, "+
        ((TP->query_gender() == G_MALE) ? "sir" : "my lady")+
        ", but I have no "+LANG_PWORD(str)+".");
    command("sigh");
    return 1;
}

public int
do_buy(int n)
{
    object herb;

    if (!objectp(herb = clone_object(herbs[n*4+1]))) { 
        command("say Hmm....I'm deeply sorry - it seems to have " + 
                "decayed..."); 
        command("frown"); 
        return 1; 
    } 
    if (herb->query_prop(OBJ_M_NO_BUY)) { 
        command("say Hmm....I'm deeply sorry - this herb should not " + 
                "be on display, it's not for sale..."); 
        command("sigh"); 
        herb->remove_object(); 
        herbs = exclude_array(herbs, n*4, n*4+3); 
        return 1; 
    } 
    if (can_afford(herbs[n*4+3]))
    {
        herb->move(TO);
        tell_room(environment(),"The herbalist picks up a herb from a " +
            "little pouch.\n");
        command("say I hope it will be useful, "+
            ((TP->query_gender() == G_MALE) ? "sir" : "mylady")+"!");
        command("give "+OB_NAME(herb)+" to "+OB_NAME(TP));
        if (environment(herb) == TO) 
        {
            command("frown");
            command("say I'll just put it here then.");
            if (!command("drop "+OB_NAME(herb))) 
            { 
                log_file("bugs", ctime(time()) + "\n" +  
                       "Report by " + file_name(TO) + "\n" + 
                       "The herb " + file_name(herb) + " is not " +
                       "properly named.\n\n"); 
             
                herb->move(environment(TO)); 
            } 
        }
        herbs[n*4+2] -= 1;
        if (herbs[n*4+2] <= 0) 
            remove_herb(n);
        save_herbs();
    }
    else 
    {
        command("frown");
        command("say Why asking when you cannot afford it, "+
            ((TP->query_gender() == G_MALE) ? "mister" : "madam") + "?");
    }
    return 1;
}

public int
can_afford(int price)
{
    int *money_arr;
    if (sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1)
        return 0;
    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
    write("You pay "+coin_pay_text+" to Lobar.\n");
    if (coin_get_text)
        write("You get "+coin_get_text+" back.\n");
    return 1;
}

public int
remove_herb(int n)
{
    command("say Hmmpf. That was my last "+herbs[n*4]+".");
    command("say I guess I will have to go searching again.");
    herbs = exclude_array(herbs, n*4, n*4+3);
    return 1;
}


/* 
 * Function: unsellable 
 * Description: If the specified herb can't be sold, returns 1, 
 *              otherwise returns 0, after writing/saying the 
 *              appropriate messages to the specified seller. 
 */ 
private int 
unsellable(object herb, object seller) 
{
    /* NOTE: this function uses the global variable tmp, for speed, 
       as this function is called by do_sell_all()  */ 
    if (tmp = herb->query_prop(OBJ_M_NO_SELL)) { 
        if (stringp(tmp)) { 
            tell_object(seller, tmp); 
            return 1; 
        } 
        command("say No-one I know would be interested in buying " + 
            "that " + herb->short() + ", " + 
            ((seller->query_gender() == G_MALE) ? "sir" : "my lady")+"!"); 
        return 1; 
    } 
}


public int
do_sell_all(object player)
{
    object *herb, tp;
    int total_price,
        price,
        asked_for,
        hn,
        n;

    herb = filter(all_inventory(player), "herb_filter", TO);
    if (!sizeof(herb))
    {
        command("say But you have no herbs to sell!");
        command("shrug");
        return 1;
    }

    if (sizeof(herb) > MAX_SELL_ALL) { 
        herb = herb[0..(MAX_SELL_ALL-1)];  
        command("say That's too many herbs to sell at once!"); 
        command("say I will buy " + LANG_WNUM(MAX_SELL_ALL) + " now."); 
    } 

    tp = this_player(); 
    while (n < sizeof(herb))
    {
        if (unsellable(herb[n], tp)) { 
            n++; 
            continue; 
        } 
        if (herb[n]->query_herb_name() == player->query_prop(LOBAR_S_HERB))
        {
            asked_for = 1;
            TP->add_prop(LOBAR_S_HERB,LOBAR_S_HERB_SOLD);
        }
        if (herb[n]->do_id_check(TO))
            price = herb[n]->query_herb_value()/4;
        else
            price = herb[n]->query_herb_value()/2;
        if ((hn = member_array(herb[n]->query_herb_name(),herbs)) > -1)
        {
            if (herbs[hn+2] > MAX_HERBS)
                price /= 4;
        }
        command("say One "+herb[n]->query_herb_name()+" - "+price+
            " coppers.");
        total_price += price;
        if (asked_for)
        {
            command("say Thanks for bringing a "+
                herb[n]->query_herb_name()+" like I asked you to.");
            command("say I will now teach you, if you ask me to.");
            asked_for = 0;
        }
        add_herb(herb[n], 1);
        n++;
    }
    save_herbs(); 

    if (total_price < 1000) {
        command("say That wasn't much you had to sell."); 
        if (!total_price) 
            return 1; // all OBJ_M_NO_BUY.. 
    } 
    do_pay(player,total_price);
    return 1;
}


public int
my_sell(string str)
{
    int price,
        hn;
    int asked_for = 0;
    object  herb, 
           *obj;

    if (!CAN_SEE_IN_ROOM(TO))
    {
        command("say Sorry, it's too dark here.");
        command("say I can't see what you are trying to sell me.");
        return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
        command("say Uhmm, what kind of witchery is this? I can't see you?");
        return 1;
    }
    if (!strlen(str))
    {
        command("say What herb do you want to sell?");
        command("chuckle");
        return 1;
    }

    str = lower_case(str);
    if (str == "all")
    {
        command("say Sorry, but I'll only buy herbs.");
        return 1;
    }

    if (str == "all herbs")
    {
        do_sell_all(TP);
        return 1;
    }

    if (!sizeof(obj = FIND_STR_IN_ARR(str, all_inventory(TP))))
    {
        command("say What do you want to sell?");
        command("smile");
        return 1;
    } 
    if (!sizeof(obj = filter(obj, herb_filter)) || !objectp(herb = obj[0]))
    {
        command("say You have no herb of that kind, "+
            ((TP->query_gender() == G_MALE) ? "sir" : "my lady")+".");
        return 1;
    } 

    if (unsellable(herb, TP)) 
        return 1; 

    // added for training, Olorin
    if(TP->query_prop(LOBAR_S_HERB) == herb->query_herb_name())
    {
        asked_for = 1;
        TP->add_prop(LOBAR_S_HERB,LOBAR_S_HERB_SOLD);
    }
    if (herb->do_id_check(TO))
    {
        price = (herb->query_herb_value() * herb->num_heap()) / 4;
        switch(random(4))
        {
            case 0: 
                command("say I'm amazed, it is " +
                LANG_ADDART(herb->query_herb_name()) + "!");
                break;
            case 1:
                command("say Oh dear, if it isn't a genuine "+
                herb->query_herb_name()+"!");
                break;
            case 2: 
                command("say Hmm...oh yes! " + 
                capitalize(LANG_ADDART(herb->query_herb_name()))+"!");
                break;
            case 3:
                command("say Most interesting! " +
                capitalize(LANG_ADDART(herb->query_herb_name()))+"!");
                break;
        }
    }
    else 
    {
        command("gasp");
        command("say By the Flaming Sword of Pyros! This is unknown to me!");
        command("blush");
        command("say 66 years of gathering herbs, but yet another unknown " +
            herb->query_name()+"!");
        command("think");
        command("say I'll pay you " + (herb->query_herb_value() * herb->num_heap()) / 4 + " coppers "+
            "for this, "+
            ((TP->query_gender() == G_MALE) ? "sir" : "mylady") +"!");
        price = (herb->query_herb_value() * herb->num_heap()) / 4;
    }
    if((hn = member_array(herb->query_herb_name(),herbs)) > -1)
    {
        if(herbs[hn+2] > MAX_HERBS)
        {
            price = price/2;
            command("say I cannot give you the full price for the " +
                herb->query_herb_name() + ".");
            command("say I already have " + LANG_WNUM(herbs[hn+2]) + 
                " of the same.");
        }
    }
    do_pay(TP, price);
    add_herb(herb);
    if(asked_for)
    {
        command("say I will now teach you, if you ask me to.");
        asked_for = 0;
    }

    return 1;
}


public void
do_pay(object player, int price)
{
    object gc,
           sc,
           cc;
    int g,
        s,
        c;
    tell_room(environment(),"The herb-master counts some coins from a " +
        "pouch.\n");
    g = price/144;
    s = (price - g*144)/12;
    c = price - g*144 - s*12;
    cc = MONEY_MAKE_CC(c);
    if (g)
    {
        gc = MONEY_MAKE_GC(g);
        write("The herbalist gives you "+g+" gold coins.\n");
        gc->move(TP);
    }
    if (s)
    {
        sc = MONEY_MAKE_SC(s);
        write("The herbalist gives you "+s+" silver coins.\n");
        sc->move(TP);
    }
    if (c)
    {
        cc = MONEY_MAKE_CC(c);
        write("The herbalist gives you "+c+" copper coins.\n");
        cc->move(TP);
    }
    command("smile");
}

varargs public void
add_herb(object herb, int nosave)
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
            if (herbs[n*4+2] + herb->num_heap() < MAX_HERBS)
                herbs[n*4+2] += herb->num_heap();
            herb->remove_split_heap();
            // Reset the price in case it has changed.
            herbs[n*4+3] = herb->query_herb_value();
            if (!nosave)
            {
                save_herbs();
            }
            return;
        }
        n++;
    }
    command("say Excellent! I had run out of "
        + LANG_PWORD(herb->query_herb_name())+".");
    if (!pointerp(herbs))
        herbs += ({ });
    herbs += ({ herb->query_herb_name(), herb_file, herb->num_heap(),
        herb->query_herb_value() });
    herb->remove_split_heap();

    if (nosave)
         return;

    save_herbs();
}

/*
 * Function:    should_accept_item
 * Description: Returns whether the item should be accepted at this time.
 */
public int
should_accept_item(object obj, object from)
{
    if (from->query_prop(LOBAR_ACADEMIC_TASK_GIVEN)
        && ACADEMIC_MANAGER->query_herbs_collected(from) < 5
        && obj->query_herb_name() == "grey willow")
    {
        // Special exception for the herb task for Academics
        return 1;
    }

    if (get_alarm(accept_alarm) || get_alarm(identify_alarm))
    {
        // If we're in the process of accepting an item already,
        // we disallow this item. Lobar can only handle one herb
        // At a time.
        return 0;
    }
        
    if (given_herb)
    {
        // When given_herb is set, Lobar has already been given
        // an herb and needs time to identify it. Therefore, we
        // don't accept any more items.
        return 0;
    }

    return IS_HERB_OBJECT(obj);
}

/*
 * Function:    hook_process_accept_items
 * Description: Redefine this to process all the accepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_accept_items(mapping items)
{
    object * willows = ({ });
    foreach (object player, mapping objs : items)
    {
        foreach (object obj : m_indexes(objs))
        {   
            if (!objectp(obj))
            {
                send_debug_message("calia_lobar", "Given object no longer exists.");
                continue;
            }
            if (player->query_prop(LOBAR_ACADEMIC_TASK_GIVEN)
                && ACADEMIC_MANAGER->query_herbs_collected(player) < 5
                && obj->query_herb_name() == "grey willow")
            {
                willows += ({ obj });
                continue;
            }
            // If the item being accepted is not a grey-willow (for Academic quest), we
            // will attempt to identify it.
            identify_alarm = set_alarm(4.5, 0.0, &test_identify(({obj, player, objs[obj]})));    
        }
        if (sizeof(willows))
        {
            // Increment the number of herbs retrieved. This assumes
            // that herbs are heaped - hence use num_heap()
            int num_willows = SUM_ARRAY(map(willows, &->num_heap()));
            ACADEMIC_MANAGER->set_herbs_collected(player, 
                min(5, ACADEMIC_MANAGER->query_herbs_collected(player) + num_willows));
            command("say Ah, good. Good! You brought me grey willow "
                + "just like I asked.");
            report_task_2_progress(player);
            willows->remove_object();
            willows = ({ });
        }        
    }
}

/*
 * Function:    hook_process_unaccept_items
 * Description: Redefine this to process all the unaccepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_unaccept_items(mapping items)
{
    foreach (object player, mapping objs : items)
    {
        foreach (object obj : m_indexes(objs))
        {
            int size = objs[obj];
            if (!IS_HERB_OBJECT(obj))
            {
                set_alarm(0.5, 0.0, &not_herb(({obj, player, size})));
                continue;
            }
            else
            {
                set_alarm(0.5, 0.0, &give_back_immediately(({obj, player, size})));
                continue;
            }                
        }
    }
}

public void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);
    receive_enter_inv(herb, from);
}

public string
close_open()
{
    if(closed)
    {
        closed = 0;
        return " *** Lobar is now ready to teach! *** \n";
    }
    closed = 1;
    return " *** Lobar will not teach anymore now! *** \n";
}

public int
query_closed()
{
    return closed;
}

public void
not_herb(mixed hf)
{
    command("say I do not care for anything but herbs!");
    switch(random(4)) 
    {
        case 0: 
            command("say Why should I care about a silly "+
                hf[0]->query_name()+"?");
            break;
        case 1:
            command("say I am too busy to be disturbed with " +
                LANG_PWORD(hf[0]->query_name())+", "+
                hf[1]->query_race_name()+".");
            break;
        case 2:
            command("say I am a herbalist, "+hf[1]->query_race_name()+
                ", not a stupid pawnshop owner!");
            break;
        case 3: 
            command("say This is of no interest to me, "+
                ((TP->query_gender() == G_MALE) ? "mister" : "madam")+".");
            break;
    }
    give_back_helper(hf[0], hf[1], hf[2]);
}

public void
give_back_immediately(mixed hf)
{
    command("say Please wait till I am finished with this other herb, "+
        ((hf[1]->query_gender() == G_MALE) ? "sir" : "mylady")+".");
    give_back_helper(hf[0], hf[1], hf[2]);
}

public int
test_identify(mixed h_arr)
{
    object player;
    string id_str,
           find_str;
    given_herb = h_arr[0];
    player = h_arr[1];
    int size = h_arr[2];
    tell_room("The herbalist looks closely at the "+
        given_herb->query_name()+".\n");
    command("think");

    switch(given_herb->query_id_diff()/10)
    {
        case 0:
            command("laugh");
            id_str = "Even the children can recognize this one.";
            break;
        case 1: 
            command("giggle");
            id_str = "Hmm...one of the easiest recognizable herbs.";
            break;
        case 2: 
            command("giggle");
            id_str = "Ahh..a nice one. Some people often mistake this " +
                "for another.";
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
            id_str = "Exciting! This one is hard to tell from the " +
                "Crimbul herb.";
            break;
        case 6: 
            command("think");
            id_str = "My dear friend - you need to be quite skilled to " +
                "identify this one.";
            break;
        case 7:
            command("think");
            id_str = "Oh! Can it really be...? Ah...yes it is.";
            break;
        case 8:
            command("gasp");
            id_str = "By the Cold Stone of Gu!! This is one of the " +
                "most difficult herbs!";
            break;
        case 9:
            command("gasp");
            id_str = "Oh dear. Not even I am sure about this....but.." +
                "it must be.";
            break;
        case 10:
            command("confused");
            id_str = "Impossible! Absolutely impossible! It just can't " +
                "be...?!";
    }
    command("say "+id_str);
    switch(given_herb->query_find_diff())
    {
        case 0:
            command("laugh");
            find_str = "Ah..this is as normal as ordinary grass.";
            break;
        case 1:
            command("giggle");
            find_str = "This one is quite a usual sight.";
            break;
        case 2:
            command("giggle");
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
            find_str = "Ah! I guess you spent some time looking for " +
                "this one!";
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
            find_str = "I am absolutely astonished! This is extremely rare!";
            break;
        case 9:
            command("gasp");
            find_str = "How can this be?? I have only seen this herb " +
                "about twice in my life!";
            break;
        case 10:
            command("confused");
            find_str = "I cannot believe it! You have actually found it! " +
                "I have only read about this in old books of herblore!";
    }
    command("say "+break_string(find_str,75));
    if (given_herb->do_id_check(TO))
        command("say "+given_herb->query_id_long());
    else
        command("say It is unknown to me what the effect of this "+
            given_herb->query_name()+" is.");
    give_back_helper(given_herb, player, size);
    command("say I hope my information has been useful, "+
        ((player->query_gender()==G_MALE) ? "sir" : "mylady")+".");
    command("bow");
    given_herb = 0;
    return 1;
}

public void
intro_me(string who)
{
    if (!who || !strlen(who) || !find_living(who) ||
        !present(who, environment()))
        command("hail");
    else
        command("hail " + who);
    command("say My name is Lobar. I'm the herb-master of Calia. ");
    command("present me");
}

public void
add_introduced(string who)
{
    set_alarm(3.0, 0.0, &intro_me(who));
}

public void
emote_hook(string emote, object actor, string adverb=0)
{
    switch (emote)
    {
        case "bow":
        case "greet":
            if (actor)
            {
                command("bow " + OB_NAME(actor));
                command("say What can I do for you, " + 
                    actor->query_name() + "?");
                command("say If you have an unknown herb, " +
                    actor->query_name() + ", you can let me identify it " +
                    "for you.");
            }
            else
                command("bow");
            break;   
    }
}

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
}

public string
ask_lore()
{
    command("say Herb lore?");
    command("say Well, there are only few who know as much about herbs " +
        "as I do!");
    command("say But even I do not know all the places where herbs grow!");
    return "";
}

public string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}

public void
set_up_skills()
{
    string  me = "to recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM, ({me, me}), 0, 0, 20);
}

public int
remove_herb_from_list(string herb)
{
    int n, s;

    n = 0;
    s = sizeof(herbs);

    while(n < (s/4))
    {
        if (herb == herbs[n*4] || herb == LANG_PWORD(herbs[n*4]))
        {
            if(n == 0)
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

public void
report_task_2_progress(object player)
{
    int herbs_needed;

    herbs_needed = max(0, 5 - ACADEMIC_MANAGER->query_herbs_collected(player));
    
    if (herbs_needed == 0)
    {
        command("say By the Elementals, that was all of them! Let me tell "
            + "you; herbs can save your life, or, if misused, may take it.");
        command("say Be sure to carry many with you, in particular those "
            + "like grey willow that when chewed, will restore your mana!");
        command("say Be mindful though of what herb you use and when. You can "
            + "only eat one every 60 seconds. Herbs can also be rather "
            + "valuable.");
        command("say Come to me and sell your herbs, or if you find some you "
            + "do not know, I may identify it for you!");
        command("say Here, take this note and give it to Amjal. He'll be "
            + "happy to see that you completed your task.");
        object note = clone_object("/d/Calia/guilds/academics/objs/task_2_note");
        note->set_owner_name(player->query_real_name());
        note->move(player, 1);
        player->catch_msg(QCTNAME(this_object()) + " gives you a sealed "
            + "approval note.\n");
        tell_room(environment(player), QCTNAME(this_object()) + " gives "
            + QTNAME(player) + " a sealed approval note.\n", ({ player }));
    }
    else
    {
        command("say You need " + herbs_needed + " more grey willows to "
            + "complete your task.");
    }
}

public string
reply_academic()
{
    object player = this_player();
    // Academics who are working on their second task should get a proper
    // respons. Everyone else should get the default response
    if (ACADEMIC_MANAGER->query_completed_task_2(player))
    {
        command("say I certainly hope you learned a lot from Amjal since. You "
            + "did a mighty fine job with the task that I gave you.");
        return 0;
    }
    else if (!IS_ACADEMIC(player)
             || !ACADEMIC_MANAGER->query_completed_task_1(player)
             || !player->query_prop(TASK_TWO_GIVEN))
    {
        return default_answer();
    }
    
    if (!player->query_prop(LOBAR_ACADEMIC_TASK_GIVEN))
    {
        command("say Oh.. one of them of Xania's students are you, eh? Bet Amjal "
            + "sent you here for a task on herbs, by Gu!");
        command("say Well, the task I have for you is pretty simple.");
        command("say Go to the moors and fetch me five grey willows. You can find "
            + "them by conducting a search in a room where herbs can be found.");
        command("say If you see a grey bark in the moors, then it is most "
            + "likely grey willow. Bring it to me to be sure!");
        command("say When you're in a room, you can always <search here for herbs>.");
        command("say As you become more skilled, you can <search here for "
            + "grey willow> to look for grey willow specifically.");
        command("say Good luck!");
        player->add_prop(LOBAR_ACADEMIC_TASK_GIVEN, time());
    }
    else if (present("academic_lobar_approval_note", player))
    {
        command("say You've already completed your task! Go give your note to "
            + "Amjal.");
    }
    else
    {
        report_task_2_progress(player);
    }
    
    return 0;
}

/*
 * Function:    reset_herb_prices
 * Description: Due to a bug, the herb prices may be incorrect. This
 *              function can be called to reset everything in the herb
 *              file.
 */
public void
reset_herb_prices()
{
    int num_herbs = sizeof(herbs) / 4;
    for (int index = 0; index < num_herbs; ++index)
    {
        object current_herb = safely_load_master_file(herbs[index * 4 + 1]);
        if (!objectp(current_herb))
        {
            write("Could not clone " + herbs[index * 4] + "\n");
            continue;
        }
        write("Setting value of " + herbs[index * 4] + " to " + current_herb->query_herb_value() + " cc.\n");
        herbs[index * 4 + 3] = current_herb->query_herb_value();
    }
    save_herbs();
}
