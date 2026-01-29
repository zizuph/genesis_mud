inherit "/d/Emerald/npc/guard"; 

#include "/d/Emerald/outpost1/defs.h";

void 
create_guard() 
{
    config_guard(95);
    set_name("sargent");
    add_adj("sargent"); 
    add_adj("outpost"); 
    set_short("outpost sargent"); 
    set_act_time(5);
    add_act("emote glares at you suspiciously.");
    add_act("emote sighs.");
    add_act("emote shifts his weight to one side.");
    set_cact_time(4);
    add_cact("emote fumes angrily.");
    add_cact("emote says: Die!.");
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "broadsword");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");
}