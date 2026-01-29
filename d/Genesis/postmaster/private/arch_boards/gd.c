inherit "/std/board";

#include <mail.h>
#include <std.h>

string *alias_list;

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/gd");
    set_num_notes(50);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only a member of the Arch council can do that.");

    setuid();
    seteuid(getuid());
    alias_list = SECURITY->query_teal_list("aog");
}

int
block_reader()
{
    if (member_array(geteuid(this_interactive()), alias_list) < 0)
    {
	if (present(this_interactive(), environment(this_object())))
	{
	    write("Only the AoG-team can handle this board.\n");
	}
	return 1;
    }
    return 0;
}

int
block_writer()
{
    return block_reader();
}

int
allow_remove()
{
    return (member_array(geteuid(this_interactive()), alias_list) != -1);
}
