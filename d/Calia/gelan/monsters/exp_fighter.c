/* 	this is a monster of the town Gelan

    coder(s):   Merlin & Maniac

    history:
             5/6/97     revised                             Maniac
             26/7/95    Major revision of old file          Maniac
      

    purpose:    this is an experienced member of the fighter guards

    weapons:    experienced fighter steel sword
    armours:    experienced fighter helmet, plate, boots, gauntlets, gloves

    special:    function to help others

*/

#include "monster.h"
inherit STD_GUARD;
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define STATDIFF    20                          /* difference between */
#define SKILLDIFF   20                          /* highest and lowest */
#define ALIGNDIFF   300                         /* possible stat/skill... */
#define COPPERDIFF  40
#define SILVERDIFF  20
#define GOLDDIFF    25

#define STATMIN     100                          /* lowest possible */
#define SKILLMIN    70                          /* stat/skill/... */
#define ALIGNMIN    400
#define COPPERMIN   10
#define SILVERMIN   10
#define GOLDMIN     0

/*
 * Function name: arm_me
 * Description:   equips the guard
 * Arguments:     none
 * Returns:       none
 */

void
arm_me()
{
    object heap;
    object weapon;
    object armour;

    /* money */

    heap = MONEY_MAKE_CC(COPPERMIN + random(COPPERDIFF));
    heap->move(this_object());

    heap = MONEY_MAKE_SC(SILVERMIN + random(SILVERDIFF));
    heap->move(this_object());

    heap = MONEY_MAKE_GC(GOLDMIN + random(GOLDDIFF));
    heap->move(this_object());

    /* weapon(s) */

    weapon = clone_object(GELAN_WEAPONS + "exp_sword");
    weapon->move(this_object());
    command("wield sword");

    /* armour */

    armour = clone_object(GELAN_ARMOURS + "exp_helmet");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "exp_plate");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "exp_boots");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "exp_gauntlets");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "exp_gloves");
    armour->move(this_object());

    command("wear all");
}

/*
 * Function name: create_monster
 * Description:   creates the guard
 * Arguments:     none
 * Returns:       none
 */

void
create_monster()
{
    /* descritpion */

    set_race_name("guard");

    set_adj(({"experienced", "fighter"}));

    set_long("This guard, dressed in blue, is a fighter guard of "
          + "Gelan, and looks to be one of the more tough and " 
          + "experienced ones.\n"); 

    set_alignment(ALIGNMIN + random(ALIGNDIFF));

    /* stats and skills */

    set_base_stat(SS_INT, STATMIN + random(STATDIFF));
    set_base_stat(SS_WIS, STATMIN + random(STATDIFF));
    set_base_stat(SS_DIS, 175);
    set_base_stat(SS_STR, STATMIN + random(STATDIFF));
    set_base_stat(SS_DEX, STATMIN + random(STATDIFF));
    set_base_stat(SS_CON, STATMIN + random(STATDIFF));

    set_skill(SS_WEP_SWORD, SKILLMIN + random(SKILLDIFF));
    set_skill(SS_PARRY,     SKILLMIN + random(SKILLDIFF));
    set_skill(SS_DEFENCE,   SKILLMIN + random(SKILLDIFF));
    set_skill(SS_AWARENESS, 95);
    set_skill(SS_BLIND_COMBAT, 95); 

    set_hp(query_max_hp());

    /* properties */

    add_prop(CONT_I_WEIGHT, 90000);
    add_prop(CONT_I_VOLUME, 90000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(CONT_I_MAX_VOLUME, 180000);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(5);
    add_act("@@return_check");
}

