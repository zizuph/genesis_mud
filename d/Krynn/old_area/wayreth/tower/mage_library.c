/* 
 * The library in the tower of Wayreth.
 *
 * Copy of the library in Vkeep. 
 * Changed for the use in Wayreth. 
 * Jeremiah, 95/07/26
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "../guild/local.h"
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "mage_lib.h"
inherit TOWERROOM;
inherit STDLIB + "library";

//#define ENCYCLO "/d/Wiz/tintin/open/encyclopedia.c"

string file; /* The file to look for book. */

void
reset_tower_room()
{
    return;
}


void
create_tower_room()
{
    set_short("Mages library");
    set_long("You find yourself in a library. Lined along the walls " +
      "are shelves with numerous books of different materials, " + 
      "colours and sizes. A treasure of information and " + 
      "knowledge is stored here. This library contains, among " +
      "many others, books with information about the Wizards of " +
    "High Sorcery, a deeper knowledge that cannot be acquired "+
      "elsewhere in the world. Apart from reading here, you can " +
      "also add your own experiences, thoughts or bits of " +
      "information you think would be of interest or value, to " +
      "the collection of books. There are some nice posters " +
      "hanging on the wall here.\n");

    add_item(({"poster", "posters"}), "There are two posters here. " +
      "The first poster contains general instructions and " +
      "the second poster contains information of how to " +
      "make a new book. Maybe you should read them.\n");

    add_cmd_item(({"poster", "other", "second"}), "read", "@@read");

    set_alarm(1.0, 0.0, "reset_tower_room");
    set_wall_type(2);

    add_exit(WTOWER + "study", "east", 0);

    set_lib_id("wohs_mage_lib_id");
    set_lib_path("/d/Krynn/wayreth/log/library/mage/");
    set_lib_type(4);
    set_lib_long("the library at the Tower of Wayreth");
    set_max_librarian_num(3);
    set_search_delay(6.0);
    set_default_topics((["New Arrivals":1,
        "Maps":0,
        "Guilds in Genesis":0,
        "Places in Genesis":0,
        "Krynn in General":0,
        "Genesis in General":0,
        "Wizards of High Sorcery":0,
        "Herbs of Genesis":2,
        "Histories of wizards":2,
        "Private wizard section":2,
        "Trash":1]));
    setup_library();
}

void
init()
{
    ::init();
    init_library();
}

int
read()
{
    string rest;

    rest = query_item_rest_command();
    if (rest == "2" || rest == "poster")
    {
        write("To write a new book you should give the command 'blank'. " +
          "Then you can take a blank book from a special shelf. " +
          "This book is yours to fill with whatever you want, maps, " +
          "songs or a novel perhaps. The command to start writing " +
          "can be found examining the blank book. You write a book " +
          "much the same way you write a note on the board. Good luck.\n");
        return 1;
    }

    write("To borrow a book you should the command 'borrow'. You may " +
      "use the command 'index' to list the different sections of " +
      "the library. Use 'catalog' to look at the books in a " +
      "certain section. Don't forget to return the books before " +
      "you leave the library.\nFor instructions of how to create " +
      "a new book you should read on the other poster.\n");

    if (member_array(TP->query_real_name(),query_librarian()) != -1)
      write("\nAs librarian, you have these commands available:\n" +
	    " Beautify <bookname>\n" +
	    " Edit <bookname>\n" +
	    " Movebook <bookname> to topic <newtopic>\n" +
	    "       To remove a book completely, use 'Movebook <bookname> " +
	    "to topic trash'.\n" +
	    " Create <new topic> <access level>\n" +
	    "       Access level is: 0: Everyone\n" +
	    "                        1: Librarian only\n" +
	    "                        2: Wizards of High Sorcery only\n" +
	    " Uncreate <old topic>\n" +
	    " Retire\n");
    return 1;
}

void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest);
    library_leave_inv(player, dest);
}

public void
hook_leave_with_books(object who, int i)
{
    string book = "book" + (i > 1 ? "s" : "");
    string place = (i > 1 ? "their places" : "it's place");

    who->catch_msg("A deep voice, sounding from somewhere within your mind, " +
      "reminds you to return the " + book + " you borrowed. " +
      "Quickly you put the " + book + " back in " + place +
      " on the shelves, and leave.... a bit ashamed of yourself.\n");

    tell_room(TO, QCTNAME(who) + " forgot to return " +
      (i > 1 ? "some" : "a") + " " + book + " " +
      PRONOUN(who) + " had borrowed from the library. " +
      C(PRONOUN(who)) + " blushes, and quickly returns the " +
      book + " to " + place + " on the shelves.\n");
}

public void
hook_borrow()
{
    clone_object(LIB_PARALYZE)->move(TP);
    write("You start to search the shelves for the book.\n");
    say(QCTNAME(TP) + " starts to search the shelves, obviously " +
      "looking for a specific book.\n");
}

public mixed
hook_can_access_catalog(int level)
{
    /* 0: everyone can read
     * 1: librarian only can read
     * above levels are handled directly,
     * we only need to take care of the ones below
     *
     * we add these access classes:
     * 2: wizards only can read
     */
    if (level == 2)
        return ({ !!(IS_MEMBER(RNAME(TP))), "Wizards of High Sorcery only" });

    return ({ 0, "No access" });
}

int
hook_can_use_library()
{
    return 1;
}

int
hook_appoint_unappoint()
{
    /* Only conclave can appoint/unappoint */
    return (IS_CONCLAVE(RNAME(TP)));
}

public void
hook_appointed_info()
{
    write("Beware: The appointed librarian must meet the requirements " +
      "(Wizard of High Sorcery, one that has taken the Test), " +
      "otherwise the position will become vacated again automatically " +
      "after an unsuccessful try.\n");
}

public int
hook_librarian_requirements()
{
    return (IS_MEMBER(RNAME(TP)));
}

public int
hook_find_book(object who)
{
    object ob;
    if (!(ob = present(LIB_PARALYZE_NAME, who)))
    {
        return 0;
    }
    ob->remove_object();
    return 1;
}

public void
hook_found_book(object who)
{
    tell_object(who, "Searching through the shelves, you find the book " +
      "you were looking for. You take it from its place on " +
      "the shelf.\n");
    tell_room(TO, QCTNAME(who) + " finds a book and takes it from its " +
      "place on the shelf.\n", who);
}

public void
hook_book_not_found(object who, string bname)
{
    /* Put in a better message here :) ~Ari */
    tell_object(who, "Book was not found.\n");
}

public void
hook_book_currently_borrowed(object who, string str)
{
    /* Might wanna change this message, too. ~Ari */
    tell_object(who, "The book you have been looking for seems to have been " +
      "borrowed.\n");
}

public void
hook_give_blank_book(int state)
{
    write("From out of nowhere a blank book appears. It slowly " +
      "floats toward you. You grab it.\n");

    say("From out of nowhere a blank book appears. It slowly " +
      "floats toward " + QTNAME(TP) + ", who takes it.\n");

    if (state)
    {
        say("But it was too heavy. The books falls to the ground.\n");
        write("It's too heavy for you, you drop it.\n");
    }
}
