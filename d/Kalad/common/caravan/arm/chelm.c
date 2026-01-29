#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("helm");
    set_adj("great");
    set_long("This helm protects all parts of the wearer's head, insuring "+
      "that little harm will come to him, or her. You notice the golden "+
      "camel engraved at the front of the helm, indicating that it belongs "+
      "to the captain of the city guard.\n");
    set_ac(28);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 840);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_WEIGHT, 3000);
}
