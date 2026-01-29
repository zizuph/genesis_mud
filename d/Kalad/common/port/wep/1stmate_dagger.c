inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("sharp");
    add_adj("steel");
    set_long("A finely-honed dagger with the blade made from the shiniest "+
      "steel you've ever seen. Upon the hilt of the dagger is engraved an image "+
      "of a dark sun.\n");
    set_hit(12);
    set_pen(10);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
}
