// Alchemist's shop in Apothecary complex
// file name:   /d/Avenir/common/bazaar/intr/p&s.c
// creator(s):  Lilith, 27 Feb 1997
// revised:     Lilith, 20 Mar 1997   
// purpose:     This is the room where potions and scrolls are sold.
// note:        Some functions borrowed from Gondor's potion shop.
// bug(s):
// to-do:

#pragma save_binary
#pragma strict_types

inherit "/d/Avenir/common/lib/shop";
#include "../bazaar.h"
#include <cmdparse.h> 

#define STRM   "/d/Avenir/common/bazaar/intr/p&sstore"
#define PMS    50
public  int    do_value(string args);

void
create_shop()
{
    seteuid(getuid(TO));    
    config_default_trade();

    set_shop_name("Sybarus Bazaar Alchemy Shop");
    set_short("Alchemist's section of the Apothecary Shop");
    set_long("This room isn't much larger than a closet. Shelves "+
        "lining the walls are covered with stacks of papers, odd "+
        "jars, and empty and broken bottles. There is a large "+
        "counter bisecting the room, and behind it is a worktable clut"+
        "tered with vials of liquid and numerous rolled-up scrolls, "+
        "glass tubes and measuring tools, mortar and pestle, inkwell, "+
        "quills, and vellum. Also behind the counter is a large glass "+
        "case containing a well-organized array of vials and rolled "+
        "parchments. A small, locked chest is bolted to the "+
        "countertop, and a sign written in intricate, curling script "+
        "has been propped against it.\n");
    
    AI(({"case", "glass case"}), "This case contains several vials and "+
        "scrolls. It is likely that it contains the stock available for "+
        "sale.\n");
    AI(({"chest", "small chest", "locked chest"}), "This chest is made "+
        "entirely of iron. It is bolted onto the counter, probably to "+
        "prevent it from being taken. It is locked.\n");
    AI(({"worktable", "table"}), "It is cluttered with numerous items "+
        "which lend themselves to potion-making and scroll-writing.\n");
    AI(({"bottles","bottle"}),"The bottles are scattered about the "+
        "shelves, some broken and others intact. Some house the remains "+
        "of various coloured liquids.\n");
    AI(({"vial", "vials"}), 
        "These vials contain vividly-coloured fluids.\n");
    AI(({"tubes", "glass tubes"}), "Fluids bubble through these "+
        "delicate, contorted glass tubes.\n");
    AI(({"mortar", "pestle"}), "It looks like someone was using the "+
        "pestle to grind some kind of herb up in the mortar.\n");
    AI(({"inkwell", "pen", "vellum"}), 
        "The tools of a scribe's trade.\n");
    AI(({"tool", "tools", "measuring tools"}),
        "They are small, and metallic and glass. Some look like they "+
        "might be weights for use in a balance.\n");
    AI(({"liquid", "liquids", "fluid", "fluids"}), 
        "There are several different colored liquids. Some of the "+
        "liquids are clear, others opaque. Some contain two colors "+
        "that remain separated, others swirl about seeming to fluctuate.\n" );
    AI(({"shelf","shelves","wall","walls"}),"Wooden shelves cover all the "+
        "walls of this room, upon which are scattered papers, bottles and "+
        "jars.\n");
    AI(({"jar","jars"}),"The jars are mostly closed and painted black.\n");
    AI(({"scroll","scrolls"}),"They are made of rolled up vellum.\n");
    AI(({"paper","papers"}),"The papers scattered around the shelves are "+
        "mostly covered with esoteric formulae with notes written down in "+
        "an indecipherable shorthand.\n");
    AI(({"curtain","doorway", "west"}),
        "The curtain hanging over the doorway is of a deep, blue velvet.\n");
    AI(({"counter", "countertop", "mahogany"}),
        "The counter is of polished mahogany. A sign rests on top of it.\n");
    AI(({"sign", "script"}),"@@exa_sign");
    ACI(({"sign","script"}), "read", "@@exa_sign"); 
   
    set_keeper_file(NPC + "alchemist");
    set_store_room(STRM);
    set_money_greed_buy(105);
    set_money_greed_sell(125);

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_prop(ROOM_I_HIDE, 25);   /* easier to hide */

    add_exit(INTR + "apoth1", "west", 0);

}
 
/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();
    init_shop();

    add_action(do_value, "value");
}

public string
exa_sign()
{
   return "\nWelcome to Sybarus Bazaar Alchemy Shop!\n"+
          "\n          Highest Quality        \n"+
          "\n    Potions and Magical Scrolls  \n"+
          "\n       Bought and Sold Here.     \n\n";
}

public int
do_read(string str)
{
    return 0;
}


int
potion_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/potion");
}

/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns: 	  The price
 */
int
query_buy_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    if (ob->id("potion"))
        return 2 * ob->query_potion_value() * (query_money_greed_buy() +
	    15 - this_player()->query_skill(SS_TRADING) / 4 +
	    random(15, seed)) / 100;

    if (ob->id("scroll"))
        return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
            15 - this_player()->query_skill(SS_TRADING) / 4 +
	    random(15, seed)) / 100;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 100;
}

/*    
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:	  ob - The object
 * Returns:	  The price
 */
int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    if (ob->id("potion"))
        return ob->query_potion_value() * 100 / (query_money_greed_sell() +
	15 - this_player()->query_skill(SS_TRADING) / 3 + 
	random(15, seed + 1)); /* Use another seed than on buying */

    if (ob->id("scroll"))
        return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
            15 - this_player()->query_skill(SS_TRADING) / 4 +
	    random(15, seed)) / 100;
}

static void
shop_hook_potion_too_weak()
{
    notify_fail(QCTNAME(keeper) +" refuses to buy the potion, believing "+
        "it is of inferior quality.");
}

/*
 * Function name:    shop_hook_filter_sell
 * Description:      Default filter function
 *                   Checks if player can sell item to shop
 * Argument:         object ob - the object to check
 * Returns:          The fail message or 1 if shop does not buy,
 *                   0 else
 */
mixed
shop_hook_filter_sell(object ob)  
{
    if (strlen(function_exists("query_strength", ob)) && 
	(ob->query_strength() < PMS))
        return QCTNAME(keeper) +" refuses to buy the potion, "+
               "believing it is of inferior quality.\n";
    if (ob->id("scroll") || potion_filter(ob))
        return 0;
    else
        return 1;
}

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:	  An array with the objects sold
 */
object *
sell_it(object *ob, string str, int check) 
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); /* Make sure store room is loaded */

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
	if (!shop_hook_allow_sell(ob[i]))
	    continue;

	if (check && (ob[i]->query_worn() ||
		      ob[i]->query_wielded()))
	{
	    shop_hook_sell_worn_or_wielded(ob[i]);
	    continue;
        }
    
	if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
	{
	    shop_hook_sell_no_sell(ob[i], tmp);
	    continue;
	}

	/* Save price if ob destructed in move */
	price = query_sell_price(ob[i]);

        if (price <= 0)
	{
	    shop_hook_sell_no_value(ob[i]);
	    continue;
        }

        if (err = ob[i]->move(store_room))
    	{
	    shop_hook_sell_object_stuck(ob[i], err);
	    continue;
    	}

        if (price > 0)
	{
            tmp_arr = calc_change(price, null, str);
            for (k = 0; k < sizeof(value_arr); k++)
                value_arr[k] += tmp_arr[k];

	    sold[j] = ob[i];
            j++;
	    if (j >= 20)
        	break;
    /*
     * Only let people sell 20 objects at once and hopefully we wont get
     * those too long evaluation problems.
     */
	}
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
        change_money(null_arr + value_arr, this_player());
	shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}


public int
do_value(string args)
{
    object *item;
    int i, price, num, *arr;
    num = sizeof(query_money_types());
    if (!strlen(args))
    {
        notify_fail("Value what?");
        return 0;
    }

    item = FIND_STR_IN_OBJECT(args, TP);
    if (!sizeof(item))
    {
        notify_fail("You don't have that!");
        return 0;
    }
    for(i = 0; i < sizeof(item); i++)
    {
        if (!shop_hook_allow_sell(item[i]) ||
            (item[i]->query_potion_value() == 0) ||
            (item[i]->query_prop(OBJ_M_NO_SELL)))
        {
            shop_hook_value_not_interesting(item[i]);
            continue;
        }
        price = query_sell_price(item[i]);
        arr = give(price, TP, "", 1);
        shop_hook_value_held(item[i], text(arr[num .. 2 * num -1]));
    }
    return 1;
}

