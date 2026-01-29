/*
 *  /d/Genesis/start/human/wild2/orcfort/stair.c
 *
 *  This room is the link between Vladimir's old stuff and the new
 *  dugeons beneath the temple.
 *
 *  Created December 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "local.h"


/* Prototypes */
public void        create_room();
public int         check_exit();
public int         climb_stairs(string arg);
public void        init();


/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    set_short("before a dark stairway");
    set_long("You stand at the end of a cramped passage which ends here"
      + " at the foot of a dark stairway leading down. South, a large"
      + " chamber is visible.\n\n");

    add_item( ({ "passage", "cramped passage", "here", "area", "corridor" }),
        "This corridor stops here at the stairway.\n");
    add_item( ({ "stair", "stairs", "stairway", "dark stairway",
                 "dark stair", "dark stairs" }),
        "The stairs lead down into darkness.\n");
    add_item( ({ "dark", "darkness" }),
        "The darkness is unusually heavy.\n");
    add_item( ({ "south", "chamber", "large chamber" }),
        "Heading south would take you back into the temple chamber.\n");
    add_item( ({ "temple", "temple chamber" }),
        "This temple is a place the orcs worship their god, Kalak.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");

    add_exit(ORC + "temple", "south");
    add_exit("/d/Sparkle/area/orc_temple/rooms/1_up", "down",
        check_exit, 1, 0);
    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        see if players can use this exit
 * Returns      :        0 - let the player move this way
 *                       1 - block the player
 */
public int
check_exit()
{
    write("\nYou descend the stairway into the dungeons ... \n\n");

/* No need for logs and notifications, currently ...
    find_living("gorboth")->catch_msg("\n\n\t"
      + capitalize(this_player()->query_real_name())
      + " enters the ORC DUNGEONS!!  ---**---***---*****\n\n");

    write_file("/d/Genesis/start/human/wild2/orcfort/enter", 
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name()) + " entered the"
      + " dungeons!\n");
*/

    return 0;
} /* check_exit */


/*
 * Function name:        climb_stairs
 * Description  :        Let players climb the stairs
 * Arguments    :        What the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [dark] 'stair' / 'stairs' / 'stairway'"))
    {
        notify_fail("Do you want to climb down the stairs perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("Normally, we would move the player 'down' here using"
          + " command(). Since you're a wizard, that won't work. You can"
          + " simply type <down> manually to use the stairs.\n");
        return 0;
    }

    this_player()->command("$d");
    return 1;
} /* climb_stairs */


/*
 * Function name:        init
 * Description  :        add some actions to the player 
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
} /* init */
