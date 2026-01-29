/*
 * Shop of Green Oaks
 * Players can access the bank thru a 'hole' in the wall, but will 
 * pay more for it, instead of going out and around the corner
 * By Finwe, March 2005
 *
 * Typos fixed.
 * Aeg, 2010
 */
 
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
inherit "/d/Shire/lib/shop_list";

#define STORE_ROOM (GO_DIR + "shop_store")

static object falawas;

void add_stuff();
 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    
    set_short("Shop of Green Oaks");
    set_long("This is the " + short() + ". The large room is full of " +
        "many things for sale. Travellers from afar come here to buy " +
        "and sell things they need or want. A counter runs along the " +
        "south. It wraps around and goes up the east wall. Behind the " +
        "eastern counter is an opening into the bank next door. There is " +
        "a sign and a plaque you may read.\n");

    set_add_ceiling_flat("the ceiling is white and undecorated.");
    add_item(({"counter", "east counter", "south counter"}),
        "The counter is wide and stained a dark color. It wraps around " +
        "the south and east wall. Behind the counter is an opening " +
        "where you can access a bank.\n");
    add_item(({"opening"}),
        "The opening is behind the east counter. It allows customers " +
        "here access to the bank next door.\n");
    

    // sets up shop
    config_default_trade();  /* Set up the trading system */
    set_store_room(STORE_ROOM);


    add_auto_object("/d/Genesis/obj/deposit");
    add_auto_object(OBJ_DIR + "bank");

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    add_exit(GO_DIR + "road02", "north");
 
}

void
init()
{
    ::init();
    init_shop();
}


void reset_room() 
{ 
    add_stuff();
}

void
add_stuff()
{
    if(!falawas)
        falawas = clone_object(NPC_DIR + "shopkeeper");
        falawas->move(TO);

}


/*
 * Function name: standard_bank_sign
 * Description:   returns a string with a sign message
 * Arguments:     none
 * Returns:       message string
 */
string
standard_bank_sign()
{
    return "You read:\n\n" + 
    "\t+-----------------------------------------------------------+\n" +
    "\t|                                                           |\n" +
    "\t|   This window to the bank provides a convenient way to    |\n" +
    "\t|   take care of your banking needs while shopping. But to  |\n" +
    "\t|   provide you with the best service possible, and to keep |\n" +
    "\t|   an extra gnome busy, our rates are different here.      |\n" +
    "\t|                                                           |\n" +
    "\t|   For each transaction we ask only a " + (BANK_FEE + EXTRA_BANK_FEE) + "% fee.             |\n" +
    "\t|   This is an example of what you can do:                  |\n" +
    "\t|   - change copper and silver for gold                     |\n" +
    "\t|     This would make you change all your copper and silver |\n" +
    "\t|     coins into as much gold as possible.                  |\n" +
    "\t|   - test change copper and silver for gold                |\n" +
    "\t|     This would show you the outcome of the command behind |\n" +
    "\t|     the 'test' word.                                      |\n" +
    "\t|   - change 1 platinum for copper                          |\n" +
    "\t|     This would change 1 platinum coin to copper coins.    |\n" +
    "\t|   - change platinum for 100 silver                        |\n" +
    "\t|     This would convert a platinum coin to 100 silver      |\n" +
    "\t|     coins, and the change that would be left over from    |\n" +
    "\t|     the platinum coin needed after 100 silver coins has   |\n" +
    "\t|     been given                                            |\n" +
    "\t|   - minimize coins                                        |\n" +
    "\t|     This changes all coins into the most valuable types   |\n" +
    "\t|     possible                                              |\n" +
    "\t|                                                           |\n" +
    "\t|   There is a sign with more information you may read.     |\n" +
    "\t|   You may also <read fine print>, <read usage> and        |\n" +
    "\t|   <read terms>.                                           |\n" +
    "\t|                                                           |\n" +
    "\t+-----------------------------------------------------------+\n\n";
}
