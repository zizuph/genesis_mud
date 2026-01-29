/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bank.c
 *
 * The Ribos bank
 *
 * Vader
 * Recoded by Sorgum 950602
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
 *  Modified: June 2008, by Lilith
 *      - made this a true bank
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/bank";
inherit "/d/Genesis/delivery/office";

#define PACKET_COUNT	3
#define OFFICE_NAME	"the Bank of Ribos in Terel"


/*
 * Function name: query_moving_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/w_knight",
	     RIBOS_DIR + "monster/w_knight"});		 
} 

void
fee()
{
    set_bank_fee(20);
    config_trade_data();
}




/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    object gndep;
    ::create_room();
    set_short("Bank");
    set_long("You are in the Ribos Bank.  It looks " +
	     "like any other bank.  It's drab and dingy, and there are " +
	     "rusty steel bars guarding everything.  There is a bank " +
	     "counter where the banker will exchange some money for you.\n"+
	     "A plaque and a poster.\n");
    add_cmd_item("plaque", "read", 
             "@@standard_bank_sign");	
    add_item("poster","@@delivery_poster@@");
    add_item("plaque", 
        "It tells you how to exchange your money.\n");
    add_cmd_item("plaque", "read", 
        "@@standard_bank_sign");	
    add_item("poster","@@delivery_poster@@");


    add_exit(RIBOS_DIR + "road11", "southeast", 0);

    FIX_EUID;

    set_office( OFFICE_NAME, PACKET_COUNT );
 
    config_default_trade();
    config_trade_data();
  
    gndep = clone_object("/d/Genesis/obj/deposit");
    gndep->set_short("deposit");
    gndep->set_no_show_composite(1);
    gndep->move(this_object());

    clone_object(RIBOS_DIR + "doors/v_door_in")->move(TO);
}

int
change(string str)
{
    fee();
    return ::change(str);
}

int
test(string str)
{
    fee();
    return ::test(str);
}

int
minimize(string str)
{
    fee();
    return ::minimize(str);
}

string
standard_bank_sign()
{
    fee();
    return ::standard_bank_sign();
}

void 
init()
{
    // load office add_actions()
    init_office();
    bank_init();    
    ::init();
    
} 
