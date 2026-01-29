#pragma strict_types
/*
 *  /d/Avenir/inherit/library_book.c
 *  Based on: /std/guild_library_book.c
 *
 *  Book that's being used in the /lib/guild_library.c, can be
 *  inherited to create a custom book. Use set_library_book_object
 *  in the library to use it.
 *
 *  Created by Linor, 24-11-2003
 *  Ported from Angalon to Genesis by Eowul, 30-8-2004
 *  Updated for inclusion in the mudlib by Eowul on May 10th, 2009
 *  Almost entirely re-written by Lucius@Genesis, 2011-2016
 */
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

#define EDITOR  "/obj/edit"

#define LIBRARY_BOOK	"_avenir_library_book"

#define MINLEN_ALL	3
#define MAXLEN_TITLE	35
#define MAXLEN_TYPE	12
#define MAXLEN_SUMMARY	100
#define MAXLEN_AUTHOR	15

inherit "/std/scroll";

public static object  library;
public static string  book_id;
public static string  book_text;
public static string  book_type;
public static string  book_title;
public static string  book_summary;
public static string *book_authors = ({});

private static int     modified;
private static string  old_text;
private static string  old_type;
private static string  old_title;
private static string  old_summary;
private static string *old_authors = ({});

/*
 * Function name: create_library_book
 * Description  : Construct the library book
 */
public void
create_library_book(void)
{
}

/*
 * Function name: create_scroll
 * Description  : Constructor
 */
static nomask void
create_scroll(void)
{
    add_name(LIBRARY_BOOK);

    add_prop(OBJ_M_NO_DROP,
	"Return it to the library instead of dropping it.\n");

    create_library_book();
}

/*
 * Function name: set_book_id
 * Description  : Set the ID of the book as known in the library
 * Arguments    : id - the book id
 */
public void
set_book_id(string id)
{
    book_id = id;
}

/*
 * Function name: set_library
 * Description  : Set the object pointer to the library this book belongs to
 * Arguments    : ob - the library object
 */
public void
set_library(object ob)
{
    library = ob;
}

/*
 * Function name: set_filename
 * Description  : Set the filename of the book context so that it can be
 *                read and edited.
 * Arguments    : name - the name of the file
 */
public void
set_filename(string name)
{
    set_file(name);
}

/*
 * Function name: query_filename
 * Description  : Query the filename of this book
 */
public string
query_filename(void)	{ return query_file(); }

/*
 * Function name: set_title
 * Description  : Set the title of this book
 * Arguments    : str - the title to set
 */
public void
set_title(string str)
{
    book_title = str;
}

/*
 * Function name: query_title
 * Description  : Query the title of this book
 */
public string
query_title(void)	{ return book_title; }

/*
 * Function name: set_type
 * Description  : Set the type of this book
 * Arguments    : str - the type to set
 */
public void
set_type(string str)
{
    // See if we use books, or scrolls or parchments or whatever
    if (strlen(str))
	book_type = str;
    else if (!strlen(book_type = library->query_library_book_type()))
	book_type = "book";

    add_name(book_type);
}

/*
 * Function name: query_type
 * Description  : Query the title of this book
 */
public string
query_type(void)	{ return book_type; }

/*
 * Function name: set_summary
 * Description  : Set the summary of this book
 * Arguments    : str - the summar to set
 */
public void
set_summary(string str)
{
    book_summary = str;
}

/*
 * Function name: query_summary
 * Description  : Query the summary of this book
 */
public string
query_summary(void)	{ return book_summary; }

/*
 * Function name: set_authors
 * Description  : Set the authors of this book
 * Arguments    : *arr - the authors to set
 */
public void
set_authors(string *arr)
{
    book_authors = arr;
}

/*
 * Function name: query_authors
 * Description  : Query the authors of this book
 */
public string *
query_authors(void)	{ return book_authors; }


public int
book_access(object ob)
{
    return ob->id(LIBRARY_BOOK) &&
	(environment(ob) == this_player());
}

private mapping input_limit = ([
      "title" : MAXLEN_TITLE,
       "type" : MAXLEN_TYPE,
    "summary" : MAXLEN_SUMMARY,
     "author" : MAXLEN_AUTHOR,
]);

private int
check_length(string str, string verb)
{
    int len = strlen(str);

    if (len < MINLEN_ALL || len > input_limit[verb])
    {
	write("That '"+ capitalize(verb) +"' is invalid!\n"+
	    "Try to keep it between "+ MINLEN_ALL +" and "+
	    input_limit[verb] +" characters.\n");

	return 1;
    }

    return 0;
}

/*
 * Function name: validate_authors
 * Description  : Called from player_input with the name of an author
 * Arguments    : string who - the author to add/remove
 */
private void
validate_authors(string who)
{
    int size;
    string *new = ({ }), *old = ({ });
    old_authors = book_authors;

    foreach(string name: filter(explode(who, " "), strlen))
    {
	if (check_length(name, "author"))
	    return;

	// Check if adding a new author
	if (member_array(name, book_authors) == -1)
	    new += ({ name });
	else
	    old += ({ name });
    }

    // Overkill?
    new -= old;

    book_authors += new;
    book_authors -= old;

    // We require at least one author
    if (!sizeof(book_authors))
    {
	write("The "+ short() +" needs to have at least one author.\n");
	book_authors = old_authors;
	return;
    }

    if (size = sizeof(new))
    {
	modified++;
	write("You add "+ COMPOSITE_WORDS(map(new, capitalize)) +
	    " as " + (size == 1 ? "an author" : "authors") +
	    " to "+ short() +".\n");
    }

    if (size = sizeof(old))
    {
	modified++;
	write("You remove "+ COMPOSITE_WORDS(map(old, capitalize)) +
	    " as " + (size == 1 ? "an author" : "authors") +
	    " to "+ short() +".\n");
    }
}

/*
 * Function name: player_input
 * Description  : Called from input_to with the new title of the book
 * Arguments    : str - the new title
 */
public void
player_input(string str, string verb)
{
    // Check if we want to abort
    if (!strlen(str) || str == "~q")
    {
        write("Aborted.\n");
        return;
    }

    if ((verb != "author") && check_length(str, verb))
	return;

    switch(verb)
    {
    case "title":
	// Update the title
	old_title = book_title;
	book_title = str;
	break;

    case "type":
	// Update the type
	old_type = book_type;
	book_type = str;
	break;

    case "summary":
	// Update the title
	old_summary = book_summary;
	book_summary = str;
	break;

    case "author":
	// Update the authors
	validate_authors(lower_case(str));
	return;
    }

    modified++;
    write("You changed the "+ capitalize(verb) +" for the "+ short() +"\n");
}

/*
 * Function name: done_editing
 * Description  : Function called when the player is done editing the
 *              : text of the book.
 * Arguments    : str - the text of the book
 */
public void
done_editing(string str)
{
    // Aborted
    if (!strlen(str))
    {
        write("Aborted.\n");
        return;
    }

    // Update the text
    old_text = book_text;
    book_text = str;

    modified++;
    write("Ok.\n");
}

/*
 * Function name: edit_cmd
 * Description  : Modify the text of this book
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public void
edit_it(string verb)
{
    // Do an access check
    if (!objectp(library))
    {
        write("Please leave a bug report, no library is set in this " +
            book_type + ".\n");
        return;
    }

    if (strlen(scroll_file) && !library->query_librarian(this_player()))
    {
        write("You are not allowed to alter the contents of this " +
            book_type + ".\n");
        return;
    }

    // See if this book is locked from editing
    if (strlen(book_id) && library->library_is_book_locked(book_id))
    {
        write("You are not able to alter the contents of this " +
            book_type + ".\n");
        return;
    }

    if (verb == "title")
    {
        if (strlen(book_title))
            write("The current title is: " + book_title + "\n");

        write("What is the new title of the " + book_type +
	    "?\n~q to abort: ");

        input_to(&player_input(, verb));
        return;
    }

    if (verb == "type")
    {
        if (strlen(book_type))
            write("The current type is: " + book_type + "\n");

        write("What is the new type for the " + book_type +
	    "?\n~q to abort: ");

        input_to(&player_input(, verb));
        return;
    }

    if (verb == "summary")
    {
        if (strlen(book_summary))
	{
            write("The current summary is:" +
		break_string("\n" + book_summary, 65, 5) + "\n");
	}

        write("What is the new summary for the " + book_type +
	    "?\n~q to abort: ");

        input_to(&player_input(, verb));
        return;
    }

    if (verb == "author")
    {
	if (!strlen(book_id))
	{
	    write("You may not modify the authors on a new book.\n");
	    return;
	}

	int size = sizeof(book_authors);

        if (size)
	{
            write("The current "+ (size > 1 ? "authors are" : "author is") +
		": "+ COMPOSITE_WORDS_WITH(map(book_authors, capitalize), "and") +"\n");
	}

        write("To add or remove an author for the " + book_type +
	    ", input their name below.\n~q to abort: ");

        input_to(&player_input(, verb));
        return;
    }

    // Load the text if there is none yet
    if (!strlen(book_text) && strlen(scroll_file))
    {
        seteuid(getuid());
        book_text = read_file(scroll_file, 1);
    }

    // Start editing
    clone_object(EDITOR)->edit(done_editing, book_text);
}

public int
edit_cmd(string args)
{
    // Syntax check
    if (!strlen(args))
        return notify_fail(capitalize(query_verb()) + " what?\n", 0);

    // Perform a parse command
    object *books = CMDPARSE_ONE_ITEM(args, "book_access", "book_access");

    // Check if we found something
    if (!sizeof(books))
        return notify_fail(capitalize(query_verb()) + " what?\n", 0);

    // See if we mean this book
    books[0]->edit_it(query_verb());
    return 1;
}

/*
 * Function name: return_library_book
 * Description  : Function called when we want to return this book
 * Returns      : 0 on failure, 1 on success
 */
public int
return_library_book(void)
{
    // Do an access check
    if (!objectp(library))
    {
        notify_fail("Please leave a bug report, no library is set in this " +
            book_type + ".\n");
        return 0;
    }

    // See if we have to add this book
    if (!strlen(book_id))
    {
        notify_fail("You must submit your " + book_type + " to add it to the " +
            "library.\n");
        return 0;
    }

    // Unborrow this book if needed
    library->library_remove_borrowed(book_id, this_object());

    // Update the book if needed
    if (modified) {
	library->update_book(book_id,
	    old_text    ? book_text    : "",
	    old_title   ? book_title   : "",
	    old_summary ? book_summary : "",
	    old_type    ? book_type    : "",
	    sizeof(old_authors) ? book_authors : ({ })
	);
    }

    write("You return the " + (modified ? "edited " : "") + book_type +
	" titled '" + book_title + "'.\n");

    return 1;
}

/*
 * Function name: discard_library_book
 * Description  : Function called when we want to submit this book
 * Returns      : 0 on failure, 1 on success
 */
public int
discard_library_book(void)
{
    // Do an access check
    if (!objectp(library))
    {
        write("Please leave a bug report, no library is set in this " +
            book_type + ".\n");
        return 0;
    }

    // See if we have to add this book
    if (strlen(book_id))
    {
        write("You must return your " + book_type + ".\n");
        return 0;
    }

    write("You discard the "+ short() +"\n");
    return 1;
}

/*
 * Function name: submit_library_book
 * Description  : Function called when we want to submit this book
 * Returns      : 0 on failure, 1 on success
 */
public int
submit_library_book(void)
{
    int result;

    // Do an access check
    if (!objectp(library))
    {
        write("Please leave a bug report, no library is set in this " +
            book_type + ".\n");
        return 0;
    }

    // See if we have to add this book
    if (strlen(book_id))
    {
        write("You must return your " + book_type + ".\n");
        return 0;
    }

    if (!strlen(book_title))
    {
        write("The " + book_type + " has no title.\n");
        return 0;
    }

    if (!strlen(book_summary))
    {
        write("The " + book_type + " has no summary.\n");
        return 0;
    }

    if (!strlen(book_text))
    {
        write("The " + book_type + " titled '" + book_title +
	    "' has no contents.\n");
        return 0;
    }

    result = library->add_new_book(book_title, book_text,
	book_summary, this_player()->query_real_name());

    write("The " + book_type + " titled '" + book_title +
	    "' has been submitted with an id of: "+ result +"\n");

    return 1;
}

/*
 * Function name: return_cmd
 * Description  : Return the book or submit it
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
return_cmd(string args)
{
    object  *books;

    // Syntax check
    if (!args || args == "")
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    // Perform a parse command
    if (!parse_command(args, this_player(), "[the] %i", books))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    // Filter
    books = NORMAL_ACCESS(books, 0, 0);

    // Check if we found something
    if (!sizeof(books))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    switch(query_verb())
    {
        case "discard":
            // Call a return function in every book
            books = filter(books, &->discard_library_book());
            break;
        case "submit":
            // Call a submit function in every book
            books = filter(books, &->submit_library_book());
            break;
        default:
            // Call a return function in every book
            books = filter(books, &->return_library_book());
            break;
    }

    if (sizeof(books) == 0)
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

    // Write messages
//    write("You " + query_verb() + " " + COMPOSITE_DEAD(books) + ".\n");
    say(QCTNAME(this_player()) + " " + query_verb() + "s " +
        COMPOSITE_DEAD(books) + ".\n");

    // Destroy the books
    books->remove_object();
    return 1;
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
public void
init(void)
{
    ::init();

    // See if we are linked to a library
    if (!objectp(library))
        return;

    add_action(return_cmd,  "return");

    // See if the player is a librarian, or that this book is a new book
    if (strlen(scroll_file) && !library->query_librarian(this_player()))
        return;

    // Add commands
    add_action(edit_cmd,   "edit");
    add_action(edit_cmd,   "title");
    add_action(edit_cmd,   "summary");

    if (!strlen(scroll_file))
    {
	add_action(return_cmd, "submit");
	add_action(return_cmd, "discard");
    }
    else if (library->query_librarian(this_player()))
	add_action(edit_cmd,   "author");
}

/*
 * Function:    long
 * Description: Description of the mount.
 * Arguments:   str: thing looked at; for_obj: who is looking.
 * Returns:     That description, as a string.
 */
public string
long(string str, object for_obj)
{
    string result = ::long(str, for_obj);

    // For add_items, use the original function
    if (strlen(str))
        return result;

    if (!objectp(for_obj))
	for_obj = this_player();

    // See if the player is a librarian, or that this book is a new book
    if (strlen(scroll_file) && !library->query_librarian(for_obj))
    {
        return result + "You can 'return' the "+ book_type +
	    " if you are done reading.\n";
    }

    // Add extra commands
    return result += "The following commands are available:" +
	"\n\t* edit "    + book_type +
	"\n\t* title "   + book_type +
	"\n\t* summary " + book_type +
	(!strlen(scroll_file) ?
	   "\n\t* submit "  + book_type +
	   "\n\t* discard " + book_type :
	   (library->query_librarian(for_obj) ?
	       "\n\t* author "  + book_type : "") +
	   "") + "\n";
}

/*
 * Function name: read_it
 * Description:   Perform the actual read
 */
public void
read_it(string answer)
{
    // Read from file if no text is set, otherwise, display the text
    if (strlen(scroll_file))
    {
        ::read_it(answer);
        return;
    }

    if (!strlen(book_text))
        write("The "+ book_type +" is empty.\n");
    else
        this_player()->more(book_text, 0);
}
