/*
 * Store room for the hammerhands shop
 * TAPAKAH, 10/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/room"; 
inherit "/lib/store_support";

#include <stdproperties.h> 
#include "../../daenbraigh.h"
#include "../../hhands/hhands.h";


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
  set_default_stock(({HH_PACK,3,HH_TORCH,3,HH_LAMP,3,HH_STONE,3,HH_FLASK,3}));
}

void
reset_room()
{
  ::reset_room();
  reset_store();
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
