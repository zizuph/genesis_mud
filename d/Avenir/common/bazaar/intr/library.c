/* Library made by Glinda may -95.
   It inherits Gresolles library from -92.
   A few things have been changed to make it work with a librarian.
 */
inherit "/d/Avenir/inherit/library";
#include "../bazaar.h"

#define LIBR	(NPC +"librarian")

public object librarian, quest_npc;


public int
check_exit(void)
{
    if (objectp(librarian) && present(librarian))
	return libblock();
    else
	return 0;
}

public void
set_librarian(object who)	{ librarian = who; }

public void
create_library(void)
{
    set_short("Bazaar library");
    set_long("You are in the library of Bazaar. Huge oaken shelves " +
	"cover the walls from floor, to ceiling. The high ceiling along "+
	"with the stone floor makes every sound you make produce a loud "+
	"echo. To your right is a large counter with a discrete brass "+
	"plaque, and on the wall behind the counter is a larger sign.\n");
    add_item(({"desk","counter"}),
	"It is a large walnut desk with a small brass sign attached on "+
	"the front of it.\n");
    add_item(({"plaque","brass plaque"}),
	"A small brass sign. You can probably read it.\n");
    add_item(({"shelves","shelf","gaps","gap","bookshelf","bookshelves"}),
	"The shelves contain books. You notice a couple of gaps where "+
	"books are missing.\n");
    add_item(({"books","book"}),
	"The books are all sorted in reverse alphabetical order.\n");
    add_item(({"sign"}), 
	"It looks quite informative. Maybe you should read it?\n");
    add_item(({"floor","stone"}),
	"The floor is made of dark stone. It produces an impressive "+
	"echo when you walk.\n");
    add_item(({"ceiling"}),
	"You tilt your head back and look at the ceiling. "+
	"Pretty uninteresting.\n");

    add_exit(EXTR + "str2", "east", "@@check_exit@@");

    add_book("seafarer", "The seafarer. By Snorr E. Lasson.",
	BOOKS + "book2", 1);
    add_book("hours", "Sybarite Gods of the Hours. By Shamer Poletip.",
	BOOKS + "book4", 1);
    add_book("codpieces", "Codpieces: Notes on the Socio-sexual "+
	"Hierarchy of Sybarus.", BOOKS + "book5", 1);
    add_book("webcloth", "Webcloth, Weavers, and Webbers. By Gregos Alluria.",
	BOOKS + "webcloth", 1);
    add_book("knight", "Knight on the Holm.",
	BOOKS + "book6", 1);
    add_book("tjana", "Tjana's Story.",
	BOOKS + "book7", 1);
    add_book("holm", "Holm of the Icondite",
	BOOKS +"book8", 1);

    add_npc(LIBR);

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.
	add_prop(ROOM_M_NO_ATTACK, "You get a feeling that the goddess Nantur "+
	    "disapproves of fighting in this place.");
	add_prop(ROOM_M_NO_MAGIC_ATTACK, "You get a feeling that the goddess "+
	    "Nantur disapproves of fighting in this place.");


    /* Set low to enable rapid-reset of the quest_npc. */
    enable_reset(20);
    reset_room();
}

public void
reset_room(void)
{
    if (!objectp(quest_npc))
    {
	if (!random(2))
	    quest_npc=clone_object(NPC + "book_man");
	else
	    quest_npc=clone_object(NPC + "book_wom");

	quest_npc->arm_me();
	quest_npc->place_me();
    }
}

public int
borrow(string str)
{
    if (!librarian)
	write("Hmm...Maybe you should wait for the librarian to do that?\n");
    else
	::borrow(str);

    return 1;
}

public int
return_it(string str)
{
    if (!librarian)
	write("Hmm...Maybe you should wait for the librarian to do that?\n");
    else
	::return_it(str);

    return 1;
}

public int
do_read(string str)
{
    notify_fail("Read what?");
    if (str == "plaque" || str == "brass plaque")
    {
	write("Please keep quiet!\n");
	return 1;
    }

    if (str == "sign")
    {
	write("The library offers the following services:\n");
	write("We provide you with a list of the books available       <list books>.\n");
	write("You may borrow any of these books                       <borrow title>.\n");
	write("Please have the courtesy to return them before leaving  <return book>.\n");
	return 1;
    }

    return 0;
}

public void
init(void)
{
    ::init();
    add_action(do_read, "read");
}
