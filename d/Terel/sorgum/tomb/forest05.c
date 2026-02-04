inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("overlook");
    set_long(
        "You are overlooking a small valley, a secret jealously "+
        "protected by the mountains surrounding it. "+
        "Cliffs rise steeply on all sides, the steepest "+
        "being to the north, where part of a mountain has "+
        "fallen away from itself. Landslide debris formed "+
        "a dam of sorts which has drowned nearly half "+
        "the valley in water. "+
        "There appears to be an old house some distance away, "+
        "crumbled to ruins, and "+
        "remnants of a great vineyard. A faint wind "+
        "blows, chilling the air. A ravine lies to the south,  "+
        "an ominous jagged gash in the dark stone of the "+
        "mountain.\n");

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "In the distance you can see some trees.\n");
    add_item("ground", 
	"The ground is hard with frost.\n");
    add_item(({"ravine", "gash"}),
        "Your eyes cannot penetrate the darkness which leads north "+
        "into the mountain.\n");
    add_item(({"house", "ruins", "mansion", "building"}),
        "These are the remains of a once-great house, long ago "+
        "abandoned and now crumbling to ruins.\n");    
    add_item(({"north", "cliff", "landslide", "avalanche", "debris"}),
        "The north edge of the valley is marked by a sheer cliff "+
        "and a huge landslide at its base, which has nearly "+
        "buried an old house, and formed a dam.\n");
   add_item(({"mountain", "mountains", "valley"}), 
       "These mountains are dark and forbidding. They cast "+
       "shadows over most of the valley and the water that "+
       "is slowly encroaching upon it.\n");
   add_item(({"water", "dam"}),
       "Rocks and shale fallen from the mountainside have "+
       "dammed the flow of water, forming a large body "+
       "of icy water that is slowly drowning the valley.\n");

   
    add_prop(ROOM_I_INSIDE, 0);
    add_exit(TOMBDIR + "forest06", "down");
    add_exit(TOMBDIR + "ravine", "south");

}


