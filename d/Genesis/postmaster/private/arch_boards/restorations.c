inherit "/std/board";

#include <mail.h>
#include <std.h>

string *alias_list;

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/restorations");
    set_num_notes(300);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("Only a member of the Arch council can do that.");

    setuid();
    seteuid(getuid());
    alias_list = SECURITY->query_team_list("aop");
}

int
block_reader()
{
    if ((SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD) &&
	(member_array(this_interactive()->query_real_name(), alias_list) < 0))
    {
	if (present(this_interactive(), environment(this_object())))
	{
	    write("You cannot read here.\n");
	}
	return 1;
    }
    return 0;
}

int
allow_remove()
{
    return (member_array(geteuid(this_interactive()), alias_list) != -1);
}
