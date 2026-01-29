/* Standard book for the library                */
/*    Cirion 032796                             */
/* 
 * Revisions:
 * 	Lucius, Apr 2005: Modified for the Union Archives
 */
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <options.h>
#include <ss_types.h>

#include "../defs.h"
inherit "/std/book";

/* Default pagelength */
#define PAGELENGTH  30

public int lang_to_read;
public string blank_page = "This page appears to be blank.\n";

/*
 * Basic defaults.
 */
public void
create_book(void)
{
    set_name("tome");
    set_short("massive dusty tome");
    set_long("It is a massive tome, heavy and unwieldly.\n");
}

/*
 * Masked to show open/closed state of book.
 */
public varargs mixed
long(string str, object for_obj)
{
    string mystr;

    if (book_is_closed)
	mystr = "It is closed.\n";
    else
	mystr = "It is opened to the " + LANG_WORD(what_page) +" page.\n";

    return ::long(str, for_obj) + mystr;
}

/*
 * Based the size of each page on the players
 * more length option. Or use PAGELENGTH as the
 * default if they have it set lower than that.
 */
public int
query_pagelength(void)
{
    int size = TP->query_option(OPT_MORE_LEN);

    if (size < PAGELENGTH)
	return PAGELENGTH;
    else
	return size;
}

/*
 * Function name: read_book_at_page
 * Description:   should be redefined in your book. is called from read_me
 * Arguments:	  which - read the book at which page
 *		  verb  - If the player wanted to read it, or mread it.
 *			  To mread something, you can look how the scoll.c does
 *			  it in read_it() if needed.
 */
public varargs void
read_book_at_page(int which, string verb)
{
    if (!CAN_SEE(TP, TO))
    {
	write("Read what?\n");
	return;
    }

    if (TP->query_skill(SS_LANGUAGE) < lang_to_read)
    {
	write("The words are in a language you do not understand.\n");
	return;
    }

    /* Use a different reading logic for read/mread. */
    if (verb == "mread")
    {
	int size = file_size(scroll_file);

	if (size < 2000)
	    write(read_file(scroll_file, 4));
	else if (size > 50000)
	    write("The "+ short() +" is too large to 'mread'.\n");
	else
	    TP->more(read_file(scroll_file, 4));
    }
    else
    {
	string text;
	int size = query_pagelength();

	if (which-- == 1)
	    text = read_file(scroll_file, (which + 4), size);
	else
	    text = read_file(scroll_file, ((which * size) + 4), size);

	if (!strlen(text))
	    write(blank_page);
	else
	    write(text);
    }
}

/* Set how the blank page looks. */
public void
set_blank_page(string str)
{
    blank_page = str;
}

/* Set how hard it is to read the book. */
public void
set_lang_to_read(int num)
{
    if (num > 100)
	lang_to_read = 100;
    else if (num < 0)
	lang_to_read = 0;
    else
	lang_to_read = num;
}

/* Query how hard it is to read the book. */
public int
query_lang_to_read(void)
{
    return lang_to_read;
}

/* Weight and volume of book based on size */
public void
set_max_pages(int num)
{
    ::set_max_pages(num);

    add_prop(OBJ_I_WEIGHT, (num * 100));
    add_prop(OBJ_I_VOLUME, (num * 210));
}
