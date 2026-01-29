inherit "/std/armour";
#include "/sys/wa_types.h"

#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("leather armour");
   set_short("leather armour");
   set_long("This is a full suit of leather armour offering limited protection " +
      "to most parts of your body.  Though it isn't very strong, its light weight " +
      "makes up for its lack of protection.  It looks pretty well-used.\n");
   set_ac(10);
   set_am(({ -2, -1, 3 }));
   set_at(A_BODY | A_LEGS| A_ARMS);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 3000);
}
