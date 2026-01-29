inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name(ONE_OF_LIST(({"leggings","pants","greaves"})));
   set_adj(ONE_OF_LIST(({"leather","metal-scale","wooden"})));
   set_adj(ONE_OF_LIST(({"hard","light","heavy"})));
   set_long("These are Fantastic!\n");
   set_ac(9);
   set_am(({ 0, 0, 0 }));
   set_at(A_LEGS);
}
