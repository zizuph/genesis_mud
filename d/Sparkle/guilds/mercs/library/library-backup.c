/* The new library in the Solamnian guild
* 
* Aridor, 10/96
* 
* Used as the mercenary library by Morrigan, Sep 2002
*
* Employs a librarian to sort the books.
*/

#include <ss_types.h>
#include "lib.h"
#include "../merc.h"
#include "/d/Krynn/common/defs.h"
#include "../room/room.h"
#include <mail.h>

inherit "/std/room";
inherit STDLIB + "library";

object knight;

public string
long_desc()
{
    return ("This is a small, well-lit room just east of an entrance "+
	"chamber to the building. "+BUILDING_DESC+" There is a small "+
        "desk here, on which rests a plaque with instructions on how "+
	"to use the library. On the wall is a small sign.\n");
}

void
create_room()
{
    set_short("A small, well-lit room");
    set_long("@@long_desc");

    add_item("desk", "@@desk");
    add_item(({"plaque","sign"}),
      "It's made of some kind of metal, words are written on it.\n");
    add_cmd_item("plaque", "read", "@@read_plaque");
    add_cmd_item("sign",   "read", "@@read_sign");

    add_exit(MROOM + "join", "west", 0);

    set_lib_id("merc_lib_id");
    set_lib_path(VLIB);
    set_lib_type(4);
    set_lib_long("the library of the Mercenary guild");
    set_search_delay(8.1);
    set_max_librarian_num(2);
    set_default_topics(([ "Causes":0,
        "New Arrivals":1,
	"Trash":1 ]));
    setup_library();

    reset_room();
}

void
reset_room()
{
    if (knight)
	return;

    knight = clone_object(MNPC + "merc_base");
    knight->move(TO);
    knight->set_random_move(0);
    knight->sclear_act();
}

string
desk()
{
    if (!knight || !present(knight, TO))
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

    ::enter_inv(player, from);

    if (!sizeof(query_librarian()))
	return;

    if (player->query_wiz_level() ||
	member_array(lower_case(player->query_name()),
	query_librarian()) == -1)
	return;

    setuid();
    seteuid(getuid());
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
    write("LIBRARY - QUIET PLEASE!\n\n" +
      "Current Librarian: " + 
      (librarian && sizeof(librarian) ? C(librarian[0]) : "-") + " "+
      (find_living(librarian[0]) ? (interactive(find_living(librarian[0])) ?
      "(active)" : "(linkdead)") : "(inactive)") + "\n"+
      "A wizard is responsible for 'appoint'ing or 'unappoint'ing " +
      "the librarian.\n");
    if (librarian && sizeof(librarian) && TP->query_real_name() == librarian[0])
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
	    "                        2: Mercenaries only\n" +
	    "                        3: Mercenary Lords only\n" +
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
    knight->move_living("into the magazine",VOID);
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

    if (level == 3)
    return ({ !!(IS_MERC_LORD(TP) || TP->query_wiz_level()), "Mercenary Lords only" });
    
    if (level == 2)
    return ({ !!(IS_MERC(TP) || TP->query_wiz_level()), "Mercenaries only" });

    return ({ 0,"No access" });
}

int
hook_can_use_library()
{
    return !!(knight && P(knight,TO));
}

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
    if (IS_MERC(TP) || TP->query_wiz_level())
        return 1;

    return 0;
}

public int
hook_find_book(object who)
{
    knight->move_living("xx",TO);
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

