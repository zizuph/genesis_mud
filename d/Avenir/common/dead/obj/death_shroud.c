
// file name: /d/Avenir/common/dead/obj/death_shroud.c
// creator(s): Lilith, June 2021
// purpose:  for the crypt residents
// note: 
// updates: 

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("shroud");
  add_name("robe");
  set_short("death shroud");
  add_adj(({"translucent", "death", "white", "webcloth"}));
  set_long("This is a death shroud used to wrap the bodies "
        +" of the dead in preparation for burial. "
        +"It is made of a very thin, translucent webcloth.\n");
  set_ac (10 +random(10));
  set_at (A_ROBE);
  add_prop(OBJ_I_VALUE, 20);
  add_prop(OBJ_I_VOLUME, 50);
  add_prop(OBJ_I_WEIGHT, 10);
}

