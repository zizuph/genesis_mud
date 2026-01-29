#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";
inherit "/lib/library";

#include "/d/Earthsea/sys/macros.h"
#include <std.h>

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

void
create_traveller_room()
{
    set_short("Traveller library");
    set_long("This is the Traveller library. In this room many "+
           "stories have been written and told. The room has "+
           "many shelves, some empty, some full. There is an "+
           "old human sitting at a table which you assume to "+
           "be the librarian. Against the wall lies a sign "+
           "explaining how to use the library.\n");

    add_item("librarian","He looks very nervous.\n");
    add_item("desk","The desk is used by the librarian to sort returned books.\n");

    add_exit("balcony", "north", library_exit_block);

    set_borrow_required(1);
    set_book_directory(TRAVELLERS_BOOK_DIR);
    set_book_approval_directory(TRAVELLERS_BOOK_DIR + "approval/");
    set_book_removal_directory(TRAVELLERS_BOOK_DIR + "removed/");
    add_book_shelf(({ "general", "maps" }));
    create_library();

    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());
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
    if (COUNCIL_MEMBER(this_player()->query_real_name()) ||
        EARTHSEA_WIZ(this_player()) ||
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
    if (IS_MEMBER(this_player()) || EARTHSEA_WIZ(this_player()) ||
       (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 
       WIZ_ARCH))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}
