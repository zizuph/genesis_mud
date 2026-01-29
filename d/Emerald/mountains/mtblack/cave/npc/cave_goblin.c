/* An Caveman (humanoid) - Recoded 18/07/95, Tulix III      */
/* Cloned by cave3b.c & cave8b.c in /d/Emerald/cave/levelb/ */
 
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/std/act/add_things.c";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("inthakur");
    set_short("noisy goblin");
    set_race_name("goblin");
    set_adj("noisy");
    set_long(
        "It is a noisy goblin. You don't particularly fancy the idea of " +
        "having him living next to you!\n" +
        "It looks as if he is not too keen on your presence.\n");
    /*
    set_random_move(10);
    */
    set_alignment(-50);
 
    set_stats(({60,40,50,50,50,50}));
    set_hp(2000);
 
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20,10);
 
    set_skill(SS_WEP_KNIFE, 40);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_PARRY,30);
    set_skill(SS_BLIND_COMBAT,60);
 
    set_chat_time(10);
    add_chat("Get out of my cave!");
    add_chat("Can't you hear? Get out!");
    add_chat("Out of my way.");
    add_chat("Get out before I kill you!");
 
    set_act_time(7);
    add_act("grin");
    add_act("spit at lichen");
    add_act("snarl");
    add_act("growl");
    add_act("finger all");
    add_act("scream");
    add_act("kick all");
 
}
 
void
arm_me()
{
    object wep,arm;
 
    wep = clone_object( CAVE_DIR + "wep/goblin_knife" );
    wep->move( TO );
    arm = clone_object( CAVE_DIR + "arm/goblin_hides" );
    arm->move( TO );
    command( "wear all" );
    command( "wield all" );
}
