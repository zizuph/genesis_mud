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
   set_name("pair of boots");
   add_name("boots");
   set_adj("black");
   add_adj("shiny");
   add_adj("strong");
   set_short("pair of black shiny boots");
   set_pshort("pairs of black shiny boots");
   set_long("These are a pair of strong, shiny, black leather boots. "+
   "They look like they are built to last a long time.\n");
   set_ac(20);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE, 240);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1500);
}
