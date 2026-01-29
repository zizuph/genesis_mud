inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("loincloth");
   set_adj("white");
   set_adj("dirty");
   set_long("This is a simple piece of cloth made to " +
      "be tied around the groin to keep your genitals from " +
      "rattling excessively.  It is well-used and smells " +
      "slightly of genitals.\n");
   set_condition(7);
   set_ac(1);
   set_at(A_WAIST);
}
void
remove_broken() {
   write("Unbreakable");
}
