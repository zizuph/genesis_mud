inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("silk shirt");
   add_name("shirt");
   set_adj("white");
   set_adj("billowy");
   set_long("This is a beautiful white silk shirt with " +
      "laces in the front keeping the low v-cut of the shirt " +
      "relatively tied.  The shirt is large in the arms especially allowing freedom of movement for its wearer " +
      "during perhaps...  a swordfight!  It appears to be clean, too.\n");
   set_ac(1);
   set_am(({ 0, 0, 0 }));
   set_at(A_BODY | A_ARMS);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME,  50);
   add_prop(OBJ_I_VALUE, 500);
}
