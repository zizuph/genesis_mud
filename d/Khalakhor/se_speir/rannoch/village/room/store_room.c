/* File         : /d/Khalakhor/se_speir/rannoch/village/room/store_room.c
 * Creator      : Darragh@Genesis
 * Date         : 03-07-27      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications:
 */

inherit "/d/Khalakhor/std/room"; 
inherit "/lib/store_support";

#include <stdproperties.h> 
#include "room.h"
#define TO this_object()

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}
 
public void
reset_room()
{
    int i;
    object *packs;
    object *dirks;
 
    packs = filter(all_inventory(TO), &->query_prop("_port_macdunn_pack"));
    dirks = filter(all_inventory(TO), &->id("dirk"));
 
    reset_euid();
    for (i = sizeof(packs); i < 4; i++)
        clone_object("/d/Khalakhor/common/obj/backpack")->move(TO);
 
    for (i = sizeof(dirks); i < 3; i++)
        clone_object("/d/Khalakhor/common/wep/dirk")->move(TO);
}
 
/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room() 
{
    set_short("storage room");
    set_long("This is the storage room for the village shop.\n");

    add_exit(ROOM + "shop", "east");

    add_prop(ROOM_I_INSIDE, 1);
    set_alarm(0.0,0.0,reset_room);
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called when an object enters this inventory.
 *                Used here to keep track of the store's inventory
 *                to 'scroll' off old objects, keeping the inventory
 *                under control.
 * Arguments    : obj - Object pointer to the incoming object.
 *                from - Object pointer to 'obj's last environment.
 * Returns      : n/a
 */
public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(obj))
        store_update(obj);
}
