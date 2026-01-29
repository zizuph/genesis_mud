/* 	this is a room of the crystalline palace
        It inherits and includes kroug raid handler code 
 
    coder(s):   Glykron & Maniac
 
    history:  
                6/4/96     tidied up kroug handling         Maniac
                12/12/95   vandalism possibility added      Maniac
                22/9/95    kroug_palace_room inherited      Maniac
                17.5.95    tax raised to 25%                Maniac 
                13.2.93    modified                         Glykron
                30.11.92    created                         Glykron
 
    purpose:	change money here
    exits:      east to entrance, north to lateroom, northeast to trainroom
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/lib/bank";
inherit "/d/Calia/std/kroug_palace_room";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

#define BANK_FEE 25

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    set_short("The Palace Bank");
    set_long(
	"This is a large trapezoidal-shaped room with north and east walls " +
	"slanting away from you to the southwest.  " +
	"This room serves the function of a bank.  " +
	"It is run by Calians, who decided that setting up a bank would be " +
	"quite profitable.  " +
	"Behind an iron-barred counter is a Calian who looks like he " +
	"wouldn't mind taking some of your money.  " +
	"A sign hangs by the counter.  " +
	"\n");

    add_item( ({ "calian", "clerk" }),
	"The Calian is trying to estimate how much money you are carrying " +
	"with you.\n");

    add_item("sign", "@@sign_long");
    add_cmd_item("sign", "read", "@@sign_long");

    add_item( ({ "counter", "iron-barred counter" }),
	"You see no way to get behind the counter, since it is totally " +
	"enclosed by thick iron bars.\n");

    add_item( ({"iron bars", "bars", "thick iron bars"}), "Thick iron " +
        "bars protect the counter of the bank. They look in perfect " +
        "condition.\n");
    add_item_possible_vandalism("iron bars", "Thick iron bars " +
         "protect the counter of the bank.", ({"dent", "scratch"}), 70); 
    
    add_exit(ROOM("light_entrance"), "east", 0);
    add_exit(ROOM("light_late"), "north", 0);
    add_exit(ROOM("light_trainroom"), "northeast", 0);
    
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    config_default_trade();

    set_bank_fee(BANK_FEE);
	/* To set the exchange fee (% of changed amount) */
    
    config_trade_data();
}

/*
 * Function name: sign_long
 * Description:   returns a string with a sign message
 * Arguments:     none
 * Returns:       message string
 */
string
sign_long()
{
    return
	"On the sign you read:\n\n" +
	"We change copper, silver, gold, and platinum coins.  " +
	"Simply mention the kind you want to change, and the kind you want " +
	"to get.  " +
	"Our bank provides you with a cheap way to relief you of the burden " +
	"of heavy coins.  " +
	"For each transaction we ask only a " + BANK_FEE + "% fee.  " + "\n" +

	"This is an example of what you can do:\n" +
	"    change copper and silver to gold\n" +
	"  This would make you change all your copper and silver coins\n" +
	"  into as much gold as possible.\n" +
	"    test change copper and silver to gold\n" +
	"  This would show you the out come of the command behind\n" +
	"  the 'test' word.\n" +
	"    change 1 platinum to copper\n" +
	"  This would change 1 platinum coin to copper coins.\n" +
	"    change platinum to 100 silver\n" +
        "  This would change platinum coins to 100 silver coins + " +
	"the change\n" +
	"  that would be left from the platinum coins needed after " +
	"100 silver\n" +
	"  coins has been given.\n" +
	"    minimize coins\n" +
	"  This changes all coins into the most valuable types possible.\n" +
	"\n";
}

/*
 * Function name: init
 * Description:   Initalize the bank actions
 */
void
init()
{
    ::init();
    init_vandalism();
    bank_init();
}
