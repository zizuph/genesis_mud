inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name(({"_prot_spell_ingrl_","rock"}));
   add_name("grey rock");
   set_short("grey rock");
   set_long("An unremarkable looking rock. It probably fell loose from "+
      "one of the mountains.\n");
   add_prop(OBJ_I_VALUE,10);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_WEIGHT,500);
}
