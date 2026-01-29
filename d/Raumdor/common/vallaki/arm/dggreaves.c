/*     Created by:      Antharanos
 *     Location:        
 *     Modified:        Toby, 970919 (fixed pluralis form)
 */

inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   ::create_armour();
   set_name("pair of greaves");
   add_name("greaves");
   set_adj("chain");
   set_short("pair of chain greaves");
   set_pshort("pairs of chain greaves");
   set_long("This set of chain greaves looks well made and protective.\n");
   set_ac(30);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 330);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 1400+random(200));
}
