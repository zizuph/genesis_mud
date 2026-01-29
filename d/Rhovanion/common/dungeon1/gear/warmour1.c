inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("armour");
   set_adj("chain");
   set_adj("plated");
   set_long("This suit of armour is comprised of chainmail covering " +
      "the chest, arms, and legs with plate mail covering " +
      "the arms and legs.  For relatively light weight metal armour " +
      "this looks like it affords good protection.\n");
   set_ac(40);
   set_am(({ 5, 0, -5 }));
   set_at(A_BODY | A_LEGS | A_ARMS );
}
