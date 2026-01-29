/*
 * BOARD.c
 * Keepers of Telberin Bulletin Board
 *  - Alaron February 18, 1997
 */

#include <macros.h>
#include "../guild.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    set_name("book");
    set_short("book of notes");

    set_long("   It is a large, leather-bound book. The book is a bound "+
	     "collection of quite a few pages of treated parchment. There "+
	     "are several empty pages at the back of the book. It looks as "+
	     "though people have been writing notes on the pages for "+
	     "others to read.\n\n");

    add_item("pages",
	     "They are carefully treated parchment pages.\n");

    add_cmd_item("pages", ({"turn","read"}),
		 "Perhaps you should try reading the notes individually.\n");

    set_board_name(KOT_LOG_DIR + "board_data");
    set_num_notes(30);
    set_silent(0);
    set_remove_rank(WIZ_LORD);
    set_show_lvl(0);
}

void
post_note_hook(string head)
{
    if (present(this_player(), environment(this_object())))
    {
	write("You carefully return the quill to its jar, having "+
	      "added your note to the book.\n");
	say(QCTNAME(this_player())+
            " carefully returns the quill to its jar, having "+
	    "added a note to the book.\n");
    }
}
