#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include <formulas.h>

create_terel_armour(){
 set_name("hat");
 set_adj("straw");
 set_short("yellow straw hat");
 set_long("This is a scruffy straw hat.\n");
 set_ac(2);
 set_at(A_HEAD);
 set_am(({0, -1, 1}));
 add_prop(OBJ_I_WEIGHT, 400);
 add_prop(OBJ_I_VOLUME, 400);
}
