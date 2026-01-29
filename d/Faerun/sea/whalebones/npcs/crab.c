/*
 * Crabs on Finback Island
 * by Nucifera, 2021
 * based on various example npcs in Faerun/examples
 */

// sets domain defs file. include in all files.
#include "/d/Faerun/defs.h"
// loads the area def file
#include "/d/Faerun/sea/whalebones/defs.h"
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

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_NIP  0
#define A_LLEG  1
#define A_RLEG  2
#define A_LCLAW 3
#define A_RCLAW 4

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2

// defines random adjs of npc
#define TYPE    ({"cute","baby","pointy", "snippy", "sharp-clawed", "friendly", "tough", "sandy"})
#define PHYS    ({"coconut","soft-shell", "king", "common", "sandy-scaled", "rock", "snow", "stone"})

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
    npc_name = "crab";

    add_adj(type);
    add_adj(phys);
// sets a prop so names are not needed.
    add_prop(LIVE_I_NEVERKNOWN, 1);

// sets what race npc is. it can also be examined with this name
    set_race_name("crab");
    add_name("crab");
    add_name(npc_name);
// sets the plural name for the npc. This can be set if a different name
// is needed.
    add_pname("crabs");

    set_short(type + " " + phys + " crab");
    set_pshort(type + " " + phys + " crab");
    set_long("This is a " + short() + ". It is a ferocious fighter crab who only looks cute and friendly at initial glance. The body is covered with a hard shell. Each foot has pointy little ends with two prominent claws. It buries its head in the sand, but is ready to kill anything it sees.\n");

    add_prop(CONT_I_WEIGHT,500+random(8500));
    add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
// randomly sets the base stats of the npc
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i <= 5; i++)
        set_base_stat(i, 40, 10);

/*
// sets body parts that can be hit or hit with
    set_hitloc_unarmed(1, 20, 15, "head");
    set_hitloc_unarmed(2, 25, 10, "right claw");
    set_hitloc_unarmed(3, 25, 10, "left claw");
    set_hitloc_unarmed(4, 35, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");*/



// sets the gender. G_MALE, G_FEMALE or G_NEUTER
    set_gender(random(2));

// sets skills the npc knows. these are in percents. may be up to 100%
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS, 90);

// sets actions the npc does. this npc will do them approximately every
// 5 seconds
    set_act_time(10);
    add_act("get all");
    add_act("get all");
    add_act("emote burrows into the sand.");
    add_act("emote snips its claws SNIP SNIP.");
    add_act("watch");

// sets npc to randomly move around area every 8 seconds in player in room.
// restricts/restrains npc to the ROOM_DIR files.
    set_random_move(20);
    set_restrain_path(ROOM_DIR);

}

public void
cr_configure()
{
// defines what body part to attack with and how much damage is done
// defines the hit damage, the pen damage, what damage type, % this part is used, and the 'body part' used
    add_attack(5+random(5),5+random(5),W_IMPALE,30,A_NIP);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_LLEG);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_RLEG);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_LCLAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_RCLAW);

// defines what body parts that can be hit
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
        case A_NIP:return "pincers";
        case A_LLEG:return "left leg";
        case A_RLEG:return "right leg";
        case A_LCLAW:return "left claw";
        case A_RCLAW:return "right claw";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}
