inherit "/d/Kalad/room_std";
#pragma save_binary
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

mapping book_list = ([]);
string *name_list = ({});

object library_room;

void
set_lib(string path)
{
    call_other(path,"??");
    library_room = find_object(path);
    if(!objectp(library_room))
        remove_object(); // should not use room if no library
}

void
load_library()
{
    book_list = restore_map(KHIRAA_DIR(log/temp_library_books));
    if(m_sizeof(book_list))
        name_list = m_indexes(book_list);
    else
        name_list = ({});
}
 
void
save_library()
{
    save_map(book_list,KHIRAA_DIR(log/temp_library_books));
}


int
remove_book(string name)
{
    if(member_array(name,name_list) == -1)
        return 0;
    rm("/d/Kalad/common/guilds/khiraa/temple/books/"+book_list[name][3]);
    book_list = m_delete(book_list,name);
    save_library(); // Save changes
    load_library(); // Load up changes
    return 1;
}

int
add_book(string name, string title, string desc, string cata, string
fbook)
{
    load_library(); // Make sure library is up to date.
    book_list += ([ name: ({ title, desc, cata, name+"_book" }) ]);
    write_file("/d/Kalad/common/guilds/khiraa/temple/books/"+name+"_book",
    fbook);
    save_library(); // Save changes
    load_library(); // Load up changes
    return 1;
}

int
add_new_book(string name, string title, string desc, string cata)
{
    load_library();
    library_room->add_book(name,title,desc,cata);
    book_list = m_delete(book_list,name); // get rid of entry here
    save_library(); // Save changes
    load_library(); // Load up changes
    return 1;
}    

string
query_new_books()
{
    if(sizeof(name_list))
        return " You notice that there are new books to review.";
    return "";
}

void
create_room()
{
    INSIDE;
    set_short("Books acceptance room.");
    set_long("\n   You are now in a small chamber of black stone. "+
    "This is where the Masters of the Library can come and review "+
    "books and add them permanently to the library.\n"+ 
    "\n   The room has "+
    "only a small chair, table with a dark purple-black candle "+
    "burning on it and a small bookcase holding the potential books. "+
    "There is a small sign on the wall with instructions."+
    "@@query_new_books@@\n\n");

    add_item("chair","A simple black oak chair sits behind the "+
    "table.\n");
    add_item("table","A small square table that has a candle on it "+
    "that burns a strange purple-black light.\n");
    add_item("candle","It provides light.\n");
    add_item("bookcase","It contains the books that need reviewing.\n");

    add_cmd_item("sign","read","To use the library you can "+
      "'add_book <bookname>' to add a book or "+
      "'toss <bookname>' to destroy a book. To "+
      "see what is in the librarians box you can "+
      "'list'. If you would like to read a "+
      "book before approving it, use 'read <bookname>'.\n");
   
    add_item(({"sign"}),"It has instructions to be read.\n");
   
    add_exit(KHIRAA_DIR(temple/rooms/temple_libr),"south",0,-1);
    set_lib(KHIRAA_DIR(temple/rooms/temple_libr));
    load_library();
}

int
do_add(string str)
{
    NF("Add what?\n");
    if(!str)
        return 0;
    NF("There is no book by that name.\n");
    if(member_array(str,name_list) == -1)
        return 0;
    write("You add the book '"+str+"' to the main library.\n");
    add_new_book(str,book_list[str][0],book_list[str][1],
        book_list[str][2]);
    return 1;
}

int
do_remove(string str)
{
    NF("There is no book by that name.\n");
    if(remove_book(str))
    {
        write("You toss that book away.\n");
        return 1;
    } 
    return 0;
}


int
do_list(string str)
{
    int i;
    string the_list;
    if(!sizeof(name_list))
    {
        write("There are no books that need to be reviewed.\n");
        return 1;
    }
    the_list = "";
    for(i=0;i<sizeof(name_list);i++)
    {
        the_list += name_list[i]+" "+book_list[name_list[i]][0]+"\n";
    }
    the_list = "This is the list of books that need to be reviewed:\n"+
        the_list;
    TP->more(the_list);
    return 1;
}

int
do_read(string str)
{
    string the_book;
    NF("Read what book?\n");
    if(!str)
        return 0;
    NF("There is no book by that name.\n");
    if(!sizeof(name_list))
        return 0;
    if(member_array(str,name_list) == -1)
        return 0;
    the_book = read_file("/d/Kalad/common/guilds/khiraa/temple/books/"+
        str+"_book");
    TP->more(the_book);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_list,"list");
    add_action(do_add,"add_book");
    add_action(do_remove,"toss");
    add_action(do_read,"read");
}

