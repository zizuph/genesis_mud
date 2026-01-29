/*
 * Library of Rivendell
 * Based on /d/Earthsea/travellers/room/library.c
 * -- Finwe, April 2005
 */

#pragma strict_types
#pragma save_binary

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit "/d/Shire/room";
inherit "/d/Earthsea/lib/library";

#define IS_ADMIN(tp) ( \
    IS_SHIRE_WIZARD(tp) || IS_GONDOR_WIZARD(tp) || \
    (SECURITY->query_wiz_rank(tp->query_real_name()) >= WIZ_ARCH) \
)

#define SHELF_TYPE      shelf_types[0]
#define BOOK_ID         (MASTER + "_library_book")

public void
create_room()
{
    set_short("The Library of Imladris");
    set_long("This is the Library of Imladris. Here you will find many " +
        "books that contain collected stories, songs, and knowledge of " +
        "the Elves. The room has many shelves that store the scrolls. " +
        "The library is quiet, and affords a place where you may write " +
        "a book or two. Against a wall hangs a sign.\n");
    
    add_item("desk",
        "The desk is used by the librarian to sort returned books.\n");    
    add_item("shelves",
        "The shelves are sturdy and full of books to read.\n");

    add_item("sign", 
        "Flowing words have been painted onto the sign. " +
        "Perhaps you should read it.\n");
    add_cmd_item("chair", "sit in", 
        "You sit back and relax in one of the most comfortable " +
        "chairs in the room.\n");
    
    add_item(({"lamp","lamps"}),
        "They are attached to the walls and radiate a soft, " +
        "white light throughout the room.\n");
    add_item("ceiling",
        "Large richly carved beams hold up the roof high " +
        "above you.\n");
    add_item(({"walls", "wall"}),
        "The walls are an off-white color and lightly textured. " +
        "Lamps are attached to the walls.\n");
    add_item(({"windows","window"}),
        "The windows are large and equally " +
        "divided vertically into two sections with each " +
        "vertical section divided horizontally into four " +
        "squares. They windows are closed to preserve the " +
        "precious books and manuscripts in here. Large " +
        "curtains cover them.\n");
    add_item("curtains",
        "They are made from a heavy fabric and are closed.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor is made from dark hardwoods and is very " +
        "clean. Large rugs cover the floor and muffle any " +
        "sounds here\n");
    add_item(({"rug", "rugs", "large rugs"}),
        "The large rugs are plush, filling the room with their " +
        "bright, luxurious colors.\n");
    
    add_cmd_item("sign", "read", library_help());
    set_book_directory("/d/Shire/rivendell/room/valley/books/");
    set_default_directory("general");
    set_approval_directory("approval");
    set_removal_directory("removed");
    create_library();

    add_exit(VALLEY_DIR + "u_cor03", "south", library_exit_block);

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

/*
public int library_write_access()
{
    return 1;
}
*/

public int library_exit_block()
{
    write ("You must return your books before leaving the library.\n");
    return !!sizeof(filter(deep_inventory(this_player()), &->id(BOOK_ID)));
}
