/*
 * A normal storage room
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/sys/stdproperties.h"
#include "/d/Shire/buckland/buckdefs.h"

#define EXIT1 BB_DIR + "shop","south",0,1

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(EXIT1);

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
}

