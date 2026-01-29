inherit  "/d/Emerald/npc/guard"; 

#include "/d/Emerald/outpost1/defs.h";


static string *patrol_path = ({ });

void 
create_guard() 
{
    config_guard(70); 
    set_name("guard");
    add_adj("outpost"); 
    set_short("outpost guard");
    set_act_time(5);
    add_act("emote peers around nervously.");
    add_act("emote coughs.");
    add_act("emote says: I miss my family.");
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
    add_equipment(OUTPOST_WEP_DIR + "spear");
    add_equipment(OUTPOST_ARM_DIR + "ringmail");
}