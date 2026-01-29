//-*-C++-*-
// file name:    /d/Avenir/common/outpost/mon/food_merch.c
// creator(s):   Lilith, May 1997 
// revised:      Lilith, Aug 1999: added spy functionality
// purpose:      To sell food in the Outpost
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/spy_npc";
inherit "/lib/trade";

#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/relation.h"

                  /*  C   F   J   N   S */ 
#define MY_PRICES ({ 210, 10, 45, 75, 350})
#define NUM sizeof(MONEY_TYPES)
#define DARK_OBJ      "/d/Avenir/common/dark/obj/"



string pay_type, get_type, coin_pay_text, coin_get_text;
int *money_arr;
int counter, i;

string
my_long()
{
    string  str;

    str = "A fellow with luxuriant whiskers and observant eyes, he "+
        "is busy and enterprising like most of the gnomes of "+
        "Sybarus.\nHe seems to be engaged in the business "+
        "of selling food.\n";

    if (IS_SYBARITE(TP))
    {
        str += "He might be inclined to tell you what he has seen "+
               "today.\n";
    }
    return str;
}

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("riglor");
    set_title("ini Du'wal");
    set_race_name("gnome");
    set_adj("busy");

    set_long(my_long);
   
    set_gender(G_MALE);
    set_stats(({ 50, 90, 45, 65, 70, 60 }));

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
   
    set_skill(SS_UNARM_COMBAT,  44);
    set_skill(SS_AWARENESS,     80);

    set_alignment(0);
    set_default_answer(VBFC_ME("what_me"));
     add_ask(({"what has occurred", "what has occured", 
         "what have you seen"}), VBFC_ME("ask_about_encountered"), 1);
     add_spy_ask();
     spy_auto_intro();

 
    set_act_time(5);
     add_act("groan");
     add_act("shout Food supplies! Get your food supplies!");
     add_act("say I've got food for your trek into the Utterdark.");
     add_act("say You will find my prices for food are reasonable.");
     add_act("yawn");
    set_cact_time(3);
     add_cact("shout Help! I'm under attack!");
     add_cact("say You would bite the hand that feeds you, eh?");
     add_cact("sniff");
     add_cact("sob");

    add_prop(CONT_I_HEIGHT, 190);
    seteuid(getuid());
} 

string
what_me()
{
    switch(random(6))
    {
        case 0:
            command("say I am not permitted to answer that question.");
            break;
        case 1:
            command("say I don't know. I stick to what I know do know:"+
                " selling food.");
            break;
        case 2:
            command("emote struggles to answer, but does not seem able "+
                "to get the words out.");
            break;
        case 3:
            command("say Would that I could, but I cannot say.");
            break;
        case 4:
            command("emote raises his eyebrows and blinks several "+
                "times in a row.");
            break;
        case 5:
            command("say Oddly enough, I don't know anything about that.");
            break;
    }
    return "";    
}

string race_sound()
{
   string *strs = ({ "speaks", "says", "whispers", "crackles" });

   return strs[random(sizeof(strs))];
}

/* Shop function redefinitions */
string price_list()
{
    return (
        "I have the following for sale:\n"+  
        "     Round of Cheese  "+ MY_PRICES[0] +" coppers\n" +
        "     Dried Fruit      "+ MY_PRICES[1] +" coppers\n" +
        "     Jerky Strips     "+ MY_PRICES[2] +" coppers\n" +
        "     Packet of Nuts   "+ MY_PRICES[3] +" coppers\n" +
        "     Hard Sausage     "+ MY_PRICES[4] +" coppers\n" +
        " \n");
}
  
int
list_me(string str)
{
    if (str)
        return 0;
 
    write(price_list());
       return 1;
}

/* Test if this_player has more money on him than the price */
int
can_afford( int price, string ware )
{
    if (sizeof(money_arr = pay(price, this_player(),pay_type,0,0,get_type)) == 1)
    {
        if (money_arr[0] == 2)
        {
            tell_room( environment(this_object()),
                "The gnome states: You've got no "+pay_type+ " coins!\n");
            return 0;
        }
        if (money_arr[0] == 1)
        {
            tell_room( environment(this_object()),
                "The gnome states: You haven't got enough "+pay_type+
                " coins to buy "+ware+"!\n");
            return 0;
        }
        else
        {
            tell_room( environment(this_object()),
                "The gnome states: When you've got enough money, then I'll "+
                "sell you a "+ware+".\n");
            return 0;
        }
    }
    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
    write("You order a "+ware+" and pay "+coin_pay_text+".\n");
    if (coin_get_text)
        write("The gnome gives you "+coin_get_text+" back in change.\n");
    return 1;
  
} // can_afford()

int
do_buy(string str) 
{
    object item, curse;
    string item_name;
    if (!str || str == "")
        return 0;

    if (curse = present(WRATHNAME, this_player()))
    {
        command("say You're accursed by Plalgus and I'll have none of you!");
        command("back "+ this_player()->query_real_name());
        return 1;
    }

    if (sscanf(str,"%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
        if (sscanf(str,"%s for %s",item_name,pay_type) != 2)
        {
            pay_type = "";
            item_name = str;
        }
    }
    if (str == "cheese" || str == "round" || str == "round of cheese")
    {
        if (can_afford(MY_PRICES[0],"round of cheese"))
        {
            item = clone_object(DARK_OBJ + "cheese");
            if (item->move(this_player()))
            {
                write("You cannot carry that much!\n");
                return 1;
            }
            say(QCTNAME(this_player())+" buys a round of cheese.\n");
        }
        return 1;
    }
    if (str == "dried fruit" || str == "fruit")
    {
        if (can_afford(MY_PRICES[1],"dried fruit"))
        {
            item = clone_object(DARK_OBJ + "dfruit");
            if (item->move(this_player()))
            {
                write("You cannot carry that much!\n");
                return 1;
            }
            say(QCTNAME(this_player())+" buys some dried fruit.\n");
        }
        return 1;
    }
    if (str == "jerky" || str == "jerky strips")
    {
        if (can_afford(MY_PRICES[2],"strip of jerky"))
        {
            item = clone_object(DARK_OBJ + "jerky");
            if (item->move(this_player()))
            {
                write("You cannot carry that much!\n");
                return 1;
            }
            say(QCTNAME(this_player())+" buys some jerky strips.\n");
        }
        return 1;
    }
    if (str == "nuts" || str == "packet" || str == "packet of nuts")
    {
        if (can_afford(MY_PRICES[3],"packet of nuts"))
        {
            item = clone_object(DARK_OBJ + "dnuts");
            if (item->move(this_player()))
            {
                write("You cannot carry that much!\n");
                return 1;
            }
            say(QCTNAME(this_player())+" buys a packet of nuts.\n");
        }
        return 1;
    }
    if (str == "sausage" || str == "hard sausage")
    {
        if (can_afford(MY_PRICES[4],"sausage"))
        {
            item = clone_object(DARK_OBJ + "sausage");
            if (item->move(this_player()))
            {
                write("You cannot carry that much!\n");
                return 1;
            }
            say(QCTNAME(this_player())+" buys a hard sausage.\n");
        }
        return 1;
    }

    notify_fail("The gnome states: I don't have any of that.\n");
    return 0;
}

void
check_meet(object tp)
{
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    if (random(3))
    {
        if (IS_SYBARITE(tp))
        {
            command("bow deeply "+ tp->query_real_name());
            command("say to "+ tp->query_real_name() +" Celebrate "+
                "the Source.\n");
            return;
        }
        command("emote looks suspicious.");
        return;
    }
}

void init_living()
{
    ::init_living();

    add_action(list_me,     "list");
    add_action(do_buy,      "buy");
    add_action(do_buy,      "order" );
}  
