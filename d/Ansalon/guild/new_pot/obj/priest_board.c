#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name("/d/Ansalon/guild/pot/log/board/priests");
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);

    set_name(({"bundle", "bundle of scrolls"}));
    set_short("bundle of scrolls");
    set_long("A bundle of scrolls and other assorted notes. " +
        "Some still are possible to write on.\n");

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1000);
    remove_prop(OBJ_M_NO_GET);
}

void
reset_board()
{
    /* We don't want the silly gnome coming. */
}

int
deny_access()
{
    string dom;

    if (TP->query_guild_name_occ() == GUILD_NAME &&
        TP->query_priest_level() >= GUILD_LEVEL_PRIEST)
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
