/* Commented out:
* write("You don't have permission to do that.\n");
*from query_librarian()
- the warning (wich was a.o. called by  init())
- wasn't really functional, but caused confusion
- Mayari 2020 5 13
*/
#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <mail.h>
#include "../herald.h"

inherit SHIRE_ROOM;
inherit "/lib/guild_library";

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
      "A sign posted to the tree will give further information, and " +
      "a plaque underneath the sign lists the current librarians.\n");

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

    set_library_book_object("/d/Shire/guild/heralds/obj/book_template");

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(HERALD_BOOKS);
    set_library_allow_new_books(1);

    create_library();

    add_item(({"sign" }), library_help);
    add_cmd_item(({"sign" }), "read", library_help);

    add_item(({"plaque" }), "@@list_herald_librarian");
    add_cmd_item(({"plaque" }), "read", "@@list_herald_librarian");

    add_exit("/d/Shire/herald/board", "southwest", prevent_leave_with_books);
}

void
init()
{
    ::init();
    init_library();
}

/*
 * Function name: library_hook_get_approval_names
 * Description  : This routine can be redefined in the library code to provide
 *                the names of the players who are authorized to approve books
 *                before they are added to the library. If this is the case,
 *                those players will receive a mail informing them of the fact
 *                that a new book has been submitted.
 * Returns      : string * - the list of names (in lower case).
 */
public mixed *
library_hook_get_approval_names()
{
    string * herald_librarians = ({ "emmiline" });

    if(sizeof(HERALD_GUILD_MASTER))
	herald_librarians += HERALD_GUILD_MASTER;

    return herald_librarians;

} /* library_hook_get_approval_names */

string
list_herald_librarian()
{
    string lib_str = "";

    if(!sizeof(library_hook_get_approval_names()))
        return "There currently are no librarians!\n";

    string * librarians = library_hook_get_approval_names();
    int num_libs = sizeof(library_hook_get_approval_names());

    foreach(string name: librarians)
    {
        lib_str += capitalize(name);
        num_libs--;

        if(num_libs > 1)
            lib_str += ", ";
        else if(num_libs > 0)
            lib_str += ", and ";
    }

    return "The current librarians are: " +lib_str+ ".\n";   
}

/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
public int 
query_librarian(object player)
{
    // By default only wizards are librarians. However, if you want,
    // return 1 here if we change that to allow players.
    //
    // Librarians have the ability to create/remove/delete, etc.

    if(player->query_name() == "Emmiline")
    {
      return 1;  
    }
    
    if (!player->query_wiz_level())
    {
       // write("You don't have permission to do that.\n"); Mayari 2020 5 13
        return 0;
    }

    return 1;
}

/*
 * Function name: add_new_book
 * Description  : Add a new book to the shelves
 * Arguments    : title - the title of the book
 *              : contents - the contents of the book
 *              : author - the author of the book
 *              : shelf (optional) - the shelf on which to place the book
 *              : filename (optional) - which filename to use for storing the
 *              :       content
 *              : book_id (optional) - the id by which the book is known
 * Returns      : a filename which contains the contents or 0 on failure
 *
 * I mask this from the parent so that I can have it generate a mail
 * and send it to whoever I have deemed to be the current guild
 * librarian.
 */
varargs mixed
add_new_book(string title, string contents, 
  string author, string shelf = "", string filename = "", 
  string book_id = "")
{
    mixed  submitted = ::add_new_book(title, contents, author, shelf,
        filename, book_id);
    string *names = library_hook_get_approval_names();

    if (!submitted)
    {
	return 0;
    }

    CREATE_MAIL("New book " + author, "HoVLibrary",
      implode(names, ","), "",
      "========================================================="
      + "======================\n"
      + "Title: " + title + "\n"
      + "========================================================="
      + "======================\n\n"
      + contents + "\n"
      + "---------------------------------------------------------"
      + "----------------------\n");

    return submitted;
} /* add_new_book */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently sitting in a chair. Also, we set up
 * some special library leave functions.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

