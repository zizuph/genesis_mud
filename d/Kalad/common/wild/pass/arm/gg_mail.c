/* 
 * /d/Kalad/common/wild/pass/arm/gg_mail.c
 * Purpose    : Old iron mail
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
   set_name("armour");
   set_adj("iron");
   add_adj("mail");
   set_long("A fairly decent suit of armour, made out of roughly forged "+
      "iron. It looks to be of goblin design. A bloody hand clutching an "+
      "eyeball decorates the front.\n");
   set_ac(21);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,450);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
