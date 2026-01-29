/*
 * 
 * Nerull, 2021
 *
 */


#include "defs.h"
inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";
inherit "/d/Genesis/specials/resist.c";
inherit "/lib/unique.c";


void
create_monster()
{
    ::create_monster();
    set_name("crusader");
    set_adj("powerful");
    add_adj("holy");
    set_short("powerful holy crusader");
    set_race_name("human");
    set_long(
      "This is obviously the leader of the elite infantry or paladins "
      +"that is sieging Castle Gylar. He is "
      +"all dressed in grey plate armour and properly "
      +"draped with white decorated fabric. The decoration "
      +"resembles a sword-shaped cross.\n");
           
    set_gender(G_MALE);

    set_stats(STAT_ARRAY(220));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);
    
    set_alignment(1200);

    set_cact_time(8);
    add_cact("smile fanatically");
	add_cact("emote say: Die demon! Die!");
	add_cact("emote say: Flee! Run back to your undead masters "
    +"and cover in fear! We are coming for You!!");
    add_cact("emote say: By the will of the Lord, you shall be "
    +"purged in the holy fire!");
    add_cact("emote say: Agent of Evil, be Purged!");
    add_cact("emote say: Feel my Wrath, Demon!!");
    add_cact("emote say: You dare to attack us?? You shall Burn "
    +"for your Evil sins!");

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_RES_DEATH, 40);

    equip(({
      clone_unique(COMMON_ARM_DIR + "fiery_platemail", 20, COMMON_ARM_DIR + "grey_plate"), 
      COMMON_ARM_DIR + "silv_boots", COMMON_ARM_DIR + "silv_gloves",
      COMMON_ARM_DIR + "white_robe", COMMON_ARM_DIR + "silv_helm",
      clone_unique(COMMON_ARM_DIR + "kbbracers", 20, COMMON_ARM_DIR + "silv_bracers"), 
      COMMON_WEP_DIR + "silv_sword",
      COMMON_WEP_DIR + "silv_sword",
    }));

    MONEY_MAKE_GC(random(13))->move(TO, 1);

    update_hooks();

    // Normal xp
    set_exp_factor(125);
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
    if (random(5))
    {
        return 0;  /* Continue with the normal attacks */
    }
    
    // The special.
    hitresult = enemy->hit_me(700
        + random(400), W_SLASH, me, -1);
    how = " doing neglible damage";
    ohow = " doing neglible damage";
    
    if (hitresult[0] >= 0)
    {
        how = " bashing ";
        ohow = " bashing ";
        tar = " chest";
    }
    
    if (hitresult[0] > 10)
    {
        how = " pounding ";
        ohow = " pounding ";
        tar = " chest";
    }
    
    if (hitresult[0] > 20)
    {
        how = " and smashes ";
        ohow = " and smashes ";
        tar = " body, cracking ribs in the process";
    }
    
    if (hitresult[0] == -1)
    {
        me->catch_msg("You slam into " + QCTNAME(enemy)
            + " with your armoured shoulder," + how + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " slams into you with his armoured shoulder," + how + ".\n");
 
        tell_watcher(QCTNAME(me) + " slams "+ QCTNAME(enemy) 
            + " with his armoured shoulder," + how + ".\n");
        return 1;
    }
    
    if (hitresult[0] >= 0)
    {
        me->catch_msg("You slam " + QCTNAME(enemy)
            + " with your armoured shoulder," +
            how + enemy->query_possessive() + tar + ".\n");
            
        enemy->catch_msg(QCTNAME(me)
            + " slams into you with his armoured shoulder," +
            ohow + "your" + tar + ".\n");
 
        tell_watcher(QCTNAME(me) + " slams "+ QCTNAME(enemy) 
            + " with his armoured shoulder," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);
            
            
        if (enemy->query_hp() <= 0);
        
        enemy->do_die(me);
        
        return 1;
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}