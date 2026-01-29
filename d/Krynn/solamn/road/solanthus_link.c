/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

void
create_road_room()
{
    set_short("On the road");
    set_long("You are on a road across the Plains of Solamnia. The " +
        "never ending plains completely surround you. While the " + 
        "plains are wild to the north, they appear to be cultivated " +
        "to the south. Fields of varying colours can be seen " +
        "there. A border watch vigilantly guards the " +
        "road at this spot.\n");
    add_item(({"road"}),
        "The road is dusty and dirty, as most roads are. It extends " +
        "north and south from here.\n");
    add_item(({"bushes", "bush"}), "The plains are dotted with many " +
        "tough windswept bushes to the north.\n");
    add_item("grass", "The plains to the north are blanketed with a " +
        "hardy grass. It sways gently as the wind dances through it.\n");
    add_item(({"plains", "plains of solamnia"}),
        "The plains are wild to the north of here, with bushes, a tree " +
        "here or there and grass, while fields spread out in the south.\n");
    add_item(({"south", "field", "fields", "cultivated land"}),
        "Wheat and other types of grain have been planted in the " +
        "fields. Further south, beyond a row of windbreaking trees, " +
        "you can make out a few houses.\n");
    add_item(({"row", "houses", "row of trees", "trees", "tree"}),
        "They are some distance away, so you cannot make out any details " +
        "from here.\n");
    add_item(({"border watch", "watch", "guard", "border guard", "guards",
      "men", "man"}), "These two men stand guard on the road against " + 
        "any intruders.\n");

   if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|S@@",6,1);
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|S@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|S@@",3,0); 
    add_exit(SOLANTHUS_LINK,"south","@@closed@@",3,0);
}

int
closed()
{
    write("The border guard says: We are instructed not to let anyone " +
          "pass. I'm sorry, but you will have to turn back (for now).\n");
    return 1;
}

