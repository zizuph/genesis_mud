/*
 * Lizardmen in the Mere of Dead Men
 * by Finwe, July, 2006
 */

// sets domain defs file. include in all files.
#include "/d/Faerun/defs.h"
// loads the area def file
#include "/d/Faerun/mere/defs.h"
// loads basic routines for this file
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

// loads basic domain NPC code. inherit this file for all npcs
inherit FAERUN_NPC_BASE;
// loads routines so npc will assist other like npcs
inherit "/d/Faerun/lib/assist_friend";
// routine to clone gems instead of coins
inherit "/d/Faerun/lib/gems";
// keeps track of magical/unique items to clone
inherit "/lib/unique";

// sets up random items for npc to clone when npc cloned
#define WEAPON  ({"sword", "sword_mop", "sword_ivory", "mace", "axe"})
#define SHIELD  ({"shield", "shield_small", "shield_oblong"})
#define BOD_ARM ({"li_plate", "brigandine"})
#define GREAVES ({"greaves", "greaves_i", "greaves_sp"})

// defines random adjs of npc
#define TYPE    ({"deadly", "evil", "bloodthirsty", "cruel", "savage", \
    "ruthless"})
#define PHYS    ({"dark-scaled", "brown-scaled", "green-scaled", "gray-scaled"})

// routine to arm npc
void arm_me();
// routine to build the npc. This is defined in FAERUN_NPC_BASE
nomask void create_monster()
{
// defines variables for npcs
    string type, phys;
    int i;

// assigns a unique ID to the npc
    seteuid(getuid());

// defines the adjectives. ONE_OF_LIST() is defined in domain def file
// and randomly chooses a value from the list.
    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

// sets the name of the npc. this var is also used in assist_friend
    npc_name = "lizardman";

    add_adj(type);
    add_adj(phys);
// sets a prop so names are not needed.
    add_prop(LIVE_I_NEVERKNOWN, 1);

// sets what race npc is. it can also be examined with this name
    set_race_name("lizardman");
    add_name("lizard");
    add_name(npc_name);
// sets the plural name for the npc. This can be set if a different name
// is needed.
    add_pname("lizardfolk");

    set_short(type + " " + phys + " lizardman");
    set_pshort(type + " " + phys + " lizardfolk");
    set_long("This is a " + short() + ". It is a ferocious fighter and taller than a human. The body is covered with scales. Each foot has three claws, and the head is large with sharp teeth. It stands upright and ready to kill anything it sees.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
// allows the npc to see in rooms up to 10 levels of darkness
    add_prop(LIVE_I_SEE_DARK,10);
// randomly sets the base stats of the npc
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(25));
    set_base_stat(5, 100);

// sets body parts that can be hit or hit with
    set_hitloc_unarmed(1, 20, 15, "head");
    set_hitloc_unarmed(2, 25, 10, "right claw");
    set_hitloc_unarmed(3, 25, 10, "left claw");
    set_hitloc_unarmed(4, 35, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");

    set_alignment(-110 + random(-50));

// sets skills the npc knows. these are in percents. may be up to 100%
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

// sets actions the npc does. this npc will do them approximately every
// 5 seconds
    set_act_time(5);
    add_act("listen attent");
    add_act("watch");

// clones armours and weapons, and wear them
    arm_me();

// sets npc to randomly move around area every 8 seconds in player in room.
// restricts/restrains npc to the ROOM_DIR files.
    set_random_move(8);
    set_restrain_path(ROOM_DIR);

// will join any npc whose name is "lizardman"
    set_pick_up_team(({"lizardman"}));
}

// sets what types of magic this npc is resistant too.
int
query_magic_res(string prop)
{
// if attacked with items with these magics, resists 50% of them, 
// ele resists 25% of other magical attacks
    if (prop == MAGIC_I_RES_EARTH ||
        prop == MAGIC_I_RES_FIRE  ||
        prop == MAGIC_I_RES_AIR   ||
        prop == MAGIC_I_RES_WATER ||
        prop == MAGIC_I_RES_ILLUSION )
        return 50;
    else
        return 25;
}

// sets up cloning of items for npc
void arm_me()
{
// any objects being cloned must be defined as object
    object arm, wep, gem;

// passes object name and clones 1 gem. defined in /d/Faerun/lib/gems.c
    make_gems(TO, 1);

// clone_unique tracks what magical items have been cloned. It randomly
// chooses if magical item li_m_plate can be cloned. MAX_UNIQUE_ITEMS is 
// defined in domain def.h file and sets the max number of items that can be
// cloned. if magical item li_m_plate not cloned, clone li_plate instead and 
// move it to the npc. Only use clone_unique if the npc will clone a 
// magical or limited item.
    arm = clone_unique(ARM_DIR + "li_m_plate", MAX_UNIQUE_ITEMS,
        ARM_DIR + "li_plate");
    arm ->move(this_object());
// randomly choose a greaves and move to npc
    arm = clone_object(ARM_DIR + ONE_OF_LIST(GREAVES));
    arm -> move(TO);

    arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELD));
    arm -> move(TO);

    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);

    command("wear armours");
    command("wield weapon");

}

// initilaize these routines for the npc
void
init_living()
{
    ::init_living();
// initializes the team code
    init_team_pickup();
}
