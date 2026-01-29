#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Cirath/common/defs.h"

void
create_armour()
{
    set_name("cloak");
    set_adj("red");
   add_adj("large");
   set_short("large red cloak");
   set_long("A large red cloak that hangs down to the backs of "
	+"the knees, this cloak provides some protection, as "
	+"well as still allowing the wearer to be mobile.\n");
   set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,  700);
    add_prop(OBJ_I_WEIGHT, 1200);

}


