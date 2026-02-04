/*
    /doc/examples/mobiles/troll.c

    JnA 920115

    A sample monster

    Monsters are humanoid creatures that get humanoid attacks and
    hitlocations predefined. We need not bother to set these if we
    do not want to, it will be managed for us.

    This troll gives an example of how to use the sequence actions in
    combination with VBFC. It is used to wield and wear.

*/
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include <money.h>

#define WEP "/d/Terel/mecien/axe"
#define ARM "/d/Terel/mecien/plate"

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

    set_name("giant");
    set_race_name("giant");; 
    set_adj("fat");;
    set_long("A very ugly, fat and mean giant.\n");

    /* Average stat: 20 
     */
    default_config_npc(5);          

    /* But we want it to have more hitpoints
     */
    set_base_stat(SS_CON, 94);
    set_base_stat(SS_DEX, 50);
    set_base_stat(SS_STR, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 74);
    set_skill(SS_WEP_AXE, 96);
    set_hp(10000);

    set_all_hitloc_unarmed(35);

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say I am very hungry!"}));
}

arm_me()
{
    object wep, arm, money;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield axe");;

    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear plate");
    
    money = MONEY_MAKE_SC(50);
    money->move(this_object());
}

/*
 * Find some player somewhere and go there
 */
find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
