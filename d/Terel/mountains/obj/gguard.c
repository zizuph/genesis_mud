

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

#define WEP "/d/Terel/mountains/obj/haxe"
#define ARM "/d/Terel/mountains/obj/chain"

void arm_me();

void
create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

    set_name("goblin guard");
    add_name("guard");
    add_name("goblin");
    set_race_name("goblin");; 
    set_adj("strong");;
    set_long("A very strong looking goblin guard of the black-horn tribe.\n");

    /* Average stat: 20 
     */
    default_config_npc(5);          

    /* But we want it to have more hitpoints
     */
    set_base_stat(SS_CON, 45);
    set_base_stat(SS_STR, 25);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_PARRY, 30);
    set_skill(SS_WEP_AXE, 45);
    set_hp(7000);

    set_all_hitloc_unarmed(15);

    arm_me();
}

void
arm_me()
{
    object wep, arm, money, key;

    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield axe");;

    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear chain");

    key = clone_object("/d/Terel/mountains/obj/bkey");
   key->move(this_object());

}
