inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"
void
create_armour()

{
	set_name("bracers");
set_short("pair of bracers");
   set_long("They are green steel bracers with the embolem of "+
      "two crossed axes over a map of the world on each bracer.\n");
	set_adj("steel");
   add_adj("green");

   set_ac(30);
   set_am(({ 0, 2, -2}));
	set_at(A_ARMS);
   add_prop(OBJ_I_VALUE, 775);
}
