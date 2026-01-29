/* Created by Lasayr 9/20/98 */
/* lasayr_sandals.c          */
/* Comments:                 */
/* ToDo:                     */

inherit "/std/armour.c";

inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Calia/domain.h"


void
create_armour()
{

set_name("sandals");
  set_adj(({"black","woven"}));
  set_short("pair of black woven sandals");
  set_pshort("pairs of black woven sandals");
  set_long("Several long strips of some sort of long " +
  "leafy plant, and various cuts of hide used to lend " +
  "strength, create this weave of knots and patterns. " +
  "Dyed to a dull tone of black, they hold a sense of " +
  "absence to them, and would easily not be noticed.\n");
  
  add_item(({"strips of long leafy plant","strips"}),
  "Long strips of some leafy plant have been tied and " +
  "teased into fashion.  A simple weave makes for a " +
  "light and encovering sandal.\n\n"); 
  
  add_item(({"cuts of hide","cuts"}),
  "Various cuts of hide have been used as simple " +
  "tie-ends for the sandals.  A knot here, and twist " +
  "here keeps the footwear snugly on the foot.\n\n");

  add_item(({"knots","patterns","weave"}),
  "A delectable delight of knots ranging from the " +
  "simple to the complex, the weave seems to be more " +
  "than just a pair of sandals.  But perhaps a key " +
  "to something if fathomed.\n\n");
 
  set_at(A_FEET);
  set_ac(2);
    
  set_keep(1);
  
  add_prop(OBJ_M_NO_BUY, "Oops. I should probably throw these away.");

}
