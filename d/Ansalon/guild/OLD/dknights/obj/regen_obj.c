inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

object deathKnight;

void
create_object()
{
   set_name(REGEN_OBJ);

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);

   set_no_show();
}

void
do_regen()
{
   deathKnight->heal_hp(200);
   deathKnight->add_fatigue(20);

}

void
enter_env(object to, object from)
{
   ::enter_env(to, from);
  
   deathKnight = to;
   set_alarm(0.0,50.0,&do_regen());
}
