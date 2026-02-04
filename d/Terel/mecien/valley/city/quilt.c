inherit "/std/object";

#include "/sys/stdproperties.h";
#include <money.h>

create_object() {
   set_name("quilt");
   set_adj("beautiful");
   set_long(
"A beautiful quilt, woven of cotton with bits of satin. It depicts " +
"seven knights crowned with garlands. Above them a silvery star.\n"
);
   add_prop(OBJ_I_VALUE,400);    /* Value 40 cc*/
   
}
