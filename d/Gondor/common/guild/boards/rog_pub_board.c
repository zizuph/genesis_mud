#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/board";
inherit "/d/Gondor/common/lib/binbit";

#include <std.h>

#include "/d/Gondor/defs.h"

static string gHeader;
static object gWriter;


void
create_board()
{
    set_board_name(BOARD_DIR + "rangersboard");
    set_num_notes(40);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Nope, you cannot remove that note.\n");
}

public int
allow_remove()
{
    if (query_bin_bits(1, 18, 2, this_player()) != 2)
        return 0;
    return 1;
}

int
post_anon_note(string txt)
{
    if (!strlen(txt))
    {
        notify_fail("Note aborted.\n");
        return 0;
    }
    write("You finish your note, signing it with your "
      + "nickname, " + TP->query_ranger_name() + ".\n");
    create_note(gHeader, TP->query_ranger_name(), txt);
    gWriter = 0;
    gHeader = "";
    return 1;
}

int
anon_post(string str)
{
    if (TP->query_guild_name_occ() != "Rangers of the North")
        return 0;
    if (objectp(gWriter) && gWriter != TP)
    {
        notify_fail("Someone else is already writing.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("What is the title of your note?\n");
        return 0;
    }
    gHeader = str;
    gWriter = TP;
    clone_object(EDITOR_OBJECT)->edit("post_anon_note");
    return 1;
}

