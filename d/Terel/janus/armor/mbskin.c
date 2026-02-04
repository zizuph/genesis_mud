inherit "/std/armour";
#include "/sys/stdproperties.h"
#include <formulas.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour(){
 set_name("bearskin");
 set_adj("brown");
 set_short("large brown bearskin");
 set_long("This is a brown bearskin. Taken from a recently killed bear. \n"+
          "From the markings on the skin you see that it is taken from a \n"+
          "large male.\n");
 set_ac(5);
 set_at(A_ROBE);
 set_am(({-1, 0, 1}));
 add_prop(OBJ_I_WEIGHT, 8000);
 add_prop(OBJ_I_VOLUME, 8000);
}



