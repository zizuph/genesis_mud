#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/tyr/tyr.h"
#define NFN notify_fail

/*
 * Function name: create_armour
 * Description:   Creator.
 */
public void
create_armour()
{
    set_name("cloak");
    set_adj("hooded");
    add_adj("dark");
   set_short("dark hooded cloak");
    set_long("This is a large cloak that stretches the length of the body.  It is "
	+"so black that it looks like a living shadow.  There is a hood " 
    	+"on it as well that probably could be useful.\n");
   add_item(({"hood", "wide hood", }),"The hood will allow the "
   +"wearer to conceal their features when it is raised.\n");
   set_ac(2);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,  700);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);

}


