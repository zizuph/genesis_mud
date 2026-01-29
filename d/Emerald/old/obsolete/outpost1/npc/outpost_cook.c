inherit "/d/Emerald/npc/guard"; 

#include "/d/Emerald/outpost1/defs.h";
void 
create_guard() 
{
    config_guard(60); 
    add_adj("outpost");
    set_name("cook"); 
    set_short("outpost cook");
    set_act_time(5);
    add_act("says: I need to get out of here, this place drives me nuts.");
    set_cact_time(3);
    add_cact("emote shouts: I'm going to chop you up and feed you to the dogs fool!.");
    add_cact("emote shouts: Guards! Help!"); 
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "cleaver");
}
