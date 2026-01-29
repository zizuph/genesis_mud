inherit "/d/Emerald/npc/guard"; 

#include "/d/Emerald/outpost1/defs.h";
void 
create_guard() 
{
    config_guard(120);
    set_name("captain"); 
    add_adj("outpost"); 
    set_short("outpost captain"); 
    set_act_time(5);
    add_act("emote drums his fingers on the desk.");
    add_act("says: We must figure out our next move.");
    add_act("emote scratches his chin.");
    set_cact_time(4);
    add_cact("emote sneers at you.");
    add_cact("emote says: I'm going to hang your entrails on the gates!.");


}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "magic_sabre");
    add_equipment(OUTPOST_ARM_DIR + "plate");
    add_equipment(OUTPOST_ARM_DIR + "shield");
}