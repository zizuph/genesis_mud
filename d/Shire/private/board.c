inherit "/std/board";

#include <std.h>

#define ME_DOMAINS   ({"Gondor", "Shire"})
#define TRUSTED      ({"igneous"})
#define TP           this_player()

void
create_board()
{
    set_board_name("/d/Shire/private/boards/me_private");
    set_num_notes(25);
    set_remove_str("The note sticks to the board.");
    add_name("_ME_private_board");
}

nomask int
block_check()
{
    if (SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_ARCH)
	return 0;
    if (member_array(SECURITY->query_wiz_dom(TP->query_real_name()), 
	ME_DOMAINS) != -1)
	return 0;
    if (member_array(TP->query_real_name(), TRUSTED) != -1)
	return 0;

    return 1;
}

nomask int
allow_remove()
{
    if (block_check())
	return 0;

    return 1;
}

nomask int 
block_reader()
{
    return block_check();
}

nomask int
block_writer()
{
    return block_check();
}
