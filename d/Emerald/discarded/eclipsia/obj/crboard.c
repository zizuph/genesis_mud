/* This board is for all who pass through Coral Requiem */

inherit "std/board";
#include "/d/Emerald/defs.h"
#include <std.h>

void
create_board()
{
    set_board_name("coral_requiem_board");
    set_num_notes(25);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Sorry, you can't do that");
    set_short("Board of Coral Requiem");
    set_long("Made of shell and coral, this board could last " +
        "forever. Merfolk make announcements to the community on " +
        "this board. This is also the place where visitors leave " +
        "their notes.\n");
}

