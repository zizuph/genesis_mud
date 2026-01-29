/*
 * Borrowed from Elessar's Herbalist
 * By Elessar, July 17th 1992.
 * added training of herbalism, Olorin, Sep 1993
 * The teaching routines were added following an example by Mortricia.
 * A Krynnish herbalist by Teth, October 21, 1996
 *
 * Modified from Remington Colton (Herbalist in Darken Wood) 
 * for the Elven Archers guild by Blizzard, 12.11.2003.
 */

inherit "/lib/trade";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Krynn/common/defs.h"

inherit   M_FILE
#include  <money.h>
#include  <stdproperties.h>
#include  <language.h>
#include  <ss_types.h>
#include  <std.h>
#include  <macros.h>
#include  <cmdparse.h>


#define HERBAL_SAVE   "/d/Ansalon/guild/archers/npc/save/herbalist_herbs"
#define NUM           sizeof(MONEY_TYPES)
#define MAX_SELL_ALL  40
#define MAX_HERBS     500

static string         pay_type, get_type, coin_pay_text, 
                      coin_get_text, *sold_arr, log_str, book_str, name;
static object         given_herb;

mixed                 *herbs;

public string         long_description();
public int            my_buy(string str);
public int            my_sell(string str);
public int            do_buy(int n);
public int            do_pay(object player, int price);
public int            can_afford(int price);
public int            remove_herb(int n);
varargs public void   add_herb(object herb, int nosave);


public void
restore_herbs()
{
   seteuid(getuid(TO));
   restore_object(HERBAL_SAVE);
}

void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;
   
    set_name("Nolineal");
    add_name("herbalist");
    set_race_name("elf");
    set_living_name("nolineal");
    set_title("Soreande, the Elven Herbalist");
    set_adj("silver-eyed");
    add_adj("long-haired");
    set_long(long_description);
    set_gender(G_FEMALE);
    set_stats(({ 130, 165, 155, 140, 140, 130 }));
    set_introduce(1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_LOOKS, 1);

    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 175);
    add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   
    set_skill(SS_HERBALISM, 95);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_DEFENCE, 80);

    set_alignment(500);
    set_knight_prestige(-250);
   
    set_act_time(5);
    add_act("@@announce_selling");
 
    set_cact_time(2);
    add_cact("say You think that herbalist can't fight?");
    add_cact("shout Help! I'm being attacked!");
    add_cact("say I hope you choke on spinach.");
   
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
    add_ask(({"herbalism","lesson","lessons","train","training"}),
        "say Why don't you try to learn or improve? You might get lucky.",1);

    config_default_trade();
    set_money_give_out(({ 10000,   700,  10,  10 }));
    set_money_give_reduce(({  0,     0,   0,   0 }));

  //    equip(({ KRARMOUR + "herb_gloves" });
    
    set_alarm(2.0, 0.0, restore_herbs);
}

public void
init_living()
{
    ::init_living();

    add_action(my_buy, "buy");
    add_action(my_sell, "sell");
}

public void
announce_selling()
{
    if ( herbs ) 
        command("say I have herbs for sale, for a pretty copper.");
    else 
        command("say I should go and search for more herbs.");
}

public string
long_description()
{
    string long_str;

    long_str = "Perhaps she knows a great deal about herbs and plants. " +
        "If you give her a herb, she may identify it for you. She might " +
        "also have some herbs to sell, and would also most likely buy " +
        "herbs from you!\n";

    if ( TP->query_wiz_level() )
        return (long_str + " Type 'stat herbalist' for " +
            "more info.\n");
 
    return break_string(long_str + "\n", 75);
}

wizinfo()
{
    int n;
    string str;
   
    if ( !herbs ) 
        return "The herbalist has no herbs for sale now.\n";
 
    str = "The herbalist has these herbs for sale:\n";

    while ( n < (sizeof(herbs) / 4) )
    {
        str = str + herbs[n * 4] + ": File " + herbs[n * 4 + 1] + 
            " - " + herbs[n * 4 + 2] + " for sale, " + herbs[n * 4 + 3] + 
            " cc each.\n";
        n++;
    }
  
    return str;
}

public int
my_buy(string str)
{
    int n;
   
    seteuid(getuid(TO));
    str = lower_case(str);
   
    if ( !CAN_SEE(TO, TP) )
    {
        command("say Why are you hiding? I can't see you!");
        return 1;
    }
    
    if ( !CAN_SEE_IN_ROOM(TO) )
    {
        command("say Uhmm, who's there? I can't see you! Light a torch " +
            "if we are to do business here!");
        return 1;
    }
   
    if ( str == "herbs" || str == "herb" || !str ) 
    {
        if ( !herbs ) 
        {
            command("say I'm sorry, I have no herbs for sale right now.\n");
            command("frown");
            
            return 1;
        }
        
        command("say Currently I have these herbs:\n");
  
        while ( n < (sizeof(herbs) / 4) ) 
        {
             write("  " + herbs[n * 4 + 2] + " " + LANG_PWORD(herbs[n * 4]) + 
                 " for " + herbs[n * 4 + 3] + " coppers each.\n");
             n++;
        }
        
         write("That is all I have.\n");
         command("smile " + TP->query_real_name());
        
         return 1;
    }
 
   /* In case the player wanted to actually buy one of the herbs */
    n = 0;

    say(QCTNAME(TP) + " asks the herbalist for a " + LANG_ADDART(str) + 
        ".\n",TP);
    write("The herbalist starts looking through his herb-storage.\n");
    say("The herbalist starts looking through his herb-storage.\n");
   
    while ( n < (sizeof(herbs) / 4) ) 
    {
        if (str == herbs[n * 4] || str == LANG_PWORD(herbs[n * 4])) 
        {
            do_buy(n);
            return 1;
        }
        
        n++;
    }

    command("say I apologize you, my friend, but I have no " + 
        LANG_PWORD(str) + ".\n");
    command("sigh");

    return 1;

}

public int
do_buy(int n)
{
    object herb;

    if ( can_afford(herbs[n * 4 + 3]) ) 
    {
        if ( !(herb = clone_object(herbs[n * 4 + 1])) ) 
        {
            command("say Hmm....it seems to have decayed...I'm sorry.");
            command("sigh");

            return 1;
        }

        herb->move(TO, 1);
        tell_room(E(TO), "The herbalist picks up a herb from a little pouch.\n");
        command("say I hope it will be useful, my friend!");
        command("give " + OB_NAME(herb) + " to " + TP->query_real_name());

        if ( E(herb) == TO )
        {
            command("eeks");
            command("say I will just put it here then.");
            command("emote puts the herb on the ground.");
            herb->move(E(TO));
          
        }
      
        herbs[n * 4 + 2] -= 1;
      
        if (herbs[n * 4 + 2] <= 0) 
            remove_herb(n);
      
        save_object(HERBAL_SAVE);
    }
    else 
    {
        command("say It seems you can't afford it.\n");
        command("smile slightly");
    }

    return 1;
}

public int
can_afford(int price)
{
    int  *money_arr;
   
    if ( sizeof(money_arr = pay(price, TP, 0, 0, 0, get_type)) == 1 )
        return 0;
    
    coin_pay_text = text(exclude_array(money_arr, NUM, NUM * 2 - 1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM - 1));
 
    write("You pay " + coin_pay_text + " to Nolineal.\n");
  
    if (coin_get_text)
        write("You get " + coin_get_text + " back.\n");

    return 1;
}

public int
remove_herb(int n)
{
    command("say Oh, that was my last " + herbs[n * 4] + ".");
    command("say I guess I will have to go searching again.");

    herbs = exclude_array(herbs, n * 4, n * 4 + 3);
   
    return 1;
}

public int
herb_filter(object ob)
{
    if ( !function_exists("create_herb", ob) )
        return 0;
    
    if ( !ob->query_herb_name() || !ob->query_herb_value() )
        return 0;
    
    return 1;
}

public int
do_sell_all(object player)
{
    object *herb;
    int    total_price, price, hn, n;
    
    herb = filter(all_inventory(player), "herb_filter", TO);
    
    if ( !sizeof(herb) )
    {
        command("say But you have no herbs to sell!");
            
        return 1;
    }
    
    if ( sizeof(herb) > MAX_SELL_ALL )
    {
        herb = herb[0..(MAX_SELL_ALL - 1)];
        command("say So many herbs?");
        command("say I can buy " + LANG_WNUM(MAX_SELL_ALL) + " at once.");
    }
    
    while ( n < sizeof(herb) )
    {
        if ( herb[n]->do_id_check(TO) )
            price = herb[n]->query_herb_value() / 4;
        else
            price = herb[n]->query_herb_value() / 2;
        
        if ( (hn = member_array(herb[n]->query_herb_name(), herbs)) > -1 )
        {
            if ( herbs[hn + 2] > MAX_HERBS )
                price /= 4;
        }
        
        command("say One " + herb[n]->query_herb_name() + " - " + price +
            " coppers.");
        total_price += price;
        
        add_herb(herb[n], 1);
        n++;
    }
    
    save_object(HERBAL_SAVE);    
    
    if ( total_price < 1000 )
        command("say That was not much you had to sell.");
    
    do_pay(player, total_price);
    
    return 1;            
}

public int
my_sell(string str)
{
    object herb, *obj;
    int    price, hn;
   
    if ( !CAN_SEE_IN_ROOM(TO) )
    {
        command("say I'm sorry, but I can not see what you are trying " +
            "to sell me.");
        return 1; 
    }
   
    if ( !CAN_SEE(TO, TP) )
    {
        command("say I can't see you!");
        return 1;
    }
        
    if ( !strlen(str) )
    {
        command("say What herb do you want to sell?");
        command("think");
        return 1;
    }

    str = lower_case(str);
    
    if ( str == "all" )
    {
        command("say Sorry, I can buy only herbs. Do you want to " +
             "sell all your herbs?");
        return 1;
    }
    
    if ( str == "all herbs" )
    {
        do_sell_all(TP);
        return 1;
    }
    
    if ( !sizeof(obj = FIND_STR_IN_ARR(str, all_inventory(TP))) )
    {
        command("say What do you want to sell?");
        return 1;
    }
        
    if ( !sizeof(obj = filter(obj, herb_filter)) || !objectp(herb = obj[0]) )
    {
        command("say You have no herb of that kind, friend.\n");
        return 1;
    }
    
    if ( herb->do_id_check(TO) ) 
    {
        price = herb->query_herb_value() / 2;
        
        switch( random(4) ) 
        {
        case 0: 
            command("say Indeed, " + 
                LANG_ADDART(herb->query_herb_name()) + "!"); 
        break;
        case 1: 
            command("say I'm surprised that you of all people managed " +
                "to find " + herb->query_herb_name() + "!"); 
        break;
        case 2: 
            command("say Hmm...oh yes! " + 
                capitalize(LANG_ADDART(herb->query_herb_name())) + "!"); 
        break;
        case 3: 
            command("say Most interesting! " +
                capitalize(LANG_ADDART(herb->query_herb_name())) + "!"); 
        break;
        }
    }
    else 
    {
        command("gasp");
        command("say By Chislev! This is unknown to me!");
        command("blush");
        command("say 40 years of gathering herbs, but yet another unknown " +
            herb->query_name() + "!");
        command("think");
        command("say I'll pay you " + herb->query_herb_value() + 
            " coppers for this, friend.");
        price = herb->query_herb_value();
    }
    if ( (hn = member_array(herb->query_herb_name(), herbs)) > -1 )
    {
        if( herbs[hn + 2] > MAX_HERBS)
        {
            price = price / 2;
            command("say I cannot give you the full price for the " +
                herb->query_herb_name() + ".");
            command("say I already have " + LANG_WNUM(herbs[hn + 2]) + 
                " of the same.");
        }
    }
    
    do_pay(TP, price);
    add_herb(herb);

    return 1;
}

public int
do_pay(object player, int price)
{
    object  gc, sc, cc;
    int     g, s, c;
   
    tell_room(E(TO),"The herb-master counts some coins from a pouch.\n");

    g = price / 144;
    s = (price - g * 144) / 12;
    c = price - g * 144 - s * 12;
    cc = MONEY_MAKE_CC(c);
   
    if (g) 
    {
        gc = MONEY_MAKE_GC(g);
        write("The herbalist gives you " + g + " gold coins.\n");
        gc->move(TP);
    }
    
    if (s) 
    {
        sc = MONEY_MAKE_SC(s);
        write("The herbalist gives you " + s + " silver coins.\n");
        sc->move(TP);
    }
    
    if (c) 
    {
        cc = MONEY_MAKE_CC(c);
        write("The herbalist gives you " + c + " copper coins.\n");
        cc->move(TP);
    }
 
    command("smile");
    return 1;
}

varargs public void
add_herb(object herb, int nosave)
{
    string herb_file, trash;
    int    n;
    
    seteuid(getuid(TO));

    if ( !objectp(herb) )
        return;
    
    herb_file = MASTER_OB(herb);
    
    while ( n < (sizeof(herbs) / 4) ) 
    {
        if ( herbs[n * 4 + 1] == herb_file ) 
        {
            if( herbs[n * 4 + 2] < MAX_HERBS ) 
                herbs[n * 4 + 2] += 1;
   
            herb->remove_object();
            return;
        }
        
        n++;
    }
 
    command("say Excellent! I had run out of " + 
        LANG_PWORD(herb->query_herb_name()) + ".");

    if ( !herbs ) 
        herbs = ({ herb->query_herb_name(), herb_file, 1, 
            herb->query_herb_value() });

    herbs += ({ herb->query_herb_name(), herb_file, 1, 
        herb->query_herb_value() });

    herb->remove_object();
    
    if ( nosave )
        return;
        
    save_object(HERBAL_SAVE);

    return;
}

public void
not_herb(mixed hf)
{
    command("say I do not care for anything but herbs!");
  
    switch(random(4)) 
    {
    case 0: 
        command("say Why should I care about a silly "+
            hf[0]->query_name() + "?"); 
    break;
    case 1: 
        command("say I am too busy to be disturbed with " +
            LANG_PWORD(hf[0]->query_name()) + ", " + 
            hf[1]->query_race_name() + "."); 
    break;
    case 2: 
        command("say I am a herbalist, " + hf[1]->query_race_name() +
            ", not a stupid pawnshop owner!"); 
    break;
    case 3: 
        command("say This is of no interest to me, friend.");
    break;
    }
 
    command("give " + OB_NAME(hf[0]) + " to " + hf[1]->query_real_name());
}

public void
give_back_immediately(mixed hf)
{
    command("say Please wait till I am finished with this other herb, " +
        "my friend.\n");
    command("give " + OB_NAME(hf[0]) + " to " + hf[1]->query_real_name());
}

public int
test_identify(mixed h_arr)
{
    object     player;
    string     id_str, find_str;
   
    given_herb = h_arr[0];
    player     = h_arr[1];
   
    tell_room("The herbalist looks closely at the " + 
        OB_NAME(given_herb) + ".\n");
    command("think");
 
    switch( given_herb->query_id_diff() / 10 ) 
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
            id_str = "I'm not surprised you couldn't get this one.";
        break;
        case 3: 
            command("frown");
            id_str = "I've seen this one a lot. Why couldn't you " +
                "figure it out?";
        break;
        case 4: 
            command("smile");
            id_str = "Ah - I can't blame you for not recognizing this one.";
        break;
        case 5: 
            command("smile");
            id_str = "Exciting! This one is hard to tell from some others.";
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
            id_str = "By Chislev!! This is one of the most difficult herbs!";
        break;
        case 9: 
            command("gasp");
            id_str = "Oh dear. Not even I am sure about this....but.." +
                "it must be.";
        break;
        case 10: 
            command("boggle");
            id_str = "Impossible! Absolutely impossible! " +
                "It just can't be...?!";
    }
  
    command("say " + id_str);
   
    switch( given_herb->query_find_diff() ) 
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
            find_str = "Interesting. Not everybody knows where to " +
                "find this one.";
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
            find_str = "I am absolutely astonished! This is extremely rare!";
        break;
        case 9: 
            command("gasp");
            find_str = "How can this be?? I have only seen this herb " +
                "about twice in my life!";
        break;
        case 10: 
            command("boggle");
            find_str = "I cannot believe it! You have actually found it! " +
                "I have only read about this in old books of herblore!";
    }
  
    command("say " + break_string(find_str, 75));

    if ( given_herb->do_id_check(TO) )
    {
        command("say This is what I can tell you about it: ");
        write(given_herb->query_id_long());
    }
    else 
        command("say It is unknown to me what the effect of this " + 
            OB_NAME(given_herb) + " is.");

    command("give " + OB_NAME(given_herb) + " to " + player->query_real_name());
    command("say I hope you found my information useful, my friend."); 
    command("bow");
    given_herb = 0;
  
    return 1;
}

string
ask_herbs()
{
   command("say Herbs?");
   command("say Well, I know most of them! And you probably don't!");
   command("cackle egocentrically");
   command("say Well, I'll buy them off you, or sell you some if you want.");
   command("say If you have an unknown herb, I may identify");
   command("say it for you, if you give it to me.");
   return "";
}

string
default_answer()
{
   command("say I don't know what you are talking about! Clarity!");
   return "";
}

public int
remove_herb_from_list(string herb)
{
    int n, s;
   
    n = 0;
    s = sizeof(herbs);
   
    while( n < s / 4 )
    {
        if ( herb == herbs[n * 4] || herb == LANG_PWORD(herbs[n * 4]) )
        {
            if(n == 0)
                herbs = herbs[4..s-1];
            else if(n == (s / 4 - 1) )
                herbs = herbs[0..s-5];
            else 
                herbs = herbs[0..n*4-1] + herbs[(n + 1) * 4..s-1];
            return 1;
        }
      
        n++;
    }
 
    return 0;
}

public void
enter_inv(object herb, object from)
{
    int ran;

    ::enter_inv(herb, from);

    if ( !from ) 
        return;
   
    if ( !function_exists("create_herb", herb) ) 
    {
        set_alarm(1.0, 0.0, &not_herb( ({ herb, from }) ));
        return;
    }
   
    if ( given_herb ) 
    {
        set_alarm(1.0, 0.0, &give_back_immediately( ({ herb, from }) ));
        return;
    }
   
    set_alarm(5.0, 0.0, &test_identify( ({ herb, from }) ));

    return;
}

