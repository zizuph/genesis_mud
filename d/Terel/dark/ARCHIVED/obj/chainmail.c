#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include <wa_types.h>

create_terel_armour(){
   set_name(({"chainmail","hauberk","chain","armor","armour"}));
   set_adj("black");
   set_short("black chainmail");
   set_long(
      "A glimmering black suit of chainmail. It is well crafted and very ornate.\n");
   set_ac(35);
   set_at(A_BODY);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 6000);
}
