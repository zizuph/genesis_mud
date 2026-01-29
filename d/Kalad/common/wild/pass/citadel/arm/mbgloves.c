inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("studded");
    add_adj("leather");
    add_name("pair of studded leather gloves");
    add_name("pair of gloves");
    add_name("pair");
    set_pname("gloves");
    set_pshort("pair of studded leather gloves");
    set_short("pair of studded leather gloves");
    set_long("A tough-looking pair of leather gloves, covered with metal "+
      "studs for added protection.\n");
    set_ac(10);
    set_at(A_HANDS);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 600);
}
