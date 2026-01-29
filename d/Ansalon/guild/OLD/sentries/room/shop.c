#include <stdproperties.h>
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <std.h>

inherit "/d/Krynn/std/room";
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#define STORE_ROOM    GUILD_ROOM + "store_room"

string
query_to_jail()
{
    return "west";
}

void
create_krynn_room()
{
    set_long("This is a huge room, it functions as the store for "
        + "the Knights of Palanthas, the wall consists of white "
        + "stone blocks, in the center of the room there is a "
        + "counter with a small sign on");
    config_default_trade();
    set_money_greed_buy(70);
    set_money_greed_sell(65);
    set_short("A huge shop");

    add_exit("center_room","west",0,0);
    add_invis_exit(STORE_ROOM,"east","@@wiz_check");

    set_store_room(STORE_ROOM);
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
}


void
init_shop()
{
    add_action("do_read", "read");
    add_action("do_list", "list");
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_show","show");

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

    write("There is no obvious exit east.\n");
    return 1;
}


int
do_buy(string str)
{
    if (check_cheater(this_player()))
        return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (check_cheater(this_player()))
        return 1;
    return ::do_sell(str);
}
