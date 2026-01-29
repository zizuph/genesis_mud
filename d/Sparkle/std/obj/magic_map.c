/*
 *  /d/Sparkle/std/obj/magic_map.c
 *
 *  This magic map is intended to be a major feature throughout Genesis.
 *  It will be given out by Lars to new players when they enter the
 *  game, and they can examine it to see maps of locations they are
 *  in with a "you are here" marker that moves when they do. To get
 *  information on how to set up your areas to function with the map,
 *  please read the man page on genesis_maps.
 *
 *  Created April 2008, by Cooper Sherry (Gorboth)
 *    Much thanks to Novo for his excellent help with this project.
 *
 *  Modification log:
 *     - Jul 23, 2016   (Gronkas): fixed a typo
 *     - Apr 17, 2017   (Gorboth): added a sanity check to prevent
 *                                 bugs when any living thing might
 *                                 enter the player's inventory, on
 *                                 a suggestion by Lucius.
 *     - Oct 6,  2017 (Cotillion): Modified to fetch map data from 
 *                                 MAP_CENTRAL
 *     - Apr 27, 2018   (Gorboth): Implemented remote-scry abilities
 */
#pragma strict_types

inherit "/std/object";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/* Definitions */
#define  SCRY_ACCESS ({ "w/gorboth/obj/crystal_ball.c" })
#define  EMPTY_MAP \
 "          _______________________________________________  __________\n" \
+"     _   /                                               |/          |\n" \
+"    | \\_/                                                            |\n" \
+"   /                                                                 |\n" \
+"  |                                                                  |\n" \
+"  `.                                                                 |\n" \
+"  '                 The map appears completely blank.                |\n" \
+"  |                                                                  |\n" \
+"  |              (You may type <help map> to learn more)             |\n" \
+"  |                                                                  |\n" \
+"  |                                                                  |\n" \
+"  |                                                                  |\n" \
+"  |                                                     _            |\n" \
+"  |                                                _/|_/ |           |\n" \
+"  |_______________________________________________/      |___________|\n"

#define  NO_COORDS_MAP \
 "          _______________________________________________  __________\n" \
+"     _   /                                               |/          |\n" \
+"    | \\_/                                                            |\n" \
+"   /                                                                 |\n" \
+"  |                                                                  |\n" \
+"  `.                                                                 |\n" \
+"  '             There actually is a map for this place ...           |\n" \
+"  |                                                                  |\n" \
+"  |      ... but you fail to find your current location on it.       |\n" \
+"  |                                                                  |\n" \
+"  |                                                                  |\n" \
+"  |                                                                  |\n" \
+"  |                                                     _            |\n" \
+"  |                                                _/|_/ |           |\n" \
+"  |_______________________________________________/      |___________|\n"

#define ZOOM_FOOTER "\n" \
+"==================================[Legend]====================================\n" \
+"     - o -  Room locations and obvious direction exits\n"                         \
+"     - X -  Room you are currently standing in\n"                                 \
+"==============================================================================\n" \
+"     The <zoom> command displays a less-detailed map of the larger area.\n"

#define NORM_FOOTER "\n" \
+"==================================[Legend]====================================\n" \
+"     . . .  Borders of the various zones (shown as * if you are within)\n"        \
+"     - o -  Room locations and obvious direction exits\n"                         \
+"     - X -  Room you are currently standing in\n"                                 \
+"==============================================================================\n"

#define MAP_HEADER \
 "==============================================================================\n" \
+"                            -*- The Magic Map -*-\n"                              \
+"==============================================================================\n"

#define MAP_HEADER_WIZ(path) \
 "==============================================================================\n" \
+" Magic Map file: " + ( path )+ "\n" \
+"==============================================================================\n"

/* Global Variables */
public int         Remote_Scry = 0;
public int         Glowing = 0;
public mixed       Glow_Alarm;
public object      Owner;
public mixed       Viewer = 0;
public int         Locked = 0;

/* Prototypes */
public string      map_long_desc();
public int         remote_scry_display(object viewer, object target);
public int         check_access();

/*
 * Function name: map_short_desc
 * Description  : Provide a short description of the magic based on whether
 *                or not the map is currently glowing.
 * Returns      : string - the description 
 */
public string
map_short_desc()
{
    return (Glowing ? "glowing " : "") + "magic map";
}

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("map");
    add_name(MAGIC_MAP_ID);
    set_adj("magic");
    
    set_short(map_short_desc);
    set_long(map_long_desc);

    add_cmd_item( ({ "map", "magic map", "the map", "the magic map" }),
                  ({ "read" }), map_long_desc);

    add_prop(OBJ_I_NO_DROP, "Throw away such a useful thing as the"
      + " magic map? If you really want to, you may <discard> it.\n");
    add_prop(OBJ_I_NO_SELL, "You'd better keep it. Too useful!\n");
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    setuid();
    seteuid(getuid());
}


/*
 * Function name: query_map_filename
 * Description  : Find out the filename of the map of this location.
 * Returns      : string - the filename, or 0.
 */
public string
query_map_filename()
{
    object room;

    if (!Owner) Owner = environment();
    
    room = environment(Owner);
    /* Room is a vessel in another room. */
    if (room->query_room_env())
    {
        room = room->query_room_env();
    }
    
    return MAP_CENTRAL->query_maplink(MASTER_OB(room));
}

/*
 * Function name: query_map_data
 * Description  : Find out the f
 * Returns      : string - the filename, or 0.
 */
public mixed
query_map_data()
{
    object room;

    if (!Owner) Owner = environment();

    room = environment(Owner);
    /* Room is a vessel in another room. */
    if (room->query_room_env())
    {
        room = room->query_room_env();
    }

    return MAP_CENTRAL->query_room_map_data(MASTER_OB(room));
}



/*
 * Function name: load_text_map
 * Description  : Fetch the map contents from the MAP_CENTRAL
 * Arguments    : string mfile - the text file that contains the
 *                     map we want to use.
 *                string msection - the section of the map we want
 *                     to draw. The default is to draw the "main" map.
 * Returns      : string array - the map in array form
 */
public string *
load_text_map(string mfile, string msection = "main")
{
    string map = MAP_CENTRAL->query_map(mfile, msection);

    if (!strlen(map))
    {
        return ({ "" });
    }


    string *rows = ({ });
    foreach (string row: explode(map, "\n")) 
    {
        rows += ({ row + "\n" });
    }
    
    return rows;
} /* load_text_map */


/*
 * Function name: draw_map
 * Description  : This is Novo's improvement on my earlier methods. It takes
 *                an existing map and draws both the point at which the player
 *                stands and bolds the borders of the section of the map the
 *                player is in.
 * Arguments      string mapdata - the array containing the text lines of the map
 *                int x - the x coordinate on the map
 *                int y - the y coordinate on the map
 *                    (both of these represent where the player stands)
 *                int zoom - true if this is a zoomed-in map, in which case we
 *                     do not use the borders. Default = false.
 */
public void
draw_map(string *mapdata, int x, int y, int zoom = 0)
{
    string *maplines = ({ }) + mapdata;
    string  header;
    int     index    = 0,
            edgex    = x,
            edgey    = y,
            startx,
            starty,
           *deltas   = ({ 0, 1, -2, 0, 0, -1, 2, 0 }),
            deltapos = 2,
            match    = 1,
            testx,
            testy;
    object  original_owner = Owner;

    Owner = Viewer || original_owner;

    if ((y >= 0) && (y <  sizeof(maplines)) &&
        (x >= 0) && (x <  strlen(maplines[y])) &&
       !zoom)
    {
        /* Find the closest starting dot to the left of out point. */
        while ((edgex >= 0) && maplines[edgey][edgex] != '.')
        {
            edgex--;
        }

        if (edgex >= 0)
        {
            startx = edgex;
            starty = edgey;

            /* Match indicates we found a dot and need to make another. */
            while (match)
            {
                /* Mark the edge. */
                maplines[edgey] = (edgex ?maplines[edgey][..edgex - 1] : "" )
                    + "*" + maplines[edgey][edgex + 1..];

                /* We will try to make a left turn first.
                 * Then we will check the other directions -
                 * straight line, right turn, backwards.
                 */
                deltapos = (4 + deltapos) % (sizeof(deltas));
                    
                match = 0;                
                for (int i = 0; i < 4; i++)
                {
                    deltapos = (2 + deltapos) % (sizeof(deltas));

                    /* Try to find the next dot. */
                    testx = edgex + deltas[deltapos];
                    testy = edgey + deltas[deltapos + 1];
                    
                    if ((startx == testx) && (starty == testy))
                    {
                        break;
                    }
                    
                    if ((testy >= 0) && (testy < sizeof(maplines)) &&  
                        (testx >= 0) && (testx < strlen(maplines[testy])) &&
                        (maplines[testy][testx] == '.'))
                    {
                        edgex = testx;
                        edgey = testy;
                        match = 1;                        
                        break;
                    }
                }
            }
        }
    }
    else if (y >= sizeof(maplines) ||
             x >= strlen(maplines[y]))
    {
        if (Remote_Scry)
        {
            Owner->catch_tell("No vision appears. How strange ...\n");
        }
        else
        {
            Owner->catch_tell(NO_COORDS_MAP);
        }

        Owner = original_owner;
        Viewer = 0;

        return;
    }

    maplines[y] = maplines[y][..x-1] + "X" + maplines[y][x+1..];

    if (Remote_Scry)
    {
        Owner->catch_tell(implode(maplines, ""));

        Viewer = 0;
        Owner = original_owner;
        return;
    }

    header = (Owner->query_wiz_level() ? MAP_HEADER_WIZ(query_map_filename()) : MAP_HEADER);
    Owner->catch_tell(header + implode(maplines, "") +
        ((zoom) ? ZOOM_FOOTER : NORM_FOOTER));
    Owner = original_owner;
    Viewer = 0;

    return;
} /* draw_map */


/*
 * Function name: display_full
 * Description  : This displays the map, zoomed out, so that the player can
 *                see what part of town they are currently in.
 * Arguments    : int zoom - true if we want to zoom to the appropriate sub-map
                      for the room this player is in. Default = false.
 * Returns      : int 1 - success always
 */
public int
display_full(int zoom = 0)
{
    mixed mapdata = query_map_data();

    if (!mapdata)
    {
        if (Remote_Scry)
        {
            write("Haze, and nothing more, is all that appears.\n");
            return 1;
        }

        write("The map is blank, and thus you cannot <zoom> out"
          + " to a larger view.\n");
        return 1;
    }

    string mapfile = mapdata[0];
    string section = mapdata[1];
    int x = mapdata[2];
    int y = mapdata[3];

    if (!zoom && section != "main") 
    {
        section = "main";
        x = mapdata[4];
        y = mapdata[5];
    }

    string *maprows = load_text_map(mapfile, section);

    if (sizeof(maprows) < 2)
    {
        write(EMPTY_MAP);
        return 1;
    }

    draw_map(maprows, x, y, zoom);
    return 1;
} /* display_full */


/*
 * Function name: map_long_desc
 * Description  : This is called when people try to examine or read the map.
 *                If a map file has been defined for the room the player is
 *                in, the map is displayed and a null string returned. If not,
 *                a message indicating that the map is blank is returned as
 *                text.
 * Returns      : string - null on success, text otherwise
 */
public string
map_long_desc()
{
    mixed  mapfile = query_map_filename();

    if (mapfile)
    {
        display_full(1);
        return "";
    }

    return EMPTY_MAP;
}


/*
 * Function name: map_zoom
 * Description  : Action for the player to use to trigger the map_module
 * Arguments    : string arg - what was typed after the verb
 * Returns      : 1 - success always
 */
public int
map_zoom(string arg)
{
    display_full(0);

    return 1;
}


/*
 * Function name: map_discard
 * Description  : Let the player get rid of the map. Maybe they don't want
 *                it anymore?
 * Arguments    : string arg - what was typed after the verb
 * Returns      : int 1 - success, 0 - failure
 */
public int
map_discard(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to discard?\n");
        return 0;
    }

    if (!parse_command(arg, ({ }), "[a] [the] [magic] 'map'"))
    {
        notify_fail("Discard the magic map?\n");
        return 0;
    }

    write("You toss the magic map aside. A little wind lifts it and"
      + " carries it away.\n");
    remove_object();
    return 1;
}


/*
 * Function name: init
 * Description  : Add some actions to the player
 */
public void
init()
{
    ::init();

    if (Locked || !query_interactive(this_player()) ||
        this_player() != environment())
    {
        return;
    }

    Owner = this_player();
    Locked = 1;

    add_action(map_discard, "discard");
    add_action(map_zoom,    "zoom");
}


/*
 * Function name: notify_glow
 * Description  : Tell the player about their map's glowing status.
 * Arguments    : int glow - 0/1 - new non-glowing/glowing state
 */
public void
notify_glow(int glow)
{
    Owner->catch_tell("Your magic map " +
        (glow ? "begins to glow" : "is no longer glowing") + ".\n");
        
    Glowing = glow;
    if (Glowing)
    {
	add_adj("glowing");
    }
    else
    {
	remove_adj("glowing");
    }
}


/*
 * Function:    notify_new_room
 * Description: This is called to notify of a new room that the player entered.
 *              Use a little delay in case the person runs around. We don't
 *              want the map to glow/unglow like a disco.
 */
public void
notify_new_room()
{
    int hasmap = stringp(query_map_filename());
    if (Glow_Alarm)
    {
        remove_alarm(Glow_Alarm);
    }

    /* This uses XOR to determine if it's needed to give a message.
     *  Glowing + !HasMap = News
     * !Glowing +  HasMap = News
     *  Glowing +  HasMap = No News
     * !Glowing + !HasMap = No News
     */
    if (Glowing ^ hasmap)
    {
        Glow_Alarm = set_alarm(0.5, 0.0, &notify_glow(hasmap));
    }
}


/*
 * Function name: query_auto_load
 * Description  : allow this to always start with the player
 */
public string
query_auto_load(void)
{
    return MASTER;
}


/*
 * Function name:        remote_scry_display
 * Description  :        Allow someone to get the magic map readout
 *                       of this player's location who is NOT this
 *                       player. This is a very special ability, so
 *                       we will create a whitelist of objects that
 *                       are allowed to do it.
 * Arguments    :        object viewer - the player who is performing
 *                                       the scry
 *                       object target - the player being scried
 * Returns      :        int 1 - allowed
 *                       int 0 - failed (not allowed)
 */
public int
remote_scry_display(object viewer, object target)
{
    int     not_allowed = check_access();
    object  original_owner = Owner;
    int     fail;

    if (not_allowed || target->query_wiz_level())
    {
        viewer->catch_tell("You are stricken momentarily with blurred"
          + " vision! Perhaps this knowledge if forbidden to you.\n");
        return 1;
    }

    fail = target->query_prop(LIVE_M_NO_SCRY) ||
           environment(target)->query_prop(ROOM_M_NO_SCRY);

    if (stringp(fail))
    {
        viewer->catch_tell(fail + "\n");
        return 1;
    }
    else if (fail)
    {
        viewer->catch_tell("Something prevents you from seeing that"
          + " person right now.\n");
        return 1;
    }

    Remote_Scry = 1;
    Viewer = viewer;
    Owner = target;

    display_full(1);

    Viewer = 0;
    Owner = original_owner;
    Remote_Scry = 0;

    return 1;
} /* remote_scry_display */


/*
 * Function name:        check_access
 * Description  :        control who is allowed to do something
 * Returns      :        int 0 - allowed
 *                       int 1 - not allowed
 */
public int
check_access()
{
    string  caller = calling_program(-1);
    string  func = calling_function(-1);

    if (!caller)
    {
        return 1;
    }

    if (!IN_ARRAY(caller, SCRY_ACCESS))
    {
        return 1;
    }

    /* TODO: create whitelist stuff here */
    return 0;
} /* check_access */
