/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * - Added housing entrance for Bree h1
 *   Varian, September 2021
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;

object human;

void
create_road_room()
{

    set_areadesc("large");
    set_area("busy");
    set_areaname("road");
    set_land("Bree");

    add_my_desc("The road is surrounded by houses and other " +
        "buildings. To the east is a fortified building and to the " +
        "south is another large building. A large, quaint house " +
        "is immediately to the west, complete with a doorman on " +
        "duty. Looking north and east you see a large inn. The " +
        "road runs north and southeast.\n");

    add_item( ({"prancing pony", "prancing pony inn", "the prancing pony", 
            "the prancing pony inn", "inn"}),
        "The large inn stands to the northeast. It is clearly one " +
        "of the biggest buildings in Bree.\n");
    add_item( ({"fortified building", "bank"}),
        "The fortified building looks strong with large iron bars " +
        "on the window. A sign swings from above the door.\n");
    add_item( ({"sign", "square sign"}),
        "It is square and swings in the breeze. " +
        "Three gold coins are painted on it.\n");
    add_item( ({"large building", "shop", "holiday shop"}),
        "It is large and wide. It is the famous holiday shop of Bree. The " +
        "shop is opened during the holidays where travellers from all " +
        "over come to get delicious food and drinks plus nifty items " +
        "to celebrate with.\n");
    add_item( ({"doorman", "door man", "servant"}),
        "This doorman is wearing a sharp looking uniform. His job is " +
        "apparently to ensure that nobody enters the large house to the " +
        "west without permission.\n");
    add_item( ({"path", "cobbles", "cobblestone", "cobble",
            "cobblestone path"}),
        "A narrow cobblestone path leads off the road to the door of a " +
        "large, quaint house where a uniformed doorman stands watch.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    room_add_object("/d/Gondor/houses/locations/bree/door/h1door_out");

    set_add_houses();
    set_add_ger();
    reset_shire_room();

    add_exit(ROAD_DIR + "broad02", "north");
    add_exit(ROAD_DIR + "broad04", "southeast");
    add_exit(TOWN_DIR + "hshop", "south", "@@block_room@@");
    add_exit(TOWN_DIR + "bank", "east");

}

string
read_sign()
{
    return "On the sign, above the coins, painted in bright silver " +
        "letters are the words: 'Bank of Bree'.\n";
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("The door is locked. Come back next holiday for more " +
        "surprises, foods, and drinks!\n");
    return 1;
}
