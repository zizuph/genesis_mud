/* A room on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

#pragma strict_types

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";
inherit "/d/Calia/guilds/colleges/tower/objects/hshop_list";
inherit "/lib/skill_raise";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <money.h>
#include <language.h>
#include "defs.h";

#define STORE_ROOM "/d/Calia/guilds/colleges/tower/tower_herbalist_store"

object clerk;


void
init_college_training()
{
    sk_add_train(SS_HERBALISM, "search for and identify herbs", "herbalism",
        100, 80, SS_WIS, 60);
}

void
create_room()
{
    set_short("Tower Herbalist");

    set_long("You have entered a herbalist's shop in the Marble Tower." +
        " It's a roomy place, every wall covered with dust-lined shelves" +
        " that again are filled with a plethora of jars and pouches of" + 
        " varying size and colour. All are meticulously labeled, but any" +
        " order or system of placement is not apparent. A sign is posted" +
        " on the counter, containing instructions for the customer. " +         
        basic_desc + " To the east a corridor stretches.\n");
       
    add_item(({"shelf", "shelves"}), "The shelves are made out of some" +
        " sort of metal, affixed to the glowing walls by no visible" +
        " mechanism.\n");
    add_item(({"jars", "pouches", "jars and pouches"}), "The jars and" +
        " pouches are of many different types, and all are labeled in" +
        " clear handwriting.\n");
    add_item(({"label", "labels"}), "They're clearly written. If you" +
        " want to read them, try listing the herbs in store to get an" +
        " overview.\n");
    add_item("sign", "The sign contains a list of the things that are" +
        " possible to do in this shop.\n");
    add_item("counter", "A simple hardwood counter with ample room for" +
        " exchange of merchandise.\n");
               
    add_exit(TOWER + "tower_corr_1_5.c", "east", 0, 1);
    
    config_default_trade();
    set_money_give_max(5000);
    set_money_give_out(({1000, 5000, 5000, 10}));
    set_money_give_reduce(({4, 0, 20, 15}));
    set_money_greed_buy(65);
    set_money_greed_sell(100);
    
    set_store_room(STORE_ROOM);
    STORE_ROOM->load_me();

    clerk = clone_object(TOWER_NPCS+"herb_clerk");
    clerk->move_living("M",TO);

    make_college_room();
    init_college_training();    
}


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

int
shop_hook_allow_sell(object ob)
{
    if(!stringp(ob->query_herb_name()))
    {
        clerk->command("say I will only buy herbs.");
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
    clerk->command("say I don't have a "+str+"!");
    return 1;
}

int
shop_hook_buy_no_match_amount(string str)
{
    clerk->command("say I don't have that many "+str+"!");
    return 1;
}

int
shop_hook_bought_items(object *arr)
{
    string sname;
    int i, num;
    mapping temp,herblist;
    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    clerk->command("emote rummages through the pouches and vials and" +
    " gets out "+COMPOSITE_DEAD(arr)+".");

    temp = restore_map(TOWER_OBJECTS+"buy_herb_log");
    herblist = temp[TP->query_real_name()];

    for(i = 0; i < sizeof(arr); i++)
    {
        sname = arr[i]->query_herb_name();
        if(!mappingp(herblist))
            herblist = ([]);
        num = herblist[sname];
        num--;
        herblist += ([sname:num]);
    }

    temp += ([TP->query_real_name():herblist]);
   
    save_map(temp,TOWER_OBJECTS+"buy_herb_log");

    clerk->command("say It's been a pleasure dealing with you.");
    write("Belos gives you "+COMPOSITE_DEAD(arr)+".\n");
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
 
/*    
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns: 	  The price
 */

int
shop_hook_sold_items(object *item)
{
    string sname;
    mapping temp, herblist;
    int i, num;
    write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    clerk->command("emote finds a jar and puts his newly bought wares in it.");

    temp = restore_map(TOWER_OBJECTS +"buy_herblog");
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

    save_map(temp,TOWER_OBJECTS +"buy_herb_log");

    clerk->command("say A pleasure doing business with you.");
    return 1;
}

int
query_buy_price(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);

    return 2 * ob->query_herb_value() * (query_money_greed_buy() +
	5 + random(15, seed)) / 100;
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
    if(ob->query_potion_name())
        return ob->query_potion_value() * 100 / (query_money_greed_sell() +
        5 + random(15, seed + 1));
    return ob->query_herb_value() * 100 / (query_money_greed_sell() +
	5 + random(15, seed + 1)); /* Use another seed than on buying */
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
    
	/* Save price if ob destructed in move */
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
    mapping herb_list,lo_list;
    object *item, store;
    string str1, str2, str3,*herb_names,*lo_names,bugga,rc;
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
    herb_list = restore_map(TOWER_OBJECTS+"herblist");
    if(sscanf(str1,"%d %s",qty,str1) != 2)
        qty = 1;
    herb_names = m_indexes(herb_list);

    for(i=0;i<sizeof(herb_names);i++)
        clone_object(herb_names[i])->move(store);

    item = FIND_STR_IN_OBJECT(str1, store);

    /* item should only have one element, the single herb */

    if(sizeof(item) > 30)
    {
        write("Too many items trying to be bought. Please narrow down.\n");
        return 0;
    }

    if (!sizeof(item))
	return shop_hook_buy_no_match(str1);

    if(item[0]->query_herb_name())
        qty_old = herb_list[MASTER_OB(item[0])];
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
        if(item[0]->query_herb_name())
        {
            herb_list += ([MASTER_OB(item[0]):qty_old]);
            save_map(herb_list,TOWER_OBJECTS+"herblist");
        }
	return shop_hook_bought_items(item);
    }
 
    return 0; /* Player tried to sell a non sellable object. */
}


void
enter_inv(object ob, object from)
{
    int maxtrain = 0;

    if (strlen(ob->is_college_member()))
    {
        if (ob->query_skill(SS_COLLEGE_BITS) & APPRENTICE_LVL_BIT)
        {
            maxtrain = 40;
        }
        else
        if (ob->query_skill(SS_COLLEGE_BITS) & HERBALISM_CHOSEN_BIT)
        {
            maxtrain = 80;
        }
        else
        {
            maxtrain = 60;
        }
        
        ob->add_prop(COLLEGE_I_MAXTRAIN, maxtrain);
    }
    
    ::enter_inv(ob, from);
}

void
leave_inv(object ob, object to)
{
    if (ob->query_prop(COLLEGE_I_MAXTRAIN))
    {
        ob->remove_prop(COLLEGE_I_MAXTRAIN);
    }
    
    ::leave_inv(ob, to);
}

public int
sk_do_train(int snum, object pl, int to_lev)
{
    if (to_lev > pl->query_prop(COLLEGE_I_MAXTRAIN))
    {
        return 0;
    }
    else
    {
        return ::sk_do_train(snum, pl, to_lev);
    }
}

/*
 * Function name: sk_hook_cant_train
 * Description  : Player can't train that skill that high for some reason.
 * Arguments    : string skill - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    notify_fail("You fail to adopt what Belos teaches you.\n");
    return 0;
}


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    write("You cannot improve further with Belos' aid. Perhaps you" +
        " can learn a new skill, or train elsewhere?\n");
    return 1;
}


void
init()
{
    ::init();
    init_shop();
    init_skill_raise();
    add_action("do_read","read");
}
     


