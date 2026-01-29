#include "defs.h"

inherit TELBERIN_ROYAL_CIRCLE;

public void
create_royal_circle()
{
    set_em_long("You stand upon the eastern arc of the Royal Circle of"
     + " Telberin. The grandeur of this part of the city is truly"
     + " remarkable. To the east, a great temple stands, covering the"
     + " skyline with its vast framework of pillars and stone. More"
     + " impressive still is the great Palace of Telberin to the west."
     + " Rising high into the air, spire upon spire, tower above tower,"
     + " its highest peaks are barely within view.\n");

    add_item( ({ "skyline", "framework", "vast framework", "pillars",
                 "pillar", "stone", "pillars and stone", "east",
                 "vast framework of pillars and stone" }),
        "The skyline is nearly blotted out east of here, where the"
      + " Temple of Telberin stands. Its bulk is formed of numerous"
      + " pillars carved from heavy stone. They twist and turn about"
      + " the structure in a dazzling display of architecture and"
      + " craftsmanship.\n");

    add_exit("royal_circle04", "southwest");
    add_exit("royal_circle02", "northwest");
    add_exit("cantors_way07", "northeast");

    set_no_exit_msg( ({ "southeast" }),
        "The road to the southeast has been closed off for repairs."
      + " It appears as if the southern stretch of Cantor's Way has"
      + " been badly damaged in the recent raids.\n");
    set_no_exit_msg( ({ "east" }),
        "A priest at the entrance to the Temple raises his hand as you"
      + " approach, and you feel yourself unable to proceed.\n");
    set_no_exit_msg( ({ "west" }),
        "As you approach the Palace, numerous guards cut you off, stating"
      + " that due to the recent raids, no one may approach without"
      + " specific permission.\n");
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
            "[the] [great] 'temple' [of] [telberin]"))
        {
            if (this_player()->query_wiz_level())
            {
                write("Normally, we would move the player 'east'"
                  + " here, using command(). Since you are a wizard,"
                  + " that won't work. Simply go 'east' yourself.\n");
                return 1;
            } /* if (this_player()->query_wiz_level()) */

            this_player()->command("east");
            return 1;
        } /* if temple parse_command */
        
        return 0; /* can't parse the player's syntax */
    } /* if palace parse_command */

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'west' here, using"
          + " command(). Since you are a wizard, that won't work. Simply"
          + " go 'west' yourself.\n");
        return 1;
    }

    this_player()->command("west");
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
