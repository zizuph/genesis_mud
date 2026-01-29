inherit "/d/Faerun/std/obj/base_wand";

#include "/d/Faerun/std/obj/wand.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
create_wand()
{
    set_name("wand");
    set_adj("strength");

    add_name("rod");
    add_adj("iron");

    set_short("iron rod");
    set_long("This is an iron rod, which looks rather uninteresting.\n"+
	    "However, when you get closer you detect a faint pulsating\n"+
	    "forcefield around it.\n");

    set_wand_type(WAND_STAT);
//  set_wand_effect(({SS_STR,20,10}));
    set_effect_stat(SS_WIS);
    set_effect_change(20);
    set_effect_time(10);
    set_charges(6);
    set_charge_value(100);
}
