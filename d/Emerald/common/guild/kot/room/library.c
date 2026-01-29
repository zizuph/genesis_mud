inherit "/lib/library";
inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "../guild.h"

#include <stdproperties.h>
#include <files.h>
#include <std.h>

public int library_exit_block();

void
create_room()
{
    set_short("Library");
    set_long("   A well appointed, private library for the " +
        "Keepers of Telberin.  The shelves, full of ancient books, " +
        "cover each wall and rise all the way to the ceiling.\n" +
        "There is a scroll affixed to the wall giving instructions " +
        "on using the library.\n");
 
    add_item("shelves", "The wooden shelves reach up to the ceiling " +
        "on each wall.  Most of the books appear truly ancient, and " +
        "you resist the urge to remove them from the shelves for fear " +
        "of destroying them.\n");

    add_item("books", "Most of the books appear truly ancient.  You " +
        "resist the desire to peruse their pages for fear of destroying " +
        "the delicate pages.  Among the old books, though, there are " +
        "several newer looking volumes.\n");

    add_exit("kot_common", "south", library_exit_block);

    set_book_directory(KOT_BOOK_DIR);
    set_book_approval_directory(KOT_BOOK_DIR + "approval/");
    set_book_removal_directory(KOT_BOOK_DIR + "removed/");

    add_prop(ROOM_I_INSIDE, 1);

    create_library();

    add_item(({"scroll", "instructions", }), library_help());
    add_cmd_item(({"scroll", "instructions", }), "read", library_help());
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
    if (this_player()->query_kot_council_member() ||
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
