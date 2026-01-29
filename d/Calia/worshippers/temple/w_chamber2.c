
 /* West Chamber of the Worshipper Temple
  * by Jaacar
  * July 22nd, 1996
  * Based on library code originally coded by Elessar, April 1992
  * Modifications by Maniac, 10/10/96
  */


#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <composite.h>
#include "defs.h"
#include WORSHIP_HEADER

#define DIR "/d/Calia/worshippers/texts/"
#define BOOK_LIST   DIR+"booklist"

int book_exists(string bt); 

string *books;
string *restricted;
string my_list;

public nomask int
wiz(object who)
{
    if (SECURITY->query_wiz_rank(who->query_real_name()) >= WIZ_ARCH)
        return 1;
    if (SECURITY->query_wiz_dom(who->query_real_name()) == "Calia")
        return 1;
    return 0;
}

void
create_room()
{
    if (!books)
        books = ({});
    set_short("A small chamber");
    set_long("This chamber is fairly small, the walls probably "+
        "as long as two humans lying head to toe.  The walls are "+
        "made of stones, wood, and mud.  On the western wall you "+
        "notice small slots carved into the stone, which appear "+
        "to be shelves of some sort.  Each of these slots "+
        "contain a parchment scroll.  On the northern wall you "+
        "notice a small poster that you can read.  "+
        "Against the southern wall you see a small desk.  You can "+
        "head out back into the entranceway to the east.\n");

    add_item(({"slot","slots","shelf","shelves"}),"@@query_title_list");
    add_item(({"scrolls","parchments","scroll","parchment"}),"There are "+
        "many scrolls and parchments here.  You will have to choose "+
        "one to look at.\n");
    add_item("poster","In this chamber you may look at the shelves to "+
        "see which scrolls and parchments are available to read.  You "+
        "can then 'read <title>'.\n");
    add_item("desk","It is a small wooden desk, most likely "+
        "used by the inhabitants of this temple for writing "+
        "scrolls for this place.\n");


    restore_object(BOOK_LIST);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_WIZINFO,
        "Some useful info for wizards:\n" +
        "The 'restrict <title>' command may be used to restrict a " +
        "text to guild members only.\n" +
        "'allscrolls' will list all the texts available.\n" +
        "'banscroll <title>' will remove a text from the shelves.\n" +
       "'newscroll <title>' will add a text to the shelves.\n" +
        "Note these commands are all restricted to Calia wizards " +
        "or arches.\n\n");
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE+"entrance","east",0,1);
}

int
read_book(string book)
{
    if (!book)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    book = lower_case(book);
    
    if (book == "poster")
    {
        write("In this chamber you may look at the shelves to "+
            "see which scrolls and parchments are available to read.  "+
            "You can then 'read <title>'.\n");
        return 1;
    }
    if (book == "stous")
    {
        if (!(TP->query_skill(SS_CARVED) &AIR_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "kataraktas")
    {
        if (!(TP->query_skill(SS_CARVED) &WATER_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "psotia")
    {
        if (!(TP->query_skill(SS_CARVED) &FIRE_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "choma" || book == "apodosi")
    {
        if (!(TP->query_skill(SS_CARVED) &EARTH_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "floga")
    {
        if (!(TP->query_skill(SS_CARVED) & FIRE_FLAG) || 
            !(TP->query_skill(SS_PATRON_ELEMENTAL) & FIRE_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "aleipso")
    {
        if (!(TP->query_skill(SS_CARVED) & WATER_FLAG) || 
            !(TP->query_skill(SS_PATRON_ELEMENTAL) & WATER_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }    
    if (book == "dynami")
    {
        if (!(TP->query_skill(SS_CARVED) & EARTH_FLAG) || 
            !(TP->query_skill(SS_PATRON_ELEMENTAL) & EARTH_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    if (book == "evimero")
    {
        if (!(TP->query_skill(SS_CARVED) & AIR_FLAG) || 
            !(TP->query_skill(SS_PATRON_ELEMENTAL) & AIR_FLAG))
        {
            write("You cannot understand the writing on the scroll as "+
                "you have not been granted the knowledge of that power.\n");
            return 1;
        }
    }
    
            
    if (book_exists(book))
    {
        if (member_array(lower_case(book),restricted) >= 0 && !TP->is_worship())
        {
            write("You cannot understand the writing on the scroll.\n");
            say(QCTNAME(TP)+" tried to read a scroll from the shelves, "+
                "but looks very confused now.\n",TP);
            return 1;
        }
        write("You read the scroll titled "+capitalize(book)+".\n");
        say(QCTNAME(TP)+" reads a scroll from the shelves.\n",TP);
        book = lower_case(book);
        TP->more(read_file(DIR+book+".txt",2));
        return 1;
    }
    write("You don't see that scroll here.\n");
    return 1;
}


int
book_exists(string booktitle)
{
    int n;
    if (!booktitle) return 0;
    booktitle = capitalize(lower_case(booktitle));
    restore_object(BOOK_LIST);
    while (n<sizeof(books))
    {
        if (booktitle == books[n]) return 1;
        n++;
    }
    return 0;
}

int
add_book(string book)
{
    if (!wiz(TP)) return 0;
    if (book_exists(book))
    {
        write("That scroll is already on the shelves.\n");
        return 1;
    }
    book = capitalize(lower_case(book));
    books = books + ({book});
    save_object(BOOK_LIST);
    write("You put a scroll titled "+book+" on the shelves.\n");
    say(QCTNAME(TP)+" puts a new scroll on the shelves.\n",TP);
    return 1;
}

string
query_title_list()
{
    string title_list;
    int n;
    if (!sizeof(books)) return "No scrolls available.\n";
    title_list = "Currently these titles are available in the Worshippers Library:\n";
    title_list+=COMPOSITE_WORDS(sort_array(books))+".\n";
    return (sort_array(title_list));
}

int
list_all_books()
{
    if (!wiz(TP)) return 0;
    write(query_title_list());
    return 1;
}

int
remove_book(string book)
{
   int n;
    if (!wiz(TP)) return 0;
    if (!book_exists(book))
    {
        write("That scroll is not on the shelves!\n");
        return 1;
    }
    book = capitalize(lower_case(book));
    while (n<sizeof(books))
    {
        if (book == books[n]) {
        books = exclude_array(books,n,n);
        write("You remove the scroll titled "+book+" from the shelves.\n");
        say(QCTNAME(TP)+" removes a scroll from the shelves.\n",TP);
        save_object(BOOK_LIST);
        return 1;
    }
        n++;
    }
    write("The scroll didn't exist afterall.\n");
    return 1;
}

int
add_restrict(string book)
{
    if (!wiz(TP)) return 0;
    if (!book_exists(book))
    {
        write("There is no scroll by that name on the shelves!\n");
        return 1;
    }
    book = lower_case(book);
    if (!restricted)
    {
        restricted = ({book});
    }
    else
    {
        restricted += ({book});
    }
    save_object(BOOK_LIST);
    write("You have restricted the scroll titled "+book+".\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(read_book,"read");
    add_action(add_book,"newscroll");
    add_action(remove_book,"banscroll");
    add_action(list_all_books,"allscrolls");
    add_action(add_restrict,"restrict");
}

