#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "monster_base";

#include <stdproperties.h>
#include <ss_types.h>

void
create_traveller_monster()
{
    set_name("guard");
    set_race_name("human");
    set_long("This massive guard doesnt want just anybody\n"
	    + " climbing the stairs.\n");
    set_short("guard");
    add_adj("massive");
    
    set_stats(({ 130, 130, 130, 80, 80, 130 }));
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_NO_ATTACK, "A ring on the guard's left hand glows " +
        "with a strange, green aura.\nYou sense a magical force protecting " +
        "him.\n");
    
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);
     
    add_act("emote studies you.");
    add_act("emote stares at you.");
    add_act("emote smiles charmingly.");
        
    set_act_time(20);
}
