/**********************************************************************
 * - cabin.c                                                        - *
 * - A small cabin on the ship.                                     - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/cabin";
 
#include <stdproperties.h>
#include "local.h"
#include "/d/Khalakhor/sys/terrains.h"
 
public void create_cabin()
{
    set_short("The cabin of the Coral Lady");
    set_long("This is the cabin of the Coral Lady. It has a warm "+
      "and inviting atmosphere. It has been constructed of thick oak "+
      "beams, which expresses the sturdiness of this cabin. Many "+
      "details have been taken with this cabin. There are polished brass "+
      "lanterns attached to the walls and a table and chair sitting in "+
      "the corner.\n");
    add_item(({"cabin", "room"}),
      "This is the cabin of the Coral Lady. It has a warm "+
      "and inviting atmosphere. It has been constructed of thick oak "+
      "beams, which expresses the sturdiness of this cabin. Many "+
      "details have been taken with this cabin. There are polished brass "+
      "lanterns attached to the walls and a table and chair sitting in "+
      "the corner.\n");
    add_item(({"coral lady"}),
      "You are in the cabin of the Coral lady.\n");
    add_item(({"oak"}),
      "The room is constructed out of oak wooden beams.\n");
    add_item(({"wall", "walls", "ceiling", "floor"}),
      "The walls, ceiling and flooring are made from thick oak beams.\n");
    add_item(({"lantern", "lanterns", "brass lantern", "brass lanterns"}),
      "There are polished brass lanterns attached to the walls. They "+
      "cast a soft glow about the cabin.\n");
    add_item(({"table"}),
      "The table is made of strong oak wood and is firmly attached to a "+
      "wall and the floor.\n");
    add_item(({"chair"}),
      "The chair is is made from stury oak wood, making it quite heavy. "+
      "It is attached to the floor with a swivel, which allows some freedom "+
      "of movement.\n");
    add_item(({"swivel"}),
      "There is a small swivel attached to the floor and on a leg of a chair. "+
      "It is made from brass and allows freedom of movement with the chair "+
      "and provides stability in strong waves.\n");
    add_exit(GALAITH+"deck","deck");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);
    set_cabin_sound("@@sounds");
}
 
public string sounds()
{
    if(random(2))
        return "The ship glides smoothly through the cool waters.\n";
        return "The ship creaks slightly as it slices through a huge wave.\n";
}
