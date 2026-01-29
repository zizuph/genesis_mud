/*
 * /d/Cirath/tyr/outskirts/tcamp/camp_1.c
 *
 * Inside the market
 *
 * Eridani - May, 2016
 *
 */

#pragma strict_types
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"

inherit "/d/Cirath/tyr/outskirts/tcamp/marketbase";

/*
 * Function name:        create_market_room()
 * Description  :        Creates a market room from the base file
 *                       /d/Cirath/tyr/outskirts/tcamp/marketbase.c
 */
void
create_market_room()
{
    set_items_tyr();
    set_items_market();

    set_short("Inside the Aarakocra's trading camp");
    set_long("The bright sun beats down on you as soon as you walk "+
        "around the market. The booths were set up by the Aarakocra "+
        "traders in order to showcase their wares while they wait for "+
        "King Kalek to approve the trade agreements with their elders.\n");
    add_item(({"booths", "booth", "market"}),
        "As you glance around at all the booths, you can tell that the "+
        "Aarakocra have brought out all of their best goods to entice "+
        "King Kalek into agreeing to trade. The booths have an array of "+
        "items made from the trademark items from the village of ice and "+
        "feathers. You wonder how the ice isn't melting in the harsh "+
        "desert heat!\n");
    add_item(({"item", "wares", "good", "goods"}),
        "As expected, the goods for sale are made of Winter's Nest's "+
        "trademark exports of ice and feathers. There looks to be quills "+
        "and fans from feathers, as well as musical instruments, bottles "+
        "and sculptures made out of ice.\n");
    add_item(({"bird", "trader", "traders", "birds"}),
        "The Aarakocra stands between 7 and 8 feet tall and has black "+
        "eyes and a grey beak with a wing span of at least 20 feet. "+
        "At the center of each wing is a three-fingered hand with an "+
        "opposable thumb.\n");

    set_no_exit_msg(({"southwest","northwest","northeast","southeast"}),
        "You try walking through a tent to no avail. Perhaps it might " +
        "be easier to try move in another direction?\n");
    
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM;

    add_exit(TYR_TCAMP+"camp_5.c", "north", "@@market@@", 1);
    add_exit(TYR_TCAMP+"camp_3.c", "east", 0, 1);
    add_exit(TYR_SLAVE+"rd_sw_05.c", "south", 0, 1);
    add_exit(TYR_TCAMP+"camp_2.c", "west", 0, 1);
}
/* create_market_room */

/*
 * Function name:        market
 * Description  :        Describes walking through the market
 */
int
market()
{
    write("You weave your way through a winding maze of tents and booths " +
        "as you move into a different part of the market.\n");
    return 0;
}
/* market */