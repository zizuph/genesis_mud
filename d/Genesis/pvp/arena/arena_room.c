/*
 *  /d/Genesis/pvp/arena/arena_room.c
 *
 *  This is the base file for rooms in the raid arena area for pvp in
 *  Genesis. It interprets a text-drawn map to create rooms based on what
 *  has been set for a given tile in a given position.
 *
 *  Created May 2014, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <composite.h>
#include <macros.h>
#include "../defs.h"


/* Global Variables */
static mapping           No_exit_msg = ([]); /* custom no-exit msgs */
public int               Arena_Row;
public int               Arena_Column;
public string            Arena_Room_Type;
public string           *Arena_Map_Rows;
public string            Nw_Room = "blocked";
public string            N_Room  = "blocked";
public string            Ne_Room = "blocked";
public string            E_Room  = "blocked";
public string            Se_Room = "blocked";
public string            S_Room  = "blocked";
public string            Sw_Room = "blocked";
public string            W_Room  = "blocked";
public string            Nw_Type = "cliffs";
public string            N_Type  = "cliffs";
public string            Ne_Type = "cliffs";
public string            E_Type  = "cliffs";
public string            Se_Type = "cliffs";
public string            S_Type  = "cliffs";
public string            Sw_Type = "cliffs";
public string            W_Type  = "cliffs";
public string            Assault_Move = "";
public int               Travel_Alarm;
public string            Extraline = "";
public string            Siege_Position = "";


/* Prototypes */
public void              create_room();
public void              create_arena_room(); 
public void              define_positions();
public void              load_arena_map();
public void              define_exits();
public void              arena_setup();
public int               travel_delay();
public void              travel_now(object who);
public int               stop_travel(string arg);
public void              init();
public string            define_room_type(int this_row, int this_column);
public string            describe();
public void              set_no_exit_msg(mixed dir, string msg);
public int               unq_no_move(string str);
public void              add_extraline(string arg);
public string            which_block();

public string
query_room_position()
{
    return Arena_Row + "-" + Arena_Column;
}

public void
query_blocks()
{
    write("Arena_Room_Type = " + Arena_Room_Type + "\n\n");

    write("Nw_Room = " + Nw_Room + "\n"
        + "N_Room = " + N_Room + "\n"
        + "Ne_Room = " + Ne_Room + "\n"
        + "E_Room = " + E_Room + "\n"
        + "Se_Room = " + Se_Room + "\n"
        + "S_Room = " + S_Room + "\n"
        + "Sw_Room = " + Sw_Room + "\n"
        + "W_Room = " + W_Room + "\n");

    write("Nw_Room = " + Nw_Type + "\n"
        + "N_Room = " + N_Type + "\n"
        + "Ne_Room = " + Ne_Type + "\n"
        + "E_Room = " + E_Type + "\n"
        + "Se_Room = " + Se_Type + "\n"
        + "S_Room = " + S_Type + "\n"
        + "Sw_Room = " + Sw_Type + "\n"
        + "W_Room = " + W_Type + "\n");
}


/*
 * Function name:        create_room
 * Description  :        the constructor
 */
public void
create_room()
{
    TELL_G("create_room called");

    setuid();
    seteuid(getuid());

    create_arena_room();

    add_prop(ROOM_S_MAP_FILE, "arena_map.txt");

    set_short("a " + Arena_Room_Type);
    set_long(describe);
} /* create_room */


/*
 * Function name:        create_arena_room
 * Description  :        dummy routine to be redefined as needed
 */
public void
create_arena_room()
{
} /* create_arena_room */


/*
 * Function name:        define_positions
 * Description  :        get the coordinates for this rooms
 *                       position based on it's filename. Example:
 *
 *                           3-12.c (filename)
 *                           becomes row 3, column 12
 */
public void
define_positions()
{
    string   this_filename;
    string  *coordinates;
    int      row;
    int      column;

    TELL_G("define_positions called");

    this_filename = explode(file_name(this_object()), "/")[-1..][0];

    // TELL_G("filename = " + this_filename);

    coordinates = explode(this_filename, "-");

    Arena_Row    = atoi(coordinates[0]);
    Arena_Column = atoi(coordinates[1]);

    Arena_Room_Type = define_room_type(Arena_Row, Arena_Column);
    TELL_G("arena_setup: Arena_Room_Type = " + Arena_Room_Type);

    // TELL_G("Row = " + Arena_Row + ", Column = " + Arena_Column);

    if (Arena_Row > 1)
    {
        row = Arena_Row - 1;

        if (Arena_Column > 1)
        {
            Nw_Room = row + "-" + (Arena_Column - 1);
            Nw_Type = define_room_type(row, (Arena_Column -1));
        }
        else
        {
            set_no_exit_msg( ({ "northwest" }), which_block());
        }

        N_Room = row + "-" + Arena_Column;
        N_Type = define_room_type(row, Arena_Column);

        if (N_Type == "castle wall" || N_Type == "castle gate")
        {
            Siege_Position = N_Type;
        }

        if (Arena_Column < 39)
        {
            Ne_Room = row + "-" + (Arena_Column + 1);
            Ne_Type = define_room_type(row, (Arena_Column + 1));
        }
        else
        {
            set_no_exit_msg( ({ "northeast" }), which_block());
        }
    }
    else
    {
        set_no_exit_msg( ({ "north", "northwest", "northeast" }),
            which_block());
    }

    if (Arena_Row < 21)
    {
        row = Arena_Row + 1;

        if (Arena_Column > 1)
        {
            Sw_Room = row + "-" + (Arena_Column - 1);
            Sw_Type = define_room_type(row, (Arena_Column -1));
        }
        else
        {
            set_no_exit_msg( ({ "southwest" }), which_block());
        }

        S_Room = row + "-" + Arena_Column;
        S_Type = define_room_type(row, Arena_Column);

        if (Arena_Column < 39)
        {
            Se_Room = row + "-" + (Arena_Column + 1);
            Se_Type = define_room_type(row, (Arena_Column + 1));
        }
        else
        {
            set_no_exit_msg( ({ "southeast" }), which_block());
        }
    }
    else
    {
        set_no_exit_msg( ({ "south", "southwest", "southeast" }),
            which_block());
    }

    if (Arena_Column > 1)
    {
        W_Room = Arena_Row + "-" + (Arena_Column - 1);
        W_Type = define_room_type(Arena_Row, (Arena_Column -1));

        if (W_Type == "castle wall" || W_Type == "castle gate")
        {
            Siege_Position = W_Type;
        }
    }
    else
    {
        set_no_exit_msg( ({ "west" }), which_block());
    }

    if (Arena_Column < 39)
    {
        E_Room = Arena_Row + "-" + (Arena_Column + 1);
        E_Type = define_room_type(Arena_Row, (Arena_Column +1));

        if (E_Type == "castle wall" || E_Type == "castle gate")
        {
            Siege_Position = E_Type;
        }
    }
    else
    {
        set_no_exit_msg( ({ "east" }), which_block());
    }
} /* define_positions */


/*
 * Function name:        load_arena_map()
 * Description  :        Generate an array of the various rows in the
 *                       text map of the arena, and store it as a
 *                       global variable.
 */
public void
load_arena_map()
{
    Arena_Map_Rows = explode(
                         read_file(ARENA_DIR + "arena_map.txt"), "\n");
} /* load_arena_map */


/*
 * Function name:        define_exits();
 * Description  :        create room exits for this room based on 
 *                       its coordinates on the map, and the surrounding
 *                       rooms.
 */
public void
define_exits()
{
    mapping  travel_diff = ([ "forest" : 7,
                              "plains" : 5,
                              "shore"  : 4,
                              "river"  : 9,
                              "road"   : 3,
                              "swamp"  : 10,
                           ]);
    int      travel_fatigue = travel_diff[Arena_Room_Type];

    TELL_G("define_exits called");

    if (Nw_Room != "blocked")
    {
        add_exit(Nw_Room, "northwest", travel_delay, travel_fatigue, 0);
    }

    if (N_Room != "blocked")
    {
        add_exit(N_Room, "north", travel_delay, travel_fatigue, 0);
    }

    if (Ne_Room != "blocked")
    {
        add_exit(Ne_Room, "northeast", travel_delay, travel_fatigue, 0);
    }

    if (E_Room != "blocked")
    {
        add_exit(E_Room, "east", travel_delay, travel_fatigue, 0);
    }

    if (Se_Room != "blocked")
    {
        add_exit(Se_Room, "southeast", travel_delay, travel_fatigue, 0);
    }

    if (S_Room != "blocked")
    {
        add_exit(S_Room, "south", travel_delay, travel_fatigue, 0);
    }

    if (Sw_Room != "blocked")
    {
        add_exit(Sw_Room, "southwest", travel_delay, travel_fatigue, 0);
    }

    if (W_Room != "blocked")
    {
        add_exit(W_Room, "west", travel_delay, travel_fatigue, 0);
    }

    if (sizeof(query_exit()) < 24)
    {
        if (Arena_Room_Type == "river")
        {
            add_extraline("The river narrows and becomes dangerous"
              + " rapids as it enters a gap in the cliffs here.");
        }
        else
        {
            add_extraline("The " + Arena_Room_Type + " comes to a"
                        + " halt at the base of rocky cliffs here.");
        }
    }
} /* define_exits */



/*
 * Function name:        arena_setup
 * Description  :        Called by all the shell room locations to
 *                       procedurally construct their content based
 *                       on the text map.
 */
public void
arena_setup()
{
    TELL_G("arena_setup called");

    load_arena_map();
    define_positions();
    define_exits();
} /* arena_setup */


/*
 * Function name:        travel_delay
 * Description  :        Create a delay when moving between rooms in
 *                       the arena based on the difficulty of the terrain.
 * Returns      :        1 - delay before move, 0 - move now
 */
public int
travel_delay()
{
    mapping  travel_diff = ([ "forest" : 7.0,
                              "plains" : 5.0,
                              "shore"  : 4.0,
                              "river"  : 9.0,
                              "road"   : 3.0,
                              "swamp"  : 10.0,
                           ]);
    mixed    delay = this_player()->query_prop(TRAVEL_DELAY);
    mapping  directions = ([ "nw" : "northwest",
                              "n" : "north",
                             "ne" : "northeast",
                              "e" : "east",
                             "se" : "southeast",
                              "s" : "south",
                             "sw" : "southwest",
                              "w" : "west",
                          ]);
    mapping  destination = ([ "northwest" : Nw_Room,
                                  "north" : N_Room,
                              "northeast" : Ne_Room,
                                  "east"  : E_Room,
                              "southeast" : Se_Room,
                                  "south" : S_Room,
                              "southwest" : Sw_Room,
                                   "west" : W_Room,
                            ]);

    mapping  dest_type   = ([ "northwest" : Nw_Type,
                                  "north" : N_Type,
                              "northeast" : Ne_Type,
                                  "east"  : E_Type,
                              "southeast" : Se_Type,
                                  "south" : S_Type,
                              "southwest" : Sw_Type,
                                   "west" : W_Type,
                            ]);
    string   travel;

    travel = directions[query_verb()];
    travel = ((travel) ? travel : query_verb());

    // TELL_G("travel_delay called:\n\tdelay = " + delay + "\n\t"
    //   + "travel = " + travel);

    switch (dest_type[travel])
    {
        case "castle wall":
            write("You boldly stroll directly into the castle wall."
              + " OOOF!\n");
            return 1;
            break;
        case "castle gate":
            write("The castle gate is closed.\n");
            return 1;
            break;
        default:
            break;
    }

    if (this_player()->query_wiz_level())
    {
        write("As a wizard, you stride confidently forward.\n");
        say(QCTNAME(this_player()) + ", as a wizard, moves with ease.\n");
        return 0;
    }

    if (delay)
    {
        if (delay == "complete")
        {
            return 0;
        }

        if (query_verb() == delay)
        {
            write("You continue heading " + travel
              + ", but travel in this area seems to take some time.\n");
        }
        else
        {
            write("You turn from your " + delay + "erly "
              + "course, and begin heading " + travel + ".\n");
            say(QCTNAME(this_player()) + " turns and begins heading"
              + " to the " + travel + ".\n");

            this_player()->add_prop(TRAVEL_DELAY, travel);

            remove_alarm(Travel_Alarm);
            Travel_Alarm = set_alarm(travel_diff[Arena_Room_Type], 0.0,
                                 &travel_now(this_player()));

        }
    }
    else
    {
        write("You begin heading to the " + travel + ".\n");
        say(QCTNAME(this_player()) + " begins heading to the "
          + travel + ".\n");

        Travel_Alarm = set_alarm(travel_diff[Arena_Room_Type], 0.0,
                                 &travel_now(this_player()));
        this_player()->add_prop(TRAVEL_DELAY, travel);
    }

    return 1;
} /* travel_delay */


/*
 * Function name:        travel_now
 * Description  :        Move the player to the room they are
 *                       travelling to.
 * Arguments    :        object : who - the player
 */
public void
travel_now(object who)
{
    string  where = this_player()->query_prop(TRAVEL_DELAY);

    // TELL_G("travel_now called: where = " + where);

    this_player()->add_prop(TRAVEL_DELAY, "complete");
    this_player()->command("$" + where);
    this_player()->remove_prop(TRAVEL_DELAY);
} /* travel_now */


/*
 * Function name:        stop_travel
 * Description  :        Allow someone to type <stop> to stop from
 *                       travelling in a certain direction.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int: 1 - success, 0 - failure
 */
public int
stop_travel(string arg)
{
    string  where = this_player()->query_prop(TRAVEL_DELAY);

    if (strlen(arg))
    {
        if (where)
        {
            notify_fail(capitalize(query_verb()) + " what?"
              + " If you want to stop heading "
              + where + ", simply type <" + query_verb() + ">.\n");
        }
        /* If they typed an arg, lets pass it to the mudlib. */
        return 0;
    }

    if (where)
    {
        write("You decide to halt.\n");
        say(QCTNAME(this_player()) + " comes to a halt.\n");

        remove_alarm(Travel_Alarm);
        this_player()->remove_prop(TRAVEL_DELAY);
        return 1;
    }
    else if (query_verb() == "halt")
    {
        notify_fail("You aren't currently headed anywhere.\n");
        return 0;
    }

    return 0;
} /* stop_travel */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    add_action(stop_travel, "stop");
    add_action(stop_travel, "halt");

    ::init();
} /* init */


/*
 * Function name:        define_room_type
 * Description  :        scan the text map for the coordinate that matches
 *                       this rooms position, and determine the type of
 *                       room this should be:
 *
 *                          @ = forest
 *                          " = plains
 *                          ` = shore
 *                          ~ = river
 *                          H = road
 *                          % = swamp
 * Arguments    :         int this_row   : the row value,
 *                            this_column: the column value.
 */
public string
define_room_type(int this_row, int this_column)
{
    string  *arena_row_columns;
    string   arena_map_character;
    mapping  arena_room_types;
    mapping  surrounding_rooms;

    TELL_G("define_room_type called!");

    arena_room_types = ([  "@" : "forest",
                          "\"" : "plains",
                           "`" : "shore",
                           "~" : "river",
                           "H" : "road",
                           "%" : "swamp",
                           "_" : "castle wall",
                           "|" : "castle wall",
                           "T" : "watchtower",
                           "#" : "castle gate",
                      ]);

    arena_row_columns = explode(Arena_Map_Rows[this_row - 1], " ");
    arena_map_character = arena_row_columns[this_column];

    return arena_room_types[arena_map_character];
} /* define_room_type */


/*
 * Function name:        describe
 * Description  :        Create a room description based on the
 *                       things in the area.
 * Returns      :        string - the description
 */
public string
describe()
{
    string   room_type_desc;
    string   desc = "";
    mapping  room_type_txt;
    mapping  area = ([ "northwest" : Nw_Type,
                           "north" : N_Type,
                       "northeast" : Ne_Type,
                            "east" : E_Type,
                       "southeast" : Se_Type,
                           "south" : S_Type,
                       "southwest" : Sw_Type,
                            "west" : W_Type,
                    ]);
    string  *area_dirs = m_indices(area);
    mapping  area_diff = ([]);
    string  *diff_dirs;
    mapping  diff_varieties = ([]);
    string  *this_v;
    int      cliffs = 0;

    room_type_txt = ([  "forest"      : ({ "looms", "rises", "closes in" }),
                        "plains"      : ({ "open", "expand", "lie" }),
                        "shore"       : ({ "sits", "lies", "appears" }),
                        "river"       : ({ "runs", "flows", "courses" }),
                        "road"        : ({ "stretches", "travels", "is" }),
                        "swamp"       : ({ "lurks", "emerges", "is" }),
                        "castle wall" : ({ "rises", "towers", "stands" }),
                        "castle gate" : ({ "looms", "stands", "rises" }),
                        "watchtower"  : ({ "is visible", "appears",
                                           "rises" }),
                      ]);

    TELL_G("describe called");

    foreach(string dir : area_dirs)
    {
        if (area[dir] != Arena_Room_Type)
        {
            TELL_G(dir + " is " + area[dir]);
            area_diff += ([ dir : area[dir] ]);

            this_v = diff_varieties[area[dir]];

            if (!sizeof(this_v))
            {
                this_v = ({ dir });
            }
            else
            {
                this_v += ({ dir });
            }

            diff_varieties[area[dir]] = this_v;
        }
    }

//  dump_array(diff_varieties);

    diff_dirs = m_indices(area_diff);      

    if (!sizeof(diff_dirs))
    {
        switch(Arena_Room_Type)
        {
            case "forest":
                desc += "Trees surround you here in the forest. ";
                break;
            case "plains":
                desc += "The plains stretch out in all directions. ";
                break;
            case "swamp":
                desc += "The fetid swamplands are all about you. ";
                break;
            default:
                desc += "There appears to be an error. ";
                break;
        }
    }
    else
    {
        switch(Arena_Room_Type)
        {
            case "forest":
                desc += "You are within a forest. ";
                break;
            case "plains":
                desc += "You stand upon the plains. ";
                break;
            case "shore":
                desc += "You are upon a sandy shoreline. ";
                break;
            case "river":
                desc += "You are wading in the waters of a river. ";
                break;
            case "road":
                desc += "You are on a long north-south road. ";
                break;
            case "swamp":
                desc += "You are in a fetid swamp. ";
                break;
            case "watchtower":
                desc += "You are within a tall watchtower. ";
                break;
            default:
                desc += "You are in an area with an error. ";
                break;
        }

        foreach(string d_var : m_indices(diff_varieties))
        {
            TELL_G("d_var = " + d_var);
            switch(d_var)
            {
            case "forest":
                room_type_desc = one_of_list(
                    ({ "a dark forest", "an outline of trees",
                       "the edge of a forest" }) );
                break;
            case "plains":
                room_type_desc = one_of_list(
                    ({ "wide grasslands", "open fields",
                       "windswept plains" }) );
                break;
            case "shore":
                room_type_desc = one_of_list(
                    ({ "a quiet shoreline", "the shore of a river",
                       "a sandy shore" }) );
                break;
            case "river":
                room_type_desc = one_of_list(
                    ({ "a swift river", "river water",
                       "a churning riverbed" }) );
                break;
            case "road":
                room_type_desc = one_of_list(
                   ({ "a paved roadway", "a long road",
                       "an open road" }) );
                break;
            case "swamp":
                room_type_desc = one_of_list(
                    ({ "a dark swampland", "a foul marsh",
                       "a fetid swamp" }) );
                break;
            case "castle wall":
                room_type_desc = one_of_list(
                    ({ "a huge castle wall", "a massive stone wall",
                       "the foundation of a huge wall" }) );
                break;
            case "watchtower":
                room_type_desc = one_of_list(
                    ({ "a tall watchtower", "a lookout tower",
                       "the shape of a watchtower" }) );
                break;
            case "castle gate":
                room_type_desc = "a sturdy castle gate";
                break;
            case "cliffs":
                cliffs = 1;
                break;
            default:
                room_type_desc = "something unknown";
                break;
            }

            if (!cliffs)
            {
                desc += capitalize(room_type_desc) + " "
                     + one_of_list(room_type_txt[d_var]) + " to the "
                     + COMPOSITE_WORDS(diff_varieties[d_var]) + ". ";
            }
        }
    }

    if (this_player()->query_wiz_level() && strlen(Siege_Position))
    {
        desc += "SEIGE POSITION: " + Siege_Position + ". ";
    }

    return desc + Extraline + "\n\n";
} /* describe */       


/*
 * From: /d/Gondor/std/room.c
 *
 * Function name:       set_no_exit_msg
 * Description  :       set the custom no-exit msg for direction(s)
 * Arguments    :       mixed dir -- either a string or an array of strings;
 *                                   each string is a direction for which
 *                                   this room does not have an exit.
 *                      string msg -- the msg for these directions
 *
 * So instead of "There is no obvious exit west.", you can tell
 * players "You wander west among the trees for a bit, then return
 * to the road."
 */
public void
set_no_exit_msg(mixed dir, string msg)
{
    int         i, n;

    if ( pointerp(dir) )
    {
        for ( i = 0, n = sizeof(dir); i < n; ++i )
            No_exit_msg[dir[i]] = msg;
    }
    else if ( stringp(dir) && strlen(dir) )
    {
        No_exit_msg[dir] = msg;
    }
} /* set_no_exit_msg */


/*
 * Function name: unq_no_move
 * Description  : mask parent to do custom msgs for 'normal' but
 *                nonexistant directions.  Here, 'normal'
 *                exits are north, southeast, down, etcetera.
 * Arguments    : string str - the command line argument.
 * Returns      : int 0 - always.
 */
public int
unq_no_move(string str)
{
    string      vb = query_verb();

    if ( strlen(No_exit_msg[vb]) )         /* custom msg */
        notify_fail(No_exit_msg[vb]);
    else                                /* oh, well */
        notify_fail("There is no obvious exit "+vb+".\n");
    return 0;
} /* unq_no_move */


/*
 * Function name:        add_extraline
 * Description  :        Increase the long description with additional
 *                       room detail.
 * Arguments    :        string arg - the extra detail to include.
 */
public void
add_extraline(string arg)
{
    Extraline += arg + " ";
} /* add_extraline */


/*
 * Function name:        which_block
 * Description  :        Determine which is the correct message for
 *                       the no_exit_msg.
 * Returns      :        string - the correct msg
 */
public string
which_block()
{
    TELL_G("which_block: Arena_Room_Type = " + Arena_Room_Type);

    switch (Arena_Room_Type)
    {
        case "river":
            return "The river becomes dangerous rapids as it"
              + " enters the cliffs in that direction. You dare"
              + " not proceed.\n";
            break;
        case "road":
            return "This is where we would exit the arena, but"
                  + " that isn't set up yet.\n";
            break;
        default:
            return "Rocky cliffs block movement in that"
                          + " direction.\n";
            break;
    }

    /* Shouldn't be possible, but just in case. */
    return "You cannot go that way, for some strange reason.\n";
} /* which_block */


/*
 * Function name:        query_assault_move
 * Description  :        determine which direction an npc would want
 *                       to move if in this room on its way to the
 *                       keep.
 * Returns      :        string - the direction (e.g. "ne")
 */
public string
query_assault_move()
{
    if (strlen(Siege_Position))
    {
        return "say Oho! Lets try to take this " + Siege_Position + "!";
    }

    if (Arena_Room_Type == "road")
    {
        return "n";
    }

    if (Nw_Type == "castle wall")
    {
        return one_of_list( ({ "n", "w" }) );
    }

    if (Ne_Type == "castle wall")
    {
        return one_of_list( ({ "n", "e" }) );
    }

    if (Arena_Row > 5)
    {
        if (Arena_Column < 16)
        {
            return one_of_list( ({ "ne", "n", "e" }) );
        }
        else if (Arena_Column > 24)
        {
            return one_of_list( ({ "nw", "n", "w" }) );
        }
        else
        {
            return one_of_list( ({ "nw", "ne", "n"}) );
        }
    }

    if (Arena_Column < 16)
    {
        if (Arena_Row > 1)
        {
            if (Arena_Row < 21)
            {
                return one_of_list( ({ "e", "ne", "se" }) );
            }
            else
            {
                return one_of_list( ({ "e", "ne" }) );
            }
        }
        else
        {
            return one_of_list( ({ "e", "se" }) );
        }
    }

    if (Arena_Row > 1)
    {
        if (Arena_Row < 21)
        {
            return one_of_list( ({ "w", "nw", "sw" }) );
        }
        else
        {
            return one_of_list( ({ "w", "nw" }) );
        }
    }

    return one_of_list( ({ "w", "sw" }) );
} /* query_assault_move */
