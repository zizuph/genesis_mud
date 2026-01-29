/*
 * Insect Men of the haunted citadel of Kryptgarden
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define WEAPON  ({"baxe", "baxe2", "mace2", "mace"})
#define BOD_ARM ({"bplate", "tchainmail"})
#define GREAVES ({"greaves"})
#define SHIELDS ({"shield_r", "shield_sp"})
#define PHYS    ({"deadly", "cruel", "savage", "primitive", "ferel", "wild", "beastly", "ruthless", "dark-scaled", "brown-scaled", "green-scaled", "gray-scaled", "dull-scaled", "blue-scaled"})

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());

    phys = ONE_OF_LIST(PHYS);

    npc_name = "insectman";

    add_adj("erect");
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("insect");
    add_name("insect");
    add_name(npc_name);

    set_short(phys + " erect insect");
    set_pshort(phys + " erect insects");
    set_long("This is a " + query_short() + ". It is a cross between a " +
        "human and a flying insect. The creature stands upright and is " +
        "as tall as a man. The skin is covered with hard scales. When " +
        "it speaks, the creature makes a humming sound. The eyes are " +
        "small but have many facets to it.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(25));
    set_base_stat(5, 100);
    set_hitloc_unarmed(1, 20, 15, "head");
    set_hitloc_unarmed(2, 25, 10, "right claw");
    set_hitloc_unarmed(3, 25, 10, "left claw");
    set_hitloc_unarmed(4, 35, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");

    set_alignment(0);
    set_gender(G_NEUTER);
    add_prop(LIVE_I_SEE_DARK,10);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(5);
    add_act("watch");
    add_act("emote hmms at you.");
    add_act("emote makes a buzzing sound.");
    add_act("emote looks around nervously.");
    add_act("emote sniffs the air tentatively.");
    add_act("emote beats its wings rapidly for a few seconds.");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(npc_name);
}


int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_FIRE)
        return 50;
    else
        return 25;
}


void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO,1);
//
//    arm = clone_unique(ARM_DIR + "li_m_plate", MAX_UNIQUE_ITEMS,
//        ARM_DIR + "li_plate");
//    arm ->move(this_object());

    arm = clone_object(ARM_DIR + ONE_OF_LIST(BOD_ARM));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELDS));
    arm -> move(TO);
//
    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);
//
    command("wear armours");
    command("wield weapon");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
