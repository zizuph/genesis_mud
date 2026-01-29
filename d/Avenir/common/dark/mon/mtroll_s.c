// Sleeping troll worker
// Troll worker digging Avenir tunnels
// Made by Boriska@Genesis Nov 1994
// revised by Tepisch March 1995
// revised by Casca 01/21/00

inherit "/std/monster";

int alarm_id;

#include "/d/Avenir/common/dark/dark.h"
#include "money.h"

create_monster ()
{
    set_name ("goblin");
    add_name ("laborer");

    set_short ("dirty goblin laborer is sleeping soundly");
    set_pshort ("dirty goblin laborers are sleeping soundly");
    set_adj (({"sleeping","dirty", "worker","troll"}));
    set_long("This fellow is a giant amongst goblins. "+
        "He is working for the sybarite elves at digging tunnels. "+
        "He is filty from his labors, and despite his exhaustion, "+
        "appears to be content with his lot.\n"+
        "He is a proud member of B.O.G.L., the Brotherhood of "+
        "Goblin Laborers.\n");
  
    set_race_name("goblin");

    add_prop(LIVE_S_SOULEXTRA,"sleeping soundly");
  
    set_stats (({90,70,70,10,10,10}));
    set_alignment (0);

    set_skill (SS_WEP_AXE, 75);
    set_skill (SS_PARRY, 60);
    set_skill (SS_DEFENSE, 60);

    set_act_time (25);

    add_act ("emote snores sonorously.");
    add_act ("emote mumbles something in his sleep.");
    add_act ("emote chokes on saliva as he inhales too deeply on a snore.");
    add_act ("snore");
    add_act ("emote gives you a bleary-eyed stare and falls back to sleep.");

    add_prop (CONT_I_WEIGHT, 500000);
    add_prop (CONT_I_VOLUME, 400000);

}

void
equip_me()
{
  clone_object (OBJ + "t_pickaxe")->move(this_object());
  clone_object (OBJ + "t_chainmail")->move(this_object());
  MONEY_MAKE_CC (50)->move(this_object());
  command ("wear all"); 
}


void 
return_to_normal()
{

    remove_alarm(alarm_id);
    alarm_id = 0;
    set_short ("dirty goblin laborer is sleeping soundly");
    set_pshort ("dirty goblin laborers are sleeping soundly");
    add_prop(LIVE_S_SOULEXTRA,"sleeping soundly");
    command("unwield all");
    command("emote begins drifting off to sleep.");
    set_adj (({"sleeping","dirty", "goblin", "worker"}));
//    set_act_time (30);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_short ("dirty goblin laborer");
    set_pshort ("dirty goblin laborer");
    add_prop(LIVE_S_SOULEXTRA,"growling ferociously");
    command("emote blinks sleep from his eyes.");
    command("wield all");
    set_adj (({"awake","dirty", "troll", "worker"}));
//    set_act_time (15);
    if (alarm_id)
        return;
    alarm_id = set_alarm(100.0, 0.0, return_to_normal);
}



