//-*-C++-*-
// file name:      library.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";
inherit "/lib/library";

#include <ss_types.h>
#include <math.h>
#include <composite.h>
#include <std.h>

#define DIARY_LOG    (LOG_DIR+"diary")

string * Removed_books=({ });

public void create_vamp_room()
{

    set_short("Private Library");
    set_long("This chamber was once a section of catacombs that "+
        "was long ago converted into a repository for books, parchments, "+
        "scrolls, and other documents. It is very dry and only somewhat "+
        "dusty, and the air smells faintly of old bones. Small and "+
        "utilitarian, this place is intended for storage of secret writings "+
        "and not much else.\n");

    add_item(({"books", "scrolls"}), 
        "There are so many of them that they are overflowing the "+
        "shelves. You find yourself wondering what knowledge they "+
        "contain, and if you have the ability to read even a small "+
        "fraction of them.\n");
    add_item(({"floor"}), "The floor is level, and covered in "+
        "a fine layer of dust that has been churned by the passage "+
        "of several feet.\n");
    add_item(({"ceiling"}), "The ceiling is the same "+
        "height as most of the other ceilings in this place.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "completely unadorned and unpolished.\n");
    add_cmd_item(({"book", "books","scrolls", "scroll"}), ({"get", "take"}), 
        "No matter how hard you try, it seems to evade your grasp.\n");
    add_item(({"darkness"}), 
        "Ebbing and flowing through the chamber, this beckoning darkness "+
        "has a substance to it that no amount of light can conquer.\n");
    add_cmd_item(({"air", "blood"}), ({"smell", "sniff", "breathe"}),
        "The air is ripe with the coppery scent of blood.\n");

    
    add_exit("library","east");

    
    /* Indicate if we want players to have to "borrow" a book in
     * order to read it.
     */
    set_borrow_required(1);

    set_book_directory(BOOK_DIR +"private/");
    set_book_approval_directory(BOOK_DIR+"private/pending/");
    set_book_removal_directory(BOOK_DIR+"private/removed/");
  
    add_book_shelf(({ "vampire", "maps" }));
        
    create_library();

    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", library_help());
    add_cmd_item("sign","read", library_help());
    add_item(({"bookshelves","bookshelf","stone bookshelves", "shelves",
        "shelf"}),
        "They appear to be carved into the stone.\nAbove the shelves is "+
        "posted a sign that reads:\n\nYou do not have to borrow the books "+
        "inorder to read them.\n@@library_help@@\n");

}



int 
do_step(string str)
{
/*

    if (!IS_VAMP(TP))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (TP->query_stat(SS_OCCUP < 150))
    {
        notify_fail("What?\n");
        return 0;
    }
*/
    notify_fail("Are you trying step into the darkness?\n");
    if (!parse_command(str, ({ }), "'in' / 'into' [the] 'darkness'"))
        return 0;    

    write_file(DIARY_LOG,ctime(time())+" I noticed " + 
        " "+capitalize(TP->query_real_name()) +" entering the sepulchre.\n");
    write("You step into the darkness which ebbs and flows in the chamber.\n");
    TP->move_living("X", "library_e", 1, 0);
    return 1;
}


public void init()
{
    ::init();

    add_action(do_step, "walk");
    add_action(do_step, "step");

    
    init_library();    
}

/*
 * Function name: library_list_access
 * Description:   Redefine this to limit permission to list books
 * Returns:       1 - this_player() is permitted to list books
 *                0 - this_player() is not permitted to list books
 */
public int
library_list_access()
{
    if (!IS_VAMP(TP))
    {
        write("You are disallowed from using this library.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: library_borrow_access
 * Description:   Redefine this function to limit permission to borrow books
 * Returns:       1 - this_player() is permitted to borrow a book
 *                0 - this_player() is not permitted to borrow a book
 */
public int
library_borrow_access()
{
    if (!IS_VAMP(TP))    {
        write("You are disallowed from using this library.\n");
        return 0;
    }

    return 1;
}
/*
 * Function name: library_admin_access
 * Description:   Limit library administration abilities to certain
 *                people.
 * Returns:       1 - this_player() has administration powers
 *                0 - this_player() does not have administration powers
 */
public int
library_admin_access()
{
    if (!IS_VAMP(TP))
    {
        write("You are disallowed from administering this library.\n");
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
library_write_access()
{
    if (!IS_VAMP(TP))    
    {
        write("You are disallowed from using this library.\n");
        return 0;
    }

    return 1;
}

/*
 * Halved the auto-mread limit and changed startline to strip
 * book headers for when reading.
 */
public void
library_read_book(string text_filename, string book_name, int mread)
{
    setuid();
    seteuid(getuid());

    if (mread || (file_size(text_filename) > 2000))
        this_player()->more(read_file(text_filename, 4));
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
    string *adjs = ({ "dark", "cloth-bound", "gold-embossed",
        "fragile", "parchment", "illuminated", "vellum", "dusty", 
        "musty", "crumbling", "aged", "leather-bound", "ancient",
        "faded", "worn", "blood-stained", "well-preserved" });
    int sz, index;
    string adj, nm;

    ::library_configure_book (book, text_filename, book_name);

    sz = sizeof(adjs);
    nm = book_name;
    /* parse out spaces: name_to_random will choke on them */
    nm = implode(explode(nm, " "), ""); 
    index = NAME_TO_RANDOM(nm, 13254, sz);

    if ((index >= 0) && (index < sizeof(adjs)))
        adj = adjs[index];
    else
        adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
}


void leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
        object * books=filter(deep_inventory(ob), return_access);
        
        write("As you leave you return "+COMPOSITE_DEAD(books)+", lest " +
            "precious knowledge be lost or acquired by our enemies.\n");
        
        map(books,return_it);
    }

}

/*
 * Function name: get_books
 * Description:   Get the full pathnames of all book files in a given directory
 * Arguments:     string dir - the directory to search
 * Returns:       An array of pathname strings
 */
public string *
get_books(string dir)
{
    string * books=::get_books(dir);
    books-=Removed_books;
    
    return books;
}

public string * get_removed_books()
{
    return Removed_books;
}

/*
 * Function name: library_borrow_hook
 * Description:   Redefine this to alter the message given when a
 *                user borrows or reads a book
 * Arguments:     object book  - the book borrowed
 *                string title - the title of the book
 */
public void
library_borrow_hook(object book, string title)
{
    Removed_books += ({ book->query_file() });    
    update_books();
    ::library_borrow_hook(book,title);
}

/*
 * Function name: library_return_hook
 * Description:   Redefine this to alter the message given when a
 *                user returns a book
 * Arguments:     object book - the book being returned
 */
public void
library_return_hook(object book)
{
    Removed_books -= ({ book->query_file() });    
    update_books();
    ::library_return_hook(book);
}

