inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"

void
create_armour()

{
        set_name("helmet");
   set_short("light steel helmet");
 set_long("It is a light steel helmet that is extremely light. "+
          "It is also very durable, not to mention comfortable. "+
          "On the inside is a small label that reads: Cove's finest.\n");
        set_adj(({"light", "steel"}));
   add_adj("strong");
   add_prop(OBJ_I_VALUE,300);

   set_ac(9);
        set_am(({ 0, 0, 0}));
        set_at(A_HEAD);
}
