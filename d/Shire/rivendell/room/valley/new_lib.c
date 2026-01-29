inherit "/std/room";
inherit "/d/Gondor/std/library/library";

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "local.h"

inherit HOUSE_IN_BASE;

public string exa_poster();

void
create_house_room()
{
    set_short("Library");
    set_long("This is a library.\n");
    set_lib_id("rivendell_lib_id");
    set_lib_path("/d/Shire/rivendell/room/valley/library");
    set_default_topics((["General":0,"Lays":1]));
    set_lib_type(4);
    set_search_delay(6.7);
    set_max_librarian_num(1);
    setup_library();
    add_item(({"poster", "instructions"}), &exa_poster());
    add_cmd_item(({"poster", "instructions"}), "read", &exa_poster());

}

void
init()
{
    ::init();
    init_library();
}

void
leave_inv(object player, object dest)
{
    library_leave_inv(player, dest);
    ::leave_inv(player, dest);
}

public string
exa_poster()
{
    string text;
 
    text = (capitalize(query_lib_long()) + "\n\n" +
        "index \n" +
        "   Lists the shelf names and the catalog of each shelf for available books.\n\n" +

        "borrow <full book title>\n" +
        "   Searches the shelves, and retrieves the book for you. When you 'borrow' a book, please give the complete title (up to any '-'). \n\n" +

        "borrow blank\n" +
        "   Gives you a blank book that you may submit to be added. Feel free to write anything, so long as it is appropriate for this library.\n\n" +
        "return\n" +
        "   Returns the book you borrowed.\n\n\n");
 
    if (check_librarian(this_player()->query_real_name()) ||
        this_player()->query_wiz_level())
    {
        text += "Librarians have these commands available:\n\n" +
            "beautify <bookname>\n" +
            "   Allows you to change the title, or align the title neatly.\n\n" +
            "edit <bookname>\n" +
            "   Allows you to edit a book or add to it.\n\n" +
            "movebook <bookname> to topic <newtopic>\n" +
            "   To remove a book completely, use 'Movebook <bookname> to topic trash'.\n\n" +
            "erase <bookname> | '-all books in trash-'\n" +
            "   Destroy book(s) (must be in the trash).\n\n" +
            " create <new shelf-topic> <access level> Access level is:\n" +
            "   0: General Public+\n"+
            "   1: Librarian Only\n" +
            "   2: Noldor Only\n\n" +
            "uncreate <old shelf-topic>\n" +
            "   Removes an old shelf.\n\n" +
            "retire as a librarian\n\n";
//            "Council members do not have these abilities, but they may:\n" +
//            " Appoint <name> as librarian\n" +
//            " Unappoint <name> as librarian\n";
    }
 
    return text;
}
