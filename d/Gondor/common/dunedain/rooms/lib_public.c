/*
 *  The room of the library in the Houses of the Dunedain
 *  where the histories of the 12 houses are kept.
 *
 *  Olorin, 20-nov-94
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room";
inherit "/d/Gondor/common/lib/new_library";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

// Prototypes
string  exa_plaque();

public void
create_gondor()
{
    set_short("in the public part of the Library of the Dunedain");
    set_long(BSN(
        "This room is the part of the library in the House of the Dunedain "
      + "that is open to the public. Here works of knowledge and lore are "
      + "kept, including the recorded history of each of the Houses of the "
      + "Dunedain. The Lords and Ladies of the Houses can "
      + "add new books and remove old ones. In a corner is a desk "
      + "where the librarian usually sits. At the front of the "
      + "desk is a plaque with instructions how to use the library."));

    add_exit(DUNEDAIN_DIR + "rooms/lib_houses", "west", "@@check_exit", 0);
    add_exit(DUNEDAIN_DIR + "rooms/hallw_n",    "east", "@@lib_check", 0);

    ceiling();
    walls(1);
    floor(1);

    add_item("desk", BSN(
        "It is a simple wooden desk without any drawers but with a "
      + "wide top so that the librarian can put many books onto it."));

    add_item(({"plaque", "instructions", }), exa_plaque());
    add_cmd_item(({"plaque", "instructions", }), "read", exa_plaque());

    add_prop(ROOM_I_INSIDE, 1);

    set_save_path(DUNEDAIN_DIR + "books/public_books");
    set_write_dir(DUNEDAIN_DIR + "books");
    set_library_name("the Library of the Dunedain");
    set_librarian_room(DUNEDAIN_DIR + "rooms/lib_lords");
    set_read_cmd("read");
    set_log_file("dunedain");
    set_up_library();
}

void
init()
{
    ::init();
    init_library();
}

int
check_exit()
{
    if (lib_check())
        return 1;

    return ::check_exit();
}

string
exa_plaque()
{
    return
        "\n\tVisitors of the House of the Dunedain can use these commands:\n\n"
      + "\tlist [books]   - list the available titles,\n"
      + "\tborrow <title> - borrow a book with the title <title>,\n"
      + "\treturn book    - return a book,\n"
      + "\tread <title>   - read a book without borrowing it,\n"
      + "\n\tMembers of the Houses of the Dunedain can also use this command:\n\n"
      + "\twrite book     - write a new book and submit it to the Lords\n"
      + "\t                 and Ladies of the Dunedain for addition to the\n"
      + "\t                 library.\n"
      + "\n\tLords and Ladies of the Dunedain can add new books to the\n"
      + "\tLibrary without submitting them. They can also remove old titles.\n\n";
}

int
query_write_priv(object pl)
{
    if (IS_MEMBER(pl) || pl->query_wiz_level())
        return 1;
    return 0;
}

int
query_remove_priv(object pl)
{
    if ((pl->query_dunedain_level() < DL_LORD) &&
        (!pl->query_wiz_level()))
        return 0;
    return 1;
}

int
query_secure_add(object pl)
{
    if (pl->query_dunedain_level() < DL_LORD)
        return 1;

    return secure_add;
}
