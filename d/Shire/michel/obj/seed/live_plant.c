inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"

void remove_plant();

void
create_container()
{
   set_name("plant");
   set_short("leafy plant");
   set_adj("leafy");
   set_long("This is quite a leafy plant.\n");

   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(CONT_I_MAX_VOLUME, 2000);
   add_prop(CONT_I_MAX_WEIGHT, 2000);

   set_alarm(600.0,0.0,"remove_plant");


}

void
remove_plant()
{
   TO->remove_object();
}
