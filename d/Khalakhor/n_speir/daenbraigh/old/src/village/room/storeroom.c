/*
 * Store room for the goblin village shop
 * TAPAKAH, 09/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/room"; 
inherit "/lib/store_support";

#include <stdproperties.h> 
#include "../../daenbraigh.h"
#include "../../village/village.h";


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
  set_long("   This is the storage room for the village shop.\n");
  
  add_exit("shop", "east");
  
  add_prop(ROOM_I_INSIDE,1);
  set_alarm(0.5,0.0,reset_room);
}

void
reset_room()
{
  ::reset_room();
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
