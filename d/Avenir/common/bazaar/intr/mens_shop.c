// file name:    /d/Avenir/common/bazaar/intr/mens_shop.c
// creator(s):   Lilith, Aug 1997
// revised:      Denis, Mar'2001: It would generate runtime error,
//                                if the person would cancel the order
//                                while the tailor already finishes it.
//                                (In finish_clothing())
// purpose:      Place to order custom clothing.      
// note:         Based on Cirion's locket_shop.c
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include "../bazaar.h"
#include "/d/Avenir/include/relation.h"

#include <cmdparse.h>
#include <composite.h>
#include <money.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define ONONE     0 
#define OSTYLE    1 
#define OSUBSTYLE 2
#define OTYPE     3
#define OCOLOUR   4
#define ODESC     5
#define OWORKING  6
#define OFINISHED 7

#define MS(delay, what)   (set_alarm(itof(delay), 0.0, &ms(what)))
#define MENSHOP_PATH      (BAZAAR + "Obj/worn/")
#define CLOTH_B_COST      (200 + random(100))

private static mapping fabric_type;
private static string *styles, *types, *colours, *descs,
	              *pants, *cloaks, *shirts;
private static string o_style, o_substyle, o_type, o_colour, o_desc;
private static object merchant, orderer, target;
private static int order_status;

public void reset_room(void);
private void finish_clothing(void);

public void
create_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("Measuring room for custom-tailored clothing");
    set_long("This is Emarus the Tailor's measuring room, where people "+
        "can be fitted with custom-tailored clothing.  Against the "+
        "walls of this tent are piled bolts of material, ranging from "+
        "linen to webcloth to suede.  The floor is littered with fabric "+
        "scraps and small bits of metal.\nA sign, artfully crafted "+
        "from patches of fabric.\n");
    add_item(({"bolts", "bolt", "material", "lengths" }), 
        "These are lengths of material used in making specialty "+
        "clothing for Emarus' better clientele.\n");
    add_item(({"walls", "tent" }),
        "The walls of this tent are made from a heavy dark-blue "+
        "material.\n");
    add_item(({"clothing", "clothes", "half-finished clothes" }), 
        "There are many, many half-finished items of clothing lying "+
        "about, as though pre-made to be fitted to the right customer "+
        "later.\n");
    add_item(({"floor", "litter", "fabric", "scraps" }),
        "The floor has fabrics scraps of various sizes all over it. "+
        "You suspect that Emarus cuts and snips and lets things fall "+
        "where it will, too busy to clean up after each customer.\n");
    add_item(({"metal", "bits", "pieces", "copper" }), 
        "It looks like pieces of copper.\n");
    add_item(({"sign", "patches" }), "@@read_sign");
    add_cmd_item("sign", "read", "@@read_sign");
    add_exit(INTR +"main_menshop", "back", 0);

    config_default_trade();
    set_money_give_reduce( ({ 1, 9, 9, 9 }) );

    reset_room();

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    object vars = (MENSHOP_PATH + "mencloth_base")->get_this_object();

    types   = vars->query_types();
    descs   = vars->query_descs();
    styles  = vars->query_styles();
    colours = vars->query_colours();

    pants   = vars->query_pants();
    cloaks  = vars->query_cloaks();
    shirts  = vars->query_shirts();

    fabric_type = vars->query_fabric_map();
}

public string
read_sign(void)
{
    return "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
           "   I, EMARUS the TAILOR, make these styles of clothing:\n"+
           capitalize(COMPOSITE_WORDS(styles)) +".\n\n"+
           "   These are the fabrics currently available:\n"+
           capitalize(COMPOSITE_WORDS(types)) +".\n\n"+
           "   I also have a wide range of colours:\n"+
           capitalize(COMPOSITE_WORDS(colours)) +".\n\n"+
           "   I also add the following special touches:\n"+
           capitalize(COMPOSITE_WORDS(descs)) +".\n\n"+         
           "   My prices are reasonable, beginning at 200cc.\n"+
           "If you want to order something, just <order clothes>.\n"+
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

private void
ms(string str)
{
    merchant->command("say " + str);
}

private void
reset_order(void)
{
    o_style = 0;
    o_substyle = 0;
    o_desc = 0;
    o_type = 0;
    o_colour = 0;
    orderer = 0; 
    order_status = ONONE;
}

private int
cancel(string str)
{
    if (str != "order")
       return NF("Cancel what? Your order?\n");

    if(TP != orderer)
    {
       ms("You have no order to cancel!");
       return 1;
    }

    MS(1,"Ok, " + TP->query_race_name() + ", I will cancel your order.");
    reset_order();
    return 1;
}

public void
reset_room(void)
{
    reset_order();

    if (!merchant)
    {
       merchant = clone_object(NPC + "tailor");
       merchant->arm_me();
    }

    if (!present(merchant))
       merchant->move_living("away", TO);
}

private int
order(string str)
{
    if (!present(merchant))
        return NF("The merchant is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (merchant->query_attack())
        return NF("The merchant is too busy.\n");

    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The tailor refuses to do business "+
            "with criminals.\n");
        return 1;
    }

    if (str != "cloth" && str != "clothes" && str != "clothing" &&
        str != "something" && str != "pants" && str != "shirt" && 
        str != "cloak")
    {
        MS(1, "I custom-make clothing only.");
        return 1;
    }

    if (orderer && orderer != TP)
    {
        MS(1, "I am currently tailoring some clothing for someone else.");
        MS(1, "You will have to wait your turn.");
        return 1;
    }

    if (orderer && orderer == TP)
    {
        MS(1, "I am already tailoring something for you!");
        MS(1, "If you like, you can cancel your order at any time.");
        return 1;
    }

    MS(1, "What item of clothing would you like me to make for you? I "+
        "can make " + COMPOSITE_WORDS(styles) + ".");
    MS(2, "Make your selection by saying \"I like your <items>\"");

    order_status = OSTYLE;
    orderer = TP;
    return 1;
}

public void
leave_inv(object to, object from)
{
    if (orderer == to)
    {
        MS(1, "I will cancel your order.");
        reset_order();
    }

    ::leave_inv(to, from);
}

private int
do_say(string str)
{
    string arg, other;  
    object *obs, what;

    if (order_status == ONONE)
        return 0;

    if (!strlen(str) || orderer != TP)
        return 0;

    if (order_status == OSTYLE)
    {
        str = lower_case(str);
        sscanf(str, "i like your %s", arg);

        if (!strlen(arg))
            return 0;

        if (member_array(arg, styles) == -1)
        {
            MS(1,"I am deeply sorry, but I'm not quite understanding you.");
            MS(1,"I only can make the following types of clothing: "+
                COMPOSITE_WORDS(styles) + ".");
            MS(2,"Please say which you like.");
            return 0;
        }

        switch(o_style = arg)
	{
	case "pant":
	case "pants":
            MS(1, "I can tailor "+ o_style +" in these styles: "+
                COMPOSITE_WORDS(pants) + ".");
	    break;
	case "cloak":
	case "cloaks":
	    MS(1, "I can tailor "+ o_style +" in these styles: "+
		COMPOSITE_WORDS(cloaks) + ".");
	    break;
	case "shirt":
	case "shirts":
		MS(1, "I can tailor "+ o_style +" in these styles: "+
		    COMPOSITE_WORDS(shirts) + ".");
	    break;
	}

        MS(2, "To choose a style, just \"say I want <style>\"");

        order_status = OSUBSTYLE;
        return 0;
    }

    if (order_status == OSUBSTYLE)
    {
        str = lower_case(str);
        sscanf(str, "i want %s", arg);
        if (!strlen(arg))
            return 0;
        
        if ( (member_array(arg, pants) == -1)  && 
             (member_array(arg, shirts) == -1) &&
             (member_array(arg, cloaks) == -1) )
        {
            MS(1,"I am deeply sorry, but "+ o_style +" in that style "+
                 "are unknown to me.");
            MS(2,"If you do not like my selection, you may cancel your order.");
            return 0;
        }

        o_substyle = arg;
                    
        MS(1,"Great! Now, for your "+ o_substyle +" I have the following "+
             "fabrics available: "+ COMPOSITE_WORDS(types) +".");
        MS(3,"You can just \"say Make it with <fabric>\"");

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
            MS(1,"I am deeply sorry, but that type of fabric is unknown "+
                "to me.");
            MS(1,"You can choose from one of these fabrics: "+ 
                COMPOSITE_WORDS(types) + "...");
            MS(2,"Or, if you do not like my selection, you may cancel "+
		"your order.");
            return 0;
        }

        o_type = arg;
        
        MS(1,"Now, what colour do you want the "+ o_type +" to be?");
        MS(2,"Right now, I have these colours: "+ 
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
            MS(1,"That is a very unusual colour...I don't have it right now.");
            MS(2,"Are you sure you wouldn't want it "+
		COMPOSITE_WORDS(colours) +"?");
            MS(3,"You can just \"say I want it <colour>\", or simply "+
		"cancel your order.");
            return 0;
        }
        
        o_colour = arg;
      
        MS(1,"You've such good taste!");
        MS(2,"Now, I can add one of these special touches: "+
            COMPOSITE_WORDS(descs) +".");       
        MS(3,"If you do not want anything else, just \"say Nothing else\".");
        MS(4,"Otherwise, \"say Also make it <special touch>\".");

       order_status = ODESC;
       return 0;
    }

    if (order_status == ODESC)
    {
        sscanf(lower_case(str), "nothing %s", arg);
        if (strlen(arg))
        {
            MS(1,"Ok. I'll make it a plain "+ o_colour +" "+ o_type +
                " "+ o_substyle +".");
            MS(3,"Let me just make the final adjustments...");
            order_status = OWORKING;
            set_alarm(20.0, 0.0, &finish_clothing());
            return 0;
        }

        sscanf(lower_case(str), "also make it %s", arg);
        if (!strlen(arg))
            return 0;

        if (member_array(arg, descs) == -1)
        {
            MS(1, "That is an unusual special touch. I'm not familiar with it.");
            MS(2, "Choose from the selection on the sign, or just "+
		"\"say Nothing else\".");
            return 0;
        }
        o_desc = arg;

        MS(1,"Very good! You have ordered a "+ o_desc +" "+ o_colour +
            " "+ o_type +" "+ o_substyle +"."); 
        MS(3,"Let me just make the final adjustments...");
        order_status = OWORKING;
        set_alarm(30.0, 0.0, &finish_clothing());
        return 0;
    }
    return 0;
}

private int
fabric_value(void)
{
    return CLOTH_B_COST + (fabric_type[o_type][0] * 10);
}

private void 
finish_clothing(void)
{
    if (!orderer)
	return;
    
    order_status = OFINISHED;
 
    if (!o_desc)
    {
        MS(1,"I am finished with the "+ o_colour +
            " "+ o_type +" "+ o_substyle +
            ". You can pay me for it now.");
    }
    else  
    {
        MS(1,"I am finished with the "+ o_desc +" "+ o_colour +
            " "+ o_type +" "+ o_substyle +
            ". You can pay me for it now.");
    }

    MS(2,"The cost is " + LANG_WNUM(fabric_value()) + " coppers.");           
}

private int
do_pay(string str)
{
    object citm;
    int   *result;

    if (orderer != TP)
    {
	NF("You haven't ordered any clothing, "+
	    "so you have nothing to pay for.\n");
        return 0;
    }

    if (order_status != OFINISHED)
        return NF("Your clothing is not yet finished.\n");

    result = pay(fabric_value(), TP);
    if (sizeof(result) == 1)
       return 0;

    say(QCTNAME(TP) + " pays for "+ POSSESS(TP) +" order.\n");
    write("You pay for your order.\n");

#if 0
    SCROLLING_LOG("/d/Avenir/log/bazaar/menshop", TP->query_name() + " bought a "
           + o_desc +" "+ o_colour +" "+ o_type +" "+ o_substyle);
#endif

    citm = clone_object(MENSHOP_PATH + "men" + o_style);
    citm->set_colour(o_colour);
    citm->set_substyle(o_substyle);
    citm->set_type(o_type);
    if (o_desc)
        citm->set_desc(o_desc);
    citm->set_load(1);
    citm->create_tailored();
    citm->update_prop_settings();    
    citm->move(TP, 1);
    write("You get your specially tailored clothing.\n");
    reset_order();
    return 1;
}             

public void
init(void)
{
    ::init();

    add_action(order, "order");
    add_action(do_pay, "pay");
    add_action(do_say, "say");
    add_action(do_say, "'", 2);
    add_action(cancel, "cancel");
}

