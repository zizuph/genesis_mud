inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("ornate");
    add_adj("bejewelled");
    set_long("A surprisingly light dagger, whose pommel is encrusted with "+
      "a number of many-faceted jewels and precious gems.\n");
    set_hit(11);
    set_pen(11);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,900);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,750);
}
