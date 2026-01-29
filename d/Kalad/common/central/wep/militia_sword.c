inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("polished longsword");
   add_name("longsword");
   add_name("sword");
   set_long("This sword has been polished to a brilliant shine. The image "+
      "of two crossed swords marks this as the standard issue sword for "+
      "the Kabal militia.\n");
   set_hit(29);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE, 450);
   add_prop(OBJ_I_WEIGHT, 8000);
   add_prop(OBJ_I_VOLUME, 3000);
}
