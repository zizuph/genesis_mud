/*
 * book.c      
 *
 * A standard book that may be inherited when you need a book of some kind.
 * Please report any bugs etc.  There are probably a few left.
 *
 * Styles
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/* Variables */
string	title,		/* The title of the book. */
	text_file;	/* The file containing the text of the book. */
int	open;		/* True if the book is open. */


/* Prototypes */
void set_text_file(string str);

/*
 * Function name: init
 * Description:   Init all commands suplied by the book.
 */
public void
init()
{
    ::init();

    add_action("open_book", "open");
    add_action("close_book", "close");
    add_action("read_book", "read");
}

/*
 * Function name: create_book
 * description:   Redefine this function and use it to configure
 *                the book to your liking.
 */
void
create_book() {}


/*
 * Function name: create_object
 * Description:   Create a plain empty book object. 
 *                Some basic settings are set here. Redefine the
 *                create_book() function and use it to configure
 *                the book to your liking.
 */
nomask void
create_object()
{
    set_name("book");
    set_long("An empty book with no title.\n");
    set_text_file("none");
   
    add_prop(OBJ_I_WEIGHT, 1000);       /* 1 kilo   */
    add_prop(OBJ_I_VOLUME, 1000);       /* 1 litre  */
    add_prop(OBJ_I_VALUE, 0);           /* 0 copper */

    create_book();
}


/*
 * Function name: set_text_file
 * Description:   Allows you to set the path to the textfile
 *                that is to be used when someone reads the book.
 * Arguments:     str - The path to the textfile.
 *
 */
void
set_text_file(string str)
{
    text_file = str;
}


/*
 * Function name: set_title
 * Description:   Allows you to set the title of the book.
 * Arguments:     str - The title of book.
 *                
 */
void
set_title(string str)
{
    title = str;
}

/*
 * Function name: query_title
 * Description:   Returns the title of the book.
 */
string
query_title()
{
    return title;
}

/*
 * Function name: reset_book
 * Description:   Redefine this function and use it if you need to 
 *                reset the book for some reason.
 */
void
reset_book() {}


/*
 * Function name: reset_object
 * Description:   If you define reset_book() in your code, it will be
 *                called from here every now and then. 
 */
nomask void
reset_object() { this_object()->reset_book(); }


/*
 * Function name: open_book
 * Description:   
 *                 
 */
public int
open_book(string what)
{

    if (!id(what))
    {
	notify_fail("Open what?\n");
	return 0;
    }

    if (open)
    write("The book is already open. Go ahead and read it.\n");
    else
    {
	write("You open the book.\n");
	say(QCTNAME(this_player()) + " opens the "+ short() +".\n");
    }

    open = 1;
    return 1;
}


/*
 * Function name: close_book
 * Description:
 *                
 */
public int
close_book(string what)
{

    if (!id(what))
    {
        notify_fail("Close what?\n");
        return 0;
    }

    if (!open)
        write("The book is already closed.\n");
    else
    {
        write("You close the book.\n");
        say(QCTNAME(this_player()) + " closes the "+ short() +".\n");
    }

    open = 0;
    return 1;
}


/*
 * Function name: read_book
 * Description:   
 *               
 */
public int
read_book(string what)
{
    int ret;
    seteuid(getuid(this_object()));

    if (!id(what))
    {
	notify_fail("Read what?\n");
	return 0;
    }

    if (open)
    {
	notify_fail("The text fades away. It can not be read.\n");

	say(QCTNAME(this_player()) + " reads the "+ short() +".\n");
	ret = this_player()->more(text_file, 1);
    }
    else
	notify_fail("The book is closed.\n");

    return ret;
}
