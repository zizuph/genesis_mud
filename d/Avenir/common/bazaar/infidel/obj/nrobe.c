// Robe for Nochipa
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_short("flowing white robe");
  set_name(({"robe"}));
  set_adj(({"flowing","soft","white"}));
  set_long ("This robe has many folds and creases, and it hangs "+
            "about the body like a shroud. The material is of fine "+
            "silk embroidered with golden threads at the hem and "+
            "sleeves.\n");
  set_ac (6);
  set_am(({ 1, 0, -1}));
  set_at (A_ROBE);
  add_prop(OBJ_I_VALUE, 1284);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 1000);   // It is small, after all...

}
