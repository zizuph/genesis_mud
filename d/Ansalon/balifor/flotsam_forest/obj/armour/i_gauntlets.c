inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 20

void
create_armour()
{
   set_name("gauntlets");
   set_pname("gauntlets");
    add_name("armour");
    add_pname("armours");
   
   set_adj("iron");
   
   set_short("pair of iron gauntlets");
   set_pshort("pairs of iron gauntlets");
   set_long("This is a pair of rather heavy iron " +
      "gauntlets. Although somewhat battered, it looks " +
      "like it was made by dwarven craftsmen, and will thus " +
      "offer decent protection.\n");
   
   set_ac(ARMOUR_CLASS);
   set_at(A_ARMS);
   
   add_prop(OBJ_I_WEIGHT, 1500);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
