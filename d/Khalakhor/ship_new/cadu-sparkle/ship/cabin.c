/*
 * cabin.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008
 * Latest update 02/2009
 */

#pragma save_binary
#pragma strict_types

#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();

  set_short("A warm and cozy cabin inside the warship");
  set_long("This is the admirals cabin. You can see that he is a very " +
           "wealthy man. Maybe he has won a lot of battles. There are " +
           "several nice paintings on the walls and in one corner of " +
           "the cabin there is a large desk with many maps. " +
           "You feel quite at home here and you could probably endure " +
           "any storm in this cabin.\n");
  
  add_item("desk",
           "Like most great desks this one is made out of finest " +
           "mahogany. It's quite big and is nailed to the " +
           "floor. Good thing to do, just in case a storm " +
           "comes up.\n");
  add_item(({"painting", "paintings"}),
           "You recognize a copy of the famous Lona Misa. The rest of " +
           "the pictures are paintings of different naval battles.\n");

  add_item(({"map", "maps"}),
           "The maps are nautical maps and there seem to be one or two " +
           "doublets, some being riddled with marks, lines, and notations "+
           "while others seem brand new.\n");

  add_exit("deck", "up");

  add_prop(ROOM_I_NO_DIG, 1);
}
