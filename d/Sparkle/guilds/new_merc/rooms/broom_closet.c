/*
 *  /d/Sparkle/guilds/new_merc/broom_closet.c
 *
 *  This is a broom closet located in the Mercenary Guild hall. Graffiti
 *  abounds!
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 *
 *  Revision History:
 *    Aug 01, 2019 - add_broom() created at request of frustrated would-
 *                   be guild-housekeepers! The thing kept being
 *                   taken and lost.
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>

/* Prototypes */
public void        create_merc_room();
public void        init();
public int         do_carve(string arg);
public void        save_carving(string arg, object who, string wfile);
public int         do_read(string arg);
public void        print_footer(object who);
public string      exa_wall(string which);
public int         add_broom();

/* Definitions */
#define            MAX_MSG_LENGTH    50  /* Graffiti limiter */

/* Global Variables */
public mixed       Broom = 0;


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    object   door;

    set_short("in a rather cramped broom closet");
    set_long("There isn't a great deal of room inside this"
      + " broom closet. The walls are fairly close on all sides.\n\n");

    add_item( ({ "floor", "ground", "down", "closet floor",
                 "floor of the closet" }),
        "The closet floor isn't much to look at.\n");
    add_item( ({ "roof", "ceiling", "up" }),
        "The ceiling is low and slanted here. This is probably the"
      + " free space located beneath the stairs.\n");
    add_item( ({ "stair", "stairs", "staircase" }),
        "You can't see the staircase from here, but you are probably right"
      + " beneath it.\n");
    add_item( ({ "graffiti", "bit of graffiti", "writing" }),
        "For whatever reason, it appears as if this broom closet has"
      + " appealed to the urge some people have to <carve> messages in"
      + " public spaces. Each individual wall has different amounts"
      + " displayed.\n");
    add_item( ({ "wall", "individual wall", "individual walls" }),
        "Which wall did you wish to examine?\n");
    add_item( ({ "walls" }),
        "The walls in here seem to have a bit of graffiti carved into"
      + " them.\n");
    add_item( ({ "amount", "amounts", "different amounts" }),
        "Can you be more specific? Where are you trying to look?\n");
    add_item( ({ "north wall", "northern wall", "wall to the north",
                 "north" }), &exa_wall("north"));
    add_item( ({ "east wall", "eastern wall", "wall to the east",
                 "east" }), &exa_wall("east"));
    add_item( ({ "south wall", "southern wall", "wall to the south",
                 "south" }), &exa_wall("south"));
    add_item( ({ "west wall", "western wall", "wall to the west",
                 "west" }), &exa_wall("west"));
    add_item( ({ "room", "here", "area", "closet", "broom closet" }),
        "I suppose making this area beneath the stairs into a closet"
      + " seemed like a good use of space to the builders of the lodge.\n");
    add_item( ({ "area beneath the stairs" }),
        "That's where you are standing.\n");
    add_item( ({ "builder", "builders", "builder of the lodge",
                 "builders of the lodge", "lodge builder",
                 "lodge builders" }),
        "Whoever they were, they must not have liked to waste perfectly"
      + " good space.\n");
    add_item( ({ "space" }),
        "Its too bad there isn't more of it in here.\n");
    add_item( ({ "lodge", "building", "mercenary lodge",
                 "old lodge", "loggers lodge", "old loggers lodge" }),
        "You're in it ... in probably its smallest room!\n");
    add_item( ({ "smallest room" }),
        "Yes. Enjoying yourself?\n");

    add_indoor_view();

    add_prop(ROOM_I_INSIDE, 1);

    set_no_exit_msg( ({ "north", "east", "south" }),
        "There is a wall there.\n");
    set_no_exit_msg( ({ "northeast", "southeast", "southwest",
                        "northwest" }),
        "Trying to wedge yourself into the corner won't help.\n");

    setuid();
    seteuid(getuid());

    door = clone_object(DOORS_DIR + "broom_e");
    door->move(this_object());

    add_broom();
} /* create_room */


/*
 * Function name:        init
 * Description  :        add some functions to the player
 */
public void
init()
{
    ::init();

    add_action(do_carve, "carve");
    add_action(do_carve, "write");
    add_action(do_carve, "graffiti");
    add_action(do_read, "read");
} /* init */


/*
 * Function name:        do_carve
 * Description  :        Let players try to carve some graffiti on one
 *                       of the walls.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_carve(string arg)
{
    mixed *locations = ({ "wall",
                          "walls",
                          "north wall",
                          "northern wall",
                          "east wall",
                          "eastern wall",
                          "south wall",
                          "southern wall",
                          "west wall",
                          "western wall",
                       });
    string  wall_file = "";
    object *weapons;
    int     knife = 0,
            i;

    if (!strlen(arg))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[on] [the] %p", locations))
    {
        notify_fail("Did you feel like carving somthing on one of the"
          + " walls? It looks like others have.\n");
        return 0;
    }

    switch(locations[0])
    {
        case "wall":
        case "walls":
            notify_fail("There are four walls here. Please be more"
              + " specific.\n");
            return 0;
            break;
        case "north wall":
        case "northern wall":
            wall_file = "north";
            break;
        case "east wall":
        case "eastern wall":
            wall_file = "east";
            break;
        case "south wall":
        case "southern wall":
            wall_file = "south";
            break;
        case "west wall":
        case "western wall":
            wall_file = "west";
            break;
        default:
            notify_fail("There seems to be a bug here. Please mail"
              + " Gorboth.\n");
            return 0;
            break;
    }

    weapons = this_player()->query_weapon(-1);

    for (i = 0 ; i < sizeof(weapons) ; i++)
    {
        if (weapons[i]->query_wt() == W_KNIFE)
        {
            knife = 1;
            break;
        }
    }

    if (!knife)
    {
        notify_fail("You'd probably need to be wielding a knife if you"
          + " wanted to carve something into a wall.\n");
        return 0;
    }

    write("You take your blade and begin to carve something into the "
      + wall_file + "ern wall.\n");
    write("Enter the message you wish to carve. ("
      + MAX_MSG_LENGTH + " characters max)\n");
    write("] ");

    wall_file = "graffiti_" + wall_file;

    input_to(&save_carving( , this_player(), wall_file));

    return 1;
} /* do_carve */


/*
 * Function name:        save_carving
 * Description  :        Take the input from the do_carve function and
 *                       save it to the appropriate file.
 * Arguments    :        string arg - the text that was carved
 *                       object who - the player doing the writing
 *                       string wfile - the direction of the wall that
 *                                      the player is writing on
 */
public void
save_carving(string arg, object who, string wfile)
{
    int     msg_length = strlen(arg);
    int     remainder = 72 - msg_length;
    int     mrnd = random(remainder);
    int     remainder2 = remainder - mrnd;
    string  msg;

    if (!who)
    {
        return;
    }

    if (!msg_length)
    {
        who->catch_tell("You decide not to carve anything after all.\n");
        return;
    }

    if (arg == "~q" || arg == "quit" || arg == "**")
    {
        who->catch_tell("You can't think of anything to carve, and"
          + " lower your blade.\n");
        return;
    }

    if (strlen(arg) > MAX_MSG_LENGTH)
    {
        who->catch_tell("Carving is hard work! Try a shorter message.\n");
        return;
    }

    /* The goal here is to make it look like the graffiti is carved
     * into a wall with borders, and that the graffiti doesn't all line
     * up in a perfect column - we want it to look like your typical
     * bathroom stall in the pub!
     */
    msg = "| " + (" " * mrnd) + arg + (" " * remainder2) + " |\n"
        + "|                                                 "
        + "                         |\n";

    /* This saves it to the files the players will see when they
     * examine specific walls. (messages are anonymous)
     */
    write_file(LOG_DIR + wfile, msg);

    /* This logs it for wizard-eyes only. I don't really want to know
     * who said what, but in the case of unacceptable stuff being
     * written (profanity and slander is fine, but I won't tolerate
     * racism or such) I can know who was guilty.
     */
    write_file(LOG_DIR + "graffiti",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " wrote: " + arg + " (" + wfile[9..] + ")\n");

    who->catch_tell("You add a bit of new graffiti to the "
      + wfile[9..] + " wall.\n");
    tell_room(this_object(), QCTNAME(who) + " adds a bit of graffiti"
      + " to the " + wfile[9..] + " wall.\n", who);

    return;
} /* save_carving */


/*
 * Function name:        do_read
 * Description  :        allow players to read the graffiti
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_read(string arg)
{
    mixed *locations = ({
                      "north",
                      "northern",
                      "north wall",
                      "northern wall",
                      "north graffiti",
                      "northern graffiti",
                      "north writing",
                      "northern writing",
                      "east",
                      "eastern",
                      "east wall",
                      "eastern wall",
                      "east graffiti",
                      "eastern graffiti",
                      "east writing",
                      "eastern writing",
                      "south",
                      "southern",
                      "south wall",
                      "southern wall",
                      "south graffiti",
                      "southern graffiti",
                      "south writing",
                      "southern writing",
                      "west",
                      "western",
                      "west wall",
                      "western wall",
                      "west graffiti",
                      "western graffiti",
                      "west writing",
                      "western writing",
                    });
    string  wfile;
    int     full = 0,
            i;
    string *entire_txt;

    if (!strlen(arg))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (arg == "graffiti" ||
        arg == "the graffiti" ||
        arg == "wall" ||
        arg == "the wall" ||
        arg == "walls" ||
        arg == "the walls" ||
        arg == "writing" ||
        arg == "the writing" ||
        arg == "carving" ||
        arg == "the carving" ||
        arg == "carvings" ||
        arg == "the carvings")
    {
        notify_fail("Graffiti covers many of the"
          + " walls in here. Which did you wish to read?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[at] [the] [entire] %p [wall] [walls] [graffiti]", locations))
    {
        notify_fail("You don't seem to be able to read that.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[at] [the] 'entire' %p [wall] [walls] [graffiti]", locations))
    {
        full = 1;
    }

    switch(locations[0])
    {
        case "north":
        case "northern":
            wfile = "north";
            break;
        case "east":
        case "eastern":
            wfile = "east";
            break;
        case "south":
        case "southern":
            wfile = "south";
            break;
        case "west":
        case "western":
            wfile = "west";
            break;
        default:
            write("An error has occurred. Please mail Gorboth.\n");
            return 0;
            break;
    }

    if (!read_file(LOG_DIR + "graffiti_" + wfile))
    {
        write("Unlike most of the other walls in here, the " + wfile
          + " wall has not yet been carved with any graffiti.\n");
        return 1;
    }

    write("\nYou "
      + ((full) ? "carefully read all of the" :
          "glance over the most recent") + " graffiti"
      + " carved into the " + wfile + " wall:\n"
      + "================================================================"
      + "============\n");

    if (full)
    {
        entire_txt = explode(read_file(LOG_DIR + "graffiti_" + wfile),
                             "\n");

        for (i = 0; i < sizeof(entire_txt); i++)
        {
            write(entire_txt[i] + "\n");
        }

        print_footer(this_player());
        return 1;
    }
    else
    {
        tail(LOG_DIR + "graffiti_" + wfile);
    }

    write(
        "================================================================"
      + "============\n");
    write("        To read more than just the most recent additions, you"
      + " can\n");
    write("                  <read entire [direction] wall>\n");

    return 1;
} /* do_read */


/*
 * Function name:        print_footer
 * Description  :        print a footer to the graffiti when players have
 *                       finished reading it
 * Arguments    :        object who - the player to write to
 */
public void
print_footer(object who)
{
    who->catch_tell(
        "================================================================"
      + "============\n");
    return;
} /* print_footer */


/*
 * Function name:        exa_wall
 * Description  :        show players whether any graffiti is written
 *                       on the walls
 * Arguments    :        string which - which wall we are looking at
 *                                      "north", "east", "south", "west"
 * Returns      :        string - the description
 */
public string
exa_wall(string which)
{
    string  desc;
    string  graffiti = read_file(LOG_DIR + "graffiti_" + which);

    if (strlen(graffiti))
    {
        return "The " + which + "ern wall appears to have some graffiti"
          + " carved into it. You could probably <read> it if you wanted"
          + " to take the time to do so.\n";
    }

    return "Unlike most of the other walls in here, the " + which
          + "ern wall has not yet been carved with any graffiti.\n";
} /* exa_wall */


/*
 * Function name:        add_broom
 * Description  :        Pearl (the powerful witch who is also the
 *                       waitress of the mess-hall adds a broom to the
 *                       closet whenever she realizes it is missing, and
 *                       at the initial load. Players can ask her about
 *                       the broom to get her to replace it if it has
 *                       gone missing.
 * Returns      :    int 0 - if the broom is already here
 *                       1 - if the broom did not exist
 *                       2 - if the broom was in a different room
 *                       3 - if the broom was in someone's inventory
 */
public int
add_broom()
{
    object  broom_location;
    int     broom_status = 2;

    if (!objectp(Broom))
    {
        Broom = clone_object(OBJ_DIR + "broom");
        Broom->move(this_object());
        return 1;
    }

    if (present(Broom, this_object()))
    {
        return 0;
    }

    broom_location = environment(Broom);

    if (living(broom_location))
    {
        broom_location->catch_tell("The sturdy broom you are carrying"
          + " suddenly vanishes with a loud pop!\n");
        broom_status++;
    }
    else
    {
        tell_room(broom_location, "The sturdy broom suddenly vanishes"
          + " from sight with a loud pop!\n");
    }

    Broom->move(this_object());
    tell_room(this_object(), "A broom suddenly materializes with a loud"
      + " pop and leans itself against the wall of the closet.\n");

    return broom_status;
} /* add_broom */
