
/* The AoB team discussion board */

inherit "/std/board";

#include <mail.h>
#include <std.h>

string *alias_list;

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/aob_board");
    set_num_notes(100);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only a member of the Arch council can do that.");

    setuid();
    seteuid(getuid());
    alias_list = SECURITY->query_team_list("aob");
}

int
block_reader()
{
    if ( "/secure/master"->query_wiz_level( this_player()->query_name() ) > 39 )
    {
        if (present(this_interactive(), environment(this_object())))
        {
            write("\n\n\tArches and Keepers are welcome to participate in the AoB debate.\n\n");
        }

        return 0;
    }

    if (member_array(geteuid(this_interactive()), alias_list) < 0)
    {
        if (present(this_interactive(), environment(this_object())))
        {
            write("Only the AoB-team can handle this board.\n");
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
