/* Added access for AoP. - Wisk 6/15/97
*/

inherit "/std/board";

#include <std.h>
#include <mail.h>

string *alias_list;


void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/player");
    set_num_notes(100);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only an Archwizard or Keeper can do that.");

    setuid();
    seteuid(getuid());
    alias_list = SECURITY->query_team_list("aop"); 
}

int
block_reader()
{
    if(member_array(geteuid(this_interactive()), alias_list) != -1)
	return 0;
    return (SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD);
}

int block_writer() { return 1; }
