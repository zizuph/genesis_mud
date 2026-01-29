#pragma strict_types
/*
 * Archives - library for the Shadow Union
 *
 * Coded by Cirion on January 3rd, 1997
 *
 * modified 1998.08.23 Cirion diallowed non-union member from
 *    using the library.
 *
 * Revisions:
 *    Lucius, Apr 2005: Use /std/library more. This causes
 *                      the age of books to be lost, but I don't think the
 *                      players had noticed it anyways.
 *    Lucius, Jun 2005: Further updates and additional commands.
 *    Lucius, Feb 2009: Changed library_admin_acces()
 *    Lucius, Jun 2016: Archiving the archives, replaced with a new one.
 */
#include <math.h>
#include <macros.h>
#include <composite.h>

#include "../defs.h"

inherit BASE;
inherit "/lib/library";

#define BOOKFILE  (OBJ + "book_old")
#define BOOKPATH  (LIBSAVE + "archive_old/")
#define BOOKTEMP  (LIBSAVE + "archive_old/tmp/")

/* Defines taken from /std/library.c */
#define BOOK_TYPE  book_types[0]
#define PLURAL_BOOK_TYPE \
        (sizeof(plural_book_types) ? \
	        plural_book_types[0] : LANG_PWORD(book_types[0]))

#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
        (sizeof(plural_shelf_types) ? \
	        plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))

#define BOOK_ID    (MASTER + "_library_book")
#define DEFAULT_TEXT_FILE_NAME "book"

#define TITLE_LINE   1
#define SUMMARY_LINE 2
#define AUTHOR_LINE  3
#define TEXT_LINE    4

#define MAX_TITLE_SIZE 20


public void
union_room(void)
{
    set_short("Former Archives");
    set_long("Deep purple granite walls frame this large room, "
      + "along which are wide wooden shelves. The room is musty, "
      + "with a thin coating of dust upon every flat surface.\n");

    add_item(({"wall","walls","granite"}),"The walls are of "
      + "smoothed granite, undressed and of a deep purple "
      + "hue. Tiny, almost inperceptable, veins of red gemstone "
      + "run along the walls like a spider's web.\n");
    add_item(({"gem","gemstone","vein","veins","web"}), "The "
      + "lines that run along the walls are nearly imperceptible, "
      + "but the gemstone that fills them seem to be akin to ruby.\n");
    add_item(({"floor","ground"}),"The floor is of plain and "
      + "flat slate tiles, worn smooth over the years.\n");

    add_cmd_item(({"tile","tiles"}),({"push","move","lift","pull"}),
      "The tiles are firmly secured to the floor.\n");
    add_cmd_item(({"shelf","shelves"}),"push","The shelves will not move.\n");


    add_exit("library", "back", library_exit_block);

    set_book_directory(BOOKPATH);
    set_book_approval_directory(BOOKPATH +"pending/");
    set_book_removal_directory(BOOKPATH + "removed/");

    add_book_shelf(({
	"equipment", "general", "guilds",
	"herblore", "history", "logs", "maps",
      }));

    set_default_shelf("general");

    create_library();
}

/*
 * Function name: library_list_access
 * Description:   Redefine this to limit permission to list books
 * Returns:       1 - this_player() is permitted to list books
 *                0 - this_player() is not permitted to list books
 */
public int
library_list_access(void)
{
    return 1;
}

/*
 * Function name: library_borrow_access
 * Description:   Redefine this function to limit permission to borrow books
 * Returns:       1 - this_player() is permitted to borrow a book
 *                0 - this_player() is not permitted to borrow a book
 */
public int
library_borrow_access(void)
{
    /* If the player is punished with "noarchives", prevent
     * him from making use of the library.  */
    if (U_IS_PUNISHED(TP, U_PUNISHED_LIBRARY))
    {
	write("You are disallowed from using this library.\n");
	return 0;
    }

    return 1;
}

public int
library_write_access(void)
{
    write("No new books are allowed in this library.\n");
    return 0;
}

/*
 * Function name: library_admin_access
 * Description:   Limit library administration abilities to certain
 *                people.
 * Returns:       1 - this_player() has administration powers
 *                0 - this_player() does not have administration powers
 */
public int
library_admin_access(void)
{
    /* Historians, Elders and GM's. */
    if (MEMBER_SPHERE(TP, SPH_HISTORY))
	return 1;

    write("Such authority does not yet lie within you.\n");
    return 0;
}

/*
 * Function name: library_approve_access
 * Description:   Redefine this function to limit permission to approve books
 * Returns:       1 - this_player() is permitted to approve a book
 *                0 - this_player() is not permitted to approve a book
 */
public int
library_approve_access(void)
{
    return library_admin_access();
}

/*
 * Function name: library_approve_hook
 * Description:   Redefine this to alter the message given when a
 *                user approves a book
 * Arguments:     string title - the book's title
 */
public void
library_approve_hook(string title)
{
    //    LIST->add_union_message("all",
    //	"A new book resides in the Union Archives.\n");

    write("You approve '" + title + "' to be in the Archives.\n");
}

/*
 * Function name: library_classify_access
 * Description:   Redefine this function to limit permission to classify books
 * Returns:       1 - this_player() is permitted to classify a book
 *                0 - this_player() is not permitted to classify a book
 */
public int
library_classify_access(void)
{
    return library_admin_access();
}

/*
 * Function name: library_deny_access
 * Description:   Redefine this function to limit permission to deny books
 * Returns:       1 - this_player() is permitted to deny a book
 *                0 - this_player() is not permitted to deny a book
 */
public int
library_deny_access(void)
{
    return library_admin_access();
}

/*
 * Function name: library_discard_access
 * Description:   Redefine this function to limit permission to discard books
 * Returns:       1 - this_player() is permitted to deny a book
 *                0 - this_player() is not permitted to deny a book
 */
public int
library_discard_access(void)
{
    return library_admin_access();
}

/*
 * Masked to capitalize the titles.
 */
public string
query_book_title(string file)
{
    return capitalize(::query_book_title(file));
}

/*
 * Masked to only show approval bit for those that actually can.
 */
public int
library_list_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() +
      (strlen(appr_dir) ? (library_approve_access() ?
	  " [approval]" : "") : "") + " [titles]\n");
    return 0;
}

/*
 * Masked to alphabetize.
 */
public void
library_list_shelves_hook(void)
{
    write(implode(sort_array(map(m_indices(book_shelves), capitalize)),
	"\n") + "\n");
}

/*
 * Masked to display and sort by shelf.
 */
public void
library_list_long_hook(void)
{
    int i = -1, size;
    string *shelves = sort_array(m_indices(book_shelves));

    size = sizeof(shelves);
    while(++i < size)
    {
	if (!strlen(book_shelves[shelves[i]][0]))
	    continue;

	write(CAP(shelves[i]) +" "+ SHELF_TYPE +":\n");
	write(book_shelves[shelves[i]][0]);
	write("\n");
    }
}

/*
 * Masked to display and sort by shelf.
 */
public void
library_list_short_hook(void)
{
    int i = -1, size;
    string *shelves = sort_array(m_indices(book_shelves));

    size = sizeof(shelves);
    while(++i < size)
    {
	if (!strlen(book_shelves[shelves[i]][0]))
	    continue;

	write(CAP(shelves[i]) +" "+ SHELF_TYPE +":\n");
	write(book_shelves[shelves[i]][1]);
	write("\n");
    }
}

/*
 * Used to sort the display of books.
 */
public int
sort_book_by_title(string one, string two)
{
    string t1 = query_book_title(one), t2 = query_book_title(two);

    if (t1 < t2)
	return -1;
    else if (t1 > t2)
	return 1;
    else
	return 0;
}

/*
 * Masked to alphabetize book listings.
 */
public string
format_book_list(string *books)
{
    int i;
    string str = "";

    books = sort_array(books, "sort_book_by_title");

    for (i = 0; i < sizeof(books); i++)
    {
	str += sprintf("%-" + MAX_TITLE_SIZE + "s %-13s %-=40s\n",
	  query_book_title(books[i]), query_book_author(books[i]),
	  query_book_summary(books[i]));
    }

    return str;
}

/*
 * Masked to alphabetize book listings.
 */
public string
format_book_list_short(string *books)
{
    string *titles;

    books = sort_array(books, "sort_book_by_title");
    titles = map(books, query_book_title);

    return sprintf("%-#70.2s\n", implode(titles, "\n"));
}

/* 
 * Masked to deliver custom messages.
 *
public int
add_book(string title, string summary, string author, 
	 string text, int approval)
{
    int result = ::add_book(title, summary, author, text, approval);

    if (result && approval)
    {
	LIST->add_union_message(LIST->elder_list(),
	    "A new book resides in the Archives requiring your approval.\n");
    }

    return result;
}
 */

/*
 * Create adjectives based on book title and size.
 */
private string *
get_book_adjs(string title, string file)
{
    string *result = ({"",""}), *adjs = ({
      "black", "blue", "red", "parchment",
      "dusty", "heavy", "leather-bound", "white",
      "iron-bound", "silver-clasped", "hide-bound",
      "steel-bound", "brass-clasped", "elegant",
    });

    switch(file_size(file))
    {
    case 0..100: result[0] = "tiny";  break;
    case 101..200: result[0] = "small";  break;
    case 201..1000: result[0] = "thin";  break;
    case 1001..2000: result[0] = "medium-sized";  break;
    case 2001..7000: result[0] = "large";  break;
    case 7001..10000: result[0] = "heavy";  break;
    default: result[0] = "massive";  break;
    }

    result[1] = adjs[NAME_TO_RANDOM(title, 1973, sizeof(adjs))];

    return result;
}

/*
 * Masked to customize books.
 */
public void
library_configure_book(object book, string text_filename, string book_name)
{
    int pages = (file_size(text_filename) / 1000) + 1;
    string *adjs = get_book_adjs(book_name, text_filename);

    ::library_configure_book(book, text_filename, book_name);

    book->set_adj(adjs);
    book->set_max_pages(pages);
    book->set_short(implode(adjs, " ") + " " + BOOK_TYPE);
    book->set_long("This is a "+ book->short() +" from the Union Archives. "+
      "Printed in large bold letters along the spine of this "+
      BOOK_TYPE +" is '"+ CAP(book_name) +"'. Along the cover, "+
      "writ in a flowing and elegant script is:\n\t"+
      query_book_summary(text_filename) +"\n\tWritten "+
      query_book_author(text_filename) + "\n");
}

/*
 * Masked to use a custom book type.
 */
public object
library_make_book(string book_name)
{
    return clone_object(BOOKFILE);
}

/*
 * Print better help text to contain additional functions
 * and only display commands available to those that can
 * actually access them.
 */
public string
library_help(void)
{
    function help_cmd = &sprintf("%-28s - %-=45s\n", , );

    string str = "Commands for the Shadow Union Archives:\n\n" +
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

    if (library_write_access())
    {
	str += help_cmd("Write",
	  "Write a book and submit it to the library.");
    }

    //    str += help_cmd("Ulog",
    //	"Add an entry to the Logbook for your Sphere.");

    str += "\nNotes on reading the volumes:\n\n";

    str += help_cmd("Read  <volume>", "Standard way to read a book. The "+
      "longer the book, the more pages it will have.") +
    help_cmd("Mread <volume>", "Alternate way to read a book. Small "+
      "volumes will be read at once, larger ones will be read with the "+
      "usual more reader.");

    /* Return here for non-admins. */
    if (!library_admin_access())
	return "\n" + str + "\n";

    str += "\nAdministrator commands available:\n\n";

    if (strlen(appr_dir))
    {
	str += help_cmd("Approve <title>",
	  "Approve a book for inclusion in the library.");

	if (borrow_required)
	{
	    str += help_cmd("Borrow approval <title>",
	      "Administrators may borrow books which have not been " +
	      "approved by using the \"approval\" option.");
	}
	else
	{
	    str += help_cmd("(M)Read approval <title>",
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

    /* Return here for non-wizards. */
    if (!TP->query_wiz_level())
	return str + "\n";

    str += "\nWizard commands available:\n\n";
    str += help_cmd("Clear <removed>", "Empty the removed books directory.");
    str += help_cmd("Renumber <books|test>", "Renumber the filenames of the "+
      "books to fill in gaps.");

    return str + "\n";
}

/*
 * Just a wrapper function to the (masked) library_help().
 */
public int
archive_help(string str)
{
    if (str != "here" && str != "archive" && str != "archives")
	return 0;

    str = library_help();
    write(str);
    return 1;
}

/*
 * Finish a logbook entry.
 */
public void
done_logging(string sphere, string input)
{
    string summary, file1, file2;

    /* No input. */
    if (!strlen(input))
    {
	library_write_abort_hook();
	return;
    }

    /* Logbook already exists. */
    if (strlen(file1 = book_map[sphere]))
    {
	/* Move the book out of the scanned
	 * directories or you'll have problems. */
	file2 = BOOKTEMP + sphere;

	/* Move it out of the way. */
	rename(file1, file2);

	/* Prepend contents of old logbook. */
	if (strlen(summary = query_book_text(file2)))
	    input = summary + "\n" + input;
    }

    summary  = "Logbook of the Sphere of " + SPHERES[sphere];

    /* Make sure we can create the book. */
    if (!add_book(sphere, summary, "by the Union", input, 0))
    {
	if (strlen(file2))
	{
	    /* Replace the old copy */
	    rename(file2, file1);
	    update_books();
	}

	library_write_failed_hook();
	return;
    }

    /* Move it into the proper shelf. */
    if (!library_classify_get_shelf(TP, sphere, "logs"))
    {
	if (strlen(file2))
	{
	    /* Replace the old copy */
	    rename(file2, file1);
	    update_books();
	}
    }
    else
    {
	/* Remove the old copy. */
	if (strlen(file2))
	    rm(file2);

	write("You finish making your entry.\n");

	LIST->add_union_message("all",
	  "There is a new entry in the "+ summary + ".\n");
    }
}

/*
 * Make an entry in Sphere specific Logbook.
 */
public int
union_log(string str)
{
    string sphere = TP->query_union_sphere();

    /* Need to be in a Sphere. */
    if (!strlen(sphere))
	return NF("You must belong to a Sphere first!\n");

    /* Novices can't make entries. */
    if (sphere == "training")
    {
	return NF("Since you are still in training, you may not "+
	  "make any log entries yet.\n");
    }

    /* Did we specifiy a proper Sphere? */
    if (strlen(str = lower_case(str)))
    {
	string *spheres = sort_array(m_indices(SPHERES));

	if (member_array(sphere = str, spheres) == -1)
	{
	    return NF("That is not a valid Sphere.\n"+
	      "Valid Spheres are: "+ COMPOSITE_WORDS(spheres) +"\n");
	}
    }

    /* Punished by the Elders. */
    if (U_IS_PUNISHED(TP, U_PUNISHED_LIBRARY))
    {
	write("You are disallowed from using the library.\n");
	return 1;
    }

    write("You begin writing an entry in: Logbook of the Sphere of "+
      SPHERES[sphere] + "\n");

    /* Entry Header. */
    str = sprintf("%|75s\n\n%s the %s:\n\n",
      one_of_list(({ "--*--", "-----", "*****", "~~~~~" })),
      TP->query_name(), TP->query_guild_title_occ());

    setuid();
    seteuid(getuid());

    write("\n");
    clone_object("/obj/edit")->edit(&done_logging(sphere), str);
    return 1;
}

/*
 * This does the actual relocation of books.
 */
private int
renumber_books_move(string *books, int test)
{
    string dir;
    int i, sz, last, *num, res;

    if (!(sz = sizeof(books)))
	return 0;
    else
	num = allocate(sz);

    for (i = 0; i < sz; i++)
	sscanf(books[i], "%s" + text_file_name + "%d", dir, num[i]);

    num = sort_array(num);
    last = num[sz - 1];

    for (i = 0; i < last; i++)
    {
	string book = (dir + text_file_name + i);

	if (i >= last)
	    break;

	if (file_size(book) != -1)
	    continue;

	if (!test)
	    rename(dir + text_file_name + last, book);

	write("RENAME: "+ (dir + text_file_name + last) +
	  "\n\t--> "+ book +"\n");

	res++;
	num[sz - 1] = i;
	num = sort_array(num);
	last = num[sz - 1];
    }

    return res;
}

/*
 * This function will parse through all the books, renumbering
 * them to fill any gaps so that book numbers do not grow vastly
 * large disproportionally to the number of actual books.
 */
public int
renumber_books(string str)
{
    int res, test;

    if (str != "books" && str != "test")
	return NF("Renumber what? The books?\n");

    if (strlen(book_dir))
    {
	string *books;

	if (m_sizeof(book_shelves))
	{
	    int i;
	    string *shelves = m_indices(book_shelves);

	    for (i = 0; i < sizeof(shelves); i++)
	    {
		books = get_books(book_dir + shelves[i] + "/");
		res += renumber_books_move(books, (str == "test"));
	    }
	}
	else
	{
	    books = get_books(book_dir);
	    res = renumber_books_move(books, (str == "test"));
	}

	update_books();
    }

    write("There were "+ (res ? "" + res : "no") +
      " books in need of renumbering.\n");

    return 1;
}

/*
 * This functions clears out the removal_dir (discarded books).
 */
public int
clear_removed(string str)
{
    int sz;
    string *books;

    if (str != "removed")
	return NF("Clear what? Removed?\n");

    if (!strlen(removal_dir))
    {
	write("There is no removal directory.\n");
	return 1;
    }

    books = get_books(removal_dir);
    if (!(sz = sizeof(books)))
    {
	write("There are no discarded books.\n");
	return 1;
    }

    while(sz--)
    {
	rm(books[sz]);
	write("Removed: "+ books[sz] + "\n");
    }

    return 1;
}

/*
 * Add custom commands and control who has them.
 */
public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP) || IS_GMASTER(TP))
    {
	init_library();

	//	add_action(union_log, "ulog");
	add_action(archive_help, "help");

	if (TP->query_wiz_level())
	{
	    add_action(clear_removed, "clear");
	    add_action(renumber_books, "renumber");
	}
    }
}
