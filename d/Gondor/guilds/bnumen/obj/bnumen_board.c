#pragma save_binary

inherit "/std/board";

#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

void
create_board()
{
    string  name;

    name = BOARD_DIR + "bnumen_board";
    if (file_size(name) != -2)
        mkdir(name);
    set_board_name(name);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("bulletin board of the Houses of the Black Numenoreans");
    set_remove_str("A magical force prevents you from removing "+
        "the note.\n");
}

varargs int
block_writer()
{
    object  tp = TP;

    if ((tp->query_wiz_level()) && (SECURITY->query_wiz_dom(tp->query_real_name()) == "Gondor"))
        return 0;

    if (tp->query_race() == "human")
        return 0;

    if (present(this_interactive(), ENV(TO)))
        write("Only humans may post notes on this board!\n");

    return 1;
}

int
allow_remove()
{
    object  tp = TP;

    if ((tp->query_wiz_level()) && (SECURITY->query_wiz_dom(tp->query_real_name()) == "Gondor"))
        return 1;

    if (tp->query_bnumen_level() == DL_LORD)
        return 1;

    if (present(this_interactive(), ENV(TO)))
        write("Only Lords and Ladies of the Houses of the Black Numenoreans may remove notes!\n");

    return 0;
}

