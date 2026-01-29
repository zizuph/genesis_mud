inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name(({"cap","leather cap","helmet","leather helmet","orc helmet"}));
  set_short("orkish leather cap");
  set_pshort("orkish leather caps");
  set_adj("orkish");
  set_adj("ringmailed");
  set_adj("leather");
  set_long(break_string("A hard leather cap, enforced with metal rings sewn to it. The rough fabrication betrays the orkish origin of the armour, "+
    "but in spite of its crude looks, it is rather effective. \n",70));
  set_default_armour(13,A_HEAD,({-2, 3,-1}),0);
}
