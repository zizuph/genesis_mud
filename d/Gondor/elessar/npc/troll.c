inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name("ugluk");
    set_race_name("troll"); 
    set_adj("nasty");

    set_long("It is a very ugly and nasty lookin' troll.\n");

    default_config_npc();
    set_base_stat(SS_CON, 50);
    set_hp(1000);
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Ok, come on you bastards!"}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object("/d/Wiz/commander/knife");
    wep->move(this_object());
    command("wield knife");

    arm = clone_object("/d/Wiz/commander/jacket");
    arm->move(this_object());
    command("wear jacket");
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
