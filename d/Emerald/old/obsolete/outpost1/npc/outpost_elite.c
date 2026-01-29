inherit  "/d/Emerald/npc/guard"; 

#include "/d/Emerald/outpost1/defs.h";


static string *patrol_path = ({ });

void 
create_guard() 
{
    config_guard(80); 
    set_name("elite guard");
    add_name("elite");
    add_adj("outpost"); 
    set_short("elite outpost guard");
    set_act_time(5);
    add_act("emote peers around.");
    add_act("emote coughs.");
    set_cact_time(4);
    add_cact("emote shouts: Taste steel you foolish bastard!.");
    add_cact("emote swears at you."); 
 
    set_monster_home(NPC_HANDLER);
    set_random_move(1 + random(1));
    set_restrain_path(OUTPOST1_DIR);

}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "mace");
    add_equipment(OUTPOST_ARM_DIR + "chainmail");
    add_equipment(OUTPOST_ARM_DIR + "shield");
}