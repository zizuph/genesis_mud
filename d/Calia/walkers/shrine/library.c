
/* 
 * The Walkers library.
 * Walkers may write books here. The Council must approve books before
 * they are available for general readership, and has the right to 
 * delete books. 
 * This code is pretty much self-contained. 
 *
 * Coded by Maniac 18-20/8/96. 
 *
 * Additions by Maniac 23/9/96, 25/10/96, 22/11/96.
 * Changed for Walkers by Jaacar on December 12th, 1997.
 */ 

#pragma save_binary 
#pragma no_inherit


#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "defs.h"

#include COUNCIL_HEADER

#define PRIVATE_BOOK_DIR (TEXTS+"library/")

#define BOOK_EXISTS(id) (file_size(PRIVATE_BOOK_DIR+id) >= 0) 

#define EDIT "/obj/edit"
#define WALKER_S_BOOK_TITLE "_walker_s_book_title"
#define WALKER_AS_BOOK_INFO "_walker_as_book_info" 
#define APPROVED "approved"
#define AWAITING "awaiting"

inherit "/std/room"; 
inherit "/d/Calia/walkers/specials/code";

void
create_room()
{
    set_short("Walker library");
    set_long("You stand in the private library for the Walkers. " +
             "Here you may read books that fellow Walkers have " +
             "written, or perhaps write some of your own. " + 
             "Your eyes are drawn to the oak shelves, which hold " +
             "volumes of all descriptions.\n"); 

    add_item(({"books", "shelves", "shelf", "bookshelves", "oak shelves"}), 
           "The oak shelves hold various books. You could try the " +
           "<browse>ing to find out what titles " +
           "exist. This will give you a list of books, which includes " +
           "the unique identifier (ID), title and author.  " +
           "When you want to <read>, <spam>, <bookedit> or <delete> a " +
           "book you should use its ID as the argument to the command. " +
           "The Council " +
           "may delete or edit any books, while other Walkers may " +
           "delete or edit books which they themselves wrote. " +
           "You can also <write> a book, in which case you should " + 
           "give the book _title_ as the argument. " +
           "This is a good opportunity for guild members to write " +
           "texts that will benefit the guild as a whole in some way! " +
           "Once you have written a book the Council will examine it " +
           "and, if it is <approve>d, it will be made available for " +
           "general readership in this library.\n");  

    add_prop(ROOM_I_INSIDE, 1); 

    add_exit(WALKER_SHRINE+"herbshop","west",0,1);
    add_exit(WORSHIP_SHRINE+"pboard","north",0,1);
}


int
query_prevent_shadow()
{
    return 1;
}


void
done_writing(string message)
{
    object tp = this_player(); 
    string n = tp->query_real_name(); 
    string *book, path, book_id; 
    int i; 

    if (message == "")  { 
        tp->remove_prop(WALKER_S_BOOK_TITLE); 
        return;
    } 

    if (strlen(message) < 180) { 
        tp->catch_msg("That would fit on a grain of rice! The librarian " +
                      "won't take it.\n"); 
        tp->remove_prop(WALKER_S_BOOK_TITLE); 
        return;
    }

    i = 1; 
    book_id = (n + i); 
    while (BOOK_EXISTS(book_id)) { 
        i++;  
        book_id = (n + i); 
    }

    path = (PRIVATE_BOOK_DIR + book_id); 

    book = ({ "", "", "", "" }); 

    if (!stringp(book[0] = tp->query_prop(WALKER_S_BOOK_TITLE))) { 
        tp->catch_msg("Ack! Lost your book title! Please re-enter your " +
                      "book.\n"); 
        return;
    }

    tp->remove_prop(WALKER_S_BOOK_TITLE); 

    book[1] = n;

    book[2] = AWAITING; 

    book[3] = message; 

    write_file(path, book[0] + "\n" + book[1] + "\n" + 
                     book[2] + "\n" + book[3]); 

    tp->catch_msg("Ok, the book ID is " + book_id + ".\n"); 
}


void
done_editing(string message)
{
    object tp = this_player(); 
    string n = tp->query_real_name(); 
    string *book, path, book_id; 
    int i; 

    if (message == "")  { 
        tp->remove_prop(WALKER_AS_BOOK_INFO); 
        return;
    } 

    if (strlen(message) < 180) { 
        tp->catch_msg("That would fit on a grain of rice! The librarian " +
                      "won't take it.\n"); 
        tp->remove_prop(WALKER_AS_BOOK_INFO); 
        return;
    }

    book = tp->query_prop(WALKER_AS_BOOK_INFO); 
    tp->remove_prop(WALKER_AS_BOOK_INFO); 

    if (!pointerp(book) || (sizeof(book) != 4)) { 
        tp->catch_msg("Ack! Lost your book details! You will have to " +
                      "re-edit the book.\n"); 
        return;
    }

    book_id = book[0]; 
    book = exclude_array(book, 0, 0);  
    book += ({ message }); 

    path = (PRIVATE_BOOK_DIR + book_id); 

    if (!rm(path)) { 
        tp->catch_msg("Oops, ran into problems when trying to " +
                      "remove the old copy.\n"); 
        return;
    } 

    write_file(path, book[0] + "\n" + book[1] + "\n" + 
                     book[2] + "\n" + book[3]); 

    tp->catch_msg("Ok, the book " + book_id + " has been edited.\n"); 
}


int
write_book(string str)
{
    object tp = this_player(); 

    if (!stringp(str) || !strlen(str)) {  
         notify_fail("Write <book title>\n"); 
         return 0;
    }

    if (strlen(str) < 3) { 
        notify_fail("That title is too short.\n"); 
        return 0;
    } 

    if (strlen(str) > 50) { 
        notify_fail("That title is too long, please think up something " + 
                    "shorter!\n"); 
        return 0;
    }

    if (!is_walker(tp)) { 
         notify_fail("You are not a Walker, you may not write books here.\n"); 
         return 0;
    } 

    tp->add_prop(WALKER_S_BOOK_TITLE, str); 
    clone_object(EDIT)->edit("done_writing"); 
    return 1;
}


/* 
 * If flag is set, read in the book body, otherwise 
 * just author, title and status. 
 */ 
string 
*get_book(string path, int flag)
{
    string title, author, st, body;     

    title = read_file(path, 1, 1); 
    title = explode(title, "\n")[0];
    author = read_file(path, 2, 1); 
    author = explode(author, "\n")[0]; 
    st = read_file(path, 3, 1); 
    st = explode(st, "\n")[0]; 

    if (flag) 
        body = read_file(path, 4); 
    else
        body = ""; 

    return ({title, author, st, body}); 
}



int
read_book(string str)
{
    object tp = this_player(); 
    string *book, path, n; 

    n = tp->query_real_name(); 

    if (!stringp(str) || !strlen(str)) {  
         notify_fail("Read <book ID>\n"); 
         return 0;
    }

    if (!BOOK_EXISTS(str)) { 
        notify_fail("There is no book with that ID.\n");  
        return 0;
    }

    path = (PRIVATE_BOOK_DIR + str); 
    book = get_book(path, 1); 

    if ((book[2] != APPROVED) &&  
        (book[1] != n) && 
        !COUNCIL_CODE->is_council_member(n) && 
        !(SECURITY->query_wiz_dom(n) == "Calia")) { 
        notify_fail("That book has not been approved yet so you can't " +
                    "read it.\n"); 
        return 0;
    } 

    if (query_verb() == "spam") { 
        if (strlen(book[3]) <= 5000) { 
           tp->catch_msg("You spam the book entitled " + book[0] + ", by " +
                         capitalize(book[1]) + ".\n\n" + book[3]); 
           return 1;
        } 
        else 
            tp->catch_msg("That book is too long to spam reasonably!\n"); 
    } 

    tp->more("You read the book entitled " + book[0] + ", by " +
             capitalize(book[1]) + ".\n\n" + book[3]); 
    return 1;
}


int
edit_book(string str)
{
    object tp = this_player(); 
    string *book, path, n; 

    n = tp->query_real_name(); 

    if (!stringp(str) || !strlen(str)) {  
         notify_fail("Try `bookedit <book ID>'\n"); 
         return 0;
    }

    if (!BOOK_EXISTS(str)) { 
        notify_fail("There is no book with that ID.\n");  
        return 0;
    }

    path = (PRIVATE_BOOK_DIR + str); 
    book = get_book(path, 1); 

    if ((book[1] != n) && 
        !COUNCIL_CODE->is_council_member(n) && 
        !(SECURITY->query_wiz_dom(n) == "Calia")) { 
        notify_fail("You are not allowed to edit that book.\n"); 
        return 0;
    } 

    tp->add_prop(WALKER_AS_BOOK_INFO, ({str, book[0], book[1], AWAITING})); 
    clone_object(EDIT)->edit("done_editing", book[3]); 

    return 1;
}


int
delete_book(string str)
{
    object tp = this_player(); 
    string *book, path; 
    string n = tp->query_real_name(); 

    if (!stringp(str) || !strlen(str)) {  
         notify_fail("Delete <book ID>\n"); 
         return 0;
    }

    if (!is_walker(tp)) { 
         notify_fail("You are not a Walker, you may not delete books here.\n"); 
         return 0;
    } 

    if (!BOOK_EXISTS(str)) { 
        notify_fail("There is no book with that ID!\n");  
        return 0;
    }

    path = (PRIVATE_BOOK_DIR + str); 
    book = get_book(path, 0);   

    if ((book[1] != n) && 
        !COUNCIL_CODE->is_council_member(n) &&
        !(SECURITY->query_wiz_dom(n) == "Calia")) { 
        notify_fail("You do not have the authority to delete that book.\n"); 
        return 0;
    }

    if (rm(path))  { 
        tp->catch_msg("Ok.\n"); 
        return 1;
    }
    else { 
        notify_fail("Strange, the librarian couldn't delete that book, " +
                    "please leave a bug report.\n"); 
        return 0;
   } 
}


int
browse(string str)
{
    string *ids, *book, msg, n; 
    object tp = this_player(); 
    int a, i,spec; 

    n = tp->query_real_name(); 

    ids = get_dir(PRIVATE_BOOK_DIR); 

    if (!sizeof(ids)) { 
        tp->catch_msg("There aren't any books to browse at the moment!\n"); 
        return 1;
    } 

    spec = (COUNCIL_CODE->is_council_member(n) || 
            (SECURITY->query_wiz_dom(n) == "Calia")); 

    a = 0; 
    msg = ""; 

    for (i = 0; i < sizeof(ids); i++) { 
        book = get_book(PRIVATE_BOOK_DIR + ids[i], 0); 
        if (book[2] == AWAITING) { 
            if (spec || (book[1] == n))  { 
                a = 1;
                msg += (ids[i] + "* - " + book[0] + ", by " + 
                        capitalize(book[1]) + ".\n");  
            } 
        }
        else { 
            msg += (ids[i] + " - " + book[0] + ", by " + 
                    capitalize(book[1]) + ".\n");  
       } 
    }  

    if (a) 
        msg = ("A * next to an ID indicates that the book is " +
               "currently awaiting approval by the Council.\n\n" + msg); 

    tp->more(msg); 
    return 1;
}


int
approve_book(string str)
{
    object tp = this_player(); 
    string *book, path, n; 

    n = tp->query_real_name();  

    if (!stringp(str) || !strlen(str)) {  
         notify_fail("Approve <book ID>\n"); 
         return 0;
    }

    if (!BOOK_EXISTS(str)) { 
        notify_fail("There is no book with that ID!\n");  
        return 0;
    }

    path = (PRIVATE_BOOK_DIR + str); 

    book = get_book(path, 1);   

    if (book[2] == APPROVED) { 
        notify_fail("That book has already been approved!\n"); 
        return 0;
    }

    if (!COUNCIL_CODE->is_council_member(n) &&
        !(SECURITY->query_wiz_dom(n) == "Calia")) { 
        notify_fail("You do not have the authority to approve books.\n"); 
        return 0;
    }

    book[2] = APPROVED; 
    rm(path); 

    write_file(path, book[0] + "\n" + book[1] + "\n" + 
                     book[2] + "\n" + book[3]); 

    tp->catch_msg("Ok.\n"); 
    return 1; 
}


void
init()
{
    ::init(); 
    add_action(write_book, "write"); 
    add_action(read_book, "read"); 
    add_action(read_book, "spam"); 
    add_action(delete_book, "delete"); 
    add_action(approve_book, "approve"); 
    add_action(browse, "browse"); 
    add_action(edit_book, "bookedit"); 
}

