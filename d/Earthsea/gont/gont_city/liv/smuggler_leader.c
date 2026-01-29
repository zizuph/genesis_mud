#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/basic_special";
inherit "/lib/unique";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public void
create_earthsea_monster()
{
    set_name("smuggler");
    add_name("leader");
    add_name("__es_smuggler_dock_leader__");
    set_race_name("human");
    set_height("very tall");
    set_width("skinny");
    set_adj(({"lanky", "shifty-eyed", "black-eyed", "kargish"}));
    set_short("lanky shifty-eyed human");
    set_long("This gangly human seems to be standing watch " +
        "over the warehouse. His deep black shifty eyes " +
        "reveal a keen awareness of his surroundings, and " +
        "there is something about his face that does not seem " +
        "quite right.\n");
    set_stats(({140, 165, 155, 120, 120, 135}));
    set_skill(SS_WEP_AXE, 85);
    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_HIDE, 90);
    set_skill(SS_SNEAK, 90);
    set_all_hitloc_unarmed(40);
    add_prop("_ranger_i_not_disarm", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    clone_unique("/d/Earthsea/gont/gont_city/wep/bl_battleaxe", 8,
	"/d/Earthsea/gont/gont_city/wep/g_axe", 
        0, 80)->move(this_object());
    clone_unique("/d/Earthsea/gont/gont_city/arm/bl_platemail", 5,
	"/d/Earthsea/gont/gont_city/arm/g_ringmail",
	0, 45)->move(this_object()); 
    log_my_kills("/d/Earthsea/log/npc_logs/smuggler_kill.log", 1);
    log_my_deaths("/d/Earthsea/log/npc_logs/smuggler_death.log", 1);
}

public void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);

    if(!ob->id("__es_big_black_battleaxe__"))
    {
        return;
    }

    set_special_attack_percent(20);
    add_special_attack(&basic_special(this_object(), 450+random(350),
        W_BLUDGEON), 100, "axesmack");
    set_target_message(" smacks you across the head with his " +
        "blackened heavy battleaxe!");
    set_watcher_message(" smacks", " across the head with his " +
        "blackened heavy battleaxe!");
    set_result_messages(([
        5 : "You are barely hurt by the attack.",
        10 : "You are somewhat hurt by the attack.",
        15 : "You are rather hurt by the attack.",
        20 : "You are extremely hurt by the attack."
    ]));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!ob->id("__es_big_black_battleaxe__"))
    {
        return;
    }

    remove_special_attack("axesmack");
}

public void
react_smuggler(object smuggler)
{
    command("reveal myself");
    command("slap __es_sneaking_smuggler__");
    command("say I hope you have good news! We needed to be " +
        "running months ago.");
    smuggler->command("cower");
}

public void
greet_smuggler(object smuggler)
{
    set_alarm(1.0, 0.0, &react_smuggler(smuggler));
}

public void
cheer_departure(object ob)
{
    if(interactive(ob))
    {
        command("hide");
    } else if(ob->id("smuggler") && !ob->id("leader")) {
        command("grumble");
        command("hide");
    }
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    command("smirk");
    command("say Fool! I will crush you.");

    if(ob == query_attack() && sizeof(query_weapon(-1)))
    {
        basic_special(this_object(), 650+random(350), W_BLUDGEON);
    }
}
