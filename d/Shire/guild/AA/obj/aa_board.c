

#include "../guild.h"

inherit "/d/Shire/std/board";

#define BOARD_NAME  (AA_DIR+"boards/aa_board_chapel")


/*
 * Function name: create_board
 * Description  : Since create_object() is nomasked, you must redefine this
 *                function in order to create your own board.
 */
void
create_board()
{
    set_board_name(BOARD_NAME);
    set_remove_str("You are not able to delete any messages.\n");
    set_num_notes(30);
}


/*
 * Function name: allow_remove
 * Description  : This function checks whether this_player() is allowed
 *                to remove notes from this board. If you print an error
 *                message on failure, please check whether this_player()
 *                is in the environment of the board. This function works
 *                independant of the set_remove_rank function.
 * Arguments    : int note - the optional number of the note to be removed.
 *                    When 0, just general access is meant.
 * Returns      : int - true if the player is allowed to remove notes.
 */
public varargs int
allow_remove(int note)
{
    if (AA_COUNCIL_OBJ->is_council(TP->query_real_name()))
    {
        return 1;
    }
    if (AA_RANKS_OBJ->lieut_cap(TP->query_real_name()))
    {
        return 1;
    }
    return 0;
}

