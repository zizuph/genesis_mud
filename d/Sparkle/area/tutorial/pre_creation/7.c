/*
 *  /d/Sparkle/area/tutorial/pre_creation/7.c
 *
 *  This room is part of the pre-creation tutorial that shows players the
 *  most basic elements of playing the mud. This room introduces players
 *  to the idea of races and the different types that can be played.
 *
 *  Created August 2004, by Cooper Shery (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit LIB_DIR + "skip";

#include <login.h>
#include <stdproperties.h>


/* prototypes */
public void        create_room();
public int         gate_shut();
public void        reset_room();
public int         do_enter(string arg);
public void        init();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("7");
    set_short("a small room with many exits");
    set_long("You stand in a large circular chamber with exits on all"
      + " sides. To the south a long corridor extends beyond"
      + " your vision. The east and west wall each have three identical"
      + " doorways leading to small rooms. At the center of the chamber"
      + " stands a shimmering blue portal, beside which a"
      + " large familiar sign provides useful information.\n\n");

    add_item( ({ "chamber", "circular chamber", "large chamber",
                 "large circular chamber", "here", "area" }), long);
    add_item( ({ "south", "south wall", "corridor", "long corridor",
                 "hall", "hallway", "long hallway" }),
        "A long corridor travels from the south wall into the"
      + " distance.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "west", "west wall", "western wall",
                 "door", "doorway", "doors", "doorways",
                 "three doors", "three doorways", "identical doors",
                 "identical doorways" }),
        "There are three doorways in the wall leading into what appear"
      + " to be very small rooms beyond.\n");
    add_item( ({ "room", "rooms", "small room", "small rooms",
                 "very small room", "very small rooms" }),
        "The interior of each room cannot be seen clearly from here.\n");
    add_item( ({ "north", "north wall", "northern wall" }),
        "The northern wall is featureless.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is illuminated by the shimmering portal which"
      + " rises from its center.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "The ceiling of this chamber is high above the floor.\n");
    add_item( ({ "portal", "shimmering portal", "blue portal",
                 "shimmering blue portal", "blue shimmering portal" }),
        "A blue shimmering portal rises from the floor of the chamber."
      + " This portal will take you to the character creation process."
      + " Once you feel that you know enough about the races, and"
      + " statistics, you may begin creating your character by typing"
      + " <enter portal> here.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("hobbit_chamber", "northeast", &log_move("hobbit_chamber"),
             1, 0);
    add_exit("human_chamber", "east", &log_move("human_chamber"),
             1, 0);
    add_exit("goblin_chamber", "southeast", &log_move("goblin_chamber"),
             1, 0);
    add_exit("6", "south", gate_shut, 1, 0);
    add_exit("gnome_chamber", "southwest", &log_move("gnome_chamber"),
             1, 0);
    add_exit("elf_chamber", "west", &log_move("elf_chamber"),
             1, 0);
    add_exit("dwarf_chamber", "northwest", &log_move("dwarf_chamber"),
             1, 0);

    reset_room();
} /* create_room */


/*
 * Function name:        gate_shut
 * Description  :        we want to prevent mortals from backtracking from
 *                       this room. this function provides an explanation
 *                       to the player.
 * Returns      :        int 1
 */
public int
gate_shut()
{
    write("You travel down the southern corridor. However, when you"
      + " get to the end, you find a gate that is shut tight. You"
      + " cannot go that way, so you return to the circular"
      + " chamber.\n");

    return 1;
} /* gate_shut */


/*
 * Function name:        reset_room
 * Description  :        add a sign to the room
 */
public void
reset_room()
{
    object   sign;

    if (!present("_tutorial_sign"))
    {
        sign = clone_object(OBJ_DIR + "sign");
        sign->config_sign("sign");
        sign->set_chapter(7);
        sign->add_adj( ({ "familiar", "useful" }) );
        sign->add_name("information");
        sign->move(this_object());
    }

    return;
} /* reset_room */


/*
 * Function name:        do_enter
 * Description  :        Allow players to begin the character creation
 *                       process
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [blue] [shimmering] 'portal'"))
    {
        if (parse_command(arg, ({}),
            "[the] [northeast] [northeastern]"
          + " [east] [eastern]"
          + " [southeast] [southeastern]"
          + " [southwest] [southwestern]"
          + " [west] [western]"
          + " [northwest] [northwestern]"
          + " 'door' / 'doorway' / 'room'"))
        {
            write("Use one of the obvious exits to get to the room"
              + " you wish to enter. (northeast, east, etc.)\n");

            return 1;
        }

        return 0; /* let the mudlib handle it. */
    }

    write("You step through the portal, and begin the creation"
      + " process.\n");

    write_file(LOG_DIR + "moves", ctime(time())
      + " " + this_player()->query_name() + " **entered** the portal.\n");

    this_player()->set_ghost(this_player()->query_ghost() & ~GP_PRE);
    this_player()->ghost_ready();
    return 1;
} /* do_enter */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
    add_action(tutorial_stat, "stats");
    add_action(tutorial_quit, "quit");
} /* init */


