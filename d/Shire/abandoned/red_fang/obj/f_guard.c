/* 
 * /d/Kalad/common/wild/pass/goblin/guild/f_guard.c
 * Purpose    : A red Fang guard
 * Located    : IN the hall.c
 * Created By : Sarr ??.??.??
 * Modified By: Sarr 16.Apr.97
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

/* Red Fang Guards */
/* Sarr */

void
create_monster()
{
    ::create_monster();
    set_name("goblin");
    add_name("guard");
    set_race_name("goblin");
    set_adj("fierce");
    add_adj("proud");
    set_short("fierce proud goblin guard");    
    set_long("This tall and fierce looking guard gazes at you with "+
    "burning red eyes. He stands pround, with a grim look on his face.\n");
    set_stats(({160,120,160,100,100,160}));
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_SNEAK,50);
    set_skill(SS_PARRY,100);
    set_act_time(6);
    add_act("emote growls something.");
    add_act("emote spits on the ground in hatred of human scum.");
    add_act("emote snarls with inhuman rage.");
    add_act("emote paces around.");
    set_cact_time(4);
    add_cact("emote cries out: The Red Fang will never die!!");
    add_cact("emote cries out: Brothers! To arms!");
    add_cact("emote growls: Die intruder!!");
}

void
init_living()
{
    if(TP->query_race_name() == "human")
        set_alarm(1.0,0.0,"do_attack");
    if(TP->test_bit("kalad",4,5))
        set_alarm(1.0,0.0,"do_drow");
    if(TP->query_race_name() == "goblin")
        set_alarm(1.0,0.0,"do_goblin");
    ::init_living();
}

void
do_goblin()
{
    if(TP->test_bit("kalad",4,8))
    {
        command("emote growls: Hail, Red Fang!");
        command("emote salutes sharply.");
    }
}

void
do_drow()
{
    command("emote growls: Hail Drow! What brings thee here, I wonder.");
    command("nod slight "+lower_case(TP->query_name()));
}

void
do_attack()
{
    if(TP->test_bit("kalad",4,4))
        command("emote screams: THAAANAAAARRRR!!!!!");
    else    
        command("emote politely says: I'm terribly sorry, dear human, but I must kill you now.");
    command("kill "+lower_case(TP->query_name()));
}

void
arm_me()
{
    object wep,arm,arm2,arm3;
    seteuid(getuid(TO));
    wep = clone_object(FANG_DIR(obj/f_dagger));
    arm = clone_object(FANG_DIR(obj/f_armour));
    arm2 = clone_object(FANG_DIR(obj/f_greaves));
    arm3 = clone_object(FANG_DIR(obj/f_helm));
    wep->move(TO,1);
    arm->move(TO,1);
    arm2->move(TO,1);
    arm3->move(TO,1);
    command("wear all");
    command("wield all");
}

int
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
   {
      command("shout Die fool!");
      command("kill "+lower_case(ob->query_name()));
   }
}


