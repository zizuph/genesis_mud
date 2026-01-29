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
    set_long("This is the notice board used by members of " +
      "the Red Dragonarmy.\n");
    set_board_name(RED_DARMY_BOARD);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}

int deny_access()
{
    if ((can_access() && allow_color("red")) || allow_wiz())
	return 0;
    return 1;
}

int
block_reader(int note = 0)
{
    return (deny_access());
}

int
block_writer()
{
    if (deny_access())
	return 1;
    if (MANAGER->query_punishment(TP, PUN_NOBOARD))
    {
	write("You have been punished by restricted board access.\n");
	return 1;
    }
    return 0;
}
