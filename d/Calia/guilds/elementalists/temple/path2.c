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
    set_short("Above a valley in the foothills");
    set_long("You are at the southwest end of a dirt path nestled in the "
        + "foothills of Calia. It is quiet and tranquil here, with barely "
        + "a whisper of the wind. The path ends abruptly overlooking the "
        + "luscious green valley below you. To the northeast, you can follow "
        + "the path up towards the small vale. Small rocks have been laid "
        + "to form a small path leading downwards into the valley. In the "
        + "middle of the valley, you can see a crystalline building, the "
        + "only indication that there is civilization here in this vibrant "
        + "natural landscape.\n\n");
        
    try_item( ({ "dirt path", "path" }),
        "The dirt path allows you to travel between the small vale to the "
      + "northeast and the valley below you. The path itself consists "
      + "mostly of dirt, but you can tell that someone made an effort to "
      + "put patches of rocks here to stabilize the path and prevent "
      + "erosion from rain.\n");
    
    try_item( ({ "valley", "green valley", "luscious green valley",
        "luscious valley", "down" }),
        "The luscious green valley below you appears to be rather "
      + "deep and large. Being surrounded by mountains has protected the "
      + "valley from the harsh elements. In the middle of the valley, "
      + "you see a crystalline structure and a walled garden that surrounds "
      + "it.\n");
    
    try_item( ({ "small vale", "vale", "northeast" }),
        "To the northeast sits a small vale nestled in the foothills of "
      + "Calia. It sits at a higher elevation than where you are.\n");
      
    try_item( ({ "crystalline", "crystalline structure", "building",
        "crystalline building" }),
        "You are able to overlook the structure, which appears to be a "
      + "large domed structure with five points extending from the "
      + "central dome. It looks very much like a star. The building "
      + "is surrounded by a walled garden. A dazzling array of colors "
      + "reflect back to you from the building. The materials closely "
      + "resemble that of the well-known Crystalline Palace. You can "
      + "head down to take a closer look.\n");
    
    try_item( ({ "garden", "walled garden" }),
        "A walled garden surrounds the domed crystalline structure "
      + "in the valley below you. It's hard to make out what the garden "
      + "contains from here.\n");

    try_item( ({ "dome", "domed structure", "five points", "points",
                 "central dome", "pentacle" }),
        "The domed structure is made of crystallive and looks magnificent "
      + "against the backdrop of the luscious valley below. The star-like "
      + "architecture reminds you that this is no ordinary building.\n");

    try_item( ({ "plant life", "life", "bushes", "flowers", "plants",
                 "plant", "bush", "flower" }),
        "Nothing seems interesting about the plant life here except its "
      + "abundance in the foothills of Calia. The lack of weeds has led "
      + "to a vibrant growth of bushes and flowers.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_exit(ELEMENTALIST_TEMPLE + "path1", "northeast");
    add_exit(ELEMENTALIST_TEMPLE + "path3", "down");

    setuid();
    seteuid(getuid());
}
