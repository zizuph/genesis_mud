/*
 *  /d/Earthsea/gont/sewers/room/pipe.c
 *
 *  A temporary room that gets cloned whenever a player tries to crawl
 *  through a pipe in the sewers.
 *
 *  APR 2021, Aeg
 *  Thank you to Gorboth for help
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>

inherit SEWER_ROOM_BASE;

#include <filter_funs.h>   /* for FILTER_LIVE         */
#include <macros.h>        /* for QCTNAME             */
#include <time.h>          /* for TIME2FORMAT         */

/* Prototypes */
public void        create_sewer();
public void        init();
public string      describe();
public string      pipe_locations(int infinitive = 1);
public void        enter_inv(object ob, object from);
public void        move_wheel(object player);
public int         do_examine(string arg);

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
 * Function name:        create_sewer
 * Descrption   :        set up the room with area presets
 */
public void
create_sewer()
{
    set_short("you are in a pipe");
    set_long(describe);

    setuid();
    seteuid(getuid());
} /* create_sewer */


/*
 * Function name:        describe
 * Description  :        provide a state-dependant descrption for the room
 * Returns      :        string - the text for set_long()
 */
public string
describe()
{
    string   desc = "You are crawling through a dark and wet pipe. "
                  + "";

    return desc + pipe_locations() + "\n";
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
        
