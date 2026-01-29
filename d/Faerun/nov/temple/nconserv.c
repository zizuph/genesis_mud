
#pragma save_binary



#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "component_list.h"
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "../nov.h"

inherit "/lib/shop.c";
inherit NOV_DIR +"temple/std_room";




#define MAXLIST         30
#define HERB_FILE       "/std/herb"
#define POTION_FILE     "/std/potion"

int gGlobal_seed;

void
create_room()
{
       
    set_short("conservatory");
    set_long("You are in the conservatory.\n");


    config_default_trade();

    set_store_room(NOV_DIR +"temple/nconserv_store");
    store_room->load_me();
    gGlobal_seed = SECURITY->query_start_time() % 30;
}

static int
query_item_value(object item)
{
    switch (function_exists("create_object", item))
    {
        case HERB_FILE:
            return item->query_herb_value();
            break;
        case POTION_FILE:
            return item->query_potion_value();
            break;
        default:
            return item->query_prop(OBJ_I_VALUE);
            break;
    }
}

public int
query_buy_price(object ob)
{
    return 0;
}

public int
query_sell_price(object ob)
{
    return 0;
}

int
shop_hook_allow_sell(object ob)
{
    string func = function_exists("create_object", ob);

    if ((func != HERB_FILE) && (func != POTION_FILE) &&
         (!sizeof(ob->query_names() & COMPONENT_LIST)))
        return notify_fail("I don't know what component you're talking about.\n");

    return 1;
}

public int
filter_files(string file, string str)
{
    object item;

    if (file_size(file + ".c") > 0)
        if (objectp((item = find_object(file))))
            switch (function_exists("create_object", item))
            {
                case HERB_FILE:
                    return (item->query_herb_name() == str);
                    break;

                case POTION_FILE:
                    return (item->query_potion_name() == str);
                    break;
            }
    return 0;
}

void
shop_hook_list_empty_store(string str)
{
    notify_fail("There are currently no components in the conservatory.\n");
}

static void
shop_hook_list_file(int count, string name, int value)
{
    string str, mess;

    str = sprintf("%5d %-20s ", count, (count > 1 ? LANG_PWORD(capitalize(name)) :
                                          capitalize(name)));
    write(str + "\n");
}

public int
do_list(string str)
{
    mixed items;
    string *item_files, *fresh_out = ({});
    int size, price, tmp;
    object item;
    
    setuid();
    seteuid(getuid());

    store_room->load_me();


    items = store_room->query_items();

    if (!m_sizeof(items[0][0]) && !m_sizeof(items[0][1]) && !sizeof(items[1]))
    {
        shop_hook_list_empty_store(str);
        return 0;
    }

    if (!str || !strlen(str) || (lower_case(str) == "herb") || (lower_case(str) == "herbs"))
    {
        if (!m_sizeof(items[0][0]))
            fresh_out += ({ "herbs" });
        else
        {
            write("---- Herbs in storage: ----\n");

            item_files = sort_array(m_indexes(items[0][0]));
            size = sizeof(item_files);

            while(size--)
                if (file_size(item_files[size] + ".c") > 0)
                    if (objectp((item = find_object(item_files[size]))) ||
                         (!item_files[size]->aaa() && (objectp((item = 
                          find_object(item_files[size]))))))
                    {   
                        price = query_buy_price(item);
                        shop_hook_list_file(items[0][0][item_files[size]],
                                            item->query_herb_name(),
                                            price);
                    }
        }
    }

    if (!str || !strlen(str) || (lower_case(str) == "potion") || (lower_case(str) == "potions"))
    {
        if (!m_sizeof(items[0][1]))
            fresh_out += ({ "potions" });
        else
        {
            write("\n---- Potions in storage: ----\n");
            
            item_files = sort_array(m_indexes(items[0][1]));
            size = sizeof(item_files);

            while(size--)
                if (file_size(item_files[size] + ".c") > 0)
                  {
                  item_files[size]->foo_bar_me();
                    if (objectp((item = find_object(item_files[size]))))
                    {
                        price = query_buy_price(item);
                        shop_hook_list_file(items[0][1][item_files[size]],
                                            item->query_potion_name(),
                                            price);
                    }
                  }
        }
    }

    size = sizeof(fresh_out);
    if (size > 1)
    {
        write("\nI'm fresh out of " + implode(fresh_out[0..size - 2], ", ") +
              " and " + fresh_out[size - 1] + ".\n");
    }
    else
        if (size == 1)
           write("\nI'm fresh out of " + fresh_out[0] + ".\n");

    return 1;
}

int
do_buy(string str)
{
    notify_fail("What ?\n");
    return 0;
}

int
do_sell(string str)
{
    notify_fail("What ?\n");
    return 0;
}
 
int
do_retrieve(string str)
{
    int size;
    object *objs, *obj_files = ({}),
           *bought_items,
            store;
    mixed items;
    string *item_files;

    if (!str || !strlen(str))
    {
        notify_fail("Retrieve what?\n");
        return 0;
    }
 
    store_room->load_me();

    store = find_object(store_room);
    items = store->query_items();

    item_files = filter(m_indexes(items[0][0]) + m_indexes(items[0][1]),
                        &filter_files(, lower_case(str)));

    size = sizeof(item_files);
    while (size--)
        obj_files += ({ clone_object(item_files[size]) });

    objs = FIND_STR_IN_ARR(str, items[1]) + obj_files;

    if (!sizeof(objs))
        return shop_hook_buy_no_match(str);

    bought_items = buy_it(objs, 0, 0);

    if (sizeof(objs) != sizeof(bought_items))
        (obj_files - (bought_items & obj_files))->remove_object();

    if (sizeof(bought_items))
    {
        store->remove_components((bought_items & obj_files));
        return shop_hook_bought_items(bought_items);
    }

    return 0; 
}

int
do_stow(string str)
{
    object *item;
    int value, check;

    if (!str || str =="")
    {
        notify_fail("Stow what?\n");
        return 0;
    }

    if (str == "all!")
    {
        str = "all";
        check = 0;
    }
    else
    {
        check = 1;
    }

    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
        return shop_hook_sell_no_match(str);

    item = sell_it(item, 0, check);
    if (sizeof(item))
        return shop_hook_sold_items(item);

    if (str == "all")
        return shop_hook_sold_nothing();

    return 0;
}

int
do_value(string str)
{
    return 0;
}

public object *
sell_it(object *ob, string str, int check)
{
    int price, i, j, k, *tmp_arr, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    store_room->load_me();

    value_arr = allocate(sizeof(query_money_types()));
    null_arr = value_arr + ({});
    sold = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_sell(ob[i]))
            continue;

        if (query_item_value(ob[i]) == 0)
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

        if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
        {
            shop_hook_sell_no_sell(ob[i], tmp);
            continue;
        }

        price = query_sell_price(ob[i]);

        if (err = ob[i]->move(store_room))
        {
            shop_hook_sell_object_stuck(ob[i], err);
            continue;
        }

        if (price >= 0)
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

    return sold;
}

public int
shop_hook_bought_items(object *arr)
{
    write(break_string("You retrieved " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " retrieved " + QCOMPDEAD + ".\n");
    arr->force_dry();
    return 1;
}

int
shop_hook_sold_items(object *item)
{
    write(break_string("You stowed " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " stowed " + QCOMPDEAD + ".\n");
    return 1;
}

void
shop_hook_buy_pay_money(string str, string change)
{
}

void
shop_hook_sell_get_money(string str)
{
    write("You retrieved " + str + ".\n");
}

public void
init()
{
   init_shop();
   ::init();
   add_action(do_stow,"stow");
   add_action(do_retrieve,"retrieve");
}