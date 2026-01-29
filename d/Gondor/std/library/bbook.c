/*
 * /d/Gondor/std/library/bbook.c
 *
 * A blank book for the mortals to write in, if they want.
 * Made by Nick
 * Updated for the new std/library by Aridor 12/96
 *
 * Modification log:
 * Gwyneth 1/29/01: Updated from /d/Krynn/std/library/bbook.c 
 *                  for Gondorian use.
 */
inherit "/std/object";

#include <stdproperties.h>
#include "lib.h"

#define  TMP_BOOK  "/d/Gondor/std/library/tmp/tmp"

/* Global variables */
string file, short, long, list;
string lib_long = "some great library";
string lib_file = "/d/Gondor/std/library/library";

/* Prototypes */
public string my_long();

public void
create_object()
{
    set_name("book");
    add_name("special_book");
    set_adj(({"brown", "leather"}));

    set_long(&my_long());

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 0);

    lib_file = file_name(previous_object());
    lib_long = lib_file->query_lib_long();    
}

public string
my_long()
{
    return ("A brown leather book. You can write in it and later put it " +
        "in " + lib_long + ".\n" +
        "'bshort' to give the book a short description,\n" +
        "'blong'  to give a long description of the book,\n" +
        "'bedit'  to write the book. Using\n" +
        "'blist'  will set how the book will be listed in the " +
        "library's catalog.\n" +
        "'bstore' the book when ready. It will work from anywhere " +
        "in the Realms. Use\n" +
        "'bread'  to read this book.\n");
}

public void
remove_object()
{
    if (file)
        rm(file);
    ::remove_object();
}


public int
blist(string str)
{
    if (!strlen(str))
    {
        write("This will set how your book should be listed in the library's " +
            "catalog, typically:\n" +
            "Ithilien - a book with a map of Ithilien.\n");
        if (strlen(list))
            write("Current setting: " + list + "\n");
        return 1;
    }

    list = str;
    write("Listing set to: " + list + "\n");
    return 1;
}

public int
blong(string str)
{
    if (!strlen(str))
    {
        write("This will set the long description of the book, typically:\n" +
            "It's an old book containing an old map of Ithilien.\n");
        if (strlen(long))
            write("Current setting: " + long + "\n");
        return 1;
    }
    
    long = str;
    write("Description set to: " + long + "\n");
    return 1;
}

public int
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

public int
bstore(string str)
{
    mixed tmp;
    string libr;

    if (!strlen(list) || !strlen(long) || !strlen(short))
    {
        notify_fail("You need to set list, long and short descriptions!\n");
        return 0;
    }

    if (!strlen(file))
    {
        notify_fail("You need to write a book first.\n");
        return 0;
    }

    tmp = lib_file->query_librarian();
    if (tmp && sizeof(tmp))
        libr = implode(map(tmp, capitalize), ", ");
    else
        libr = "Gondor or leave a (bug) report in the library";
    if (lib_file->add_new_book(long + "\n", short, list, read_file(file)))
    {
        write("You have now written a nice book. If you for some reason " +
            "change your mind and don't want it to be published, " +
            "mail " + libr + " and it will be removed.\n");     
        write("The book suddenly disappears.\n");
        set_alarm(1.0, 0.0, &remove_object());
    }
    else
    {
      write("There is already a book with this name in the library!\n" +
          "Try a new listing ('blist').\n");
    }

    return 1;
}

public int
bread(string str)
{
    if (!strlen(file))
    {
        notify_fail("You haven't written anything in the book yet.\n");
        return 0;
    }

    clone_object(MOREOBJ)->more(file, 1);
    return 1;
}

public int
bedit(string str)
{
    seteuid(getuid(this_object()));
    if (!file || !file_size(file))
        clone_object(BEDIT)->edit("done_editing");
    else
        clone_object(BEDIT)->edit("done_editing", read_file(file),
				sizeof(explode(read_file(file), "\n")));
    return 1;
}

public void
done_editing(string text)
{
    /* need to check if there's text before storing it away??? */
    seteuid(getuid(this_object()));
    if (!file)
        file = TMP_BOOK + time();
    write_file(file, text);
    /* remove the tmp book before storing it */
}

public void
init()
{
    ::init();

    add_action(bedit, "bedit");
    add_action(blist, "blist");
    add_action(bshort, "bshort");
    add_action(blong, "blong");
    add_action(bstore, "bstore");
    add_action(bread, "bread");
}

