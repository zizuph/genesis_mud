inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("ring");
   set_adj("ornate");
   set_long("This is a silver ring made of a thin band of silver " +
      "twisted over and over in a unique pattern.  It is quite " +
      "nice and probably worth a bit.\n");
   set_ac(0);
   set_am(({ 0, 0, 0 }));
   set_at(A_ANY_FINGER);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 175);
}
