/* Armour Shop of Last
 * /d/Terel/last/ashop.c
 * 
 *
 * Coded by Shinto, March 98
 *
 *  Modifications:
 *    Lilith Feb 2022: added ROOM_I_INSIDE prop
 *    Lilith Mar 2022: added armour repair services
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"

#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>

#define STORE_ROOM "/d/Terel/last/astore"
#define STDARMFILE "/std/armour"

object orderer;

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Last Armour Shop");
    set_long("You are in the armour shop of Last. Various types of armours "+
      "can be seen lying about the shop, some even hanging behind "+
      "the counter. There is a sign on the wall with some directions. "+
      "The entrance of the store is to the north, back out to the road.\n");

    set_shop_name("Last Armour Shop");
    set_keeper_file(LAST_DIR + "npc/corman");
    set_hated_race(({"goblin", "ogre", "minotaur"}));
    set_suspected_race(({"gnome","hobbit", "kender"}));
    set_favoured_race(({"human","dwarf","elf"})); 
    add_item(({"door"}),
        "The door is probably leading into the storeroom of the "+
        "shop. The door is open but even looking at that door " +
        "gains a stern stare from the shopkeeper. ");
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_prop(ROOM_I_INSIDE, 1);
	add_exit(LAST_DIR+"lroad5","north",0);
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy armour for gold and get copper back\n"
      + "    buy armour for gold coins\n"
      + "    sell armour for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn.\n"
      + "    sell armour, sell second armour, sell armour 2, sell two armours\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all armours available in the store, the\n"
      + "    correct syntax is: 'list armours' also works.\n"
	  + "\n"
	  + "Now offering armour repair services:\n"
      + "  If you want to repair an armour, just <fix [armour]>.\n"
	  + "  If you want to estimate repair costs, just <cost [armour]>.\n"
      + "\n";
}


int
shop_hook_allow_sell(object ob)  
{
    if (function_exists("create_object", ob) != STDARMFILE )
    {
        keeper->command("say I'm only interested in armours.");
        NF("");
        return 0;
    }
    return 1;
}
int
shop_hook_allow_buy(object ob)  
{
    return 1;
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
	return notify_fail("Cost estimate which armour?\n");

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


public void
init(void)
{
    ::init();

    /* Armour Repairs  */
    add_action(do_cost, "cost");
    add_action(do_fix,  "fix");
}


