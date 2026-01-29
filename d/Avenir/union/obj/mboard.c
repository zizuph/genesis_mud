/* The Union board
 *    Cirion, 032996
 *
 * Revisions:
 * 	????,   Jul 1997: Allow Elders of the Union to post anonymously "Elders"
 *	Manat,  Jan 2001: Changed the checks for read/write functions
 *	Lucius, Aug 2017: Removed 'eldernote' as all Warriors may now access
 *			  the board. No need for anonymous postings here.
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/board";

#include <std.h>
#include <stdproperties.h>


public void
create_board(void)
{
    set_board_name(BOARDS+"mboard");
    set_num_notes(47);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_remove_str("You are not permitted.\n");
    set_no_show_composite(1);
    set_name("book");
    add_name("book of mists");

    set_long("A very large book standing on a pedestal, with "+
      "thick vellum pages the length of your arm. Each page "+
      "is a self-contained message, written by those who "+
      "concern themselves with the mentoring of novices.\n"+
      "This is known as the Book of Mists.\n");
}

public int
block_reader(void)
{
    string name = TP->query_real_name();

    if (!IS_MEMBER(TP) &&
	SECURITY->query_wiz_rank(name) < WIZ_MAGE &&
	SECURITY->query_wiz_dom(name) != "Avenir")
    {
	if (environment(TP) == environment(TO))
	    write("You are not permitted to view this board.\n");
	return 1;
    }

    return 0;
}

public int
block_writer(void)
{
    return block_reader();
}

public int
allow_remove(void)
{
    if (IS_ELDER(TP))
    {
	if (present(TP, ENV(TO)))
	    write("Since you are an Elder, you may remove the note.\n");
	return 1;
    }

    if (SECURITY->query_wiz_dom(TP->query_real_name()) == "Avenir")
	return 1;

    return 0;
}
