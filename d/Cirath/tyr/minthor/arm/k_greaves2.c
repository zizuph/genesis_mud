inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("greaves");
   set_adj("steel");
   add_adj("plate");
    set_short("steel plate greaves");
   set_long("These greaves are a part of a suit of steel plate mail. "
	+"They have intricate damasked designs on them, and have been "
	+"designed to be incredibly light. Steel is extremely rare in "
	+"Athas, so these must be worth a fortune there.  When worn "
	+"they make you feel stronger.\n");
    set_ac(35);
   set_at(A_LEGS);
   set_wf(TO);
}
query_recover()
{
   return 1;
}




