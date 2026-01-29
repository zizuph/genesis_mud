#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/board";

#include <std.h>

#include "/d/Shire/sys/defs.h"

static string gHeader;
static object gWriter;

void
create_board()
{
    set_board_name(BREE_DIR + "guild_board");
    set_num_notes(25);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Nope, you cannot remove that note.\n");
    ::create_board();
}

public int
allow_remove()
{
    if (this_player()->query_guild_name_occ() == "Rangers of the North")
        return 1;
    return 0;
}

int
post_anon_note(string txt)
{
    if (!strlen(txt))
    {
        notify_fail("Note aborted.\n");
        return 0;
    }
    gWriter->catch_msg("You finish your note, signing it with your "
      + "nickname, " + gWriter->query_ranger_name() + ".\n");
    FIXEUID;
    create_note(gHeader, gWriter->query_ranger_name(), txt);
    gWriter = 0;
    gHeader = "";
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
    if (strlen(str) < 10)
    {
        notify_fail("The title must be at least 10"
          + " characters long.\n");
        return 0;
    }
    if (strlen(str) > 41)
    {
        notify_fail("The title cannot be longer than 41"
          + " characters long.\n");
        return 0;
    }
    gHeader = str;
    gWriter = TP;
    clone_object(EDITOR_OBJECT)->edit("post_anon_note");
    return 1;
}

void
init()
{
    ::init();
    add_action(anon_post, "anote");
    if (objectp(gWriter))
    {
        if (environment(gWriter) != TO)
        {
            gHeader = "";
            gWriter = 0;
        }
    }
}
