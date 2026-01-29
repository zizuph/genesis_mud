/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*   Modified by Meton - 2020
*/

inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Kalad/lib/special";
inherit "/d/Kalad/lib/prestige";

#include <wa_types.h>
#include "../local.h"
#include <macros.h>
#include "/sys/money.h"
#include <files.h>

inherit LIV + "npc_looting.c";
inherit LIV + "goblinspecial.c";
#include "/std/act/attack.c"

public void         create_goblin_living();

/*
* Function name: create_active_monster
* Description  : Constructor. Creates the monster.
*/
nomask void create_active_monster()
{
    /* Redefine this function to customize the npcs */
    
    create_goblin_living();
    
} /* create_active_monster */

void
create_goblin_living()
{
    set_name("goblin");
    add_name("_hgiant_friends");
    set_race_name("goblin");
    set_adj(one_of_list(GOBLINADVERBS));
    set_long(one_of_list(GOBLINDESC) + "He is "+ one_of_list(HEIGHT)
    + " and " + one_of_list(WIDTH) + " for a goblin.\n");
    set_stats(({120,80,120,100,100,100}));
    set_alignment(-400);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_prospective_cluster(({"_hgiant_friends"}));
    set_aggressive(1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    set_act_time(9);
    add_act("smile stupidly");
    add_act("duh");
    add_act("scratch behind");
    add_act("get all from corpse");
    
    set_cact_time(9);
    add_cact("say Me smash you like bug!");
    add_cact("say Me eat you for dinner!");
    add_speak("You know go away, me want to bash you.\n");

    set_knight_prestige(50);
    set_exp_factor(130);
    //set_default_special(25, W_BLUDGEON, 85, 250, A_BODY);
    //Thich skin, easiest pierced, hard to slash, absorbs bludgeon.

    equip(({one_of_list(GOBLINWEAPONS),
        ARM + "goblin_boots",
        ARM + "goblin_bracers",
        ARM + "goblin_breastplate",
        ARM + "goblin_gloves",
        ARM + "goblin_greaves",
        ARM + "goblin_helmet",
        ARM + "goblin_armring",
        ARM + "bed_erobe"}));
    MONEY_MAKE_CC(random(50))->move(this_object);
    MONEY_MAKE_SC(random(20))->move(this_object);
    MONEY_MAKE_GC(random(3))->move(this_object);
}
