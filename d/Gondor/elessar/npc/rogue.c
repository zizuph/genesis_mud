
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"

#define WEP1 "/d/Gondor/gus/obj/weapon/sword"
#define WEP2 "/d/Gondor/gus/obj/weapon/shortsword"

#define ARM1 "/d/Gondor/gus/obj/armour/chainmail"
#define ARM2 "/d/Gondor/gus/obj/armour/shield"
#define ARM3 "/d/Gondor/gus/obj/armour/helmet"

create_monster()
{
 if (!IS_CLONE) 
        return;
    set_living_name("erkam");
    set_name(({"Erkam","knight","instructor","erkam"}));
    set_race_name("human");
    set_short("Erkam the knight");
    set_adj("lazy");
    set_long("This is Erkam the knight of the town Imdorad in Rohan. In the\n"
           + "garrison, he works as a drill instructor. He teaches, among\n"
           + "other things, the art of riding.\n");
    
    /* set_random_move(15); */

    /* Average stat: 20 */
    default_config_npc(20);          

    /* But we want it to have more hitpoints */
    set_base_stat(SS_STR, 17);
    set_base_stat(SS_CON, 45);
    set_hp(2000);
    set_exp(100000);
    set_skill(SS_WEP_SWORD, 45);
    set_skill(SS_2H_COMBAT,50);
    set_skill(SS_PARRY,40);
    set_skill(SS_DEFENCE,45);

    /* He wants to talk */
    set_chat_time(15);
    add_chat("I love the Army!");
    add_chat("This is the town Imdorad.");
    add_chat("Can you tell me a nice story?");
    add_chat("I love good literature!");
    add_chat("What are you doing here?");
    add_cchat("Alarm!");
add_cchat("Just give up, traitor! I'm a master of the sword!");
add_cchat("Ok, come on, bastard! I'll beat you up badly!");

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Wait! I'll get my gear."}));
}

arm_me()
{
    object wep, arm;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object(WEP1);
    wep->move(this_object());
    command("wield sword");

    wep = clone_object(WEP2);
    wep->move(this_object());
    command("wield shortsword");

    arm = clone_object(ARM1);
    arm->move(this_object());
    command("wear chainmail");

    arm = clone_object(ARM2);
    arm->move(this_object());
    command("wear shield");

    arm = clone_object(ARM3);
    arm->move(this_object());
    command("wear phelmet");
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
