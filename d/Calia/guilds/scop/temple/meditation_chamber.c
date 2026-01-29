
/*
 * meditation_chamber.c
 *
 * Meditation chamber for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/guild_support";
// inherit "/lib/shop";
// inherit "/d/Genesis/gems/gem_shop";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>

#include "defs.h"

// #define STOREROOM   "/d/Calia/guilds/scop/temple/gemstore"

// Prototypes
// int query_acceptable_gem(object gem);


// object clerk;

void
create_room()
{
    set_short("Meditation chamber");
    set_long("This small chamber has many small altars with kneeling "+
        "cushions in front of them that you can <kneel> upon to "+
        "<estimate> your stats and <set> your preferences. You may also "+
        "<list guilds> here as well. There refectory lies to the west.\n");

    add_item("refectory","The refectory lies back to the west.\n");
    add_item(({"altar","altars","small altar","small altars"}),
        "There are many small altars in this chamber made of white "+
        "marble. In front of each of the altars is a small kneeling "+
        "pillow which you could <kneel> on.\n");
    add_item(({"pillow","pillows","kneeling pillow","kneeling pillows",
        "small pillow","small pillows","small keeling pillow",
        "small kneeling pillows"}),"In front of each of the small altars "+
        "there is a small kneeling pillow. They are red in colour and feel "+
        "very comfortable.\n");
    add_item("floor", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards. The floor is "+
      "quite comfortable to walk on.\n");
    add_item(({"wall","walls"}), "The walls here are covered in a polished "+
      "wood, light brown, almost red, in colour. They are extremely smooth "+
      "to the touch.\n");
    add_item("ceiling", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards.\n");
    add_item("tapestry", "This finely woven tapestry hangs from a rod of "+
      "finely wrought iron, and sways gently in the breezes coming from the "+
      "garden.  The tapestry depicts a dark-eyed male human, dozing quietly "+
      "against a black obelisk. Behind him, and filling much of the "+
      "tapestry, are what can only be his dreams, ever changing in a "+
      "blending of colors and light.  Images of dolphins, a man "+
      "silhouetted in the mouth of a watery cave, lovers embracing, and "+
      "a child, walking in the light can be seen.\n");
    add_item("obelisk", "The black stone of the obelisk shimmers faintly.\n");
    add_item("dolphins", "The dolphins look remarkably similar to those "+
      "found in the Thalassian Sea, and seem to revel in the freedom of "+
      "the water.\n");
    add_item("lovers", "The lovers are engaged in a tender kiss, and "+
      "around their shoulders is draped a garland of hanwi flowers, "+
      "the sacred flower of Spiritbinding.\n");
    add_item("child", "The child seems to turn his eyes to meet your gaze, "+
      "and holds a scroll for you to see.  The scroll reads:\n\n"+
      "Sometimes dreams are wiser than waking.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

//    config_default_trade();
//    create_gem_shop();
//    set_store_room(STOREROOM);
    
//    clerk = clone_object(SPIRIT_NPCS+"gem_clerk");
//    clerk->move(TO);

    add_exit(SPIRIT_TEMPLE+"refectory","west",0,1);
    create_guild_support();
}

void
gs_hook_start_meditate()
{
    write("You kneel down and close your eyes. A feeling of great "+
        "ease and self control falls upon you. You block off "+
        "your senses and concentrate solely upon your own mind. You "+
        "find yourself able to <estimate> your different preferences "+
        "and <set> them at your own desire.\nJust <rise> when you "+
        "are done meditating.\n");
    say(QCTNAME(this_player())+" kneels down and starts to meditate.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface "+
        "of your consciousness. You exhale and feel very relaxed as "+
        "you stand up.\n");
    say(QCTNAME(this_player())+" comes out of a trance and stands up.\n");
}
 
int 
query_prevent_snoop()
{
    return 1;
}

/*
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
*/

/*
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
*/

/*
 * Function name:    shop_hook_filter_sell
 * Description:      Default filter function
 *                   Checks if player can sell item to shop
 * Argument:         object ob - the object to check
 * Returns:          The fail message or 1 if shop does not buy,
 *                   0 else
 */
 
/*
mixed
shop_hook_filter_sell(object ob)  
{
    if ((ob->id("gem") || ob->id("jewel")) && query_acceptable_gem(ob))
        return 0;
    else
        return 1;
}
*/

/*
int
query_acceptable_gem(object ob)
{
    if(ob->id("yellow_topaz") ||
       ob->id("red_spinel") ||
       ob->id("black_pearl") ||
       ob->id("white_pearl") ||
       ob->id("iridescent_opal") ||
       ob->id("black_onyx") ||
       ob->id("lambent_moonstone") ||
       ob->id("orange-red_garnet") ||
       ob->id("black_diamond") ||
       ob->id("glittering_diamond") ||
       ob->id("pink_coral") ||
       ob->id("striped_chalcedony") ||
       ob->id("red_carnelian") ||
       ob->id("shining_bloodstone") ||
       ob->id("yellow_beryl") ||
       ob->id("yellow_amber") ||
       ob->id("purple_amethyst") ||
       ob->id("blue_lapis lazuli"))
     {
       return 1;
     }
     return 0;
}
*/

/*
int
shop_hook_allow_sell(object ob)  
{
    if(!present(clerk, this_object()))
    {
        NF("The shopkeeper isn't here.\n");
        return 0;
    }

    if (shop_hook_filter_sell(ob))
    {
        clerk->command("stsay I am only interested in gems that serves the needs of the Clergy!");
        NF("");
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
*/

/*
 * Function name: sell_it
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:	  An array with the objects sold
 */
 
/*
object *
sell_it(object *ob, string str, int check) 
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    call_other(store_room, "load_me"); // Make sure store room is loaded 

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
	  // Save price if ob destructed in move 
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
*/

/*
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
*/

/*
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

        // If you don't feel greedy you can shorten the calculation above.
        //Fixed bug here, there was no check to see if buyer could pay the
        //price before moving the object, causing problems because of the heap
        //nature of gems. Bishop, 10. April 2004.
        if (sizeof(arr = pay(price, this_player(), str2, 1, 0, str3)) == 1)
        {
            shop_hook_buy_cant_pay(ob[i], arr);
            continue;
        }

        if (err = ob[i]->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob[i], err);
                continue;
        }

        if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
	  {
	      ob[i]->move(store_room, 1);
            shop_hook_buy_cant_pay(ob[i], arr);
                continue;  // pay() can handle notify_fail() call 
        }

        // Detect if there was a move error. 
	  if (error = arr[sizeof(arr) - 1])
	  {
	      if (error < -1)
	      {
            // Couldn't take the money from player, the coins were stuck 
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
	// Well, we don't want to let a player accidentily buy too much :) 
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
		text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
    return bought;
}
*/

void
init()
{
    ::init();
    init_guild_support();
//    init_gem_shop();
    add_action(gs_meditate,"kneel");
}
