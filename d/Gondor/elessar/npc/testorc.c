inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("orc");
    add_name("orch");
    set_race_name("orc"); 

    set_long("This is a real ugly orc.\n");

    default_config_npc(7);
    set_base_stat(SS_CON,12);
    set_hp(100);
    set_aggressive(1);
    set_scar(7000);
   set_alignment(-100);
    set_chat_time(5);
    add_chat("Ugly!");
    add_chat("Stick och brinn!");
    add_chat("I'm hungry!");
    seq_new("do_things");
    seq_addfirst("do_things",({"say Wait I'll get my weapons and armour","@@arm_me","say Ok, come on you bastards!"}));
}

query_combat_file() { return "/std/combat/chumanoid"; }

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Gondor/hamurabbi/weapon/shortsword");
    wep->move(this_object());
    command("wield shortsword");

    arm = clone_object("/d/Gondor/hamurabbi/armour/leather");
    arm->move(this_object());
    command("wear armour");
}

find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
