#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"
inherit "/std/object";

create_object() {
   set_name("igloo");
   set_short("igloo");
   set_long(
      "The igloo is rounded and shaped like a half-circle. "
      + "It is composed of roughly hewn blocks of ice "
      + "but is still good at keeping its inhabitants warm. "
      + "It is pretty much solid. "
      + "\n");
   add_prop(OBJ_I_NO_GET, 1);
}
