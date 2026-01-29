/*
 * File:     board_link.c
 * Created:  Cirion, 1998.08.30
 * Purpose:  This board serves as a link between the Outside
 *           World and the Elders. Elders posting on the
 *           board will be given the name "Elders" in order
 *           to stay anonymous. The board is cloned in two
 *           places, up from the post office and
 *           west of the council room.
 *
 * Revisions:
 *   Lilith, Jun 2004: implemented.
 *   Lucius, May 2016: Added writer restrictions.
 */
#pragma strict_types

inherit "/std/board";
#include <std.h>

#include "../defs.h"

public void 
create_board()
{
    set_board_name(BOARDS + "board_link");
    set_num_notes(66);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_remove_str("Only the Elders may do so.\n");
    set_no_show_composite(1);

    set_name(({"link", "Link"}));

    set_long("It is the Link, that which permits you to "+
      "communicate with the Elders. Its surface is "+
      "shadowed, thus concealing in mystery the messages "+
      "of those who came here before you.\nJust above it, "+
      "inscribed upon the stone, are the following words:\n\n"+
      "  Warriors may write to Us, but they may not read.\n\n"+
      "  Warriors may remove, but only what they have written.\n\n"+
      "  Posts may be answered by the Voice, by the "+
      "Shadows, or through a vision, as the Elders decree.\n\n");
    add_item(({"words" }),
      "  Warriors may write to Us, but they may not read.\n\n"+
      "  Warriors may remove, but only what they have written.\n\n"+
      "  Past may be answered by the Voice, by the "+
      "Shadows, or through a vision, as the Elders decree.\n\n");
}

/*
 * Function name: block_reader
 * Description  : If this_player() is not allowed to read notes of other
 *                people on this board, this function should be used to
 *                block access. If you print an error message on failure,
 *                please check whether this_player() is in the environment
 *                of the board.
 *                Redefine this function in your board code. It gets called
 *                automatically when someone tries to read.
 * Arguments      int note - Optional argument with the number of the note
 *                    the person wants to read. When 0, basic access to the
 *                    board.
 * Returns      : int - true if the player is NOT allowed to read.
 */
public varargs int
block_reader(int note = 0)
{
    object tp = this_player();
    string name = tp->query_real_name();

    /* The only mortals who can read this board are the Elders */
    if (!IS_ELDER(tp) &&
	SECURITY->query_wiz_rank(name) < WIZ_ARCH &&
	SECURITY->query_wiz_dom(name) != "Avenir")
    {
	if (environment(tp) == environment(TO))
	{
	    write("What is written upon this board is for the eyes "+
	      "of the Elders only.\n");
	}
	return 1;
    }
    return 0;
}

/*
 * Function name: block_writer
 * Description  : If this_player() is not allowed to write notes on this
 *                board, this function should be used to block access.
 *                If you print an error message on failure, please check
 *                whether this_player() is in the environment of the board.
 *                Redefine this function in your board code. It gets called
 *                automatically when someone tries to write.
 * Returns      : int 1/0 - true if the player is NOT allowed to write.
 */
public int
block_writer()
{
    if (this_player()->query_union_sphere() == SPH_TRAINING)
    {
	if (environment(this_player()) == environment(this_object()))
	    write("Only those who are Named may write upon the link.\n");
	return 1;
    }

    if (!IS_MEMBER(this_player()))
    {
	if (environment(this_player()) == environment(this_object()))
	{
	    write("This forum is not for you, find another way to "+
	      "communicate.\n");
	}
	return 1;
    }

    return 0;
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
    return 0;
}
