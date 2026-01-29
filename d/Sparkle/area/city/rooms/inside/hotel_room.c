/*
 *  /d/Emerald/telberin/arts/hotel_room.c
 *
 *  This is the hotel room which can be purchased by players in
 *  the Silver Swan Inn in Telberin. It was copied from the
 *  hotel room in Minas Morgul created by Olorin in 1993.
 *
 *  Copyright (c) March 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../../defs.h"

inherit SPARKLE_ROOM_BASE;

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>


/* Global Variables */
public int         Window_Open = 0;


/* Prototypes */
public void        create_sparkle();
public int         start(string arg);
public void        init();
public string      exa_window();
public string      exa_alley();
public string      exa_roof();
public string      exa_breeze();
public int         mess_with_window(string arg);
public int         climb_window(string arg);
public void        open_window_from_roof();

public int         query_window_open() { return Window_Open; }


/*
 * Function name:        create_sparkle
 * Description  :        set up the room
 */
public void
create_sparkle()
{
    set_short("an upstairs hallway in the Silver Swan Inn in Sparkle");
    set_long("You stand in a long upstairs hallway on the second"
      + " floor of the inn. Wooden doors line the walls, each leading"
      + " to a bedroom. If you have purchased a key downstairs, you"
      + " may <start here> to have Sparkle be the place you will"
      + " awaken the next time you enter Genesis. You notice a window"
      + " at the north end of the hallway, and there is a long"
      + " flight of stairs leading back down to the main room of the"
      + " inn.\n\n");

    add_item( ({ "floor", "ground" }),
        "The floor here has been recently swept, it appears.\n");
    add_item( ({ "ceiling", "up" }),
        "The ceiling is free of dust or any visible cobwebs.\n");
    add_item( ({ "stair", "step", "steps", "stairs", "flight",
                 "flight of stairs" }),
        "The stairs are clean and well-built. They lead down"
      + " to the main floor of the Inn.\n");
    add_item( ({ "main floor", "down", "downstairs", "below",
                 "main room", "main room of the inn" }),
        "The main floor is visible down below the stairs. It is"
      + " there that one might purchase a key for this room, if"
      + " one does not already possess one.\n");
    add_item( ({ "wall", "walls", "floor", "ceiling", "room",
                 "here", "area" }),
        "The walls and floor are all immaculately kept here."
      + " It looks as if this would be a very comfortable place"
      + " to spend the night. There are many doors each leading"
      + " to a bedroom.\n");
    add_item( ({ "door", "doors", "many doors", "bedroom",
                 "bedrooms" }),
        "The bedrooms are where you may stay if you have purchased a"
      + " key downstairs. Just <start here> if you wish to do so.\n");
    add_item( ({ "hall", "hallway", "upstairs", "upstairs hall",
                 "upstairs hallway", "long upstairs hall",
                 "long upstairs hallway", "long hall", "long hallway",
                 "inn", "silver swan inn", "second floor" }),
        "The hallway is immaculately clean and leads onto many"
      + " bedrooms.\n");
    add_item( ({ "north end", "end", "end of the hallway",
                 "north end of the hallway" }),
        "A window is set in the wall at the north end of the hallway.\n");

    add_item( ({ "window" }), "@@exa_window@@");
    add_item( ({ "alley", "alleyway", "outside" }), "@@exa_alley@@");
    add_item( ({ "roof", "rooftop" }), "@@exa_roof@@");
    add_item( ({ "breeze", "wind" }), "@@exa_breeze@@");

    add_cmd_item( ({ "door", "doors" }),
                  ({ "open", "close", "unlock", "lock", "pick" }),
        "No need to fool around with the doors. If you want to"
      + " make one of the bedrooms your own, you just need to"
      + " <start here> once you have purchased a key downstairs.\n");

    add_exit("inn", "down");
    add_prop(ROOM_I_INSIDE, 1);  /* This room is indoors */
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
} /* create_sparkle */


/*
 * Function name:        start
 * Description  :        allows the player to start here, if they have
 *                       the key
 * Returns      :        int 1 - player did something we understand,
 *                           0 - player did something else
 */
public int
start(string arg)
{
    object ob;

    if (!strlen(arg))
    {
        notify_fail("Do you wish to <start here>?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [this] 'room' / 'here'"))
    {
        return 0;
    }


    if (this_player()->query_temp_start_location() ==
        "/d/Sparkle/area/city/rooms/inside/hotel_room")
    {
        write("You have already checked in!\n");
        return 1;
    }

    if (!(ob=present("_the_key_to_the_silver_swan_inn_",
          this_player())))
    {
        write("You need to purchase a key downstairs first.\n");
        return 1;
    }

    ob->remove_object();

    this_player()->set_temp_start_location(
        "/d/Sparkle/area/city/rooms/inside/hotel_room");
    write("Using your key, you enter one of the rooms and make it your"
      + " own. Confident that you will awaken here the next time you"
      + " enter the game, you close the door again behind you. As you"
      + " do so, the slender alabaster key crumbles to dust in your"
      + " hand.\n");
    return 1;
} /* start */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(start, "start");
    add_action(mess_with_window, "open");
    add_action(mess_with_window, "close");
    add_action(climb_window, "climb");
} /* init */


/*
 * Function name:        exa_window
 * Description  :        A state dependant description for the
 *                       window.
 * Returns      :        string - the description
 */
public string
exa_window()
{
    return ((Window_Open) ?
        "The window has been opened, and a cool breeze is moving"
      + " lightly through the hall. Peering out, you notice that the"
      + " window overlooks an alley behind the inn.\n" :
        "The window is closed.\n");
} /* exa_window */


/*
 * Function name:        exa_alley
 * Description  :        A state dependant description for the
 *                       alley.
 * Returns      :        string - the description
 */
public string
exa_alley()
{
    return ((Window_Open) ?
        "Peering out the window, you notice that the peak of the"
      + " roof overhangs the alley, which is deserted.\n" :
        "With the window closed, it is not easy to see much of the"
      + " alley outside.\n");
} /* exa_alley */


/*
 * Function name:        exa_roof
 * Description  :        A state dependant description for the
 *                       roof.
 * Returns      :        string - the description
 */
public string
exa_roof()
{
    return ((Window_Open) ?
        "You lean out the window and gaze up toward the roof, which looks"
      + " almost looks within reach. A skilled climber could"
      + " perhaps find their way up there from here.\n" :
        "To see the roof you'd have to be able to look out the"
      + " window, which is closed.\n");
} /* exa_roof */


/*
 * Function name:        exa_breeze
 * Description  :        A state dependant description for the
 *                       breeze.
 * Returns      :        string - the description
 */
public string
exa_breeze()
{
    return ((Window_Open) ?
        "The breeze is making the hallway fairly chilly. Someone really"
      + " ought to shut the window.\n" :
        "With the window closed, there is no breeze in the hallway.\n");
} /* exa_breeze */


/*
 * Function name:        mess_with_window
 * Description  :        allow players to open/close the window
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mess_with_window(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'window'"))
    {
        return 0;
    }

    switch(query_verb())
    {
        case "open":
            if (Window_Open)
            {
                write("The window is already open, it seems.\n");
                return 1;
            }

            /* We're not ready to open this yet, so lets put in a
             * temporary block.
             */
            write("The window seems stuck. Perhaps someday someone will"
              + " get around to fixing it, but for now it isn't possible"
              + " to open it.\n");
            return 1;

            write("You slide the window open.\n");
            break;
        default:
            if (!Window_Open)
            {
                write("The window is already closed.\n");
                return 1;
            }
            write("You slide the window closed.\n");
            break;
    }

    tell_room(this_object(), QCTNAME(this_player())
      + " " + query_verb() + "s the window.\n", this_player());
    Window_Open = !Window_Open;

    return 1;
} /* mess_with_window */


/*
 * Function name:        climb_window
 * Description  :        allow players to climb out the window on to the
 *                       roof, should they be skilled enough to manage
 *                       it.
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
climb_window(string arg)
{
    int    success;

    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[out] [through] [of] [the] 'window' [on] [to] [the] [roof]") &&
        !parse_command(arg, ({}),
        "[up] [on] [to] [the] 'roof' [through] [the] [window]"))
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    if (!Window_Open)
    {
        notify_fail("But, good " + ((this_player()->query_gender()) ?
           "Lady" : "Sir") + ", the window is closed.\n");
        return 0;
    }

    if (this_player()->query_fatigue() < 20)
    {
        notify_fail("You are too tired to try that right now.\n");
        return 0;
    }

    success = this_player()->resolve_task(TASK_FORMIDABLE,
              ({ SS_CLIMB, SKILL_AVG, TS_STR, TS_DEX, SKILL_END }) );
    dump_array(success);

    this_player()->add_fatigue(-20);

    if (success > 0)
    {
        write("Leaning out of the window, you perch yourself on the sill,"
          + " muster your strength, and hoist yourself up onto the roof,"
          + " climbing with expert skill up and out of the inn.\n");
        this_player()->move_living("M", 
            ROOFTOP_DIR + "room/rooftop_inn", 1, 1);
        tell_room(this_object(), QCTNAME(this_player())
          + " leans out of the window and climbs out of view.\n");

        return 1;
    }
    else if (success <= -50)
    {
        notify_fail("Peering out the window, you make a few vain"
          + " attempts to balance correctly and climb up to the roof,"
          + " but soon realize you lack the skill or physical"
          + " prowess to even make a realistic attempt.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " leans out of the window and struggles around a bit, but"
          + " seems to give up at whatever " + this_player()->query_pronoun()
          + " was attempting.\n", this_player());
        return 0;
    }
    else
    {
        notify_fail("You try to balance correctly on the windowsill"
          + " while working to hoist yourself to the roof. Just as you"
          + " get your elbows up, you realize this is a bit tougher"
          + " than you thought, and you slide back inside the window.\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " leans out of the window and struggles around a bit, but"
          + " seems to give up at whatever " + this_player()->query_pronoun()
          + " was attempting.\n", this_player());
        return 0;
    }

    return 0;
} /* climb_window */


/*
 * Function name:        open_window_from_roof
 * Description  :        This is called if someone from the roof tries
 *                       to open the window.
 */
public void
open_window_from_roof()
{
    tell_room(this_object(), "The window slides slowly open.\n");
    Window_Open = 1;
} /* open_window_from_roof */