/*
 *   The storage room of the Bree shop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "huntclub.h"
#include "/sys/stdproperties.h"


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
    set_short("Huntclub storage room");
    set_long("You have entered the dusty storage room of the " +
        "Tools and Supplies shop. This is where the shopkeeper " +
        "keeps all his items that are for sale in the store. " +
        "You better leave the stuff here alone, or else the " +
        "shopkeeper will be upset with you.\n");

    add_exit(HUNTCLUB_DIR + "huntclub_joinrm","south");

    add_prop(ROOM_I_NO_CLEANUP, 1); // We don't want this room to be unloaded
    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}

reset_room() 
{
int index;
}
