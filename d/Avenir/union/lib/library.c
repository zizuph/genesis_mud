#pragma strict_types
/*
 *  /d/Avenir/inherit/library.c
 *  Based on: /lib/guild_library.c
 *
 *  Example usage:
 *
 *  inherit "/std/room";
 *  inherit "/d/Avenir/inherit/library";
 *
 *  void create_room()
 *  {
 *      set_short("Library");
 *      set_long("This is a guild library.\n");
 *
 *      set_library_save_path("/d/Domain/somedir/");
 *      set_library_allow_new_books(1);
 *
 *      create_library();
 *
 *      add_item(({"plaque", "instructions", }), library_help);
 *      add_cmd_item(({"plaque", "instructions", }), "read", library_help);
 *  }
 *
 *  void init()
 *  {
 *      ::init();
 *      init_library();
 *  }
 *
 *  void leave_inv(object ob, object to)
 *  {
 *      library_leave_inv(ob, to);
 *      ::leave_inv(ob, to);
 *  }
 *
 *  Created by Linor, 23-11-2003
 *  Ported from Angalon to Genesis by Eowul, 30-8-2004
 *  Almost entirely re-written by Lucius@Genesis, 2011-2016
 *
 *  Someday:
 *    Implement per item styling
 */
#include <macros.h>
#include <composite.h>

#define EDITOR  "/obj/edit"

#define BACKUPS 10
#define VERSION 6

#define BOOKS     library_data["books"]
#define SHELVES   library_data["shelves"]
#define BORROWED  library_borrowed_books

#define BORROW_MAX	10
#define BORROW_DEFAULT	 3
#define BORROW_DELAY	itof(2 + random(3))

#define LIBRARY_BOOK	   "_avenir_library_book"
#define BORROW_ALARM_PROP  "_avenir_i_borrow_book"

#define MAX_SET_BOOK_ID   999999
#define MAX_NEW_BOOK_ID   999000
#define DEF_NEW_BOOK_ID   1000

// Keep these in-sync with the book.
#define MINLEN_ALL	3
#define MAXLEN_SHELF	15
#define MAXLEN_DESC	50
#define MAXLEN_SECTN	15
#define MAXLEN_TITLE	35

#define SHELF_DESC	0
#define SHELF_ACCESS	1
#define SHELF_BOOKS	2
#define SHELF_SECTN	3
#define SHELF_ALLOCATE  4

#define BOOK_FILE       0
#define BOOK_SHELF      1
#define BOOK_SECTN      2
#define BOOK_LOCKED     3
//#define BOOK_RESERVED   4
#define BOOK_TITLE      5
#define BOOK_TYPE       6
#define BOOK_SUMMARY    7
#define BOOK_AUTHORS    8
//#define BOOK_RESERVED   9
//#define BOOK_RESERVED   10
//#define BOOK_RESERVED   11
#define BOOK_ALLOCATE   12
/*
 * mapping library_data = ([
 *	"version" : (int),
 *	"shelves" : ([
 *	    "shelf" : ({
 *	        description[0], access[1], ({ books })[2], ({ sections })[3]
 *	    }),
 *	]),
 *	"books"   : ([
 *	    "book_id" : ({
 *              file[0], shelf[1], section[2], locked[3], RES[4],
 *              title[5], type[6], summary[7], ({ authors })[8],
 *              RES[9], RES[10], RES[11]
 *	    }),
 *	]),
 * ])
 */
private static mapping library_data = ([]);
private static mapping library_access_levels = ([]);
private static mapping library_borrowed_books = ([]);

private static int     library_new_book_id_start;
private static int     library_allow_edit_direct;
private static int     library_allow_read_direct;
private static int     library_allow_new_books;
private static int     library_max_borrow;

private static string  library_log_file;
private static string  library_save_file;
private static string  library_save_path;
private static string  library_book_type;
private static string  library_book_object;
private static string  library_new_book_shelf;
private static string  library_librarian_level;
private static string *library_protected_shelves = ({});
private static string  library_cmd_prefix;


// Prototypes
private void save_library_data(void);    // Write data to disk
private void load_library_data(void);    // Get data from disk
public string query_access_desc(string level);
public string * query_player_access(object player);
public int query_librarian(object player);
public int query_access_display(void);


// Hooks

/*
 * Function name: library_hook_book_none
 * Description  : Called when trying to access a non-existant book
 * Arguments    : book_id - the id of the book
 * Returns      : a string message
 */
public string
library_hook_book_none(string book_id)
{
    return "There is no " + library_book_type +
	" with id '" + book_id + "' available.\n";
}

/*
 * Function name: library_hook_book_exists
 * Description  : Called when trying to change an existing book
 * Arguments    : book_id - the id of the book
 * Returns      : a string
 */
public string
library_hook_book_exists(string book_id)
{
    return "There is already a " + library_book_type +
	" numbered '" + book_id + "'.\n";
}

/*
 * Function name: library_hook_shelf_none
 * Description  : Called when trying to access a non-existant shelf
 * Arguments    : shelf - the name of the shelf
 * Returns      : a string message
 */
public string
library_hook_shelf_none(string shelf)
{
    return "There is no shelf named '" +
	capitalize(shelf) + "' available.\n";
}

/*
 * Function name: library_hook_shelf_exists
 * Description  : Called when trying to change an existing shelf
 * Arguments    : shelf - the name of the shelf
 * Returns      : a string
 */
public string
library_hook_shelf_exists(string shelf)
{
    return "There is already a shelf named '" +
	capitalize(shelf) + "'.\n";
}

/*
 * Function name: library_hook_fail_length
 * Description  : Called when failing due to string too long
 * Arguments    : what - a string categore
 *                limit - the limiter
 * Returns      : a string
 */
public string
library_hook_fail_length(string what, int limit)
{
    return "That '"+ capitalize(what) +"' is invalid!\n"+
	    "Try to keep it between "+ MINLEN_ALL +" and "+
	    limit +" characters.\n";
}

/*
 * Function name: library_hook_fail_same
 * Description  : Called when failing due to names being equal
 * Arguments    : misc - a string
 * Returns      : a string
 */
public string
library_hook_fail_same(string misc)
{
    return "The old and new names are identical, "+
	"no change needed.\n";
}

/*
 * Function name: library_hook_book_locked
 * Description  : Called attempting to alter a locked book
 * Arguments    : book_id - the id of the book
 */
public void
library_hook_book_locked(string book_id)
{
    write("You are not allowed to alter the contents "+
	"of this " + library_book_type + ".\n");
}

/*
 * Function name: library_hook_rename_book
 * Description  : Called after a book is renamed
 * Arguments    : book_id - the id of the book
 *              : new_name - the new title of the book
 * Returns      : a string
 */
public string
library_hook_rename_book(string book_id, string new_name)
{
    return "The " + library_book_type + " '" +
	book_id + "' is now titled '" + new_name + "'.\n";
}

/*
 * Function name: library_hook_access_change
 * Description  : Called when the access level of a shelf is changed
 * Arguments    : shelf - the name of the shelf
 *              : level - the new access level
 * Returns	: a string
 */
public string
library_hook_access_change(string shelf, string level)
{
    return "Changed the access level of '" +
	shelf + "' to '" + level + "'.\n";
}

/*
 * Function name: library_hook_renumber_book
 * Description  : Called after a book has been renumbered
 * Arguments    : old_id - the original id of the book
 *              : new_id - the new id of the book
 */
public void
library_hook_renumber_book(string old_id, string new_id)
{
    write("You renumber " + library_book_type + " '" + old_id + "' to '" +
        new_id + "'.\n");
    say(QCTNAME(this_player()) + " moves some " + library_book_type +
        "s around on the shelves.\n");
}

/*
 * Function name: library_hook_rename_shelf
 * Description  : Called when a shelf is renamed
 * Arguments    : old_name - the original name
 *              : new_name - the new name of the shelf
 * Returns      : a string
 */
public string
library_hook_rename_shelf(string old_name, string new_name)
{
    return "The shelf '" + capitalize(old_name) +
	"' has been renamed to '" + capitalize(new_name) + "'.\n";
}

/*
 * Function name: library_hook_change_shelf_title
 * Description  : Called when a shelf is renamed
 * Arguments    : shelf - the name of the shelf
 *              : desc - the new description
 * Returns      : a string
 */
public string
library_hook_change_shelf_desc(string shelf, string desc)
{
    return "Changed description of shelf '" +
	capitalize(shelf) + "' to: " + desc + ".\n";
}

/*
 * Function name: library_hook_edit_direct
 * Description  : Called when finished directly editing a book
 * Arguments	: book_id - id of the edited book
 */
public void
library_hook_edit_direct(string book_id)
{
    write("You complete your revisions to the "+
	library_book_type +" numbered '"+ book_id +"'.\n");
}

/*
 * Function name: library_hook_edit_direct_fail
 * Description  : Called when directly reading books is disallowed.
 * Arguments	: book_id - id of the edited book
 */
public void
library_hook_edit_direct_fail(string book_id)
{
    write("The "+ library_book_type +" '"+ book_id +"' "+
	"was locked while you were editing.\nChanges lost!\n");
}

/*
 * Function name: library_hook_no_edit_direct
 * Description  : Called when directly editing books is disallowed.
 */
public void
library_hook_no_edit_direct(void)
{
    write("If you wish to edit the "+ library_book_type +
	", try to borrow it first.\n");
    say(QCTNAME(this_player()) +" scans the shelves for a "+
	library_book_type +" to scribble in.\n");
}

/*
 * Function name: library_hook_read_direct
 * Description  : Called when a player directly reads a book
 * Arguments    : book_id - the id of the book
 * 		  content - the text of the book
 */
public void
library_hook_read_direct(string book_id, string content)
{
    this_player()->more(content);
    say(QCTNAME(this_player()) +" pulls a "+ library_book_type +
	" from the shelves and quickly scans its contents.\n");
}

/*
 * Function name: library_hook_no_read_direct
 * Description  : Called when directly reading books is disallowed.
 */
public void
library_hook_no_read_direct(void)
{
    write("If you wish to read a "+ library_book_type +
	", try to borrow it first.\n");
    say(QCTNAME(this_player()) +" scans the shelves for a "+
	library_book_type +" to read.\n");
}

/*
 * Function name: library_hook_begin_borrow
 * Description  : Write the messages for the start of the borrow process
 */
public void
library_hook_begin_borrow(void)
{
    write("You start searching the shelves for the " +
	library_book_type + ".\n");
    say(QCTNAME(this_player()) + " begins searching the shelves.\n");
}

/*
 * Function name: library_hook_already_borrowing
 * Description  : Write a message for when already searching for a book
 */
public void
library_hook_already_borrowing(void)
{
    write("You are already searching the shelves for another " +
	library_book_type + "!\n");
}

/*
 * Function name: library_hook_receive_book
 * Description  : Write the messages for a player receiving a book
 * Arguments    : player - the player receiving the book
 *              : book - the book the player receives
 */
public void
library_hook_receive_book(object player, object book)
{
    player->catch_tell("You find the " + library_book_type +
        " that you were looking for and take it from the shelf.\n");
    tell_room(environment(player), QCTNAME(player) + " seems to " +
        "have found the " + library_book_type + " " +
        player->query_pronoun() + " was " +
        "looking for and lifts it off the shelf.\n", player);
}

/*
 * Function name: library_hook_book_not_found
 * Description  : Write the messages for a player unable to find a book
 * Arguments    : player - the player to get the message
 *                noaccess - this is set when failed due to access
 */
public varargs void
library_hook_book_not_found(object player, int noaccess = 0)
{
    player->catch_tell("You do not seem able to find the " +
	library_book_type +" you were looking for, perhaps "+
	(noaccess ? "it does not exist?\n" : (library_max_borrow > 1 ?
		"all copies were" : "it was") + " borrowed?\n"));
    tell_room(environment(player), QCTNAME(player) +
	" seems unable to find the " + library_book_type + " " +
	player->query_pronoun() + " was looking for.\n", player);
}

/*
 * Function name: library_hook_borrow_blank
 * Description  : Write the messages for player receiving a blank book
 */
public void
library_hook_borrow_blank(void)
{
    write("You take a blank " + library_book_type + " from the shelf.\n");
    say(QCTNAME(this_player()) + " takes a blank " +
	library_book_type + " from the shelf.\n");
}

/*
 * Function name: library_hook_borrow_blank
 * Description  : Write the messages for player unable to get a blank book
 */
public void
library_hook_borrow_blank_fail(void)
{
    write("You already have a blank " + library_book_type + "!\n");
    say(QCTNAME(this_player()) + " starts to take a blank " +
	library_book_type + " from the shelf but then returns it.\n");
}

/*
 * Function name: library_hook_leave_with_books
 * Description  : Called when a player leaves the library with books
 * Arguments    : player - the player that's leaving
 *              : books - an array with the books that have not been returned
 */
public void
library_hook_leave_with_books(object player, object *books)
{
    player->catch_msg("A librarian comes running after you and " +
	"takes " + COMPOSITE_DEAD(books) + ".\n");
    tell_room(environment(player), "A librarian runs in after " +
	QTNAME(player) + " and takes " + COMPOSITE_DEAD(books) +
	" from " + player->query_objective() + ".\n", player);
}

/*
 * Function name: library_hook_stop_leave
 * Description  : Called when a player is stopped while carrying books,
 * Arguments    : player - the player that's trying to leave
 *              : books - an array with the books that have not been returned
 */
public void
library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("The librarian wont let you leave with " +
        COMPOSITE_DEAD(books) + ".\n");
}

/*
 * Function name: library_hook_stop_borrowing
 * Description  : Called when a player leaves while searching
 * Arguments    : player - the player that's trying to leave
 */
public void
library_hook_stop_borrowing(object player)
{
    player->catch_tell("You stop searching the shelves.\n");
}

/*
 * Function name: library_hook_list_empty_shelf
 * Description  : Called when a player tries to list an empty shelf
 * Arguments    : shelf - the name of the shelf being listed
 */
public void
library_hook_list_empty_shelf(string shelf)
{
    write("The shelf '" + capitalize(shelf) + "' is empty.\n");
}

/*
 * Function name: library_hook_list_none
 * Description  : Called when there was nothing valid to list
 * Arguments    : what - the argument we tried to list
 */
public string
library_hook_list_none(string what)
{
    return "There is nothing named '"+ capitalize(what) +"' to display.\n";
}

/*
 * Function name: library_hook_list_item
 * Description  : Called when a player lists a specific item
 * Arguments    : name - the id of the item being listed
 */
public void
library_hook_list_item(string book_id)
{
    mixed *data = BOOKS[book_id];
    string str = sprintf("\n   %s\n"+
	"\n %6s   %-=50s   %|13s\n%'-'8s %'-'52s %'-'15s",
	implode(map(explode(data[BOOK_SHELF], ""), capitalize), " * "),
	"Number", "Title", "Author", "", "", "");

    str += sprintf("\n %6d   %-=50s   %|13s",
	atoi(book_id), data[BOOK_TITLE] +
	(strlen(data[BOOK_SUMMARY]) ?
	    "\n" + data[BOOK_SUMMARY] : ""),
	capitalize(data[BOOK_AUTHORS][0]));

    write(str + "\n");
}


/*
 * Function name: library_hook_list_books
 * Description  : Called when a player lists the contents of a shelf
 * Arguments    : name - the name of the shelf being listed
 *		  books - an array book id's belonging to the shelf
 */
public void
library_hook_list_books(string shelf, string *books)
{
    // Check for empty shelves
    if (!sizeof(books))
	return library_hook_list_empty_shelf(shelf);

    shelf = implode(map(explode(shelf, ""), capitalize), " * ");

    // Display the list
    string str = sprintf("\n   %s\n"+
	"\n %6s   %-50s   %|13s\n%'-'8s %'-'52s %'-'15s",
	shelf, "Number", "Title", "Section", "", "", "");

    foreach(string book: sort_array(books))
    {
	mixed *data = BOOKS[book];

        str += sprintf("\n %6d   %-=50s   %|13s",
	    atoi(book), data[BOOK_TITLE] +
	    (strlen(data[BOOK_SUMMARY]) ? " \n" + data[BOOK_SUMMARY] : ""),
	    (strlen(data[BOOK_SECTN]) ? capitalize(data[BOOK_SECTN]) : "-"));
    }

    write(str + "\n");
}

/*
 * Function name: library_hook_list_shelves
 * Description  : Called when a player lists the available shelves
 * Arguments    : shelves - the array of shelves the player has access to
 */
public void
library_hook_list_shelves(string *shelves)
{
    int admin = query_librarian(this_player()),
	display_access = query_access_display();
    string str = "You find the following shelves:\n\n";

    if ((display_access == 1) || ((display_access == 2) && admin))
	display_access = 1;
    else
	display_access = 0;

    if (display_access)
    {
	str += sprintf(" %-18s%-5s   %-33s   %|13s\n"+
	    "%'-'25s %'-'35s %'-'16s\n",
	    "Shelf", "Books", "Description", "Access", "", "", "");
    } else {
	str += sprintf(" %-18s%-5s   %-50s\n"+
	    "%'-'25s %'-'50s\n", "Shelf", "Books", "Description", "", "");
    }

    foreach(string shelf: shelves)
    {
	mixed *data = SHELVES[shelf];

	if (display_access)
	{
	    str += sprintf(" %-18.18s%|5.5d   %-33.33s   %|13.13s\n",
		capitalize(shelf), sizeof(data[SHELF_BOOKS]), data[SHELF_DESC],
		query_access_desc(data[SHELF_ACCESS]));
	} else {
	    str += sprintf(" %-18.18s%|5.5d   %-50.50s\n",
		capitalize(shelf), sizeof(data[SHELF_BOOKS]), data[SHELF_DESC]);
	}
    }

    write(str + "\n");
}

/*
 * Function name: library_hook_list_sections
 * Description  : Called when a player lists the available sections
 * Arguments    : sections - the mapping of shelves/sections the player has access to
 */
public void
library_hook_list_sections(mapping sections)
{
    string str = "You find the following sections:\n\n";

    str += sprintf(" %16s     %-30s\n%'-'19s %'-'32s\n",
	"Shelf", "Sections", "", "");

    foreach(string shelf: sort_array(m_indexes(sections)))
    {
	string *arr = map(sections[shelf], capitalize);

	str += sprintf(" %16.16s     %-#30.1s \n\n",
	    capitalize(shelf), implode(arr, "\n"));
    }

    write(str);
}

/*
 * Function name: library_hook_list_section_items
 * Description  : Called when a player lists one section
 * Arguments    : section - The name of the sections
 *                shelves - The shelves having 'section'
 */
public void
library_hook_list_section_items(string section, string *shelves)
{
    string str = "You find the following items for section: "+
	capitalize(section) +"\n\n";

    str += sprintf("%6s   %-50s    %-15s\n%'-'8s %'-'52s %'-'16s",
	"Number", "Title", "Shelf", "", "", "");

    foreach(string shelf: shelves)
    {
	string *books = filter(SHELVES[shelf][SHELF_BOOKS],
	    &operator(==)(, section) @
	    &operator([])(, BOOK_SECTN) @
	    &operator([])(BOOKS, ));

	foreach(string book: sort_array(books))
	{
	    mixed *data = BOOKS[book];
	    str += sprintf("\n %6d   %-=50s   %-15s",
	    atoi(book), data[BOOK_TITLE] +
	    (strlen(data[BOOK_SUMMARY]) ? "\n" + data[BOOK_SUMMARY] : ""),
	    capitalize(shelf));
	}
    }

    write(str + "\n");
}

/*
 * Function name: library_hook_list_shelf_no_access
 * Description  : Called when a player has no access to a specific shelf
 * Arguments	: shelf - Name of shelf we tried to list
 */
public void
library_hook_list_shelf_no_access(string shelf)
{
    write(library_hook_shelf_none(shelf));
}

/*
 * Function name: library_hook_list_shelves_no_access
 * Description  : Called when a player has no access to any shelves
 */
public void
library_hook_list_shelves_no_access(void)
{
    write("You look at the shelves but don't find anything " +
	"interesting.\n");
}

/*
 * Function name: library_hook_list_no_sections
 * Description  : Called when there are no sections to list
 */
public void
library_hook_list_no_sections(void)
{
    library_hook_list_shelves_no_access();
}

/*
 * Function name: library_hook_list_access_levels
 * Description  : Called when a player wants to list the access levels
 */
public void
library_hook_list_access_levels(void)
{
    string *access;
    string msg = "These are the following access levels:\n";

    if (query_librarian(this_player()))
        access = m_indexes(library_access_levels);
    else
	access = query_player_access(this_player());

    foreach(string level: access)
    {
	msg += sprintf("%15s /=/ %-s\n",
	    level, library_access_levels[level]);
    }

    write(msg);
}

/*
 * Function name: library_hook_remove_shelf
 * Description  : Called when a shelf is removed, should give a nice message
 * Arguments	: shelf - name of shelf being removed
 * 		  count - number of books unpublished by removal
 * Returns      : a string
 */
public string
library_hook_remove_shelf(string shelf, int count)
{
    // Status
    if (!count)
    {
        return "The shelf '" + capitalize(shelf) + "' has been " +
            "removed, no " + library_book_type + "s needed moving.\n";
    }

    return "The shelf '" + capitalize(shelf) + "' has been " +
            "removed, " + count + " " + library_book_type +
	    (count > 1 ? "s have" : " has") + " been moved to the '" +
	    library_new_book_shelf + "' shelf.\n";
}

/*
 * Function name: library_hook_modify_protected
 * Description  : Called when trying to remove a protected shelf
 * Arguments	: shelf - name of shelf we tried to modify
 * Returns      : a string
 */
public string
library_hook_modify_protected(string shelf)
{
    return "The shelf '" + capitalize(shelf) +
	"' is protected and cannot be modified.\n";
}

/*
 * Function name: library_hook_create_shelf
 * Description  : Called when successfully creating a new shelf
 * Arguments	: shelf - name of the newly created shelf
 * 		  desc - descriptions for the new shelf
 * Returns      : a string
 */
public string
library_hook_create_shelf(string shelf, string desc)
{
    return "The shelf '" + capitalize(shelf) +
	"' has been created with description '" + desc + "'.\n";
}

/*
 * Function name: library_remove_book
 * Description  : Called when a book is removed
 * Arguments    : book_id - the id of the removed book
 */
public void
library_hook_remove_book(string book_id)
{
    write("You remove " + library_book_type + " '" + book_id + "'.\n");
    say(QCTNAME(this_player()) + " moves some " + library_book_type +
        "s around on the shelves.\n");
}

/*
 * Function name: library_hook_move_book
 * Description  : Called after a book is moved from one shelf to the other
 * Arguments    : book_id - the id of the book being moved
 * 		  old_shelf - the old shelf name
 * 		  new_shelf - the new shelf name
 */
public void
library_hook_move_book(string book_id, string old_shelf, string new_shelf)
{
    write("You assigned " + library_book_type + " '" + book_id +
        "' to the '" + new_shelf + "' shelf.\n");
    say(QCTNAME(this_player()) + " moves some " + library_book_type +
        "s around on the shelves.\n");
}

/*
 * Function name: library_hook_section_book
 * Description  : Called after a book is assigned to a section
 * Arguments    : book_id - the id of the book being sectioned
 * 		  section - the section name
 * 		  prev - the previous section, if applicable
 */
public void
library_hook_section_book(string book_id, string section, string prev)
{
    if (section == "none")
    {
	write("You remove " + library_book_type + " '" + book_id +
	    "' from the '" + capitalize(section) + "' section.\n");
    }
    else
    {
	write("You assigned " + library_book_type + " '" + book_id +
	    "' to the '" + capitalize(section) + "' section.\n");
    }

    say(QCTNAME(this_player()) + " moves some " + library_book_type +
        "s around on the shelves.\n");
}

/*
 * Function name: create_library
 * Description  : Initialise the library, let it read data and such
 */
public void
create_library(void)
{
    setuid();
    seteuid(getuid());

    // Make sure we always have a save file set
    if (!strlen(library_save_file))
        library_save_file = MASTER;

    // Load the data
    load_library_data();

    // Set our new book shelf
    if (!strlen(library_new_book_shelf))
        library_new_book_shelf = "unpublished";

    // Set the librarian level
    if (!strlen(library_librarian_level))
        library_librarian_level = "librarian";

    // Make sure our new book shelf exists
    if (!SHELVES[library_new_book_shelf])
    {
        // Always add the unpublished book shelf
	// and set access level to librarian
        SHELVES[library_new_book_shelf] = ({
	    "Unpublished books", library_librarian_level, ({ }),
	});
    }

    if (!m_sizeof(library_access_levels))
    {
        // Always at the librarians level
        library_access_levels = ([
            library_librarian_level : "Librarians only",
            "normal"                : "Everyone" ]);
    }

    // Set our starting ID to a default value
    if (!library_new_book_id_start)
        library_new_book_id_start = DEF_NEW_BOOK_ID;

    // See if we have a book object
    if (!strlen(library_book_object))
        library_book_object = "/std/guild_library_book";

    // See if we have a book type
    if (!strlen(library_book_type))
        library_book_type = "book";

    // Set a default borrow limit
    if (!library_max_borrow)
	library_max_borrow = BORROW_DEFAULT;

    // Add the new books shelf to the protected list
    library_protected_shelves += ({ library_new_book_shelf });
}

/*
 * Function name: add_library_access_level
 * Description  : Add a new access level
 * Arguments    : level - the short name of the level
 *              : desc - the description of the level
 */
public void
add_library_access_level(string level, string desc)
{
    library_access_levels[lower_case(level)] = desc;
}

/*
 * Function name: add_library_protected_shelf
 * Description  : Add a new shelf to the protected list
 * Arguments    : shelf - the name of the shelf
 */
public void
add_library_protected_shelf(string shelf)
{
    library_protected_shelves += ({ lower_case(shelf) });
}

/*
 * Function name: query_protected_shelves
 * Description  : Return a list of the library protectes shelves
 * Returns      : an array with the protected shelf names
 */
public string *
query_protected_shelves(void)
{
    return secure_var(library_protected_shelves);
}

/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 * Notes	: Called externally by book object
 */
public int
query_librarian(object player)
{
    return player->query_wiz_level();
}

/*
 * Function name: query_player_access
 * Description  : Return a list of the levels that the player have access to
 * Arguments    : player - the player we want to check
 * Returns      : an array with access levels
 */
public string *
query_player_access(object player)
{
    // Add librarian access to librarians
    if (query_librarian(player))
	return ({ "normal", library_librarian_level });

    // Non wizzes get access to the normal shelf only
    return ({ "normal" });
}

/*
 * Function name: query_shelf_access
 * Description  : Query if a player can access a shelf
 * Arguments    : player - the player we want to check for
 *                 shelf - the shelf to check against
 *               book_id - or the book_id to check against
 * Returns      : 1 - Yes, 0 - No
 */
public int
query_shelf_access(object player, string shelf = "", string book_id = "")
{
    string *access = query_player_access(player);

    if (strlen(shelf) && SHELVES[shelf])
	return (member_array(SHELVES[shelf][SHELF_ACCESS], access) != -1);

    if (strlen(book_id) && BOOKS[book_id])
    {
	string shelf = BOOKS[book_id][BOOK_SHELF];
	if (sizeof(SHELVES[shelf]) &&
	    (member_array(SHELVES[shelf][SHELF_ACCESS], access) != -1))
	    return 1;
    }

    return 0;
}

/*
 * Function name: query_access_display
 * Description  : Determine who sees the access levels when listing shelves.
 * Returns      : int 0/1/2 - Display for none, all or admin only.
 */
public int
query_access_display(void)	{ return 1; }

/*
 * Function name: query_access_desc
 * Description  : Get the description of a certain access level
 * Arguments    : level - the index of the level
 * Returns      : a string with the name or 'Unknown'
 */
public string
query_access_desc(string level)
{
    // We work on lowercase levels only
    level = lower_case(level);

    // See if we have the level
    if (!library_access_levels[level])
        return "Unknown";

    // Return the name
    return library_access_levels[level];
}

/*
 * Function name: query_book_data
 * Description  : Get the information about a book
 * Arguments    : book_id - the id of the book
 * Returns      : the book data
 */
public mixed *
query_book_data(string book_id)
{
    return secure_var(BOOKS[book_id]);
}

/*
 * Function name: query_shelf_data
 * Description  : Get the information about a shelf
 * Arguments    : shelf - the name of the shelf
 * Returns      : the shelf data
 */
public mixed *
query_shelf_data(string shelf)
{
    return secure_var(SHELVES[shelf]);
}

/*
 * Function name: query_library_cmd_prefix
 * Description  : Get the library command prefix, if any
 * Returns      : the value set with set_library_cmd_prefix
 */
public string
query_library_cmd_prefix(void)
{
    return library_cmd_prefix;
}

/*
 * Function name: set_library_cmd_prefix
 * Description  : Set the library command prefix
 * Returns      : void
 * Arguments    : prefix - the prefix for library commands
 */
public void
set_library_cmd_prefix(string prefix)
{
    if (stringp(prefix) && strlen(prefix))
	library_cmd_prefix = prefix;
}

/*
 * Function name: set_library_book_object
 * Description  : Set the book object to clone when a new book is needed
 * Arguments    : file - the filename of the object
 */
public void
set_library_book_object(string file)
{
    library_book_object = file;
}

/*
 * Function name: query_library_book_object
 * Description  : Return the value set by set_library_book_object
 * Returns	: a string
 */
public string
query_library_book_object(void)
{
    return library_book_object;
}

/*
 * Function name: set_library_new_book_shelf
 * Description  : Set the shelf on which to publish new books
 * Arguments    : shelf - the name of the shelf
 */
public void
set_library_new_book_shelf(string shelf)
{
    library_new_book_shelf = shelf;
}

/*
 * Function name: query_library_new_book_shelf
 * Description  : Return the value set by set_library_new_book_shelf
 * Returns      : a string
 */
public string
query_library_new_book_shelf(void)
{
    return library_new_book_shelf;
}

/*
 * Function name: query_display_new_book_shelf
 * Description  : Determine whether or not to display the new book shelf.
 * Returns      : int 0/1/2 - Never, always or for admins only.
 */
public int
query_display_new_book_shelf(void)	{ return 1; }

/*
 * Function name: set_library_new_book_id_start
 * Description  : Set the starting id for new books
 * Arguments    : start_id - the number to start from
 */
public void
set_library_new_book_id_start(int start_id)
{
    if (start_id > MAX_NEW_BOOK_ID)
	start_id = MAX_NEW_BOOK_ID;

    library_new_book_id_start = start_id;
}

/*
 * Function name: query_library_new_book_id_start
 * Description  : Return the value set by set_library_new_book_id_start
 * Returns      : an integer
 */
public int
query_library_new_book_id_start(void)
{
    return library_new_book_id_start;
}

/*
 * Function name: set_library_librarian_level
 * Description  : Set the level of the librarian
 * Arguments    : str - the short name of the level
 */
public void
set_library_librarian_level(string str)
{
    library_librarian_level = str;
}

/*
 * Function name: query_library_librarian_level
 * Description  : Returns the level of the librarian
 * Returns      : a string
 */
public string
query_library_librarian_level(void)
{
    return library_librarian_level;
}

/*
 * Function name: set_library_book_type
 * Description  : Set the name of the books that we use (ie. book, scroll)
 * Arguments    : type - the book type
 */
public void
set_library_book_type(string type)
{
    library_book_type = type;
}

/*
 * Function name: query_library_book_type
 * Description  : See what type of books we use
 * Returns      : the value set with set_library_book_type
 * Notes	: Called externally by book object
 */
public string
query_library_book_type(void)
{
    return library_book_type;
}

/*
 * Function name: set_library_allow_new_books
 * Description  : Allow new books to be added to the library
 * Arguments    : allow - allow it or not
 */
public void
set_library_allow_new_books(int allow)
{
    library_allow_new_books = allow;
}

/*
 * Function name: query_library_allow_new_books
 * Description  : See if we allow new books to be added to the library
 * Returns	: the value set with set_library_allow_new_books
 */
public int
query_library_allow_new_books(void)
{
    return library_allow_new_books;
}

/*
 * Function name: set_library_allow_edit_direct
 * Description  : Allow books to be edited without borrowing?
 * Arguments    : allow - allow it or not
 */
public void
set_library_allow_edit_direct(int allow)
{
    library_allow_edit_direct = allow;
}

/*
 * Function name: query_library_allow_edit_direct
 * Description  : See if we allow editing books without borrowing
 * Returns	: the value set with set_library_allow_edit_direct
 */
public int
query_library_allow_edit_direct(void)
{
    return library_allow_edit_direct;
}

/*
 * Function name: set_library_allow_read_direct
 * Description  : Allow books to be read without borrowing?
 * Arguments    : allow - allow it or not
 */
public void
set_library_allow_read_direct(int allow)
{
    library_allow_read_direct = allow;
}

/*
 * Function name: query_library_allow_read_direct
 * Description  : See if we allow reading books without borrowing
 * Returns	: the value set with set_library_allow_read_direct
 */
public int
query_library_allow_read_direct(void)
{
    return library_allow_read_direct;
}

/*
 * Function name: query_library_max_borrow
 * Description  : Set how many of each book may be borrowed
 * Returns      : the value set with set_library_max_borrow
 */
public int
query_library_max_borrow(void)
{
    return library_max_borrow;
}

/*
 * Function name: set_library_max_borrow
 * Description  : Allow this many of each book to be borrowed
 * Arguments    : limit - how many
 */
public void
set_library_max_borrow(int limit)
{
    if (limit > BORROW_MAX)
	limit = BORROW_MAX;

    library_max_borrow = limit;
}

/*
 * Function name: set_library_log_file
 * Description  : Set the filename we log to
 * Arguments    : file - the filename
 */
public void
set_library_log_file(string file)
{
    library_log_file = file;
}

/*
 * Function name: query_library_log_file
 * Description  : See where our logfile resides
 * Returns      : the value set with set_library_log_file
 *                or the auto-determined value if previously unset
 */
public string
query_library_log_file(void)
{
    return library_log_file;
}

/*
 * Function name: set_library_save_file
 * Description  : Set the filename in which we store our library data
 * Arguments    : filename - the name of the file
 */
public void
set_library_save_file(string filename)
{
    library_save_file = filename;
}

/*
 * Function name: query_library_save_file
 * Description  : Get the filename in which we want to store our data
 * Returns      : a string with the filename
 */
public string
query_library_save_file(void)
{
    return library_save_file;
}

/*
 * Function name: set_library_save_path
 * Description  : Set the directory in which the books are stored. This
 *                is used both for adding new books, as well as reading
 *                existing books. Auto-append trailing slash if needed.
 * Arguments    : path - the new path
 */
public void
set_library_save_path(string path)
{
    // If no trailing slash is given, add it
    if (path[-1] != '/')
	path += "/";

    library_save_path = path;
}

/*
 * Function name: query_library_save_path
 * Description  : Get the path in which the books are stored
 * Returns      : the path with a trailing /
 */
public string
query_library_save_path(void)
{
    return library_save_path;
}

/*
 * Function name: sort_by_number
 * Description  : Make sure the books are sorted by number
 * Arguments    : bookid1 - the first book id
 *              : bookid2 - the second book id
 * Returns      : 0 if equal, -1 when 1 < 2, 1 when 2 > 1
 */
private int
sort_by_number(string bookid1, string bookid2)
{
    return atoi(bookid1) - atoi(bookid2);
}

/*
 * Function name: query_new_book_id
 * Description  : Find a new available book id
 * Arguments    : str - Find a new book id for this shelf
 * Returns      : a string with a number
 */
public string
query_new_book_id(string shelf)
{
    string new_id;

    if (strlen(shelf) && SHELVES[shelf] && sizeof(SHELVES[shelf][SHELF_BOOKS]))
	new_id = sort_array(SHELVES[shelf][SHELF_BOOKS], sort_by_number)[-1];
    else
	new_id = sprintf("%04d", library_new_book_id_start);

    // Loop through the list, increase as necessary
    while (BOOKS[new_id])
        new_id = sprintf("%04d", atoi(new_id) + 1);

    // Return the id
    return new_id;
}

/*
 * Function name: convert_library_data
 * Description  : Handle updating old library format data
 */
private void
convert_library_data(void)
{
    int version = library_data["version"];

    if (version >= VERSION)
	return;

    foreach(string shelf, mixed *data : SHELVES)
	SHELVES[shelf] += ({ ({})  });

    foreach(string book, mixed *data : BOOKS)
    {
	mixed *new = allocate(BOOK_ALLOCATE);
	new[BOOK_FILE]   = data[0];
	new[BOOK_SHELF]  = data[2];
	new[BOOK_SECTN]  = "";
	new[BOOK_LOCKED] = data[6];

	new[BOOK_TITLE]   = data[1];
	new[BOOK_TYPE]    = data[5];
	new[BOOK_SUMMARY] = data[4];
	new[BOOK_AUTHORS] = data[3];

        BOOKS[book] = new;;
    }

    library_data["version"] = VERSION;
    save_library_data();
}

/*
 * Function name: load_library_data
 * Description  : Read our datafile from disk
 */
private void
load_library_data(void)
{
    // Load the file if it's not empty
    if (file_size(library_save_file + ".o") > 0)
        library_data = restore_map(library_save_file);

    // Make sure the mapping exists
    if (!m_sizeof(library_data))
    {
        library_data = ([
	    "books"    : ([ ]),
	    "shelves"  : ([ ]),
	]);
        save_library_data();
    }
    else convert_library_data();
}

/*
 * Function name: save_library_data
 * Description  : Save our datafile to disk
 */
private void
save_library_data(void)
{
    // Check first, as we may not have data yet.
    if (file_size(library_save_file + ".o") > 0)
    {
	int sz, rotate = BACKUPS;
	string file = library_save_file + ".o";

	// Keep rotation backups.
	while(++sz)
	{
	    if (file_size(file + "." + sz) < 1)
		break;
	}

	while(--sz >= 1)
	{
	    if ((rotate != -1) && (sz >= rotate))
		continue;
	    rename(file + "." + sz, file + "." + (sz + 1));
	}

	rename(file, file + ".1");
    }

    // Save our data to disc
    save_map(library_data, library_save_file);
}

/*
 * Function name: library_add_log
 * Description  : Add a log entry if the logfile is set
 * Arguments    : msg - the message to log
 *              : extra - extra text to add to the log
 */
public varargs void
library_add_log(string msg, string extra)
{
    // Do nothing if no log is set
    if (!strlen(library_log_file))
	return;

    // Log the message
    write_file(library_log_file, sprintf("%s [%12|s] %s\n",
        ctime(time()), this_player()->query_real_name(), msg));

    // See if we have an extra message to append
    if (strlen(extra))
        write_file(library_log_file, break_string(extra, 75, 3) + "\n");
}

/*
 * Function name: library_remove_borrowed
 * Description  : Remove a book from the list of borrowed books
 * Arguments    : book_id - the id of the book being returned
 * 		  book - the book object
 * Notes	: Called externally by book object
 */
public void
library_remove_borrowed(string book_id, object book)
{
    if (!BORROWED[book_id])
	return;

    BORROWED[book_id] -= ({ book });

    if (!sizeof(BORROWED[book_id]))
	m_delkey(BORROWED, book_id);
}

/*
 * Function name: library_is_book_locked
 * Description  : See if the book is locked for editing
 * Arguments    : book_id - the id of the book
 * Returns      : 0 if not locked, 1 if locked
 * Notes	: Called externally by book object
 */
public int
library_is_book_locked(string book_id)
{
    if (BOOKS[book_id])
	return BOOKS[book_id][BOOK_LOCKED];

    return 0;
}

/*
 * Function name: library_list_cmd
 * Description  : The code for the list command
 * Arguments    : args - the command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_list_cmd(string args)
{
    if (!strlen(args))
	args = "shelves";
    else
	args = lower_case(args);

    // Print out a list of access levels
    if (args == "access")
    {
	library_hook_list_access_levels();
	return 1;
    }

    // Find the shelves we have access to
    string *access = query_player_access(this_player());
    // Find all shelves that the player can read
    string *shelves = filter(m_indexes(SHELVES),
	&operator(!=)(-1) @
	&member_array(, access) @
	&operator([])(, SHELF_ACCESS) @
	&operator([])(SHELVES, ));

    // List all shelves we have access too
    if (args == "shelves")
    {
	int admin = query_librarian(this_player()),
	    new_shelf = query_display_new_book_shelf();

	if ((new_shelf == 0) || ((new_shelf == 2) && !admin))
	    shelves -= ({ library_new_book_shelf });

        // See if they have read access
        if (!sizeof(shelves))
        {
	    library_hook_list_shelves_no_access();
            return 1;
        }

	// Loop through the shelves and display them
	library_hook_list_shelves(sort_array(shelves));
	return 1;
    }

    // See if we have this shelf
    if (SHELVES[args])
    {
	// See if we have access to the shelf
	if (member_array(args, shelves) == -1)
	{
	    library_hook_list_shelf_no_access(args);
	    return 1;
	}

	// Call the hook to have the books listed
	library_hook_list_books(args, SHELVES[args][SHELF_BOOKS]);
	return 1;
    }

    // See if we have this item
    if (BOOKS[args])
    {
	// See if we have access to the item
	string shelf = BOOKS[args][BOOK_SHELF];

	if (member_array(shelf, shelves) == -1)
	{
	    library_hook_list_shelf_no_access(args);
	    return 1;
	}

	// Call the hook to have the books listed
	library_hook_list_item(args);
	return 1;
    }

    // Find all sections available to us
    mapping sections = ([]);
    foreach(string shelf: sort_array(shelves))
    {
	string *arr = ({});
	foreach(string book: SHELVES[shelf][SHELF_BOOKS])
	{
	    if (strlen(BOOKS[book][BOOK_SECTN]) &&
		member_array(BOOKS[book][BOOK_SECTN], arr) == -1)
	    {
		arr += ({ BOOKS[book][BOOK_SECTN] });
	    }
	}

	if (sizeof(arr))
	    sections[shelf] = sort_array(arr);
    }

    if (args == "sections")
    {
	// No sections available
        if (!m_sizeof(sections))
        {
	    library_hook_list_no_sections();
            return 1;
        }

        // Loop through the sections and display them
        library_hook_list_sections(sections);
        return 1;
    }

    /* Create a reverse lookup for sections */
    mapping reverse = ([]);
    foreach(string shelf, string *sects: sections)
    {
	foreach(string sectn: sects)
	{
	    if (reverse[sectn])
		reverse[sectn] += ({ shelf });
	    else
		reverse[sectn] = ({ shelf });
	}
    }

    // See if we have this section
    if (reverse[args])
    {
        // Loop through the sections and display them
        library_hook_list_section_items(args, reverse[args]);
        return 1;
    }

    notify_fail(library_hook_list_none(args));
    return 0;
}

/*
 * Function name: add_shelf
 * Description  : Add a new shelf to the list of available shelves, default
 *                access level will be library_librarian_level
 * Arguments    : shelf - the short name of the shelf
 *              : desc - the description of the shelf
 * Returns      : a string with the result message
 */
private string
add_shelf(string shelf, string desc)
{
    int len;

    // We only use lowercase shelf names
    shelf = lower_case(shelf);
    len = strlen(shelf);

    if (len < MINLEN_ALL || len > MAXLEN_SHELF)
	return library_hook_fail_length("Shelf Name", MAXLEN_SHELF);

    len = strlen(desc);
    if (len < MINLEN_ALL || len > MAXLEN_DESC)
	return library_hook_fail_length("Shelf Description", MAXLEN_DESC);

    // See if the shelf already exists
    if (SHELVES[shelf])
	return library_hook_shelf_exists(shelf);

    // Add the shelf
    SHELVES[shelf] = allocate(SHELF_ALLOCATE);
    SHELVES[shelf][SHELF_DESC] = desc;
    SHELVES[shelf][SHELF_ACCESS] = library_librarian_level;
    SHELVES[shelf][SHELF_BOOKS] = ({ });
    SHELVES[shelf][SHELF_SECTN] = ({ });

    // Log
    library_add_log("Shelf '" + capitalize(shelf) + "' added.",
        "Description '" + desc + "'");

    // Store & Return
    save_library_data();
    return library_hook_create_shelf(shelf, desc);
}

/*
 * Function name: remove_shelf
 * Description  : Remove a shelf from the available shelf list, all books
 *                will be moved to the unpublished shelf.
 * Arguments    : shelf - the short name of the shelf
 * Returns      : a string with the result
 */
private string
remove_shelf(string shelf)
{
    // We only use lowercase shelf names
    shelf = lower_case(shelf);

    // See if the shelf already exists
    if (!strlen(shelf) || !SHELVES[shelf])
	return library_hook_shelf_none(shelf);


    // See if we have access to the shelf
    if (!query_shelf_access(this_player(), shelf))
    {
	library_hook_list_shelf_no_access(shelf);
	return "";
    }

    // See if this is a protected book shelf
    if (member_array(shelf, library_protected_shelves) != -1)
	return library_hook_modify_protected(shelf);

    int book_count = 0;

    // Find all books on the shelf
    foreach(string book_id : SHELVES[shelf][SHELF_BOOKS])
    {
	// Move the book to the unpublished shelf
	BOOKS[book_id][BOOK_SHELF] = library_new_book_shelf;
	book_count++;
    }

    // Remove the shelf
    m_delkey(SHELVES, shelf);

    // Log
    library_add_log("Removed shelf '" + capitalize(shelf) + "'");

    // Save & Return
    save_library_data();
    return library_hook_remove_shelf(shelf, book_count);
}

/*
 * Function name: change_shelf_description
 * Description  : Give a shelf a new description
 * Arguments    : shelf - the name of the shelf
 *              : desc - the new description of the shelf
 * Returns      : a string with the result
 */
private string
change_shelf_description(string shelf, string desc)
{
    // We only use lower case shelf names
    shelf = lower_case(shelf);

    // See if the shelf already exists
    if (!SHELVES[shelf])
	return library_hook_shelf_none(shelf);

    // See if we have access to the shelf
    if (!query_shelf_access(this_player(), shelf))
    {
	library_hook_list_shelf_no_access(shelf);
	return "";
    }

    int len = strlen(desc);
    if (len < MINLEN_ALL || len > MAXLEN_DESC)
	return library_hook_fail_length("Shelf Description", MAXLEN_DESC);

    // Describe the shelf
    SHELVES[shelf][SHELF_DESC] = desc;

    // Log
    library_add_log("Description of '" + capitalize(shelf) +
        "' changed.", "New Desc '" + desc + "'");

    // Save & Return
    save_library_data();
    return library_hook_change_shelf_desc(shelf, desc);
}

/*
 * Function name: rename_book
 * Description  : Give a book a new title
 * Arguments    : book - the name of the book
 *              : title - the new name of the shelf
 * Returns      : a string with the result
 */
private string
rename_book(string book, string title)
{
    // Look for this book
    if (!BOOKS[book])
	return library_hook_book_none(book);

    // See if we have access to the book
    if (!query_shelf_access(this_player(), "", book))
	return library_hook_book_none(book);

    int len = strlen(title);
    if (len < MINLEN_ALL || len > MAXLEN_TITLE)
	return library_hook_fail_length("Title", MAXLEN_TITLE);

    library_add_log("New title '" + title + "' for '" + book + "'");

    // Rename the book otherwise
    BOOKS[book][BOOK_TITLE] = title;

    // Save & Return
    save_library_data();
    return library_hook_rename_book(book, title);
}

/*
 * Function name: rename_shelf
 * Description  : Give a shelf a new description
 * Arguments    : shelf - the name of the shelf
 *              : new_name - the new name of the shelf
 * Returns      : a string with the result
 */
private string
rename_shelf(string shelf, string new_name)
{
    // We only use lowercase shelf names
    shelf = lower_case(shelf);
    new_name = lower_case(new_name);

    // See if the shelf already exists
    if (!SHELVES[shelf])
	return library_hook_shelf_none(shelf);

    // See if we have access to the shelf
    if (!query_shelf_access(this_player(), shelf))
    {
	library_hook_list_shelf_no_access(shelf);
	return "";
    }

    // See if this is a protected book shelf
    if (member_array(shelf, library_protected_shelves) != -1)
	return library_hook_modify_protected(shelf);

    // See if this is the same
    if (new_name == shelf)
	return library_hook_fail_same(shelf);

    // See if the shelf already exists
    if (SHELVES[new_name])
	return library_hook_shelf_exists(new_name);

    // See if the name is too long
    int len = strlen(new_name);
    if (len < MINLEN_ALL || len > MAXLEN_SHELF)
	return library_hook_fail_length("Shelf Name", MAXLEN_SHELF);

    // Rename the shelf
    SHELVES[new_name] = SHELVES[shelf];
    m_delkey(SHELVES, shelf);

    // Find all books on the shelf and move them to the new one
    foreach(string book_id : SHELVES[new_name][SHELF_BOOKS])
    {
	// Move the book to the renamed shelf
	BOOKS[book_id][BOOK_SHELF] = new_name;
    }

    // Log
    library_add_log("Renamed '" + shelf + "' to '" + new_name + "'");

    // Save & Return
    save_library_data();
    return library_hook_rename_shelf(shelf, new_name);
}

/*
 * Function name: change_shelf_access
 * Description  : Allow us to alter the access level of a shelf
 * Arguments    : shelf - the shelf we want to alter
 *              : level - the new access level
 * Returns      : a string with the result
 */
private string
change_shelf_access(string shelf, string level)
{
    // We only use lowercase shelf names
    shelf = lower_case(shelf);
    level = lower_case(level);

    // See if the shelf already exists
    if (!SHELVES[shelf])
	return library_hook_shelf_none(shelf);

    // See if this is the same
    if (SHELVES[shelf][SHELF_ACCESS] == level)
	return library_hook_fail_same(shelf);

    // See if we have this level
    if (!library_access_levels[level])
    {
        // Return the available access levels
        string ret = "No such access level '" +
	    level + "', known levels are:\n\n";

	foreach(string level, string desc : library_access_levels)
            ret += sprintf("%20s - %s\n", level, desc);

        return ret + "\n";
    }

    // See if we have access to the shelf
    if (!query_shelf_access(this_player(), shelf))
    {
	library_hook_list_shelf_no_access(shelf);
	return "";
    }

    // Alter the access level
    SHELVES[shelf][SHELF_ACCESS] = level;

    // Log
    library_add_log("Access of '" + shelf + "' for '" + level + "'");

    // Save & Return
    save_library_data();
    return library_hook_access_change(shelf, level);
}

/*
 * Function name: add_new_book
 * Description  : Add a new book to the shelves
 * Arguments    : title - the title of the book
 *              : contents - the contents of the book
 *              : summary - the summary fort the book
 *              : author - the author of the book
 *              : shelf (optional) - the shelf on which to place the book
 *              : filename (optional) - which filename to use for storing the
 *              :       content
 *              : book_id (optional) - the id by which the book is known
 * Returns      : a filename which contains the contents or 0 on failure
 * Notes	: Called externally by book object
 */
public varargs int
add_new_book(string title, string contents, string summary,
             string author, string shelf = "", string filename = "",
	     string book_id = "")
{
    // We cannot add books without a valid save path
    if (!strlen(library_save_path))
        return 0;

    // Set the value to the new book shelf if empty
    if (!strlen(shelf))
        shelf = library_new_book_shelf;

    // Find ourselves a filename
    if (!strlen(filename))
        filename = sprintf("%s%d", author, time());

    // Generate a new book id
    if (!strlen(book_id))
        book_id = query_new_book_id(shelf);

    // Make sure the path exists
    if (file_size(library_save_path) != -2)
        mkdir(library_save_path);

    // Erase the file first if it already exists
    string filepath = library_save_path + filename;
    if (file_size(filepath) > 0)
        rm(filepath);

    // Write the contents to the file
    write_file(filepath, contents);

    // Create the book entry
    BOOKS[book_id] = allocate(BOOK_ALLOCATE);
    BOOKS[book_id][BOOK_FILE] = filename;
    BOOKS[book_id][BOOK_SHELF] = shelf;
    BOOKS[book_id][BOOK_SECTN] = "";
    BOOKS[book_id][BOOK_TITLE] = title;
    BOOKS[book_id][BOOK_TYPE] = library_book_type;
    BOOKS[book_id][BOOK_SUMMARY] = summary;
    BOOKS[book_id][BOOK_AUTHORS] = ({ author });

    // Add the book to the shelf
    SHELVES[shelf][SHELF_BOOKS] += ({ book_id });

    // Sort the list of books
    string *tmp = sort_array(SHELVES[shelf][SHELF_BOOKS], sort_by_number);
    SHELVES[shelf][SHELF_BOOKS] = tmp;

    // Log the addition
    library_add_log("Added book '" + book_id + "'",
        "Filename '" + filename + "'\n" +
        "Author   '" + author + "'\n" +
        "Title    '" + title + "'\n" +
        "Shelf    '" + shelf + "'");

    // Store everything
    save_library_data();
    return atoi(book_id);
}

/*
 * Function name: update_book
 * Description  : Update the contents of a book
 * Arguments    : book_id - the id of the book
 *              : text - the new contents of the book
 *              : title - the new title of the book
 *              : summary - the new summary for the book
 *              : type - the new type for the book
 *              : authors - the new authors of the book
 * Returns      : 0 on failure, 1 on success
 * Notes	: Called externally by book object
 */
public int
update_book(string book_id, string text = "", string title = "",
            string summary = "", string type = "", string *authors = ({ }))
{
    // See if we find this book
    if (!BOOKS[book_id])
        return 0;

    // We cannot add books without a valid save path
    if (!strlen(library_save_path))
        return 0;

    // Make sure the path exists
    if (file_size(library_save_path) != -2)
        mkdir(library_save_path);

    string logtxt = "Updated contents of '" + book_id + "':\n";

    if (strlen(title))
    {
	// Update the book title
	BOOKS[book_id][BOOK_TITLE] = title;
        logtxt += "\tTitle '" + title + "'";
    }

    if (strlen(type))
    {
	// Update the book type
	BOOKS[book_id][BOOK_TYPE] = type;
        logtxt += "\tType '" + type + "'";
    }

    if (strlen(summary))
    {
	// Update the book type
	BOOKS[book_id][BOOK_SUMMARY] = summary;
        logtxt += "\tSummary '" + summary + "'";
    }

    if (sizeof(authors))
    {
	// Update the book type
	BOOKS[book_id][BOOK_AUTHORS] = authors;
        logtxt += "\tAuthors '" + COMPOSITE_WORDS_WITH(authors, "and") + "'";
    }

    // We need to update the book contents
    if (strlen(text))
    {
	// Fetch our full filename path
	string filepath = library_save_path + BOOKS[book_id][BOOK_FILE];

	// Erase the file first if it already exists
	if (file_size(filepath) > 0)
	    rm(filepath);

	// Write the contents to the file
	write_file(filepath, text);
        logtxt += "\tContents modified";
    }

    // Log the updates
    library_add_log(logtxt);

    // Store everything
    save_library_data();
    return 1;
}

/*
 * Function name: library_configure_book
 * Description  : Configure a book before giving to player
 * Arguments    : book - the book object
 *                book_id - the id of the book (none for blanks)
 */
public varargs void
library_configure_book(object book, string book_id = "")
{
    book->set_library(this_object());

    if (strlen(book_id))
    {
	book->set_book_id(book_id);
	book->set_type(BOOKS[book_id][BOOK_TYPE]);
	book->set_title(BOOKS[book_id][BOOK_TITLE]);
	book->set_authors(BOOKS[book_id][BOOK_AUTHORS]);
	book->set_summary(BOOKS[book_id][BOOK_SUMMARY]);
	book->set_filename(library_save_path + BOOKS[book_id][BOOK_FILE]);
    }
    else
    {
	// Blank books.
	book->set_type(library_book_type);
	book->set_name(library_book_type);
	book->add_name(LIBRARY_BOOK + "_blank");
	book->set_adj("blank");
	book->set_long("This is a blank "+ library_book_type +
	    " that is just waiting to be written upon!\n");
    }
}

/*
 * Function name: give_book_to_player
 * Description  : Called after a delay when a player wants to get a book
 * Arguments    : player - the name of the player
 *                book_id - the id of the book
 */
public void
give_book_to_player(object player, string book_id)
{
    object book;

    // Remove alarm prop
    player->remove_prop(BORROW_ALARM_PROP);

    // Don't do anything if the player isnt here anymore
    if (environment(player) != this_object())
        return;

    // See if we have the book
    if (BOOKS[book_id])
    {
        string shelf = BOOKS[book_id][BOOK_SHELF];

        // See if the player has access to the book
        if (member_array(SHELVES[shelf][SHELF_ACCESS],
		query_player_access(player)) == -1)
        {
	    library_hook_book_not_found(player, 1);
	    return;
	}

	// Check if the book is available
	int count = sizeof(BORROWED[book_id]);
	if (count >= library_max_borrow)
	{
	    library_hook_book_not_found(player);
	    return;
	}

	// We have the book, player has access, make it
	book = clone_object(library_book_object);
	library_configure_book(book, book_id);
    }

    // No book
    if (!objectp(book))
    {
	library_hook_book_not_found(player, 1);
	return;
    }

    if (book->move(player))
	book->move(player, 1);

    // Set the book as borrowed
    if (!BORROWED[book_id])
	BORROWED[book_id] = ({ book });
    else
	BORROWED[book_id] += ({ book });

    // Messages
    library_hook_receive_book(player, book);
}

/*
 * Function name: library_borrow_cmd
 * Description  : The code for the 'borrow' command
 * Arguments    : args - the command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_borrow_cmd(string args)
{
    int alarm;

    // Syntax check
    if (!strlen(args))
    {
        notify_fail("Borrow what " + library_book_type + "?\n");
        return 0;
    }

    if (this_player()->query_prop(BORROW_ALARM_PROP))
    {
	library_hook_already_borrowing();
	return 1;
    }

    // Set the alarm
    alarm = set_alarm(BORROW_DELAY, 0.0,
	&give_book_to_player(this_player(), args));

    this_player()->add_prop(BORROW_ALARM_PROP, alarm);

    // Write a message
    library_hook_begin_borrow();
    return 1;
}

/*
 * Function name: library_blank_cmd
 * Description  : Allow the person executing the command to get a new book
 *              : so that they can submit new things to the library
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_blank_cmd(string args)
{
    if (!strlen(args) || args != library_book_type)
    {
        notify_fail("Blank what? A blank " + library_book_type + "?\n");
        return 0;
    }

    if (present(LIBRARY_BOOK + "_blank", this_player()))
    {
	library_hook_borrow_blank_fail();
	return 1;
    }

    object book = clone_object(library_book_object);
    library_configure_book(book, "");

    if (book->move(this_player()))
	book->move(this_player(), 1);

    // Log
    library_add_log("Received blank book.");

    // Messages
    library_hook_borrow_blank();
    return 1;
}

/*
 * Function name: library_renumber_cmd
 * Description  : Assign a new number to a book
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_renumber_cmd(string args)
{
    int num;
    string old_id, new_id;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "%w [to] %w", old_id, new_id) ||
	!strlen(old_id) || !strlen(new_id))
    {
        notify_fail("Renumber <what> to <what>?\n");
        return 0;
    }

    // See if the old id exists
    if (!BOOKS[old_id])
    {
        notify_fail(library_hook_book_none(old_id));
        return 0;
    }

    // See if we have access to the book
    if (!query_shelf_access(this_player(), "", old_id))
    {
        notify_fail(library_hook_book_none(old_id));
	return 0;
    }

    // Do not allow locked books to be altered
    if (library_is_book_locked(old_id))
    {
	library_hook_book_locked(old_id);
        return 1;
    }

    // See if they are equal (add 0's to make it at least 4 chars)
    new_id = sprintf("%04s", new_id);
    if (new_id == old_id)
    {
        write(library_hook_fail_same(old_id));
        return 1;
    }

    // Convert to integer
    num = atoi(new_id);

    // Check if the new id is valid
    if ((num > MAX_SET_BOOK_ID) || (num < DEF_NEW_BOOK_ID))
    {
	write("The new book id is invalid, "+
	    "try a number between "+ DEF_NEW_BOOK_ID +
	    " and "+ MAX_SET_BOOK_ID +".\n");
	return 1;
    }

    // Convert to string
    new_id = num + "";

    // See if the new number exists
    if (BOOKS[new_id])
    {
	write(library_hook_book_exists(new_id));
        return 1;
    }

    // Change everything
    BOOKS[new_id] = BOOKS[old_id];
    m_delkey(BOOKS, old_id);

    // Update cross-reference in shelf
    string shelf = BOOKS[new_id][BOOK_SHELF];
    int idx = member_array(old_id, SHELVES[shelf][SHELF_BOOKS]);
    SHELVES[shelf][SHELF_BOOKS][idx] = new_id;

    // Sort the list of books
    string *tmp = sort_array(SHELVES[shelf][SHELF_BOOKS], sort_by_number);
    SHELVES[shelf][SHELF_BOOKS] = tmp;

    // Store everything
    save_library_data();

    // Update borrowed books
    if (BORROWED[old_id])
    {
	BORROWED[old_id]->set_book_id(new_id);
	BORROWED[new_id] = BORROWED[old_id];
	m_delkey(BORROWED, old_id);
    }

    library_add_log("Renumbered '" + old_id + "' to '" + new_id + "'");
    library_hook_renumber_book(old_id, new_id);
    return 1;
}

/*
 * Function name: library_section_cmd
 * Description  : Assign a book to a section
 * Arguments    : args - command line arguments
 * Return       : 0 on failure, 1 on success
 */
public int
library_section_cmd(string args)
{
    string book_id, section, prev;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "%w [to] %s", book_id, section) ||
	!strlen(book_id) || !strlen(section))
    {
        notify_fail("Assign which " +
	    library_book_type + " to what section?\n");
        return 0;
    }

    // See if the book exists
    if (!BOOKS[book_id])
    {
	notify_fail(library_hook_book_none(book_id));
        return 0;
    }

    // See if we have access to the book
    if (!query_shelf_access(this_player(), "", book_id))
    {
        notify_fail(library_hook_book_none(book_id));
	return 0;
    }

    // Convert lower case
    section = lower_case(section);
    int len = strlen(section);

    // See if the name is too long
    if (len < MINLEN_ALL || len > MAXLEN_SECTN)
    {
	write(library_hook_fail_length("Section Name", MAXLEN_SECTN));
	return 1;
    }

    // Are we already in the section?
    prev = BOOKS[book_id][BOOK_SECTN];
    if (prev == section)
    {
	write(library_hook_fail_same(section));
	return 1;
    }

    // See if the shelf is protected
    if (BOOKS[book_id][BOOK_SHELF] == library_new_book_shelf)
    {
	write(library_hook_modify_protected(library_new_book_shelf));
        return 1;
    }

    // Do not allow locked books to be altered
    if (library_is_book_locked(book_id))
    {
	library_hook_book_locked(book_id);
        return 1;
    }

    // Assign the book to the section
    BOOKS[book_id][BOOK_SECTN] = (section == "none" ? "" : section);

    // Log
    library_add_log("Sectioned '" + book_id + "' to '" + section + "'");

    save_library_data();
    library_hook_section_book(book_id, section, prev);
    return 1;
}

/*
 * Function name: library_assign_cmd
 * Description  : Assign a book to a shelf
 * Arguments    : args - command line arguments
 * Return       : 0 on failure, 1 on success
 */
public int
library_assign_cmd(string args)
{
    string book_id, shelf, old_shelf;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "%w [to] %s", book_id, shelf) ||
	!strlen(book_id) || !strlen(shelf))
    {
        notify_fail("Assign which " +
	    library_book_type + " to what shelf?\n");
        return 0;
    }

    // See if the book exists
    if (!BOOKS[book_id])
    {
	notify_fail(library_hook_book_none(book_id));
        return 0;
    }

    // See if we have access to the book
    if (!query_shelf_access(this_player(), "", book_id))
    {
        notify_fail(library_hook_book_none(book_id));
	return 0;
    }

    // Do not allow locked books to be altered
    if (library_is_book_locked(book_id))
    {
	library_hook_book_locked(book_id);
        return 1;
    }

    // Convert input to lower case
    shelf = lower_case(shelf);

    // See if the shelf exists
    if (!SHELVES[shelf])
    {
	write(library_hook_shelf_none(shelf));
        return 1;
    }

    // See if the book is already on that shelf
    if (BOOKS[book_id][BOOK_SHELF] == shelf)
    {
        write("The " + library_book_type +
	    " is already on that shelf.\n");
        return 1;
    }

    // See if we have access to the new shelf
    if (!query_shelf_access(this_player(), shelf))
    {
	library_hook_list_shelf_no_access(shelf);
	return 1;
    }

    // Remove the book from the old shelf
    old_shelf = BOOKS[book_id][BOOK_SHELF];
    SHELVES[old_shelf][SHELF_BOOKS] -= ({ book_id });

    // Assign the book to the shelf
    BOOKS[book_id][BOOK_SHELF] = shelf;
    SHELVES[shelf][SHELF_BOOKS] += ({ book_id });

    // Sort the list of books
    sort_array(SHELVES[shelf][SHELF_BOOKS], sort_by_number);

    // Log
    library_add_log("Moved '" + book_id + "' to '" + shelf + "'");

    save_library_data();
    library_hook_move_book(book_id, old_shelf, shelf);
    return 1;
}

/*
 * Function name: library_create_cmd
 * Description  : Allow us to create a shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_create_cmd(string args)
{
    string name, desc;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "[shelf] %s 'as' / 'with' [desc] / [description] %s",
	    name, desc) || !strlen(name) || !strlen(desc))
    {
        notify_fail("Create which shelf with what description?\n");
        return 0;
    }

    // Do the renaming
    write(add_shelf(name, desc));
    return 1;
}

/*
 * Function name: library_rename_cmd
 * Description  : Allow us to rename a shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_rename_cmd(string args)
{
    string  from, to;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    if (!strlen(args) ||
	sscanf(args, "%s to %s", from, to) != 2)
    {
        notify_fail("Rename which shelf or book?\n");
        return 0;
    }

    // Access checks are done in the sub-routines

    if (BOOKS[from])
    {
        write(rename_book(from, to));
        return 1;
    }

    write(rename_shelf(from, to));
    return 1;
}

/*
 * Function name: library_change_cmd
 * Description  : Allow us to change the description of a shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_change_cmd(string args)
{
    string name, desc;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "[shelf] %s 'to' %s", name, desc) ||
	!strlen(name) || !strlen(desc))
    {
        notify_fail("Change the description of "+
	    "which shelf to be what?\n");
        return 0;
    }

    // Access checks doen in sub-routine.

    // Do the renaming
    write(change_shelf_description(name, desc));
    return 1;
}

/*
 * Function name: library_access_cmd
 * Description  : Allow us to change the access level of a shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_access_cmd(string args)
{
    string name, level;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "[shelf] %s 'to' [level] %s", name, level) ||
	!strlen(name) || !strlen(level))
    {
        notify_fail("Change access on which shelf to what level?\n");
        return 0;
    }

    // Access checks doen in sub-routine.

    // Do the renaming
    write(change_shelf_access(name, level));
    return 1;
}

/*
 * Function name: library_remove_cmd
 * Description  : Allow us to remove a shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_remove_cmd(string args)
{
    string name, filename, shelf;

    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    // Syntax check
    if (strlen(args) &&
	parse_command(args, ({ }), "'shelf' %s", name))
    {
	if (!strlen(name))
	{
	    notify_fail("Remove which shelf?\n");
	    return 0;
	}

        // Remove the shelf
        write(remove_shelf(name));
        return 1;
    }

    if (!strlen(args) || !parse_command(args, ({ }),
	    "[" + library_book_type + "] %s", name) || !strlen(name))
    {
        notify_fail("Remove what " + library_book_type + "?\n");
        return 0;
    }

    // See if the book exists
    if (!BOOKS[name])
    {
        notify_fail(library_hook_book_none(name));
        return 0;
    }

    // See if we have access to the book
    if (!query_shelf_access(this_player(), "", name))
    {
        write(library_hook_book_none(name));
	return 1;
    }

    // Log
    library_add_log("Removed book '" + name + "'");

    filename = BOOKS[name][BOOK_FILE];

    // Make sure our obsolete path exists
    if (file_size(library_save_path + "obsolete") != -2)
        mkdir(library_save_path + "obsolete");

    // Erase the file if it already exists
    if (file_size(library_save_path + "obsolete/" + filename) > 0)
        rm(library_save_path + "obsolete/" + filename);

    // Move the book to the obsolete dir
    rename(library_save_path + filename,
	library_save_path + "obsolete/" + filename);

    // Remove the book
    shelf = BOOKS[name][BOOK_SHELF];
    SHELVES[shelf][SHELF_BOOKS] -= ({ name });
    m_delkey(BOOKS, name);

    // Store everything
    save_library_data();
    library_hook_remove_book(name);
    return 1;
}

/*
 * Function name: library_help
 * Description  : Get the help based on this_player()'s permissions
 * Returns      : a string
 */
public string
library_help(void)
{
    // Header
    string result = "The following library commands are "+
	"available to you:\n";

    // Regular commands
    result += "\n"+
	" o list [shelf]     - List the various shelves\n" +
	" o list sections    - List the available sections\n"+
	" o list access      - List the access levels\n"+
	" o list <id>        - List the "+ library_book_type +" with <id>\n" +
	" o list <section>   - List all "+ library_book_type +"s in <section>\n\n";

    if (query_library_allow_read_direct())
    {
	result += " o read <id>        - Read the " +
	    library_book_type +" with id <number>\n";
    }

    result += " o borrow <"+ library_book_type +">    - Borrow the " +
		library_book_type +" with id <number>\n";

    // Give the librarian extra options
    if (query_librarian(this_player()))
    {
        result += "\nAs a Librarian, you also have these commands:\n\n"+
	    " * edit <" + library_book_type + " id>\n" +
            " * remove " + library_book_type + " <" +
	    	library_book_type + " id>\n" +
	    " * renumber <old id> to <new id>\n" +
            " * rename <" + library_book_type + " id> to <new title>\n" +
            " * assign <" + library_book_type + " id> to <shelf name>\n" +
            " * section <" + library_book_type + " id> to <section name>\n" +
	    "\n" +
            " * create shelf <shelf name> with <description>\n" +
            " * rename <shelf name> to <new name>\n" +
            " * change <shelf name> to <new desc>\n" +
            " * access <shelf name> to <access level>\n" +
            " * remove shelf <shelf name>\n";
    }

    // Gives more help for wizards
    if (this_player()->query_wiz_level())
    {
        result += "\n"+
	    " % lock <" + library_book_type + " id>\n" +
            " % unlock <" + library_book_type + " id>\n";
    }

    // Add text when we allow new books
    if (library_allow_new_books)
    {
        result += "\n" +
	    "You are allowed to write your own " + library_book_type +
	    "s.\nJust type 'blank " + library_book_type +
	    "' and 'submit " + library_book_type +
	    "' when done.\n";
    }

    if (library_cmd_prefix)
    {
	result += "\n** In case of command conflicts, "+
	    "try prefixing commands with \"" +
	    library_cmd_prefix +"\". **\n";
    }

    return result;
}

/*
 * Function name: library_lock_cmd
 * Description  : Allows an immortal to lock a book from editing
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_lock_cmd(string args)
{
    string name;

    // Do a wizard check
    if (!this_player()->query_wiz_level())
        return 0;

    // Syntax check
    if (!strlen(args) || !parse_command(args, ({ }),
	    "[" + library_book_type + "] %s", name) || !strlen(name))
    {
        notify_fail(capitalize(query_verb()) + " what " +
            library_book_type + "?\n");
        return 0;
    }

    // See if the book exists
    if (!BOOKS[name])
    {
	notify_fail(library_hook_book_none(name));
        return 0;
    }

    // Check if we want to lock or unlock
    if (query_verb() == "lock")
    {
        if (BOOKS[name][BOOK_LOCKED])
        {
            write(capitalize(library_book_type) + " '" + name +
                "' was already locked.\n");
        }
        else
        {
            write("Locked " + library_book_type + " '" + name +
                "' for editing.\n");

            // Log
            library_add_log("Locked '" + name + "' for editing.");

            // Modify and save
            BOOKS[name][BOOK_LOCKED] = 1;
            save_library_data();
        }

	return 1;
    }

    // Check for unlocked books
    if (!BOOKS[name][BOOK_LOCKED])
    {
        write(capitalize(library_book_type) + " '" +
	    name + "' was not locked.\n");
    }
    else
    {
        write("Allowed editing for " +
	    library_book_type + " '" + name + "'\n");

        // Log
        library_add_log("Unlocked '" + name + "' for editing.");

        // Modify and save
        BOOKS[name][BOOK_LOCKED] = 0;
        save_library_data();
    }
    return 1;
}

/*
 * Function name: library_read_cmd
 * Description  : Allows players to read directly from the shelf
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_read_cmd(string args)
{
    if (!strlen(args))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    // See if the book exists
    if (!BOOKS[args])
    {
        notify_fail(library_hook_book_none(args));
        return 0;
    }

    // See if the player has access to the book
    if (!query_shelf_access(this_player(), "", args))
    {
	library_hook_book_not_found(this_player(), 1);
	return 1;
    }

    if (!library_allow_read_direct)
    {
	library_hook_no_read_direct();
	return 1;
    }

    // We have access, check that it is available
    if (sizeof(BORROWED[args]) <= library_max_borrow)
    {
	library_hook_read_direct(args,
	    read_file(library_save_path + BOOKS[args][BOOK_FILE]));
	return 1;
    }

    library_hook_book_not_found(this_player());
    return 1;
}

/*
 * Function name: done_editing
 * Description  : Called after editing is complete
 * Arguments    : book_id - the book being edited
 *              : text - the text of the book
 */
public void
done_editing(string book_id, string text)
{
    // Remove the book from the borrowed list
    m_delkey(BORROWED, book_id);

    // See if we were locked out
    if (BOOKS[book_id][BOOK_LOCKED] == 1)
    {
	library_hook_edit_direct_fail(book_id);
	return;
    }

    // Remove temporary lock.
    BOOKS[book_id][BOOK_LOCKED] = 0;

    // Aborted
    if (!strlen(text))
    {
        write("Aborted.\n");
        return;
    }

    // Update the text
    update_book(book_id, text);
    library_hook_edit_direct(book_id);
}

/*
 * Function name: library_edit_cmd
 * Description  : Allows direct editing of a scroll
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
library_edit_cmd(string args)
{
    // Librarian check
    if (!query_librarian(this_player()))
        return 0;

    if (!strlen(args))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    // See if the book exists
    if (!BOOKS[args])
    {
	notify_fail(library_hook_book_none(args));
        return 0;
    }

    // See if the player has access to the book
    if (!query_shelf_access(this_player(), "", args))
    {
	library_hook_book_not_found(this_player(), 1);
	return 1;
    }

    // Is direct editing allowed?
    if (!library_allow_edit_direct)
    {
	library_hook_no_edit_direct();
	return 1;
    }

    // Make sure it isn't borrowed
    if (BORROWED[args])
    {
	library_hook_book_not_found(this_player());
	return 1;
    }

    // See if this book is locked from editing
    if (library_is_book_locked(args))
    {
	library_hook_book_locked(args);
        return 1;
    }

    // Temporarily lock the book.
    BOOKS[args][BOOK_LOCKED] = -1;

    // Set the book as borrowed to prevent others from editing
    BORROWED[args] = allocate(library_max_borrow);

    // Start editing
    clone_object(EDITOR)->edit(&done_editing(args),
	read_file(library_save_path + BOOKS[args][BOOK_FILE]));

    return 1;
}

#define LIBRARY_CMD(x, y) add_action(x, y); \
    if (prefix) add_action(x, library_cmd_prefix + y);

/*
 * Function name: init_library
 * Description  : Add the library commands to the player
 */
public void
init_library(void)
{
    int prefix = strlen(library_cmd_prefix);

    LIBRARY_CMD( library_borrow_cmd, "borrow" );
    LIBRARY_CMD( library_borrow_cmd, "borrow" );
    LIBRARY_CMD(   library_list_cmd, "list"   );

    // Allow reading w/out borrowing
    if (query_library_allow_read_direct())
    {
	LIBRARY_CMD(   library_read_cmd, "read" );
	LIBRARY_CMD(   library_read_cmd, "mread");
    }

    // Allow the addition of books
    if (query_library_allow_new_books())
    {
        LIBRARY_CMD( library_blank_cmd, "blank" );
    }

    // Give the librarian extra options
    if (query_librarian(this_player()))
    {
	LIBRARY_CMD(   library_assign_cmd, "assign"   );
	LIBRARY_CMD(  library_section_cmd, "section"  );
	LIBRARY_CMD(   library_create_cmd, "create"   );
	LIBRARY_CMD(   library_rename_cmd, "rename"   );
	LIBRARY_CMD(   library_change_cmd, "change"   );
	LIBRARY_CMD(   library_access_cmd, "access"   );
	LIBRARY_CMD(   library_remove_cmd, "remove"   );
	LIBRARY_CMD( library_renumber_cmd, "renumber" );
	LIBRARY_CMD(     library_edit_cmd, "edit"     );
    }

    // Only wizards get these commands
    if (this_player()->query_wiz_level())
    {
	LIBRARY_CMD( library_lock_cmd, "lock"   );
	LIBRARY_CMD( library_lock_cmd, "unlock" );
    }
}

/*
 * Function name: library_leave_inv
 * Description  : Called when someone leaves our inventory (the room)
 * Arguments    : ob - the object leaving
 *              : to - where are we leaving to
 */
public void
library_leave_inv(object ob, object to)
{
    // Check for living
    if (!living(ob))
	return;

    // Find all library books
    object *obs = filter(deep_inventory(ob), &->id(LIBRARY_BOOK));

    // Make a librarian run after the unreturned books
    if (sizeof(obs))
    {
        library_hook_leave_with_books(ob, obs);
	obs->return_library_book();
	obs->remove_object();
    }

    int alarm = ob->query_prop(BORROW_ALARM_PROP);
    if (alarm > 0)
    {
	remove_alarm(alarm);
	ob->remove_prop(BORROW_ALARM_PROP);
        library_hook_stop_borrowing(ob);
    }
}

/*
 * Function name: prevent_leave_with_books
 * Description  : A function that can be used in add_exit, it will prevent
 *              : a player from leaving while carrying books.
 * Returns      : 0 when allowed to leave, 1 when blocked
 */
public int
prevent_leave_with_books(void)
{
    // Find all library books
    object *obs = filter(deep_inventory(this_player()),
	&->id(LIBRARY_BOOK));

    // Stop with books
    if (sizeof(obs))
    {
        library_hook_stop_leave(this_player(), obs);
        return 1;
    }

    int alarm = this_player()->query_prop(BORROW_ALARM_PROP);
    if (alarm > 0)
    {
	remove_alarm(alarm);
	this_player()->remove_prop(BORROW_ALARM_PROP);
        library_hook_stop_borrowing(this_player());
    }

    return 0;
}
