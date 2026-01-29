#pragma save_binary

inherit "/std/board";

#include "/d/Gondor/defs.h"
#include <std.h>

void
create_board()
{
  set_board_name(BOARD_DIR + "me_idea_board");
  set_num_notes(30);
  set_silent(0);
  set_show_lvl(1);
  set_remove_rank(WIZ_NORMAL);
  set_remove_str("Nope, you cannot remove that note.");
}

varargs int
allow_remove()
{
    string name = this_interactive()->query_real_name();

    if ((SECURITY->query_wiz_rank(name) >= WIZ_ARCH) ||
	(member_array(SECURITY->query_wiz_dom(name),
	    ({ "Gondor", "Mordor", "Shire" }) ) >= 0))
    {
	return 1;
    }

    /* test for present added by Mrpr for use with his soul, Mercade */
    if (present(this_interactive(), environment(this_object())))
	write("Only wizards of Middle Earth are allowed to handle this board.\n");
    return 0;
}

