/* 
 * /d/Kalad/common/wild/pass/arm/gk_armour.c
 * Purpose    : Full suit of iron plate armour
 * Located    : Used by the goblins in the caves
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("full suit of iron armour");
   add_name("suit");
   add_name("iron armour");
   add_name("armour");
   set_long("A complete suit of reinforced iron armour, consisting of "+
      "interlocking helmet, platemail, gauntlets and greaves. In stark contrast "+
      "to the stormy grey of the metal is the bright red symbol of a "+
      "bloody hand clutching a severed eyeball.\n");
   set_ac(30);
   set_at(A_HEAD | A_BODY | A_ARMS | A_LEGS);
   add_prop(OBJ_I_VALUE,1728);
   add_prop(OBJ_I_WEIGHT,37500);
   add_prop(OBJ_I_VOLUME,37500);
}
