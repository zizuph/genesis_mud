#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <stdproperties.h>
#include <formulas.h>

create_terel_armour(){
 set_name("bearskin");
 set_adj("brown","small");
 set_short("brown bearskin");
 set_long("This is a small brown bearskin. Taken from a recently killed \n"+
          "bear. From the size of the skin you guess that it is taken from \n"+
          "a bearcub.");
 set_ac(1);
 set_at(A_ROBE);
 set_am(({0,-1, 1}));
 add_prop(OBJ_I_WEIGHT, 2000);
 add_prop(OBJ_I_VOLUME, 2000);
 set_armour_size(SMALL);
}



