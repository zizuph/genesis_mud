/*
 * /d/Genesis/wiz/ideaboard.c
 *
 * This board carries a little warning to people posting here, as it turns out that
 * many wizards fail to make proper distinction between a board for ideas and a board
 * for discussions.
 */

inherit "/std/board";

#include <std.h>

/*
 * Function name: block_writer
 * Description  : We use this function to send a little message to the wizard who is
 *                about to write on this board. It appears that wizards have a problem
 *                with writing ideas on the idea board and discussions on the discuss
 *                board.
 * Returns      : int 0 - always, we only want to print the message.
 */
void
block_writer()
{
    /* We do not check for the presence of the player in this room as we also want
     * to trigger on remote posting via MBS. We use this construct to see if we
     * are called from new_msg() as that is the function that is invoked when a new
     * note is posted. We must do this because we do not want to spam people who
     * just use MBS to see which access they have to which board.
     */
    if (calling_function(-1) == "new_msg")
    {
        write("\nPlease note that this board is only meant for ideas!\nFor " +
            "follow up and further discussion, please use the " +
            "\"discuss\" board!\n\n");
    }

    /* Don't block access. Just deliver the message. */
    return 0;
}

void
create_board()
{
    set_board_name("/d/Genesis/wiz/boards/ideas");
    set_num_notes(50);
    set_silent(1);  /* Keep the mud tidy RW */
    set_show_lvl(1); /* Wizards may see levels, Mercade. */
    set_keep_discarded(0);
}
