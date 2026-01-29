/* This file was taken from the /doc/examples/trade (The
 * Last Home) Modified by Marisol (1/27/98) To be used in
 * new village of Re Albi. 1998 */
/* Modified by Marisol (07/20/98) to be used for the village of
 * Ovejuno in Emerald. */

inherit "/d/Emerald/std/room";
inherit "/lib/pub";
#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#define LANIER OV_VILLAGE_NPC + "lanier"

object lanier;

void reset_room()
{
 if(!objectp(lanier))
 {
 lanier=clone_object(LANIER);
 lanier->move(TO);
 lanier->command("walks in.");
 }
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */

nomask void
create_emerald_room()
{
    set_short("The Drunkard Ram");
    set_long("You are in the Drunkard Ram, the only pub in this "+
        "village. A happy fireplace cracks cozily at the left of "+
        "the bar. A flight of stairs goes up to the second floor "+
        "where the bastender lives with his family. Sturdy chairs "+
        "and tables are scattered in the room with some customers "+
        "talking in low voices. A ruddy bastender attends the "+
        "polished oak bar. A menu is hanging in the wall behind "+
        "the bar.\n");

    add_item("bar",
        "This is a very nice-looking bar of oak wood. Its polished "+
        "surface shines with the reflect light from the "+
        "hearth.\n");

    add_item("fireplace",
        "A stone fireplace. Right now a cozy fire burns happily "+
        "inside, warming the pub and feeling the air with a nice "+
        "smoky smell of apple wood.\n");

    add_item("customers",
        "Some villagers are enjoying their meal quietly in the pub. "+
        "They seem regular customers and they don't look like the "+
        "ones that like to talk with strangers.\n");

    add_item("stairs",
        "A wooden stair that goes up to the second floor. But it is "+
        "close to the general public.\n");

    add_item("bastender",
        "The bastender is a pleasant enough fellow with a ruddy "+
        "completion and a quick smile. He will serve you quietly "+
        "and fast any of your order from the menu.\n");

    add_item("menu", "It has a lot of readable words on it.\n");

    add_item("chairs",
        "They are made out of a durable wood to withstand "+
        "rough use.\n");

    add_item("tables", "They are worn-down with use.\n");

    add_cmd_item("menu", "read", "@@read");           

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_drink( ({ "ale", "ales", "fruity", "fruity ale" }),
        "ale", "fruity", 100, 4, 12, 0, 0,
        "A fruity ale common in the region. It is very refresing.\n", 0);

    add_drink( ({ "wine", "wines", "dry", "dry wine" }),
        "wine", "dry", 200, 20, 72, 0, 0,
        "A dry, red wine from the town of Lisardi. A mellow flavor "+
        "that can satisfy the most exigent palate.\n", 0);

    add_food( ({ "bread", "breads" }),
        "bread", "brown", 30, 25, 0, 0,
        "It smells and tastes delicious.\n", 0);

    add_food( ({ "fish", "fish chowder", "chowder", "chowder" }),
        "chowder", "chowder", 65, 80, "bowl of fish chowder",
        "bowls of fish chowders",
        "A hearty and seasoned chowder. The fish come fresh "+
        "from the local brook, so this is one of our freshest dishes "+
        "in the pub.\n", 0);

    add_food( ({ "mutton", "roast", "plate of spicy roast mutton", 
        "plate", "plates" }),
        "mutton", "roast", 110, 110, "plate of roast mutton",
        "plates of roast goat",
        "The specialty of the house. A very earthy and wholesome "+
        "dish made with the local sheep and a secret recipe.\n", 0);

    add_exit("village_ov05.c", "north");
    reset_room();


}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()                                                          
{
    ::init(); /* Since it's a room this must be done. */

    init_pub();
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write("" +
        "   Fruity ale                12 cc\n" +
        "   Lisardi dry wine          72 cc\n" +
        "   brown bread               25 cc\n" +
        "   Fish chowder              80 cc\n" +
        "   Plate of roast mutton     210 cc\n" +
        "Try 'buy ale with gold' if you wanna specify what to\n" +
        "pay with, or 'test buy ale' to see what would happen\n" +
        "if you typed 'buy ale'. 'buy 10 ales' would get you\n" +
        "ten ales from the bar, but it takes a little while to\n" +
        "give them all to you.\n");                        

    return 1;
}                                                              
