#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>

inherit "/std/container";

create_container() {
   set_short("nice @@warm");
   set_name("box");
   add_name("kender_box");
   set_adj("nice");
   set_long("This is a really nice @@warm@@. It is rather "
      + "small but well made. The interior is coated with "
      + "a flame-retardant material. Such a box would be a "
      + "very prized possession for a Kender. "
      + "Beware if you see one. He might try to 'borrow' it from you.\n");
   
   add_prop(CONT_I_VOLUME,50);
   add_prop(CONT_I_WEIGHT,50);
   add_prop(CONT_I_MAX_VOLUME,80);
   add_prop(CONT_I_MAX_WEIGHT,80);
   add_prop(CONT_I_RIGID,1);
}

string warm() {
   if (P("ember",TO)) return "and very warm box";
   return "box";
}
