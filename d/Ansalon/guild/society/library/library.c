/* 
 * /d/Ansalon/guild/society/library/library.c
 *
 * Kender library for wild tales, maps and other things 
 * Gwyneth, September 1999 
 */

/* Navarre July 3rd 2006, added line break for no fight prop. */


#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "../guild.h"
#include <macros.h>
#include <std.h>
#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>

#define STDLIB   "/d/Krynn/std/library/library"

inherit KENDERMORE_IN;
inherit STDLIB;

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("Library of maps, stories and wild tales");
    set_long("You are standing in a treasure trove of knowledge. Likely " + 
        "half of it is exaggerated, and the other half outdated, but the " + 
        "truth lies buried somewhere. Kender are world famous for their " + 
        "desire to travel, and here lie numerous copies of stories and " + 
        "maps written by those famous travellers. A set of stairs winds " + 
        "down to the rest of the guild. A small sign is posted " + 
        "on the wall with instructions on writing your own work.\n");

    add_item(({"stairs", "stair", "set", "set of stairs"}), "They look " +
        "a bit old, but should hold your weight easily.\n");
    add_item(({"copies", "stories", "maps"}), "They are stored on various " + 
        "shelves around the library.\n");
    add_item(({"shelves", "various shelves"}), "Many books are stacked " + 
        "on these shelves. Whether or not everything written here is true " + 
        "or not is highly doubtful.\n");
    add_item(({"wall", "walls"}), "Many shelves line the walls. A small " + 
        "sign is posted on one wall.\n");
    add_item(({"sign", "small sign"}),
        "Check the 'index' for a list of topics, and the 'catalog' of each " + 
        "topic for a list of available books. You can then 'borrow' any of " + 
        "the available books. Note that you must give the complete title " + 
        "of a book (up to any '-') you want to borrow. Please do not " + 
        "FORGET to return borrowed books!\n\n" + 
        "To write a new book you should give the command 'blank'. " + 
        "You will get a blank book, which is yours to fill with whatever " + 
        "you wish, maps, songs, or exciting adventures. The command to " + 
        "start writing is 'bedit'. You write a book much the same way " + 
        "you write a note on the board.\n");
    add_cmd_item(({"sign", "small sign"}), "read", "@@read_sign");
    add_prop(ROOM_M_NO_ATTACK, "This is a library! No fighting!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "This is a library! No fighting!");

    reset_room();

    add_exit(KGROOM + "rack_room", "down", 0);

    set_lib_id("kender_lib_id");
    set_lib_path(KGLIB);
    set_book_file(KGLIB + "book");
    set_lib_type(4);
    set_lib_long("the Kender library");
    set_max_librarian_num(4);
    set_search_delay(3.2);
    set_default_topics((["New Arrivals":1,
        "Maps":0,
        "Stories":0,
        "General":0,
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

public void
hook_leave_with_books(object who, int i)
{
    who->catch_msg("You remember to return the book" + 
        (i > 1 ? "s" : "") + " to the shelves before leaving.\n");
    tell_room(TO, QCTNAME(who) + " returns the book" + 
        (i > 1 ? "s" : "") + " to the shelves before leaving.\n");
}

int
hook_appoint_unappoint()
{
    if(TP->query_real_name() == "arman")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void
hook_appointed_inf()
{
    write("Various members of the guild may be librarians. " +
        "Contact the guildmaster.\n");
}

int
hook_librarian_requirements()
{
    return MEMBER(TP);
}

string
read_sign()
{
    int i, temp;
    string str = "";

    if(sizeof(librarian) > 0)
    {
        for(i = 0; i < sizeof(librarian); i++)
        {
            if(TP->query_real_name() == librarian[i])
            {
                temp = 1;
            }
        }
        if(temp)
        {
            str = "As librarian, you have these commands available:\n" +
                " Beautify <bookname>\n" +
                "       Allows you to change the title, or align " +
                "the title neatly.\n" +
                " Edit <bookname>\n" +
                "       Allows you to edit a book or add to it.\n" +
                " Movebook <bookname> to topic <newtopic>\n" +
                "       To remove a book completely, use 'Movebook " +
                "<bookname> to topic trash'.\n" +
                " Erase <bookname> | '-all books in trash-'\n" +
                "       Destroy a book (must be in the trash) " +
                "unrecoverably.\n" +
                " Create <new topic> <access level>\n" +
                "       Access level is: 0: everyone\n" +
                "                        1: librarian only\n" +
                " Uncreate <old topic>\n" +
                " Retire\n";
        }
    }
        
    return("Check the 'index' for a list of topics, and the 'catalog' of " +
        "each topic for a list of available books. You can then 'borrow' " +
        "any of the available books. Note that you must give the complete " +
        "title of a book (up to any '-') you want to borrow. Please do not " +
        "FORGET to return borrowed books!\n\n" +
        "To write a new book you should give the command 'blank'. " +
        "You will get a blank book, which is yours to fill with whatever " +
        "you wish, maps, songs, or exciting adventures. The command to " +
        "start writing is 'bedit'. You write a book much the same way " +
        "you write a note on the board.\n" + str);
}

