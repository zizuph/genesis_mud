#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"

inherit "/d/Kalad/common/noble/arm/piercing";
/* by Sarr */

void
create_piercing()
{
   set_name("pierce11");
   add_name("brilderisreallyaniceguy");
   set_long("Right nipple pierced.\n");
   set_short("right nipple");
}

void
enter_env(object to, object from)
{
   if (living(to))
   {
      to->add_subloc(SUBLOC, this_object());
      to->add_prop(KALAD_RING_NIP_RIGHT,1);
   }
   ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
   if (living(from))
   {
      from->remove_subloc(SUBLOC);
      from->remove_prop(KALAD_RING_NIP_RIGHT);
   }
   ::leave_env(from, to);
}

