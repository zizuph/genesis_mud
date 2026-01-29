inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("gloves");
  set_pname("gloves");
   set_adj("black");
   add_adj("supple");
   set_short("black supple gloves");
   set_long("This is a pair of black gloves made of some material "
	+"that makes them incredibly soft and supple.  The feel very "
	+"thin, and probably would fit like a second skin.\n");
   set_ac(25);
    set_at(A_HANDS);
   set_wf(TO);
}

query_recover()
{
   return 1;
}


