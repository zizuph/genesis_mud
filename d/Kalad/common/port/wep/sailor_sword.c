inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("cutlass");
    add_name("sword");
    set_adj("ornate");
    add_adj("steel");
    set_long("The weapon looks to be of an antiquated design yet seems "+
      "to have been just newly forged, for there are no visible nicks on the "+
      "blade. A symbol of a dark sun has been engraved upon the sword's "+
      "pommel.\n");
    set_hit(25);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VOLUME,6000);
}
