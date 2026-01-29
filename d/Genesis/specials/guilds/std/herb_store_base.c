/*
 * Example Herb Shop Base
 *
 * This herb shop can be used to create an herb shop very easily. Simply inherit
 * this file and definet create_herb_room() and you'll have a fully
 * functioning herb shop.
 *
 * Created by Petros, April 2010
 */
#pragma strict_types;

#include <filter_funs.h>
#include <macros.h>
#include <language.h>
#include <files.h>

inherit "/std/room";
inherit "/d/Genesis/specials/guilds/lib/storeless_shop";

/*
 * Function:    create_herb_store
 * Description: This is the function that should be masked if inheriting from
 *              this base object. You can customize all the room properties
 *              here instead of in create_room.
 */
public void
create_herb_store()
{
    // Customize this.
}

/*
 * Function:    create_room
 * Description: A nomask version of create_room that will do the basic setup
 *              needed for this herb store to work. You can override all the
 *              settinsg here inside of create_herb_store
 */
public nomask void
create_room()
{
    set_short("A sample herb store");
    set_long("This is a sample herb store that provides basic functionality "
        + "for listing, valuing, selling, and buying of herbs. It uses "
        + "the herb_store_support library to perform the herb functionality "
        + "correctly.\n\n");
    
    set_store_room(VOID_OBJECT);
    config_default_trade();
    set_money_give_max(5000);
    set_money_give_out(({1000, 5000, 5000, 10}));
    set_money_give_reduce(({4, 0, 20, 15}));
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    
    load_object_data();
    
    create_herb_store();
}

/*
 * Function:    init
 * Description: Simple init that calls init_shop, which adds all
 *              the necessary actions in a store.
 */
public void
init()
{
    ::init();
    init_shop();
}
