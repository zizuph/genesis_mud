
/*
   Living statue of Hurn the mighty Calian hero.
   A most dangerous guard of the way to the Palace of Caliana.
   Blocks enemies of the guild from entering. 
   Coded by Maniac  16.6.95

   History:
         17.1.05   Added immunities           Bishop
         10.6.97   revised                    Maniac
         23.6.95   Modified                   Maniac   
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/creature_statue"; 
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <const.h>
#include "/d/Calia/domain.h"
#include CALIAN_GUILD_BASE_DEF
#include CALIAN_HEADER

#define A_RFIST 0
#define A_LFIST 1 
#define A_LFOOT 2
#define A_RFOOT 3
#define H_HEAD 0
#define H_LEGS 1
#define H_BODY 2
#define H_LARM 3
#define H_RARM 4


int 
is_calian(object player)
{
    return player->query_guild_name_occ() == GUILD_NAME;
}


string
hurn_animate_short()
{
     if (is_calian(this_player()))
         return "living statue of Hurn";
     else
         return "living statue of a huge muscular human";
}


string
hurn_animate_long()
{
     string str = "It moves with incredible agility for " +
                  "something made out of stone, and you " +
                  "shudder at the thought of the crushing power " +
                  "behind those rock limbs.\n";

     if (is_calian(this_player()))
         return "This statue of Hurn, the mighty Calian hero, " +
                "appears to have come to life in order to repel " +
                "those who it believes are a danger to Calians " +
                "from entering the palace. " + str;
     else
         return "This statue of a huge muscular human, " +
                "a hero from Calian legend perhaps, " +
                "appears to have come to life to repel " +
                "an unwanted incursion into Calian territory. " + str;
}


string
hurn_inanimate_short()
{
     if (is_calian(this_player()))
         return "statue of Hurn";
     else
         return "statue of a huge muscular human";
}


string
hurn_inanimate_long()
{
     if (is_calian(this_player()))
         return "This is a statue of Hurn, the mighty Calian hero " +
                "who it is said had the strength to twist the heads " +
                "from wild bulls. Legend has it that it will come to " +
                "life when necessary, in order to repel those who are " +
                "a danger to Calians from entering the palace.\n";
     else
         return "This is a statue of a huge muscular human, " +
                "a hero from Calian legend perhaps. It looks " +
                "ominously lifelike.\n";
}


void
heal_hp(int hp)
{
     if (hp < 0) 
         ::heal_hp(hp/3); 
     else 
         ::heal_hp(hp); 
}


varargs public mixed 
hit_me(int wcpen, int dt, object attacker, 
       int attack_id, int target_hitloc = -1)
{
    if (attack_id == -1) 
         return ::hit_me(wcpen/10, dt, attacker, attack_id, target_hitloc); 
    else 
         return ::hit_me(wcpen/2, dt, attacker, attack_id, target_hitloc); 
}


void
create_creature_statue()
{
    set_name("hurn");
    set_race_name("statue");
    set_gender(G_NEUTER);
    set_animate_short("@@hurn_animate_short");
    set_animate_long("@@hurn_animate_long");
    set_inanimate_short("@@hurn_inanimate_short"); 
    set_inanimate_long("@@hurn_inanimate_long"); 
    set_min_avg_stat_to_attack(10);  
    set_max_avg_stat_to_attack(500); 
    enable_give_warning(); 
    set_adj(({"huge", "muscular", "human"}));
    set_direc_blocks(({"n", "north"})); 

    set_base_stat(SS_STR,250);
    set_base_stat(SS_DEX,250);
    set_base_stat(SS_CON,250);
    set_base_stat(SS_INT,1);
    set_base_stat(SS_WIS,1);
    set_base_stat(SS_DIS,148);

    set_attack_unarmed(A_RFIST,100,100,W_BLUDGEON,40,"right fist");
    set_attack_unarmed(A_LFIST,100,100,W_BLUDGEON,40,"left fist");
    set_attack_unarmed(A_LFOOT,100,100,W_BLUDGEON,10,"left foot");
    set_attack_unarmed(A_RFOOT,100,100,W_BLUDGEON,10,"right foot");
    set_hitloc_unarmed(H_HEAD,({100,100,100,100}),15,"head");
    set_hitloc_unarmed(H_LEGS,({100,100,100,100}),20,"legs");
    set_hitloc_unarmed(H_BODY,({100,100,100,100}),45,"body");
    set_hitloc_unarmed(H_LARM,({100,100,100,100}),10,"left arm");
    set_hitloc_unarmed(H_RARM,({100,100,100,100}),10,"right arm");
    set_alignment(0);
    set_hp(30000);

    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);

    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(OBJ_I_RES_MAGIC, 95);
    add_prop(OBJ_I_RES_POISON, 100);    
}



int
second_life(object killer)
{
    log_file("hurn", ctime(time()) + ": " + 
        "Killed by " + killer->query_name() + " (" +  
        killer->query_real_name() + ")\n" +
        "Present were: " + 
        implode(map(FILTER_PLAYERS(all_inventory(environment())), 
                                  &->query_real_name()), ", ")  + 
          ".\n"); 
    return 0;
}

