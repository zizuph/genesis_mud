#pragma strict_types
#pragma save_binary

#include "../guild.h"
#include "defs.h"
#include <stdproperties.h>

inherit TRAVELLERS_STD_DIR + "room_base";
inherit "/d/Earthsea/lib/library";

#define IS_ADMIN(tp) ( \
    COUNCIL_MEMBER(tp->query_real_name()) || EARTHSEA_WIZ(tp) || \
       (SECURITY->query_wiz_rank(tp->query_real_name()) >= WIZ_ARCH) \
)

public int
library_exit_block()
{
    if(::library_exit_block())
    {
        write("You cannot leave with a library book!\n");
        return 1;
    }

    return 0;
}

public void
create_traveller_room()
{
    add_prop(ROOM_S_MAP_FILE, "trav_map.txt");
    set_short("Travellers library");
    set_long("This is the Traveller library. In this room many " +
           "stories have been written and told. The room has " +
           "many shelves, some empty, some full. There is an " +
           "old human sitting at a table which you assume to " +
           "be the librarian. Against the wall lies a sign " +
           "explaining how to use the library.\n");
    add_item("librarian", "He looks very nervous.\n");
    add_item("desk",
        "The desk is used by the librarian to sort returned books.\n");
    add_exit("balcony", "north", library_exit_block);
    add_item("sign", library_help());
    add_cmd_item("sign", "read", library_help());
    set_book_directory("/d/Earthsea/travellers/log/books/");
    set_default_directory("general");
    set_approval_directory("approval");
    set_removal_directory("removed");
    create_library();
}

public void
init()
{
    ::init();
    init_library();
}

public int
library_admin_access()
{
    if(IS_ADMIN(this_player()))
    {
        return 1;
    }

    return 0;
}

public int
library_write_access()
{
    if(IS_ADMIN(this_player()))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}
