/* The witch's helper, Ten Alders
 * coded by Amelia, 4/12/97
 * Modified to be used in Re Albi's village
 * by Marisol 92/10/98)
*/

inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "defs.h"

#define PRICE_LAMP  450
#define PRICE_BACKPACK 600
#define PRICE_TORCH 100
#define PRICE_OIL 250

void
create_emerald_monster()
{
    set_name("fern");
    add_name("storekeeper");
    add_name("ovejuno_storekeeper");
    set_gender(G_MALE);
    add_adj(({"wiry", "weathered"}));
    set_long("A wiry weathered man, who looks like a "+
        "craftsman. He has hands scarred and calloused from working "+
        "with leather and tools.\n");

    add_prop(OBJ_M_NO_ATTACK, "You feel this man is protected "+
        "by the wizards of this region.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The man holds up "+
        "his hand palm outward and shouts loudly, Avert!!\n"+
        "The spell falls harmlessly on empty air.\n"); 

    set_act_time(60);

    set_chat_time(90);
    add_act("emote pokes a hole in a piece of leather with an awl.");
    add_act("emote polishes a new backpack, getting it ready for sale.");
    add_chat("I only sell new equipment here. Read the sign, if you can " +
        "read, that is.");
    add_act("emote hums softly as he works.");
}

public int
try_to_purchase(string path, int price)
{
    object ob;

    if (!MONEY_ADD(this_player(), -price))
    {
        switch (random(3))
	{
  	    case 0:
        	command("say You can't afford that much!");
        	command("poke " + OB_NAME(this_player()));
        	break;
            case 1:
		command("say Get out of my store, "+
		  "you bum!");
		command("peer "+ OB_NAME(this_player()));
		break;
            default:
    	    	command("hmm");
    	    	command("say I'm not doing charity!");
    	    	command("say No money no honey.");
    	    	command("nudge " + OB_NAME(this_player()));
                break;
	}

        return 0;
    }

    write("You pay " + query_the_name(this_player()) + ".\n");
    say(QCTNAME(this_player()) + " pays " + QTNAME(this_object()) + ".\n");

    setuid();
    seteuid(getuid());

    ob = clone_object(path);
    ob->move(this_object(), 1);

    /* Should do some checking to see if this fails */

    command("give " + OB_NAME(ob) + " to " + OB_NAME(this_player()));
    return 1;
}

/*  buy_equip:  allows a player to buy equipment in the store
 *  arguments:  string str
 *              = what the player wants to buy
 *  returns:    int (1 if is successful/0 if not)
 *  npcs:       storekeeper must be present
 */

int
buy_equip(string str)
{
    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    switch (str)
    {
	case "lamp":
	case "terra cota lamp":
	    try_to_purchase(LAMP, PRICE_LAMP);
	    break;
	case "backpack":
	case "pack":
	    try_to_purchase(BACKPACK, PRICE_BACKPACK);
	    break;
	case "oil":
	case "oil flask":
	    try_to_purchase(OIL, PRICE_OIL);
	    break;
	case "torch":
	case "large torch":
	    try_to_purchase(TORCH, PRICE_TORCH);
	    break;
	default:
	    command("say I have no " + str + " in stock.");
	    break;
    }

    return 1;
}

int
list_equip(string str)
{
    if ((str == "equipment") || (str == "equip"))
    {
        command("say I have the following items in "+
          "stock:\nBackpacks, lamps, oil flasks and torches.");
        command("emote points at the sign.");
        command("say Read the sign for current prices.");
        return 1;
    }

    notify_fail("List what? Maybe you should read the sign.\n");
    return 0;
}                                                                

void
init_living()
{
    ::init_living();
    add_action(buy_equip, "buy");
    add_action(list_equip, "list");
}

