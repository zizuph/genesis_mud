/*
 *  /d/Sparkle/area/city/rooftops/rooftop_inn.c
 *
 *  The rooftop of the Silver Swan Inn in Sparkle.
 *
 *  Created April 2011, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include "defs.h"

inherit ROOFTOP_ROOM_BASE;
inherit "/d/Sparkle/area/city/lib/utility_functions";


/* Global Variables */
public object           Ground_Below = STREET_DIR + "center_a";
public object           Inside_Inn = ROOMS_DIR + "inside/hotel_room";


/* Prototypes */
public void             init();
public int              climb_cmd(string arg);
public void             create_rooftop_room();
public int              mess_with_window(string arg);


/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  

    add_action(climb_cmd, "climb");
    add_action(climb_cmd, "enter");
    add_action(mess_with_window, "open");
    add_action(mess_with_window, "close");
} /* init */


/* 
 * Function name:       create_rooftop_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_rooftop_room()
{
    set_short("on the roof of the Silver Swan Inn");
    set_long("A very nice view is available here atop the roof of the"
      + " Silver Swan Inn. Below, the street is visible leading in to"
      + " the Post Office, beyond which the high rooftops of the First"
      + " Church of Sparkle block most of the view to the south. Just"
      + " to the west, the rooftop of the Enchanter's Workshop runs"
      + " alongside this one, if a bit lower in level. To the east,"
      + " the docks are visible above the buildings.\n\n");
                              
    add_item( ({ "view", "nice view", "very nice view" }),
        "The view from the rooftop is impressive even though here it"
      + " is somewhat limited by other nearby buildings.\n");

    add_item( ({ "nearby buildings", "buildings", "building" }),
        "The buildings visible from this rooftop include the Post"
      + " Office which is across the street from the Inn, the AoP"
      + " Office just southeast of here, and the Enchanter's Workshop"
      + " directly to the west. A ways to the south the First Church"
      + " of Sparkle rises high above much of the other buildings.\n");   
                    
    add_item( ({ "tower", "tower of realms" }),
        "The Tower of Realms is visible rising above everything else"
      + " in the city some distance to the southeast.\n");
    
    add_item( ({ "ledge", "window ledge", "sill", "window sill",
                 "window" }), "@@exa_window@@");

    add_item( ({ "rooftop", "rooftops", "roof", "roofs" }),
        "All around you are various rooftops in Sparkle. You are"
      + " surprised how closely they have all been built together."
      + " Quite near to this one is the roof of the Enchanter's"
      + " Workshop, just to the west.\n");

    add_item( ({ "inn", "silver swan", "silver swan inn" }),
        "You're standing on it's roof!\n");

    add_item( ({ "street", "below" }),
        "Below you here, a fountain is in the middle of the street,"
      + " before the entrances to the Post Office, Inn, and AoP office.\n");

    add_item( ({ "post office", "post", "office" }),
        "The Post Office is just south of this Inn.\n");

    add_item( ({ "aop office", "aop" }),
        "The AoP Office is just southeast of the Inn here. The corner"
      + " of its roof is probably a good 20 yards from here.\n");

    add_item( ({ "workshop", "enchanter", "enchanters workshop",
                 "enchanter workshop", "enchanter's workshop",
                 "rooftop of the enchanters workshop",
                 "rooftop of the enchanter's workshop",
                 "rooftop of the enchanter workshop",
                 "workshop roof", "workshop rooftop",
                 "enchanter roof", "enchanter rooftop",
                 "enchanters roof", "enchanters rooftop",
                 "enchanter's roof", "enchanter's rooftop" }),
        "The rootop of the Enchanter's Workshop is directly to the west,"
      + " just a few feet away and slightly below the level of where"
      + " you are standing.\n");

    add_item( ({ "church", "sparkle church", "first church of sparkle",
                 "roofline", "roofline of the church",
                 "church roofline",
                 "roofline of the first church of sparkle" }),
        "The roofline of the First Church of Sparkle is massive, blocking"
      + " out much of the view to the south.\n");

    add_item( ({ "dock", "docks" }),
        "The docks are only just visible above the buildings to the"
      + " east.\n");

    add_item( ({ "building to the east", "buildings to the east" }),
        "The buildings to the east are not in full view. You would need"
      + " to travel over to the docks to view them from the front.\n");

    add_item( ({ "fountain" }),
        "The fountain below shines brightly in the light.\n");

    /* Lets add some room tells */
    add_tell("A continuous and fresh-smelling breeze tugs at your"
      + " clothing.\n");
    add_tell("A few swallows dart past you, soaring over the neighboring"
      + " rooftops and out of sight.\n");
    add_tell("A group of people below walk past the fountain and into"
      + " the Post Office.\n");
    add_tell("A cloud passes before the sun, casting sudden shade over"
      + " the area.\n");

    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
    
    // Set up the broadcast room calls
    // set_broadcast_room_type(ROOM_TYPE_ROOF);
    // register_broadcast_rooms( ({ STREET_DIR + "center_a" }) ); 
} /* create_rooftop_room */


/*
 * Function name:        climb_cmd
 * Description  :        This is the way to get back down off the roof
 *                       back into the Library
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        nothing
 */
public int
climb_cmd(string arg)
{
    object    *watchers;
    object     old_room;
    object     new_room = safely_load_master_file(Inside_Inn);
    
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }
    
    if (!parse_command(arg, ({}),
        "[down] [in] [through] [to] [the] 'window'"))
    {
        if (parse_command(arg, ({}),
            "[down] [from] [the] 'roof'"))
        {
            write("Climb down from the roof? Where do you wish to climb"
              + " to?\n");
            return 1;
        }

        return 0;
    }

    if (!new_room->query_window_open())
    {
        write("The window is closed. You'd need to find a way to open it"
          + " first.\n");
        return 1;
    }

    old_room = this_object();
    write("You hang down from the ledge of the roof and slip yourself"
      + " in through the open window.\n");

    /* Send a message to the old room to tell them what happened. */
    watchers = FILTER_LIVING_OBJECTS(all_inventory(old_room));
    watchers = filter(watchers, this_player()->check_seen);
    watchers -= ({ this_player() });
    watchers->catch_msg(QCTNAME(this_player()) + " climbs down over the"
        + "edge of the roof and disappears.\n", watchers);
    
    if (!objectp(new_room))
    {
        return 1;
    }
        
    watchers = FILTER_LIVING_OBJECTS(all_inventory(new_room));
    watchers = filter(watchers, this_player()->check_seen);
    watchers -= ({ this_player() });    
    if (this_player()->move_living("M", new_room) == 0)
    {
        /* Write the arrival messages in the new room. */
        watchers->catch_msg(QCTNAME(this_player()) + " climbs in"
          + " through the window.\n");
    }
        
    return 1;
} /* climb_cmd */


/*
 * Function name:        exa_window
 * Description  :        allow players to examine the window
 * Returns      :        string - the description (state dependant)
 */
public string
exa_window()
{
    return ("A window is built high into the north side of the Inn, just"
      + " below the overhang of the roof. " +
        ((Inside_Inn->query_window_open()) ? 
        "The window is wide open.\n" : "The window is closed.\n") );
} /* exa_window */


/*
 * Function name:        mess_with_window
 * Description  :        allow players to try to open/close the window
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mess_with_window(string arg)
{
    string  word;
    int     window_open = Inside_Inn->query_window_open();
    object *weapons = this_player()->query_weapon(-1);

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'window'") &&
        !parse_command(arg, ({}),
        "[the] 'window' [with] [the] %w", word))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (query_verb() == "close")
    {
        if (!window_open)
        {
            write("The window is already closed.\n");
            return 1;
        }

        write("You can't manage to close the window from up here. It can"
          + " probably only be effectively done from inside the Inn.\n");
        return 1;
    }

    if (window_open)
    {
        write("The window is alread wide open.\n");
        return 1;
    }

    if (!sizeof(weapons))
    {
        write("You struggle to open the window, but can't quite reach"
          + " it. Perhaps if you were wielding something?\n");
        return 1;
    }

    write("Using the length of your " + weapons[0]->short() + " to your"
      + " advantage, you manage to hook the lip of the window, and slowly"
      + " pull it open.\n");
    Inside_Inn->open_window_from_roof();
    tell_room(this_object(), QCTNAME(this_player())
      + " leans over the northern edge of the roof for a moment.\n",
        this_player());

    return 1;
} /* mess_with_window */