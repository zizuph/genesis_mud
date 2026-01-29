/* Kip's Clothing Store in Kendermore by Gwyneth May 17, 1999 */
/* Based on the General Shop in Calia by Maniac         */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit "/lib/shop";
inherit KENDERMORE_IN;
#define STORE_ROOM KROOM + "kip_store2"

object kip;


void
reset_kendermore_room()
{
    if (!objectp(kip))
    {
        kip = clone_object(KNPC + "kip");
        kip->move(this_object());
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
    set_short("Kip's clothing store");
    set_long("The room is oddly bare for a store. You wonder if " + 
        "someone borrowed all of the goods. There is a wooden counter " + 
        "at the back of the store, and a brightly clad kender stands " + 
        "behind it. There is a sign firmly nailed down to the counter " + 
        "with instructions.\n");
    add_item(({"counter", "wooden counter"}), "Several small items are " + 
        "spread out across the counter. It seems the clerk is sorting " + 
        "her pouches.\n");
    add_cmd_item("sign", "read", "@@do_read");
    set_store_room(KROOM + "kip_store2");
    add_exit(KROOM + "street44", "southwest", 0);
    add_invis_exit(STORE_ROOM, "south", "@@wiz_check");

    INSIDE;
    query_store_room()->load_me();
    reset_kendermore_room();
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
    write("There is no obvious exit south.\n");
    return 1;
}

int
do_read(string str)
{   
    if (str == "sign")
    {
        write("   Welcome to Kip's Clothing Shop!\n" + 
              "   I sell a variety of vests, leggings,\n" + 
              "   blouses, capes, cloaks, shirts and\n" + 
              "   boots! You can list what I have in\n" + 
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
    NF("The shopkeeper is not here to buy from.\n");
    if (!P(kip, TO))
	return 0;

    if (KMASTER->query_enemy(this_player()->query_real_name()))
    {
        write("The shopkeeper won't deal with the likes of you!\n");
        return 1;
    }

    return ::do_buy(str);
}

