/* The new library in the Solamnian guild
* 
* Aridor, 10/96
* 
* Used as the mercenary library by Morrigan, Sep 2002
*
* Employs a librarian to sort the books.
* 
* 2005-05-30, Dargoth: fixed the bug with multiple librarians
* 2006-03-19, Finwe: Modified from the Merc library for Green Oaks
*/

#include <ss_types.h>
#include <macros.h>
//#include "lib.h"
//#include "/d/Krynn/common/defs.h"
#include "defs.h"
#include <mail.h>

#define IS_LIBRARIAN(X) (member_array(lower_case(X),query_librarian()) != -1)
    
inherit INDOORS_BASE;
inherit STDLIB + "library";

object yealean;

void
create_indoor_room()
{
    set_short("Library of the " + ACADEMY_NAME);
    set_long("This is " + short() + ". It is a great storage of knowledge " +
        "for the elves. Shelves line the walls and hold many books, " +
        "many of which may be borrowed and read. A desk sits in the " +
        "center of the room where a librarian sits. A sign sits on " +
        "the desk and a plaque hangs on the wall. ");

    add_item("desk", 
        "It's a large wooden piece of furniture. It sits in the center " +
        "of the room with an elf sitting behind it. ");
    add_item(({"plaque","sign"}),
      "It's made of some kind of metal, words are written on it.\n");
    add_cmd_item("plaque", "read", "@@read_plaque");
    add_cmd_item("sign",   "read", "@@read_sign");

    add_exit(GO_DIR + "ac_board", "east");

    set_lib_id("ga_lib_id");
    set_lib_path(LIBRARY_DIR);
    set_lib_type(4);
    set_lib_long("the Library of Green Oaks");
    set_search_delay(8.1);
    set_max_librarian_num(2);
    set_default_topics(([ "Tutorial":0,
        "General":0,
        "Realms":0,
        "New Arrivals":1,
	    "Trash":1 ]));
    setup_library();

    reset_room();
}

void
reset_room()
{
    if (yealean)
	return;

    yealean = clone_object(NPC_DIR + "librarian");
    yealean->move(TO);
}

string
desk()
{
    if (!yealean || !present(yealean, TO))
	return "Behind this desk usually stands a librarian to help " +
	"you with get the books you want but he's nowhere to be " +
	"seen now.\n";
    else
	return "Behind the desk stands a librarian, eager to " +
	"find the books you are looking for.\n";
}

void
init()
{
    init_library();
    ::init();
}

void
enter_inv(object player, object from)
{
    object reader;

    setuid();
    seteuid(getuid());

    ::enter_inv(player, from);

    if (!sizeof(query_librarian()))
	return;

    if (player->query_wiz_level() ||
        !(IS_LIBRARIAN(player->query_name())))
	return;

    reader = clone_object(MAIL_READER);
    reader->move(player, 1);
}


void
leave_inv(object player, object dest)
{
    object reader;

    if (objectp(reader = present(READER_ID, player)) && 
	!player->query_wiz_level())
	reader->remove_object();
	
    ::leave_inv(player, dest);

    library_leave_inv(player, dest);
}

string
read_plaque()
{
    write("The Library\n" +
      "============================\n\n" +
      "Check the 'index' for a list of topics, and the 'catalog' of each " +
      "topic for a list of available books. You can then 'borrow' any of " +
      "the available books. Note that you must give the complete title of " +
      "a book (up to any '-') you want to borrow. Please do not forget to " +
      "return borrowed books!\n\n" +
      "To write a new book you should give the command 'blank'. " +
      "Then the librarian will give you a blank book, which is yours to " +
      "fill with whatever you want, maps, songs, or a novel perhaps? " +
      "The command to start writing is 'bedit'. You write a " +
      "book much the same way you write a note on the board. Once you "+
      "have written a book, the librarian will have to approve it before "+
      "it is accessible to others.\n");
    return "";
}


string
read_sign()
{
    string *libr_list;
    object ob;
    string s;
    libr_list=({});
    if (!(librarian && sizeof(librarian)))
        libr_list=({ "none" });
    else
        foreach (string lbr : librarian)
        {
            s="offline";
            ob=find_living(lbr);
            if (ob)
                s= interactive(ob) ? "online": "linkdead";
            libr_list+= ({ sprintf("%s(%s)",capitalize(lbr), s) });
        }

    write("LIBRARY - QUIET PLEASE!\n\n" +
      "Current Librarian(s): " + implode(libr_list,", ") + ".\n\n"+
      "A wizard is responsible for 'appoint'ing or 'unappoint'ing " +
      "the librarian.\n");
    
    if (librarian && sizeof(librarian) && IS_LIBRARIAN(TP->query_real_name()))
      write("As librarian, you have these commands available:\n" +
	    " Beautify <bookname>\n" +
	    "       Allows you to change the title, or align the title neatly.\n" +
	    " Edit <bookname>\n" +
	    "       Allows you to edit a book or add to it.\n" +
	    " Movebook <bookname> to topic <newtopic>\n" +
	    "       To remove a book completely, use 'Movebook <bookname> to topic trash'.\n" +
	    " Erase <bookname> | '-all books in trash-'\n" +
	    "       Destroy a book (must be in the trash) unrecoverably.\n" +
	    " Create <new topic> <access level>\n" +
	    "       Access level is: 0: Everyone\n" +
	    "                        1: Librarian only\n" +
//	    "                        2: Mercenaries only\n" +
//	    "                        3: Mercenary Lords only\n" +
	    " Uncreate <old topic>\n" +
	    " Retire\n");
    return "";
}

void
hook_leave_with_books(object who, int i)
{
    who->catch_msg("The librarian runs after you and takes the book" +
      (i > 1 ? "s" : "") + " you didn't return.\n"); 
    tell_room(TO, QCTNAME(who) + " tried to take " +
      (i > 1 ? "some books" : "a book") + " from " +
      "the library. The librarian got " +
      (i > 1 ? "them" : "it") + " back.\n",who);
}

void 
hook_borrow()
{
    write("You ask the librarian for a book, and the librarian runs off to " +
      "search for the book.\n");
    tell_room(TO, QCTNAME(TP) + " asks for a book. The librarian runs off.\n",
      TP);

}

mixed
hook_can_access_catalog(int level)
{
    /* 0: everyone can read
    * 1: librarian only can read
    * above levels are handled directly,
    * we only need to take care of the ones below
    *
    * we add these access classes:
    * 2: mercenaries only can read 
    * 3: mercenary lords only can read
    */
/*
    if (level == 3)
    return ({ !!(IS_MERC_LORD(TP) || TP->query_wiz_level()), "Mercenary Lords only" });
    
    if (level == 2)
    return ({ !!(IS_MERC(TP) || TP->query_wiz_level()), "Mercenaries only" });
*/
    return ({ 0,"No access" });
}

/*
int
hook_can_use_library()
{
    return !!(yealean && P(yealean,TO));
}
*/
int
hook_appoint_unappoint()
{
    /* Any wizard can appoint a librarian */
    if (TP->query_wiz_level())
	return 1;

    return 0;

}

void
hook_appointed_info()
{
    write("Note: The appointed librarian must meet the requirements" +
      ", otherwise " +
      "the position will become vacated again automatically after " +
      "an unsuccessful try.\n");
}

int
hook_librarian_requirements()
{
//    if (IS_MERC(TP) || TP->query_wiz_level())
    if (TP->query_wiz_level())
        return 1;

    return 0;
}

public int
hook_find_book(object who)
{
    yealean->move_living("xx",TO);
    if (!present(who,TO))
    {
	tell_room(TO,"The librarian looks around and states: Wasn't " +
	  "there someone here looking for a book just now?\n" +
	  "The librarian shrugs helplessly.\n");
	return 0;
    }
    return 1;
}

public void
hook_found_book(object who)
{
    tell_object(who, "The librarian gives you the ordered book.\n");
    tell_room(TO, "The librarian gives out an ordered book.\n", who);
}

public void
hook_book_not_found(object who,string bname)
{
    tell_object(who, "The librarian tells you: The book that " +
      "you were looking for doesn't exist.\n");
    tell_room(TO, "The librarian is without the ordered book.\n", who);
}

public void
hook_book_currently_borrowed(object who, string bname)
{
    tell_object(who, "The librarian tells you: That book has " +
      "already been borrowed.\n");
    tell_room(TO, "The librarian is without the ordered book.\n", who);
}

public void
hook_give_blank_book(int state)
{
    say(QCTNAME(TP) + " got a blank book from the librarian.\n");  
    write("The librarian gladly hands you a blank book.\n");
    if (state)
    {
	say("But it was too heavy. The books falls to the ground.\n");
	write("It's too heavy for you, you drop it.\n");
    }
}

