/*
 * Lizardmen in the Mere of Dead Men
 * by Finwe, July, 2006
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

#define WEAPON  ({"sword", "sword_mop", "sword_ivory", "mace", "axe"})
#define SHIELD  ({"shield", "shield_small", "shield_oblong"})
#define BOD_ARM ({"li_plate", "brigandine"})
#define GREAVES ({"greaves", "greaves_i", "greaves_sp"})
//#define HELMET  ({""})
#define TYPE    ({"deadly", "evil", "bloodthirsty", "cruel", "savage", \
    "ruthless"})
#define PHYS    ({"dark-scaled", "brown-scaled", "green-scaled", "gray-scaled"})

void arm_me();
nomask void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    npc_name = "lizardman";

//    add_adj(type[x]);
//    add_adj(phys[y]);
    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("lizardman");
    add_name("lizard");
    add_pname("lizardmen");
    add_name(npc_name);
    add_name("lizardfolk");

    set_short(type + " " + phys + " lizardman");
    set_pshort(type + " " + phys + " lizardmen");
    set_long("This is a " + short() + ". It is a ferocious fighter and taller than a human. The body is covered with scales. Each foot has three claws, and the head is large with sharp teeth. It stands upright and ready to kill anything it sees.\n");

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

    set_alignment(-110 + random(-50));
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
    add_act("emote hisses at you.");
    add_act("emote snarls at you dangerously.");
    add_act("emote flicks its tongue out, tasting the air.");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(({"lizardman"}));
}


int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_EARTH ||
        prop == MAGIC_I_RES_FIRE  ||
        prop == MAGIC_I_RES_AIR   ||
        prop == MAGIC_I_RES_WATER ||
        prop == MAGIC_I_RES_ILLUSION )
        return 50;
    else
        return 25;
}


void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_unique(ARM_DIR + "li_m_plate", MAX_UNIQUE_ITEMS,
        ARM_DIR + "li_plate");
    arm ->move(this_object());
    arm = clone_object(ARM_DIR + ONE_OF_LIST(GREAVES));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELD));
    arm -> move(TO);

    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);

    command("wear armours");
    command("wield weapon");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
