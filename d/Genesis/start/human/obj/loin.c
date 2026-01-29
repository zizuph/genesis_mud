#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

void
create_armour()
{
    set_name("cloth");
    set_adj("smelly");
    add_adj("loin");
    set_long("This is a huge, raunchy loin cloth.\n");
    set_short("smelly loin cloth");
    set_pshort("smelly loin cloths");

    set_af(TO);
    set_default_armour(10, A_WAIST, ({-2,2,0}), 0);

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_VOLUME,2000);
}

mixed
wear(object what)
{
    if (!interactive(TP)) return 0; //Worn by a NPC

	if (TP->query_base_stat(SS_STR) > 180)
	{
	    write("The foul smell from the loin cloth is overwhelming.\n");
	    return 0;
	}

    TP->add_fatigue(-random(200)-10);
    return "You try to pull the huge cloth around your body, "+
    "you give up though, deciding it is just too large.\n";


}

mixed
remove(object what)
{
    return 0;
}
