/*
 *  /d/Sparkle/area/city/rooms/streets/market_square.c
 *
 *  This is Market Square in Sparkle. Here, every Wednesday, the
 *  Travelling Merchants come to town. North is the donations office,
 *  and south is the General Store.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";

#include <macros.h>
#include <ss_types.h>

/* Prototpyes */
public void        create_sparkle();
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public void        check_market();
public void        init();
public int         do_drink(string arg);
public int         climb_down(string arg);
public string      exa_well();
public string      exa_sign(string arg);

int                alarm;

/* Definitions */
#define BELLSOUND    "     "
#define TELL_STY(x)  find_living("styles")->catch_tell( \
                         ctime(time()) + BELLSOUND + x + "\n")

/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("center");
    set_street("Market Square");
    set_square(1);

    set_short_extra("The donations office is to the north. South is a"
      + " general store");
    set_long_extra("Situated just west of the docks, Market Square is"
      + " the perfect place in town for various merchants to gather"
      + " to offer their wares to townsfolk and visitors alike. Drawing"
      + " on this theme, the General Store of Sparkle is located just"
      + " south of the square, a brightly painted sign hanging from"
      + " its entrance. North of the square, a short walk leads to"
      + " a small office where a small metal sign hangs from a"
      + " signpost.");

    try_item( ({ "dock", "docks", "harbor", "harbour" }),
        "The docks are just to the east. You can barely glimpse them"
      + " from here.\n");
    try_item( ({ "merchant", "merchants", "various merchants" }),
        "It is said that " + MARKETDAY + " is the best time to find"
      + " merchants here in the square.\n");
    try_item( ({ "townsfolk" }),
        "Folk ... from the town.\n");
    try_item( ({ "visitor", "visitors" }),
        "I suppose you yourself are one.\n");
    try_item( ({ "store", "general store", "shop",
                 "general store of sparkle", "south", "southern building",
                 "building to the south" }),
        "The General Store is one of the most frequently visited"
      + " establishments in Sparkle. They say location is everything,"
      + " in which case it being placed right between the docks and"
      + " the church must make all the difference in the world. Whatever"
      + " the reason, business is always good.\n");
    try_item( ({ "establishment", "establishments" }),
        "There are many of them, but most those in this central part"
      + " of town are to the west.\n");
    try_item( ({ "square", "market square" }),
        "The square spreads out around the old well, providing ample"
      + " space for merchants or any others to set up their wares for"
      + " perusal.\n");
    try_item( ({ "entrance", "entrance to the store", "store entrance" }),
        "Customers frequently move in and out of the entrance, passing"
      + " beneath the brightly painted sign.\n");
    try_item( ({ "customer", "customers" }),
        "Most look satisfied. Maybe you should enter and see for yourself"
      + " if there is good trade to be had?\n");
    try_item( ({ "walk", "short walk", "paved path", "paved pathway" }),
        "A paved pathway runs north toward the office, passing a signpost"
      + " from which a small metal sign is displayed.\n");
    try_item( ({ "well", "fresh water well", "old well",
                 "fresh-water well" }),
        "The well seems old and well used. Nevertheless "+
        "it is kept in good working order. Peering down into the "+
        "darkness of the well, you see a reflection in the water "+
        "surface far down below.@@exa_well@@\n");
    add_item( ({ "reflection", "surface", "water", "darkness",
                 "darkness of the well", "reflection in the water",
                 "water surface" }),
        "The reflection in the water surface is at least ten meters "+
        "down. Free falling is not advised but you might be able to "+
        "climb down if you are skilled and brave enough ...\n");

    try_item( ({ "sign", "signs" }),
        "Examine which sign? The small metal sign and the"
      + " brightly painted sign are both nearby.\n");
    try_item( ({ "small sign", "metal sign", "small metal sign",
                 "north sign", "north sign",
                 "northern sign", "sign to the north",
                 "signpost", "post", "sign post",
                 "donation sign", "donations sign",
                 "donation office sign", "donations office sign" }),
        "@@exa_sign|sign_donations@@");
    try_item( ({ "painted sign", "brightly painted sign",
                 "south sign", "southern sign", "sign to the south",
                 "store sign", "general store sign" }),
                 "@@exa_sign|sign_general_store@@");
    add_cmd_item( ({ "sign", "signs" }),
                  ({ "read" }),
        "Read which sign? The small metal sign and the"
      + " brightly painted sign are both nearby.\n");
    add_cmd_item( ({ "small sign", "the small sign",
                     "metal sign", "the metal sign",
                     "small metal sign", "the small metal sign",
                     "north sign", "northern sign", "sign to the north",
                     "the north sign", "the northern sign",
                     "the sign to the north",
                     "signpost", "the signpost",
                     "post", "the post",
                     "sign post", "the sign post",
                     "donation sign", "the donation sign",
                     "donations sign", "the donations sign",
                     "donation office sign", "the donation office sign",
                     "donations office sign", "the donations office sign" }),
                  ({ "read" }),
        "@@exa_sign|sign_donations@@");
    add_cmd_item( ({ "painted sign", "the painted sign",
                     "brightly painted sign", "the brightly painted sign",
                     "south sign", "the south sign",
                     "southern sign", "the southern sign",
                     "sign to the south", "the sign to the south",
                     "store sign", "the store sign",
                     "general store sign", "the general store sign" }),
                  ({ "read" }),
        "@@exa_sign|sign_general_store@@");

    add_center_items();

    add_tell("A salty sea breeze blows in from the east.\n");
    add_tell("A cart laden with many weapons and armours stops in front"
      + " of the building to the south. A number of men help unload the"
      + " cart, and the goods are taken inside. The driver is paid, and"
      + " the now empty cart drives out of sight down the road.\n");
    add_tell("A colorful bird flies overhead towards the docks.\n");
    add_tell("The sails of a tall ship are briefly visible to the east"
      + " passing between two nearby rooftops.\n");

    add_exit("center_g", "west");
    add_exit("/d/Genesis/obj/donation/office", "north");
//  add_exit("market_square2", "east");
    add_exit("/d/Genesis/start/human/town/pier4", "east");
    add_exit("/d/Genesis/start/human/town/shop", "south");

    room_add_object("/d/Genesis/obj/donation/column", 1);
    room_add_object("/d/Sparkle/area/city/auction/obj/tent", 1);
} /* create_sparkle */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * I am redefining this function to allow for the market to show up
 * at the beginning of each Wednesday and leave when that Wednesday
 * is over.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(VENDORNAME))
    {
        check_market();
    }
} /* enter_inv */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * I am redefining this function to allow for the market to show up
 * at the beginning of each Wednesday and leave when that Wednesday
 * is over.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!ob->id(VENDORNAME))
    {
        check_market();
    }
} /* leave_inv */


/*
 * Function name:        check_market
 * Description  :        See if it is the correct day for the Market
 *                       to come to town. It happens only on the
 *                       day defined by MARKETDAY in the defs.h file.
 */
public void
check_market()
{
    object  market;

    if (!objectp(market = present(VENDORNAME, this_object())))
    {
        if (ctime(time())[0..2] == MARKETDAY[0..2])
        {
            room_add_object(OBJ_DIR + "questvendor");
            tell_room(this_object(),
                "A cart laden with many supplies rolls suddenly into"
              + " the square followed by another, and another. Vendors"
              + " soon crowd the street on all corners, setting up"
              + " tables and displaying their wares. One erects a"
              + " large kiosk and loudly proclaims, \"The "
              + MARKETDAY + " Market is now open for business! May"
              + " it be a profitable day for all!\"\n");
        }
        alarm = 0;
    }
    else
    {
        if ((ctime(time())[0..2] != MARKETDAY[0..2]) && (!alarm))
        {
            alarm = set_alarm(1.0, 0.0, &market->goodbye());
        }
    }
} /* check_market */


/*
 * Function name:       init
 * Description  :       set up some actions for the player
 */
public void
init()
{
    ::init();

    add_action(climb_down, "climb");
    add_action(do_drink, "drink");
} /* init */


/*
 * Function name:       climb_down
 * Description  :       Let players climb down the well
 * Arguments    :
 * Returns      :       1 or 0. Success or failure.
 */
public int
climb_down(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [in] [into] [to] [the] [fresh] [water] 'well'"))
    {
        notify_fail("You don't seem to be able to " + query_verb()
          + " there.\n");
        return 0;
    }

    if (this_player()->query_skill(SS_CLIMB) > random(30))
    {
        write("You climb down into the well.\n");
        say(QCTNAME(this_player()) + " climbs down into the well.\n");

        this_player()->move_living("M", "/d/Genesis/start/human/town/well");

        //TELL_STY(this_player()->query_real_name()
        //  + " climbed down the well.\n");
    }
    else
    {
        write("You carefully lower yourself into the well, and try to"
          + " get a grip on ... OOPS! You slip and fall!\n");
        say(QCTNAME(this_player()) + " falls down into the well!\n");

        this_player()->move_living("M", "/d/Genesis/start/human/town/well");

        this_player()->heal_hp(-100);

        /* I refuse to have a death trap here in Sparkle. We'll hurt
         * but not kill. (Gorboth)
         */
        write("Ouch! That really hurt.\n");

        //TELL_STY(this_player()->query_real_name()
        //  + " (HPB:" + this_player()->query_hp()
        //  + ")fell down the well.\n");
    }

    return 1;
} /* climb_down */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the fountain
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'well'"
      + " [from] [the] [well]"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("You raise the bucket from the well, and take a drink"
          + " from the water. It tastes excellent! You seem to have"
          + " drunk your fill.\n");
    }
    else
    {
        write("You raise the bucket from the well, and take a drink"
          + " from the water. It tastes excellent! You feel"
          + " refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " well.\n");

    return 1;
} /* do_drink */


/*
 * Function name:        exa_well
 * Description  :        Uh .... I guess this is for Styles. ;-)
 * Returns      :        null string
 */
public string
exa_well()
{
    //TELL_STY(this_player()->query_real_name() + " examined the well.\n");

    return"";
} /* exa_well */


/*
 * Function name:        exa_sign
 * Description  :        provide a description of the sign that is
 *                       hanging here
 * Arguments    :        string arg - which sign do we want?
 * Returns      :        string - the text to display
 */
public string
exa_sign(string arg)
{
    string  sign = ((arg == "sign_donations")
                 ? "donations office" : "general store");

    /* A check for the sign rating quest */
    check_rating_form(this_player(), sign);

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + arg);
} /* exa_sign */
