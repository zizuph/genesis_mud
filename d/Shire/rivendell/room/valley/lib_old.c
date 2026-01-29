/*
     The entrance to the smiths guild
*/

#pragma save_binary;

inherit "/d/Shire/room";
inherit "/lib/library";

#include "local.h"
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define BOOK_ID         (MASTER + "_library_book")


void
create_room()
{
   set_short("Library of Imladris");
    set_long("The Library is well known as a place of learning " +
        "among the Free Peoples. Countless tomes and books fill " +
        "the shelves in this room which appear to be in " +
        "fine condition. It is said that the Noldor are wise in " +
        "knowledge and understanding. The Library also acts a " +
        "repository for the Dunedain. An elven librarian sits " +
        "here, studying books. He looks around occasionally to " +
        "see if anyone needs help finding a book.\n");

    set_book_directory(VALLEY_DIR + "library/");
    set_borrow_required(1);
    add_book_shelf("lays");
    add_book_shelf("verses");

    create_library();

    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());

    add_prop(ROOM_I_INSIDE,1);
    add_exit(VALLEY_DIR + "u_cor03", "south", "@@library_exit_block@@");

}

void
init()
{
    ::init();
    init_library();


}

public int
library_write_access()
{
    return 1;
}

 public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);

} /* leave_inv */



/*
 * Function name: library_exit_block
 * Description:   Returns true if this_player() is in possession of
 *                a book from this library.  It can be used as a block
 *                function for library exits.
 * Returns:       1/0 - library book possessed/not possessed
 */
public int
library_exit_block()
{
//    write("The librarian looks up, wonder who is trying to sneak out with a book.\n");
    write ("You must return your books before leaving the library.\n");
    return !!sizeof(filter(deep_inventory(this_player()), &->id(BOOK_ID)));
}


/*
 * Function name: library_admin_access
 * Description:   Redefine this function to limit permission to admin commands
 * Returns:       1 - this_player() is permitted to perform admin commands
 *                0 - this_player() is not permitted to perform admin commands
 */
public int
library_admin_access()
{
    if (!this_player()->query_wiz_level())
    {
        write("You don't have permission to do that.\n");
        return 0;
    }

    return 1;
}