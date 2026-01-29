#pragma no_clone
#pragma strict_types

object shop;
string store_room;

/*
 * Function name: set_shop
 * Description  : Sets npc's shop object pointer, to make
 *                it easier to see if he's where he's supposed
 *                to be.
 * Arguments    : ob - Object pointer to set as his shop.
 * Returns      : n/a
 */
void
set_shop (object ob)
{
  if (!shop)
    shop = ob;
}

/* Function name: set_store_room
 * Description  : Sets Brom's store room pointer, to make it easier
 *                dealing with him running and hiding from attackers.
 * Arguments    : str - String with the path name to the store room.
 * Returns      : n/a
 */
void
set_store_room (string str)
{
  if (!store_room)
    store_room = str;
}


