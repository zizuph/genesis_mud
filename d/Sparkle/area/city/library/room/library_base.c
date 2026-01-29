/*
 * /w/petros/sparkle/library/room/library_base.c
 *
 * Inherits from /lib/library.c and customizes the hooks for use
 * in the Genesis Library. Every room in the Genesis library will
 * that supports retrieving books will use this inheritable class.
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <mail.h>
#include <cmdparse.h>
#include "defs.h"

// Defines
#define BOOK_TYPE  book_types[0]
#define PLURAL_BOOK_TYPE \
    (sizeof(plural_book_types) ? \
    plural_book_types[0] : LANG_PWORD(book_types[0]))
  
#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))

#define TITLE_LINE   1
#define SUMMARY_LINE 2
#define AUTHOR_LINE  3
#define TEXT_LINE    4

#define MAX_TITLE_SIZE 20

// Inheritance
inherit "/lib/library";
inherit LIBRARY_ROOM_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables

// Prototypes
nomask void             create_library_room();
public void             create_library_stack();
public string           sparkle_short();
public varargs string   sparkle_long();
public void             create_genesis_library(string *shelves, 
                                               string subdir);
public void             init_genesis_library();
public int              can_write_book();
public int              library_list(string str);
public int              library_write(string str);
public int              library_no_books_hook();
public void             library_list_short_hook();
public void             library_list_long_hook();
public void             library_list_shelves_hook();
public void             library_list_shelf_long_hook(string shelf);
public void             library_list_shelf_short_hook(string shelf);
public int              library_list_syntax_failure_hook(string str);
public int              library_read(string str);
public string           library_help();
public void             library_read_book(string text_filename, 
                                          string book_name, int mread);
public void             display_library_action(string msg);
private int             cannot_see_library_action(object ob);                                          
private string          get_formatted_short_row(string title, string shelf,
                                                int centered);
private string          get_formatted_long_row(string title, string author, 
                                             string summary, int header);
private mapping         retrieve_book_mapping(mapping shelves_mapping);
private void            print_long_listing(mapping all_book_map, 
                                            string successmessage,
                                            string failmessage);

/*
 * Function name:        create_library_room
 * Description  :        set up the room
 */
nomask void
create_library_room()
{
    // Room Item Section                              
    add_item("sign", library_help());
    add_item( ({ "bookshelf", "bookshelves", "shelf", "shelves",
                 "shelving" }),
                  "The bookshelves in this room of the stacks are "
                + "finely constructed from solid oak. Each bookshelf "
                + "stands about 15 feet high, and books fill every "
                + "nook and cranny of the shelves. You think you might "
                + "be able to <browse> the shelves.\n");

    add_item( ({ "oak", "oak wood", "wood", "oak wood material",
                 "wood material", "oak material", "paint" }),
                  "The oak wood material that the bookshelves are made of "
                + "is really solid. The wood was finely hewn, and "
                + "varnished quite well. It looks like the wood is fairly "
                + "fresh, and you can still smell the paint on it.\n");

    add_item( ({ "books", "book", "title", "titles" }),
                  "There are so many books on the shelves that it is hard "
                + "to even imagine how one can possibly read through them "
                + "all. You think you might be able to <browse> through "
                + "and find some interesting titles.\n");

    add_item( ({ "stacks", "library stacks", "library",
                 "room" }),
                  "You are in one of the stacks of the Genesis Library. "
                + "There are many patrons of the Library gleaning "
                + "knowledge from the books that are all around you.\n"); 

    add_item( ({ "patrons" }),
                  "Patrons of all races, genders, and sizes can be seen "
                + "either walking up and down the wings, or browsing the "
                + "many volumes of books. Some of them look like they "
                + "probably spend all their time here.\n"); 
                               
    // Allow inheriting classes to define their things
    create_library_stack();
} // create_library_room

/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    return "Template Genesis Library Room";
} // sparkle_short


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    return "This is a basic room for the Genesis Library.";
} // sparkle_long

/*
 * Function name:        create_library_stack
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_library_stack()
{
} // create_library_stack

public void 
init() 
{
    ::init();  
    
    // Initialize Library
    init_genesis_library();    
} // init

/* 
 * Function name: library_list
 * Description:   The "list" command
 * Arguments:     string str - arguments given to the "list" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_list(string str)
{
    if (!m_sizeof(book_shelves))
    {
        // No browsing necessary when there are no shelves
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        write("It's a bit dark here to " + query_verb() + " anything.\n");
        return 1;
    }
        
    // we mask this method so that we can print the usage information
    // when someone doesn't provide an argument
    if (!str)
    {
        return library_list_syntax_failure_hook(str);
    }
    
    // Otherwise, process as normal
    return ::library_list(lower_case(str));
}

/*
 * Hooks for altering default messages
 */

/*
 * Function name: library_no_books_hook
 * Description:   Redefine this to alter the message given when commands
 *                fail because the library is empty.
 * Returns:       1/0
 */
public int
library_no_books_hook()
{
    write("You browse through the bookshelves, but you don't "
        + "find any books of interest.\n");
    return 1;
}

/*
 * Function name: get_formatted_short_row
 * Description  : This is a line formatter for when the title and shelf
 *                only are to be displayed
 * Arguments    : title    - book title
 *                shelf    - shelf name
 *                centered - whether the text should be centered or left
 *                           aligned              
 * Returns      : the string after calling sprintf
 */
private string
get_formatted_short_row(string title, string shelf, int centered)
{
    if (centered == 0)
    {
        return sprintf("%-30s| %-15s\n", title, shelf);
    }
    else
    {
        return sprintf("%|30s| %|15s\n", title, shelf);
    }       
}

private string *
split_lines(string line, int width)
{
    string * lines, * words;
    string current_line;
    int inf_counter, inf_counter2;
    
    lines = ({ });
    current_line = "";
    inf_counter = 0;
    inf_counter2 = 0;
    while (strlen(line) > width)
    {
        if (inf_counter > 5)
        {
            return ({ "ERROR: Infinite loop detected\n" });
        }
        
        words = explode(line, " ");
        while (sizeof(words) > 0 && strlen(current_line) <= width)
        {
            if (inf_counter2 > 30)
            {
                return ({ "ERROR: Infinite loop detected.\n" });
            }
            
            if (current_line == "")
            {
                current_line += words[0];
            }
            else if (strlen(words[0]) + strlen(current_line) + 1 <= width)
            {
                current_line += " " + words[0];
            }
            else
            {
                break;
            }
            if (sizeof(words) == 1)
            {
                words = ({ });
            }
            else
            {
                words = words[1..];
            }
            ++inf_counter2;
        }
        if (strlen(current_line) > 0)
        {
            lines += ({ current_line });
        }
        current_line = "";
        line = implode(words, " ");
        inf_counter2 = 0;
        ++inf_counter;
    }
    lines += ({ line });
    return lines;
}

/*
 * Function name: get_formatted_long_row
 * Description  : This is a line formatter for when the title and shelf
 *                only are to be displayed
 * Arguments    : title    - book title
 *                author   - book's author
 *                summary  - book summary
 *                header - whether the text should be centered or left
 *                           aligned              
 * Returns      : the string after calling sprintf
 */
private string
get_formatted_long_row(string title, string author, 
                       string summary, int header)
{
    string formatted_row;
    string * summary_lines;
    
    formatted_row = "";
    if (header == 0)
    {
        summary_lines = split_lines(summary, 35);
        foreach (string line : summary_lines)
        {
            formatted_row += sprintf("%-30s| %-10s| %-35s\n", title, 
                                     author, line);
            title = "";
            author = "";                                     
        }
        formatted_row += sprintf("%-30s|%-11s|%-36s\n",
                                 "------------------------------",
                                 "-----------",
                                 "------------------------------------"); 
        return formatted_row;
    }
    else
    {
        formatted_row += sprintf("%|30s|%|11s|%|36s\n", title, 
                                 author, summary);
        return formatted_row;
    }       
}
 
/*
 * Function name: retrieve_book_mapping
 * Description  : This is a help function that takes in a mapping of the
 *                shelves, and returns a mapping of the book title to the
 *                book filename for each shelf.
 * Arguments    : shelves_mapping - the mapping of shelves we want to
 *                                  retrieve the book titles for.
 * Returns      : mapping of shelf->(title->file) mapping.
 */
private mapping
retrieve_book_mapping(mapping shelves_mapping)
{
    mapping final_book_map = ([]);
    mapping book_map;
    string *shelves = ({}); // all the shelves available
    string *books = ({}); // all the book filenames on the shelves
    if (m_sizeof(shelves_mapping))
    {
        shelves = sort_array(m_indices(shelves_mapping));
        
        foreach (string shelf : shelves)
        {
            book_map = ([]);
            // For each shelf, print out the Shelf, and then the
            // books on that shelf.
            books = get_books(book_dir + shelf + "/");
            if (sizeof(books) == 0)
            {
                // No books to be printed. Go on to the next shelf
                continue;
            }
            get_book_info(books, book_map);
            final_book_map[shelf] = ([]) + book_map;            
        }
    }
    
    return final_book_map;            
}

/*
 * Function name: cannot_see_library_action
 * Description  : This private method is used to filter out livings that
 *                can see this_player(). The second argument of say and
 *                tell_room use an object array to exclude the objects
 *                to send a message to.
 * Arguments    : ob    - object to check whether it can see this_player()
 * Returns      : 0/1 - can/cannot see this_player()
 */
private int
cannot_see_library_action(object ob)
{
    // A person cannot see the action if they cannot see the invisible
    // person or if they cannot see in the dark
    return living(ob) && 
            (!CAN_SEE(ob, this_player())
             || !CAN_SEE_IN_ROOM(ob));
}

/*
 * Function name: display_library_action
 * Description  : This method allows an action by an invisible person
 *                to be unseen by onlookers
 * Arguments    : msg - mesage to be appended to the player performing the
 *                      action
 * Returns      : nothing
 */
public void
display_library_action(string msg)
{
    object *onlookers = filter(all_inventory(environment(this_player()))
                                   - ({ this_player() }), 
                               cannot_see_library_action);
    onlookers += ({ this_player() });                                                                                           
    say(QCTNAME(this_player()) + msg, onlookers);    
}

/*
 * Function name: library_list_short_hook
 * Description:   Redefine this to alter how the short listing of books
 *                is presented
 */
public void
library_list_short_hook()
{
    mapping all_book_map = retrieve_book_mapping(book_shelves);
    mapping book_map = ([]);
    string *titles = ({}); // all the book titles
    string *shelves = ({}); // all the shelves available
    string formatted_output = "";
    if (m_sizeof(all_book_map))
    {
        shelves = sort_array(m_indices(all_book_map));
        
        foreach (string shelf : shelves)
        {
            // For each shelf, print out the Shelf, and then the
            // books on that shelf.
            book_map = all_book_map[shelf];
            shelf = implode(map(explode(shelf, " "), capitalize), " ");
            if (sizeof(m_indices(book_map)) == 0)
            {
                // No books to be printed. Go on to the next shelf
                continue;
            }
            titles = sort_array(m_indices(book_map));
            foreach (string title : titles)
            {
                // Formats the lines of the output using a private function
                formatted_output += get_formatted_short_row(
                                        implode(map(explode(title, " "), 
                                                 capitalize), " "),
                                        shelf, 0);
            }
        }
    }    
    if (strlen(formatted_output) == 0)
    {
        library_no_books_hook();
    }
    else
    { 
        write("You browse through the bookshelves and you see these "
            + "books of interest: \n\n");
        formatted_output = get_formatted_short_row("Book Title", 
                                                   "Bookshelf Name", 1)
                         + get_formatted_short_row(
                               "=============================",
                               "===============", 0)
                         + formatted_output;
        write(formatted_output);
        // Now tell the user that they can <read> the titles
        write("\n"
            + "You can <read> any of the titles on the shelf.\n");        
    }
    
    display_library_action(" browses through all the bookshelves.\n");
}

/* 
 * Function name: print_long_listing
 * Description:   This method takes the mapping of books and prints out
 *                in long line format the book's title, author, and 
 *                summary.
 * Arguments:     all_book_map   - the mapping of all the books to print
 *                successmessage - the message to print when there are
 *                                 books to print
 *                failmessage    - the message to print whene there are no
 *                                 books to print
 * Returns:       nothing
 */
private void
print_long_listing(mapping all_book_map, string successmessage,
                   string failmessage)
{
    mapping book_map = ([]);
    string *titles = ({}); // all the book titles
    string *shelves = ({}); // all the shelves available
    string formatted_output = "";
    string author = "";
    string summary = "";
    if (m_sizeof(all_book_map))
    {
        shelves = sort_array(m_indices(all_book_map));
        
        foreach (string shelf : shelves)
        {
            // For each shelf, print out the Shelf, and then the
            // books on that shelf.
            book_map = all_book_map[shelf];
            shelf = implode(map(explode(shelf, " "), capitalize), " ");
            if (sizeof(m_indices(book_map)) == 0)
            {
                // No books to be printed. Go on to the next shelf
                continue;
            }
            titles = sort_array(m_indices(book_map));
            foreach (string title : titles)
            {
                author = query_book_author(book_map[title]);
                summary = query_book_summary(book_map[title]);
                // Formats the lines of the output using a private function
                formatted_output += get_formatted_long_row(
                                        implode(map(explode(title, " "), 
                                                 capitalize), " "),
                                        author, summary, 0);
            }
        }
    }    
    if (strlen(formatted_output) == 0)
    {
        write(failmessage);
    }
    else
    { 
        write(successmessage);
        formatted_output = get_formatted_long_row("Book Title", 
                                                   "Author",
                                                   "Book Summary", 1)
                         + get_formatted_long_row(
                               "==============================",
                               "===========",
                               "====================================", 1)
                         + formatted_output;
        write(formatted_output);
        // Now tell the user that they can <read> the titles
        write("\n"
            + "You can <read> any of the titles on the shelf.\n");
    }                              
}

/*
 * Function name: library_list_long_hook
 * Description  : Redefine this to alter how the long listing of books is
 *                presented
 */
public void
library_list_long_hook()
{
    mapping all_book_map = retrieve_book_mapping(book_shelves);
    print_long_listing(all_book_map,
        "You browse carefully through the bookshelves and you see "
      + "these books of interest: \n\n",
        "You browse carefully through the bookshelves, but you don't "
      + "find any books of interest.\n");

    display_library_action(" browses through all the bookshelves.\n");
}

/*
 * Function name: library_list_shelves_hook
 * Description  : Redefine this to alter how the listing of shelves is
 *                presented
 */
public void
library_list_shelves_hook()
{
    write("You carefully read the labels on the bookshelves.\n\n"
        + "Bookshelf Name\n"
        + "==============\n");
    foreach (string shelf : sort_array(m_indices(book_shelves)))
    {
        write(capitalize(shelf) + "\n");
    }
    write("\nYou can <browse> each shelf to see what interesting books "
        + "you can read.\n");   

    display_library_action(" browses through the labels on the "
                         + "bookshelves.\n");
}

/*
 * Function name: library_list_shelf_long_hook
 * Description  : Redefine this to alter how the long listing of books
 *                on a given shelf is presented
 * Arguments    : string shelf - the name of the shelf
 * Returns      : nothing
 */
public void
library_list_shelf_long_hook(string shelf)
{
    mapping input_map = ([ lower_case(shelf):"1" ]);
    mapping book_map = retrieve_book_mapping(input_map);
    print_long_listing(book_map,
        "You browse through the \"" + capitalize(shelf) 
      + "\" bookshelf and find these interesting books.\n\n",
        "You browse through the \"" + capitalize(shelf)
      + "\" bookshelf, but you don't find any books of interest.\n");

    display_library_action(" browses through the \"" 
                         + capitalize(shelf) 
                         + "\" bookshelf.\n");      
}

/*
 * Function name: library_list_shelf_short_hook
 * Description  : Redefine this to alter how the short listing of books
 *                on a given shelf is presented
 * Arguments    : string shelf - the name of the shelf
 * Returns      :
 */
public void
library_list_shelf_short_hook(string shelf)
{
    mapping input_map = ([ lower_case(shelf):"1" ]);
    mapping all_book_map = retrieve_book_mapping(input_map);
    mapping book_map = all_book_map[shelf];

    display_library_action(" browses through the titles on the \"" 
                         + capitalize(shelf) + "\" bookshelf.\n");
            
    if (sizeof(m_indices(book_map)) == 0)
    {
        write("You browse through the \"" + capitalize(shelf)
            + "\" bookshelf, but you don't find any interesting "
            + "titles.\n");
        return;
    }
    
    // From here, we know that we have some books to print out
    write("You browse through the \"" + capitalize(shelf)
        + "\" bookshelf and see these interesting titles.\n\n"
        + "Book Title\n"
        + "========================\n");
    foreach (string title : sort_array(m_indices(book_map)))
    {
        write(implode(map(explode(title, " "), capitalize), " ") + "\n");             
    }
}

/*
 * Function name: library_list_syntax_failure_hook
 * Description:   Redefine this to alter the message given when
 *                incorrect syntax is used for the "list" command
 * Arguments:     string str - the arguments to the "list" command
 * Returns:       1/0
 */
public int
library_list_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + " shelves\n"
              + "       " + query_verb() + " titles\n"
              + "       " + query_verb() + " <shelf name>\n"
              + "       " + query_verb() + " <shelf name> titles\n");
    return 0;
}

/*
 * Function name: library_borrow_unavailable_book_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to borrow or read a nonexistant book
 * Arguments:     string title - the title of the book
 * Returns:       1/0
 */
public int
library_borrow_unavailable_book_hook(string title)
{
    title = implode(map(explode(title, " "), capitalize), " ");
    notify_fail("There is no " + BOOK_TYPE + " titled '" + title 
              + "' available.\n");
    return 0;
}

/*
 * Function name: create_library
 * Description:   Initialize the library.  This should be called when the
 *                library object is created, AFTER it has been configured.
 * Arguments    : shelves - array of the shelves that belong to this room
 *                subdir  - the subdirectory that the books for this room
 *                          will be under
 */
public void
create_genesis_library(string *shelves, string subdir)
{
    // Set the directory where book files will be stored
    string bookdir = LIBRARY_BOOK_DIR;
    if (strlen(subdir))
    {
        bookdir += subdir + "/";
    }
    set_book_directory(bookdir); 
    set_book_approval_directory(LIBRARY_APPROVAL_DIR);
    set_book_removal_directory(LIBRARY_REMOVED_DIR);
    
    set_borrow_required(0);                                          
    if (sizeof(shelves))
    {        
        add_book_shelf(shelves);
        foreach (string shelf : shelves)
        {
            string shelfname = shelf;
            if (strlen(subdir))
            {
                shelfname += "_" + subdir;
            }
            LIBRARY_SHELF_MANAGER->add_shelf(shelfname, bookdir + shelf + "/",
                MASTER_OB(this_object()));
        }
    }
    set_shelf_type( ({ "shelf", "bookshelf", "bookcase" }) ); 
    set_plural_shelf_type( ({ "shelves", "bookshelves", "bookcases" }) );

    // Call the parent create_library to load the shelves
    ::create_library();
}

/*
 * Function name: init_genesis_library
 * Description:   Add library commands
 */
public void
init_genesis_library()
{
    add_action(library_read, "read");
    add_action(library_read, "mread");
    add_action(library_list, "browse");
    add_action(library_write, "write");

    if (library_admin_access())
    {
        add_action(library_approve,  "approve");
        add_action(library_classify, "classify");
        add_action(library_deny,     "deny");
        add_action(library_discard,  "discard");
    }
}

/*
 * Function name: library_read
 * Description:   Try to read a book from the library.
 * Arguments:     string str - any arguments to the command
 * Returns:       1/0 - Command success/failure
 */
public int
library_read(string str)
{
    if (!m_sizeof(book_shelves))
    {
        // No shelves means that there are no books.
        return 0;
    }
    
    string book_file;
    object * items = PARSE_COMMAND(str, 0, "%i");
    if (items)
    {
        // There are objects that match in this read. We will
        // allow them to be read.
        notify_fail("There is no book titled '" + str + "'.\n");
        return 0;
    }
    
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("It's too dark in here to read anything.\n");
        return 1;
    }
       
    switch (str)
    {
    case "sign":
        write(library_help());
        return 1;
    case "labels":
    case "label":
        library_list_shelves_hook();
        return 1;
    }

    if (strlen(str) && strlen(book_map[str]))
    {
        book_file = book_map[str];
        if (file_size(book_file) > 2000)
        {
            library_read_book(book_file, str, 1);
            return 1;
        }
    }
            
    return ::library_read(str);
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
        "Welcome to the Genesis Library! We hope that you will find "
      + "everything you need to quench that thirst of knowledge that "
      + "you have. In order to assist you, here are some instructions "
      + "on the use of the library.\n\n"
      + help_cmd("browse [<" + SHELF_TYPE + ">] " +
            "[titles]", "Browse books on the shelves here.");

    str += help_cmd("browse " + PLURAL_SHELF_TYPE, 
                    "Browse " + PLURAL_SHELF_TYPE + " here in this "
                  + "stack.");

    str += help_cmd("read <title>", "Read a book found on the shelves.") +
           help_cmd("mread <title>", "Mread a book found on the shelves.");

    if (can_write_book())
    {
        str += help_cmd("write", "Write a book and submit it to the "
                      + "library.");
    }
    
    return str + "\n";
}

/*
 * Function name: library_read_book
 * Description:   Display the text of a book to the reader
 * Arguments:     string text_filename - The filename of the book file to use
 *                string book_name     - The title of the book
 *                int mread            - true if more should be used
 * Returns:       nothing
 */
public void
library_read_book(string text_filename, string book_name, int mread)
{
    setuid();
    seteuid(getuid());

    write("You pick up the book titled \"" 
        + implode(map(explode(book_name, " "), capitalize), " ")
        + "\" from the bookshelf and begin to read it:\n\n");        
    display_library_action(" picks up a book from the bookshelf and "
                        + "begins to read it.\n");
        
    if (mread || (file_size(text_filename) > 4000))
    {
        this_player()->more(read_file(text_filename, TEXT_LINE));
    }
    else
    {
        write(read_file(text_filename, TEXT_LINE));
    }
}

/* 
 * Function name: can_write_book
 * Description:   Will be used to determine whether one can write books
 *                in this particular library room.
 * Arguments:     none
 * Returns:       nothing
 */
public int
can_write_book()
{
    // By default, don't allow writing of books
    return 0;
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
    if (!can_write_book())
    {
        return 0;
    }

    return ::library_write(str);
}

/*
 * Function name: library_classify_prompt_shelf_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a shelf name
 * Arguments:     string title - the title of the book being classified
 */
public void
library_classify_prompt_shelf_input_hook(string title)
{
    mapping all_shelves;
    
    all_shelves = LIBRARY_SHELF_MANAGER->query_all_shelves();
    write(sprintf("/%'-'73s\\\n", "-"));
    write(sprintf("| %|30s| %|39s |\n", "Shelf Name", "Room Location"));
    write(sprintf("|%'-'73s|\n", "-"));
    foreach (string shelfname : sort_array(m_indices(all_shelves)))
    {
        string roomfile = LIBRARY_SHELF_MANAGER->query_shelf_room(shelfname);
        string location = roomfile->short();
        location = implode(map(explode(location, " "), capitalize), " ");
        write(sprintf("| %-30s| %-39s |\n", shelfname, location));
    }
    write(sprintf("%'-'75s\n", "-"));
    write("Which " + SHELF_TYPE + " do you wish to place " + title +
        " in?\n> ");
}

/*
 * Function name: library_classify_get_shelf
 * Description:   Catch input from the user and classify a book under
 *                the indicated shelf
 * Arguments:     object who   - the user
 *                string title - the book's title
 *                string input - the shelf name
 * Returns:       1/0 - book classified/not classified
 */
public int
library_classify_get_shelf(object who, string title, string input)
{
    mapping all_shelves;
    object oldtp;
    string book_file;
    
    oldtp = this_player();
    set_this_player(who);
    
    all_shelves = LIBRARY_SHELF_MANAGER->query_all_shelves();
    input = lower_case(input);
    if (!IN_ARRAY(input, m_indices(all_shelves)))
    {
        send_debug_message("library_base", "Input shelf is "
            + input);
        library_classify_unavailable_shelf_hook(input);
        set_this_player(oldtp);
        return 0;
    }
    
    if (!strlen(book_file = book_map[title])) 
    {
        library_classify_unavailable_book_hook(title);
        set_this_player(oldtp);
        return 0;
    }

    library_move_book(book_file, all_shelves[input]);

    update_books();
    LIBRARY_SHELF_MANAGER->query_shelf_room(input)->update_books();
    
    library_classify_hook(title, input);
    set_this_player(oldtp);
    return 1;
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
    // Three groups allowed to access admin
    // 1. Arches and Keepers
    // 2. AoD team members
    // 3. Sparkle Liege
    int level;
    string * aod_team;
    string name;
    
    name = this_player()->query_real_name();
    level = this_player()->query_wiz_level();
    aod_team = SECURITY->query_team_list("aod");
    if (level >= WIZ_ARCH
        || IN_ARRAY(name, aod_team)
        || SECURITY->query_domain_lord("sparkle") == name)
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function:    contains_keywords
 * Description: Returns whether this room contains books that has
 *              the keywords in either the book titles, authors,
 *              or the summary.
 */
public int
contains_keywords(string words)
{
    string * keywords;
    string all_words;
    
    keywords = map(explode(words, " "), lower_case);
    all_words = lower_case(book_list);
    
    foreach (string keyword : keywords)
    {
        if (!wildmatch("*" + keyword + "*", all_words))
        {
            return 0;
        }
    }
    
    return 1;
}
