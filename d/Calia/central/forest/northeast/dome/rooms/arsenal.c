// ROOM:  Dome - Arsenal
//        DOME_ROOMS + arsenal

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.
        Store code drived from /d/Genesis/doc/examples/trade/shop.c

        PURPOSE
        Here dedicated craftsmen work diligently, improving
        thier skills and also selling wonderful weapons to
        visitors and members.
 
        AREA HISTORY
        Origionally an arsenal, the hedonists were very
        annoyed by the intense heat and loud noise involved
        in making and repairing metal weapons. So they came
        up with wood and leather substitute weapons, and
        mastered using them. Metals are now only used to
        ornament weapons.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";
inherit "/lib/shop";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome arsenal");

    set_long("Racks for holding weapons cover the walls of this colourful " +
        "room. Workbenches are covered with tools and partially completed " +
        "weapons, as well as leather, silk, and other supplies.\n");

    /* ITEMS */

    add_item(({"racks", "rack"}),
        "Beautifully carved racks of stained hardwood cover the walls, " +
        "decorative as well utilitarian. There are racks to hold every " +
        "kind of weapon, though they are mostly empty.\n");

    add_item(({"weapon", "weapons"}),
        "The racks have a few weapons in them for sale, type 'list' to " +
        "see them.\n");

    add_item(({"workbench", "workbenches", "tool", "tools", "leather",
        "silk", "silks", "supplies"}),
        "Silks, leather and all manner of supplies and tools cover " +
        "the workbenches in this room. They are used to construct and " +
        "decorate nonmetal weapons.\n");

    add_item(({"wood", "hardwood"}),
        "The stained hardwood of the racks is beautifully carved and " +
        "decorated.\n");

    /* EXITS */

    /*
     * Add an exit to the store-room, the first parameter is the
     * path to the store, the second command to enter it and the
     * third parameter is a VBFC call to block all mortals players
     * from using the exit.
     */
    add_exit("arsenal_store", "up", "@@check_wizard@@");
    add_exit("common", "northwest", 0, 01);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    /* This sets the storeroom where goods are taken from/sent to */

    set_store_room(DOME_ROOMS + "arsenal_store");
    config_default_trade();

    }

/* This is to keep the shop from buying things.. it only sells.
 */
int
shop_hook_allow_sell(object ob)
    {
    notify_fail("I'm sorry, we don't buy anything at this shop.\n");
    return 0;
    }


/*
 * You must do this to add the shop-commands to the player.
 */
void
init()
{
    ::init();
    init_shop();
}

/*
 * We do not want mortal players to walk into the storeroom and help
 * themselves.
 */
int
check_wizard()
{
    /* wizards may use the exit.
     */
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    /* however, mortal players cannot...
     */
    write("A magical force keeps you from going there.\n");
    return 1;
}