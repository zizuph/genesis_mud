/*
 *  /d/Sparkle/area/city/rooms/outdoor_room.c
 *
 *  This will be the main outdoor master file for rooms in the city of
 *  Sparkle.
 *
 *  Created January 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Sparkle/sys/defs.h"
#include "/d/Sparkle/area/city/sys/broadcast_msgs.h"

inherit S_BASE_ROOM;
inherit LIB_DIR + "map_module";
inherit BC_MODULE;

#include <stdproperties.h>



/* Global Variables */
public string      City_Quadrant = "nigh";
                                /* what area of the city are we in,
                                 * direction-wise, relating to the
                                 * first church of Sparkle?
                                 */
public string      City_Street   = "a well-built road";
                                /* What is the street name here?         */
public mixed       Short_Extra; /* room-specific text for the short desc */
public mixed       Long_Extra;  /* room-specific text for the long desc  */
public int         Rooftop = 0; /* Is the player on a rooftop?           */
public int         Show_Weather = 1; /* Shall we show the weather here?  */
public int         Square = 0;  /* Are we in a city square?              */


/* Prototypes */
nomask void        create_room();
public void        create_sparkle();
public string      sparkle_short();
public string      sparkle_long();
public int         try_item(mixed names, mixed desc);
public void        add_outdoor_items();
public void        init();

public void        set_quadrant(string s)      { City_Quadrant = s; }
public void        set_street(string s)          { City_Street = s; }
public void        set_short_extra(string s)     { Short_Extra = s; }
public void        set_long_extra(string s)       { Long_Extra = s; }
public void        set_rooftop(int i)                { Rooftop = i; }
public void        set_weather(int i)           { Show_Weather = i; }
public void        set_square(int i)                  { Square = i; }
public string      query_quadrant()         { return City_Quadrant; }


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
nomask void
create_room()
{
    string *bc_rooms;

    create_sparkle();

    bc_rooms = query_broadcast(this_object());

    if (sizeof(bc_rooms))
    {
        set_bc_rooms(bc_rooms);
    }

    set_short(sparkle_short);
    set_long(sparkle_long);
    set_text_map_file(TEXT_DIR + "sparkle_main.txt");
} /* create_room */


/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_sparkle()
{
} /* create_sparkle */


/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for street locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    string  locstr = "",
            dir = "on",
            shortstr = "";

    if (Rooftop)
    {
        locstr = "On a rooftop ";
        dir = "overlooking";
    }
    else if(Square)
    {
        dir = "in";
    }

    shortstr = locstr + dir + " " + City_Street;

    switch (City_Quadrant)
    {
        case "center":
            locstr += "among the ancient structures of the Old City"
                   + " " + dir + " " + City_Street + " in the center"
                   + " of Sparkle";
            break;
        case "north":
            locstr += dir + " " + City_Street + " in the main residential"
                   + " district of Sparkle, north of the Old City";
            break;
        case "northeast":
            locstr += dir + " " + City_Street + " northeast of the Old"
                   + " City in Sparkle, nearing the eastern sea";
            break;
        case "east":
            locstr += dir + " " + City_Street + " just east of the Old"
                   + " City proper in Sparkle";
            break;
        case "southeast":
            locstr += dir + " " + City_Street + " in Sparkle, southwest of"
                   + " the Old City";
            break;
        case "south":
            locstr += "just south of the Old City wall " + dir
                   + " " + City_Street + " in Sparkle";
            break;
        case "southwest":
            locstr += "near the affluent estates of Shimmering Lake " + dir
                   + " " + City_Street + " southwest of the Old City in"
                   + " Sparkle";
            break;
        case "west":
            locstr += dir + " " + City_Street + " just west of the Old City"
                   + " walls in Sparkle";
            break;
        case "northwest":
            locstr += "in a somewhat rural area of Sparkle northwest of"
                   + " the Old City " + dir + " " + City_Street;
            break;
        default:
            locstr += dir + " " + City_Street + " in the city of Sparkle";
            break;
    }

    if (Short_Extra && calling_function() != "sparkle_long")
    {
        shortstr += ". " + this_object()->check_call(Short_Extra);
        return shortstr;
    }

    if (calling_function() == "sparkle_long")
    {
        return locstr;
    }

    return shortstr;
} /* sparkle_short */


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for street locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    string  long_desc,
            weather;

    long_desc = capitalize(sparkle_short()) + ".";


    if (!this_object()->query_prop(ROOM_I_INSIDE))
    {
        switch (ctime(time())[0..2])
        {
            case "Sun":
                weather = " The sun beams down on this crisp cool day,"
                        + " its warm light brightening";
                break;
            case "Mon":
                weather = " Dull heavy rainclouds have moved in over"
                        + " the city, sending occasional showers down"
                        + " to drench";
                break;
            case "Tue":
                weather = " High windswept clouds hover over the city"
                        + " where gusts of occasional strong breeze"
                        + " are blowing through today to tug at";
                break;
            case "Wed":
                weather = " Pallid grey skies hang evenly above the"
                        + " city today, sending neither raindrop nor"
                        + " ray of sun down upon";
                break;
            case "Thu":
                weather = " Scattered clouds cover the sky from horizon"
                        + " to horizon, their various forms parting now"
                        + " and again to allow the occasional sunbreak"
                        + " to beam down on";
                break;
            case "Fri":
                weather = " A brilliant sun blazes in the vivid blue"
                        + " sky, its bright rays pouring down to warm";
                break;
            case "Sat":
                weather = " The sun rides lazily above in the sky, its"
                        + " warm rays brightening every corner of";
                break;
            default:
                weather = " A strange breeze blows in from the sea,"
                        + " stirring";
                break;
        }

        switch(City_Quadrant)
        {
            case "center":
               weather+= " the old stone buildings.";
                break;
            case "north":
               weather+= " the many local rooftops.";
                break;
            case "northeast":
               weather+= " the beaches to the northeast.";
                break;
            case "east":
               weather+= " the surrounding docks.";
                break;
            case "southeast":
               weather+= " the beaches to the southeast.";
                break;
            case "south":
               weather+= " these southern roadways.";
                break;
            case "southwest":
               weather+= " these luxureous environs.";
                break;
            case "west":
               weather+= " these well-travelled byways.";
                break;
            case "northwest":
               weather+= " the rugged local establishments.";
                break;
            default:
               weather+= " the local terrain.";
        }
    }

    if (this_player()->query_prop(LIVE_O_LAST_ROOM)->
        query_prop(ROOM_I_INSIDE))
    {
        long_desc += weather;
    }

    if (Long_Extra)
    {
        long_desc += " " + this_object()->check_call(Long_Extra);
    }
 
    if (calling_function() == "check_weather")
    {
        return weather;
    }
    else
    {
        return long_desc + "\n\n";
    }
} /* sparkle_long */


/*
 * Function name:        check_weather
 * Description  :        get the weather report from the sparkle_long
 *                       function
 * Returns      :        string - the weather description
 */
public string
check_weather()
{
    return sparkle_long();
} /* check_weather */


/*
 * Function name:        try_item
 * Description  :        checks to see if an item already exists
 *                       within a given object, and if it does not, it 
 *                       then adds it as add_item() would.
 * Arguments    :        mixed names --  string or array of strings, the
 *                                       item name(s).
 *                       mixed desc -- string or function, the description.
 * Returns      :        int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        for (i = 0; i < sizeof(names); i++) 
        {
            if (item_id(names[i])) 
            {
                exists += ({ names[i] });
            }
        }
        names -= exists;
        if ((i = sizeof(names)))
        {
            add_item(names, desc);
        }
    } 
    else if (!this_object()->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   /* # of items added */
} /* try_item */


/*
 * Function name:        add_outdoor_items
 * Description  :        add_items that describe things present in
 *                       just about any outdoor room in Sparkle
 */
public void
add_outdoor_items()
{
    try_item( ({ "sky", "up", "blue sky" }), one_of_list(
              ({ "Scattered white clouds drift slowly through the bright"
               + " blue sky overhead.\n",
                 "The sky is bright and blue above.\n",
                 "The sun shines brightly down from the blue sky"
               + "overhead.\n",
              }) ) );
    try_item( ({ "cloud", "clouds", "scattered clouds",
                 "puff", "puffs", "puffs of cloud", "scattered clouds",
                 "scattered white clouds", "drifting cloud",
                 "drifting clouds",
                 "white cloud", "white clouds" }), one_of_list(
              ({ "Clouds drift silently by overhead, occasionally passing"
               + " before the sun to cast a temporary shade on the area.\n",
                 "The clouds drift past as white puffs in an otherwise"
               + " vibrant blue canopy.\n",
                 "Glancing up, you study a passing cloud. It looks a bit"
               + " like a large " + one_of_list( ({ "goat", "pig", "sheep",
                 "whale", "dragon", "ship", "tree", "pumpkin", "canoe",
                 "buffalo", "swan", "duck", "horse", "cow", "fish",
                 "hen", "bird" }) ) + ".\n",
               }) ) );
    try_item( ({ "sun", "sunlight", "rays", "rays of warmth",
                 "light", "illumination" }), one_of_list(
              ({ "Sunlight beams down from above.\n",
                 "Shielding your eyes, you squint up into the brilliant"
               + " sunlight above.\n",
                 "The sun casts warm rays down over the Sparkle area.\n",
              }) ) );
    try_item( ({ "here", "area", "land", "lands", "region", "domain" }),
                 "You pause a moment to gaze at your surroundings.\n");
    try_item( ({ "ground", "down", "floor", "pebble", "pebbles",
                 "dirt", "soil", "earth", "dust" }), one_of_list( ({
        "The ground here is solid beneath your feet.\n",
        "A few pebbles dot the ground, which is otherwise fairly"
      + " plain.\n",
        "You kick a bit at the dirt along the ground, testing the"
      + " earth with your foot.\n" }) ) );
    try_item( ({ "wind", "breeze", "smell", "stench" }), 
        "There is a bit of breeze here in the outdoors.\n");
} /* add_outdoor_items */


/*
 * Function name:        add_road_items
 * Description  :        add_items that describe the road
 */
public void
add_road_items()
{
    try_item( ({ "road", "path", "dirt road", "dirt path", "street",
                 "streets" }),
        one_of_list( ({
        "The road is well-worn, showing numerous ruts and grooves in"
      + " its surface.\n",
        "Dust blows along the road in the occasional breeze.\n",
        "Though the road is rough in places, it looks well used,"
      + " and appears to have been cared for by able hands.\n" }) ) );
    try_item( ({ "rut", "ruts", "groove", "grooves", "depression",
                 "depressions", "surface" }),
        "There are numerous depressions in the road which have been"
      + " caused by rain and the travelling foot and hoof.\n");
} /* add_road_items */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    ::init_map_module();
} /* init */


/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this room. We want
 *                       to allow for broadcasting movement to rooms that
 *                       look onto this location.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob))
    {
        broadcast_movement(ob, 1);
    }
} /* enter_inv */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this room. We want
 *                       to allow for broadcasting movement to rooms that
 *                       look onto this location.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (living(ob))
    {
        broadcast_movement(ob, 0);
    }
} /* leave_inv */


