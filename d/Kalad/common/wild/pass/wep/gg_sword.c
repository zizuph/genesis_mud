/* 
 * /d/Kalad/common/wild/pass/wep/gg_sword.c
 * Purpose    : An iron sword of goblin make
 * Located    : Used by the Red Hand goblins in the mountains
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("large");
   add_adj("iron");
   set_long("A roughly forged sword made of pig iron, apparently of "+
      "goblin make. A bloody hand clutching an eyeball decorates the sword's "+
      "pommel.\n");
   set_hit(21);
   set_pen(17);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_BLUDGEON);
   add_prop(OBJ_I_VALUE, 300);
   add_prop(OBJ_I_WEIGHT,7500);
   add_prop(OBJ_I_VOLUME,7500);
}
