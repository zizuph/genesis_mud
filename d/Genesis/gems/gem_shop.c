/* gem_shop.c
 *
 * Inherit this along with /lib/shop.c to create a shop that only
 * deals in gems.
 *
 * This doesn't inherit /lib/shop.c itself because many domains
 * have their own shop implementations which they may wish to use,
 * and I don't want to rely on /lib/shop.c and /lib/trade.c never
 * having any nomask functions.
 *
 * Example usage:
 *
 * inherit "/std/room";
 * inherit "/lib/shop";
 * inherit "/d/Genesis/gems/gem_shop";
 *
 * void
 * create_room()
 * {
 *     set_short("Gem shop");
 *     set_long("It's a gem shop!\n");
 *      
 *     create_gem_shop();
 *     set_store_room("/d/Wiz/shiva/gem_store_room");
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *     init_gem_shop();
 * }
 */

#pragma save_binary
#pragma strict_types

/*
 * Function name: create_gem_shop
 * Description:   Configure a default gem shop
 */
public void
create_gem_shop()
{
    this_object()->config_default_trade();

    this_object()->set_money_greed_buy(100);
    this_object()->set_money_greed_sell(130);
    this_object()->set_money_give_max(10000);
    this_object()->set_money_give_out(   ({  100,  1000, 1000,  25 }));
    this_object()->set_money_give_reduce(({    0,     2,    4,  10 }));
}

/*
 * Function name: init_gem_shop
 * Description:   Add shop commands
 */
void
init_gem_shop()
{
    this_object()->init_shop();
}

/*
 * Function name: gem_shop_filter_gems
 * Description:   See if an object is a gem
 * Arguments:     object ob - the object to check
 * Returns:       1/0 - object is a gem/is not
 */
public int
gem_shop_filter_gems(object ob)  
{
    return ob->query_gem();
}

/*
 * Function name: gem_shop_hook_sell_non_gem
 * Description:   Redefine this to change the message given when
 *                someone attempts to sell a non-gem item.
 * Arguments:     object ob - the non-gem item
 */
public void
gem_shop_hook_sell_non_gem(object ob)
{
    write("Sorry, I am not interested in this " + ob->short(this_object()) +
        ".\n");
}

/*
 * Function name: shop_hook_allow_sell
 * Description:   See if an item can be sold.  We check to be sure
 *                that the item is a gem.
 * Arguments:     object ob - the item to be sold
 * Returns:       1/0 - the item can be sold/cannot be sold
 */
int
shop_hook_allow_sell(object ob)  
{
    if (!gem_shop_filter_gems(ob))
    {
        gem_shop_hook_sell_non_gem(ob);
        return 0;
    }

    return 1;
}
