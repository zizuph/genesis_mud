#include "../guild.h"

inherit "/lib/library";
inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <files.h>
#include <std.h>

string *library_admin = ({ "thalamus" });

void create_board()
{
    object b;

    setuid();
    seteuid(getuid());

    if (b = clone_object(BOARD_OBJECT))
    {
        b->set_board_name(VAMP_LOG_DIR + "private_board_save");
        b->set_num_notes(30);
        b->set_silent(1);
        b->move(this_object(), 1);
    }
}

void create_vamp_room()
{
    set_short("Private library");
    set_long("   A small, private library that adjoins the main study " +
        "to the south.  While many of the shelves are " +
        "empty, a few books look to have been added recently, and " +
        "there are plenty of supplies for creating new ones.\n" +
        "There is a scroll affixed to the wall giving instructions " +
        "on using the study.\n");
 
    add_exit("/d/Emerald/mist_tower/tower_library", "south",
        library_exit_block);

    add_item("shelves", "The wooden shelves reach up to the ceiling " +
        "on each wall.  Most of the books have apparently been removed, " +
        "but a few remain.\n");
    add_item("books", "There are a few books on the shelves.  They look " +
        "rather new.\n");

    set_borrow_required(1);
    set_book_directory(VAMP_BOOK_DIR + "/private/");
    set_book_approval_directory(VAMP_BOOK_DIR + "/private/approval/");
    set_book_removal_directory(VAMP_BOOK_DIR + "/private/removed/");

    add_book_shelf(({ "histories", "general", "coven" }));
    set_default_shelf("general");

    create_library();

    add_item(({"scroll", "instructions", }), library_help());
    add_cmd_item(({"scroll", "instructions", }), "read", library_help());

    create_board();
}

void
init()
{
    ::init();
    init_library();
}

public int
library_admin_access()
{
    if ((this_player()->query_vamp_covenmaster() && (this_player()->query_vamp_coven() == "Emerald")) ||
       (member_array(this_player()->query_real_name(), library_admin) >= 0) ||
       EMRLD_WIZ(this_player()) ||
       (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 
       WIZ_ARCH))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}

public int
library_write_access()
{
    if (IS_MEMBER(this_player()) || EMRLD_WIZ(this_player()) ||
       (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 
       WIZ_ARCH))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}

public int
library_exit_block()
{
    if (::library_exit_block())
    {
        write("You cannot leave with a library book!\n");
        return 1;
    }

    return 0;
}
