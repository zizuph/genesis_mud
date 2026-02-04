#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include <formulas.h>

create_terel_armour(){
 set_name("boots");
 set_adj("black","rubber");
 set_short("black rubber boots");
 set_long("This is a pair of black rubber boots.\n");
 set_ac(4);
 set_at(A_FEET);
 set_am(({1, 0, -1}));
 add_prop(OBJ_I_WEIGHT, 4000);
 add_prop(OBJ_I_VOLUME, 4000);
}
