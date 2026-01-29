/*     Created by:      Antharanos
 *     Location:        
 *     Modified:        Toby, 970919 (fixed pluralform)
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
   set_adj("plate");
   set_short("pair of plate greaves");
   set_pshort("pairs of plate greaves");
   set_long("This set of plate greaves looks well made and protective. "+
   "They glimmer strangely.\n");
   set_ac(40);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 530);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 1400+random(200));
}
