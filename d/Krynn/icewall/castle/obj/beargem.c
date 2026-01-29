/* a diamond coded for Icewall by Stevenson */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit "/std/object";

create_object() {
   set_name("gem");
   add_name("beargem");
   set_short("glowing gem");
   add_adj("glowing");
   set_long(
      "As you study the glowing gem, "
      + "you see what appears to be a polar "
      + "bear trapped inside.\n");
   
   add_prop(OBJ_I_VALUE, 3000);
   add_prop(OBJ_I_WEIGHT, 175);
   add_prop(OBJ_I_VOLUME, 70);
}
