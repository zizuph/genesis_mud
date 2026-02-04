#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <stdproperties.h>
#include <wa_types.h>

create_terel_armour(){
   set_name(({"mail", "chainmail", "chain mail", "armour", "armor"}));
   set_adj("steel");
   set_short("shiny steel chainmail");
   set_long("This is a standard armour.\n");
   set_ac(25);
   set_at(A_BODY);
   set_am(({0,0,0}));
    set_armour_size(MEDIUM);
}
