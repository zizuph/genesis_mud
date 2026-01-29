#include "defs.h"
inherit "/d/Raumdor/common/std/undead_std.c";
//inherit "/std/combat/unarmed";

void
create_monster() 
{
    ::create_monster();
    set_race_name("zombie");
    set_act_time(3);
    add_act("moan");
    add_act("emote shambles around.");
    //set_cact_time(3);
    /*
    set_attack_unarmed(0, 35, 35, W_IMPALE, 10, "bite");
    set_attack_unarmed(1, 25, 30, W_SLASH, 45, "left hand");
    set_attack_unarmed(2, 25, 30, W_SLASH, 45, "right hand");
    set_hitloc_unarmed(0,10,15,"head");
    set_hitloc_unarmed(1,10,10,"left arm");
    set_hitloc_unarmed(2,10,10,"right arm");
    set_hitloc_unarmed(3,20,45,"body");
    set_hitloc_unarmed(4,10,20,"legs");
    */
}

string
query_combat_file()
{ 
    return "/d/Raumdor/common/std/chumanoid.c"; 
}

void
notify_you_killed_me(object who)
{
    foreach (object ob: FILTER_LIVE(AINV(E(TO))))
    {
        if (ob->query_name() == "Chogaros")
        {
            if (ob->query_is_illusion() == 0)
            {
                ob->notify_you_killed_me(who);
                return;
            }
        }
    }
}

void
do_die(object killer)
{
    command("emote falls to the ground, spewing black ooze out of " + 
        HIS(killer) + " mouth.");
    ::do_die(killer);
}
