/* File:          /d/Khalakhor/ship/macdunn/shire/cabin.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications: 
 * Purpose:       The cabin is a room on the Khalakhor to
 *                Shire ship. It contains a chest.
 *                /d/Khalakhor/ship/macdunn/shire/chest.c
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 * Ported to the new ship system by Tapakah, 03/2009
 */

#pragma save_binary
#pragma strict_types

#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

inherit STDSHIPROOM;

object chest;

public string sounds ();

public void
create_room()
{
  ::create_shiproom();

  set_short("the cabin of the Corran");
  set_long("   This is the cabin of the Corran. The cramped quarters " +
           "are barely comfortable for one person. Little lighting gives " +
           "the room a heavily shaded quality, the only light source " +
           "coming from outside. A bed, a chair, and a table decorate " +
           "the room. An archway surrounds the exit to the deck.\n");
  
  add_item(({"cabin","quarters","cramped quarters","room"}),
           "@@query_long");
  add_item(({"lighting","shadows","light source"}),"The shadows " +
           "in the room are caused by the only light source, natural light " +
           "which seeps in through cracks between the woodwork, and the " +
           "archway.\n");
  add_item(({"woodwork","wood"}),"The walls, floor, and ceiling " +
           "are made from the same sturdy pine as the rest of the ship.\n");
  add_item("walls","The walls are constructed of pine.\n");
  add_item(({"floor","ceiling","wall"}),"It is made out of pine.\n");
  add_item("pine","Bleached beige, pine is a lightweight wood " +
           "that is durable.\n");
  add_item("bed","The bed is made, and is used by the captain of " +
           "the ship.\n");
  add_item("chair","The chair is not tucked underneath the " +
           "table, but rather, out in the open.\n");
  add_item("table","The table is bare of any covering.\n");
  add_cmd_item(({"on bed","down on bed","bed"}),({"lie","rest"}),
               "You rest on the bed for a short while, then stand back up.\n");
  add_cmd_item(({"on chair","chair"}),"sit","You sit on the chair " +
               "briefly, but find it boring, so you stand again.\n");
  add_item(({"furniture","large furniture"}),"A bed, a chair and a " +
           "table are the only large pieces of furniture in the cabin.\n");
  add_item("archway","The archway surrounds the entrance to or exit " +
           "from the cabin.\n");
  add_item("deck","The main deck of the ship lies outside the cabin.\n");
  
  add_exit("deck", "out", 0);
  
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);
  
  chest = clone_object(SHIP_OBJS_DIR + "/chest");
  chest->move(this_object(), 1);

  set_cabin_sound(sounds());
}

public string
sounds ()
{
    if (random(2))
        return "The ship softly sways on the ocean.\n";

    return "All is quiet as the ship smoothly sails.\n";
}
