
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
set_name("brigandine");
set_short("white brigandine armour");
set_long("This is a brigandine armour worn by the Tallfellow warriors "+
	"of Esmirin.  It is bleached pure white.\n");
set_adj("white");

set_default_armour(35, A_BODY,0,0);
set_am(({1,1,-2}));
}
