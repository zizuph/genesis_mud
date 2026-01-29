/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:     1.6.95     typos taken out                 Maniac
                 15.9.94    kick out non-interactives       Maniac
                    8.94    taken out timer stuff & cmdsoul Maniac
                    8.94    fixed typos                     Maniac
                15. 2.93    path system installed           Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.92    slight modifications            Merlin
                28.12.92    intalled cmdsoul                Merlin
                20.12.92    descriptions modified           Merlin
                 2.11.92    installed guard system          Merlin
                31.10.92    installed new timer             Merlin

    purpose:	entrance to Gelan, drawbridge can be closed
    exits:      north to Gelan, south to crystalline palace

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      exit to the moat
    bug:        none known
*/

#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

/*
 * Function name: pass_drawbridge
 * Description:   checks if drawbridge is down (to cross it)
 * Arguments:     none
 * Returns:       1 if down, 0 if up and not passable
 */
int
pass_drawbridge()
{
  return 0;
}


/*
 * Function name: look_drawbridge
 * Description:   gives description of the room 
 * Arguments:     none
 * Returns:       string with description
 */
string
look_drawbridge()
{
    return "You are standing in front of a drawbridge. To the north "
      + "is the fortified gate of Gelan. The gate has an impressive "
      + "height, which fully hides the rest of the town. To your "
      + "south is a road leading to a large roundabout. "
      + "The drawbridge is down now. You can pass to the gate of " 
      + "Gelan.\n";

} /* look_drawbridge */


/*
 * Function name: exa_drawbridge
 * Description:   gives description of bridge
 * Arguments:     none
 * Returns:       string with description
 */

string
exa_drawbridge()
{
    return "The drawbridge looks very solid. Because it is down now, you "
            + "can easily pass to the gate of Gelan.\n";
} /* exa_drawbridge */



/*
 * Function name: create_room
 * Description:   create the room
 * Arguments:     none
 * Returns:       none
 */

public void
create_gelan_room()
{
    /* descriptions */
    set_short("Drawbridge of Gelan");
    set_long("@@look_drawbridge");

    /* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "gate","north","@@pass_drawbridge");
    add_exit(GELAN_ROOMS + "entrance_road","south",0);

    /* items in the room */

    add_item(({"drawbridge", "bridge"}),"@@exa_drawbridge");
    add_item("gate", "The gate is impressive. Not only its height but "
      + "also its strength. It seems impossible to overcome it. To "
      + "the left and right side of the gate you see huge towers. They "
      + "are engraved with magical symbols meant to ward off all evil. "
      + "East and west big white walls stretch out as far as you can see.\n");
    add_item("gelan","You should know Gelan! If not, it's time "
          + "to have a look there!\n");
    add_item(({"tower","towers"}),"The Towers are really huge. They are "
          + "made out of sandstone and you notice some strange magical "
          + "symbols on them.\n");
    add_item(({"wall","walls"}),"The walls are a bright white colour, " 
          + "and seem to shine. You wonder whether they are made of " 
          + "some sort of white lava rock.\n");
    add_item(({"symbol","symbols","town"}), GO_CLOSER);
    add_item(({"road","floor","ground","walk","street"}), 
            "The road to your south is " 
          + "something like a gravel walk, made with a lot of small pieces "
          + "of broken white marble. It leads to a large roundabout.\n");
    add_item(({"roundabout", "large roundabout"}), "The large roundabout " 
            + "away to your south has much traffic going around it.\n");
} /* create_room */



/*
 * Function name: init
 * Description:   
 * Arguments:     none
 * Returns:       none
 */

void
init()
{
  ::init();
}



