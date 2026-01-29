inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("gauntlets");
   set_adj("plated");
   set_adj("steel");
   set_short("the steel plated gauntlets\n");
   set_long("This is a pair of soft leather gauntlets " +
      "with steel plates covering most of the hand and " +
      "chainmail linking the plates together over joints.\n");
   set_ac(16);
   set_am(({ 1, 1, -2 }));
   set_at(A_HANDS);
}
