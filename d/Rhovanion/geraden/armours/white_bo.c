
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
set_short("pair of white boots");
set_pshort("pairs of white boots");
set_long("A pair of boots common to the Tallfellow warriors of "+
	"Esmirin.  They are made of leather and bleached white.\n");
set_adj("white");

set_default_armour(5, A_FEET, 0, 0);
}
