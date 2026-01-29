inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_armour()
{
    set_name("mail");
    set_adj("scale");
    add_adj("leather");
    set_short("leather scale mail");
    set_long("This is the armour worn by the mercs of" +
        " Altaruk. Its made from thick leather covered" +
        " with erdlu scales. Most of the mercs have modified" +
        " their armour for their personal use. Its drenched" +
        " with the sweat of its former owner. \n");

    set_ac(35);
    set_am(({ -6, 4, 2}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
