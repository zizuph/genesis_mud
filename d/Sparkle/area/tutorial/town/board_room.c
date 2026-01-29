/*
 *  /d/Sparkle/area/tutorial/town/board_room.c
 *
 *  This is the Town Hall of Greenhollow. The bulletin board for the
 *  town is here, along with a tutorial about how to use boards.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    28  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public object      make_board();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    object   board;

    set_short("the Greenhollow Town Hall");
    set_long("This is the Greenhollow Town Hall. Here people come to"
      + " read and post notes on the Bulletin Board which is an open"
      + " public discussion forum. Read the tutorial sign for information"
      + " on boards. You can access the common board by typing <common>"
      + " here.\n\n");

    add_item( ({ "hall", "town hall", "here", "building", "area",
                 "greenhollow town hall",
                 "town hall of greenhollow" }), long);
    add_item( ({ "common", "common board", }),
        "The Common Board is a board where important announcements are"
      + " posted for the entire Genesis community. To reach it, just"
      + " type <common>.\n");

    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_5", "west");
    add_exit("common_board_room", "common");

    if (!(board = make_board()))
    {
        add_my_desc("ERROR: Board not created. Please mail Gorboth.\n");
    }
} /* create_greenhollow */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
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
    write("A hint? Sure ... If you are having trouble reading the board,"
      + " try <exa board> to get a list of the notes. Then <read #>"
      + " where the # is the number of the note you want to read.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        make_board
 * Description  :        set up the bulletin board
 * Returns      :        the board object - success,
 *                       0                - failure, board not created.
 */
public object
make_board()
{
    object  bboard;

    bboard = clone_object("/std/board");
    if (bboard)
    {
        bboard->set_board_name(TUTORIAL_DIR + "board_save");
        bboard->set_num_notes(25);         /* Number of notes         */
        bboard->set_anonymous(1);          /* You may write anonymous */
        bboard->set_silent(0);             /* Make noise when reading */
        bboard->set_show_lvl(0);           /* Full wizards or higher  */
        bboard->set_remove_lvl(15);        /* Full wizards or higher  */
        bboard->set_remove_str("Only full wizards can remove notes.");
        bboard->set_use_gedit(0);          /* Don't use that editor */
        bboard->move(this_object());

        return bboard;
    }
    return 0;
} /* make_board */
