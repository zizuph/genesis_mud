#include "defs.h"
inherit STD_UNDEAD;
inherit LIB_DIR + "locate";

void
create_monster() 
{
    ::create_monster();
    set_race_name("zombie");
    set_act_time(3);
    add_act("moan");
    add_act("emote shambles around.");
}

string
query_combat_file()
{ 
    return "/d/Raumdor/common/std/chumanoid.c"; 
}

void
notify_you_killed_me(object who)
{
    command("emote hisses in satisfaction as a fresh body falls before it.");
    command("emote moans: Your corpse isss miinnnneeee.");
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    command("emote quickly devours the remains of its victim, splatting " +
            "flood and flesh all around.");
}

void
do_die(object killer)
{
    command("emote falls to the ground, spewing black ooze out of " + 
        HIS(killer) + " mouth.");
    ::do_die(killer);
}
