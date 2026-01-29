inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("cloak");
    set_ac(6);
    set_at(A_ROBE);
    set_adj("golden-trimmed");
    set_short("golden-trimmed cloak");
    set_long("This is a fine golden-edged cloak, worn by the elite " +
      "guards of Kalaman.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
}


