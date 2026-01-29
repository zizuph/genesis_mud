//
// store_room.c
//
// Store room for the village shop in Baile Ashlagh
//
// Zima  - June 10/98
//
inherit "/d/Khalakhor/std/room";
inherit "/lib/store_support";
 
#include <stdproperties.h>
#include "defs.h"
 
public object pointer_me()         { return TO; }
public int*   query_local_coords() { return ({3,6}); }
 
//
// reset_room
//
public void reset_room()
{
    int i;
    object *packs;
 
    packs = filter(all_inventory(TO), &->query_prop("_port_macdunn_pack"));
 
    reset_euid();
    for (i = sizeof(packs); i < 4; i++)
        clone_object("/d/Khalakhor/common/obj/backpack")->move(TO);
}
 
//
// create_khalakhor_room
//
public void create_khalakhor_room()
{
    set_short("storage room");
    set_long("This is the storage room for the village shop.\n");
    add_exit("shop", "down");
    INSIDE;
    set_alarm(0.0,0.0,reset_room);
}
 
//
// enter_inv - used to scroll off old objects in shop, limiting inventory
//
public void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(obj))
        store_update(obj);
}
