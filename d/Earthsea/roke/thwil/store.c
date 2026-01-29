/*
 *   The storage room of the Solamnian drugstore, made by Nick
 *   borrowed by Mordur for Thvil
 */
#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/lib/store_support";

#include "/sys/stdproperties.h"

void create_thwil_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(THWIL+"shop", "south");
    set_no_npc(1);
    INSIDE;
}

enter_inv(ob, from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

