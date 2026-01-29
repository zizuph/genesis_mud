/*
 * Designed to work the same as /lib/library.c
 * - Rhyn
*/

#include <stdproperties.h>
#include <files.h>

#define MAX_TITLE_SIZE 20

private string book_directory, default_directory,
    approval_directory, removal_directory;

private int initialized = 0;

private mapping shelves = ([ ]); // "shelf_name" : ({ "titles", "here" })
private mapping books = ([ ]); /* "title" : ({ file, shelf, author, summary */

public void create_library();
public void init_library();
public string library_help();

public string get_book_author(string file);
public string get_book_title(string file);
public string get_book_summary(string file);

private object
create_book(string file)
{
    object book = clone_object("/std/scroll");
    book->set_long("A book entitled \"" + get_book_title(file) + "\".\n");
    book->set_name("book");
    book->set_pname("books");
    book->add_name("book_" + book_directory + "_obj");
    book->add_prop(OBJ_I_NO_DROP, 1);
    book->set_file(file);
    return book;
}

public string
get_next_file(string dir)
{
    string *files;
    int i, tmp, last = -1;

    setuid();
    seteuid(getuid());

    files = get_dir(dir);

    for(i = sizeof(files) - 1; i >= 0; i--)
    {
        if (!sscanf(files[i], "book%d", tmp))
        {
           continue;
        }

        if (tmp > last)
        {
            last = tmp;
        }
    }

    return dir + "book" + (last + 1);
}

public int
library_exit_block()
{
    return !!present("book_" + book_directory + "_obj", this_player());
}

public int
library_admin_access()
{
    return (!!this_player()->query_wiz_level());
}

public int
_borrow(string str)
{
    if(!str || !strlen(str) || member_array(str, m_indices(books)) == -1)
    {
        return notify_fail("Usage: " + query_verb() + " <title>\n");
    }

    create_book(books[str][0])->move(this_player(), 1);
    write("You borrow a book.\n");
    return 1;
}

public int
_return(string str)
{
    object book = present("book_" + book_directory + "_obj", this_player());

    if(!str || str != "book" || !book)
        return notify_fail("Return what?\n");

    book->remove_object();
    write("You return the book.\n");
    return 1;
}

public int
_list(string str)
{
    string *list_shelves = sort_array(m_indices(shelves)), *titles, *book;
    int i, j, sz;

    if(!library_admin_access())
    {
        list_shelves -= ({ "approval", "removed" });
    }

    if(str && strlen(str))
    {
        if(str == "shelves")
        {
            write(implode(map(list_shelves, capitalize), "\n") + "\n");
            return 1;
        } else if(member_array(str, list_shelves) != -1) {
            titles = sort_array(shelves[str]);
            sz = sizeof(titles);

            if(sz == 0)
                return notify_fail("No titles in \"" + str + "\".\n");

            for(i=0; i<sizeof(titles); i++)
            {
                book = books[titles[i]];
                write(sprintf("%-" + MAX_TITLE_SIZE + "s %-13s %-=40s\n",
                    titles[i], book[2], book[3]));
            }

            return 1;
        }

        return notify_fail("Usage: " + query_verb() + " [shelf]\n");
    }

    list_shelves -= ({ "approval", "removed" });

    for(i=0; i<sizeof(list_shelves); i++)
    {
        titles = sort_array(shelves[list_shelves[i]]);
        sz = sizeof(titles);

        for(j=0; j<sz; j++)
        {
            book = books[titles[j]];
            write(sprintf("%-" + MAX_TITLE_SIZE + "s %-13s %-=40s\n",
                titles[j], book[2], book[3]));
        }
    }

    return 1;
}

public int
_approve(string str)
{
    if(!library_admin_access())
    {
        return notify_fail("You do not have permission to do that.\n");
    }

    if(!str || !strlen(str) || member_array(str, m_indices(books)) == -1)
    {
        return notify_fail("Usage: " + query_verb() + " <title>\n");
    }

    if(books[str][1] != "approval")
    {
        return notify_fail("The book \"" + str + "\" is not subject to approval.\n");
    }

    rename(books[str][0], get_next_file(default_directory));
    create_library();

    write("Ok.\n");
    return 1;
}

public int
_deny(string str)
{
    if(!library_admin_access())
        return notify_fail("You do not have permission to do that.\n");

    if(!str || !strlen(str) || member_array(str, m_indices(books)) == -1)
        return notify_fail("Usage: " + query_verb() + " <title>\n");

    if(books[str][1] != "approval")
        return notify_fail("The book \"" + str + "\" is not subject to approval.\n");

    rm(books[str][0]);
    create_library();

    write("Ok.\n");
    return 1;
}

public int
_discard(string str)
{
    if(!library_admin_access())
        return notify_fail("You do not have permission to do that.\n");

    if(!str || !strlen(str) || member_array(str, m_indices(books)) == -1)
        return notify_fail("Usage: " + query_verb() + " <title>\n");

    if(books[str][1] == "approval")
        return notify_fail("The book \"" + str + "\" is still subject to approval.\n");

    rename(books[str][0], get_next_file(removal_directory));
    create_library();

    write("Ok.\n");
    return 1;
}

public int
_classify(string str)
{
    string shelf, title;

    if(!library_admin_access())
        return notify_fail("You do not have permission to do that.\n");

    if(!str || !strlen(str) || member_array((shelf = explode(str, " ")[0]),
        m_indices(shelves)) == -1 || member_array(
        (title = implode(explode(str, " ")[1..], " ")), m_indices(books)) == -1)
        return notify_fail("Usage: " + query_verb() + " <shelf> <title>\n");

    rename(books[title][0], get_next_file(book_directory + shelf + "/"));
    create_library();

    write("Title \"" + title + "\" moved to shelf \"" + shelf + "\".\n");
    return 1;
}

private int
write_text(object tp, string title, string summary, string text)
{
    string output;

    if(!text || !strlen(text))
    {
        write("Aborted.\n");
        return 1;
    }

    write_file(get_next_file(approval_directory), sprintf("%|75s\n%|75s\n%|75s\n",
        title, summary, "by " + tp->query_cap_name()) + text + "\n");
    create_library();

    write("Written!\n");
    return 1;
}

private int
write_summary(object tp, string title, string summary)
{
    if(summary == "~q")
        return 0;

    clone_object(EDITOR_OBJECT)->edit(&write_text(tp, title, summary));
    return 1;
}

public int
_write(string str)
{
    if(!str || !strlen(str))
        return notify_fail("Usage: " + query_verb() + " <title>\n");

    if(strlen(str) > MAX_TITLE_SIZE)
        return notify_fail("Title cannot be more than 20 characters long.\n");

    if(books[str])
        return notify_fail("The title \"" + str + "\" is already in use.\n");

    write("Enter a short summary of the book. (~q to quit)\n> ");
    input_to(&write_summary(this_player(), str));
    return 1;
}

public void
create_library()
{
    string *files, *dirs, file, shelf, title, author, summary;
    int i, j;
    mapping newshelves = ([]), newbooks = ([]);

    if(!book_directory || !strlen(book_directory))
        return; // No directory!

    setuid();
    seteuid(getuid());

    dirs = sort_array(filter(map(get_dir(book_directory), &operator(+)(book_directory)
        @ &operator(+)(, "/")), &operator(==)(-2) @ file_size));

    if(!sizeof(dirs))
        return; // No shelves!

    for(i=0; i<sizeof(dirs); i++)
    {
        shelf = (dirs[i])[strlen(book_directory)..strlen(dirs[i])-2];
        files = filter(map(get_dir(dirs[i]), &operator(+)(dirs[i])),
            &operator(<)(0) @ file_size);
        newshelves[shelf] = ({ });

        for(j=0; j<sizeof(files); j++)
        {
            file = files[j];
            title = get_book_title(file);
            summary = get_book_summary(file);
            author = get_book_author(file);
            newshelves[shelf] += ({ title });
            newbooks[title] = ({ file, shelf, author, summary });
        }
    }

    shelves = newshelves;
    books = newbooks;
}

public void
init_library()
{
    add_action(_borrow, "borrow");
    add_action(_return, "return");
    add_action(_list, "list");
    add_action(_write, "write");

    if(!library_admin_access())
        return;

    add_action(_approve, "approve");
    add_action(_deny, "deny");
    add_action(_discard, "discard");
    add_action(_classify, "classify");
}

public string
library_help()
{
    function help_cmd = &sprintf("%-33s - %-=40s\n", , );

    string str = "Library commands available:\n" +
        help_cmd("List " + "[<shelf>]", "List books in the library.");

    str += help_cmd("List shelves", 
                    "List shelves in the library.");

    str += 
        help_cmd("Borrow <title>",
                 "Borrow a book for reading.") +
        help_cmd("Return <book>",
                 "Return a book to the library.");

    str += help_cmd("Write <title>",
        "Write a book and submit it to the library.");

    str += "\nAdministrator commands available:\n";

    str += help_cmd("Approve <title>",
        "Approve a book for inclusion in the library.");

    str +=
        help_cmd("Deny <title>",
             "Deny a book from inclusion in the library.");

    str += help_cmd("Discard <title>", "Remove a book from the library.");

    str += help_cmd("Classify <shelf> <title>",
                    "Assign a book to a shelf.");

    return str + "\n";
}

public void
set_book_directory(string str)
{
    book_directory = str;
}

public void
set_approval_directory(string str)
{
    approval_directory = book_directory + str + "/";
}

public void
set_removal_directory(string str)
{
    removal_directory = book_directory + str + "/";
}

public void
set_default_directory(string str)
{
    default_directory = book_directory + str + "/";
}

public string
get_book_title(string file)
{
    return implode(explode(read_file(file, 1, 1)[..-2], " ") -
        ({ "" }), " ");
}

public string
get_book_summary(string file)
{
    return implode(explode(read_file(file, 2, 1)[..-2], " ") -
        ({ "" }), " ");
}

public string
get_book_author(string file)
{
    return implode(explode(read_file(file, 3, 1)[..-2], " ") -
        ({ "" }), " ");
}
