inherit "/std/board";

#include <std.h>
#include <mail.h>

string *alias_list;

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/wizapp");
    set_num_notes(100);
    set_keep_discarded(1);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only a member of the Arch council can do that.");

    setuid(); 
    seteuid(getuid()); 
    alias_list = (SECURITY->query_team_list("aop") +
      SECURITY->query_team_list("aod")); 
}

int
block_writer()
{
    int rank = SECURITY->query_wiz_rank(geteuid(this_interactive()));

    /* Lords have access. */
    if (rank >= WIZ_STEWARD)
    {
	return 0;
    }

    /* Aop team can write here */  
    if (member_array(geteuid(this_interactive()), alias_list) >= 0)
	return 0;

    /* Mortals have access if they have an average stat > 60 */
    if ((rank == WIZ_MORTAL) &&
      (this_interactive()->query_average_stat() > 60))
    {
	return 0;
    }

    if (present(this_interactive(), environment()))
    {
	if (this_interactive()->query_wiz_level())
	{
	    write("Only a mortal player applying for wizardhood may write " +
	      "here, along with the Lieges and the members of the " +
	      "administration.\n");
	}
	else
	{
	    write("Only a mortal player applying for wizardhood may write " +
	      "here, along with the Lieges and the members of the " +
	      "administration.\nIf you may not write on this board, then " +
	      "you do not have enough experience yet. To be a wizard in " +
	      "Genesis, you need to know the game and the atmosphere in " +
	      "order to know what would fit in and how. Explore the lands " +
	      "futher and then come back to try again.\n");
	}
    }
    return 1;
}

int
block_reader()
{
    /* Aop team can read here */ 
    if (member_array(geteuid(this_interactive()), alias_list) >= 0)
	return 0;

    if (SECURITY->query_wiz_rank(geteuid(this_interactive())) 
      >= WIZ_STEWARD)
	return 0;

    return 1;
}

