/* created by Aridor 06/21/93 */
// March 30, 2000 Commented out cloning the jeweler, as there is
// no jeweler, the store is supposed to be closed, but something
// was loading up this room and spamming the error logs.
// Gwyneth
//
// Added gem store features from /d/Avenir/common/bazaar/intr/lapidary.c
// Arman 9/11/2003


#pragma save_binary
#pragma strict_types

inherit "/d/Avenir/common/lib/shop";
inherit "/d/Genesis/gems/gem_shop";

#include "../local.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>

#define STRM   "/d/Krynn/solamn/palan/city/jewelstore"

void
create_shop()
{
    seteuid(getuid(TO));    
    config_default_trade();
    create_gem_shop();
    set_store_room(STRM);
    set_keeper_file("/d/Krynn/solamn/palan/living/jeweler_npc");

    set_shop_name("Jeweler's Shop in Palanthas");
    set_short("Jeweler's Shop in Palanthas");
    set_long("This is the jeweler's shop. Exquisite furnishings gleam in " +
                "the sunlight coming in through the windows. Several displays " +
                "show sparkling gems and delicately crafted pieces of jewelery. " +
                "A sign sits on one of the display cases.\n");
    add_item(({"sign"}), "@@exa_sign");
    add_cmd_item(({"sign"}), "read", 
        "@@exa_sign"); 
    add_item(({"case", "display case", "displays", "glass case", "display" }),
        "@@do_case");    

    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_exit(ROOM + "street4","southwest",0,1);
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
    init_gem_shop();
}

public string
exa_sign()
{
   return "\nThe Palanthian Gem and Jewelry Store!\n"+
          "          HighestQuality        \n"+
          "        GemstonesAndJewels      \n"+
          "        BoughtAndSoldHere.    \n\n"+
          "       FeelFreeToExamineThe     \n"+
          "       DisplaysForAnything      \n"+
          "       ThatCatchesYourEye!!   \n\n"+
          "     KenderMustStandTwoFeet  \n" +
          "           FromDisplays!\n\n";
}

public int
do_read(string str)
{
    return 0;
}

string
do_case()
{    
    do_list("all");
    return "You stare through the thick glass.\n";
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
    if (ob->id("gem") || ob->id("jewel"))
        return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	    15 - this_player()->query_skill(SS_TRADING) / 4 +
	    random(15, seed)) / 150;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	15 - this_player()->query_skill(SS_TRADING) / 4 +
	random(15, seed)) / 150;
}

int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    if (ob->id("gem") || ob->id("jewel"))
        return ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	    15 - this_player()->query_skill(SS_TRADING) / 3 +
	    random(15, seed)) / 100;
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
    if (ob->id("gem") || ob->id("jewel"))
        return 0;
    else
        return 1;
}

int
shop_hook_allow_sell(object ob)  
{


    if (shop_hook_filter_sell(ob))
    {
        NF("The shopkeeper says: I'm sorry, I do not trade in anything but "+
            "jewels.\n");
        return 0;
    }

    if (ob->query_value() > money_give_max)
    {
        if (ob->num_heap() > 1)
        {
            NF("The shopkeeper says: I'm afraid I cannot afford to pay "+
                "that much.\nThe shopkeeper says: Perhaps you could try "+
                "to sell the "+ob->short()+" singly.\n");
            return 0;
        }
        write("The shopkeeper says: I'm afraid I cannot afford to pay "+
            "the full value.\n");
    }
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
        notify_fail("You don't have that!\n");
        return 0;
    }
    for(i = 0; i < sizeof(item); i++)
    {
        if (!shop_hook_allow_sell(item[i]) ||
            (item[i]->query_prop(OBJ_M_NO_SELL)))
        {
            write("The shopkeeper finds it uninteresting. If you "+
            "want to value a gemstone, try 'unkeeping' it first.\n"); 
            continue;
        }
        price = query_sell_price(item[i]);
        arr = give(price, TP, "", 1);
        shop_hook_value_held(item[i], text(arr[num .. 2 * num -1]));
    }
    return 1;
}

#ifdef _USE_LOCAL_BUY_IT
/*
 * Function name: buy_it
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 * Returns:       1 on sucess
 */
object *
buy_it(object *ob, string str2, string str3) 
{
    int price, i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
        {
            shop_hook_buy_no_buy(ob[i], tmp);
            continue;
        }

        price = query_buy_price(ob[i]);

        /* If you don't feel greedy you can shorten the calculation above. */

        if (err = ob[i]->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob[i], err);
                continue;
        }

        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
	  {
	      ob[i]->move(store_room, 1);
            shop_hook_buy_cant_pay(ob[i], arr);
                continue;  /* pay() can handle notify_fail() call */
        }

        /* Detect if there was a move error. */
	  if (error = arr[sizeof(arr) - 1])
	  {
	      if (error < -1)
	      {
            /* Couldn't take the money from player, the coins were stuck */
	          shop_hook_buy_magic_money(ob[i]);
	          ob[i]->move(store_room, 1);
		    continue;
	      }
        }

        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];

        bought[j] = ob[i];
        j++;
        if (j >= 1)
            break;
	/* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
		text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
    return bought;
}
#endif /* _USE_LOCAL_BUY_IT */
