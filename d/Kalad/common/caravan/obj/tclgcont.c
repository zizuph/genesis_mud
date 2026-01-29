inherit "/std/container";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
/* by Antharanos */
void
create_container()
{
    set_name("container");
    set_adj("glass");
    set_long("A rectangular glass container that has been placed in the "+
      "center of this room. Its base is made out of solid metal. You can "+
      "see the contents of the container through the glass.\n");
    add_prop(CONT_I_WEIGHT,150000);
    add_prop(CONT_I_MAX_WEIGHT,200000);
    add_prop(CONT_I_VOLUME,75000);
    add_prop(CONT_I_MAX_VOLUME,125000);
    add_prop(OBJ_I_VALUE,1200);
    set_alarm(1.0,0.0,"make_book");
}
make_book()
{
    object book;
    int n;
    seteuid(getuid(TO));
    for(n=0;n < 1;n++)
    {
	book = clone_object("/d/Kalad/common/caravan/obj/tcbook1");
	book -> move(TO);
    }
}
