/*
green leather helmet from Esmirin
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
set_name("helmet");
set_short("white helmet");
set_long("This is a white helmet worn by the Tallfellow warriors of "+
	"Esmirin. It is bleached white to match the rest of their armours.\n");
set_adj("white");

set_default_armour(25, A_HEAD,0,0);
set_am(({1,1,-2}));
}
