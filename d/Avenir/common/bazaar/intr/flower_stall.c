//-*-C++-*-
// file name:    Flower stall: /bazaar/intr/flower_stall
// creator(s):   Lilith, Jul 1997
// purpose:      Flowers made-to-order and delivered.
// note:         Made with idea contributions from Angelique.
//               Based on Cirion's locket_shop
/* Revisions:
 * 	Lucius, Apr 2018: Moved 'say' capturing to the npc which
 * 	                  gets passed back to the room. Also added
 * 	                  punctuation stripping to ordering.
 */
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

#define ONONE     0 
#define OSIZE     1 
#define OTYPE     2
#define OCOLOUR   3
#define OMESSAGE  4
#define ODELIVER  5
#define OWORKING  6
#define OFINISHED 7

#define VOID            (COM + "void")
#define FLOWER_HELP     (FLOWER_PATH +"flower_help")
#define FLOWER_PATH     (OBJ + "flower/")
#define FLOWER_B_COST   100
#define DELIVER_COST    50
#define DELIVER_TIME    random(20) + 40

object merchant;

mapping flower_sizes = ([ "bouquet" : 500, "posy" : 250, "circlet" : 200,
                          "corsage" : 100, "buttoniere" : 50, "single" : 25 ]);
string *types = ({ "aster", "carnation", "chrysanthemum", "daffodil", "daisy",
                   "dragonflower", "forget-me-not", "freesia", "hibiscus", 
                   "honeysuckle", "iris", "lavender", "lilac", "lily", "orchid", 
                   "passionflower", "peony", "poppy", "rose", "tulip" });
string *colours = ({ "black", "blue", "dead", "green", "orange", "pink", 
                     "purple", "red", "white", "yellow", "peach", "scarlet",
                     "violet", "faded"});
string *sizes = m_indices(flower_sizes);
string o_size, o_type, o_colour, o_message, o_deliver;

object orderer, flower, target;

int order_status;
int deliver_it;
void finish_flower();
void reset_room();

void
create_room()
{
    reset_euid();

    set_name("stall");
    set_short("Flower stall");
    set_long("This is an open-air flower stall. Baskets of flowers "+
       "perfume the air and crowd the mat that has been spread upon "+
       "the ground to mark this merchant's space. There is a sign "+
       "propped against one of the baskets.\n");

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    add_item(({"basket", "baskets", "flower", "flowers" }),
       "Water-tight baskets are filled to capacity with "+
       "numerous species of flowers.\n");
    add_item("sign", "@@read_sign");
    add_cmd_item("sign", "read", "@@read_sign");
    add_exit(EXTR +"str11", "out", 0);
    reset_room();
	
		
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


}

string
read_sign()
{
    return "   Flowers from the Hanging Gardens of the Sybarus "+
           "Ziggurat, cut fresh daily.\nI, Shabaz, make the following:\n"+
           capitalize(COMPOSITE_WORDS(sizes)) +".\n\n"+
           "   These are the flowers currently available:\n"+
           capitalize(COMPOSITE_WORDS(types)) +".\n\n"+
           "   The costs range from 150cc to 650cc. "+
           "There is an extra charge for deliveries. "+
           "If you want one, just <order flower>. "+
           "If you need help, just <help flowers>.\n\n";
}

int
do_help(string str)
{
    string text;

    if ( (str!="flower") && (str!="flowers") )
        return 0;

    text = read_file(FLOWER_HELP);
    this_player()->more(text);
    return 1;
}

void
MS(int delay, string str)
{
    float val;

    if (!merchant || !strlen(str))
	return;

    if (delay > 0)
	set_alarm(itof(delay), 0.0, &merchant->command("say "+ str));
    else
	merchant->command("say "+ str);
}

void
reset_order()
{
    o_size = 0;
    o_message = 0;
    o_type = 0;
    o_colour = 0;
    o_deliver = 0;
    orderer = 0; 
    deliver_it = 0;  
    order_status = ONONE;
}

int
cancel(string str)
{
    NF("Cancel what? Your order?\n");
    if(str != "order")
       return 0;

    if(TP != orderer)
    {
       MS(0, "You have no order to cancel!");
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
       merchant = clone_object(NPC + "flower_seller");
       merchant->arm_me();
    }

    if(!present(merchant))
       merchant->move_living("away", TO);
}

int
order(string str)
{
    NF("The merchant is not here now.\n");
    if(!present(merchant))
        return 0;

    NF("You are too busy.\n");
    if(TP->query_attack())
        return 0;

    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The florist refuses to "+
            "conduct business with criminals.");
        return 1;
    }        
    if (str != "flower" && str != "flowers" && str != "posy" &&
        str != "flower arrangement" && str != "corsage" && 
        str != "bouquet" && str != "buttoniere" && str != "circlet")
    {
        MS(1, "I only sell flowers.");
        return 1;
    }

    if(orderer && orderer != TP)
    {
        MS(1, "I am already working on a flower arrangement for someone else.");
        MS(1, "You will have to wait your turn.");
        return 1;
    }

    if(orderer && orderer == TP)
    {
        MS(1, "I am already working on a flower arrangement for you!");
        MS(1, "If you like, you can cancel your order at any time.");
        return 1;
    }


    MS(1, "What size would you like your flower arrangement to be? You "+
        "can choose from " + COMPOSITE_WORDS(sizes) + ".");
    MS(2, "Select your arrangement by saying \"Make it a <arrangement>\"");
    order_status = OSIZE;
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
do_say(string str)
{
    string arg;
    object *obs, what;

    if (order_status == ONONE)
        return 0;

    if (!strlen(str) || orderer != TP)
        return 0;

    /* Strip punctuation */
    while(wildmatch("*[.?!]", str))
	str = str[..-2];

    if (order_status == OSIZE)
    {
        str = lower_case(str);
        sscanf(str, "make it a %s", arg);

        if (!strlen(arg))
            return 0;

        if (member_array(arg, sizes) == -1)
        {
            MS(1,"I am deeply sorry, but I do not know how to make that.");
            MS(1,"I only can make flower arrangements of these types: "+
                COMPOSITE_WORDS(sizes) + ".");
            return 0;
        }

        o_size = arg;

        MS(1,"I have the following flowers available: "+ COMPOSITE_WORDS(types) +
             ".");
        MS(2,"I can only make that arrangement using one kind of flower. "+
            "What flower shall we use?");
        MS(3,"You can just \"say Make it with <flower>\"");

        order_status = OTYPE;
        return 0;
    }

    if (order_status == OTYPE)
    {
        str = lower_case(str);
        sscanf(str, "make it with %s", arg);
        if (!strlen(arg))
            return 0;

        if (member_array(arg, types) == -1)
        {
            MS(1,"I am deeply sorry, but that species of flower is unavailable "+
                "to me.");
            MS(1,"You can choose one of these flowers: "+ 
                COMPOSITE_WORDS(types) + "...");
            MS(2,"Or, if you do not like my selection, you may cancel your order.");
            return 0;
        }

        o_type = arg;
        
        MS(1,"Now, what colour do you want the "+ o_type +" in your "+ o_size +
            " to be?");
        MS(2,"At present, it is available in these colours: "+ 
            COMPOSITE_WORDS(colours) +".");
        MS(3,"You can just \"say I want it <colour>\"");
 
        order_status = OCOLOUR;
        return 0;
    }

    if (order_status == OCOLOUR)
    {
        str = lower_case(str);
        sscanf(str, "i want it %s", arg);
        if (!strlen(arg))
            return 0;

        if (member_array(arg, colours) == -1)
        {
            MS(1,"The Goddess Sachluph has blessed us with the "+ o_type +
                "in many shades, however, I do not have it in the colour "+
                "you have requested.");
            MS(2,"Are you sure you wouldn't want it "+ COMPOSITE_WORDS(colours) +"?");
            MS(3,"You can just \"say I want it <colour>\", or simply cancel your "+
                "order.");
            return 0;
        }
        
        o_colour = arg;
      
        if (o_colour == "dead")
            MS(1, "How morbid! Well, it just so happens I have a "+
                "dead "+ o_type +" or two.");
        else
            MS(1,"Excellent choice!");
        
        MS(2,"Now, would you like a card with a special message included?");       
        MS(3,"If you do not, just \"say No message on card\".");
        MS(4,"Otherwise, \"say Include the message <words>\".");

       order_status = OMESSAGE;
       return 0;
    }

    if (order_status == OMESSAGE)
    {
        sscanf(lower_case(str), "no message %s", arg);
        if(strlen(arg))
        {
            MS(1,"Ok. Will you want this "+ o_type +" delivered?");
            MS(2,"If you do not, just \"say Don't deliver it\".");
            MS(3,"Otherwise, \"say Deliver to <first name>\".");
            order_status = ODELIVER;
            return 0;
        }

        sscanf(lower_case(str), "include the message %s", arg);
        if(!strlen(arg))
            return 0;

        if(strlen(arg) > 100)
        {
            MS(1,"Sorry, but that message is too long!");
            MS(2,"You need to keep it short, or else it won't fit on the card.");
            return 0;
        }

        o_message = arg;

        MS(1,"Succinctly put! I will include the message: "+ o_message +" in "+
            "the card that goes with the "+ o_type +".");
        MS(2,"And will you want this "+ o_type +" delivered? It will cost an "+
            "additonal " + LANG_WNUM(DELIVER_COST)+" coppers.");
        MS(3,"If you do not, just \"say Don't deliver it\".");
        MS(4,"Otherwise, \"say Deliver to <first name>\".");

        order_status = ODELIVER;
        return 0;
    }

    if (order_status == ODELIVER)
    {
        sscanf(lower_case(str), "don't deliver %s", arg);
        if(strlen(arg))
        {
            MS(1,"Ok. I will have your "+ o_type +" ready shortly.");
            order_status = OWORKING;
            set_alarm(30.0, 0.0, &finish_flower());
            return 0;
        }

        sscanf(lower_case(str), "deliver to %s", arg);
        if(!strlen(arg))
        {
            MS(1,"Deliver to whom?");              
            return 0;
        }        

        arg = lower_case(arg);
        target = find_player(arg);
        if (!target)
        {
            MS(1,"The "+ o_type +" cannot be delivered to "+ capitalize(arg) +
                ", because that individual is currently out of touch with "+
                "our reality.");
            MS(2,"Choose another person to deliver to, or just \"say Don't "+
                "deliver it\".");
            return 0;
        }

        o_deliver = arg;

        MS(1,"Ah yes, I do believe that we can reach "+ capitalize(arg) +
            ". Now if you will just wait one moment while I complete the "+
            "flower arrangement...");
        deliver_it = 1;
        order_status = OWORKING;
        set_alarm(45.0, 0.0, &finish_flower());
        return 0;
    }
    return 0;
}

int
flower_value()
{
    int value;

    value = FLOWER_B_COST;
    if(o_deliver)
       value += DELIVER_COST;
    value += flower_sizes[o_size];

    return value;
}

void 
finish_flower()
{
    order_status = OFINISHED;
 
    if (deliver_it)
    {
        if (!target || target->query_prop(OBJ_I_INVIS) ||
           (target->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M))
        {
            MS(1,"I've just received word that "+ capitalize(o_deliver) +
                " is not accepting deliveries at this time.");             
            MS(2,"You can pay me for the "+ o_type +" "+ 
                " or cancel your order.");
            o_deliver = 0; 
            deliver_it = 0;
            MS(3,"The cost is " + LANG_WNUM(flower_value()) + " coppers.");
            return;
        }                       
        MS(1,"I am finished with the "+ o_type +" arrangement"+
            ". You can pay me for it now.");
        MS(2,"The cost is " + LANG_WNUM(flower_value()) + " coppers.");           
        return;
    }
    else
    {
        MS(1,"I am finished with the "+ o_colour +" "+ o_type +
            " arrangement. You can pay me for it now.");
        MS(2,"The cost is " + LANG_WNUM(flower_value()) + " coppers.");           
        return;
    }
}

int
do_pay(string str)
{
    object flwr;
    int   *result;

    NF("You have no flower ordered to pay for.\n");
    if (orderer != TP)
        return 0;

    NF("Your flower arrangement is not yet finished.\n");
    if (order_status != OFINISHED)
        return 0;

    result = pay(flower_value(), TP);
    if (sizeof(result) == 1)
       return 0;

    say(QCTNAME(TP) + " pays for a flower arrangement.\n");
    write("You pay for the flower arrangement.\n");

    flwr = clone_object(FLOWER_PATH + o_size);
    flwr->set_colour(o_colour);
    flwr->set_size(o_size);
    flwr->set_type(o_type);
    flwr->set_from(orderer->query_real_name());
    flwr->set_message(o_message);
    flwr->set_load(1);

    STATSERV_LOG_EVENT("bazaar", "Flowers bought:");
    SCROLLING_LOG("/d/Avenir/log/bazaar/flowers", TP->query_name() + " bought a " 
           + o_colour + " " + o_type + " " + o_size + " (" + o_message + " "+
           o_deliver +")");

    if (deliver_it)
    {
        flwr->set_target(o_deliver);
        flwr->create_flower();
        flwr->make_her();
        tell_room(ENV(TP), "The flower merchant gives the flower arrangement "+
            "and a few coins to a "+ flwr->query_her() +", who runs "+
            "off into the crowd.\n");
        MS(1,"The arrangement will be delivered in good time. If the child "+
            "cannot find "+ capitalize(o_deliver) +" she will return your "+
            "purchase to you.");      
        flwr->do_deliver();
        flwr->move(VOID, 1);
        reset_order();
        return 1;
    }
    flwr->create_flower();
    flwr->move(TP, 1);
    write("You get your flower arrangement.\n");
    reset_order();
    return 1;
}             

void
init()
{
    ::init();

    add_action(order, "order");
    add_action(do_pay, "pay");
//    add_action(do_say, "say");
//    add_action(do_say, "'", 2);
    add_action(cancel, "cancel");
    add_action(do_help, "help");
}

