/*
 *  /d/Genesis/wiz/deleted.c
 *
 *  This room houses the board which will act as a forum to announce and
 *  discuss players who have been deleted and now have applied to be
 *  restored.
 *
 *  Created Novermber 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/room";

/* prototypes */
public void        create_room();
public object      make_board();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    object   board;

    set_short("the deleted players restoration board room");
    set_long("This room has no purpose other than to house the bulletin"
      + " board that is used for listing applicants for restoration from"
      + " a deleted state. The board is also used to discuss said"
      + " applicants.\n\n");

    if (!(board = make_board()))
    {
        add_my_desc("ERROR: Board not created. Please mail Gorboth.\n");
    }
} /* create_room */


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
        bboard->set_board_name("/d/Genesis/wiz/boards/deleted");
        bboard->set_num_notes(99);         /* Number of notes         */
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