/*
 * hotel.c
 *
 *  A hotel in Last of Terel. Here the player can, for
 *  a small fee, have a temporary starting location.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/trade";

#include <money.h>


#define NUM      sizeof(MONEY_TYPES)

/*
 * Prototypes
 */
public string price_long();

/*
 * Global variables
 */
object chump;

/*
 * Function name: reset_room
 * Description:   clone the hotel keeper if necessary
 */
public void
reset_room()
{
    if (!chump) {
        seteuid(getuid());
        chump = clone_object(LAST_DIR +"npc/chump");
        chump->move_living(LAST_DIR + "inn_main");
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("The White Dragon Inn");
    set_long("This is the White Dragon Inn. " +
               "You are in the common room of the Inn. Before you is a "+
               "counter with a small bell on it. There is a fireplace to "+
               "your right, and a small table in front of it. On the wall "+
               "behind the counter is a sign with some prices listed. "+
               "You see several doors leading to rentable rooms.\n");

    add_item(({"counter"}), 
                              "It's made of solid oak. There is a small slot in it " +
                              "where you can return your key.\n");
    add_item(({"fire","fireplace"}),"A low fire burns in the fireplace "+
                      "fighting back the chilling cold that seeps in from the "+
                      "front door.\n");
    add_item("table","The small table stands before the fireplace for "+
                    "visitors to relax at.\n");    
    add_item(({"slot"}), "The shape of the slot reminds you of a key.\n");
    
    add_item(({"list", "pricelist", "sign"}), "@@price_long");
    add_item(({"bell"}), "It is a small iron bell.\n");

    INSIDE;

    add_exit(CALATHIN_DIR + "square1_2",   "north",     0);
    add_exit(LAST_DIR + "hotel1", "west", "@@check|hotel_1@@");
    add_exit(LAST_DIR + "hotel2", "south",     "@@check|hotel_2@@");
    add_exit(LAST_DIR + "hotel3", "east", "@@check|hotel_3@@");

    /* Set up the trading system */
    config_default_trade();
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
    set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

    reset_room();
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_read",   "read",   0);
    add_action("do_read",   "study",  0);
    add_action("do_rent",   "rent",   0);
    add_action("do_return", "return", 0);
}

/*
 * Function name: do_read
 * Description:   Handle the read action
 * Returns:       1/0
 */ 
public int
do_read(string str)
{
    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
                         return 0;
    
    if (str == "pricelist" || str == "list" || str == "prices" ||
                         str == "sign") {
                         write(price_long());
                         return 1;
    }
    return 0;
}

/*
 * Function name: price_long
 * Descrition:    Returns what is written on the price list
 * Returns:       A string that is the pricelist.
 */
public string
price_long()
{
    return (
                     "The list reads:\n"
                  + "    Lodging ...........................1 pc\n"
                  + "You rent a room with 'rent room'.\n");
}

/*
 * Function name: do_return
 * Description:   Handle the return action
 * Returns:       1/0
 */
public int
do_return(string str)
{
    object key;

    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;
    
    if (str != "key" && str != "iron key")
        return 0;

    key = present("_room_key", TP);
    if (!key)
        return 0;

    write("You put the key in the slot on the counter.\n");
    if (argarn) 
        chump->command("thank " + TP->query_real_name());
    key->remove_object();
    say(QCTNAME(TP) + " returns a key.\n");
    return 1;
}


/*
 * Function name: do_rent
 * Description:   Handle the rent action
 * Returns:       1/0
 */
public int
do_rent(string str)
{
    string pay_type, get_type; string coin_pay_text, coin_get_text;
    int *money_arr;    
    object key;
    string item_name, name;
    int price;

    NF("There is no one here to help you!\n");
    if (!argarn || !present(chump))
                         return 0;

    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
        return 0;

    /*
     * Check if the player defines what she wants to pay with
     * and what you would like in return.
     */

    if(sscanf(str, "%s with %s and get %s", item_name, pay_type,
                    get_type) != 3) {
        get_type = "";

        if (sscanf(str, "%s with %s", item_name, pay_type) != 2) {
            pay_type = "";
            item_name = str;
         }
    }

    if (item_name != "room" && item_name != "overnight stay" &&
                         item_name != "lodging")
        return 0;

    price = 1728;

    NF("You failed to rent a room.\n");

    if (sizeof(money_arr = pay(price, TP, pay_type, 0, 0, get_type)) == 1) {
                         if (money_arr[0] == 2) {
        chump->command("say You don't have any " + pay_type +
                " coins, silly " + TP->query_nonmet_name() +".");
        return 0;
     }
     if (money_arr[0] == 1) {
            chump->command("say The room is a little too " +
                  "expensive to pay for in " + pay_type +
                  " coins, silly " + TP->query_nonmet_name() + ".");
            return 0;
     }
    else {
         chump->command("say I don't think so!  You are "+
                        "going to need more money than that, silly "+
                         TP->query_nonmet_name() + ".");
         return 0;
         }
     }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You rent a room and pay " + coin_pay_text + ".\n");
    if (coin_get_text) write("You get " + coin_get_text + " back.\n");
    
    name = TP->query_real_name();

    seteuid(getuid());
    key = clone_object(LAST_DIR + "obj/hotel_key");
    key->move(chump);
    key->add_name("_room_key");
    key->add_prop("_room_renter", name);
    chump->command("give key to " + name);
    if (present(key, argarn))
        chump->command("drop key");
    say(QCTNAME(TP) + " rents a room.\n");
    
    return 1;
}




/*
 * Function name: check
 * Description:   vbfc from add_exit to see if a player is allowed to
 *                enter a hotel room
 * Arguments:     cell - the room name
 * Returns:       0 if player is allowed 1 if not allowed
 */
public int
check(string cell)
{
    int i;
    object room, key, *obs;

    key = present("_room_key", TP);
    if(!key || key->query_prop("_room_renter") != TP->query_real_name()) {
        write("You aren't entitled to go there!\n");
        return 1;
    }

    room = find_object(LAST_DIR + cell);
    if (!room)
        return 0;

    obs = all_inventory(room);
    for (i = 0; i < sizeof(obs); i++) 
        if (living(obs[i])) {
            write("That room is already occupied by someone. "+
                      "Try another one.\n");
            return 1;
        }

    return 0;
}
