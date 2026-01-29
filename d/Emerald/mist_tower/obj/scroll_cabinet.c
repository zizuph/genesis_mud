/*
 * /d/Emerald/mist_tower/obj/scroll_cabinet.c
 *
 * A cabinet in the training room of the Vampire Guild.
 *
 * Copyright (c) ?? 1998 ?? by Shiva
 *
 * Revision History:
 *     10-3-00: (Gorboth) - added OBJ_M_NO_GET prop
 */
#pragma strict_types

inherit "/std/container";
inherit "/d/Emerald/mist_tower/library";

#include "/d/Emerald/common/guild/vamp/guild.h"
#include "/d/Emerald/sys/macros.h"

#include <stdproperties.h>
#include <std.h>

string *library_admin = ({});

public void mkbooks(mixed books);

public void
create_container()
{
    set_name("cabinet");
    set_adj("scroll");

    setuid();
    seteuid(getuid());

    set_library_name("cabinet");
    set_book_type("scroll");
    set_plural_book_type("scrolls");
    set_book_directory(VAMP_BOOK_DIR);
    set_book_approval_directory(VAMP_BOOK_DIR + "approval/");
    set_book_removal_directory(VAMP_BOOK_DIR + "removed/");
    set_borrow_required(1);

    create_library();

    set_long("A large, sturdy, wooden scroll cabinet.\n" + library_help());

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(OBJ_M_NO_GET, "The cabinet is fixed in place.\n");

    /* Use an alarm to call mkbooks to be sure that there are no eval-cost
     * errors
     */
    set_alarm(0.0, 0.0, &mkbooks(query_books() + query_approval_books()));
}

/*
 * Function name: mkbooks
 * Description:   In a standard library, the books are created when the
 *                player tries to borrow them.  Since we want the books
 *                to be visible inside the cabinet, though, we'll create
 *                them ahead of time and move them into the cabinet.
 * Arguments:     mixed books - The list of books to add.  They will be
 *                              processed in chunks to avoid eval-cost
 *                              errors.
 */
public void
mkbooks(mixed books)
{
    object book;
    int i;

    if (stringp(books))
    {
	books = ({ books });
    }

    for (i = 0; (i < sizeof(books)) && (i < 10); i++)
    {
        book = make_book(books[i]);
	configure_book(book, 
            query_book_path(books[i]) || query_approval_book_path(books[i]),
            books[i]);

	book->move(this_object(), 1);
    }

    books = books[10..];

    if (sizeof(books))
    {
	set_alarm(0.0, 0.0, &mkbooks(books));
    }
}

/*
 * Function name: prevent_leave
 * Description:   We don't want people taking books directly out of the
 *                cabinet.  They should use the "borrow" command.
 * Arguments:     The object that's being removed
 * Returns:       1 - the object cannot be removed
 *                0 - The object can be removed
 */
public int
prevent_leave(object ob)
{
    if (ob->id(query_book_id()))
    {
	write("Please use the \"borrow\" command to borrow a book.\n");
	return 1;
    }

    return 0;
}

/*
 * Function name: prevent_enter
 * Description:   We don't want people putting books directly into the
 *                cabinet.  They should use the "return" command.
 * Arguments:     The object that's being placed in the cabinet
 * Returns:       1 - the object cannot enter
 *                0 - The object can enter
 */
public int
prevent_enter(object ob)
{
    if (ob->id(query_book_id()))
    {
	write("Please use the \"return\" command to return a book.\n");
	return 1;
    }
   
    return 0;
}

/*
 * Function name: give_book
 * Description:   A standard library creates a new book when one is borrowed.
 *                Since our books are cloned already, we just want to find
 *                an existing one and move it.
 * Arguments:     see /lib/library:give_book
 */
public object
give_book(string text_filename, string name)
{
    object book = present(name);
    if (book)
    {
	book->move(this_player(), 1);
    }

    return book;
}

/*
 * Function name: return_book
 * Description:   A standard library simply removes books when they're
 *                returned.  We want to move the book back into the cabinet.
 * Arguments:     see /lib/library:return_book
 */
public int
return_book(object ob)
{
    library_return_hook(ob);
    ob->move(this_object(), 1);
    return 1;
}

/*
 * Funtion name: add_book
 * Description:  The standard library doesn't create a new book object when
 *               a new book is written.  For our library, we want a book
 *               cloned and added to the cabinet.
 * Arguments:    See /lib/library:add_book
 */
public int
add_book(string title, string summary, string author, 
         string text, int approval)
{
    if (!::add_book(title, summary, author, text, approval))
    {
	return 0;
    }

    mkbooks(title);
    return 1;
}

/*
 * Funtion name: add_book
 * Description:  Since our library maintains a set of book objects, we need
 *               to make sure they're removed when a book is taken out of
 *               the library.
 * Arguments:    See /lib/library:remove_book
 */
public void
remove_book(string title, string filename)
{
    object book;

    ::remove_book(title, filename);

    if (book = present(title))
    {
	book->remove_object();
    }
}

void
init()
{
    ::init();
    init_library();
}

/*
 * Function name: library_admin_access
 * Description:   Determine if this_player() is an administrator
 * Returns:       1/0 - administrator/not administrator
 */
public int
library_admin_access()
{
    if ((this_player()->query_vamp_covenmaster() &&
       	(this_player()->query_vamp_coven() == "Emerald")) ||
       	(member_array(this_player()->query_real_name(), library_admin) >= 0) ||
       	EMRLD_WIZ(this_player()) ||
       	(SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 
       	WIZ_ARCH))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}

/*
 * Function name: library_write_access
 * Description:   Determine if this_player() has permission to write books
 *                in the library
 * Returns:       1/0 - permission/no permission
 */
public int
library_write_access()
{
    if (IS_MEMBER(this_player()) || EMRLD_WIZ(this_player()) ||
       (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 
       WIZ_ARCH))
    {
        return 1;
    }

    write("You do not have permission to do that.\n");
    return 0;
}
