inherit "/std/scroll";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
void
create_scroll()
{
    set_name("book");
    set_adj("black");
    add_adj("leather");
    set_long("A dusty old tome, on the spine you can make out the title. "+
      "It is labeled 'Observations on Thanar'.\n");
    add_prop(OBJ_I_VALUE, 600);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    set_file("/d/Kalad/common/caravan/obj/tcbook1");
}
