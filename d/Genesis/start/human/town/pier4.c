/*
 *  /d/Genesis/start/human/town/pier4.c
 *
 *  Created long ago by Styles at CD.
 *
 *  Modification log:
 *
 *    Mar-2008: Included quest vendor code
 *              Included different defs.h file to allow for the
 *                code necessary for the quest vendor sign. (Gorboth)
 *  Grosso line transferred elsewhere - Tapakah, 05/2009
 *  Now serves the line to Kalaman - Tapakah, 06/2009
 */
#pragma save_binary

#include <stdproperties.h>

// #include "../defs.h"
#include "/d/Sparkle/area/city/defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include <macros.h>

#define  TOWN_DIR   ("/d/Genesis/start/human/town/")
inherit STDPIER;

object ship, sign;
int    alarm;

/* Prototypes */
public void        create_room();
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public string      pre_day();
public void        check_market();


public void
create_room()
{
    set_short("Berth 4 - Kalaman");
    set_long("\n"+
		"This is the west pier of Sparkle harbour.\n" +
		"Looking out over the Pensea you see the waves break in the wind.\n"+
		"You would need a ship to cross. West of here is the market square\n"+
		"and the smell of fresh fish tickles your nose.\n"+
		"There is a sign here that reads: Berth 4 - Kalaman.\n");

    add_item(({"waves" }),
	  "Rather wild and not ideal to swim in.\n");
    add_item( ({ "daughter", "daughters" }), 
		"You degenerate, why would you possibly want to do that?\n");
    add_item( ({ "harbor", "harbour" }), 
		"The harbour is the prime source of income for a village like\n"+
        "Sparkle. Here, traders and merchant ships come in to sell their\n"+
        "cargos and draft new crews. The sailors spend their gold in the\n"+
        "pub and shop while the village people hide their daughters.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");


    add_exit(TOWN_DIR + "pier3","north");
    add_exit("/d/Sparkle/area/city/rooms/streets/market_square", "west");
    add_exit(TOWN_DIR + "pier5","south");
    add_pier_entry(MASTER_OB(TO), "Sparkle", "Pier to Kalaman");
    initialize_pier();

}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * I am redefining this function to allow for an advertisement for
 * the Market to appear each Tuesday and then be removed at the end of
 * the day.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(VENDORSIGN))
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
 * I am redefining this function to allow for an advertisement for
 * the Market to appear each Tuesday and then be removed at the end of
 * the day.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!ob->id(VENDORSIGN))
    {
        check_market();
    }
} /* leave_inv */


/*
 * Function name:        pre_day
 * Description  :        figure out what the day should be before
 *                       the market is due to open
 */
public string
pre_day()
{
    string *days = ({ "Sunday",
                      "Monday",
                      "Tuesday",
                      "Wednesday",
                      "Thursday",
                      "Friday",
                      "Saturday",
                   }),
            preday = "ERROR";
    int     day_point = member_array(MARKETDAY, days);

    switch(day_point)
    {
        case 0:
            preday = days[6];
            break;
        case 1..6:
            preday = days[day_point - 1];
            break;
        default:
            break;
    }

    return preday[0..2];
} /* pre_day */


/*
 * Function name:        check_market
 * Description  :        See if it is the correct day before the Market
 *                       to comes to town. It happens only on the
 *                       day defined by MARKETDAY in the defs.h file.
 */
public void
check_market()
{
    object  market;   

    if (!objectp(market = present(VENDORSIGN, this_object())))
    {
        if (ctime(time())[0..2] == pre_day())
        {
            room_add_object(OBJ_DIR + "vendorsign");
            tell_room(this_object(),
                "A travel-worn man in a dusty robe arrives and hangs"
              + " a poster here along the docks. He then moves away out"
              + " of sight.\n");         
        }
        alarm = 0;
    }
    else
    {
        if ((ctime(time())[0..2] != pre_day()) && (!alarm))
        {
            alarm = set_alarm(1.0, 0.0, &market->goodbye());
        }
    }
} /* check_market */
