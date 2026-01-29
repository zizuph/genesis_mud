/* a fishing pole -- created by Stevenson to be part of
* the polar bear quest
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/std/object";

void create_object() {
   set_name("pole");
   add_name("fishingpole");
   add_name("icepole");
   set_adj("fishing");
   set_short("fishing pole");
   set_long("This is a typical fishing pole with a line and a reel. "
      + "It is already baited with an imitation bug so you needn't "
      + "worry about getting your fingers too dirty.\n");
   
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 300);
}
