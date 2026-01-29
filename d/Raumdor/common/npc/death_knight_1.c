/* Originally By Sarr */
/*
 * Created and added by Nerull 2/5-09.
 * Updated to match the criteria of the AoB. 29/8-10. - Nerull.
 *
 */
#include "defs.h"
inherit STD_UNDEAD;

void
create_monster()
{
    ::create_monster();
    set_name("knight");
    set_adj("death");
    add_adj("black-armoured");
    set_short("black-armoured death knight");
    set_race_name("human");
    set_alignment(UNDEAD_ALIGN);
    set_long("A towering figure clad in all in black. His arms, legs, head, "+
    "feet, everything are armoured with blackened armour of steel. You see a " +
    "pair of red glowing eyes through the eye slits of his helm.\n");

    set_stats(STAT_ARRAY(110));
    set_all_hitloc_unarmed(25);

    set_skill(SS_DEFENCE,80);
    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_WEP_POLEARM,80);
    set_skill(SS_WEP_AXE,80);
    set_skill(SS_PARRY,80);    
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_MOUNTED_COMBAT, 80);
    set_skill(SS_ANI_HANDL, 50);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(LIVE_I_UNDEAD,100);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_aggressive(1);
    
    equip(({
        one_of_list(({
            COMMON_WEP_DIR + "kbsword",
            COMMON_WEP_DIR + "kbaxe",
            COMMON_WEP_DIR + "kbspear",
            COMMON_WEP_DIR + "kbmace",
        })),
        COMMON_ARM_DIR + "kbbracers",
        COMMON_ARM_DIR + "gfplate",
        COMMON_ARM_DIR + "gboots",
        COMMON_ARM_DIR + "ggloves",
        COMMON_ARM_DIR + "gshield",
    }));
    MONEY_MAKE_GC(random(13))->move(TO,1);

    add_cmdsoul(SOULS_DIR + "death_knight");
    update_hooks();
}


mixed 
query_option(int opt) 
{
    return (opt == OPT_UNARMED_OFF); 
}

int
special_attack(object enemy)
{
    if (!random(20))
        command("bash");       

    return 0;
}


