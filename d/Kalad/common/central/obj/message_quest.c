/* a message to be found on a pigeon in CENTRAL(plaza/monument) */
/* made by korat */

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Kalad/defs.h"

void
create_scroll()
{
   set_name("message");
   set_adj("strange");
   set_long("A small piece of paper with some text written down on it.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 20);
   set_file("/d/Kalad/common/central/obj/message_quest");
}

