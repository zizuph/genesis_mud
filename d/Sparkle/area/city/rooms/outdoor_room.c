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

inherit ROOMS_DIR + "delay_room";
inherit "/d/Sparkle/lib/room_tell";

#include <stdproperties.h>



/* Global Variables */
public string      City_Quadrant = "nigh";
                                /* what area of the city are we in,
                                 * direction-wise, relating to the
                                 * first church of Sparkle?
                                 */
public string      City_Street   = "a well-built road";
                                /* What is the street name here?         */
public string      Bc_Arrive_Msg = ""; /* Message to display to certain rooms
                                        * connected to this one when an
                                        * interactive enters.            */
public string      Bc_Leave_Msg = "";  /* Same as above, but for leaving.*/
public string      Spied_Msg = ""; /* Location text to display when people
                                    * in this location are seen from afar*/
public string     *Broadcast_Rooms; /* Array of the filenames of rooms 
                                     * that should receive potential   
                                     * messages when people enter or leave
                                     * this room.                        */ 
public string     *Unique_Broadcast; /* Special broadcasts defined by an
                                      * individual room to override the
                                      * defaults.
                                      *    element 0: arrive_msg
                                      *    element 1: leave_msg          */
public mixed       Short_Extra; /* room-specific text for the short desc */
public mixed       Long_Extra;  /* room-specific text for the long desc  */
public int         Rooftop = 0; /* Is the player on a rooftop?           */
public int         Show_Weather = 1; /* Shall we show the weather here?  */
public int         Square = 0;  /* Are we in a city square?              */
public object      Broadcast_Mover; /* Who is doing the moving?          */
public object      Broadcast_Viewer; /* Who is viewing the moving?       */

/* Prototypes */
nomask void        create_room();
public void        create_sparkle();
public string      sparkle_short();
public string      sparkle_long();
public int         try_item(mixed names, mixed desc);
public void        add_outdoor_items();
public void        add_center_items();
public void        add_construction_items();
public void        init();
public void        config_broadcasts(object who, object viewer);
public string      format_broadcast(object mover, object viewer, string bc, string where = "");
public void        check_rating_form(object who, string sign);

public void        set_quadrant(string s)      { City_Quadrant = s; }
public void        set_street(string s)          { City_Street = s; }
public void        set_short_extra(string s)     { Short_Extra = s; }
public void        set_long_extra(string s)       { Long_Extra = s; }
public void        set_rooftop(int i)                { Rooftop = i; }
public void        set_weather(int i)           { Show_Weather = i; }
public void        set_square(int i)                  { Square = i; }
public void        set_bc_arrive(string s)     { Bc_Arrive_Msg = s; }
public void        set_bc_leave(string s)       { Bc_Leave_Msg = s; }
public void        set_spied(string s)             { Spied_Msg = s; }
public void        set_bc_rooms(string *s)   { Broadcast_Rooms = s; }
public void        set_unique_bc(string *s) { Unique_Broadcast = s; }
public string      query_quadrant()         { return City_Quadrant; }
public string *    query_bc_rooms()       { return Broadcast_Rooms; }
public string      query_bc_arrive()        { return Bc_Arrive_Msg; }
public string      query_bc_leave()          { return Bc_Leave_Msg; }
public string      query_spied_msg()            { return Spied_Msg; }
public object      query_bc_mover()       { return Broadcast_Mover; }
public object      query_bc_viewer()      { return Broadcast_Viewer;}



/*
 * Function name:        create_room
 * Description  :        set up the room
 */
nomask void
create_room()
{
    string *bc_rooms;

    create_sparkle();

    bc_rooms = BC_MODULE->query_broadcast(this_object());

    if (sizeof(bc_rooms))
    {
        set_bc_rooms(bc_rooms);
    }

    set_short(sparkle_short);
    set_long(sparkle_long);

    set_tell_time(180);

    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
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
        shortstr += " in the city of Sparkle. " 
          + this_object()->check_call(Short_Extra);

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
    try_item( ({ "sky", "up", "blue sky", "vivid sky",
                 "vivid blue sky" }), one_of_list(
              ({ "Scattered white clouds drift slowly through the bright"
               + " blue sky overhead.\n",
                 "The sky is bright and blue above.\n",
                 "The sun shines brightly down from the blue sky"
               + " overhead.\n",
              }) ) );
    try_item( ({ "cloud", "clouds", "scattered clouds",
                 "puff", "puffs", "puffs of cloud", "scattered clouds",
                 "scattered white clouds", "drifting cloud",
                 "drifting clouds", "raincloud", "rain cloud",
                 "rainclouds", "heavy raincloud", "heavy rainclouds",
                 "dull raincloud", "dull rainclouds",
                 "dull heavy raincloud", "dull heavy rainclouds",
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
                 "light", "illumination", "brilliant sun" }), one_of_list(
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
    try_item( ({ "steeple", "church steeple", "steeple of the church" }),
        "The steeple of the First Church of Sparkle rises above the"
      + " rooftops at the center of town. It is visible from just about"
      + " anywhere in the city.\n");
    try_item( ({ "tower", "tower of realms", "tall tower",
                 "fabled tower", "fabled tower of realms",
                 "tallest building", "tallest structure" }),
        "Majestic and yet austere, the Tower of Realms rises high above"
      + " any neighboring rooftops - easily the tallest building in all"
      + " of Sparkle. It is visible throughout the city.\n");
    try_item( ({ "horizon", "horizons" }),
        "You pause for a moment and stare into the horizon.\n");
} /* add_outdoor_items */


/*
 * Function name:        add_road_items
 * Description  :        add_items that describe the road
 */
public void
add_road_items()
{
    try_item( ({ "road", "path", "dirt road", "dirt path", "street",
                 "streets", "city street", "city streets",
                 "streets of the city", "streets of town",
                 "streets of sparkle" }),
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
    try_item( ({ "roof", "rooftop", "rooftops", "roof of the building",
                 "top of the building", "nearby rooftop",
                 "nearby rooftops" }),
        "The rooftops of Sparkle peer down over the city streets,"
      + " often-times built so close together that they practically"
      + " touch one another.\n");
} /* add_road_items */


/*
 * Function name:        add_center_items
 * Description  :        Items appropriate for when you are in the
 *                       center of Sparkle
 */
public void
add_center_items()
{
    try_item( ({ "sparkle", "city", "city of sparkle", "town",
                 "village", "town of sparkle", "sparkle city" }),
        "From here in the center of the Old City, the largest buildings"
      + " in Sparkle loom over the streets.\n");
    try_item( ({ "buildings", "large buildings", "largest buildings",
                 "structure", "structures", "ancient structure",
                 "ancient structures", "stone building",
                 "stone buildings", "old building", "old buildings",
                 "old stone building", "old stone buildings",
                 "building" }),
        "Many of the buildings here in the oldest parts of Sparkle are"
      + " extremely large. The steeple of the church rises directly in"
      + " the center of town, and south of that the Tower of Realms"
      + " rises higher still. Other rooftops are less high, but still"
      + " very impressive throughout this area.\n");
    try_item( ({ "church", "first church", "first church of sparkle",
                 "church of sparkle", "sparkle church", "old church" }),
        "The First Church of Sparkle is one of the oldest buildings"
      + " in all of Genesis. Its steeple can be seen from almost anywhere"
      + " in the city.\n");
    try_item( ({ "old city", "oldest parts of sparkle", "the old city",
                 "old sparkle", "old section", "old section of town",
                 "old town" }),
        "Old Sparkle is marked by ancient buildings which have been"
      + " in the realms as long as anyone can remember. As the city has"
      + " grown, they have been expanded somewhat, and newer buildings"
      + " sprouted up around them. Even so, there is a distinct look and"
      + " feel to this old original section of the city.\n");
    try_item( ({ "ancient building", "ancient buildings" }),
        "Boy, some of them sure do look old.\n");
    try_item( ({ "new buildings", "newer buildings", "new building",
                 "newer building" }),
        "As the city has expanded, more and more buildings have continued"
      + " to pop up between the old. In some cases, they are shoehorned"
      + " in rather tightly.\n");
    try_item( ({ "center", "city center", "center of the old city",
                 "sparkle center", "town center", "sparkle town center",
                 "center of town", "center of sparkle",
                 "center of the city" }),
        "This area is the heart of Sparkle. Most of the major"
      + " establishments and features of town reside in this central"
      + " area.\n");
    try_item( ({ "heart of sparkle" }),
        "That it is. You can practially feel it beating with the pulse"
      + " of a thousand citizens and travellers.\n");
    try_item( ({ "citizen", "citizens" }),
        "Look around. You'll find them.\n");
    try_item( ({ "traveller", "travellers" }),
        "I suppose you could count yourself in that category.\n");
    try_item( ({ "gate", "city gate", "city gates", "gates of the city",
                 "old city gate", "old city gates", "gates" }),
        "The city gates can be glimpsed now and then between rooftops"
      + " on the west side of Old Sparkle. These gates used to be the"
      + " only way into Sparkle, but the city has expanded beyond the"
      + " original old walls, and so now it is just a final"
      + " barrier for this inner part of the city.\n");
    try_item( ({ "old wall", "old city wall", "wall of the old city",
                 "wall", "walls", "old walls", "old city walls",
                 "walls of the old city", "old wall of the city",
                 "old walls of the city" }),
        "The wall of the old city is still standing. Though Sparkle has"
      + " continued to expand beyond its original borders, this sturdy"
      + " fortification has remained intact, acting as both a marker for"
      + " these oldest places in town as well as a last defence in the"
      + " case the city were ever again to come under attack.\n");
    try_item( ({ "fortification", "fortifications", "sturdy fortification",
                 "sturdy fortifications" }),
        "The wall may be old, but it will serve for many centuries"
      + " beyond the present without failing.\n");
    try_item( ({ "last defence" }),
        "None shall pass!\n");
    try_item( ({ "road", "street", "city street", "old sparkle road" }),
        "Old Sparkle Road progresses through the center of the city"
      + " winding its way around from the docks to the east.\n");
    try_item( ({ "dock", "docks" }),
        "The docks are not visible from here.\n");
    try_item( ({ "major establishments", "establishments",
                 "establishment", "major establishment" }),
        "There are many. Explore them at your leisure.\n");
    try_item( ({ "central area" }),
        "There is no mistaking it. This is the center of town.\n");

    add_construction_items();
    add_outdoor_items();
    add_road_items();
} /* add_center_items */

    
/*
 * Function name:        add_construction_items
 * Description  :        items that describe the fact that the city is
 *                       undergoing construction
 *
 * When the city is no longer under consruction, the call
 * add_construction_items() should be removed from whatever
 * rooms or functions have included it.
 */
public void
add_construction_items()
{
    try_item( ({ "construction", "construction zone",
                 "construction area", "construction site",
                 "work area", "work zone", "work site" }),
        "There are various work sites and construction zones"
      + " throughout Sparkle at present. Ever since the Genesis"
      + " ShipLine organization took over the shipping industry,"
      + " the heavy influx of visitors to the city has driven up"
      + " commerce, and given the townsfolk both incentive and"
      + " the necessity to expand what the city has to offer.\n");
} /* add_construction_items */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
} /* init */


/*
 * Function name:        broadcast_movement
 * Description  :        When players move along rooftops or beneath
 *                       piers or sewer drains, they will sometimes
 *                       catch the eye of someone on the levels above
 *                       or below them. This function is called when 
 *                       the movement takes place.
 * Arguments    :        object who - the person doing the moving
 *                       int arriving - true if they are arriving to rather 
 *                                      than leaving from the location.
 */
public void
broadcast_movement(object who, int arriving)
{
    object  room;
    mixed  *viewers;
    int     seen_moving = 0; /* is the player seen moving? */
    int     awareness;       /* the awareness of the viewer */
    int     sneak;           /* the sneak skill of the mover */
    string  check_bc = ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg);

    if (!sizeof(Broadcast_Rooms))
    {
        /* There are no rooms that are supposed to see this movement
         * designated, so lets drop here.
         */
        return;
    }

    foreach(string bc_room: Broadcast_Rooms)
    {
        room = find_object(bc_room);
        viewers = FILTER_LIVE(all_inventory(room));

        if (!sizeof(viewers))
        {
            /* Apparently, there are no viable targets who might hope
             * to see the movement, so we drop.
             */
            return;
        }

        /* We need to know if the person moving more than eight feet
         * tall. Huge beings are always seen! (Sorry Ogres!)
         */
        seen_moving = who->query_prop(CONT_I_HEIGHT) > 243;
        sneak = who->query_skill(SS_SNEAK);

        foreach(object viewer: viewers)
        {
            awareness = viewer->query_skill(SS_AWARENESS);

            /* The viewer gets a % chance to see the movement based on
             * their awareness.
             */
            if (awareness - random(90))
            {
                /* But! We don't want to base it entirely on the viewer.
                 * If the mover has good sneak skill, we want to give
                 * them a chance to foil the opportunity. 
                 */
                if ((sneak - random(30)) < (awareness - random(50)))
                {
                    /* If they have some form of enhanced speed, lets
                     * give them one last flip of the coin.
                     */
                    if (who->query_prop(LIVE_I_QUICKNESS) > 99)
                    {
                        if (random(2))
                        {
                            seen_moving = 1;
                        }
                    }
                    else
                    {
                        seen_moving = 1;
                    }
                }
            }

            if (viewer == who)
            {
                /* we don't want to see a message about ourself! */
                return;
            }

            if (seen_moving)
            {
                config_broadcasts(who, viewer);
                check_bc = ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg);

                if (!strlen(check_bc))
                {
                    /* No message has been set, so we drop. */
                    return;
                }

                viewer->catch_tell(
                    ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg));
            }
        }
    }

    return;
} /* broadcast_movement */


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

    start_room_tells();

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


/*
 * Function name:        config_broadcast
 * Description  :        determine what should be broadcast
 * Arguments    :        who - the person broadcasting their movements
 *                       viewer - the one who will see them
 */
public void
config_broadcasts(object who, object viewer)
{
    string *bc_rooms = BC_MODULE->query_broadcast(this_object());

    if (sizeof(bc_rooms))
    {
        set_bc_rooms(bc_rooms);
    }

    if (!sizeof(Unique_Broadcast))
    {
        switch (City_Street)
        {
            case STREET_CENTER:
            case STREET_SOUTHEAST:
            case STREET_SOUTH_1:
            case STREET_SOUTH_2:
            case STREET_SOUTHWEST_1:
            case STREET_SOUTHWEST_2:
            case STREET_SOUTHWEST_3:
            case STREET_WEST:
            case STREET_NORTHWEST:
            case STREET_NORTH:
            case STREET_NORTHEAST_1:
            case STREET_NORTHEAST_2:
            case STREET_NORTHEAST_3:
            case STREET_NORTHEAST_4:
                Bc_Arrive_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_ARRIVE, "street");
                Bc_Leave_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_LEAVE, "street");
                break;
            case STREET_EAST_1:
            case STREET_EAST_2:
            case STREET_EAST_3:
                Bc_Arrive_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_ARRIVE, "docks");
                Bc_Leave_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_LEAVE, "docks");
                if (Rooftop)
                {
                    Bc_Arrive_Msg = format_broadcast(who, viewer,
                        ROOF_TO_STREET_ARRIVE);
                    Bc_Leave_Msg = format_broadcast(who, viewer,
                        ROOF_TO_STREET_LEAVE);
                }
                break;
        }
    }
    else
    {
        Broadcast_Mover = who;
        Broadcast_Viewer = viewer;
        Bc_Arrive_Msg = format_broadcast(who, viewer, Unique_Broadcast[0]);
        Bc_Leave_Msg = format_broadcast(who, viewer, Unique_Broadcast[1]);
    }   
} /* config_broadcasts */


/*
 * Function name:        format_broadcast
 * Description  :        Because we want to do so much with met/nonmet
 *                       and the individual descriptions of movers, we
 *                       need a way to assign and replace placeholders
 *                       in the text. This function takes a given
 *                       text, searches for the break_string of
 *                       MOVER, and replaces it with the appropriate
 *                       call for the description of that mover.
 * Arguments    :        object mover - the one doing the moving
 *                       object viewer - the one seeing the mover
 *                       string bc - the broadcast message
 *                       string where - the type of area the mover is
 *                                      moving in. Default is set to a
 *                                      null string. Define this only
 *                                      if you need to replace the
 *                                      placeholder WHERE in the text.
 * Returns      :        string - the text with the appropriate text
 *                                inserted.
 */
public string
format_broadcast(object mover, object viewer, string bc, string where = "")
{
    string *bc_text = explode(bc, "MOVER");
    string  mover_text = mover->query_art_name(viewer);
    string  formatted_text;

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, mover_text);
    }
    else
    {
        formatted_text = bc;
    }

    bc_text = explode(formatted_text, "WHERE");

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, where);
    }

    return capitalize(formatted_text) + "\n";
} /* format_broadcast */


/*
 * Function name:        check_rating_form
 * Description  :        This function supports the sign rating quest
 *                       for Sparkle. It sets a prop in the player if
 *                       they are currently working on the quest when
 *                       they read a sign.
 * Arguments    :        object who  - the player
 *                       string sign - which sign they have just read
 */
public void
check_rating_form(object who, string sign)
{
    object  form;

    if (!objectp(form = present(RATING_FORM, who)))
    {
        return;
    }

    form->set_sign_rating_prop(who, sign);

    set_alarm(0.5, 0.0, &form->consider_sign(who, sign));
} /* check_rating_form */