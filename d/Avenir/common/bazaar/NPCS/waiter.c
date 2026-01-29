// Waiter       (/d/Avenir/common/bazaar/NPC/waiter.c)
// creator(s):    Glinda
// last update:   Boriska, runtime errors in add_asks and buying of the
//                inn_key fixed.
//                Denis, Mar'01: Runtime error when trying to buy non-existant
//                               stuff fixed.
//                Lucius, Jan 2005: Waiter was not giving the inn key
//                  to the players, this is needed since players may
//                  no longer start in the bazaar and the startrooms
//                  were moved here.
//                  Gorboth, Oct 2014: Changed race "waiter"->"human"
//		  Cotillion, Oct 2014: Fixed Gorboths comment
// purpose:       Figured a slow waiter might add soem color
// note:
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/monster.c";
inherit "/lib/trade";

#include <language.h>
#include <macros.h>
#include <money.h>
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Avenir/common/common.h"

#define STAND_DIR "/d/Avenir/common/bazaar/Obj/food/"
#define NUM sizeof(MONEY_TYPES)

string pay_type, get_type, coin_pay_text, coin_get_text;
int *money_arr;
int test;

public void
create_monster(void)
{
   set_name("waiter");
   set_race_name("human");
   set_adj(({"arthritic", "old"}));
   set_long("This old human has worked hard all his life for a kind "+
       "but demanding master.  He is new to the job of being a waiter, "+
       "but takes great pride in his efforts and is most eager to "+
       "please.\nIf you want to know what is on today's menu, just "+
       "ask him and he will be happy to tell you.\n");

    default_config_npc(42);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_DEFENCE,40);
    set_skill(SS_AWARENESS,20);
    set_scar(random(20));
    set_alignment(0);
    set_pick_up(1);

    add_prop("_live_m_attack_thief", "thief_fun");

    add_act("emote rubs the small of his back.");
    add_act("emote looks with disgust at a weird stranger sitting at a table.");
    add_act("say The Shadow-elves of Sybarus will see that the " +
	    "Gods are appeased.");
    add_act("say What can I do for you?");
    add_act("say I'm not a very good waiter, but I'm not an insolent "+
       "young fool like the other fellow.");
    add_act("say Outlanders are odd, but seem nice all the same.");
    add_act("emote eyes you curiously.");
    add_act("emote tries to move out of your way.");
    add_act("emote gets a stone trencher from a table and wipes "+
        "it clean.");

    set_cact_time(2);
    add_cact("emote mumbles: Death is impermanent. In the cycle " +
	     "of the Source I will always be a slave.");
    add_cact(({"say Isn't this just like you surface-dwellers?" +
	       " Killing defenseless people!", "emote blows spittle " +
	       "into your face"}));
    add_cact("say Damn you to the Source-less depths of the" +
	     "Utterdark!");
    add_cact("say I hope the demons take you!");
    add_cact("shout You are cruel, even for an Outlander!");
    add_cact("say Upon your head the fate of my orphaned children!");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"menu","help","food","key","fish","potato"}),
        "@@give_menu",1);
    add_ask(({"price","prices","cost","money","dish"}),
        "@@give_prices",1);
    add_ask(({"drink","drinks","beer"}),
        "shake",1);
    add_ask(({"library"}), "say The library is up north, right across " +
	    "the street from the bank.", 1);
    add_ask(({"bank"}), "say The bank is up north, right across " +
	    "the street from the library.", 1);
    add_ask(({"holm", "park", "Holm"}), 
        "say It can be reached through the garden in the bazaar. "+
        "It is a dangerours place. A gatekeeper guards the way.",1);
    add_ask(({"post office", "post"}), "say The postoffice is up north, " +
	    "right across the street from the smith.", 1);
    add_ask(({"smith", "forge"}), "say The smith is up north, " +
	    "right across the street from the postoffice.", 1);
    add_ask(({"pier"}), "say The pier is up northwest.", 1);
    add_ask(({"guild"}), "say The guild is on the west side of the bazaar.", 1);
    add_ask(({"pub"}), "say The pub is on the east side of the bazaar.", 1);
    add_ask(({"garden"}), "say Yes there is a garden south of the bazaar.", 1);


   config_default_trade();
   set_money_give_max(2000);
   set_money_give_out(({ 2000, 700, 50, 4}));
   set_money_give_reduce(({1,1,1,1}));

   seteuid(getuid(TO));
//   clone_object(BAZAAR+"Obj/misc/platter")->move(TO);
}

public string
what_me(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say The very air speaks!");        
        return "";
    }

    switch(random(4))
    {
        case 0:
            command("say I am but a humble servant, do not seek "+
                "answers from me.");
            break;
        case 1:
            command("say I fear such questions are beyond my ability "+
               "to answer.");
            break;
        case 2:
            command("emote shudders and carefully avoids meeting "+
                "your eyes.");
            break;
        case 3:
            command("say Isn't there someone else you should ask such "+
                "questions of?");
            break;
    }
    return "";    
}


public int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;

    name = arg[0];
    num = arg[1];
    ob = arg[2];

    for (i = 0; i < 10; i++)
    {
        num--;
        file = STAND_DIR + name;
        drink = clone_object(file);
        drink->move(TO);
        if (num < 1)
            break;
    }

    if (name == "inn_key")
	command("give "+ OB_NAME(drink) + " to "+ OB_NAME(ob));
    else
	command("give foods to "+ OB_NAME(ob));

    return 1;
}

/*
 * Function name: do_order
 * Description:   The buyer orders food
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
public int
do_order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("Buy what?\n");
    if (!str)
        return 0;

    /* Has the player defined how payment will be done and what change to get
       back? */
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    if (num > 10)
    {
        set_alarm(1.5, 0.0, &command("say I cannot carry that much."));
        return 1;
    }

    switch(str1)
    {
        case "soup":
        case "soups":
        case "fish soup":
            name = "soup";
            price = num * 12;
            break;
        case "stew":
        case "stews":
        case "potato stew":
            name = "stew";
            price = num * 24;
            break;
        case "mollusks":
        case "mollusk":
        case "boiled mollusk":
            name = "mollusk";
            price = num * 48;;
            break;
        case "meal":
        case "meals":
        case "fish meal":
            name = "fish";
            price = num * 200;
            break;
        case "eel":
        case "fried eel":
        case "plate of fried eel":
            name = "eel";
            price = num * 530;
            break;
        case "room":
        case "key":
            name = "inn_key";
            price = num * 144;
            break;
        default:
            command("say What is that?");
	    return 1;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
    {
        command("say No money - no food.");
        command("say My master doesn't feed beggars, sorry.");
        return 1;
    }

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
        write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    return move_item(({name, num, TP}));
}
 
public string
give_menu(void)
{
    command("emote glances upward as though he is trying to remember.");
    command("emote takes a deep breath.");
    command("emote exhales: We got the hot fish soup...the potato stew..."+
        "the boiled mollusk...the fish meal and the plate of fried eel. " +
        "If you want to spend the night, you will have to buy a key.");
    return "smile helpful";
}

public string
give_prices(void)
{
    command("smile joy");
    command("emote takes a deep breath.");
    command("emote exhales: Twelve coppers for the soup...Twentyfour "+
        "for the stew...Fortyeight for the mollusk. The fish meal is "+
        "twohundred...The eel is fivehundredandthirty and the key to "+
        "a room is ahundredandfourtyfour.");
    return "sweat"; 
}

public void
init_living(void)
{
    ::init_living();
    add_action(do_order,"buy");
    add_action(do_order,"order");
}

public void
thief_fun(object thief, object victim, object ob)
{
    set_alarm(1.8, 0.0, &command("poke "+ OB_NAME(thief) +" eye"));
    set_alarm(4.0, 0.0, &command("emote says "+
          "very slowly: I ... really ... hate ...."));
    set_alarm(4.5, 0.0, &command("say thieves."));
}
