/*
 * Large Bullywug in the Mere of Dead Men
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

#define WEAPON  ({"club_spike", "sword_short"})
#define SHIELD  ({"shield", "shield_small",})
#define BOD_ARM ({"plate_bul", "brigandine"})
//#define GREAVES ({"greaves", "greaves_i", "greaves_sp"})
//#define HELMET  ({""})

#define TYPE    ({"chaotic", "evil", "cunning", "tricky", "shifty", "crafty", \
    "shrewd", "sly"})
#define PHYS    ({"tall", "small", "medium"})

void arm_me();
void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    npc_name = "bullywug";

//    add_adj(type[x]);
//    add_adj(phys[y]);
    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("bullywug");
    add_name(npc_name);

    set_short(phys + " " + type + " bullywug");
    set_pshort(phys + " " + type + " bullywugs");
    set_long("This is a " + short() + ". It lives in swamps and marshes, and is very territorial. The bullywug is frog-like. It has smooth, mottled olive green hide that is reasonably tough. The head is round with slightly bulging eyes. The hands and feet are webbed. The bullywug stands upright and ready to defend itself.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

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
    add_act("emote croaks.");
    add_act("emote splashes in the water.");
    add_act("emote suddenly jumps high in the air.");
    add_act("emote watches you carefully.");
    add_act("emote watches something in the water.");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_random_move(8);
    set_restrain_path(ROOM_DIR);

    set_pick_up_team(({npc_name}));
}



void
arm_me()
{
    object arm, wep;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + ONE_OF_LIST(BOD_ARM));
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
