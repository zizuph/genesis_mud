

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("armour");
    set_short("studded leather armour");
    set_adj(({"studded", "leather"}));
    set_long("A shirt of leather with steel studs lining up and down "+
             "the shirt. Light armour providing some protection.\n");

    set_default_armour(20, A_BODY, 0, 0);
    
    add_prop(OBJ_I_VALUE,            200);
    add_prop(OBJ_I_WEIGHT,          800);
}
