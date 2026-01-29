/*
 *  /d/Sparkle/guilds/new_merc/obj/merc_board.c
 *
 *  This is the bulletin board for the Mercenary Guildhall.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/board";

/* Prototypes */
public void        create_board();

/*
 * Function name:        create_board
 * Description  :        set up the board
 */
public void
create_board()
{
    set_board_name("/d/Sparkle/boards/new_merc_board");
    set_num_notes(50);         /* Number of notes         */
    set_silent(0);             /* Make noise when reading */
    set_show_lvl(0);           /* Full wizards or higher  */
    set_keep_discarded(1);     /* Posterity!              */
} /* create_board */
