/* Originally By Sarr */
/*
 * Created and added by Nerull 2/5-09.
 * Removed extra hp buffer, and special functions, making the
 * npc alot easier to kill. 1/7-10
 * Magical resistchecks added to special attacks added 13/7-10.  -Nerull
 * Randomized special attacks 13/7-10.  - Nerull
 *
 * 2018-02-26 Malus: Replaced specials with new implementation 
 * 2010 - New version of this death knight guarding the 
 *         path to the altar room in Khiraa temple 
 *
 * 2021-01-02 Cotillion: Fixed incorrect resistance prop
 */


#include "defs.h"
inherit STD_UNDEAD;
inherit "/d/Genesis/specials/resist.c";
inherit "/lib/unique.c";

void
create_monster()
{
    ::create_monster();
    set_name("knight");
	add_name("death knight");
	add_name("deathknight");
	add_name("terrifying death knight");
    set_adj("death");
    add_adj("terrifying");
    set_short("terrifying death knight");
    set_race_name("human");
    set_long(
      "This is a former Doomguard of Khiraa. He is a skeletal figure "
	  +"clad in all in black, and his arms, legs, head, and " +
      "feet are armoured. You see nothing but darkness through the eye slits " +
      "in his helm. He is tall, menacing and terrible.\n");

    set_stats(STAT_ARRAY(220));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BASHSTUN, 100);
    set_skill(SS_WHIRLWIND, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);
    
    set_alignment(-1200);

    set_cact_time(8);
    add_cact("klaugh");
	add_cact("emote rasps: Khiraa!");
	add_cact("emote rasps: The Nameless One shall have your soul!");
    add_cact("emote rasps: You shall die!");

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_I_RES_LIFE, 40);

    equip(({
      clone_unique("/d/Raumdor/common/arm/gfplate2", 7,
        "/d/Raumdor/common/arm/gfplate2"),
      COMMON_ARM_DIR + "gboots", COMMON_ARM_DIR + "ggloves",
      COMMON_ARM_DIR + "dmrobe", COMMON_ARM_DIR + "dmhelm",
      clone_unique(COMMON_ARM_DIR + "kbbracers", 40, COMMON_ARM_DIR + "rcbracers"), 
      COMMON_WEP_DIR + "kblsword",
      COMMON_WEP_DIR + "kbsword",
    }));

    MONEY_MAKE_GC(random(13))->move(TO, 1);

    add_cmdsoul(SOULS_DIR + "death_knight");
    update_hooks();

    set_exp_factor(125);
}


int
special_attack(object enemy)
{
    if (random(8) == 0)
    {
        command("$whirlwind");
        
        return 1;
    }
    
    return 0;
}