/*
 * File: novlib.c
 *
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit "/lib/library";

#include <math.h>

#define BOOKPATH	(LIBSAVE + "/novice_old/")

/* global vars */
public object table;
public int level, words;
public string *phrases = ({ });


/*
 * Function name: up_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
up_exit_block(void)
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
	/* A book was found.  Give a warning and return 1 to block the exit */
	write("You cannot leave without returning the book you have borrowed.\n");
	return 1;
    }

    if (!IS_MEMBER(TP))
    {
	write("Such authority does not lie within you, that "+
	  "the shadows will part to let you pass.\n");
	return 1;
    }

    /* Novices: check level */
    if ((SPHERE(TP) == SPH_TRAINING) &&
	(LIST->query_nov_lvl(TP) < level))
    {
	write("Such authority does not yet lie within you, that "+
	  "the shadows will part to let you pass.\n");
	return 1;
    }

    /* must then be novice of appropriate level or full occ member */
    write("The shadows part, permitting you to ascend the stone "+
      "staircase to the next level of the library.\n");

    return 0;
}

public string
library_table_desc(void)
{
    if (present(table))
	return table->describe_table();

    return "";
}

public void
union_library(int lev)
{
    level = lev + 1;
    words = random(sizeof(phrases));

    /* Indicate if we want players to have to "borrow" a book in
     * order to read it.
     */
    set_borrow_required(0);

    /* This is the directory where approved books are saved */
    set_book_directory(BOOKPATH);

    /* This is the directory where books that need approval are saved */
    set_book_approval_directory(BOOKPATH + "pending/");

    /* This is the directory where books that have been denied or discarded
     * are saved.
     */
    set_book_removal_directory(BOOKPATH + "removed/");

    create_library();

    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", "@@library_help@@");
    add_cmd_item("sign","read", "@@library_help@@");
    add_item(({"bookshelves","bookshelf","stone bookshelves", "shelves",
	"north wall", "shelf"}),
      "They appear to be carved into the stone.\nAbove the shelves is "+
      "posted a sign that reads:\n\nYou do not have to borrow the books "+
      "inorder to read them.\n@@library_help@@\n");
    add_item(({"light"}),
      "Light filters down the stairs from an unknown source " +
      "high in the tower. Mists coalesce and float down " +
      "the stairwell, where they seem to dance in an intricate "+
      "pattern at your feet.\n");
    add_item(({"cushion", "cushions", "grey cushion", "flat cushion"}),
      "The cushions are very thin, flat, and square. Their concession "+
      "to comfort is utilitarian, rather than luxurious, as the "+
      "cushions in the Salon of Shadows are.\n");
    add_cmd_item(({"word","words","wall","inscription","inscriptions",
	"scroll", "scrolls"}), "read", "@@words@@");
    add_item(({"word","words","wall","inscription","inscriptions",
	"scroll", "scrolls" }), "@@words@@");
    add_item(({"wall","walls",}),
      "The walls are incredibly smooth and reflect the light "+
      "drifting down the stairwell. Upon closer inspection, you "+
      "realize that they are made of black obsidian glass that has " +
      "been formed by the fires of Jazur. They are cool to the touch "+
      "and very slick.\nAll along the walls hang scrolls inscribed "+
      "with words written in an elegant script.\n");

    add_object(OBJ + "library_table");
}

static void
update_vars(void)
{
    table = present("_union_novice_table");
}

public string
words(void)
{
    if (!IS_MEMBER(TP))
    {
	return "As you do not recognize the script, the words "+
	    "are all indecipherable.\n";
    }

    if (++words >= sizeof(phrases))
	words = 0;

    return "One of the phrases upon the scrolls reads:\n"+
	break_string(phrases[words], 55, 5)+"\n";
}

public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP))
	init_library();
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
    if (IS_MEMBER(TP))
	return 1;

    write("You are disallowed from using this library.\n");
    return 0;
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
    if (IS_MEMBER(TP))
	return 1;

    write("You are disallowed from using this library.\n");
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
    if (!MEMBER_SPHERES(TP, ({ SPH_VOICE, SPH_MENTOR })))
    {
	write("Such authority does not yet lie within you.\n");
	return 0;
    }
    return 1;
}

/*
 * Function name: library_write_access
 * Description:   Limit permission to write books to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */
public int
library_write_access(void)
{
    return library_admin_access();
}

/*
 * Halved the auto-mread limit and changed startline to strip
 * book headers for when reading.
 */
public void
library_read_book(string text_filename, string book_name, int mread)
{
    if (mread || (file_size(text_filename) > 2000))
	TP->more(read_file(text_filename, 4));
    else
	write(read_file(text_filename, 4));
}

/*
 * Function name: library_configure_book
 * Description:   Configure a library book.  Redefined to add a
 *                nice short description for the book based
 *                on the file name of the book.
 * Arguments:     object book           - the book object
 *                string text_filename - the file name of the book file to use
 *                string book_name     - the name of the book
 */
public void
library_configure_book(object book, string text_filename, string book_name)
{
    int sz, index;
    string adj, nm;
    string *adjs = ({ "small", "dark", "cloth-bound", "gold-embossed",
			"slender", "fragile" });

    ::library_configure_book (book, text_filename, book_name);

    sz = sizeof(adjs);
    // parse out spaces: name_to_random will choke on them
    nm = implode(explode(book_name, " "), "");
    index = NAME_TO_RANDOM(nm, 13254, sz);

    // I am not confident that NAME_TO_RANDOM is reliable (I have
    // seen it return random numbers!). So I will do my own sanity
    // checking.
    if ((index >= 0) && (index < sizeof(adjs)))
	adj = adjs[index];
    else
	adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
}
