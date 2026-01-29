/*********************************************************************
 * - club.c                                                        - *
 * - This is the base room of the Gentlemans Club located in       - *
 * - Drakmere                                                      - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/

#include "../guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

inherit STD_ROOM;

void
create_guild_room()
{
}

nomask void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    /* To set the short desc. in the rooms. */
    set_short("Gentleman's club room");
    set_long("Gentleman's club room.\n");
    add_item(({"wall", "walls"}),
      "The walls are made from darken grey stones. There are "+
      "a few lanterns attached to them.\n");
    add_item(({"floor", "flooring"}),
      "The flooring is made from darkened hard wood with tiles placed "+
      "in an intricate pattern around a symbol in the center.\n");
    add_item(({"ceiling", "roof"}),
      "The ceiling is dark just as the walls, but there is a large "+
      "symbol painted in gold.\n");
    add_item(({"symbol", "gold symbol"}),
      "The symbol is definately painted gold and is recognizable as "+
      "GC.\n");
    add_item(({"light", "lighting", "lantern", "lanterns"}),
      "There are a few golden lanterns attached firmly to the walls.\n");
    add_item(({"pattern", "patterns", "intricate pattern", "intricate patterns"}),
      "There is are various patterns stained in the tiles. Red is "+
      "the most dominant colour used and they have been intricately done.\n");

    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_room_tell(({
      "The joyous sound of laughter infiltrates from an adjoining room.\n",
      "The soft sounds of footsteps are heard along the wooden floor.\n",
      "The sweet aroma of pipe tobacco infiltrates the air.\n",
    }));

   
    create_guild_room();

}
