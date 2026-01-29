
/*
 * study.c
 *
 * Study for the Spirit Circle of Psuchae Temple
 * This chamber will hold the components required for all of the
 * gifts (spells) granted to the members of the guild. They can
 * also get ceremonial daggers from a hook hanging above the 
 * stand here (for cutting body parts out of bodies).
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 * Modification Log:
 *  - Added Leftover Closet for ease of storage. (Petros - 9/24/2008)
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
// inherit "/d/Calia/guilds/scop/temple/hshop_list";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <money.h>
#include <language.h>

#include "defs.h"

// #define STORE_ROOM "/d/Calia/guilds/scop/temple/herb_store_room"

// object clerk;
// object closet;

void
create_room()
{
    set_short("Study");
    set_long("This chamber is much smaller than any other you "+
        "have been in while inside of this temple. All four walls "+
        "are polished wood, the ceiling and floor both a smoothly "+
        "polished grey stone. Upon entering this small chamber, "+
        "your eyes focus upon a small stand sitting against "+
        "the western wall and a tall double-doored closet on the "+
        "northern wall. The stand has several drawers to hold "+
        "different items. On the wall above the stand is a small "+
        "rack and a sign. The sleeping chamber lies back out to the east.\n");

    add_item(({"dagger","daggers","ceremonial dagger","ceremonial daggers"}),
        "These daggers have golden handles and appear to be quite sharp. "+
        "You could probably unhook one if you wanted one to take with you. "+
        "<unhook dagger>\n");
    add_item(({"rack","small rack"}),"It is a small wooden rack hanging "+
        "on the wall above the stand. Hanging from the rack are several "+
        "ceremonial daggers.\n");
    add_item(({"drawer","drawers"}),"There are several drawers in the "+
        "small stand to hold different items and components.\n");
    add_item(({"stone","grey stone","polished stone","polished grey stone"}),
        "Both the walls and the ceiling are made of polished grey stone.\n");
    add_item("sleeping chamber","The sleeping chamber lies back out "+
        "to the west.\n");
    add_item(({"floor","roof","ceiling"}),"The floor and ceiling are "+
        "both constructed with a grey stone and then smoothed and "+
        "polished afterwards. The floor is quite comfortable to "+
        "walk on.\n");
    add_item(({"wall","walls"}),"The walls here are covered in a "+
        "polished wood, light brown, almost red, in colour. They are "+
        "extremely smooth to the touch.\n");
//    add_item("sign", "The sign contains a list of the things that are" +
//        " possible to do in this shop.\n");
    add_item("ceiling", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards.\n");


    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

//    clone_object(SPIRIT_OBJECTS+"small_stand")->move(TO);

//    config_default_trade();
//    set_money_give_max(5000);
//    set_money_give_out(({1000, 5000, 5000, 10}));
//    set_money_give_reduce(({4, 0, 20, 15}));
//    set_money_greed_buy(125);
//    set_money_greed_sell(125);
    
//    set_store_room(STORE_ROOM);
//    STORE_ROOM->load_me();

//    clerk = clone_object(SPIRIT_NPCS+"herb_clerk");
//    clerk->move_living("M",TO);

    // Add the leftover closet
//    closet = clone_object(SPIRIT_OBJECTS+"leftover_closet");
//    closet->move(TO, 1);
//    closet->set_no_show_composite(1);

    add_exit(SPIRIT_TEMPLE+"startroom","east",0,1);
    add_exit("/d/Calia/guilds/elementalists/temple/ec_rack","south",0,1);
}

int
do_unhook(string str)
{
    object dagger;

    if (!str)
    {
        NF("Unhook what? A dagger? <unhook dagger>\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'"))
    {
        NF("Unhook what? A dagger? <unhook dagger>\n");
        return 0;
    }
    
    if (!present("_spirit_ceremonial_dagger_",TP))
    {
        dagger = clone_object(SPIRIT_OBJECTS+"ceremonial_dagger");
        write("You unhook a dagger from the rack and take it.\n");
        say(QCTNAME(TP)+" unhooks a dagger from the small rack and takes it.\n");
        dagger->move(TP);
        return 1;
    }

    NF("You already have a ceremonial dagger, no use having two!\n");
    return 0;
}

int
do_hook(string str)
{
    object dagger;

    if (!str)
    {
        NF("Hook what? A dagger? <hook dagger>\n");
        return 0;
    }

    if (!parse_command(str, ({}),"[a] [the] [ceremonial] 'dagger'"))
    {
        NF("Hook what? A dagger? <hook dagger>\n");
        return 0;
    }

    dagger = present("_spirit_ceremonial_dagger_",TP);
    
    if (!dagger)
    {
        NF("You do not have a dagger to hang back on the hook.\n");
        return 0;
    }

    write("You carefully wash the ceremonial dagger, making sure it is "+
        "clean and ready for the next person to use. When you are sure it "+
        "is clean, you hang the dagger back on the hook.\n");
    say(QCTNAME(TP)+" carefully washes the ceremonial dagger that "+
        TP->query_pronoun()+" is holding. When "+TP->query_pronoun()+
        " is sure it is clean, "+TP->query_pronoun()+" hangs the dagger "+
        "back on the hook.\n");
    dagger->remove_object();
    return 1;
}
/*

int
do_read(string str)
{
    if (str != "sign")
    {
        notify_fail("Read what? The sign perhaps?\n");
        return 0;
    }
    
    write("You can buy and sell herbs in this shop.\n" +
        "Other possible commands:\n" +
        "<list> - Lists what's in stock.\n" +
        "<value> - Allows you to see how much the herbalist would give you" +
        " for a particular herb.\n"); 
    return 1;
}
*/
/*
int
shop_hook_allow_sell(object ob)
{
    if(!stringp(ob->query_herb_name()))
    {
        write("Jardeth telepatically says: I will only buy herbs.\n");
        return 0;
    }
    return 1;
}


void
shop_hook_list_object(object ob, int price)
{
    string str, mess;

    str = sprintf("%-25s", ob->query_herb_name());
    if (mess = text(split_values(price)))
        write(break_string(str + mess + ".\n", 75));
    else
        write(str + "That item wouldn't cost you much.\n");
}

int
shop_hook_buy_no_match(string str)
{
    write("Jardeth telepatically says: I don't have a "+str+"!\n");
    return 1;
}

int
shop_hook_buy_no_match_amount(string str)
{
    write("Jardeth telepatically says: I don't have that many "+str+"!\n");
    return 1;
}

int
shop_hook_bought_items(object herb)
{
    string sname;
    int i, num;
    mapping temp,herblist;

    write(break_string("You bought " + COMPOSITE_DEAD( ({ herb }) ) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    clerk->command("emote rummages through the pouches and vials and" +
    " gets out "+COMPOSITE_DEAD( ({ herb }) )+".");

    temp = restore_map(SPIRIT_OBJECTS+"buy_herb_log");
    herblist = temp[TP->query_real_name()];

    sname = herb->query_herb_name();
    if(!mappingp(herblist))
        herblist = ([]);
    num = herblist[sname] - herb->num_heap();
    herblist += ([sname:num]);

    temp += ([TP->query_real_name():herblist]);
    save_map(temp,SPIRIT_OBJECTS+"buy_herb_log");
   
    write("Jardeth telepatically says: It's been a pleasure dealing "+
        "with you.\n");
    write("Jardeth gives you "+COMPOSITE_DEAD( ({ herb }) )+".\n");
    return 1;
}
*/
/*
object
buy_it(object ob, string str2, string str3)
{
    int price, k, *value_arr, *arr, error, num, err;
 
    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);

    if (!shop_hook_allow_buy(ob))
        return 0;

    price = query_buy_price(ob);
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
        ob->move(store_room, 1);
        shop_hook_buy_cant_pay(ob, arr);
        return 0;  // pay() can handle notify_fail() call 
    }

    if (err, ob->move(this_player()))
    {
        shop_hook_buy_cant_carry(ob, err);
        return 0;
    }
 
    // Detect if there was a move error. 
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
        // Couldn't take the money from player, the coins were stuck 
            shop_hook_buy_magic_money(ob);
            ob->move(store_room, 1);
            return 0;
        }
        // We don't want the money so no move error to us, if there was one
        // it was because the player couldn't hold all coins, and if so the
        // drop text is already written, but the deal is still on :) 
    }
 
    for (k = 0; k < 2 * num; k++)
        value_arr[k] += arr[k];

    shop_hook_buy_pay_money(
        text(value_arr[0 .. num - 1]), text(value_arr[num .. 2 * num -1]));
 
    return ob;
}
*/

/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns: 	  The price
 */
/*
int
shop_hook_sold_items(object *item)
{
    string sname;
    mapping temp, herblist;
    int i, num;
    write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    clerk->command("emote finds a pouch and puts his newly bought wares in it.");

    temp = restore_map(SPIRIT_OBJECTS +"buy_herb_log");
    herblist = temp[TP->query_real_name()];

    for(i = 0; i < sizeof(item); i++)
    {
        sname = item[i]->query_herb_name();
        if(!mappingp(herblist))
            herblist = ([]);
        num = herblist[sname];
        num++;
        herblist += ([sname:num]);
    }

    temp += ([TP->query_real_name():herblist]);
    save_map(temp,SPIRIT_OBJECTS +"buy_herb_log");

    write("Jardeth telepatically says: A pleasure doing business with you.\n");
    return 1;
}

int
query_buy_price(object ob)
{
    // If the object is invalid, it's not worth anything
    if (!objectp(ob))
    {
        return 0;
    }

    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return 2 * ob->num_heap() * ob->query_herb_value() *
        (query_money_greed_buy() + 5 + random(15, seed)) / 100;
}
*/

/*    
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:	  ob - The object
 * Returns:	  The price
 */
/*
int
query_sell_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    
    int sellValue = ob->query_herb_value() * 100 / (query_money_greed_sell() +
	    5 + random(15, seed + 1)); // Use another seed than on buying 

    if (ob != 0 && IS_HEAP_OBJECT(ob)) 
    {
        sellValue = sellValue * ob->num_heap();
    }
    return sellValue;
}
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

        if (ob[i]->query_herb_name() && ob[i]->query_herb_value() == 0)
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
    
	// Save price if ob destructed in move 
	price = query_sell_price(ob[i]);

        if (price <= 0)
	{
	    shop_hook_sell_no_value(ob[i]);
	    continue;
        }
        ob[i]->add_prop("just_sold_herb",1);

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
    
    // * Only let people sell 20 objects at once and hopefully we wont get
    // * those too long evaluation problems.
    
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
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
/*
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
		!item[i]->query_herb_value() ||
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
	arr = split_values(price); // A price with few coins possible 
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return 0;
}
*/
/*
int
do_buy(string str)
{
    mapping herb_list,lo_list;
    object item, store;
    string str1, str2, str3,*lo_names,bugga,rc;
    int i,qty,qty_old;

    if (!str || str =="")
    {
	    notify_fail("Buy what?\n");
	    return 0;
    }
 
    call_other(store_room, "load_me"); // Make sure storeroom is loaded 

    //  Did the player specify payment and change? 
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    // Well, maybe player has defined how payment will be done atleast? 
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    store = find_object(store_room);
    herb_list = restore_map(SPIRIT_OBJECTS+"herblist");
    if(sscanf(str1,"%d %s",qty,str1) != 2)
        qty = 1;

    string herbfile = find_herbfile_using_name(str1, herb_list);
    if (strlen(herbfile))
    {
        item = find_object(herbfile);
    }
    
    if (!objectp(item))
	return shop_hook_buy_no_match(str1);

    if(item->query_herb_name())
        qty_old = herb_list[MASTER_OB(item)];
    else 
        qty_old = lo_list[MASTER_OB(item)];

    item = 0;
    if(qty <= qty_old)
    {
        item = clone_object(herbfile);
        item->set_heap_size(qty);
    }
    
    if (!objectp(item))
	return shop_hook_buy_no_match_amount(str1);

    item = buy_it(item, str2, str3);
    if (objectp(item))
    {
        qty = item->num_heap();
        qty_old -= qty;
        if(item->query_herb_name())
        {
            herb_list += ([MASTER_OB(item) : qty_old]);
            save_map(herb_list,SPIRIT_OBJECTS+"herblist");
        }
	return shop_hook_bought_items(item);
    }
 
    return 0; // Player tried to sell a non sellable object. 
}
*/

void
init()
{
    ::init();
//    init_shop();
//    add_action(do_read,"read");
    add_action(do_unhook,"unhook");
    add_action(do_hook,"hook");
}
