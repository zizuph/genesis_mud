/* created by Aridor 06/19/93 */

#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

void
create_krynn_monster()
{
    set_name("gob");
    set_race_name("goblin");
    set_adj("well-dressed");
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_short("well-dressed goblin");
    set_long("This short goblin is strangely well dressed for a goblin. "+
    "perhaps its because of its merchant status.\n");
    set_stats(({100,100,100,50,50,80}));
    set_skill(SS_DEFENCE,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_act_time(8);
    add_act("say You buy?");
    add_act("say You buy or leave!");
    add_act("say What you got for me?");
    add_act("say Me busy, you buy or go away.");
    add_act("say Hrmph, you don't look like you got good warzes!");
}

