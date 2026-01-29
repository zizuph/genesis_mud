/*
 * Pathway to Elementalist Temple
 * 
 * This is a pathway leading to above the Elementalist Temple valley
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
    set_short("Above a valley in the foothills");
    set_long("You are standing on a dirt path nestled in the foothills "+
        "of Calia. To the north you see a luscious green valley "+
        "stretching out into the distance. The path continues upwards "+
        "off to the northwest and downwards off to the southeast.\n");
        
    try_item( ({ "dirt path", "path" }),
        "The dirt path allows you to travel northwest or southeast. "+
        "The path itself consists mostly of dirt, but you can tell "+
        "that someone made an effort to put patches of rocks here "+
        "to stabilize the path and prevent erosion from rain.\n");
    
    try_item( ({ "valley", "green valley", "luscious green valley",
        "luscious valley"}),
        "The luscious green valley below you appears to be rather "
      + "deep and large. Being surrounded by mountains has protected the "
      + "valley from the harsh elements.\n");
    
    try_item( ({ "plant life", "life", "bushes", "flowers", "plants",
                 "plant", "bush", "flower" }),
        "Nothing seems interesting about the plant life here except its "
      + "abundance in the foothills of Calia. The lack of weeds has led "
      + "to a vibrant growth of bushes and flowers.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_exit(ELEMENTALIST_TEMPLE + "path7", "northwest");
    add_exit(ELEMENTALIST_TEMPLE + "path5", "southeast");

    setuid();
    seteuid(getuid());
}
