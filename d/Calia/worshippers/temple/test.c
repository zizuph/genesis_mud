inherit "/std/room";
inherit "/lib/library";
inherit "/d/Calia/worshippers/temple/chair_room";

#include "defs.h"
#include <files.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <composite.h>

#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))

string tempstring = "";

void
create_room()
{
    set_short("A small chamber");
    set_long("This chamber is fairly small, the walls probably "+
        "as long as two humans lying head to toe. The walls are "+
        "made of stones, wood, and mud. On the western wall you "+
        "notice rows of small slots carved into the stone, which appear "+
        "to be shelves of some sort. Each of these slots "+
        "contain a number of parchment scrolls. On the northern wall you "+
        "notice a small slate plaque that you can read. "+
        "Against the southern wall you see a small desk. You can "+
        "head out back into the entranceway to the east.\n");

    set_book_type("scroll");
    set_plural_book_type("scrolls");

    set_shelf_type(({"row", "shelf"}));
    set_plural_shelf_type(({"rows", "shelves"}));
 
    set_borrow_required(1);
   
    // Set the directory where book files will be stored
    set_book_directory("/d/Calia/worshippers/test/");
    set_book_approval_directory("/d/Calia/worshippers/test/approval/");
    set_book_removal_directory("/d/Calia/worshippers/test/removal/");
   
    // Make two shelves, one for maps and one for other books
    add_book_shelf(({ "general", "spells", "knowledge" }));
    set_default_shelf("general"); 

    // Initialize the library
    create_library();
 
    // Add things to look at in this room.

    add_item("chamber", query_long());
    add_item("entranceway", "You can't see it very well from inside. Perhaps " +
             "you should leave to see it better.\n");
    add_item(({"plaque", "small plaque", "slate plaque", "small slate plaque"}),              &library_help());
    add_cmd_item("plaque", "read", &library_help());
    add_item(({"row", "rows"}), "These rows of slots are carved into the west " +
              "wall. There are a number of scrolls in them.\n");
    add_item(({"shelf", "shelves"}), "These aren't really shelves, but more " +
              "like rows of slots.\n");
    add_item(({"slot", "slots"}), "There are a number of little slots carved " +
              "into the wall.  Each contains mutliple scrolls.\n");
    add_item(({"scroll", "scrolls", "parchment scrolls"}), "These scrolls fit " +
              "nicely in the slots that hold them.  Perhaps you should read " +
              "the plaque to find out how to read them?\n");
    add_cmd_item("scroll", "read", "Hmmm, are you actually holding a scroll?\n");
    add_item(({"west wall", "western wall"}), "This wall has rows of small slots " +
              "carved into it.\n");
    add_item(({"wall", "walls", "eastern wall", "southern wall"}), "These walls " +
              "are made of wood and stone, with a pale, mud daubing used as a " +
              "coating. The west wall is different as it appears to be made " +
              "completely out of stone.\n");
    add_item(({"north wall", "northern wall"}), "This is the north wall of this " +
              "chamber. It is made out of wood and covered with a pale, mud " +
              "plaster. There is a slate plaque hanging on it.\n");
    add_item("desk", "This is a sturdy wooden desk with a chair behind it. " +
             "You see a pile of parchment and an inkwell with a quill " +
             "sitting on it.\n");
    add_item(({"pile", "parchment", "pile of parchment"}), "These leaves of " +
             "parchment are of a good quality.  In fact, they are good " +
             "to write a tome of information with!\n");
    add_item(({"inkwell", "pot"}), "This is a small, black-laquered, ceramic " +
             "pot. It is full of ink and ready for use.\n");
    add_item("quill", "The quill is a large pinfeather from a pigeon. It has " +
             "been sharpened and fitted with a split metal tip, to make it " +
             "into a writing implement.\n");
    add_item("ink", "This is a black, viscous, liquid that can be used for " +
             "writing a book.\n");
    add_item(({"tip", "metal tip"}), "This metal tip is split from it's point " +
             "up it's center to form a slot to hold ink.  Perhaps you could " +
             "use it to write a book?\n");
    add_item("chair", describe_chair);
    add_item("floor", "A packed dirt floor. It has been kept clean of natural " +
             "litter.\n");
    add_item("ceiling", "This is a ceiling made out of wooden beams and stone " +
             "slabs. The slabs have been covered by mud plaster to keep the " +
             "rain out.\n");
    add_item(({"beams", "wooden beams", "wood beams", "wood"}), "These wood " +
             "beams are roughly hewn from trees.  The are strong enough to " +
             "hold up the stone slabs that make the ceiling.\n");
    add_item(({"slabs", "stones"}), "These stone slabs are carefully fitted " +                     "together and covered with a mud plaster that provides a dry, " +
             "sheltered area for scholars to write books.\n");
    add_item(({"mud", "plaster", "daubing"}), "The plaster is a mud " +
             "that has been made from a light-colored soil and allowed to dry. " +
             "It covers the walls and ceiling.\n");    

    add_exit(WOR_TEMPLE+"entrance","east",can_leave,1);
}


void
init()
{
    ::init();

    // Add the library commands
    init_library();
}


/*
 * Function name: library_list_shelves_hook
 * Description:   Redefine this to alter how the listing of shelves is
 *                presented
 */
public void
library_list_shelves_hook()
{
    string *shelves;
    
    shelves = m_indices(book_shelves);
    if (!this_player()->is_worship())
    {
        shelves -= ({"spells", "knowledge"});
    }

    write(implode(map(shelves, capitalize),"\n") + "\n");
}


/*
 * Function name: library_restrict_books
 * Description:   Creates a string of books minus the restricted books.
 * Argumenst:     string *books - The book array to have restricted books
 *                                removed from.
 */

public string
library_restrict_books(string books)
{
    string *restricted, *spells, *knowledge, *templist;
    string bookstring, bookstringshort, spellstring, knowstring, restring;
    int i;

    restricted = ({});
    spells = ({});
    knowledge = ({});
    templist= ({});
    bookstring = "";
    bookstringshort = "";

 /*   seteuid(getuid());  */

    spells = map(get_dir(book_dir + "spells/"), &operator(+)(book_dir + "spells/"));
    spellstring = "";
    restring = "";
    knowstring = "";
    for (i=0; i<sizeof(spells); i++)
    {
        spellstring += spells[i] + " ";
    }
    write("This is the contents of spells : " + spellstring + "\n\n");
    knowledge = map(get_dir(book_dir + "knowledge/"), &operator(+)(book_dir + "knowledge/"));
    for (i=0; i<sizeof(knowledge); i++)
    {
        knowstring += knowledge[i] + " ";
    }
    write("This is the contents of knowledge : " + knowstring + "\n\n");
    templist = explode(books, "\n");
    for (i=0; i<sizeof(templist); i++)
    {
        tempstring += templist[i] + " ";
    }
    write("This is the value of templist : " + tempstring + "\n\n");
    restricted = spells + knowledge;
    write("This is the size of restricted : " + sizeof(restricted) + "\n\n");
    for (i=0; i<sizeof(restricted); i++)
    {
        restring += restricted[i] + " ";
    }
    write("This is the contents of restricted : " + restring + "\n\n");

    templist -= ({restricted});
    for (i=0; i<sizeof(templist); i++)
    {
        tempstring += templist[i] + " ";
    }
    write("This is the value of templist : " + tempstring + "\n\n");
    tempstring = implode(templist - ({""}), " ");
    write("This is the value to restricted tempstring : " + tempstring + "\n\n");
    write("This is just before format_book_list is called.\n");
    bookstring = format_book_list(templist);
    bookstringshort = format_book_list_short(templist);
    book_list = bookstring;
    book_list_short = bookstringshort;
    write("This is the end of library_restrict_books.\n");

}


string
query_tempstring()
{
    return tempstring;
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
    if (SECURITY->query_wiz_rank(this_interactive()->query_real_name()) &&         SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Calia")
    {
        return 1;
    }

    if (SECURITY->query_wiz_rank(this_interactive()->query_real_name()) >= WIZ_ARCH)
    {
        return 1;
    }

    if (this_interactive()->query_guild_member("Elemental Worshippers of Calia") && this_interactive()->query_guild_leader_lay())
    {
        return 1;
    }

    write("You don't have permission to do that.\n");
    return 0;
}


/*
 * Function name: library_write_access
 * Description:   Limit permission to write books to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */

public int
library_write_access()
{
    /* We'll allow any member of the layman guild
     * to write books
     */
    if (this_interactive()->query_guild_member("Elemental Worshippers of Calia"))
    {
        return 1;
    }

    /* We'll allow Calian wizards to write books */
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Calia")
    {
        return 1;
    }

    /* No-one else has permission to write books */
    write("The Elementals will not accept books from people " +
          "who do not worship them.\n");
    return 0;
}




/*
 * Function name: library_list_short_hook
 * Description:   Redefine this to alter how the short listing of books
 *                is presented
 */
public void
library_list_short_hook()
{
    if (!this_player()->is_worship())
    {
        library_restrict_books(book_list_short);
    }
    write(book_list_short);
    update_books();
}


/*
 * Function name: library_list_long_hook
 * Description:   Redefine this to alter how the long listing of books is
 *                presented
 */
public void
library_list_long_hook()
{
    if (!this_player()->is_worship())
    {
        library_restrict_books(book_list);
    }
    write(book_list);
    update_books();
}


/*
 * Function name: done_writing
 * Description:   Catch input from the user to be used as the new
 *                book's text and add the new book to the library
 * Arguments:     string title   - the book's title
 *                string summary - the book's summary
 *                string input   - the book's text
 * Returns:       1/0 - text set/not set
 */
public int
done_writing(string title, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        return 0;
    }

    if (SECURITY->query_guild_is_master("worshipper",this_interactive()->query_real_name()))
    {
        if (!add_book(title, summary, " ", input, !!strlen(appr_dir)))
        {
            library_write_failed_hook();
        }

        else
        {
            this_player()->remove_prop("_is_writing");
            write("Ok.\n");
        }
        return 1;
    }
    
    if (!add_book(title, summary, "by " + this_player()->query_name(), 
        input, !!strlen(appr_dir)))
    {
        library_write_failed_hook();
    }
    else
    {
        this_player()->remove_prop("_is_writing");
        write("Ok.\n");
    }

    return 1;

}


string
query_booklist()
{
    return book_list;
}


/*
 * Function name: library_write
 * Description:   The "write" command
 * Arguments:     string str - arguments to the "write" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_write(string str)
{
    if (!library_write_access())
    {
        return 1;
    }

    if (!this_player()->query_prop("_is_sitting"))
    {
        write("Don't you think it would be easier to write a book " +
              "if you were sitting down?\n");
        return 1;
    }

    this_player()->add_prop("_is_writing", 1);
    library_write_prompt_title_input_hook();

    input_to(&library_write_get_title(this_player()));
    return 1;
}


/*
 * Function name: library_help
 * Returns:       A string containing library help information
 */
public string
library_help()
{
    function help_cmd = &sprintf("%-33s - %-=40s\n", , );

    string str =
        "\nLibrary commands available:\n" +
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

    if ((SECURITY->query_wiz_rank(this_player()->query_real_name()) &&                 SECURITY->query_wiz_dom(this_player()->query_real_name()) == "Calia") ||
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= WIZ_ARCH) ||
        (this_player()->query_guild_member("Elemental Worshippers of Calia") &&         this_player()->query_guild_leader_lay()))
    {
        str += "\nAdministrator commands available:\n\n";

        if (strlen(appr_dir))
        {
            str += 
                help_cmd("Approve <title>",
                     "Approve a book for inclusion in the library.");

            if (borrow_required)
            {
                str += help_cmd("Borrow approval <title>",
                    "Administrators may borrow books which have not been " +
                     "approved by using the \"approval\" option.");
            }
            else
            {
                str += help_cmd("(m)read approval <title>",
                    "Administrators may read books which have not been " +
                    "approved by using the \"approval\" option.");
            }

            str +=
                help_cmd("Deny <title>",
                     "Deny a book from inclusion in the library.") +
                help_cmd("List approval [titles]",
                     "Administrators may list books that need approval with " +
                     "the \"approval\" option.");
        }

        str += help_cmd("Discard <title>", "Remove a book from the library.");

        if (m_sizeof(book_shelves))
        {
            str += help_cmd("Classify <title>",
                            "Assign a book to a " + SHELF_TYPE + ".");
        }
    }
    return str + "\n";
}