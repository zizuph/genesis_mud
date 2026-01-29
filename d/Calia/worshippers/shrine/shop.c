/* 
 * An example shop coded by Nick, some Ideas and part of code taken from 
 * Tricky's shop in hobbitown.
 */

inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include <stdproperties.h>
#include "defs.h"

#define STORE_ROOM WOR_SHRINE+"store"

void
create_room()
{
    config_default_trade();
    set_short("An equipment store");
    set_long("This is the equipment shop for the Elemental disciples.  "+
        "Here you may purchase equipment, clothing, and components "+
        "for use in your journies.  You see several things behind "+
        "the counter that look like they may be interesting to "+
        "you.  There is a sign on the counter that you can read "+
        "containing more instructions.  West you see a storeroom "+
        "where some equipment is kept, and back to the east you "+
        "see the common room of the Shrine.\n");

    add_exit(WOR_SHRINE+"common","east");
    add_exit(STORE_ROOM, "west", "@@wiz_check");
    /*
    add_exit(WALKER_SHRINE+"herbshop","north",0,1);
    */

    add_item("sign", "A nice looking sign for you to read.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(STORE_ROOM);
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}
int
shop_hook_allow_sell(object ob)
{
    notify_fail("I'm sorry, we do not buy anything at this shop.\n");
    return 0;
}
