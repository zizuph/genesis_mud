
/* Basic armour file to be edited for use 
Geraden 941014
leather armour from Esmirin
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
set_name("leather armour");
set_short("green leather armour");
set_long("This is a leather armour common to the small folk of "+
     "Esmirin.  It is dyed green, most likely to blen with a forest "+
     "surrounding.\n\n");
set_adj("green");

set_default_armour(30,A_BODY,0,0);
set_am(({1, -2, 1}));
}
