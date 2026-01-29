/*
green leather helmet from Esmirin
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
set_name("cap");
set_short("green cap");
set_long("This green leather cap is common to the small folk of Esmirin.  "+
     "It is dyed green, most likely to blend in with a forest "+
     "surrounding.\n\n");
set_adj("green");

set_default_armour(20,A_HEAD,0,0);
set_am(({1, -2, 1}));
}
