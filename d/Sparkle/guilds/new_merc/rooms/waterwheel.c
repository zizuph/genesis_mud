/*
 *  /d/Sparkle/guilds/new_merc/rooms/waterwheel.c
 *
 *  A temporary room that gets cloned whenever a player tries to ride
 *  the waterwheel. Never a static location.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h>   /* for FILTER_LIVE         */
#include <macros.h>        /* for QCTNAME             */
#include <time.h>          /* for TIME2FORMAT         */


/* Prototypes */
public void        create_merc_room();
public void        init();
public int         try_climb(string arg);
public int         ride_wheel(string arg);
public int         do_drink(string arg);
public string      describe();
public string      trough_locations(int infinitive = 1);
public int         do_examine(string arg);
public void        enter_inv(object ob, object from);
public void        move_wheel(object player);
public int         let_go(string arg);
public void        land_player(object player);

/* Global Variables */
public int         Travel_Arc = 0; /* trough positions:
                                    *   0 - near ground
                                    *   1 - halfway to roof
                                    *   2 - nearing roof
                                    *   3 - above roof, nearing top
                                    *   4 - above roof, starting down
                                    *   5 - nearing tipping point
                                    *   6 - player falls!
                                    */

#define            DELAY       10.0


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("you are clinging to the waterwheel");
    set_long(describe);
     
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast", "south",
                        "southwest", "west", "northwest", "up", "down" }),
        "You'll have to let go if you want to do any travelling!\n");

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_examine, "look");
    add_action(do_examine, "exa");
    add_action(do_drink, "drink");
    add_action(try_climb, "climb");
    add_action(ride_wheel, "ride");
    add_action(ride_wheel, "grab");
    add_action(ride_wheel, "grasp");
    add_action(ride_wheel, "hold");
    add_action(ride_wheel, "grip");
    add_action(ride_wheel, "hang");
    add_action(let_go, "let");
    add_action(let_go, "release");
    add_action(let_go, "jump");
} /* init */


/*
 * Function name:        try_climb
 * Description  :        let players try to climb stuff
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
try_climb(string arg)
{
    notify_fail("Climbing is definitely NOT an option right now. You can"
      + " either keep riding this thing or let go.\n");
    return 0;
} /* try_climb */


/*
 * Function name:        ride_wheel
 * Description  :        allow players to climb under the bridge
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
ride_wheel(string arg)
{
    mixed  *targets;
    mixed  *non_seers;
    object  trough;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    notify_fail("Letting go of the trough is the only way you'll"
      + " be able to try to " + query_verb() + " something else!\n");

    if (!parse_command(arg, ({}),
        "[on] [to] [onto] [in] [the] 'trough' / 'troughs' [of] [the]"
      + " [water] [wheel] [waterwheel]"))
    {
        if (parse_command(arg, ({}),
            "[on] [to] [onto] [in] [the] [water] 'waterwheel'"
          + " / 'wheel'"))
        {
            if (query_verb() == "ride")
            {
                notify_fail("You are already doing so! You'll have to"
                  + " let go if you want to try something else.\n");
                return 0;
            }

            notify_fail("If you want to " + query_verb() + " something"
              + " other than this trough, you'll have to first let go."
              + " That may or may not be advisable.\n");
            return 0;
        }

        if (parse_command(arg, ({}),
            "[up] [to] [the] [old] 'mill' / 'roof'"))
        {
            notify_fail("If you want to reach the mill, you'll have to"
              + " wait till you are high enough and then let go of the"
              + " wheel.\n");
            return 0;
        }

        return 0;
    }

    return 0;
} /* ride_wheel */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the spring
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'trough'"))
    {
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("Still hanging on with one hand, you quickly scoop up"
          + " some water from the trough to take a sip. You seem to"
          + " have drunk your fill.\n");
     
    }
    else
    {
        write("Still hanging on with one hand, you quickly scoop up"
          + " some water from the trough and take a sip. You feel"
          + " refreshed, but was that really safe?\n");
    }

    return 1;
} /* do_drink */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant descrption for the room
 * Returns      :        string - the text for set_long()
 */
public string
describe()
{
    string   desc = "You are clinging with all of your might to one of"
                  + " the troughs of a great turning waterwheel! ";

    return desc + trough_locations() + "\n";
} /* describe */


/*
 * Function name:        trough_locations
 * Descrption   :        a text descrption of the position of the player
 *                       along the arc of the waterwheel
 * Arguments    :        int infinitive - true (default) if we want to
 *                                        have the verbs in the 
 *                                        "is rising" form. False if we
 *                                        want it to be in the "rises" form.
 * Returns      :        string - the description 
 */
public string
trough_locations(int infinitive = 1)
{
    switch (Travel_Arc)
    {
        case 0:
            return "The trough you are on is just rising away from the"
              + " level of the riverbed, travelling upward.";
            break;
        case 1:
            return "The trough " + ( (infinitive) ? "has reached" :
                "reaches" ) + " the halfway point along its arc toward"
              + " the top of the mill.";
            break;
        case 2:
            return "The trough is nearing the roofline as it continues"
              + " to travel upward.";
            break;
        case 3:
            return "The trough " + ( (infinitive) ? "has passed" :
                "passes" ) + " above the roof of the mill, and is"
              + " nearing the top of the waterwheel.";
            break;
        case 4:
            return "The trough " + ( (infinitive) ? "has crested" :
                "crests" ) + " the top of the waterwheel, and is now"
              + " heading back down toward the roofline of the mill.";
            break;
        case 5:
            return "The trough " + ( (infinitive) ? "has sunk" :
                "sinks" ) + " beneath the roofline of the mill. You are"
              + " dangerously close to being flipped head over heels!";
            break;
        case 6:
        default:
            return "The trough reaches the halfway mark of its downward"
              + " journey, pitching you headlong into the water along"
              + " the riverbed!";
            break;
    }

    /* should never happen, but just in case */
    return "";
} /* trough_locations */


/*
 * Function name:        do_examine
 * Description  :        We actually want to mask the examine functions
 *                       to prevent the player from looking around at
 *                       much other than the wheel itself.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_examine(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* The mudlib will handle the fail message */
    }

    if (parse_command(arg, ({}),
        "[at] [the] [water] 'waterwheel' / 'wheel'"))
    {
        write("You are clinging to one of its troughs as it turns!\n");
        return 1;
    }

    if (parse_command(arg, ({}),
        "[at] [the] 'trough' / 'troughs' / [of] [the] [water] [wheel]"
      + " [waterwheel]"))
    {
        write(trough_locations() + " You are hanging on to it with"
          + " all of your might!\n");
        return 1;
    }

    write("You are too busy trying to keep yourself from falling"
      + " to examine anything other than what is right in front of"
      + " your face - namely the waterwheel!\n");
    return 1;
} /* do_examine */



/*
 * Function name:        enter_inv
 * Description  :        we mask this to set up the turning motion of
 *                       the wheel and move the trough along the path
 * Arguments    :        object ob   - the object that entered the room
 *                       object from - where it came from
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_alarm(DELAY, 0.0, &move_wheel(ob));
} /* enter_inv */


/*
 * Function name:        move_wheel
 * Description  :        move the position of the trough and dump the
 *                       player if it has moved too far
 * Arguments    :        object player - the player
 */
public void
move_wheel(object player)
{
    Travel_Arc++;

    tell_room(this_object(), trough_locations(0) + "\n");

    if (Travel_Arc > 5)
    {
        if (environment(player) == this_object())
        {
            tell_room(ROOM_DIR + "behind_mill", QCTNAME(player) + " falls"
              + " from above and lands in the water with a heavy"
              + " splash!\n");

            player->move_living("M", ROOM_DIR + "behind_mill", 1, 1);
            player->catch_tell("\nYou land with a splash! OOOOOF!\n");

            write_file(LOG_DIR + "waterwheel",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " rides too far and falls in the water.\n");
        }

        this_object()->remove_object();
    }
    else
        set_alarm(DELAY, 0.0, &move_wheel(player));
} /* move_wheel */


/*
 * Function name:        let_go
 * Description  :        Let the player jump off the waterwheel
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
let_go(string arg)
{
    if (!strlen(arg))
    {
        switch(query_verb())
        {
            case "jump":
                write("You leap from the waterwheel!\n");
                land_player(this_player());
                return 1;
                break;
            case "let":
                notify_fail("Let what? Let go?\n");
                return 0;
                break;
            default:
                notify_fail(capitalize(query_verb()) + " what?\n");
                break;
        }

        return 0;
    }

    if (!parse_command(arg, ({}),
        "[go] [of] [the] [water] 'trough' / 'waterwheel' / 'wheel'"))
    {
        if (query_verb() == "let" &&
            parse_command(arg, ({}),
                "'go' / [of] [the] [water] [wheel] [waterwheel]"
              + " [trough] [troughs]"))
        {
            write("You release your grip on the trough, instantly"
              + " plummeting downward!\n");
            land_player(this_player());

            return 1;
        }

        notify_fail("Do you want to let go of the trough?\n");
        return 0;
    }

    write("You release your grip on the trough, instantly plummeting"
      + " downward!\n");
    land_player(this_player());

    return 1;
} /* let_go */


/*
 * Function name:        land_player
 * Description  :        have the player land in the right place after
 *                       letting go of the wheel.
 * Arguments    :        object player - the player in question
 */
public void
land_player(object player)
{
    switch (Travel_Arc)
    {
        case 3..4:
        {
            tell_room(ROOM_DIR + "mill_roof", QCTNAME(player) + " jumps"
              + " from the top of the waterwheel and lands on the"
              + " roof with a loud thump.\n");

            player->move_living("M", ROOM_DIR + "mill_roof", 1, 1);
            set_alarm(1.0, 0.0, &player->catch_tell(
                "\nYou land on the roof of the mill with a loud"
              + " thump!\n"));
            tell_room(ROOM_DIR + "join", "A loud thump sounds from"
              + " the roof overhead.\n");

            write_file(LOG_DIR + "waterwheel",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " jumps to the mill roof.\n");

            break;
        default:
            tell_room(ROOM_DIR + "behind_mill", QCTNAME(player) + " falls"
              + " from above and lands in the water with a heavy"
              + " splash!\n");

            player->move_living("M", ROOM_DIR + "behind_mill", 1, 1);
            player->catch_tell("\nYou land with a splash! OOOOOF!\n");

            write_file(LOG_DIR + "waterwheel",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " lets go and falls to the water.\n");

            break;
        }
    }
} /* land_player */

