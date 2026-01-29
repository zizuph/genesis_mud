#include "/d/Emerald/common/guild/vamp/guild.h"

inherit "/d/Emerald/lib/library";
inherit VAMP_ROOM_DIR + "vamp_room";

#include "/d/Emerald/kroad/graveyard/church/defs.h"
#include <stdproperties.h>
#include <files.h>
#include <std.h>

static string *library_admin = ({});

void
create_board()
{
    object b;

    setuid();
    seteuid(getuid());

    if (b = clone_object(BOARD_OBJECT))
    {
        b->set_board_name(CHURCH_DIR + "board_save");
	b->set_num_notes(50);
        b->set_silent(1);
        b->set_no_report(1);
        b->move(this_object(), 1);
    }
}

public int
block_north()
{
    if ((this_player()->query_vamp_coven() != "Emerald") &&
        !this_player()->query_wiz_level() &&
        !wildmatch("jr*", this_player()->query_real_name()))
    {
        write("Some force prevents you from entering!\n");
        return 1;
    }

    return library_exit_block();
}

public string
shelves_desc()
{
    if (m_sizeof(book_map))
    {
        return "While many of the shelves are empty, a few books look " +
            "to have been added recently, and";
    }

    return "While the shelves are empty,";
}

void create_vamp_room()
{
    set_short("Church Study");
    add_exit("under_church04", "north", library_exit_block);
    add_exit("study", "south", library_exit_block);
 
    add_item("shelves", "The wooden shelves reach up to the ceiling " +
        "on each wall.  Most of the books have apparently been removed, " +
        "but a few remain.\n");
    add_item("books", "There are a few books on the shelves.  They look " +
        "rather new.\n");

    set_book_directory(CHURCH_DIR + "books/");
    set_book_approval_directory(CHURCH_DIR + "books/approval/");
    set_book_removal_directory(CHURCH_DIR + "books/removed/");

    create_library();

    set_long("   A small library.  @@shelves_desc@@ " +
        "there are plenty of supplies for creating new texts.  " +
        "There is a scroll affixed to the wall giving instructions " +
        "on using the study.\n");
 

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
