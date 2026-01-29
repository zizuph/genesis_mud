/* Armourer Shop of Fort Sybarus
 * /d/Avenir/common/outpost/armourer.c
 * Created by: Lilith, April 2022
 * Revisions:
 *
 */

#pragma strict_types

#include "outpost.h"

inherit OUTPOST +"fort_base";
inherit "/lib/trade";

#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

private object keeper, orderer;

#define SEE_WEST   ({ OUTPOST + "smithy", })

string 
west_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_WEST); i++)
    if((room = find_object(SEE_WEST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "You can see "+ COMPOSITE_LIVE(live) +
       " east of here, where the weaponsmiths are hard "+
       "at work.";
  }
  return "To the east are the weaponsmiths and a stairwell "+
         "leading up.";
}


public void
reset_fort_room(void)
{
    if (!keeper)
    {
       keeper = clone_object(MON + "armourer");
    }

    if (!present(keeper))
       keeper->move_living("X", this_object());
}

void
create_fort_room()
{
    set_short("the armourers of Fort Sybarus");
    set_long("This room has been cut into the stone of the cavern, "+
        "deep beneath the fortress above. "+
        "The walls are fairly smooth and dark, with crystal and copper "+
        "lamps hung at regular invervals casting excellent light upon "+
        "the female armourers hard at work outfitting the defenders "+
        "of Fort Sybarus. "+
        "There is a contraption made of chains and buckets "+
		"that hangs down into a hole in the floor. "+		
        "@@west_view@@\n"+
        "There is a sign on the wall with some instructions. "+
        "\n");

	add_exit("smithy",  "west", 0);
//	add_exit("assay_office", "east", 0);
	
	add_fort_room();
	add_exit_views();

    add_item(({"sign", "poster", "instructions"}), "@@exa_poster@@");
	add_cmd_item(({"sign", "poster", "instructions"}), "read",
	    "@@exa_poster@@");
    add_item(({"armourers", "female armourers", "female dwarves"}),
        "The armourers are all female dwarves, hard at work under the "+
        "watchful eye of the master armourer.\n");
    add_item(({"contraption", "buckets", "chains", "lift", 
	    "bucket lift", "bucket-lift", "hole", "hole in the floor"}),
        "This is a bucket-lift, a contraption designed to lift "+
        "and lower metals and ores between the foundry and "+
        "forges below and the smithy and armourer above.\n");
		
	config_default_trade();	

    reset_fort_room();
}

string
exa_poster()
{
    return "\n"
      + "               Fort Sybarus Armourer\n"
	  + "             --=====================--\n"
	  + " New defenders <report> to receive custom-fitted armours.\n"
	  + " Departing defenders, <return> your armours on the pile.\n\n"
	  + " No flirting with or distracting the armourers.\n\n\n"
	  + "Now offering armour repair services to the general public:\n"
      + "  If you want to repair an armour, try <fix [armour]>.\n"
	  + "  If you want an estimate of repair costs, try <cost [armour]>.\n"
      + "\n";
}

/* Code for repairing armours based on Bubba in Gelan by Maniac */

private void
ms(string str)
{
    keeper->command("say " + str);
}

private void
msto(string str, object who)
{
    keeper->command("say to "+ OB_NAME(who) + " " + str);
}


public int
do_cost(string str)
{
    object *armour;
    int cond, rep, price;

    if (!strlen(str))
	return notify_fail("Cost to repair which armour?\n");

    if (!present(keeper))
        return NF("The armourer is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (orderer || keeper->query_attack())
        return NF("They are too busy.\n");

    write("You ask about the price to fix your "+ str +".\n");
    say(QCTNAME(TP) + " asks the price for fixing " +
	TP->query_possessive() +" "+ str +".\n", TP);

    if (!CAN_SEE(keeper, TP))
    {
	keeper->command("say The spirits.. they speak to me...");
	return 1;
    }

    if (!sizeof(armour = FIND_STR_IN_OBJECT(str, TP)))
    {
	msto("Which armour?", TP);
	return 1;
    }

    if (sizeof(armour) > 1)
    {
	msto("Be more specific, which one do you want the repair cost for?", TP);
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

    if (!present(keeper))
        return NF("The armourer is not here now.\n");

    if (TP->query_attack())
        return NF("You are too busy.\n");

    if (orderer || keeper->query_attack())
        return NF("They are too busy.\n");

    write("You ask "+ keeper->query_the_name(TP) +
	" to repair your "+ str +".\n");
    say(QCTNAME(TP) + " asks " + QTNAME(keeper) +" to fix " +
	TP->query_possessive() +" "+ str +".\n", TP);

    if (!CAN_SEE(keeper, TP))
    {
	keeper->command("say The spirits.. they speak to me...");
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

    /* armourer can't fix broken armours */
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

    write("You give " + keeper->query_the_name(TP) +
	" your "+ armour[0]->short() +".\n");
    say(QCTNAME(TP) + " gives "+ QTNAME(keeper) +" "+ 
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
	keeper->command("emote fails to repair the "+
	    armour[0]->short() +".");
	msto("I couldn't repair your armour.", TP);
	keeper->command("emote gives the "+ armour[0]->short() +" back.");
    }
    else
    {
	keeper->command("emote repairs the " + armour[0]->short() + ".");
    }

    keeper->command("emote gives the "+ armour[0]->short() +" back.");
    return 1;
}

public int
not_defender(string str)
{
	
    if (!keeper)
    {
        write("The armourers ignore your attention-seeking "+
        "behavior.\n");
	    return 1;
    }		
    ms("You're not one of our brave defenders!");
    ms("Stop wasting our time or I'll call for the guards to deal "+
        "with you.");	
    return 1;	
}

	
public void
init(void)
{
    ::init();

    /* Armour Repairs  */
    add_action(do_cost, "cost");
    add_action(do_fix,  "fix");
	
	add_action(not_defender, "report");
	add_action(not_defender, "return");
	
}


