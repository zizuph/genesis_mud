#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>

inherit "/std/container";

create_container() {
   set_short("fireplace");
   set_name("fireplace");
   set_long(
      "It is a very nice fireplace, filled with hot embers "
      + "and giving the room much warmth and light. Above the "
      + "fireplace is an oaken mantle. "
      + "\n");
   
   add_prop(CONT_I_VOLUME,50);
   add_prop(CONT_I_WEIGHT,50);
   add_prop(CONT_I_MAX_VOLUME,80);
   add_prop(CONT_I_MAX_WEIGHT,80);
   add_prop(CONT_I_RIGID,1);
   add_prop(OBJ_M_NO_GET,"It is WAY too heavy for you to carry around.\n");
}

