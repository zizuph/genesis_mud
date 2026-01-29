/*
 *  /d/Sparkle/guilds/new_merc/doors/evil_e.c
 *
 *  This is the east side of the door to the evil bunk and droproom
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

    set_door_id("evil_start");
    set_pass_command( ({ "w" ,"west" }) );
    set_door_name( ({ "door", "ash-grey door", "stained door",
                      "doorway", "ash-grey doorway", "stained doorway",
                      "very stained door", "very stained ash-grey door",
                      "very stained doorway",
                      "very stained ash-grey doorway",
                      "west door", "western door",
                      "door to the west" }) );

    set_open_desc("There is an open ash-grey door leading west.\n");
    set_closed_desc("There is a closed ash-grey door leading west.\n");

    set_fail_pass("The ash-grey door is closed.\n");
    set_open_mess( ({ "opens the ash-grey door.\n",
                      "The ash-grey door closes.\n" }) );
    set_close_mess( ({ "closes the ash-grey door.\n",
                       "The ash-grey door closes.\n" }) );

    set_door_desc("A stained ash-grey door is set into the west wall"
      + " of this corridor. Something about this door seems to"
      + " communicate malevolence.\n");

    set_other_room(ROOM_DIR + "evil_start");

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
        write("The ash-grey door is closed.\n");
        return 1;
    }

    if (this_player()->query_invis())
    {
        write("A gruff-looking Mercenary suddenly looms before you"
          + " in the doorway. Though he doesn't see you, he leans"
          + " against the doorframe, glaring into the hall.\n");
        write("You are unable to proceed that direction.\n");
        return 1;
    }

    write("As you approach the door, a menacing looking Mercenary suddenly"
      + " appears in the opening and says: Who the hell are you? Get"
      + " out of here - NOW!\n");
    write("You are prevented from going further.\n");

    return 1;
} /* pass_door */