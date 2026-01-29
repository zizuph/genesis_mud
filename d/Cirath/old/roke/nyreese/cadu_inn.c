/*
 * cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Modified copy of inn in solace, coded by Nick */
/* Improved (?) by Ged & Gresolle */
/* Changed to use /lib/pub by Glindor */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Cirath/roke/lib/pub";

#include "defs.h"

#define CDIR ROKEDIR + "obj/"

object tika; /* Kalufs */

/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_room()
{
    if (!tika)
    {
	tika = clone_object(ROKEDIR + "npc/kalufs");
	tika->move_living("home", TO);
    }
    if (!present(tika, TO))
    {
	tika->move_living("home", TO);
    }        
}

/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_room()
{
    config_pub();
    set_short("The Fisherman's Friend");
    set_long(
	"You are in the Fisherman's Friend Inn. There is a menu on the bar. " +
	"There are lots of drunken sailors dancing on the tables and chairs." +
	" It's very noisy but still you feel strangely comfortable here. " +
	"Upstairs is a small room where you can stay for the night.\n");

    add_item("bar", "A nice looking wooden bar with a menu on it.\n" +
             "A fishing net is hanging in the roof.\n" +
             "There is a small plaque attached to the bar.\n");
    add_item(({"menu", "list", "pricelist"}), "@@read");
    add_cmd_item(({"menu", "list", "pricelist"}), "read", "@@read");
    add_item("plaque", "This bar was borrowed from Nick and altered " +
      "by Gresolle.\n");
    add_item("chairs", "They smell like fish.\n");
    add_item("tables", "They have many pictures carved by drunken sailors.\n");

    add_exit("cadu_out", "south"); /* open air cafe */
    add_exit("cadu_hotel", "up", "@@block");

    add_article(({"silly", "ale"}), CDIR + "ale", 10);
    add_article(({"wine", "bordeaux","bordeaux wine"}), 
                CDIR + "wine", 72);
    add_article(({"beer", "cadu", "cadu beer"}), 
                CDIR + "cadubeer", 21 * 12);
    add_article(({"ahlgrens", "coaches", "cars", "stagecoaches", 
                  "ahlgrens stagecoaches", "ahlgrens cars"}),
                CDIR + "ahlgrens", 32);
    add_article(({"herring", "barbecued herring"}), CDIR + "herring", 12);
    add_article(({"salmon", "raw spiced salmon", "spiced salmon"}),
                CDIR + "salmon", 6 * 12);
    add_article(({"ticket", "hotel ticket"}), CDIR + "ticket", 144);

    INSIDE;
    reset_room();
}

int
block()
{
    write("Due to recent earthquake damage, the rooms " +
          "upstairs are unavailable until further notice!\n");
    return 1;
}

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
string
read(string str)
{
    return
        "   Ale                         10 copper\n" +
        "   A glass of finest Bordeaux  72 copper\n" +
        "   A pint of Cadu Beer         21 silver\n" +
        "   Barbecued Herring            1 silver\n" +  /*  64 g */
        "   Raw Spiced Salmon            6 silver\n" +  /* 200 g */
        "   Ahlgrens Stagecoaches       32 copper\n" +  /* 114 g */
        "   A hotel ticket               1 gold\n" +
        "\n" + pub_std_usage_string();
}

/*
 * Function name: pub_hook_may_order
 * Description:   Check if the player may order.
 *                If not, set notify_fail.
 * Returns:       1/0
 */
int
pub_hook_may_order()
{
    if (!tika || !present(tika, TO))
    {
        NF("Kalufs isn't here to answer your call.\n");
	return 0;
    }
    return 1;
}

/*
 * Function name: pub_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 *                players - The player(s) recieving the order
 *                pay     - The coins payed.
 *                change  - The coins got in change.
 */
void
pub_hook_player_buys(object ob, int price, object *players, object buyer,
                     string pay, mixed change)
{
    write("Kalufs gets to work.\n");
    ::pub_hook_player_buys(ob, price, players, buyer, pay, change);
}
