/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *  The Stumble Inn located in Dabaay 
 *
 *  Here the player can, for a small fee, have a temporary 
 *  starting location.  Various beverages are also available
 *  here.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/d/Terel/std/pub";
inherit "/lib/trade";

#include <money.h>

#define NUM      sizeof(MONEY_TYPES)

#define DOBJ  DABAAY_DIR + "obj/"
#define DNPC  DABAAY_DIR + "npc/"
#define DAB_TOWN DABAAY_DIR + "town/"


/*
 * Prototypes
 */
public string price_long();
public string menu_long();
public void get_keep(object who);
public void rem_keep();

/*
 * Global variables
 */
int aid=0;
object hotel_keep, pub_keep;

/*
 * Function name: reset_room
 * Description:   clone the hotel keeper if necessary
 */
public void
reset_room()
{
    if (!hotel_keep) {
        seteuid(getuid());
	hotel_keep = clone_object(DNPC + "jarred");
	hotel_keep->move(DAB_TOWN + "stumble_priv");
    }
    if (!pub_keep) {
        seteuid(getuid());
        pub_keep = clone_object(DNPC + "brooke");
        pub_keep->move(TO);
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
    
    set_short("The Stumble Inn");
    set_long(
        "This is the Stumble Inn of Dabaay.\n" +
        "In here, you can rent a room and stay overnight.  You " +
        "may also purchase beverages to quench whatever thirst you "+
        "might have.\n"+
        "There is an old bar in the back of the room, with a menu on "+
        "it.\n"+
        "There is a sign on the counter with information on renting a "+
        "room for the night.  There is also a bell on the counter.\n");

    add_item(({"counter"}), 
	     "It's made of solid oak. There is a small slot in it " +
	     "where you can return your key.\n");
    
    add_item(({"slot"}), "The shape of the slot reminds you of a key.\n");
    
    add_item(({"sign"}), "@@price_long");
    add_item(({"bell"}), "It is a small iron bell.\n");

    INSIDE;

    add_exit(DAB_TOWN + "stumble2", "north",     "@@check|stumble_2@@");
    add_exit(DAB_TOWN + "square4_5", "west", 0);
    add_exit(DAB_TOWN + "stumble3", "northeast", "@@check|stumble_3@@");
    add_exit(DAB_TOWN + "stumble1", "northwest", "@@check|stumble_1@@");

    /* Set up the trading system */
    config_default_trade();
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,   2,    3 })); /* Max_pay   */
    set_money_give_reduce(({     0,     1,   0,    6 })); /* Threshold */

    /* Beverages */
    add_drink(({"special","specials"}),                /* ID's   */
              ({"special","specials"}),                /* Names  */
              "dabaayan",                   /* Adj    */
              120,                          /* Soft   */
              80,                           /* Alco   */
              320,                          /* Price  */
              "Dabaayan Special",           /* Short  */
              "Dabaayan Specials",          /* Pshort */
              "A dark drink with a powerful smell.  You think "+
              "you can see fumes rising from the top of it.\n",  /* Long   */
              0);                           /* dummy  */ 
              
    add_drink(({"slug","slugs"}),           /* ID's   */
              ({"slug","slugs"}),           /* Names  */
              "sea",                        /* Adj    */
              100,                          /* Soft   */
              20,                           /* Alco   */
              50,                          /* Price  */
              0,                           /* Short  */
              0,                           /* Pshort */
              "A bluish-green drink with a salty smell to it. "+
              "It also looks a bit slimy.\n",  /* Long   */
              0);                           /* dummy  */ 
              
    add_drink(({"scratcher","scratchers"}), /* ID's   */
              ({"scratcher","scratchers"}), /* Names  */
              "back",                       /* Adj    */
              70,                          /* Soft   */
              10,                          /* Alco   */
              25,                          /* Price  */
              0,                           /* Short  */
              0,                           /* Pshort */
              "A Dabaayan Back Scratcher. A fine malt liquor that is "+
              "rumoured to cure irksome itches.\n",
              0);                           /* dummy  */ 
              

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
    add_action("do_ring",   "ring",   0);
    init_pub();
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
    if (str == "menu")
    {
        write(menu_long());
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
	  + "    Lodging ...........................1 gc\n"
	  + "You rent a room with 'rent room'.\n");
}

public string
menu_long()
{
    return (
	    "The menu reads:\n"
	  + "    Dabaayan Special ..................320 copper\n"
	  + "    Sea Slug .......................... 50 copper\n"
	  + "    Back Scratcher .................... 25 copper\n");
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

    key = present("_stumble_room_key", TP);
    if (!key)
	return 0;

    write("You put the key in the slot on the counter.\n");
    if (hotel_keep) 
	hotel_keep->command("thank " + TP->query_real_name());
    key->remove_object();
    say(QCTNAME(TP) + " returns a key.\n");
    return 1;
}

/*
 * Function name: do_ring
 * Description:   Handle the ring action
 * Returns:       1/0
 */
public int
do_ring(string str)
{
    string name;

    NF(capitalize(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;
    
    if (str != "bell" && str != "iron bell")
	return 0;

    name = TP->query_real_name();
    write("You ring the bell.\n");
    tell_room(TO, "PLING - PLING\n");
    
    if (!hotel_keep) 
	write("Hmm..., no one seems to be here.\n");
    else {
	if (present(hotel_keep)) {
	    hotel_keep->command("glare " + name);
            if (aid) {
                remove_alarm(aid);
                aid = 0;
            }
	} else 
	    set_alarm(2.0, -1.0, &get_keep(TP));
    }
    return 1;
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (!ob || !living(ob)) return;
    
    if (!hotel_keep || hotel_keep == ob) return;
    
    if (aid) return;
    
    aid = set_alarm(5.0, -1.0, rem_keep);
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
    if (!hotel_keep || !present(hotel_keep))
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

    price = 144;

    NF("You failed to rent a room.\n");

    if (sizeof(money_arr = pay(price, TP, pay_type, 0, 0, get_type)) == 1) {
	if (money_arr[0] == 2) {
	    hotel_keep->command("say You don't have any " + pay_type +
                                " coins, silly " + TP->query_nonmet_name() +
                                ".");
	    return 0;
	}
	if (money_arr[0] == 1) {
            hotel_keep->command("say The room is a little too " +
				"expensive to pay for in " + pay_type +
    			    	" coins, silly " +
				TP->query_nonmet_name() + ".");
	    return 0;
	} else {
            hotel_keep->command("say I don't think so!  You are "
			     + "going to need more money than that, silly "
			     + TP->query_nonmet_name() + ".");
	    return 0;
        }
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You rent a room and pay " + coin_pay_text + ".\n");
    if (coin_get_text) write("You get " + coin_get_text + " back.\n");
    
    name = TP->query_real_name();

    seteuid(getuid());
    key = clone_object(DOBJ + "stumble_key");
    key->move(hotel_keep);
    key->add_name("_stumble_room_key");
    key->add_prop("_stumble_room_renter", name);
    hotel_keep->command("give key to " + name);
    if (present(key, hotel_keep))
	hotel_keep->command("drop key");
    say(QCTNAME(TP) + " rents a room.\n");
    
    if (!aid)
        aid = set_alarm(10.0, -1.0, rem_keep);
    
    return 1;
}

/*
 * Function name: get_keep
 * Descrition:    an alarm to move the hotel keeper here
 *                (assumes the hotel_keeper is in the game)
 * Argument:      who     should be this player.
 */
public void
get_keep(object who)
{
    if (!hotel_keep) return;
    
    if (!present(hotel_keep))
        hotel_keep->move_living("xx", TO);
    
    if (who && present(who, TO)) {
        hotel_keep->command("say Welcome!");
	hotel_keep->command("smile " + who->query_real_name());
        hotel_keep->command("say Do you want to rent a room?");
    }
}

/*
 * Function name: rem_keep
 * Descrition:    an alarm to move the hotel keeper back into
 *                the private room
 * Arguments:     ob    should be the hotel_keeper
 */
public void
rem_keep()
{
    aid = 0;
    
    if (!hotel_keep) return;
    
    if (present(hotel_keep)) 
	tell_room(TO, QCTNAME(hotel_keep) +
		  " leaves through a door behind the counter.\n");
    hotel_keep->move(DAB_TOWN + "stumble_priv");
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

    key = present("_stumble_room_key", TP);
    if(!key || key->query_prop("_stumble_room_renter") != TP->query_real_name()) {
	write("You aren't entitled to go there!\n");
	return 1;
    }

    room = find_object(DAB_TOWN + cell);
    if (!room)
	return 0;

    obs = all_inventory(room);
    for (i = 0; i < sizeof(obs); i++) 
	if (living(obs[i])) {
	    write("That room is already occupied by someone. " +
		  "Try another one.\n");
	    return 1;
	}

    return 0;
}
