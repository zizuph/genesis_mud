/*
 *  /d/Sparkle/guilds/new_merc/doors/good_e.c
 *
 *  This is the east side of the door to the good bunk and droproom
 *  in the Mercenary Guildhall.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/door";

#include "../merc_defs.h"

/* Prototypes */
public void        create_door();


/*
 * Function name:        create_door
 * Description  :        constructor for the door object
 */
public void
create_door()
{
    ::create_door();

    set_door_id("good_start");
    set_pass_command( ({ "w" ,"west" }) );
    set_door_name( ({ "door", "polished door", "beautiful door",
                      "doorway", "polished doorway", "beautiful doorway",
                      "very beautiful door", "very beautiful polished door",
                      "very beautiful doorway",
                      "very beautiful polished doorway",
                      "west door", "western door",
                      "door to the west" }) );

    set_open_desc("There is an open polished door leading west.\n");
    set_closed_desc("There is a closed polished door leading west.\n");

    set_fail_pass("The polished door is closed.\n");
    set_open_mess( ({ "opens the polished door.\n",
                      "The polished door closes.\n" }) );
    set_close_mess( ({ "closes the polished door.\n",
                       "The polished door closes.\n" }) );

    set_door_desc("A beautiful polished door is set into the west wall"
      + " of this corridor. The look of the door communicates a"
      + " sense of well-being and tranquility.\n");

    set_other_room(ROOM_DIR + "good_start");

    set_open(0);
    set_locked(0);
} /* create_door */


/*
 * Function name: pass_door
 * Description:   Pass the door. Wizards can pass the door by giving the
 *                command with an exclamation point.
 * Arguments:     arg - arguments given
 *
 * I mask this to include a check for whether or not the player is a
 * Mercenary.
 */
int
pass_door(string arg)
{
    if (IS_MERC(this_player()) ||
        this_player()->query_wiz_level())
    {
        if (this_player()->query_wiz_level())
        {
            write("Normally, we'd try to block a non-mercenary, but since"
              + " you are a wizard, go right ahead!\n");
        }

        return ::pass_door(arg);
    }

    if (!this_object()->query_open())
    {
        write("The polished door is closed.\n");
        return 1;
    }

    if (this_player()->query_invis())
    {
        write("A noble-looking Mercenary suddenly looms before you"
          + " in the doorway. Though she doesn't see you, she leans"
          + " against the doorframe, peering suspiciously into the"
          + " hall.\n");
        write("You are unable to proceed that direction.\n");
        return 1;
    }

    write("As you approach the door, a stern looking Mercenary suddenly"
      + " appears in the opening and says: You do not belong in this"
      + " lodge, stranger. You may come no further.\n");
    write("You are prevented from going further.\n");

    return 1;
} /* pass_door */