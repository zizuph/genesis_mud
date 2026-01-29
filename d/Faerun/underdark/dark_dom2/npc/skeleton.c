/*
 * Skeletons of Underdark
 * Cannibalized from Finwe's Svirf by Abaddon, June, 2020
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

void arm_me();

void create_monster()
{
    int x, y, i;
    string *type, *phys;

    seteuid(getuid());

    type = ({"agitated", "sullen", "withdrawn", "suspicious", "watchful", "stoic", "evasive" });
    phys = ({"yellow", "jawless", "runed", "whispy-haired", "bald", "gnarled"});

    x = random(sizeof(type));
    y = random(sizeof(phys));

    npc_name = "skeleton";

    add_adj(type[x]);
    add_adj(phys[y]);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_race_name("skeleton");
    add_name("skeleton");
    add_name(npc_name);

    set_short(type[x] + " " + phys[y] + " skeleton");
    set_pshort(type[x] + " " + phys[y] + " skeletons");
    set_long("This appears to be a reanimated corpse. Near entirely decayed" +
        ", this creature appears to have been humanoid in life. The malevol" +
        "ent glow in its eye suggests it has been raised by some occult rit" +
        "ual.\n");

    add_prop(NPC_I_NO_FEAR, 1);     /* all skellies defend each other */
    add_prop(CONT_I_WEIGHT,6128);  /* 27.5 Kg */
    add_prop(CONT_I_HEIGHT,63);     /* 63 cm */
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 110 + random(25));
    set_base_stat(5, 70);


    set_alignment(0);
    add_prop(LIVE_I_SEE_DARK,10);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(50);
    add_act("blanch ominous");
    add_act("stare");
    add_act("wring");
    add_act("stagger .");
    add_act("pace clum");
    add_act("grit teeth");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

//    set_random_move(8);
//    set_restrain_path(ROOM_DIR);

    set_pick_up_team(({"skeleton"}));
    set_pick_up_team(({"necromancer"}));
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
/*
//I would like to make these Skeletons
//immune to impaling damage, resistant
//to slashing damage, but very weak to
// bludgeoning damage.
*/

void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + "sk_mail");
    arm -> move(TO);
//    wep = clone_object(WEP_DIR + "sv_axe");
//    wep -> move(TO);

    command("wear all");
    command("wield all");

}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}