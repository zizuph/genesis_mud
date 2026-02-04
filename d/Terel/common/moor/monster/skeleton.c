
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_monster()
{
     string adj;
     
     ::create_monster();
     set_name("skeleton");
     adj = one_of_list(({"dusty", "scary", "deranged"}));
     set_adj(adj);
     set_short(adj+" skeleton");
     set_long(
        "This "+ adj +" skeleton was at rest until you disturbed it!\n "+
		"Now it's quite unhappy with you.\n");
    set_race_name("skeleton");
    set_stats(({75,75,75,30,30,100}));     
    add_prop(LIVE_I_UNDEAD, 1);
	add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);	
    set_aggressive(1);

}
