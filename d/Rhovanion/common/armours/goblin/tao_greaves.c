/* Greaves  35 AC           */
/* Apr-18-2001 Dimitry@Igor */

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

void
create_armour()
{
  set_name("greaves");
  set_short("pair of rusty elven greaves");
  set_pshort("rusty elven greaves");
  set_adj(({"rusty","elven"}));
  
  set_long("These are old and rusty elven greaves which are made of light silvery "+    
           "metal. The greaves are quite light and dirty. It is a part " +              
           "of the equipment of some unlucky elven warrior who has dared " +            
           "to mess with mighty goblin warriors.\n");                                 

  set_ac(35);
  set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE,  6000);
}
