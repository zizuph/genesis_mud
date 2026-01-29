/* 
 *  /d/Sparkle/area/city/rooms/inside/inn.c
 *
 *  This is the Silver Swan Inn in the Arts Quarter of Telberin.
 *  Here, travellers may rest a while, and create a temporary
 *  startlocation in Emerald. This file was copied from the
 *  Sleeping Stallion inn from Gondor created most likely by
 *  Elessar and Olorin, and modified by Gnadnar.
 *
 *  UPDATE: This Inn has been closed in Telberin and moved to the City
 *          of Sparkle. It will now serve the hub. (Gorboth - Apr. 2011)
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 *
 *  Modification log:
 *    Nov. 2012 - opened the Chef Herbs weekly quest. (Gorboth)
 */
#pragma strict_types

#include "../../defs.h"

inherit SPARKLE_ROOM_BASE;
inherit "/d/Emerald/lib/inn";


#include <macros.h>
#include <money.h>
#include <stdproperties.h>

/* Definitions */
#define	STAND_DIR       "/d/Emerald/telberin/obj/"
#define	MY_PRICES       ({ 9, 15, 40, 100, 10, 24, 50, 240, 550, 144})
#define	NUM             sizeof(MONEY_TYPES)
#define	HOTEL_KEY       ("/d/Emerald/telberin/obj/hotel_key")

/* Global Variables */
int                Alarm;
public object      TB_Innkeep;

/* Prototypes */
public void        create_sparkle();
public void        reset_room();
public void        init();
static string      price_long();
public int         do_read(string arg);
public void        buy_item(string item, int number, string desc);
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public void        check_chef();



/*
 * Function name:       create_telberin_building
 * Description  :       create the room
 */
public void
create_sparkle()
{
    set_short("The Silver Swan Inn");
    set_long("This is the Silver Swan Inn, the finest lodging"
      + " that is offered within the city. Here, in the main"
      + " room, a large vaulted ceiling rises above polished white"
      + " tiles in the floor, upon which are many tables and"
      + " chairs. Beside a staircase, a counter with a menu listing"
      + " the prices at the inn are at the end of the hall.\n\n");

    add_item( ({ "silver swan", "inn", "silver swan inn",
                 "here", "area", "room", "hall", "main room" }), long);
    add_item( ({"table","tables"}),
        "The tables are oval in shape, and white. They show"
      + " signs of long use, but are polished and clean.\n");
    add_item( ({"chair", "chairs"}),
        "The chairs are elegant, with high backs and curved"
      + " legs.\n");
    add_item( ({ "high back", "high backs", "back", "backs" }),
        "The backs of the chairs, much like the general atmosphere"
      + " here in the inn, display a refined elegance.\n");
    add_item( ({ "atmosphere", "general atmosphere", "elegance",
                 "refined elegance", "lines", "elegant lines" }),
        "The craftsmanship and stylings within the inn are unmistakably"
      + " elvish.\n");
    add_item( ({ "craftsmanship", "elvish craftsmanship",
                 "styling", "stylings" }),
        "Fancy!\n");
    add_item( ({ "counter", "wooden counter", "bar", "light wood",
                 "wood" }), 
        "The counter is long and slightly curved. It is made of" 
      + " some sort of light wood, which has been finely polished."
      + " A menu listing the services provided hangs on the wall"
      + " above.\n");
    add_item( ({ "tile", "tiles", "white tile", "white tiles",
                 "polished white tile", "polished white tiles",
                 "polished tile", "polished tiles", "floor",
                 "ground" }),
        "The tiles on this floor are clean and seem to have been"
      + " swept recently. A few marks are visible where people"
      + " have slid chairs and tables along the surface.\n");
    add_item( ({ "plaster wall", "plaster walls", "plaster", 
                 "wall", "walls" }),
        "The smooth plaster walls gleam with light.\n");
    add_item( ({ "light" }),
        "No light source is visible here, though the room is"
      + " positively luminous.\n");
    add_item( ({ "ceiling", "vaulted ceiling" }),
        "The ceiling rises high above the floor, its vaulted"
      + " frame drawing the eye up along its elegant lines.\n");
    add_item( ({ "upper floor", "stair", "stairs", "stairway",
                 "upper level", "upstairs", "staircase" }),
        "Curved polished stairs lead to an upper floor.\n");
    add_item( ({ "leg", "legs", "curved leg", "curved legs",
                 "chair leg", "chair legs",
                 "leg of the chair", "legs of the chairs" }),
        "There is an elegance to the style of these chairs, to be"
      + " sure.\n");

    add_item(({"pricelist","list","prices","menu","bill","bill of fare"}),
        price_long());

    add_exit("hotel_room", "up");
    add_exit(STREET_DIR + "center_a", "south");

    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");

    config_default_trade();
    set_money_give_max(2000);
    set_money_give_out( ({ 2000, 700, 50, 4}) );
    set_money_give_reduce( ({ 1, 1, 1, 1 }) ); 

    reset_room();
} /* create_sparkle */

/*
 * Function name:       reset_room
 * Description  :       restore npcs as needed
 */
public void
reset_room()
{
    if (!objectp(present(TB_Innkeep, this_object())))
    {
        TB_Innkeep = clone_object("/d/Emerald/telberin/arts/npc/innkeeper");
        TB_Innkeep->arm_me();
        TB_Innkeep->move(this_object());

        set_innkeeper_npc(TB_Innkeep);
    }
} /* reset_room */


/*
 * Function name:       init
 * Description  :       add player verbs
 */
public void
init()
{
    ::init();
    ::init_inn();
    add_action(do_read, "read");
} /* init */


/*
 * Function name:       price_long
 * Description  :       describe the bill of fare
 * Returns      :       string -- the description
 */
static string
price_long() 
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Spring Water          ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Stout Porter          ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Southland Wine        ...  " + money_text(MY_PRICES[2]) + "\n"
    + "   Rimmon Cognac         ...  " + money_text(MY_PRICES[3]) + "\n\n"
    + "HOT MEALS:\n"
    + "   Creamed Oats          ...  " + money_text(MY_PRICES[4]) + "\n"
    + "   Onion Soup            ...  " + money_text(MY_PRICES[5]) + "\n"
    + "   Baked Sweetroot       ...  " + money_text(MY_PRICES[6]) + "\n"
    + "   Roasted Duck          ...  " + money_text(MY_PRICES[7]) + "\n"
    + "   Filet of Venison      ...  " + money_text(MY_PRICES[8]) + "\n\n"
    + "ROOMS:\n"
    + "   Key for a room        ...  " + money_text(MY_PRICES[9]) + "\n\n");
} /* price_long */


/*
 * Function name:       do_read
 * Description  :       handle attempts to read bill of fare
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_read(string arg) 
{
    if (!strlen(arg))
        return 0;
    if (arg == "bill of fare" || arg == "pricelist" ||
    arg == "list" || arg == "prices" || arg == "menu")
    {
        write(price_long());
        return 1;
    }
    return 0;
} /* do_read */


/*
 * Function name: buy_it
 * Description:   identify the item the player tries to buy
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string      file,
                ware;
    int         price;


    switch (item_name)
    {
    case "water":
    case "spring water":
            file = STAND_DIR + "water";
            ware = "spring water";
            price = MY_PRICES[0];
        break;
    case "porter":
    case "stout porter":
            file = STAND_DIR + "porter";
            ware = "stout porter";
            price = MY_PRICES[1];
        break;
    case "wine":
    case "southland wine":
            file = STAND_DIR + "wine";
            ware = "southland wine";
            price = MY_PRICES[2];
        break;
    case "cognac":
    case "rimmon cognac":
            file = STAND_DIR + "cognac";
            ware = "rimmon cognac";
            price = MY_PRICES[3];
        break;
    case "oats":
    case "creamed oats":
            file = STAND_DIR + "oats";
            ware = "creamed oats";
            price = MY_PRICES[4];
        break;
    case "soup":
    case "onion soup":
            file = STAND_DIR + "soup";
            ware = "onion soup";
            price = MY_PRICES[5];
        break;
    case "sweetroot":
    case "baked sweetroot":
            file = STAND_DIR + "sweetroot";
            ware = "baked sweetroot";
            price = MY_PRICES[6];
        break;
    case "duck":
    case "roasted duck":
            file = STAND_DIR + "duck";
            ware = "roasted duck";
            price = MY_PRICES[7];
        break;
    case "venison":
    case "filet":
    case "filet of venison":
    case "venison filet":
            file = STAND_DIR + "venison";
            ware = "filet of venison";
            price = MY_PRICES[8];
        break;
    case "room":
    case "key":
    case "key for a room":
    case "single room":
    case "night":
            if (number > 1 )
            {
                write(TB_Innkeep->query_The_name(this_player())+" stares at you.\n"+
                    TB_Innkeep->query_The_name(this_player())+
                    " says: I only rent one room per person.\n");
                return 1;
            }
            file = HOTEL_KEY;
            ware = "single room to spend the night in Sparkle";
            price = MY_PRICES[9];
        break;
    default:
        notify_fail(TB_Innkeep->query_The_name(this_player())+
            " says: We don't have that on the menu.\n");
        return 0;
        break;
    }
    if (can_afford(price, number, ware, pay_type, get_type))
        buy_item(file, number, ware);
    return 1;
} /* buy_it */


/*
 * Function name: buy_item
 * Description:   clone and move the bought item
 *                mask parent to handle room keys.
 * Arguments:     item   - filename of item to clone
 *                number - heap size of item
 *                desc   - description for item
 */
void
buy_item(string item, int number = 1, string desc = 0)
{

    object      ob,
                tp = this_player();

    if (item == HOTEL_KEY)
    {
        say(QCTNAME(this_player()) + " orders a room for the night.\n");
        ob = clone_object(item);
        if (!ob->move(tp))
        {
            write(TB_Innkeep->query_The_name(tp)
                + " gives you the key to the room. Don't lose it!\n");
            say(QCTNAME(TB_Innkeep) + " gives a key to "+QTNAME(tp)+".\n");
        }
        else
        {
            write("Since you cannot carry the key, "
             + TB_Innkeep->query_the_name(tp) + " puts it down on a"
             + " table.\n");
            if (ob->move(this_object()))
                ob->move(this_object(), 1);
        }
        return;
    }
    ::buy_item(item, number, desc);
} /* but_item */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * I am redefining this function to allow for the chef to show up
 * at the beginning of each Saturday and leave when that Saturday
 * is over.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(H_VENDORNAME))
    {
        check_chef();
    }
} /* enter_inv */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * I am redefining this function to allow for the chef to show up
 * at the beginning of each Saturday and leave when that Saturday
 * is over.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!ob->id(H_VENDORNAME))
    {
        check_chef();
    }
} /* leave_inv */


/*
 * Function name:        check_chef
 * Description  :        See if it is the correct day for the Market
 *                       to come to town. It happens only on the
 *                       day defined by HERBDAY in the defs.h file.
 */
public void
check_chef()
{
    object  chef;

    if (!objectp(chef = present(H_VENDORNAME, this_object())))
    {
        if (ctime(time())[0..2] == HERBDAY[0..2])
        {
            room_add_object(OBJ_DIR + "herbvendor");
            tell_room(this_object(),
                "A skilled-looking chef suddenly appears from the"
              + " kitchen, wheeling a rolling station into the main"
              + " room of the inn. He gets his things set up, sits"
              + " down behind the station, and then proclaims, \"It is "
              + HERBDAY + "! The weekly special is now served!\"\n");
        }
        Alarm = 0;
    }
    else
    {
        if ((ctime(time())[0..2] != HERBDAY[0..2]) && (!Alarm))
        {
            Alarm = set_alarm(1.0, 0.0, &chef->goodbye());
        }
    }
} /* check_chef */