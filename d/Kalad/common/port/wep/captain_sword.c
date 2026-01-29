inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("scimitar");
    add_name("sword");
    set_adj("great");
    add_adj("steel");
    set_long("An exquisitely-crafted steel-bladed scimitar. Its finely "+
      "honed blade is over five feet in length and its black leather "+
      "pommel is nearly a foot long. Engraved upon it is the image of a "+
      "dark sun.\n");
    set_hit(30);
    set_pen(21);
    set_hands(W_BOTH);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE, 700);
    add_prop(OBJ_I_WEIGHT,12000);
    add_prop(OBJ_I_VOLUME,12000);
}
