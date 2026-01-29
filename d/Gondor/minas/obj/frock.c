/* Modified to remove unworn desc. - Gwyneth, 10/26/03 */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
  set_name("frock");
   add_name("dress");
    set_short("embroidered wool frock");
  set_adj("wool");
  set_adj("embroidered");
  set_pshort("embroidered wool frocks");
   set_long("A homespun wool dress, dyed a dark blue and " +
   "faded with wear. The frock is that of a common woman, " +
   "with rough embroidery along the hem of vines and birds. " +
   "Although the dress seems loose-fitting, the sleeves are " +
   "tailored for use in work, and is probably meant to be " +
   "tied by an apron.\n");
  set_default_armour(5,A_ROBE,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(40));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
