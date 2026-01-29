inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("silver platemail");
    add_name("platemail");
    add_name("mail");
    set_pname("platemails");
    set_short("silver platemail");
    set_pshort("silver platemails");
    set_long("This suit of platemail looks strong and well made. It has "+
      "a golden cross etched on the breastplate.\n");
    set_ac(40);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 650);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
}
