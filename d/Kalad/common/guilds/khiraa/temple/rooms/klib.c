/* Library of the Khiraa
 * By Sarr 3.Set.97
 */

inherit "/d/Kalad/room_std";
   
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/* Current catagories */

#define CATAGORIES  ({"maps","guilds","equipment","magic","people", \
                            "history","herbs","khiraa","ceremony"})
#define TITLE 0
#define BDESC 1
#define BCAT  2
#define FNAME 3

/* 
 * globals
 */

int number_of_books = 0;
mapping book_list = ([]);
string *name_list = ({});

object librarian_room;

string new_bookname;
string new_booktitle;
string new_bookdesc;
string new_bookcata;

void get_bookname(string str);
void get_booktitle(string str);
void get_bookdesc(string str);
void get_bookcata(string str);

void
set_librarian_room(string path)
{
    call_other(path,"??");
    librarian_room = find_object(path);
    if(!objectp(librarian_room))
        tell_room(TO,"The librarian room did not load!!\n");
}

void
load_library()
{
    book_list = restore_map(KHIRAA_DIR(log/library_books));
    if(number_of_books = m_sizeof(book_list))
        name_list = m_indexes(book_list);
}

void
save_library()
{
    save_map(book_list,KHIRAA_DIR(log/library_books));
}

int
add_book(string name, string title, string desc, string cata)
{
    load_library(); // Make sure library is up to date.
    book_list += ([ name: ({ title, desc, cata, name+"_book" }) ]);
    /* Librarian room should have already added 
    
    write_file("/d/Kalad/common/guilds/khiraa/temple/books/"+name+"_book",
    fbook);

    */
    save_library(); // Save changes
    load_library(); // Load up changes
    return 1;
}

int
remove_book(string name)
{
    if(member_array(name,name_list) == -1)
        return 0;
    rm("/d/Kalad/common/guilds/khiraa/temple/books/"+book_list[name][FNAME]);
    book_list = m_delete(book_list,name);
    save_library(); // Save changes
    load_library(); // Load up changes
    return 1;
}

void
do_cancel()
{
    write("You stop writing the book.\n");
    say(QCTNAME(TP)+" stops writing a book.\n");
    return;
}

int 
do_write(string str)
{
    int i;
    NF("Write what?\n");
    if(str != "book")
        return 0;
    say(QCTNAME(TP)+" starts to write a book.\n");
    write("You start writing a book.\n");
    write("You may enter '**' at any time to cancel.\n");
    
    write("\nPlease enter the name of the book:");
    write("\nThis may only be ONE word!\n");

    input_to(get_bookname);
        
    return 1;
}

void
get_bookcata(string str)
{
    new_bookcata = str;
    if(str == "**")
    {
        do_cancel();
        return;
    }
    if(member_array(str,CATAGORIES) == -1)
    {
        new_bookcata = "_beebelbox_";
        write("That is not one of the categories listed.\n");
        write("Chose again:");
        input_to(get_bookcata);
    }
    if(new_bookcata != "_beebelbox_" )
    {
        write("Now enter the contents of the book:\n");
        clone_object("/obj/edit")->edit();
    }
}


void
get_bookdesc(string str)
{
    int i;
    new_bookdesc = str;
    if(str == "**")
    {
        do_cancel();
        return;
    }
    if(strlen(str) > 30)
    {
        write("That description is too long, chose a shorter one:");
        input_to(get_bookdesc);
    }

    write("\nPlease enter the category for this book.\n");
    write("The avaiable catagories are: ");
    for(i = 0; i<sizeof(CATAGORIES);i++)
    {
        write(CATAGORIES[i]+" ");
    }
    write("\n");
    input_to(get_bookcata);
}

void
get_booktitle(string str)
{
    new_booktitle = str;
    if(str == "**")
    {
        do_cancel();
        return;
    }
    write("\nPlease enter what you want the book to look like:\n");
    write("Do not put in the 'book' part. Example: 'leather-bounded' "+
    "will produce a 'leather-bounded book'.\n");
    input_to(get_bookdesc);
}

void
get_bookname(string str)
{
    new_bookname = str;
    if(str == "**")
    {
        do_cancel();
        return;
    }
    if(member_array(str,name_list) != -1)
    {
        write("There already is a book with that name.\n");
        write("Please enter another:");
        input_to(get_bookname);
    }

    write("\nPlease enter the title of the book:");
    input_to(get_booktitle);
}

void
done_editing(string text)
{
    if(strlen(text) < 1)
    {
        write("You discard the book.\n");
        say(QCTNAME(TP)+" stops writing a book.\n");
        return;
    }

    write("You finish the book, and place it in the stack of "+
    "books designated for review by the Circle.\n");
    
    librarian_room->add_book(new_bookname,new_booktitle,new_bookdesc,
        new_bookcata,text);

}

int
do_borrow(string str)
{
    object the_book;
    NF("First return the book you have now before borrowing another.\n");
    if(present("_khiraabook_",TP))
        return 0;
    NF("There is no book by that name here.\n");
    if(member_array(str,name_list) == -1)
        return 0;
    the_book = clone_object(KHIRAA_DIR(temple/obj/scroll));
    the_book->set_long("This is a book from the Khiraa library. It "+
    "has the title "+book_list[str][TITLE]+".\n");
    the_book->set_short(book_list[str][BDESC]+" book");
    the_book->set_name("book");
    the_book->add_name(str);
    the_book->set_file("/d/Kalad/common/guilds/khiraa/temple/books/"+
        book_list[str][FNAME]);
    the_book->move(TP);

    say(QCTNAME(TP)+" takes a "+the_book->short()+" from the shelves.\n");
    write("You take a "+the_book->short()+" from the shelves.\n");
    return 1;

}


int 
do_return(string str)
{
    object ob;
    NF("What do you want to return?\n");
    if(str != "book")
        return 0;
    NF("You don't have any books you can return here.\n");
    ob = present("_khiraabook_",TP); 
    if(!objectp(ob))
        return 0;
    write("You return the "+ob->short()+".\n");
    say(QCTNAME(TP)+" returns a "+ob->short()+".\n");
    ob->remove_object();
    return 1;
}

int
do_list(string str)
{
    int i;
    string the_list;
    if(!str)
    {
        write("Looking among the many ancient shelves, you notice "+
        "many categories of books. They are: ");
        for(i=0;i<sizeof(CATAGORIES);i++)
            write(CATAGORIES[i]+" ");
        write("\nYou can list each category with 'list <category>'\n");
        return 1;
    }
    NF("There is no such category: "+str+".\n");
    if(member_array(str,CATAGORIES) == -1)
        return 0;
    the_list = "";
    for(i=0;i<sizeof(name_list);i++)
    {
        if(book_list[name_list[i]][BCAT] == str)
            the_list += sprintf("%-30s %s\n",name_list[i],
                book_list[name_list[i]][TITLE]);
    }
    if(!strlen(the_list))
        the_list = "There are no books in that category.\n";
    else
        the_list = "You see these books in this category:\n"+
            the_list;
    TP->more(the_list);
    return 1;
}


void
init()
{
    ::init();
    add_action(do_borrow,"borrow");
    add_action(do_return,"return");
    add_action(do_list,"list");
    add_action(do_write,"write");
}

