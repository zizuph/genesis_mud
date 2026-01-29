#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name("/d/Ansalon/guild/pot/log/board/pot");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
    set_long("This is the bulletin board for the Priests of Takhisis " +
        "guild.\n");
    set_adj("large");
    set_no_show_composite(1);
}

int
deny_access()
{
    string dom;

    if (TP->query_guild_name_occ() == GUILD_NAME)
        return 0;

    dom = SECURITY->query_wiz_dom(TP->query_real_name());
    if (dom == "ansalon")
        return 0;

    return 1;
}

int
block_reader(int note = 0)
{
    return deny_access();
}

int
block_writer()
{
    return deny_access();
}
