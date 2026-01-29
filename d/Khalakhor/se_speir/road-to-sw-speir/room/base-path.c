/*
 * Base file for the road linking the SE and the SW speirs
 * Tapakah, 09/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <filepath.h>
#include "../defs.h"

inherit KSTDROOM;
inherit BASE_ROOM;

string
setup_camp_long ()
{
  string desc = "You are on a medium-width path between a military camp "+
    "to the south and steep mountains to the north. You can enter "+
    "the camp, or continue moving along the path. The camp seems to be "+
    "carrying the colors of blue, green and black according to the "+
    "clans of the soldiers in it. Beyond the camp you can smell and "+
    "head the Cala Fasdagh crashing into the rocks.\n";
    
  return desc;
}

string
setup_long ()
{
  string desc = "You are walking on a path next the rocky shore of the "+
    "Cala Fasdagh. Waves are crashing into the wide patch of "+
    "rocks to your south with a never-ending hammering, "+
    "however, you are far out of their reach. The path is "+
    "not very wide, but not too narrow as well, probably "+
    "sufficient for a cart to drive on. The terrain is quite "+
    "rugged, though, and such a cart would need quite sturdy "+
    "wheels. To your north the mountains make a sharp turn "+
    "towards the path effectively blocking any passage in their "+
    "direction. There is barely any vegetation around.\n";
  return desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  set_short("On a path next to the rocky shore");
  set_long(setup_long);
  add_item(({"sea", "cala fasdagh", "Cala Fasdagh", "waves"}),
           "The waves, six feet and higher, are constantly crashing "+
           "into the rocky strip between you and the sea. Occasionally "+
           "a bouncing spash lands at your feet.\n");
  add_item(({"rocks", "strip"}), "The rocks are dark and glistening "+
           "with the sea water. Birds land on them once in a while, "+
           "in search for prey.\n");
  add_cmd_item(({"mountains"}), ({"climb"}),
               "It's not like the mountains are particularly "+
               "high here, but they are nearly vertical and too crumbly to "+
               "try to climb them.\n");
}
