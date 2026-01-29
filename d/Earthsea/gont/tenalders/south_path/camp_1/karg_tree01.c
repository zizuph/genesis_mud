/*
 * Ckrik Aug 2016
 *
 * A tree where some Karg archers can snipe at people below.
 *  
 */

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

#define BELOW "/d/Earthsea/gont/tenalders/south_path/camp_1/karg_camp01"

public nomask void
create_earthsea_room()
{
    set_short("A tree in the forest overlooking a camp");
    set_long("The tall tree overlooks a military camp located " +
        "in a freshly cut clearing. From this vantage point " +
        "you can see the entire camp and the path up the " +
        "mountain to the east. You see several tents on " +
        "ground and some fires.\n");
    add_item((({"forest", "trees", "tree", "forests"})),
        "There is not much of that here now, the occupants of " +
        "of the camp chopped down all the trees in the vicinity " +
        "save a couple here and there including the one you are " +
        "on.\n");
    add_item((({"tent", "tents"})),
        "You see several tents. The tent in the middle seems " +
        "to be the largest and fanciest in the camp.\n");
    add_item((({"fire", "fires"})),
        "You see meat roasting over the fire below.\n");
    add_item((({"below", "ground"})),
        "You look down.\n" + "@@below_desc");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room, 
 *    matching pattern with parse_command syntax, 
 *    description of remote room,
 *    description of this room as seen from remote room 
 *  })
 *
 * Note that upon making it possible to shoot across
 * rooms, you better make your npc:s able to respond
 * to it so they won't be sitting ducks.
 *
 */
mixed 
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (BELOW)->load_me();
   return ({    (BELOW),
                "[at] [on] [the] 'ground' / 'below'",
                "on the ground",
                "on the ground below" });
}

public string
below_desc()
{
    object *folks_below, below;
    (BELOW)->load_me();
    below = find_object(BELOW);
    string long_desc = below->query_long(), liv_desc = long_desc;

    if(objectp(below))
    {
        folks_below = FILTER_LIVE(all_inventory(below));

        if(sizeof(folks_below))
        {
            liv_desc += "You see ";
            liv_desc += COMPOSITE_LIVE(folks_below);
            liv_desc += " below you.\n";
        }
    }

    return liv_desc;
}

public void
reset_room()
{
    ::reset_room();
}
