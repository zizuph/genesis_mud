//-*-C++-*-
// file name:    Butcher Shop: /bazaar/intr/butcher_shop.c
// creator(s):   Lilith, Sep 1997  
// revised:      Lilith Jun 2014   Barrel wasn't re-setting.
// 
// purpose:      To dress corpses, turning them into food.      
//               A barrel is cloned here, as a source of organs.
// note:         Some functions borrowed from Cirion's locket_shop
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include "../bazaar.h"
#include <cmdparse.h>
#include <money.h>
#include <composite.h>
#include <flags.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define BAD_BOY   "_no_butcher_business_today"
#define FOOD_PATH BAZAAR +"Obj/food/"
#define ONONE     0 
#define OSTART    1 
#define OPROCEED  2
#define OCUTTING  3
#define OWORKING  4
#define OFINISHED 5

#define MS(delay, what)   (set_alarm(itof(delay), 0.0, &ms(what)))
#define BUTCHER_B_COST    150

object merchant, barrel;
string o_race;
object orderer, corpse, target;
int    order_status, meat, st, sa;

void finish_dressing();
void reset_room();

void
create_room()
{
    set_name("Drasbin's Butcher Shop");
    set_short("Drasbin's Butcher Shop");
    set_long("The slate floor of this shop is impeccably clean where "+
        "it is not splattered with blood and bits of flesh. There is "+
        "a long, low counter with a scale on it, and behind it, a "+
        "huge wooden chopping block with various tools embedded in "+
        "it.\nThere is a sign above the counter.\n");
    add_item(({"block", "chopping block", "tools", "hatchet"}), 
        "The wodden chopping block looks well-used. It has some "+
        "knives and a hatchet on it.\n");
    add_item(({"floor", "slate floor", "blood", "flesh", "bits",
        "work area" }),
        "A well-scrubbed floor of slate. Blood and bits of flesh "+
        "mark the butchers work area.");
    add_item(({"counter", "low counter", "scales", "scale"}),
        "It is long and low, the perfect height for laying out a "+
        "corpse for easy appraisal. The scale on it is for weigh"+
        "ing the cuts of meat.\n");
    add_item(({"sign", "list" }), "@@read_sign");
    add_cmd_item("sign", "read", "@@read_sign");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_exit(EXTR +"str8", "south", 0);

    config_default_trade();
    set_money_give_reduce( ({ 1, 9, 9, 9 }) );

    seteuid(getuid(this_object()));
    reset_room();
}

string
read_sign()
{
    return "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
           "~~~~~\n"+
           "    I, Drasbin the Butcher, am very efficient at dressing corpses.\n\n"+
           "    I will take any corpse and cut from it choice steaks, turning\n"+
           "    the rest into sausages.\n\n"+
           "    Please use <butcher corpse> if you want my services.\n"+
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
           "~~~\n\n";
}

int
do_help(string str)
{
    string text;

    if ( (str != "shop") && (str != "butcher") )
        return 0;
    write("There is no help file on this shop.\n");
    return 1;
}

int
do_item_filter(object ob)
{
    return(ob->id("corpse"));
}

void
ms(string str)
{
    merchant->command("say " + str);
}

void
reset_order()
{
    o_race = 0;
    meat = 0;
    st = 0;
    sa = 0;
    corpse = 0;
    orderer = 0; 
    order_status = ONONE;
}

int
cancel(string str)
{
    NF("Cancel what? Your order?\n");
    if (str != "order")
        return 0;

    if (TP != orderer)
    {
        MS(1, "You have no order to cancel!");
        return 1;
    }
    if (order_status >= OCUTTING)
    {
        MS(1, "Ok, "+ TP->query_race_name() +", I will cancel your "+
            "order.");
        MS(2, "I will keep the corpse as payment for my time and "+
            "effort, though.");
        reset_order();
        return 1;
    }
    MS(1,"Ok, " + TP->query_race_name() + ", I will cancel your order.");
    reset_order();
    return 1;
}

void
reset_room()
{
    reset_order();

    if(!merchant)
    {
       merchant = clone_object(NPC + "butcher");
       merchant->arm_me();
    }

    if(!present(merchant))
       merchant->move_living("away", TO);

    if(!barrel)
    {
        barrel = clone_object(BAZAAR +"Obj/misc/barrel");
        barrel->move(TO);
    } 
	barrel->fill_barrel();
}

int
order(string str)
{
    object *corpses;

    NF("The merchant is not here now.\n");
    if(!present(merchant))
        return 0;

    NF("You are too busy.\n");
    if(TP->query_attack())
        return 0;

    if (IS_INFIDEL(TP))
    {
        tell_object(TP, "The butcher refuses to do business with "+
            "criminals.\n");
        return 1;
    }

    if (str != "corpse")
    {
        MS(1, "I dress corpses only.");
        return 1;
    }
    if (TP->query_prop(BAD_BOY))
    {
        MS(1, "What? Do you think I'm stupid?!");
        MS(2, "Get out of my shop!");
        return 1;
    }
    if(orderer && orderer != TP)
    {
        MS(1, "I am currently dressing a corpse for someone else.");
        MS(1, "You will have to wait your turn.");
        return 1;
    }
    if(orderer && orderer == TP)
    {
        MS(1, "I am already dressing a corpse for you!");
        MS(1, "You can cancel at any time.");
        return 1;
    }
    corpses = filter(deep_inventory(TP), "do_item_filter", TO);
    if (!sizeof(corpses))
    {
        MS(1, "But you don't have a corpse for me to dress!");
        return 1;
    }
    corpse = corpses[0];
    if (sizeof(corpses) > 1)
    {
        MS(1, "I see you have more than one corpse, so I'll dress "+
            "the first one, which is "+ corpse->short() +".\n");
        MS(2, "To continue, please \"say That is fine.\"");
        MS(3, "If that corpse isn't the one you want dressed, just "+
            "<cancel order> and dispose of it before coming back.");
        order_status = OSTART;
        orderer = TP;
        return 1;
    }
    if (corpse->query_race() == "shadow-elf")
    {
        MS(1, "Did you really think I'd dress the corpse of a "+
            "shadow-elf?");
        MS(2, "Get out of my shop! I'll do no more business with "+
            "you today.");
        TP->add_prop(BAD_BOY, 1);
        return 1;
    }         
    MS(1, "I will be pleased to dress your "+ corpse->short() + 
        " for you.");
    MS(2, "If that is what you want, please \"say That is fine.\"");
    MS(3, "Otherwise, just cancel your order.");
    order_status = OSTART;
    orderer = TP;
    return 1;
}

void
leave_inv(object to, object from)
{
    ::leave_inv(to, from);

    if(orderer == to)
    {
        MS(1,"I will cancel your order.");
        reset_order();
    }
}

int
butcher_charge()
{
    int charge;

    /* We're providing a service, the player hauls the meat here */
    charge = BUTCHER_B_COST + (meat / 20);
    return charge;
}

int
do_say(string str)
{
    string arg;  

    if (order_status == ONONE)
        return 0;

    if (!strlen(str) || orderer != TP)
        return 0;

    if (str == "cancel order")
    {
        MS(1, "Don't \"say Cancel order.\" Just use <cancel order>.");
        return 0;
    }
    if (!corpse)
    {
        MS(1, "I cannot dress a corpse that you don't have.");
        MS(2, "Cancel your order and start again.");
        return 0;
    }
    if (order_status == OSTART)
    {
        str = lower_case(str);
        if (str == "that is fine" || str == "that is fine.")
        {
            meat = (corpse->weight() / 20);
            MS(1, "The "+ corpse->short() +" will produce "+ meat +" grams "+
                "of meat, packaged as steak and sausages.");
            MS(2, "My charge will be "+ LANG_WNUM(butcher_charge()) +
                " coppers.");
            MS(2, "If that is acceptable, \"say Please proceed.\"");
            order_status = OPROCEED;
            return 0;
        }
        else
        {
            MS(1, "I will be pleased to dress your "+ corpse->short() + 
                " for you.");
            MS(2, "If that is what you want, please \"say That is fine.\"");
            MS(2, "Otherwise, just cancel your order.");
            return 0;
        }                
    }
    if (order_status == OPROCEED)
    {
        if (!corpse)
        {
            MS(1, "I cannot dress a corpse that you don't have!");
            MS(2, "Cancel your order and start again.");
            return 0;
        }
        str = lower_case(str);        
        if (str == "please proceed" || str == "please proceed.")
        {
            o_race = corpse->query_race();
            set_alarm(1.0, 0.0, &merchant->command("emote gets the "+ 
                corpse->short()+"."));            
            MS(2,"I'll get started now. It will take a short while.");
            order_status = OCUTTING;
            set_alarm(2.0, 0.0, &corpse->remove_object());      
            set_alarm(45.0, 0.0, &finish_dressing());
            return 0;
        }
        else
        {
            MS(1,"Do you want me to proceed with dressing the "+ 
                corpse->short() +"?");
            MS(2,"If so, \"say Please proceed.\" If not, cancel your "+
                "order.");
            return 0;
        }
    }
    return 0;
}

void 
finish_dressing()
{
    int spam;
    if (order_status == ONONE)
        return 0;

    order_status = OFINISHED;

    /* half steak, half sausage */
    spam = meat / 2;
    st   = spam / 250;
    sa   = spam / 100; 

    write("The butcher opens the pristine barrel and puts some "+
        o_race +" organs in it.\n");
    MS(1,"I am finished dressing the "+ o_race +" corpse.");
    MS(2,"The cost is " + LANG_WNUM(butcher_charge()) + " coppers.");           
    return;
}

int
do_pay(string str)
{
    object food;
    int   *result;
    string file;

    NF("You haven't ordered anything to be butchered, so you have "+
        "nothing to pay for.\n");
    if (orderer != TP)
        return 0;

    NF("Your order is not yet finished.\n");
    if (order_status != OFINISHED)
        return 0;

    result = pay(butcher_charge(), TP);
    if (sizeof(result) == 1)
       return 0;

    say(QCTNAME(TP) + " pays for "+ POSSESS(TP) +" order.\n");
    write("You pay for your order.\n");
    STATSERV_LOG_EVENT("bazaar", "Corpses butchered");
    SCROLLING_LOG("/d/Avenir/log/bazaar/butcher", TP->query_name() +
        " visited the butcher.");

    if (st > 0)
    {
        file = FOOD_PATH +"b_steak";      
        food = clone_object(file);
        food->set_race(o_race);
        food->set_heap_size(st);
        food->add_race();
        food->move(this_player(), 1);
        write("You get your steaks.\n");
    }

    if (sa > 0)
    {
        file = FOOD_PATH +"b_sausage";      
        food = clone_object(file);
        food->set_race(o_race);
        food->set_heap_size(sa);
        food->add_race();
        food->move(this_player(), 1);
        write("You get your sausages.\n");
    }
    reset_order();
    return 1;
}

void
init()
{
    ::init();

    add_action(order,   "dress");
    add_action(order,   "butcher");
    add_action(do_pay,  "pay");
    add_action(do_say,  "say");
    add_action(cancel,  "cancel");
    add_action(do_help, "help");
}

