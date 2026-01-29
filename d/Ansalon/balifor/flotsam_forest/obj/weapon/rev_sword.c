/* created by Aridor 09/15/94 */

inherit "/std/weapon";

#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
set_name(({"longsword","_ansalon_flaming_sword_"}));
   set_adj("flaming");
   add_adj("two-handed");
   add_name("sword");
   set_short("flaming two-handed longsword");
   set_pshort("flaming two-handed longswords");
   set_long("This is a very peculiar sword indeed! Consisting " +
      "of only a hilt, the swords blade consists totally of " +
      "a deep red flame!\n");
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC,({10, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon has a simple enchantment on it, that " +
            "being a blade of magical flame. Apart from being as " +
            "effective as a bastard sword in battle, in sheds a " +
            "permanent light for the wielder.\n",5}));
   
   
   add_prop(OBJ_I_LIGHT,1);
   
   set_hit(26);
   set_pen(22);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_BOTH);
   
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 6000);
   
}

