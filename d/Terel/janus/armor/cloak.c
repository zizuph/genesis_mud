#include "defs.h"
inherit ARMOUR;
#include <formulas.h>
#include "/d/Terel/common/terel_std_rec.h"
#include <stdproperties.h>

create_armour(){
 set_name("cloak");
 set_adj("mithril");
 set_short("mithril-colored cloak");
 set_long("This is a mithril-colored cloak of a human make.\n");
 set_good_ac(25);
 set_at(A_ROBE);
 set_am(({0, 0, 0}));
 add_prop(OBJ_I_WEIGHT, 2000);
 add_prop(OBJ_I_VOLUME, 5000);
}
