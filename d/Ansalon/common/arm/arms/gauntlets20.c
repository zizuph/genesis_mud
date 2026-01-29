inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
   set_name("gauntlets");
   set_pname("gauntlets");
   set_adj("iron");
   set_short("pair of iron gauntlets");
   set_pshort("pairs of iron gauntlets");
   set_long("This is a pair of rather heavy iron " +
      "gauntlets. Although somewhat battered, it looks " +
      "like it was made by dwarven craftsmen, and will thus " +
      "offer decent protection.\n");
   set_ac(20);
   set_at(A_ARMS);
   add_prop(OBJ_I_VOLUME, 500);
}
