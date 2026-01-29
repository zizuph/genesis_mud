#include "defs.h"

inherit TELBERIN_ROYAL_CIRCLE;

public void
create_royal_circle()
{
    set_em_long("Here, within the Royal Circle of Telberin, you are"
      + " surrounded by grandeur on all sides. To the north, a great"
      + " amphitheatre has been hollowed out of the earth, resting"
      + " before a long reflecting pool which extends the length of"
      + " Scholars Way. To the south, the Palace of Telberin dazzles"
      + " the mind with its impossibly twisting towers and turrets,"
      + " which rise almost out of sight above. Fragrant aromas waft"
      + " to meet your senses from the east, where the Royal Magic"
      + " Gardens lie.\n");

    add_item( ({ "amphitheatre", "theatre", "great amphitheatre",
                 "north", "steps" }),
        "North of the Royal Circle, steps lead down into a great"
      + " amphitheatre which is used for various functions in the"
      + " city. Currently, it does not appear as if there is anything"
      + " going on, as the amphitheatre is empty.\n");
    add_item( ({ "smell", "smells", "aroma", "aromas",
                 "fragrance", "fragrant aroma", "fragrant aromas" }),
        "Smells which delight the senses flow into the street from"
      + " the Royal Magic Garden which borders the Royal Circle east"
      + " of here.\n");

    add_exit("royal_circle03", "southeast");
    add_exit("royal_circle01", "southwest");
    add_exit("scholars_way01", "northeast");

    set_no_exit_msg( ({ "northwest" }),
        "Northwest of here, it appears as if much of Scholar's Way"
      + " has been damaged by the recent raids. The road has been"
      + " closed for repairs.\n");
    set_no_exit_msg( ({ "north" }),
        "As you approach the stairway leading down into the amphitheatre,"
      + " an old man stops you, saying: Only dignitaries of the Royal"
      + " Circle are permitted into the Forum.\n");
    set_no_exit_msg( ({ "south" }),
        "Guards confront you as you head towards the Palace. One speaks"
      + " up, saying: Only those on official business are allowed into"
      + " the Palace, due to the raids.\n");

    add_door_exit(TELBERIN_MAGIC_GARDEN_DIR + "garden_gate",
                  "/d/Emerald/telberin/magic_garden/magic1",
                  "east", 0, 0, 1);
}


/*
 * Function name:        do_enter
 * Description  :        allow players to try to enter the
 *                       buildings in the Royal Circle
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
//      notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [great] [royal] 'palace' [of] [telberin]"))
    {
        if (parse_command(arg, ({}),
            "[the] [great] 'amphitheatre' / 'theatre'"))
        {
            if (this_player()->query_wiz_level())
            {
                write("Normally, we would move the player 'north'"
                  + " here, using command(). Since you are a wizard,"
                  + " that won't work. Simply go 'north' yourself.\n");
                return 1;
            } /* if (this_player()->query_wiz_level()) */

            this_player()->command("north");
            return 1;
        } /* if amphitheatre parse_command */
        
        return 0; /* can't parse the player's syntax */
    } /* if palace parse_command */

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'south' here, using"
          + " command(). Since you are a wizard, that won't work. Simply"
          + " go 'south' yourself.\n");
        return 1;
    }

    this_player()->command("south");
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
} /* init */
