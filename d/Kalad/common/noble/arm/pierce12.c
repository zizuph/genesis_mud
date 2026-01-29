#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"

inherit "/d/Kalad/common/noble/arm/piercing";
/* by Sarr */

void
create_piercing()
{
   set_name("pierce12");
   add_name("brilderisreallyaniceguy");
   set_long("Both nipples pierced.\n");
   set_short("nipples");
}

void
enter_env(object to, object from)
{
   if (living(to))
   {
      to->add_subloc(SUBLOC, this_object());
      to->add_prop(KALAD_RING_NIP_BOTH,1);
   }
   ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
   if (living(from))
   {
      from->remove_subloc(SUBLOC);
      from->remove_prop(KALAD_RING_NIP_BOTH);
   }
   ::leave_env(from, to);
}

