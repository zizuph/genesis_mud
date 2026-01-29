/*
 * The library of Green Oaks
 * Based on the Blacksmiths of Shire and the Mercs Library
 * -- Finwe, March 2006
 */

#pragma save_binary;

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/lib/library";
inherit INDOORS_BASE;

#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))
#define BOOK_ID         (MASTER + "_library_book")

public void	    leave_inv(object ob, object dest);

void
create_room()
{
    set_short("Library of the Smiths Guild");
    set_long("This is the private area of the library, open " +
        "only to advanced Smiths. The room is full of shelves that line the " +
        "walls. The shelves are full of various books, tomes, " +
        "parchments, records, and scrolls. A large rug covers " +
        "the floor. A chair, a sofa, and a couch are here for " +
        "members to relax in and write or read books. There is " +
        "a sign posted on the wall.\n");
    add_item(({"books", "tomes", "parchments", "records"}),
        "They are bound between two harden leather covers and " +
        "held then together with two iron hinges. some look " +
        "well used, while others look new. They fill the " +
        "shelves and probably contain useful information.\n");
    add_item("scrolls",
        "They are of various sizes and made of rolled up paper. " +
        "They are stored on the shelves in scroll cases.\n");
    add_item("scroll cases",
        "The scroll cases are made of metal and look sturdy. " +
        "They are cylindrical and slightly larger than the " +
        "scroll it holds. Each case holds only one scroll.\n");
    add_item("rug",
        "The rug is thick and luxurious. It is a deep blue " +
        "color with a golden fringe. The rug is decorated with " +
        "geometric shapes.\n");
     add_item(({"fringe", "golden fringe"}),
        "The fringe is made from golden colored strands of yarn " +
        "and are about a hand's length long.\n");
    add_item(({"ground", "floor"}),
        "The floor is made of stone blocks. It is covered by a " +
        "large rug.\n");
    add_item(({"stone blocks","blocks"}),
        "The stone blocks are large and of granite. The blocks " +
        "fit together and make up the floor and walls.\n");
    add_item("walls",
        "The walls are made of fitted granite stone blocks. " +
        "They are lined with bookshelves.\n");
    add_item(({"shelves", "bookshelves"}),
        "The book shelves are made of steel. They line the " +
        "walls and are stuffed with books, tomes, scrolls, " +
        "parchments, and records.\n");
    add_item("ceiling",
        "The ceiling is plain and made of supported stone\n");

//    set_book_directory("/d/Sparkle/area/faerie/library/accepted/");
//    set_book_approval_directory("/d/Sparkle/area/faerie/library/waiting/");
    set_book_directory(LIBRARY_DIR + "accepted/");
    set_book_approval_directory(LIBRARY_DIR + "waiting/");

    set_borrow_required(1);
    create_library();

    add_item("sign", "@@read_sign@@");
    add_cmd_item("sign","read", "@@read_sign@@");

    add_prop(ROOM_I_INSIDE,1);
//    add_exit(GO_DIR + "library_entr", "east", "@@library_exit_block@@");
//    add_exit(GO_DIR + "adv_hall", "south", "@@library_exit_block@@");

}

void
init()
{
    ::init();
    init_library();


}

 public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
//    leave_inv_room_chairs(ob, dest);
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
 * Function name: library_help
 * Returns:       A string containing library help information
 */
public string
read_sign()
{
    string *libr_list;
    object ob;
    string s;
    libr_list=({});
/*
    if (!(librarian && sizeof(librarian)))
        libr_list=({ "none" });
    else
        foreach (string lbr : librarian)
        {
            s="offline";
            ob=find_living(lbr);
            if (ob)
                s= interactive(ob) ? "online": "linkdead";
            libr_list+= ({ sprintf("%s(%s)",capitalize(lbr), s) });
        }
*/
    write("Library of the " + ACADEMY_NAME + "\n\n" +
      "Current Librarian(s): " + implode(libr_list,", ") + ".\n\n"+
      "A wizard is responsible for 'appoint'ing or 'unappoint'ing " +
      "the librarian.\n");

    function help_cmd = &sprintf("%-33s - %-=40s\n", , );

    string str =
        "Library commands available:\n" +
        help_cmd("List " + 
            (m_sizeof(book_shelves) ? "[<" + SHELF_TYPE + ">] " : "") +
            "[titles]", "List books in the library.");

    if (m_sizeof(book_shelves))
    {
        str += help_cmd("List " + PLURAL_SHELF_TYPE, 
                        "List " + PLURAL_SHELF_TYPE + " in the library.");
    }

    if (borrow_required)
    {
        str += 
            help_cmd("Borrow <title>",
                     "Borrow a book for reading.") +
            help_cmd("Return <book>",
                     "Return a book to the library.");
    }
    else
    {
        str += help_cmd("Read <title>", "Read a book in the library.") +
               help_cmd("Mread <title>", "Mread a book in the library.");
    }

    str += help_cmd("Write", "Write a book and submit it to the library.");

        str += "\nLibrarian commands:\n";

        if (strlen(appr_dir))
        {
            str += 
                help_cmd("Approve <title>",
                         "Approve a book for inclusion in the library.");

            if (borrow_required)
            {
                str += help_cmd("Borrow approval <title>",
                    "Librarians may borrow books which have not been " +
                     "approved by using the \"approval\" option.");
            }
            else
            {
                str += help_cmd("(m)read approval <title>",
                    "Librarians may read books which have not been " +
                    "approved by using the \"approval\" option.");
            }

            str +=
                help_cmd("Deny <title>",
                     "Deny a book from inclusion in the library.") +
                help_cmd("List approval [titles]",
                     "Librarians may list books that need approval with " +
                     "the \"approval\" option.");
        }

        str += help_cmd("Discard <title>", "Remove a book from the library.");

        if (m_sizeof(book_shelves))
        {
            str += help_cmd("Classify <title>",
                            "Assign a book to a " + SHELF_TYPE + ".");
        }
        return str + "\n";

}
