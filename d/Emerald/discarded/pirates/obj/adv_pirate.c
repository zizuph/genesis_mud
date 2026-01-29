inherit "/std/object";

#include "defs.h"

#define LOST_EYE_SUBLOC "_lost_eye"

void
create_object()
{
   set_short(0);
set_name("ADV_PIRATE");
   set_no_show();
   
   add_prop(OBJ_M_NO_DROP,1);
   add_prop(OBJ_M_NO_GIVE,1);
   
   seteuid(getuid());
}
