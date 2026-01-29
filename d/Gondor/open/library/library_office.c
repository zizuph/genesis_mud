/*
 *  library_office.c
 *
 *  a set of functions to inherit in your room to make it work as
 *  the librarian's office
 *
 *  Created by Gresolle@Genesis
 *  Modified by Olorin@Genesis, January 1995
 */
#pragma save_binary
#pragma strict_types

mapping books;
static  string lsave,
               lib,
               log_file;

public string
lib_hook_office_desc()
{
    return "You notice a few books waiting for approval.\n";
}

/*
 * Function name: check_desc
 * Description:   add notice on new books to room desc
 * Arguments:	  none
 * Returns:	  0
 */
void
check_desc()
{
    if (sizeof(m_indexes(books)))
        this_object()->change_my_desc(lib_hook_office_desc(), this_object());
    else
        this_object()->remove_my_desc(this_object());
}

void set_save_path(string s) { lsave = s; }

void set_log_file(string s) { log_file = s; }

void set_library(string s) { lib = s; }

/*
 * Function name: set_up_office
 * Description:   set up the office ;-)
 *		  call from create_room()
 * Arguments:	  none
 * Returns:	  0
 */
public void
set_up_office()
{
    seteuid(getuid(this_object()));
    books=([]);

    if (file_size(lsave + ".o") >= 0)
        restore_object(lsave);

    check_desc();
}

/*
 * Function name: add_book
 * Description:   add a book to the office
 * Arguments:	  same as for add_book in the library
 * Returns:	  error msg or 0
 */
public string
add_book(string nbnam,string nbdesc,string fnam,int flag)
{
    nbnam = capitalize(lower_case(nbnam));
    if (!books[nbnam])
        books[nbnam]=({nbdesc,fnam,flag});
    else
        return "Too bad. That book already exists.\n";

    tell_room(this_object(),"Someone has just added a book to the library.\n");
    seteuid(getuid(this_object()));
    save_object(lsave);
    check_desc();
    return 0;
}

public int
lib_hook_office_not_exist()
{
    notify_fail("That book does not exist.\n");
    return 0;
}

/*
 * Function name: add_book_to_library
 * Description:   add a book to the library
 * Arguments:	  s - name of the book
 * Returns:	  1 if success, 0 else
 */
public int
add_book_to_library(string s)
{
    s = capitalize(lower_case(s));

    if (!sizeof(books[s]))
        return lib_hook_office_not_exist();
  
    lib->add_book(s,books[s][0],books[s][1],books[s][2]);
    write("You add the book to " + lib->query_library_name() + ".\n");
    seteuid(getuid(this_object()));

    log_file(log_file, "LIBRARY: " + this_player()->query_name()
      + " added the book " + s + " (" + books[s][0]
      + ") on "+ctime(time())+".\n");

    books = m_delete(books,s);
    save_object(lsave);
    check_desc();
    return 1;
}
  
public void
lib_hook_office_book_reject()
{
    write("You reject the book and toss it into the trashcan.\n");
}

/*
 * Function name: read_book
 * Description:   read a book submitted for inclusion to the library
 * Arguments:	  s - name of the book
 * Returns:	  1 if success, 0 else
 */
public int
read_book(string s)
{
    s = capitalize(lower_case(s));

    if (!sizeof(books[s]))
        return lib_hook_office_not_exist();

    if (file_size(books[s][1]) > 1000)
        this_player()->more(read_file(books[s][1]), 0);
    else
        cat(books[s][1]);
    write("\n");
    return 1;
}

/*
 * Function name: remove_book
 * Description:   remove a book submitted by a player
 * Arguments:	  s - name of the book
 * Returns:	  1 if success, 0 else
 */
int
remove_book(string s)
{
    s = capitalize(lower_case(s));

    if(!books[s])
        return lib_hook_office_not_exist();

    rm(books[s][1]);

    seteuid(getuid(this_object()));
    log_file(log_file, "LIBRARY: " + this_player()->query_name()
      + " removed the book " + s + " (" + books[s][0]
      + ") on "+ctime(time())+".\n");

    books = m_delete(books,s);
    save_object(lsave);
    lib_hook_office_book_reject();
    check_desc();
    return 1;
}

/*
 * Function name: list_books
 * Description:   list the books submitted by players
 * Arguments:	  s - argument given to the command
 * Returns:	  1 if success, 0 else
 */
int
list_books(string s)
{
    int     i;
    string *apa;

    notify_fail("List what?\n");
    if (strlen(s) && s != "books")
        return 0;

    apa = m_indexes(books);
    
    if(!sizeof(apa))
        write("There are no books here.\n");
    else
        write("Books waiting to be accepted:\n");

    for (i = 0;i < sizeof(apa); i++)
        write(apa[i]+": "+books[apa[i]][0]+"\n");

    return 1;
}

public string query_library() { return lib; }

/*
 * Function name: init_office
 * Description:   set up commands, call from init()
 * Arguments:	  none
 * Returns:	  0
 */
void
init_office()
{
    add_action(list_books,  "list");
    add_action(read_book,   "read");
    add_action(remove_book, "reject");
    add_action(add_book_to_library, "add");
}

