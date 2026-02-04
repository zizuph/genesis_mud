inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
     set_name("magnesium");
     add_name(({"ribbon", "_mag_ribbon"}));
	 set_adj(({"metal", "magnesium"}));
     set_short("metal ribbon");
     set_long("A thin metal ribbon that looks like magnesium.\n");

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);
     add_prop("is_reactive", 1);
}
     
