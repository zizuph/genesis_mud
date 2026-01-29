
/* Basic armour file to be edited for use 
Geraden 941014
green hunting boots from Esmirin.
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
set_name("boots", "pair of boots");
set_pname("pairs of boots");
set_short("pair of green boots");
set_pshort("pairs of green boots");
set_long("These boots are common to the small folk of "+
     "Esmirin.  Like all such armours, they are dyed green to blend "+
     "in with the forest surroundings.\n\n");
set_adj("green");

set_default_armour(5, A_FEET, 0, 0);
}
