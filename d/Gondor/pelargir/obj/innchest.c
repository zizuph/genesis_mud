inherit "/std/container";

#include <stdproperties.h>

void
create_container()
{
   set_name("chest");
   set_short("small oak chest");
   set_pshort("small oak chests");
   set_long("The oak chest is here for anyone to use. " +
	"It is bolted to the floor.\n");
   add_prop(CONT_I_WEIGHT, 9000000);
   add_prop(CONT_I_MAX_WEIGHT,9140000);
   add_prop(CONT_I_VOLUME, 24000);
   add_prop(CONT_I_MAX_VOLUME, 48000);
   add_prop(CONT_I_RIGID, 1);
   add_prop(OBJ_M_NO_GET, "The chest is bolted to the floor!\n");
}
