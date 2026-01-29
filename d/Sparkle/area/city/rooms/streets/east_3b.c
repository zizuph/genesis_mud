/*
 *  /d/Sparkle/area/city/rooms/streets/east_3b.c
 *
 *  These are the city streets of Sparkle. Refer to outdoor_room.c for
 *  functionality.
 *
 *  Created February 2008, by Cooper Sherry (Gorboth)
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 */
#pragma strict_types

#include <time.h>
#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";


/* Prototpyes */
public void        create_sparkle();
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public string      pre_day();
public void        check_market();



/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_quadrant("east");
    set_street(STREET_EAST_3);

    add_exit("east_3c", "north");
    add_exit("east_3a", "south");
    add_exit("lars_square", "west");
} /* create_sparkle */


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
                "A travel-worn man in a dusty robe arrives and places"
              + " a sign here along the docks. He then moves away out"
              + " of sight.\n");
        }
    }
    else
    {
        if (ctime(time())[0..2] != pre_day())
        {
            set_alarm(1.0, 0.0, &market->goodbye());
        }
    }
} /* check_market */