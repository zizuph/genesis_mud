inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("helmet");
   set_adj("chain");
   set_adj("plated");
   set_adj("horned");
   set_long("This chainmail helmet is covered with sections of " +
      "ornately shaped, dark steel plates.  Odd horns protrude from " +
      "the helmet in a symmetrical pattern where the dark plates " +
      "do not meet.  It is a bit heavy with all its accoutrements, " +
      "but looks like it's pretty protective.  Most of the " +
      "face is covered with metal plates that curve ornately " +
      "around to cover all but the face and eyes.\n");
   set_ac(25);
   set_am(({ 0, 3, -3 }));
   set_at(A_HEAD);
}
