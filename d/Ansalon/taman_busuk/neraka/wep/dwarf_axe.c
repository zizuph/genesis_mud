inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("axe");
   add_adj("one-handed");
   add_adj("steel");
   set_short("one-handed steel axe");
   set_long("Upon this polished wooden handle, there sits a heavy, steel "+
   "axe head sharpened to perfection. It looks like a deadly weapon.\n");
   set_hit(25);
   set_pen(31);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE,732);
   add_prop(OBJ_I_VOLUME, 3600);
   add_prop(OBJ_I_WEIGHT, 4700);
}
