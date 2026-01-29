/* An Caveman (humanoid) - Recoded 18/07/95, Tulix III      */
/* Cloned by cave3a.c & cave9a.c in /d/Emerald/cave/levela/ */
 
inherit "/std/monster";
inherit "/std/act/action"; 
inherit "/std/act/chat";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("ungd");
    add_name("caveman");
    set_race_name("human");
    set_short("primitive human");
    set_adj("primitive");
    set_long(
        "It is a very primitive looking cave-man. He does not look like a " +
        "particularly well educated chap.\n" );
 
    add_prop(LIVE_I_NEVERKNOWN, 1 );
 
    set_gender(0);
 
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  40,  35,  35,  30,  30,  30}));
    set_hp(10000);
    set_alignment(20);
 
    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10,10);
 
    set_attack_chance(15);
 
    /* Set the all important skills.           */
    set_skill(SS_WEP_CLUB,45);
 
    set_skill(SS_UNARM_COMBAT,10);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_PARRY,40);
    set_skill(SS_DEFENCE,30);
 
    set_act_time(10);   /* Set action interval */
    add_act("growl all");
    add_act("spit at lichen");
    add_act("stomp");
    add_act("shiver");
 
}
 
 
void
arm_me()
{
    object wep;
 
    wep = clone_object( CAVE_DIR + "wep/bone" );
    wep->move( TO );
    command( "wield all" );
}
