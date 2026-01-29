#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void reset_room();

void
create_room()
{
    set_short("An old warehouse");

    set_long("\n"+
             "This old warehouse has seen its glory days long time ago.\n"+
             "It is rather empty except for two crates and a pile of\n"+
             "sand which is dumped in a corner.\n"+
             "");

    add_item("crates", "There are two crates here, probably used at one time to store things.\n");
    add_item("sand", "There is a pile of sand in the corner. You wonder why?\n");
    add_item(({"room" }),"It looks very old and wore down.\n"+
    "");

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/shire", "east");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    reset_room();
}

void
reset_room()
{
    if (present("knife")) return;

    clone_object(S_COMMON_WEP_DIR + "knife")->move(TO);
}

