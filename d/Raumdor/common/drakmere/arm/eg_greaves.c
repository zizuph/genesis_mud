/*     Created by:      Antharanos 
 *     Location:        
 *     Modified:        Toby, 970919 (fixed pluralis form plus random ac)
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
   set_adj("black");
   add_adj("silver-striped");
   set_short("pair of black silver-striped greaves");
   set_pshort("pairs of black silver-striped greaves");
   set_long("This set of greaves are made of strong, black painted "+
   "steel. They are decorated with silver stripes and trimmings.\n");
   set_ac(40);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 480);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 1400+random(200));
}
