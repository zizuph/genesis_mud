inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "defs.h"

void
create_weapon()
{
    set_name("axe");
    set_adj("mithril");
    add_adj("razor-edged");
    set_short("mithril razor-edged axe");
    set_long("This axe is etched in gold runes, and its mithril "
      +"head is sharp enough to shave with. The haft is crafted "
      +"from what looks to be a rib from a giant. Worn leather "
      +"wrappings cover the end of the rib and form it into what "
      +"appears to be a well used grip. This is truly a magnificent "
      +"weapon.\n");
   set_hit(40);
    set_pen(46);
    set_wt(W_AXE);
    set_dt(W_SLASH);
     set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
   add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 4000);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
}

