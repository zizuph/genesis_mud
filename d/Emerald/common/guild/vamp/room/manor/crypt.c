/*
 * Crypt
 * Louie 2006
 */
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit VAMP_LIB_DIR + "lair_new";

void
create_vamp_room()
{
    set_short("Crypt");
    set_long("You stand in an ancient cavern which serves "+
        "as a large underground crypt.  "+
        "Coffins line the walls, cold and silent sentinels of "+
        "this private chamber.  "+
        "To the north a small alcove has been cut from the stone "+
        "to make a storage room, while to the south is another "+
        "cavern.  "+
        "\n");
    add_exit("cave1.c","up");
    add_exit("crypt_storage","north");
    add_exit("crypt_library","south");
    add_coffins();
}

public void init()
{
    ::init();
    init_lair();
}




