/*
 * A blank book for the mortals to write in, if they want.
 * Made by Nick
 * Updated for the new std/library by Aridor 12/96
 *
 * 13.9.2002 Milan - Fixed runtime error (see line 177)
 *
 * April 25th 2007 Navarre: Instead of printing out a runtime error on line 177
 *                          I fixed the code to make the book work instead.
 */

inherit "/std/object";
#include <stdproperties.h>
#include "lib.h"

#define  TMP_BOOK  "/d/Krynn/std/library/tmp/tmp"

string file, short, long, list;
string lib_long = "some great library";
string lib_file = "/d/Krynn/std/library/library";

void
create_object()
{
    set_name("book");
    add_name("special_book");
    set_adj("brown");
    add_adj("leather");

    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 0);

    lib_file = file_name(previous_object());
    lib_long = lib_file->query_lib_long();    
}

string
my_long()
{
    return ("A brown leather book, you can write in it and later put it " +
	    "in " + lib_long + ".\n" +
	    "'bshort' to give the book a short description,\n" +
	    "'blong'  to give a long description of the book,\n" +
	    "'bedit'  to write the book. Using\n" +
	    "'blist'  will set how the book will be listed in the library's catalog.\n" +
	    "'bstore' the book when ready. It will work from any part of the mud. Use\n" +
	    "'bread'  to read this book.\n" +
	    "'bdiscard' to discard the book.\n");
}

void
init()
{
    ::init();

    ADA("bedit");
    ADA("blist");
    ADA("bshort");
    ADA("blong");
    ADA("bstore");
    ADA("bread");
    ADA("bdiscard");
}

void
remove_object()
{
    if (file)
      rm(file);
    ::remove_object();
}


int
blist(string str)
{
    if (!str)
    {
	write("This will set how your book should be listed in the library's " +
	      "catalog, typically:\n" +
	      "Neraka - a book with a map of Neraka.\n");
	if (strlen(list))
	  write("Current setting: " + list + "\n");
	return 1;
    }

    list = str;
    write("Listing set to: " + list + "\n");
    return 1;
}

void discard_book(object me)
{
    me->remove_object();
}


int
bdiscard(string str)
{
    if (!str || str !="book")
    {
	NF("Discard what?\n");
	return 0;
    }
    set_alarm(0.0, 0.0, &discard_book(this_object()));
    write("You decide to discard your book.\n");
    return 1;
}


int
blong(string str)
{
    if (!str)
    {
	write("This will set the long description of the book, typically:\n" +
	      "It's an old book containing an old map of Neraka.\n");
	if (strlen(long))
	  write("Current setting: " + long + "\n");
	return 1;
    }
    
    long = str;
    write("Description set to: " + long + "\n");
    return 1;
}

int
bshort(string str)
{
    if (!str)
    {
	write("This will set the short description of the book, typically:\n" +
	      "'red golden book'; OBSERVE, NOT 'a red golden book'!\n");
	if (strlen(short))
	  write("Current setting: " + short + "\n");
	return 1;
    }

    short = str;
    write("Short set to: " + short + "\n");
    return 1;
}

int
bstore(string str)
{
    mixed tmp;
    string libr, text;

    NF("You need to set list, long and short descriptions!\n");
    if (!strlen(list) || !strlen(long) || !strlen(short))
      return 0;
    
    NF("You need to write a book first.\n");
    if (!strlen(file))
      return 0;

	text = read_file(file);
	if (!text)
	{
	    write("There was problem reading file:\n   " + file +
		"\nPlease make a bugreport.\n");
	    return 1;
	}

    tmp = lib_file->query_librarian();
    if (tmp && sizeof(tmp))
      libr = implode(map(tmp,capitalize),", ");
    else
      libr = "Krynn or leave a (bug) report in the library";

    if (lib_file->add_new_book(long + "\n",short,list,text))
    {
	write("You have now written a nice book. If you for some reason " +
	      "change your mind and don't want it to be published, " +
	      "mail " + libr + " and it will be removed.\n");     
	write("The book suddenly disappears.\n");
	set_alarm(1.0,0.0,"remove_object");
    }
    else
      write("There is already a book with this name in the library!\n" +
	    "Try a new listing ('blist').\n");

    return 1;
}

int
bread(string str)
{
    notify_fail("You haven't written anything in the book yet.\n");
    if (!strlen(file))
	return 0;

    clone_object(MOREOBJ)->more(file,1);
    return 1;
}

int
bedit(string str)
{
    seteuid(getuid(TO));
    if (!file)
      clone_object(BEDIT)->edit("done_editing");
    else
    {
	// Milan - here runtime error bad argument 1 to explode was generated
	str = read_file(file);
	if (!str)
	{
	    clone_object(BEDIT)->edit("done_editing");
	    /*
	      write("There was problem reading file:\n   " + file +
	      "\nPlease make a bugreport.\n");
	    */
	    return 1;
	}
	clone_object(BEDIT)->edit("done_editing",str,sizeof(explode(str,"\n")));
    }
    return 1;
}

void
done_editing(string text)
{
    /* need to check if there's text before storing it away??? */
    seteuid(getuid(TO));
    if (!file)
      file = TMP_BOOK + time();
    write_file(file, text);
    /* remove the tmp book before storing it */
}
