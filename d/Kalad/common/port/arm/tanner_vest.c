inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("vest");
    set_adj("large");
    add_adj("tanned");
    set_long("A nicely tanned leather vest. Sewn onto it are the "+
      "following words:\n"+
      "Hand-made by Telbruin the Tanner.\n");
    set_ac(5);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,60);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,5000);
}
