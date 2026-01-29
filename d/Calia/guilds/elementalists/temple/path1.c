/*
 * Pathway to Elementalist Temple
 * 
 * This is the pathway leading to the Elementalist Temple valley
 * that houses the Elemental Clerics, Elemental Worshippers, and
 * Elemental Seekers guilds.
 *
 * Created by Petros, April 2010
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit "/std/room";
inherit "/d/Calia/lib/try_item";

/*
 * Function:    create_room
 * Description: Standard room creation function.
 */
public void
create_room()
{
    set_short("Along a path in the foothills");
    set_long("You are walking along a dirt path nestled in the foothills "
        + "of Calia. It is quiet and tranquil here, with barely a whisper "
        + "of the wind. The air is fresh and life surrounds you as you gaze "
        + "at the various plant life that have found refuge from the "
        + "harsh elements. To the northeast you see a small vale. The path "
        + "continues to the southwest towards a luscious green valley.\n\n");

    try_item( ({ "dirt path", "path" }),
        "The dirt path allows you to travel between the small vale to the "
      + "northeast and the valley to the southwest. The path itself consists "
      + "mostly of dirt, but you can tell that someone made an effort to "
      + "put patches of rocks here to stabilize the path and prevent "
      + "erosion from rain.\n");
    
    try_item( ({ "valley", "green valley", "luscious green valley",
        "luscious valley", "southwest" }),
        "The luscious green valley to the southwest appears to be rather "
      + "deep and large. Being surrounded by mountains has protected the "
      + "valley from the harsh elements. In the middle of the valley, "
      + "you see a crystalline structure that looks like it could be "
      + "a building.\n");
    
    try_item( ({ "mountain", "mountains" }),
        "The Calian mountains surround you on all sides, providing shelter "
      + "from the harsh elements. It helps to keep this area relatively "
      + "calm and serene.\n");

    try_item( ({ "small vale", "vale", "northeast" }),
        "To the northeast sits a small vale nestled in the foothills of "
      + "Calia. It sits at a slightly higher elevation than where "
      + "you are.\n");
      
    try_item( ({ "crystalline", "crystalline structure", "building",
        "crystalline building", "structure" }),
        "You can't see the details of the building as you are still too "
      + "far away, but it is reflecting a dazzling display of rainbow "
      + "colors. The materials closely resemble that of the well-known "
      + "Crystalline Palace. You can travel to the southwest if you "
      + "want to take a closer look.\n");
    
    try_item( ({ "plant life", "life", "bushes", "flowers", "plants",
                 "plant", "bush", "flower" }),
        "Nothing seems interesting about the plant life here except its "
      + "abundance in the foothills of Calia. The lack of weeds has led "
      + "to a vibrant growth of bushes and flowers.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_exit(ELEMENTALIST_TEMPLE + "newarchway", "northeast");
    add_exit(ELEMENTALIST_TEMPLE + "path2", "southwest");

    setuid();
    seteuid(getuid());
}
