inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name(({"spear","_flotsam_c_shell_"}));
   set_adj("dargonesti");
   set_short("dargonesti spear");
   set_pshort("dargonesti spears");
   set_long("This deadly one-handed barbed spear is often used by " +
      "the sea-elves to hunt and slay the great sharks that plague " +
      "the Bloodsea. A master of weapons such as these could wield " +
      "two without problems. \n");
   set_default_weapon(35,25,W_POLEARM,W_IMPALE,W_ANYH);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 2500);
}
