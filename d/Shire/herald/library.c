#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include "herald.h"

inherit SHIRE_ROOM;
inherit "/lib/library";

#define BOOK_ID         (MASTER + "_library_book")

void
create_room()
{
    set_short("A place of learning and scholarship");
    set_long("Here, among the branches, in the many nooks and crannies " +
      "naturally made by the tree is a place where many scrolls and " +
      "small books are kept. A leather tarp covers those places where " +
      "rain is apt to seep in, but on the whole the scrolls are left to " +
      "the open air, as copies are constantly being made by junior " +
      "Heralds. The main tree branch that led here, also ends here. " +
      "A sign posted to the tree will give further information.\n");

    add_item(({"branches","nooks","crannies","nook","cranny"}),
      "The branches twisting upward and every which way make many "+
      "convenient cubby-holes for putting scrolls and small books.\n");

    add_item(({"scroll","scrolls","book","small book","books"}),
      "The scrolls and books can be listed by doing: list.\n");

    add_item(({"leather tarp","cover","covers","leather tarpaulin"}),
      "The leather covers protect from direct sunlight as well as "+
      "water damage.\n");

    add_item(({"branch","tree branch","main tree branch"}),
      "The strong main tree branch that leads to the main trunk "+
      "goes southeast of here back to a meeting of the ways.\n");

    add_item("sign", "It has writing which should be read, not "+
      "merely examined. As signs go, it is a nice one.\n");
    add_cmd_item("branch", "sit on", "You sit back and relax in one "+
      "of the most comfortable chairs in the room.\n");

    set_book_directory(HERALD_DIR + "library/accepted/");
    set_book_approval_directory(HERALD_DIR + "library/waiting/");
    set_borrow_required(1);

    create_library();

    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());
    add_exit("board", "southwest", "@@library_exit_block@@");

    add_exit("/d/Shire/guild/heralds/room/library","northeast",0,0,1);
}

void
init()
{
    ::init();
    init_library();
}

/*
 * Function name: library_admin_access
 * Description:   Redefine this function to limit permission to admin commands
 *                Add mortal players by name to allow mortals admin access
 *                to the library.
 * Returns:       1 - this_player() is permitted to perform admin commands
 *                0 - this_player() is not permitted to perform admin commands
 */

public int
library_admin_access()
{  
    if(this_player()->query_name() == "Emmiline"){
      return 1;  
    }
    
    if (!this_player()->query_wiz_level())
    {
        write("You don't have permission to do that.\n");
        return 0;
    }

    return 1;
}

public int
library_write_access()
{
    return 1;
}

public int library_exit_block()
{
    write ("You must return your books before leaving the library.\n");
    return !!sizeof(filter(deep_inventory(this_player()), &->id(BOOK_ID)));
}
