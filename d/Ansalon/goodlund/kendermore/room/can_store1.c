/* Jenna's Candle Store in Kendermore by Gwyneth May 20, 1999 */
/* Based on the General Shop in Calia by Maniac         */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit "/lib/shop";
inherit KENDERMORE_IN;
inherit STREET_DESC;
#define STORE_ROOM KROOM + "can_store2"
object jenna;


void
reset_kendermore_room()
{
    if (!jenna)
        if (!P(jenna, TO))
    {
	jenna = clone_object(KNPC + "jenna");
	jenna->move(this_object());
    }
}

/*
* Function name:   create_room
* Description:     Initialize this room
* Returns:
*/

void
create_room()
{
    config_default_trade();
    set_short("Jenna's candle store");
    set_long("The door stands wide open, propped by a red brick. Vats of " + 
             "hot wax line a large table in the back of the store, and " + 
             "a gray-haired kender stands peering into them. A door leads " + 
             "into a cluttered back room.\n"); 
    add_item(({"brick", "red brick"}), "It keeps the door from swinging " + 
        "shut.\n");
    add_item("door", "Which door?\n");
    add_item("front door", "You can see the street outside.\n");
    add_item("back door", "A door on the east wall leads into another " + 
        "room.\n");
    add_item("table", "It looks sturdy. It better be with all those vats " + 
        "of hot wax on them!.\n");
    add_item(({"wax", "hot wax"}), "It's too hot to touch. This is what " + 
        "the candles are made of. There are a few different colours.\n");
    add_item("vats", "They are made of metal and filled with hot wax.\n");
    add_item("street", "@@street_descr@@\n");
    add_cmd_item(({"vat", "vats"}), ({"get", "take", "pick", "touch"}),
        "@@do_vats");
    add_cmd_item("sign", "read", "@@do_read");
    set_store_room(KROOM + "can_store2");
    add_exit(KROOM + "nowhere", "east","@@no_go");
    add_exit(KROOM + "street51", "west", 0);
    add_invis_exit(STORE_ROOM, "south", "@@wiz_check");

    INSIDE;
    query_store_room()->load_me();
    reset_kendermore_room();
}

string
do_vats ()
{
    write("Ouch! You burn your fingers as you touch the vats of hot " +
        "wax!\n");
    say(QCTNAME(TP) + " gets burnt fingers from the vats of " + 
        "hot wax.\n");
    TP->heal_hp(-10);
    return "";
}

int
no_go()
{
    write("The room is too cluttered to enter now. Perhaps the owner will " + 
        "clean it up a bit later.\n");
    return 1;
}
    
void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
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

    init_shop();
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
    object tp;

    tp = TP;
    if (tp->query_wiz_level())
	return 0;
    write("There is no obvious exit west.\n");
    return 1;
}

int
do_read(string str)
{   
    if (str == "sign")
    {
        write("   Welcome to Jenna's Candle Store! I\n" + 
              "   sell large beeswax candles for great\n" + 
              "   prices! You can list what I have in\n" + 
              "   stock, and I can show each piece to\n" + 
              "   you. I don't buy anything here, sorry!\n");

	return 1;
    }
    else
    {
	NF("Read what? The sign?\n");
	return 0;
    }
}

int
do_sell(string str)
{
    NF("You may not sell items here.\n");
    return 0;
}

int
do_buy(string str)
{
    if (!P(jenna, TO))
    {
        NF("The shopkeeper is not here to buy from.\n");
	return 0;
    }

    if (KMASTER->query_enemy(this_player()->query_real_name()))
    {
        write("The shopkeeper won't deal with the likes of you!\n");
        return 1;
    }

    return ::do_buy(str);
}

