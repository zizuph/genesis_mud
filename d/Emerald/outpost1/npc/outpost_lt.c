inherit "/d/Emerald/npc/guard"; 

#include "../defs.h"

void 
create_guard() 
{
    config_guard(90); 
    add_adj("outpost");
    set_name("leiutenant"); 
    set_short("outpost leiutenant"); 
    set_act_time(5);
    add_act("emote glances at you.");
    add_act("emote frowns.");
    add_act("emote says: The men are tired, I wonder what our next move will be.");
    set_cact_time(4);
    add_cact("emote shouts: For Telberin!");
    add_cact("emote says: I'm going to rip you apart you fool!");


}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "mil_longsword");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");
}
