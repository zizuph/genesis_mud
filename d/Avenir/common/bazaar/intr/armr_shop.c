//-*-C++-*-
// file name:    Armourer: /bazaar/intr/armour_shop.c
// creator(s):   Lilith, March 1998
// revised:
// purpose:      Place to order custom-made armours
// note:         Accessible only after completion of falchion quest.
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/trade";

#include "../bazaar.h"
#include "../Obj/forge/forge.h"

#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>

private int order_status;
private object merchant, orderer, clothing;
private string o_worn, o_style, o_decor, o_plate, o_colour, o_lining;


public void
reset_room(void)
{
    if (!merchant)
    {
       merchant = clone_object(NPC + "armourer");
       merchant->equip_me();
    }

    if (!present(merchant))
       merchant->move_living("X", this_object());
}

public void
create_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("Bazaar Island Forge Specialty Armourer");
    set_long("Here, beyond the oppressive warmth of the blacksmith's "+
        "forge, is the place where specialty armours are designed "+
        "and fitted.\n   The light of the Source illuminates this "+
        "small cobblestone courtyard. There is a small well at the "+
        "center, surrounded by work-benches and scraps of metal and "+
        "cloth. The high stone wall to the south has been plastered "+
        "and painted with letters, making a large, legible sign.\n");

    add_item(({"bench", "benches", "work-bench", "work-benches"}),
        "There are numerous benches surrounding the well. Apprentices "+
        "and master armourers alike work at them, heads bent and "+
        "fingers moving busily.\n");
    add_item("well", "It is a small well, scarely wider than a bucket.\n");
    add_item(({"apprentice", "apprentices", "master armourers", "armourers", }),
        "Upon closer observation, you notice that nearly everyone in "+
        "this courtyard is not only dwarven, but also female.\n");
    add_item(({"scrap", "scraps", "metal", "cloth"}), 
        "They are unremarkable...just what you would expect to see "+
        "in a place where armours are made.\n");
    add_item(({"sign", "letters" }), "@@read_sign");
    add_cmd_item(({"sign", "wall", "stone wall"}), "read", 
        "@@read_sign");
    add_item("cobblestone", "Small, octogonal cobblestones are fitted "+
        "together without mortar.\n");
    add_item(({"source", "Source", "illumination", "vein", "mineral"}), 
        "A vein of brilliantly-glowing mineral snakes across the "+
        "ceiling of this great cavern.\n");

	
	IN;       // Avenir is an undergound domain.

    add_exit(INTR +"armr", "east", 0);

    config_default_trade();
    reset_room();
}

public string
read_sign(void)
{
#define H_I(x)  HANGING_INDENT("      " + implode(x, ", "), 6, 0)
    return 
	" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
	"~~~~~~~~~~~\n"+
	"               Bazaar Island Forge Specialty Armourer\n"+
	" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
	"~~~~~~~~~~~\n"+
	"   This specialty armoury makes high-quality armours "+
	"for the following:\n"+
	H_I(FORGE_MASTER->query_where()) +"\n"+
	"   These are the armour styles (mail) currently available:\n"+
	H_I(FORGE_MASTER->query_styles()) +"\n"+
	"   Armours can be decorated in the following ways:\n"+
	H_I(FORGE_MASTER->query_decors()) +"\n"+
	"   Plating is currently available in:\n"+
	H_I(FORGE_MASTER->query_platings()) +"\n"+
     	"   We have lacquers and enamels in a wide range of colours:\n"+
	H_I(FORGE_MASTER->query_colours()) +"\n"+
	"   Lastly, we provide armour lining from the following list.\n"+
	H_I(FORGE_MASTER->query_linings()) +"\n"+
	"  The lining colour will be the same colour as the lacquer or\n"+
	"  enamel you have chosen. If you choose to have your armour\n"+
	"  plated, the lining will be white.\n\n"+
	"  My prices are reasonable, as you can judge by the wares I\n"+
	"  currently have in stock, which you can do with <list>.\n\n"+
	"  If you want to order something, just <order armour>.\n"+
	"  If you want to repair an armour, just <fix [armour]>.\n"+
	"  If you want to estimate repair costs, just <cost [armour]>.\n"+
	" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
	"~~~~~~~~~~~~~~~~~~~~\n";
#undef H_I
}

private void
ms(string str)
{
    merchant->command("say " + str);
}

private void
msto(string str, object who)
{
    merchant->command("say to "+ OB_NAME(who) + " " + str);
}

private void
reset_order(void)
{
    if (order_status == OFINISHED)
    {
        MS(1,"I suppose I'll just add this"+ 
            " to the pile. Maybe someone will want to buy it.");
        clothing->move(merchant, 1);
    }

    order_status = ONONE;
    o_worn = 0; 
    o_style = 0;
    o_decor = 0;
    o_plate = 0; 
    o_lining = 0;
    o_colour = 0;
    orderer = 0;     
    clothing = 0;
}

public int
cancel(string str)
{
    if (str != "order")
       return NF("Cancel what? Your order?\n");

    if (TP != orderer)
    {
       ms("You have no order to cancel!");
       return 1;
    }

    MS(1,"Ok, " + TP->query_race_name() + ", I will cancel your order.");
    reset_order();

    return 1;
}

public int
order(string str)
{
    if (!present(merchant))
        return NF("The armourer is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (merchant->query_attack())
        return NF("They are too busy.\n");

    if (str != "armour")
    {
        MS(1, "Try <order armour>.");
        return 1;
    }

    if (orderer && (orderer != TP))
    {
        MS(1, "We are currently making armour for someone else.");
        MS(1, "You will have to wait your turn.");
        return 1;
    }

    if (orderer && (orderer == TP))
    {
        MS(1, "I am already making something for you!");
        MS(1, "If you like, you can cancel your order at any time.");
        return 1;
    }

    MS(1, "What part of your body are we fitting with armour? I "+
        "can make armour for: " +
        COMPOSITE_WORDS(FORGE_MASTER->query_where()) + ".");
    MS(2, "Make your selection with \"say Armour for my <body-part>\"");

    order_status = OWORN;
    orderer = TP;

    return 1;
}

public void
leave_inv(object to, object from)
{
    ::leave_inv(to, from);

    if (orderer == to)
    {
        if (order_status == OFINISHED)
	{
            MS(0,"If you do decide you want the "+ clothing->short() +
                " after all, it will be in the pile here.");
	}
        else
	{
            MS(1,"I will cancel your order.");
	}

        reset_order();
    }
}

private void 
finish_clothing(void)
{
    order_status = OFINISHED;

    switch(o_worn)
    {
    case "hands"      :  o_worn = "gauntlets"; break;
    case "feet"       :  o_worn = "boots";     break;
    case "head"       :  o_worn = "helm";      break;
    case "arms"       :  o_worn = "bracers";   break;
    case "legs"       :  o_worn = "greaves";   break;
    case "torso"      :  o_worn = "breast";    break;
    case "full-body"  :  o_worn = "suit";      break;
    case "full body"  :  o_worn = "suit";      break;
    case "entire body":  o_worn = "suit";      break;
    case "shield"     :  o_worn = "shield";    break;
    case "shield-arm" :  o_worn = "shield";    break;
    case "shield arm" :  o_worn = "shield";    break;
    default           :  o_worn = "";          break;
    }

    if (!strlen(o_worn) || !(clothing = clone_object(ARMSHOP_PATH + o_worn)))
    {
        write("The armour is flawed! I'm sorry, we will "+
            "have to start again!");

        reset_order();
        return;
    }     

    if (o_plate)
        clothing->set_plating(o_plate);

    clothing->set_colour(o_colour);
    clothing->set_decor(o_decor);
    clothing->set_style(o_style);
    clothing->set_lining(o_lining);
    clothing->set_owner(orderer->query_race());

    clothing->forge_it();
 
    MS(1,"I am finished with your "+ clothing->short() +
        ", "+ orderer->query_nonmet_name() +". You can pay me for it now.");
    MS(2,"The cost is " + clothing->query_value() + " coppers.");           

    return;
}

public int
do_say(string str)
{
    string arg, other;  
    object *obs, what;

    if (order_status == ONONE)
        return 0;

    if (!strlen(str) || (orderer != TP))
        return 0;

    if (!CAN_SEE(merchant, TP))
    {
	merchant->command("say The spirits.. they speak to me...");
	return 1;
    }

    if (order_status == OWORN)
    {
        str = lower_case(str);
        sscanf(str, "armour for my %s", arg);

        if (!strlen(arg))
            return 0;

        if (member_array(arg, FORGE_MASTER->query_where()) == -1)
        {
            MS(1,"I am deeply sorry, but I'm not quite understanding you.");
            MS(1,"I only can make armours for the following body-parts: "+
                COMPOSITE_WORDS(FORGE_MASTER->query_where()) + ".");
            MS(2, "Please \"say Armour for my <body-part>\"");
            return 0;
        }

        o_worn = arg;

        MS(1, "Fine. We will make armour for your "+ o_worn +".");
        MS(2, "Now, you need to choose one of these armour styles: "+
            capitalize(COMPOSITE_WORDS(FORGE_MASTER->query_styles())) +
            ". Just \"say I would like <style>\"");

        order_status = OSTYLE;
        return 0;
    }

    if (order_status == OSTYLE)
    {
        str = lower_case(str);
        sscanf(str, "i would like %s", arg);
        if (!strlen(arg))
            return 0;
        
        if (member_array(arg, FORGE_MASTER->query_styles()) == -1)
        {
            MS(1,"I am deeply sorry, but that style of armour is "+
                "unknown to me.");
            MS(2,"If you do not like my selection, you may cancel your order.");
            return 0;
        }

        o_style = arg;
                    
        MS(1,"That is easy enough! Now, how do you want your "+ 
            FORGE_MASTER->query_armour_style(o_style) +" decorated? "+
            "Armours can be "+ 
            capitalize(COMPOSITE_WORDS(FORGE_MASTER->query_decor())) +".");
        MS(3,"You can just \"say I want it <how>\"");

        order_status = ODECOR;
        return 0;
    }

    if (order_status == ODECOR)
    {
        str = lower_case(str);
        sscanf(str, "i want it %s", arg);
        if (!strlen(arg))
            return 0;

        if (member_array(arg, FORGE_MASTER->query_decor()) == -1)
        {
            MS(1,"I am not skilled enough to do that. Armour can be "+ 
                COMPOSITE_WORDS(FORGE_MASTER->query_decor()) +".");
            MS(2,"Or, if you do not like my selection, "+
		"you may \"cancel order\".");
            return 0;
        }

        o_decor = arg;
        
        if (o_decor == "plated")
        {
            MS(1,"How do you want your "+ 
                FORGE_MASTER->query_armour_style(o_style) +" plated?");
            MS(2,"I can add "+ COMPOSITE_WORDS(
		    FORGE_MASTER->query_plating()) +
		" plating to your armour.");
            MS(3,"You can just \"say Plate it in <metal>\"");

            order_status = OPLATE;
            return 0;
        }        
        else
        {
            MS(1,"What colour do you want the "+ o_decor +" "+ o_style +
                " mail to be?");
            MS(2,"Right now, I have these colours: "+ 
                COMPOSITE_WORDS(FORGE_MASTER->query_colours()) +".");
            MS(3,"You can just \"say Please make it <colour>\"");
        
            order_status = OCOLOUR;
            return 0;
        }
    }
    
    if (order_status == OPLATE)
    {
        str = lower_case(str);
        sscanf(str, "plate it in %s", arg);
        if (!strlen(arg))
            return 0;
    
        if (member_array(arg, FORGE_MASTER->query_plating()) == -1)
        {
            MS(2,"I can add "+ COMPOSITE_WORDS(FORGE_MASTER->query_plating())+
                " plating to your armour.");
            MS(3,"You can just \"say Plate it in <metal>\"");
            MS(2,"Or, if you do not like my selection, "+
		"you may \"cancel order\".");
            return 0;
        }
        
        o_plate = arg;
        o_colour = "white";

        MS(1,"An excellent choice! Now, what material do you want your "+ 
            FORGE_MASTER->query_armour_style(o_style) +" lined with? ");
        MS(2,"The following materials are available: "+ 
            (COMPOSITE_WORDS(FORGE_MASTER->query_linings())) +".");
        MS(3,"You can just \"say Line it with <material>\"");

        order_status = OLINING;
        return 0;
    }

    if (order_status == OCOLOUR)
    {
        str = lower_case(str);
        sscanf(str, "please make it %s", arg);
        if (!strlen(arg))
            return 0;

        if (member_array(arg, FORGE_MASTER->query_colours()) == -1)
        {
            MS(1,"That is a very unusual colour...I don't have it right now.");
            MS(2,"Are you sure you wouldn't want your "+ o_style +
                " mail "+ o_decor +" with one of the following colours "+ 
                COMPOSITE_WORDS(FORGE_MASTER->query_colours()) +"?");
            MS(3,"You can just \"say I want it <colour>\", or "+
		"simply cancel your order.");
            return 0;
        }
        
        o_colour = arg;
      
        MS(1,"An excellent choice! Now, what material do you want your "+ 
            FORGE_MASTER->query_armour_style(o_style) +" lined with? ");
        MS(2,"The following materials are available: "+ 
            (COMPOSITE_WORDS(FORGE_MASTER->query_linings())) +".");
        MS(3,"You can just \"say Line it with <material>\"");

        order_status = OLINING;
        return 0;
    }

    if (order_status == OLINING)
    {
        sscanf(lower_case(str), "line it with %s", arg);
        if (member_array(arg, FORGE_MASTER->query_linings()) == -1)
        {
            MS(1, "That is an unusual fabric. I'm not familiar with it.");
            MS(2, "Please \"say Line it with <material>\", using one "+
                " of the following: "+ 
                COMPOSITE_WORDS(FORGE_MASTER->query_linings()) +"?");
            return 0;
        }

        o_lining = arg;

        MS(1,"That is the final option. We're done!");
       
        if (o_plate)
        {
            MS(2,"You have ordered the "+ o_plate +"-"+ o_decor +
                " "+ FORGE_MASTER->query_armour_style(o_style) +" "+
                "lined with "+ o_colour +" "+ o_lining +" for your "+ 
                o_worn +".");
        }
        else
	{
            MS(2,"You have ordered the "+ o_colour +"-"+ o_decor + 
                " "+ FORGE_MASTER->query_armour_style(o_style) +" "+
                "lined with "+ o_colour +" "+ o_lining +" for your "+ 
                o_worn +".");
	}

        MS(3,"I'll have it ready for you in a moment or two...");
        set_alarm(30.0, 0.0, &finish_clothing());
        order_status = OWORKING;
        return 0;
    }

    return 0;
}

public int
do_pay(string str)
{
    int *result;

    if (orderer != TP)
        return NF("You haven't ordered any armour, "+
	    "so you have nothing to pay for.\n");

    if (order_status != OFINISHED)
        return NF("Your armour is not yet finished.\n");

    result = pay(clothing->query_value(), TP);
    if (sizeof(result) == 1)
       return 0;

    if (!CAN_SEE(merchant, TP))
    {
	merchant->command("say The spirits.. they speak to me...");
	return 1;
    }

    say(QCTNAME(TP) + " pays for "+ POSSESS(TP) +" order.\n");
    write("You pay for your order.\n");
    write("You get your "+ clothing->short()+".\n");

    clothing->move(TP, 1);
    SCROLLING_LOG("/d/Avenir/log/bazaar/armshop", TP->query_name() + 
        " bought "+ clothing->short());

    order_status = ONONE;
    reset_order();

    return 1;
}             

/* Code for repairing armours based on Bubba in Gelan by Maniac */

public int
do_cost(string str)
{
    object *armour;
    int cond, rep, price;

    if (!strlen(str))
	return notify_fail("Cost estimate which armour?\n");

    if (!present(merchant))
        return NF("The armourer is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (orderer || merchant->query_attack())
        return NF("They are too busy.\n");

    write("You ask about the price to fix your "+ str +".\n");
    say(QCTNAME(TP) + " asks the price for fixing " +
	TP->query_possessive() +" "+ str +".\n", TP);

    if (!CAN_SEE(merchant, TP))
    {
	merchant->command("say The spirits.. they speak to me...");
	return 1;
    }

    if (!sizeof(armour = FIND_STR_IN_OBJECT(str, TP)))
    {
	msto("Which armour?", TP);
	return 1;
    }

    if (sizeof(armour) > 1)
    {
	msto("Be more specific, which one do you want appraised?", TP);
	return 1;
    }

    if (!(armour[0]->check_armour()))
    {
	msto("That is not really an armour.", TP);
	return 1;
    }

    /* blacksmith can't fix broken armours */
    if (armour[0]->query_prop(OBJ_I_BROKEN))
    {
	msto("I cannot repair the " + armour[0]->short() + ".", TP);
	return 1;
    }

    cond = armour[0]->query_condition();
    rep = armour[0]->query_repair();

    if (!cond)
    {
	msto("That "+armour[0]->short()+" is not in need of repair.", TP);
	return 1;
    }

    price = max((cond / 2 + 2 - rep) * 12,
	armour[0]->query_repair_cost());

    if (rep)
    {
	if (F_LEGAL_ARMOUR_REPAIR(rep + 1, cond))
	{
	    msto("I will charge you "+
		MONEY_TEXT_SPLIT(price) +" to fix.", TP);
	}
	else
	{
	    msto("No further repairs to the "+
		armour[0]->short() +" are possible.", TP);
	}

	return 1;
    }

    msto("I can repair your "+ armour[0]->short() +
	" for about "+ MONEY_TEXT_SPLIT(price) +".", TP);

    return 1;
}

/* Action : 
   Carry out fixing of an armour until it can't be fixed further 
*/
public int
do_fix(string str)
{
    object *armour;
    int *money_arr, cond, rep, price;

    if (!strlen(str))
	return notify_fail("Fix which armour?\n");

    if (!present(merchant))
        return NF("The armourer is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (orderer || merchant->query_attack())
        return NF("They are too busy.\n");

    write("You ask "+ merchant->query_the_name(TP) +
	" to repair your "+ str +".\n");
    say(QCTNAME(TP) + " asks " + QTNAME(merchant) +" to fix " +
	TP->query_possessive() +" "+ str +".\n", TP);

    if (!CAN_SEE(merchant, TP))
    {
	merchant->command("say The spirits.. they speak to me...");
	return 1;
    }

    if (!sizeof(armour = FIND_STR_IN_OBJECT(str, TP)))
    {
	msto("Repair which armour?", TP);
	return 1;
    }

    if (sizeof(armour) > 1)
    {
	msto("Be more specific, which armour do you want repaired?", TP);
	return 1;
    }

    if (!armour[0]->check_armour())
    {
	msto("That doesn't look like a piece of armour to me...", TP);
	return 1;
    }

    /* blacksmith can't fix broken armours */
    if (armour[0]->query_prop(OBJ_I_BROKEN))
    {
	msto("I cannot repair the " + armour[0]->short() + ".", TP);
	return 1;
    }

    cond = armour[0]->query_condition();
    rep = armour[0]->query_repair();

    if (!cond)
    {
	msto("Your "+ armour[0]->short() +" is not in need of repair.", TP);
	return 1;
    }

    if (rep && !(F_LEGAL_ARMOUR_REPAIR(rep + 1, cond)))
    {
	msto("That item cannot be repaired any further.", TP);
	return 1;
    }

    price = max((cond / 2 + 2 - rep) * 12,
	armour[0]->query_repair_cost());

    /* Try to take the money */
    if (sizeof(money_arr = pay(price, TP)) == 1)
    {
	msto("You cannot afford the repairs.", TP);
	return 1;
    }

    write("You give " + merchant->query_the_name(TP) +
	" your "+ armour[0]->short() +".\n");
    say(QCTNAME(TP) + " gives "+ QTNAME(merchant) +" "+ 
	TP->query_possessive() +" "+ armour[0]->short() +".\n");

    string pay_text = text(exclude_array(money_arr,
	    sizeof(money_types), sizeof(money_types) * 2 - 1));
    string get_text = text(exclude_array(money_arr, 0,
	    sizeof(money_types) - 1));

    write("You pay "+ pay_text +".\n");
    if (strlen(get_text))
        write("You get "+ get_text +" in return.\n");

    /* carry out the fixing */
    while (F_LEGAL_ARMOUR_REPAIR(rep + 1, cond))
    {
	int cur = armour[0]->query_repair();
	armour[0]->set_repair(cur + 1);
	rep++;
    }

    if (!armour[0]->query_value())  /* broken */
    {
	merchant->command("emote fails to repair the "+
	    armour[0]->short() +".");
	msto("I couldn't repair your armour.", TP);
	merchant->command("emote gives the "+ armour[0]->short() +" back.");
    }
    else
    {
	merchant->command("emote repairs the " + armour[0]->short() + ".");
    }

    merchant->command("emote gives the "+ armour[0]->short() +" back.");
    return 1;
}

public void
init(void)
{
    ::init();

       /* Armour Ordering */
    add_action(order,   "order");
    add_action(do_pay,  "pay");
    add_action(do_say,  "say");
    add_action(cancel,  "cancel");
       /* Armour Repairs  */
    add_action(do_cost, "cost");
    add_action(do_fix,  "fix");
}

