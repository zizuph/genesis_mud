/* /d/Faerun/kryptg/npcs/mutated_human.c
 * 
 * This abomination holds the possessed black dagger, which
 * may turn into the magical nondull long black dagger.
 *
 * Most of the time, it will simply drop a regular rusty black
 * dagger, which has no practical uses.
 *
 * Nerull 2020
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
inherit "/lib/unique";

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include "defs.h"

#define ITEMSPAWN_LOG(x,y)  write_file("/d/Faerun/log/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define KILL_LOG(x,y)  write_file("/d/Faerun/log/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

//void arm_me();


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    set_name("_mutated_boss");
    add_name("bertil");
	add_name("vraeling");

    set_adj("grotesque");
    add_adj("mutated");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("grotesque mutated human");
    
    set_long("Once a human, this grotesque creature seems "
    +"to have mutated beyond recognition. Corrossive fluids "
    +"leak from open infested wounds and unto the ground, "
    +"creating whisps of smoke as if the terrain instantly "
    +"burns and wither away from an unseen flame. Strips of "
    +"tattered clothing covers what looks like skin consisting "
    +"of hardened sickly yellow scales, and the feet and the "
    +"arms are mangled and twisted in unnatural angles. Yet, "
    +"the arms of this creature seems to have mutated into "
    +"powerful claws while the head is half emerged into the "
    +"shoulders with dull eyes barely glancing around in "
    +"pain and desperation. Items still worn on this creature "
    +"is rusted and corroded by the seeping fluids from the "
    +"festering sores.\n");

    add_prop(CONT_I_WEIGHT, 90000);
    add_prop(CONT_I_HEIGHT, 210);

    set_stats(({ 240, 280, 230,
                 170, 180, 220 }));

    set_hitloc_unarmed(A_HEAD, 60, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 60, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 60, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 60, 45, "body");
    set_hitloc_unarmed(A_LEGS, 60, 20, "legs");

    set_attack_unarmed(W_LEFT,  60, 60, W_SLASH,
    80, "left mutated claw");

    set_attack_unarmed(W_RIGHT,  60, 60, W_SLASH,
    80, "right mutated claw");
    
    set_attack_unarmed(W_FOOTR, 25, 25, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 25, 25, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_AWARENESS,60);
    
    set_random_move(5);
    
    set_act_time(5);
    set_cact_time(5);
    add_act("emote growls painfully.");
    add_act("emote staggers about in pain.");
    add_act("emote is in agony, but fails to scream.");
    
    set_cchat_time(5);
    add_cchat("Dyee..deed you be!");
    add_cchat("I wieel reep you skull open!");
    add_cchat("Give mee your hearrth...your intestinees..");
    add_cchat("Come to me...eat ya alive I will!");
    
    set_aggressive(1);
    
    //arm_me();
}


/*void
arm_me()
{
    object wep, magic_wep;
    
    wep = clone_unique(one_of_list(({
                  WEP_DIR + "possessed_black_dagger.c",
                  })),
        15, WEP_DIR + "rusty_black_dagger", 0, 25);
        
    wep->move(this_object(), 1);
    
    ITEMSPAWN_LOG("mutatedhuman_itemspawn_log",
                "The mutated human in underdark spawned a "
                +wep->query_name()+" during the npc respawn.\n");
}*/


void
do_die(object killer)
{
    seteuid(getuid());
    
    KILL_LOG("mutatedhuman_killedby",
             "The mutated human in underdark was slain by "
             +capitalize(killer->query_real_name())+".\n");
             
    object wep, magic_wep;
    
    wep = clone_unique(one_of_list(({
                  WEP_DIR + "possessed_black_dagger.c",
                  })),
        15, WEP_DIR + "rusty_black_dagger", 0, 25);
        
    wep->move(this_object(), 1);
    
    ITEMSPAWN_LOG("mutatedhuman_itemspawn_log",
                "The mutated human in underdark spawned a "
                +wep->query_name()+" during the npc respawn.\n");
    
    ::do_die(killer);
}


/*
* Function name: special_attack()
* Description  : The special attack vs player teams.
*/
int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    
    string how;
    string ohow;
    string tar;

    int     n = -1;

    if (random(4))
    {
        return 0;  /* Continue with the normal attacks */
    }

    // The special.
    hitresult = enemy->hit_me(800
        + random(300), W_SLASH, me, -1);

    how = " doing neglible damage";
    ohow = " doing neglible damage";

    if (hitresult[0] >= 0)

    {
        how = " tearing ";
        ohow = " tearing ";
        tar = " chest";
    }

    if (hitresult[0] > 10)
    {
        how = " raking ";
        ohow = " raking ";
        tar = " chest";
    }

    if (hitresult[0] > 20)
    {
        how = " and rends ";
        ohow = " and rends ";
        tar = " body, spraying gut and blood everywhere";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You hit " + QCTNAME(enemy)
            + " with your mutated claws," + how + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " hits you with his mutated claws," + how + ".\n");
 
        tell_watcher(QCTNAME(me) + " hits "+ QCTNAME(enemy) 
            + " with his mutated claws," + how + ".\n");

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You hit " + QCTNAME(enemy)
            + " with your mutated claws," +
            how + enemy->query_possessive() + tar + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " hits you with his mutated claws," +
            ohow + "your" + tar + ".\n");
 
        tell_watcher(QCTNAME(me) + " hits "+ QCTNAME(enemy) 
            + " with his mutated claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);
            
            

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}



