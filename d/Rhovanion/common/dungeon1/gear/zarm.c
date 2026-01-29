inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("arm");
   set_adj(({"giant","rotted","zombie"}));
   set_short("giant, rotted zombie arm");
   set_pshort("giant, rotted zombie arms");
   set_long("This horrid smelling right limb seems to " +
      "have been ripped from its socket and might possibly " +
      "be useful as a club if its wielder isn't opposed to " +
      "wielding rotting, zombie limbs.\n");
   set_hit(15);
   set_pen(30);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
}
