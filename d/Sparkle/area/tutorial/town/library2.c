/*
 *  /d/Sparkle/area/tutorial/town/library2.c
 *
 *  This is the annex to the Greenhollow Library. Here, players who
 *  skipped the pre-creation tutorial can review what they have missed.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2011 to incorporate Review concept (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>
#include <stdproperties.h>


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public string      describe();
public int         begin_review(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the annex of the Greenhollow Library");
    set_long("This is the Annex to the Greenhollow Library."
      + " Here, you can review the early aspects of gameplay that"
      + " you learned by entering the portal when you first"
      + " arrived in these realms. You can <read sign> here"
      + " to learn about the review process.\n\n");

    add_item( ({ "library", "here", "building", "area",
                 "greenhollow library", "library of greenhollow",
                 "annex", "annex of the library" }), long);
    add_item( ({ "sign" }), describe);
    add_cmd_item( ({ "sign" }),
                  ({ "read" }), describe);

    add_indoor_items();

    prevent_attacks();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("library", "south");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
    add_action(begin_review, "begin");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Well, unless you skipped the tutorial, you probably"
      + " don't need to worry about this information. But if you are"
      + " looking for chapters, this is the place to add those chapters"
      + " to your tutorial journal.\n");
 
    return 1;
} /* hint */


/*
 * Function name:        describe
 * Description  :        provide the long description for the sign
 * Returns      :        string - the room description
 */
public string
describe()
{
    return read_file(TEXT_DIR + "review", 0);
} /* describe */


/* Function name:        begin_review
 * Description  :        allow players to begin the review
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
begin_review(string arg)
{
    if (arg != "review")
    {
        write("Do you wish to <begin review>?\n");
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " disappears in a flash of light!\n", this_player());
    write("\nLight flashes, and you feel yourself magically transported!\n\n");

    this_player()->move_living("M", REVIEW_DIR + "1", 1);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " appears in a flash of light!\n", this_player());

    return 1;
} /* begin_review */