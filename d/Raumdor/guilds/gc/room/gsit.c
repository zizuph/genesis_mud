/*********************************************************************
 * - gsit.c                                                        - *
 * - This is the sitting room of the Gentlemans Club               - *
 * - This room is also a Library                                   - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/
#pragma strict_types
#include <stdproperties.h>  
#include "../guild.h"
inherit CLUB;

inherit "/lib/library";
#include "fireplace.c"
#include "seating2.c"
public int
library_exit_block()
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
        /* A book was found.  Give a warning and return 1 to block the exit */
        write("A magical force prevents you from leaving.\n" +
            "You must be carrying a book.\n");
        return 1;
    }

    /* No book present.  Return 0 to allow the player to exit */
    return 0;
}

public void
create_guild_room()
{
    set_short("An informal sitting room");
    set_long("This is an informal sitting room. Chairs have been "+
        "placed in various positions around a small round table. There "+
        "is a large fireplace on the southern wall, which holds a "+
        "marvelous fire dancing within its depths. Bookshelves line "+
        "the western wall with many different books. Delicate finely "+
        "crafted lanterns hang on the walls along side a few paintings.\n");
    add_item(({"room", "sitting room", "area"}), query_long);
    add_item(({"chair","chairs"}), seat_desc);
    add_my_desc(seat_desc, this_object());
    add_item(({"north", "south", "west", "northwest", "northeast",
        "southwest", "southeast"}),
        "There is a wall in that direction.\n");
    add_item(({"east"}),
        "There is a doorway in that direction.\n");
    add_item(({"lantern", "lanterns"}),
        "The lanterns are finely crafted with gold and glass and quite "+
        "delicate.\n");
    add_item(({"wall", "walls"}),
        "The walls have dark wooden panels one them with delicate gold "+
        "lanterns.\n");
    add_item(({"painting", "paintings"}),
        "There are a few different sized paintings in here of very "+
        "distinguished looking gentlemen.\n");
    set_borrow_required(1);
    set_book_directory(BOOKS);
    set_book_approval_directory(BOOKS + "approval/");
    set_book_removal_directory(BOOKS + "removed/");
    add_book_shelf(({ "general", "history", "members" }));
    create_library();
    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());
    add_exit("join","east", library_exit_block);
    set_no_exit_msg(({"north", "south", "west", "northeast", "northwest",
        "southeast", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
}

public int
library_admin_access()
{
    /* We'll give admin access to wizards */
    if (this_player()->query_wiz_level())
	    return 1;

    /* No-one else has admin access */
    write("You do not have permission to do that.\n");
    return 0;
}


public int
library_write_access()
{
    /* We'll allow any member of the racial guild  to write books
     */
    if (IS_MEMBER(this_player()))
	    return 1;

    /* We'll allow wizards to write books */
    if (this_player()->query_wiz_level())
	    return 1;

    /* No-one else has permission to write books */
    write("You do not have permission to do that.\n");
    return 0;
}

void
init()
{
    ::init();
    init_library();
    init_fire();
    init_seat();
}
