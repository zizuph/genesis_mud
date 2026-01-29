#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    set_long("This notice board is used by dwarves who " +
      "have travelled to Iron Delving and wish to leave a message " +
      "for their brethren here.\n");
    set_board_name(CLAN_APP_BOARD);
    set_num_notes(20);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}

int
allow_remove()
{
    /* Allow Elders and Thane to remove */
    if(TP->test_bit("Ansalon",3,3) && TP->test_bit("Ansalon",3,4))
	return 0;
    if(TP->test_bit("Ansalon",3,3) || TP->test_bit("Ansalon",3,4))
	return 1;
    else
	return 0;
}

