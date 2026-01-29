#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit DA_BOARD;

void
create_board()
{
    setuid();
    seteuid(getuid());
    set_short("notice board");
    set_long("This notice board has been posted on a tall " +
      "blackened post, and stands in the middle of Sanction's " +
      "marshalling yard.\n");
    set_board_name(NORMAL_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}

int
block_writer()
{
    if (MANAGER->query_punishment(TP, PUN_NOBOARD))
    {
	write("You have been punished by restricted board access.\n");
	return 1;
    }
    return 0;
}
