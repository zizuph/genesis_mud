inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

create_armour()
{
    set_name("shirt");
    set_short("frilly white shirt");
    set_long("An ordinary white shirt with puffy sleeves, " +
      "and lace cuffs.\n"); 
    set_adj(({"frilly","white"}));
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 200);
}
