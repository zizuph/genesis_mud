#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

//#define BOOK_LIST "/d/Gondor/common/library/books/grbooks"

int    test_open();

static string *books, 
              *authors;

public void
create_room()
{
    set_short("a corridor in the second floor of the Gondorian "
      + "Rangers' Guildhouse");
    set_long(BSN("You are in a corridor in the second floor of the "
      + "Gondorian Rangers' Guildhouse. An open doorway leads west, "
      + "and there is a plaque beside the door. The corridor leads "
      + "south to a hall."));
    add_item("plaque", "The plaque states:\n"
      + " Library and Archive of the Gondorian Rangers.\n"
      + "\tNo talking!\n");
    add_item("doorway","The doorway is open, and you can see shelves "
      + "filled with books inside.\n");
    add_exit(RANGER_GON_DIR + "uphall",          "south", 0, 0);
    add_exit(RANGER_DIR + "library/rog_library", "west",  test_open, 0);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_M_NO_STEAL, no_theft);
}

int
test_open()
{
    int     wl = TP->query_wiz_level(),
            n;

    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS)
    {
        write("You have no access to the library!\n");
        return (!wl);
    }

    return 0;
/*
    if (TP->query_guild_name_occ() == "Gondorian Rangers Guild")
        return 0;

    restore_object(BOOK_LIST);
    while(n < sizeof(authors))
    {
        if(TP->query_real_name() == authors[n])
        {
            write("The library is open to you in acknowledgement of "
              + "your contribution to it!\n"
              + "Welcome to the Library of the Rangers of Gondor!\n");
            return 0;
        }
        n++;
    }

    write("The library is not open for other than the Rangers, sorry!\n");
    return (!wl);
*/
}

