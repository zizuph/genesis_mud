
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
inherit "/d/Genesis/gems/gem_shop";
inherit "/d/Calia/guilds/scop/temple/gemshop_list";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>

#include "defs.h"

#define STOREROOM   "/d/Calia/guilds/scop/temple/gemstore2"

object clerk;

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

    config_default_trade();
    create_gem_shop();
    set_store_room(STOREROOM);
    
    clerk = clone_object(SPIRIT_NPCS+"gem_clerk");
    clerk->move(TO);

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

int
query_buy_price(object ob)
{
    if (ob->query_gem())
        return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
	    20 - this_player()->query_skill(SS_TRADING) / 4) / 150;
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
        NF("You can only trade gems here.\n");
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


void
shop_hook_list_object(object ob, int price)
{
    string str, mess;

    str = sprintf("%-25s", ob->query_gem_name());
    if (mess = text(split_values(price)))
        write(break_string(str + mess + ".\n", 75));
    else
        write(str + "That item wouldn't cost you much.\n");
}

int
shop_hook_buy_no_match(string str)
{
    write("Arial telepatically says: I don't have a "+str+"!\n");
    return 1;
}

int
shop_hook_buy_no_match_amount(string str)
{
    write("Arial telepatically says: I don't have that many "+str+"!\n");
    return 1;
}

int
shop_hook_bought_items(object *arr)
{
    string sname;
    int i, num;
    mapping temp,gemlist;

    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    clerk->command("emote rummages through her containers and" +
    " gets out "+COMPOSITE_DEAD(arr)+".");

    temp = restore_map(SPIRIT_OBJECTS+"buy_gem_log");
    gemlist = temp[TP->query_real_name()];

    for(i = 0; i < sizeof(arr); i++)
    {
        sname = arr[i]->query_gem_name();
        if(!mappingp(gemlist))
            gemlist = ([]);
        num = gemlist[sname];
        num--;
        gemlist += ([sname:num]);
    }

    temp += ([TP->query_real_name():gemlist]);
    save_map(temp,SPIRIT_OBJECTS+"buy_gem_log");
   
    write("Arial telepatically says: It's been a pleasure dealing "+
        "with you.\n");
    write("Arial gives you "+COMPOSITE_DEAD(arr)+".\n");
    return 1;
}

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
        price = query_buy_price(ob[i]);
 
        if (err, ob[i]->move(this_player()))
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
            /* We don't want the money so no move error to us, if there was one
               it was because the player couldn't hold all coins, and if so the
               drop text is already written, but the deal is still on :) */
        }
 
        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];
 
        bought[j] = ob[i];
        j++;
        if (j >= 100)
            break;
        /* Well, we don't want to let a player accidentily buy too much :) */
    }
 
    bought = bought - ({ 0 });
 
    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(
                text(value_arr[0 .. num - 1]), text(value_arr[num .. 2 * num -1]));
 
    return bought;
}
 
int
shop_hook_sold_items(object *item)
{
    string sname;
    mapping temp, gemlist;
    int i, num;
    write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    clerk->command("emote puts her newly bought wares in their proper places.");

    temp = restore_map(SPIRIT_OBJECTS +"buy_gem_log");
    gemlist = temp[TP->query_real_name()];

    for(i = 0; i < sizeof(item); i++)
    {
        sname = item[i]->query_gem_name();
        if(!mappingp(gemlist))
            gemlist = ([]);
        num = gemlist[sname];
        num++;
        gemlist += ([sname:num]);
    }

    temp += ([TP->query_real_name():gemlist]);
    save_map(temp,SPIRIT_OBJECTS +"buy_gem_log");

    write("Arial telepatically says: A pleasure doing business with you.\n");
    return 1;
}

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

        if (ob[i]->query_gem() && ob[i]->query_prop(HEAP_I_UNIT_VALUE) == 0)
	{
	    shop_hook_sell_no_value(ob[i]);
	    continue;
        }

	if (check && (ob[i]->query_worn() ||
		      ob[i]->query_wielded()))
	{
	    shop_hook_sell_worn_or_wielded(ob[i]);
	    continue;
        }
    
	/* Save price if ob destructed in move */
	price = query_sell_price(ob[i]);

        if (price <= 0)
	{
	    shop_hook_sell_no_value(ob[i]);
	    continue;
        }
        ob[i]->add_prop("just_sold_gem",1);

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

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */

int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num, no_inv;

    if (!str || str =="")
    {
	notify_fail("Value what?\n");
	return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
	no_inv = 1;

    for (i = 0; i < sizeof(item); i++)
    {
	if (!shop_hook_allow_sell(item[i]) ||
		!item[i]->query_prop(HEAP_I_UNIT_VALUE) ||
		item[i]->query_prop(OBJ_M_NO_SELL)) 
	{
	    shop_hook_value_not_interesting(item[i]);
	    continue;
	}

	price = query_sell_price(item[i]);
        arr = give(price, this_player(), "", 1);
	shop_hook_value_held(item[i], text(arr[num .. 2 * num - 1]));
	j++;
    }

    call_other(store_room, "load_me");
    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str, store);
    if (!sizeof(item) && no_inv)
	return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
	price = query_buy_price(item[i]);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return 0;
}

int
do_buy(string str)
{
    mapping gem_list,lo_list;
    object *item, store;
    string str1, str2, str3,*gem_names,*lo_names,bugga,rc;
    int i,qty,qty_old;

    if (!str || str =="")
    {
	    notify_fail("Buy what?\n");
	    return 0;
    }
 
    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    store = find_object(store_room);
    gem_list = restore_map(SPIRIT_OBJECTS+"gemlist");
    if(sscanf(str1,"%d %s",qty,str1) != 2)
        qty = 1;
    gem_names = m_indexes(gem_list);

    for(i=0;i<sizeof(gem_names);i++)
        clone_object(gem_names[i])->move(store);

    item = FIND_STR_IN_OBJECT(str1, store);

    /* item should only have one element, the single gem */

    if(sizeof(item) > 30)
    {
        write("Too many items trying to be bought. Please narrow down.\n");
        return 0;
    }

    if (!sizeof(item))
	return shop_hook_buy_no_match(str1);

    if(item[0]->query_gem_name())
        qty_old = gem_list[MASTER_OB(item[0])];
    else 
        qty_old = lo_list[MASTER_OB(item[0])];
    if(qty > qty_old)
        item = ({});
    else
    {
        for(i=1;i<qty;i++)
            item += ({clone_object(MASTER_OB(item[0]))});
    }
    
    if (!sizeof(item))
	return shop_hook_buy_no_match_amount(str1);

    item = buy_it(item, str2, str3);
    if (sizeof(item))
    {
        qty = sizeof(item);
        qty_old -= qty;
        if(item[0]->query_gem_name())
        {
            gem_list += ([MASTER_OB(item[0]):qty_old]);
            save_map(gem_list,SPIRIT_OBJECTS+"gemlist");
        }
	return shop_hook_bought_items(item);
    }
 
    return 0; /* Player tried to sell a non sellable object. */
}

void
init()
{
    ::init();
    init_guild_support();
    init_gem_shop();
    add_action(gs_meditate,"kneel");
}
