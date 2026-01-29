/*
 * Creator: Shadowlynx
 * Date   : December 4, 1999
 * Updated: 
 * By Whom: 
 * File   : /d/Genesis/start/human/sparkle/square_nc.c 
 * Purpose: The north central location in Sparkle's market square.
 * Comment:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

void
create_room()
{
    set_short("market square");
    set_long("\nYou're standing on a market square.\n"+
        "Many farmers and merchants are trying to sell their crops and goods. " +
        "Better keep a firm hand on your purse. There is a fresh water well in " +
        "the middle of the square. The harbour is east of here, the shop is " +
        "south and the road towards the gates is leading west. On the north " +
        "side of the square, the treasury of Genesis is located.\n");

    add_item( ({ "office", "treasury" }), "On the north side of the square, the " +
        "office of the treasurer of Genesis is located. In the treasury, the " +
        "records of the treasurer are kept.\n");
    add_item("square","It is a quite ordinary market square.\n");
    add_item("well","The well seems old and well used. Nevertheless it is kept\n"+
        "in good working order. Peering down into the darkness of\n"+
        "the well, you see a reflection in the water surface about\n"+
        "3 meters away.\n");
    add_item("shop","The shop is probably one of the major places of commerce\n"+
       "in this region. It should be able to supply you with the\n"+
       "items you need although the price may at times be high.\n");
    add_item("people","Oh they're just commoners. Nothing special about them.\n");

    add_exit(TOWN_DIR + "road4","west");
    add_exit(TOWN_DIR + "shop","south");
    add_exit(TOWN_DIR + "pier4","east");
    add_exit("/d/Genesis/obj/donation/office", "north");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_cmd_item( ({ "from well", "water" }), "drink",
        "You take a sip of water from the well.\n" );

    clone_object("/d/Genesis/obj/donation/column")->move(this_object(), 1);
/*
  clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
  */
}

int
climb_down(string str)
{
    if (str != "down")
    {
        NF("Exactly where do you want to climb?\n");
        return 0;
    }

    if (TP->query_skill(SS_CLIMB) > random(30))
	TP->move_living("climbs down the well", TOWN_DIR + "well");
    else
    {
        write("You don't seem to be able to get a good hold. You faallllll...\n");
	TP->move_living("climbs down the well", TOWN_DIR + "well");
        TP->heal_hp(-100);
        if (TP->query_hp() <= 0)
            TP->do_die(TO);
        else
            write("Ouch! That really hurt.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(climb_down, "climb");
}
