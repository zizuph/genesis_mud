inherit "/d/Terel/mortricia/camp/house/demon.c";

/* Added LIVE_I_UNDEAD property, after bug report on that.
  skeletons should be undead when you think about it;]
     /Udana 03/2006
  */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BSN(xxx)        break_string(xxx + "\n", 70)
#define ADJS            ({"dusty", "scary", "deranged"})


void
create_monster()
{
     string adj;
     
     ::create_monster();
     set_name("skeleton");
     adj = ADJS[random(sizeof(ADJS))];
     set_adj(adj);
     set_short(adj+" skeleton");
     set_long(BSN(
        "This "+adj+" skeleton was at rest until you disturbed it!  Now it's" +
	" quite unhappy with you."
        ));
    set_race_name("skeleton");
    set_stats(({75,75,75,30,30,100}));     
    set_gender(2);
    add_prop(LIVE_I_UNDEAD, 15);
    set_aggressive(1);
}
