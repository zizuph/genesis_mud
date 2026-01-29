/* Arman, 29/11/98 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <stdproperties.h>

#include <macros.h>
#include <std.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>

#define STDLIB          "/d/Krynn/std/library/library"

inherit SANCINROOM;
inherit STDLIB;


void
reset_sanction_room()
{
}

string
long_descr()
{
    return "You are standing in a large archive within the city " +
    "of Sanction. Here various books and tomes are stored for " +
    "use by soldiers of the dragonarmy, wannabe recruits, and " +
    "various denizens of this city. On the wall, a large plaque " +
    "has been set. A sign hangs just below it.\n";
}

void
create_sanction_room()
{
    set_short("dragonarmy archive within the city of Sanction");
    set_long("@@long_descr");

    add_item(({"books","tomes"}),"Many books have been stored " +
      "here, ranging from handbooks to tomes of lore.\n");
    add_item(({"archive","large archive"}),"@@long_descr");
    add_item("wall","On one wall hangs a plaque, with a " +
      "sign beneath it.\n");
    add_item(({"plaque","large plaque"}),"@@read_plaque");
    add_cmd_item(({"plaque","large plaque"}),"read","@@read_plaque");
    add_item("sign","@@read_sign");
    add_cmd_item("sign","read","@@read_sign");

    add_exit(SCITY + "office","west",0);

    //lib_type must be 4 to allow appoint/unappoint
    lib_type = 4;

    reset_room();

    set_lib_id("sanction_lib_id");
    set_lib_path(SLIB);
    set_book_file(SLIB + "book");
    set_lib_type(4);
    set_lib_long("the Archive in the city of Sanction");
    set_search_delay(6.2);
    set_default_topics((["New Arrivals":1,
	"Public section":0,
	"Private section":2,
	"Trash":1]));
    setup_library();
}

void
init()
{
    init_library();
    ::init();
}

void
leave_inv(object player, object dest)
{
    ::leave_inv(player, dest);
    library_leave_inv(player, dest);
}

string
read_plaque()
{
    write("The Sanction Military Archive of the Dragonarmies\n"+
      "====================================================\n\n"+
      "Check the 'index' for a list of topics, and the 'catalog' of each " +
      "topic for a list of available books. You can then 'borrow' any of " +
      "the available books. Note that you must give the complete title of " +
      "a book (up to any '-') you want to borrow. Please do not forget to " +
      "return borrowed books!\n\n" +
      "To write a new book you should give the command 'blank'. " +
      "Then you will get a blank book, which is yours to " +
      "fill with whatever you want, maps, songs, or a novel perhaps? " +
      "The command to start writing is 'bedit'. You write a " +
      "book much the same way you write a note on the board.\n");
    return "";
}

string
read_sign()
{
    write("LIBRARY - QUIET PLEASE!\n\n" +
      "Current Librarian: " + (librarian && sizeof(librarian) ? 
			       COMPOSITE_WORDS(map(librarian,capitalize)) : 
			       "-") + "\n" +
      /*
	    "The guild leader is responsible for 'appoint'ing or 'unappoint'ing " +
	    "the librarian.\n");
      */
      "\n");
    if (librarian && sizeof(librarian) && member_array(TP->query_real_name(), librarian) >= 0)
	write("As librarian, you have these commands available:\n" +
	      " Beautify <bookname>\n" +
	      "       Allows you to change the title, or align the title neatly.\n" +
	      " Movebook <bookname> to topic <newtopic>\n" +
	      "       To remove a book completely, use 'Movebook <bookname> to topic trash'.\n" +
	      " Erase <bookname> | '-all books in trash-'\n" +
	      "       Destroy a book (must be in the trash) unrecoverably.\n" +
	      " Create <new topic> <access level>\n" +
	      "       Access level is: 0: everyone\n" +
	      "                        1: librarian only\n" +
	      "                        2: Dragonarmy members only\n"+
	      " Uncreate <old topic>\n" +
	      " Retire\n");
    return "";
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
    * 2: dragonarmy members only can read
    */
    if (level == 2)
	return ({!!(IS_MEMBER(TP)) || !!(TP->query_wiz_level()),
	  "Soldiers of the Dragonarmy only"});

    return ({ 0,"No access" });
}

int
hook_appoint_unappoint()
{
    if (TP->query_real_name() == "arman" ||
      TP->query_real_name() == "torqual" ||
    TP->query_real_name() == "louie" ||
     TP->query_real_name() == "milan" ||
    (TP->query_dragonarmy_occ_member() &&
            TP->query_guild_leader_occ())
        )
	return 1;

    return 0;
}

void
hook_appointed_info()
{
    write("As of yet, there are no requirements necessary " +
      "to be the Librarian of the Archive. This will probably " +
      "change in the future.\n");
}

int
hook_librarian_requirements()
{
    return 1;
}

