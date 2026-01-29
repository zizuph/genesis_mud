/* 
 *  An example shop coded by Nick, some Ideas and part of code taken from 
 *  Tricky's shop in Hobbitown.
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#include DELIVERY

inherit SOLINROOM;
inherit "/lib/shop";
inherit DELIVERY_OFFICE;

#define STORE_ROOM TDIR + "store"
#define MAXLIST    30
#define TORCH      OBJ + "torch"


/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_solace_room()
{
    config_default_trade();
    set_short("The local shop");
    set_long("You are in the local shop. Here you can sell and buy stuff. " +
	     "You can also use value or list commands, 'list armours', " +
	     "'list weapons', 'list <name>' and 'list' works too. " +
	     "There is also a small sign to read with more instructions. " +
	     "A new poster has been hung onto one of the walls. The exit " +
	     "from the shop is to the west. There is also a locked door " +
	     "leading north.\n");

    add_exit(TDIR + "bridge_walk12", "west", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_item("bridge",
        "It's made out of wood and look safe to travel, in fact, most\n" +
        "people does here in solace.\n");
    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");
    add_item("poster","It's readable.\n");
    add_cmd_item("poster","read",
		 "Delivery Office Solace\n" +
		 "'Ask for a delivery tour' if you wish to help out and earn " +
		 "a few coins.\n All you need to do with the packet you " +
		 "receive then is to bring it to\n its destination where you " +
		 "will also receive the payment. Use 'deliver\n packet' to " +
		 "deliver your packet at its destination. 'Return packet' " +
		 "is\n for packets which are not destined for this office " +
		 "and which do not\n have this office set as origin.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    set_store_room(STORE_ROOM);
    set_office("the Shop in Solace",15);
    add_content(TORCH);
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
    init_office(); /* Get the commands from the delivery office */
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    if (this_player()->query_wiz_level())
      	return 0;
    write("Some magic force keeps you from going north.\n");
    say(QCTNAME(this_player()) + " tries to go north but fails.\n");
    return 1;
}


void
print_message(string str)
{
    write("The shopkeeper says: " + str + "\n");
}
