inherit "/std/armour";
#include "/sys/stdproperties.h"
#include <formulas.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour(){
 set_name("jumpsuit");
 set_adj("green");
 set_short("green workers jumpsuit");
 set_long("This is a green jumpsuit.\n");
 set_ac(16);
 set_at(A_ROBE);
 set_am(({5,0,-5}));
 add_prop(OBJ_I_WEIGHT, 5000);
 add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
}
