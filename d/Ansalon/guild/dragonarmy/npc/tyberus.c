/* Based on aurak_leader by Aridor */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit "/d/Ansalon/guild/dragonarmy/npc/da_monster";
inherit AUTO_TEAM

void
create_da_monster()
{
    set_name("tyberus");
    set_living_name("tyberus");
    set_adj(({"dark-eyed", "muscular"}));

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 70);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(CONT_I_HEIGHT, 165);
    set_all_hitloc_unarmed(20);

    set_color("green");
    set_dragonarmy_rank(3, 4);

    set_act_time(3);
    add_act("emote sneers at you with contempt.");
    add_act("emote barks: Mess with the Green, and you will die by my blade!");
    add_act("emote adjusts his armour to fit perfectly.");

    set_cact_time(10);
    add_cact("emote yells: May Takhisis feast upon your soul!");
    add_cact("emote laughs: You dare oppose the Green Dragonarmy?");
    add_cact("emote looks for an opening to take advantage of.");

    set_pick_up_team(({"aurak"}));
    set_max_team_size_auto_join(3);
}

arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());

    if(random(2))
    {
        ob = clone_object("/d/Krynn/solamn/splains/obj/bbattleaxe");
    }
    else
    {
        ob = clone_object("/d/Krynn/solamn/splains/obj/bclaymore");
    }
    ob->move(TO, 1);

    if(random(3))
    {
        ob = clone_object("/d/Ansalon/balifor/flotsam/obj/armour/bplatemail");
    }
    else
    {
        ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonarm");
    }
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bshinguard");
    ob->move(TO, 1);

    ob = clone_object("/d/Krynn/solamn/splains/obj/bheavyboots");
    ob->move(TO, 1);

    command("wear all");
    command("wield all");
}

void
return_intro(object ob)
{
    if(!present(ob, E(TO)))
    {
	return;
    }
    command("introduce me to "+ob->query_real_name());
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
	set_alarm(3.0, 0.0, &return_intro(ob));
    }
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
