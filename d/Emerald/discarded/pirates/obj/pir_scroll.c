inherit "/std/object.c";

#include <stdproperties.h>
#include </sys/macros.h>
#include "defs.h"


void
create_object()
{
   set_name("scroll");
   set_short("scroll in a glass display case");
   set_long("There is information about the pirates guild on the scroll.\n");
   add_prop(OBJ_M_NO_GET,1);
}
