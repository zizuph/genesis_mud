// Ziggurat Garden shop (ZIG_RL3 + "garden.c")
// creator(s):  Zielia 2006
// purpose:     Ziggurat shop where players can buy flowers and picnic
//		baskets.
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;
inherit "/d/Avenir/inherit/shop";

#define STORE_ROOM   (ZIG_RL3 + "store_garden")


private static object maree;

public void
reset_room(void)
{
    fix_keeper();

    if (!objectp(maree))
    {
	maree = clone_object(ZIG_MON + "maree");
	maree->equip_me();
    }
}

public void
zig_room(void)
{
    set_short("Ziggurat Garden Shop");
    set_long("The echo of water running over stone somewhere nearby fills "+
	"this chamber. Hundreds of colorful jewels sparkle amidst the "+
	"carved black walls. Source-crystals set amongst the jeweled bas "+
	"relief cast scintillating light on flower filled urns standing on "+
	"the dull black floor. At the center of this junction is a round "+
	"stand where visitors may make their purchases before entering "+
	"the garden through the short, arched tunnels to the southwest and "+
	"southeast or returning to the Ziggurat through the dimmer "+
	"corridor to the north. @@see_nearby@@\n");

    set_store_room(STORE_ROOM);
    set_keeper_file(ZIG_MON + "daisy");
    set_favoured_race(({"elf", "gnome"}));
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_money_greed_buy(50);

    add_exit("room6", "north", 0);
    add_exit(ZIG_RLG + "room1", "southwest", "@@garden_exit");
    add_exit(ZIG_RLG + "room12", "southeast", "@@garden_exit");
    add_exit(STORE_ROOM, "store", wiz_check, 0, 1);

    add_item("sign", "@@read_me");

    add_item(({"walls", "wall"}),
        "The walls and high ceiling are made of smooth, black stone, "+
        "like most of the Ziggurat, but instead of a glossy polish, it is "+
        "highly carved with leafy, climbing vines creating a continuous "+
        "pattern in bas relief. Evenly spaced along the vines are jeweled "+
	"flowers, petals made of sparkling gems of every color, surrounding "+
	"a tiny, glowing Source crystal at the center.\n");
    add_item(({"center", "centers", "crystal", "crystals",}),
        "Firmly set into the black stone wall, at the center of every "+
        "jeweled flower, are tiny, glowing source crystals, their cumulative "+
        "light filling the chamber and making the jeweled walls sparkle.\n");
    add_item(({"petals", "jewels", "jeweled flowers", "carved flowers"}),
        "Precious gems of every hue are set into the wall to form the petals "+
        "of delicately carved flowers. You note rubies, sapphires, pink "+
	"tourmalines, diamonds, emeralds and violet spinels amoungst others, "+
	"all surrounding tiny, glowing source crystals.\n");
    add_item(({"floor", "ground",}), "The black stone of the floor is "+
	"covered with flower filled urns and a somewhat dusty path "+
	"winding between them.\n");
    add_item(({"counter", "round counter", "stand", "round stand"}),
        "At the center of the chamber is a round counter made of green "+
	"marble, behind which the shopkeeper stores her picnic supplies "+
	"for sale. A small is sign propped on the counter.\n");
    add_item(({"urn", "urns","flower-filled urns","heavy urns", "clay urns" }),
        "Heavy, clay urns cover the floor from the walls up to the dusty "+
	"paths leading from tunnel to tunnel. The urns are filled with "+
	"water and brimming with colorful flowers, posies and bouquets for "+
	"sale.\n");

    /* special listing add_items */
    add_item(({"posies", "posy urns", "colorful posies"}), "@@view_posies");
    add_item(({"bouquets", "bouquet urns", "fresh bouquets"}),
	"@@view_bouquets");
    add_item(({"flowers", "singles", "single urns", "flower urns",
	"fresh flowers"}), "@@view_flowers");

    set_tell_time(800);

    add_tell(({"A slender young female human arrives from the north "+
        "and drops off a tray of fresh tomato and cheese sandwiches.\n",
        "The jeweled walls glitter and sparkle in the light.\n"}));

    fix_keeper();
    config_shop();

    room_add_object("/d/Avenir/common/obj/trash_can");
}

public int
garden_exit(void)
{
    write("You pass through the short corridor to the southwest. Flowered "+
        "vines brush against you as they part of their own volition, "+
        "revealing the terraced garden of the Ziggurat.\n");

    return 0;
}

/* Functions for listing what is for sale in each basket. */

public string
view_bouquets(void)
{
    write("Large bouquets made of a variety of flowers from the Ziggurat "+
	"gardens are set into urns ready to be sold.\n\n");
    say(QCTNAME(TP) + " examines the fresh bouquets for sale.\n");
    do_list("bouquets");
    return "";
}

public string
view_posies(void)
{
    write("Small posies made of a variety of flowers from the Ziggurat "+
	"gardens are set into urns ready to be sold.\n\n");
    say(QCTNAME(TP) + " examines the colorful posies for sale.\n");
    do_list("posies");
    return "";
}

public string
view_flowers(void)
{
    write("Fresh flowers of all kinds have been plucked from the Ziggurat "+
	"gardens are set into urns ready to be sold.\n\n");
    say(QCTNAME(TP) + " examines the fresh flowers for sale.\n");
    do_list("flowers");
    return "";
}

/*
* Function name: do_sell
* Description:   Try to let the player sell the_item
* Returns:       1 on sucess, 0 fail; should always fail.
* Arguments:     str - string holding name of item, hopefully
*/
public int
do_sell(string str)
{
    if (keeper_speak("I only sell things, not buy them."))
    return 1;

    notify_fail("This shop only sells items, it doesn't buy them.\n");
    return 0;
}

/*
* Function name: do_buy
* Description:   Try to let the player buy the_item if not an infidel.
* Returns:       1 on sucess, 0 fail.
* Arguments:     str - string holding name of item, hopefully
*/
public int
do_buy(string str)
{
    if (!check_keeper())
    return 0;

    if (IS_INFIDEL(this_player()))
    {
	if (keeper_speak("I don't do business with criminals."))
	    return 1;

	notify_fail("This shop does not conduct business with criminals.\n");
	return 0;
    }

    return ::do_buy(str);
}

/* Functions for reading and examining the shop sign. */
string
read_me()
{
    write("              Welcome to the Public Gardens\n"+
          "            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"+
          "  Posies and Bouquets have been arranged for your \n"+
          "  convenience or you may purchase flowers individually.\n"+
          "  Try <help flowers> after you make your purchase for \n"+
          "  for more information.\n"+
          "\n"+
          "  Picnic baskets are also available for pleasure. \n"+
          "  Each basket contains a blanket and snacks for you to \n"+
          "  taste, nibble, bite, and savour.\n"+
          "\n"+
          "  We hope you'll enjoy your visit to our Idrys-blessed Garden.\n");

    return "";
}

public int
do_read(string str)
{
    if (str != "sign")
    {
	notify_fail("Read what?\n");
	return 0;
    }

    read_me();
    return 1;
}

/*
* Function name: do_get
* Description:   If the player attempts to get certain items in the room
*                gives a unique message about why they can't get them.
* Returns:       1 on sucess, 0 fail; should always fail.
* Arguments:     str - string anything the player tries to get or take.
*/
int
do_get(string str)
{
    string a, b;

    parse_command(str, ({}), "%s 'from' [the] %s", a, b);

    if (item_id(b) && ( b == "urn" || b == "urns"))
    {
        write(keeper->query_The_name(TP) +" stops you as you reach "+
            "toward the clay urn.\n");

        say(QCTNAME(TP) +" reaches toward one of the urns, but "+
            keeper->query_the_name(TP) +" stops "+ HIM(TP) +".\n");

        keeper->command("say to "+ OB_NAME(TP) +" Su must purchase the "+
            "flowers before you take them.");

        return 1;
    }

    if (item_id(b) && (b == "wall" || b == "carved wall" || b == "stone wall"))
    {

        write("You try to pull the "+ a +" from the carved wall, but it "+
	    "is firmly fixed.\n");

        say(QCTNAME(TP) +" tries to pull the "+ a +" from the carved "+
            "wall but seems unable to free it from the stone.\n");

        return 1;
    }
    else return 0;
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
*/
public void
init(void)
{
    ::init();

    add_action(  do_get, "get"  );
    add_action(  do_get, "take" );
    add_action(  do_read, "read" );

    init_shop();
}

/* Shop List customizations. */

public string
category(object ob)
{
    if (ob->id("flower"))
	return "Single";

    if (ob->id("posy"))
	return "Posy";

    if (ob->id("bouquet"))
	return "Bouquet";
}
