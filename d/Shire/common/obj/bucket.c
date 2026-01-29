inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"


void
create_container()
{
   set_name("bucket");
   set_adj("wooden");
   set_short("wooden bucket");
   set_long("This is a wooden bucket, probably used to hold things.\n");

   add_prop(CONT_I_WEIGHT, 130);
   add_prop(CONT_I_VOLUME, 500);
   add_prop(CONT_I_MAX_WEIGHT, 18000);
   add_prop(CONT_I_MAX_VOLUME, 10000);

   add_prop(OBJ_I_VALUE, 8);

}
