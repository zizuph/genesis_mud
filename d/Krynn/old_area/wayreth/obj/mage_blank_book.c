/*
 * A blank book for the mortals to write in, if they want.
 * Made by Nick
 *
 * Descriptions changed slighty by Jeremiah 95/06/30, for
 * the use in the library in the tower of High Sorcery.
 *
 * Latest update : Jeremiah 95/07/26
 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/tower/mage_lib.h"
#include <stdproperties.h>
#include <macros.h>

string file, short, long, list;

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
}

string
my_long()
{
    return "A brown book bound in soft leather. The pages of this book " +
           "are all blank. You can write in it and have it registrered " +
           "among the other books of the mages library.\n\n" +
           "You can use the following commands with this book:\n" +
           "  'bshort <description>' - Give the book a short description.\n" +
           "  'blong <description>'  - Give the book a long description.\n" +
           "  'bnote'                - Write the book.\n" +
           "  'blist <title>'        - Set how the book will be listed.\n" +
           "  'bread'                - Read this book.\n" +
           "  'bstore'               - Store the book, when ready.\n\n" +
           "Note: 'bshort', 'blong' or 'blist'  entered without any " +
           "description or title, will give you the current descriptions.\n";
}

void
init()
{
    ::init();

    ADA("bnote");
    ADA("blist");
    ADA("bshort");
    ADA("blong");
    ADA("bstore");
    ADA("bread");
}

int
blist(string str)
{
    if (!str)
    {
	write("This will set how your book should be listed, typically:\n" +
	    "Magic - a book about the use of magic.\n");
	if (strlen(list))
	    write("Current setting: " + list + "\n");
	return 1;
    }

    while(str[0] == ' ')     /* remove all spaces at start */
       str = extract(str,1);

    list = str;
    write("List set to.............: " + list + "\n");
    return 1;
}

int
blong(string str)
{
    if (!str)
    {
	write("This will set the long description of the book, typically:\n" +
	    "It's an old book bound in a soft red material. The front " +
            "of the book is beatifully decorated with golden ornaments " +
            "around a silvery 'D'.\n");
	if (strlen(long))
	    write("Current setting: " + long + "\n");
	return 1;
    }

    while(str[0] == ' ')     /* remove all spaces at start */
       str = extract(str,1);

    long = str;
    write("Long description set to.: " + long + "\n");
    return 1;
}

int
bshort(string str)
{
    if (!str)
    {
	write("This will set the short description of the book, typically:\n" +
	    "red golden book\n" +
	    "OBSERVE, not 'a red golden book'\n");
	if (strlen(short))
	    write("Current setting: " + short + "\n");
	return 1;
    }

    while(str[0] == ' ')     /* remove all spaces at start */
       str = extract(str,1);

    short = str;
    write("Short description set to: " + short + "\n");
    return 1;
}

int
bstore(string str)
{
    string *tmp;

    NF("You need to set both list, long and short descriptions.\n");
    if (!strlen(list) || !strlen(long) || !strlen(short))
	return 0;

    NF("You need to write a book first.\n");
    if (!strlen(file))
	return 0;

    tmp = explode(list, " ");
    if ((file_size(NEW_BOOKS + L(tmp[0])) > 0) ||
	(file_size(OLD_BOOKS + L(tmp[0])) > 0))
    {
	write("There is already a book called " + tmp[0] + ".\n" +
	    "Try a new listning.\n");
	return 1;
    }

    seteuid(getuid(TO));

    write_file(NEW_LIST, "\t" + C(list) + "\n");
    write_file(NEW_LONG + L(tmp[0]), C(long) + "\n");
    write_file(NEW_BOOKS + L(tmp[0]), read_file(file));
    write_file(NEW_SHORT + L(tmp[0]), short);

    write_file(NEW_LOG, C(TP->query_real_name()) + " wrote a book, " +
	    extract(ctime(time()), 4, 15) + ", named " + C(tmp[0]) + "\n");

    write("You have now completed a nice book. If you for some reason " +
        "change your mind and don't want it to be published, mail " +
        "Rastlin or Jeremiah and it will be removed.\n");     
    write("You put the book onto the shelves.\n");
    say(QCTNAME(TP) + " puts a new book onto the shelves.\n");

    call_out("remove_object", 1);
    return 1;
}

int
bread(string str)
{
    notify_fail("You haven't written anything in the book yet.\n");
    if (!strlen(file))
	return 0;

    TP->more(file, 0, TP->query_prop(PLAYER_I_MORE_LEN));
    return 1;
}


public int
done_writing(string text)
{
    /* temporarily save the book in the tmp dir */
    /* book is finally saved by using 'bstore'. */

    seteuid(getuid(TO));
    file = TMP_DIR + "tmp" + time();
    write_file(file, text);
    write("You finish writing and close the book.\n");
    say(QCTNAME(TP) + " finishes writing and closes the book.\n");

    return 1;
}


int
bnote(string str)
{
    if (strlen(file))
	write("NOTA BENE: If you write something the earlier writing will " +
	    "be lost.\n");

    write("You open the book and start writing.\n");
    say(QCTNAME(TP) + " opens a book and starts writing.\n");
    seteuid(getuid(TO));
    clone_object("/std/edit")->edit("done_writing", "");
    return 1;
}
