inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("pants");
    add_name("tanned_leather_pants");
    set_adj("tanned");
    add_adj("leather");
    set_pshort("tanned leather pants");
    set_long("A nicely tanned pair of leather pants. Sewn onto it are the "+
      "following words:\n"+
      "Hand-made by Telbruin the Tanner.\n");
    set_ac(5);
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE,48);
    add_prop(OBJ_I_VOLUME,7500);
    add_prop(OBJ_I_WEIGHT,7500);
}
