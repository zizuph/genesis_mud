inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("short");
    add_adj("steel");
    set_long("A magnificent example of the work a true blacksmith can accomplish. "+
      "Everything about this sword is perfection! Its lovely blade looks "+
      "capable of slicing through armor with the greates of ease, and its "+
      "leather-covered pommel, with the image of a dark sun, provides its "+
      "wielder with an excellent grip.\n");
    set_hit(20);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,600);
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VOLUME,6000);
}
