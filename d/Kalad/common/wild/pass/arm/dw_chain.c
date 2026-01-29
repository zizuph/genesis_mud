/* 
 * /d/Kalad/common/wild/pass/arm/dw_chain.c
 * Purpose    : Adamantine chainmail of drow make
 * Located    : Used by drows in undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("chainmail");
   set_adj("adamantine");
   set_long("An extremely light and supple version of the already "+
      "unburdenable chainmail armor. Since it is fashioned from adamantine, it "+
      "is nearly as durable as standard plate armor, without its awkward "+
      "bulkiness.\n");
   set_ac(27);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,750);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
