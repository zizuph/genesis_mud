
/*
 * library.c
 *
 * Library for the Spirit Circle of Psuchae Temple
 * Borrowed the Library Code from Quintas' Worshippers
 * Library Code (Thanks Quintas!!)
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 * Modifications
 *   12/11/2009 - Added code to capitalize the titles.
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/library";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <std.h>
#include <composite.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))


void load_board();

int 
query_prevent_snoop()
{
    return 1;
}

/*
 * Function name: library_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
library_exit_block()
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
        /* A book was found.  Give a warning and return 1 to block the exit */
        write("You cannot leave with a library book! Please <return "+
            "book>.\n");
        return 1;
    }
        /* No book present.  Return 0 to allow the player to exit */
    return 0;
}

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

void
create_room()
{
    set_short("Library");
    set_long("You are in the private library of the Spirit Circle of "+
        "Psuchae. Here you may sit at the desk that is sitting against the "+
        "eastern wall and write your thoughts and stories for the other "+
        "members of the Circle to enjoy. Lining the northern wall are "+
        "shelves. Just above the shelves you see a small slate plaque. "+
        "You can head back out to the Chamber of Statues to the west.\n");

    add_item(({"chamber of statues", "statues","statue","statue chamber"}), 
        "The Chamber of Statues lies to the west.\n");
    add_item(({"plaque", "small plaque", "slate plaque", "small slate plaque"}),              &library_help());
    add_cmd_item("plaque", "read", &library_help());
    add_item(({"shelf", "shelves"}), "These are quite a few shelves lining "+
        "the northern wall. There are several books on each shelf.\n");
    add_item(({"north wall", "northern wall"}), "This is the north wall of this " +
        "chamber. There is a slate plaque hanging on it above the shelves.\n");
    add_item("desk", "This is a sturdy wooden desk with a chair behind it. " +
        "You see a pile of parchment, a pile of papers, and an inkwell "+
        "with a quill sitting on it.\n");
    add_item(({"pile", "parchment", "pile of parchment"}), "These leaves of " +
        "parchment are of a good quality.  In fact, they are good " +
        "to write a tome of information with!\n");
    add_item(({"inkwell", "pot"}), "This is a small, black-laquered, ceramic " +
        "pot. It is full of ink and ready for use.\n");
    add_item("quill", "The quill is a large tailfeather from a pigeon. It has " +
        "been sharpened and fitted with a split metal tip, to make it " +
        "into a writing implement.\n");
    add_item(({"tailfeather", "feather"}), "This is a large tail feather from " +
        "a pigeon that has been harvested to make a quill like the one " +
        "you are holding.\n");
    add_item("ink", "This is a black, viscous, liquid that can be used for " +
        "writing a book.\n");
    add_item(({"tip", "metal tip"}), "This metal tip is split from it's point " +
        "up it's center to form a slot to hold ink.  Perhaps you could " +
        "use it to write a book?\n");
    add_item("chair", "It is a small wooden chair.\n");
    add_item("floor", "The floor and ceiling are both constructed with a grey "+
      "stone and then smoothed and polished afterwards. The floor is quite "+
      "comfortable to walk on.\n");
    add_item(({"wall", "walls"}),"The walls here are covered in a polished "+
      "wood, light brown, almost red, in colour. They are extremely smooth to "+
      "the touch.\n");
    add_item("ceiling", "The floor and ceiling are both constructed with a "+
      "grey stone and then smoothed and polished afterwards.\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    add_prop(ROOM_M_NO_TELEPORT, "You cannot do that here.");

    set_book_type("book");
    set_plural_book_type("books");

    set_shelf_type(({"row", "shelf"}));
    set_plural_shelf_type(({"rows", "shelves"}));

    add_book_shelf(({"general","maps","gifts","artifacts","herbs",
        "spirit_circle"}));
    
    set_borrow_required(1);
    
    // Set the directory where book files will be store */
    set_book_directory("/d/Calia/guilds/scop/texts/books/");
    set_book_approval_directory("/d/Calia/guilds/scop/texts/books/approval/");
    set_book_removal_directory("/d/Calia/guilds/scop/texts/books/removal/");
   
    // Initialize the library
    create_library();
    load_board();

    add_exit(SPIRIT_TEMPLE+"statue_chamber","west",library_exit_block,1);
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(SPIRIT_TEMPLE+"elder_board");
    bb->move(this_object());
}

void
init()
{
    ::init();

    // Add the library commands
    init_library();
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
    if (SECURITY->query_wiz_rank(TP->query_real_name()) &&
        SECURITY->query_wiz_dom(TP->query_real_name()) == 
        "Calia")
    {
        return 1;
    }

    if (SECURITY->query_wiz_rank(TP->query_real_name()) 
        >= WIZ_ARCH)
    {
        return 1;
    }

    if (is_spirit(TP) && 
        (COUNCIL_CODE->is_council_member(TP->query_real_name())
         || COUNCIL_CODE->is_luminary(TP->query_real_name())))
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
    /* We'll allow any member of the occ guild
     * to write books
     */
    if (is_spirit(TP))
    {
        return 1;
    }

    /* We'll allow Calian wizards to write books */
    if (SECURITY->query_wiz_dom(TP->query_real_name()) ==
        "Calia")
    {
        return 1;
    }

    /* No-one else has permission to write books */
    write("The Circle will not accept books from people " +
          "who are not members.\n");
    return 0;
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

/* Quintas : Redefined to add property management. */
public int
done_writing(string title, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        TP->remove_prop("_is_writing");
        return 0;
    }

    if (!add_book(title, summary, "by " + TP->query_name(), 
        input, !!strlen(appr_dir)))
    {
        library_write_failed_hook();
        TP->remove_prop("_is_writing");
    }
    else
    {
        TP->remove_prop("_is_writing");
        write("Ok.\n");
    }

    return 1;

}

/*
 * Function name: library_write_get_summary
 * Description:   Catch input from the user to be used as the new
 *                book's summary
 * Arguments:     object who   - the user
 *                string title - the new book's title
 *                string input - the user's input
 * Returns:       1/0 - summary set/not set
 */
public int
library_write_get_summary(object who, string title, string input)
{
    if (input == "~q")
    {
        TP->remove_prop("_is_writing");
        return 0;
    }

    set_this_player(who);

    if (!library_validate_summary(input))
    {
        input_to(&library_write_get_summary(TP, title));
        return 0;
    }

    setuid();
    seteuid(getuid());

    write("\n");
    clone_object(EDITOR_OBJECT)->edit(&done_writing(title, input));
    return 1;
}

/*
 * Function name: library_write_get_title
 * Description:   Catch user input to be used as the new book's title
 * Arguments:     object who   - the user
 *                string input - the title
 * Returns:       1/0 - title set/not set
 */
public int
library_write_get_title(object who, string input)
{
    if (input == "~q")
    {
        TP->remove_prop("_is_writing");
        return 0;
    }

    set_this_player(who);

    if (!library_validate_title(input))
    {
        input_to(&library_write_get_title(TP));
        return 0;
    }

    library_write_prompt_summary_input_hook();
    input_to(&library_write_get_summary(TP, input));
    return 1;
}


/*
 * Function name: library_write
 * Description:   The "write" command
 * Arguments:     string str - arguments to the "write" command
 * Returns:       1/0 - syntax success/failure
 */
/* Quintas : Redefined to add property management. */
public int
library_write(string str)
{
    if (!library_write_access())
    {
        return 1;
    }
 
    TP->add_prop("_is_writing", 1);
    library_write_prompt_title_input_hook();

    input_to(&library_write_get_title(TP));
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
    if ((SECURITY->query_wiz_rank(TP->query_real_name()) && 
        SECURITY->query_wiz_dom(TP->query_real_name()) == "Calia") ||
        (SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_ARCH) ||
        (is_spirit(TP)) && 
        (COUNCIL_CODE->is_council_member(TP->query_real_name())
         || COUNCIL_CODE->is_luminary(TP->query_real_name())))
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

/*
 * Function name: query_book_title
 * Description:   Given a book file, return the book's title
 * Arguments:     string file - The filename for the desired book
 * Returns:       The book's title
 */
public string
query_book_title(string file)
{
    string sTitle = ::query_book_title(file);
    if (!strlen(sTitle))
    {
        return sTitle;
    }
    sTitle = implode(map(explode(sTitle, " "), capitalize), " ");
    return sTitle;
}

private string
clean_title(string sTitle)
{
    string first_word, rest_of_title;
    if (sscanf(sTitle, "%s %s", first_word, rest_of_title) == 2
        && (lower_case(first_word) == "the" || lower_case(first_word) == "a"))
    {
        sTitle = rest_of_title;
    }
    
    return sTitle;
}

private int 
sort_book_file(string a, string b)
{
    string title_a = clean_title(query_book_title(a));
    string title_b = clean_title(query_book_title(b));

    if (title_a < title_b)
    {
        return -1;
    }
    else if (title_a > title_b)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: format_book_list
 * Description:   Given an array of book files, return a nicely formatted
 *                string which lists the given books.
 * Arguments:     string *books - an array of book filename strings
 * Returns:       A string description of the given books
 */
public string
format_book_list(string *books)
{
    string * sorted_books = sort_array(books, sort_book_file);

    return ::format_book_list(sorted_books);
}

/*
 * Function name: format_book_list_short
 * Description:   Return a short version of the book listing (See documentation
 *                for format_book_list())
 * Arguments:     string *books - an array of book filename strings
 * Returns:       A string description of the given books
 */
public string
format_book_list_short(string *books)
{
    string * titles = sort_array(map(books, query_book_title));
    return sprintf("%-#70.2s\n", implode(titles, "\n"));
}
