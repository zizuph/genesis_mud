#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"

inherit "/d/Kalad/common/noble/arm/piercing";
/* by Sarr */

void
create_piercing()
{
   set_name("pierce8");
   add_name("brilderisreallyaniceguy");
   set_long("Tongue pierced.\n");
   set_short("tongue");
}

void
enter_env(object to, object from)
{
   if (living(to))
   {
      to->add_subloc(SUBLOC, this_object());
      to->add_prop(KALAD_RING_TONGUE,1);
   }
   ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
   if (living(from))
   {
      from->remove_subloc(SUBLOC);
      from->remove_prop(KALAD_RING_TONGUE);
   }
   ::leave_env(from, to);
}
