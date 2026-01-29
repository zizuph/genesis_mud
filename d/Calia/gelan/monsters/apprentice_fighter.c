/* 	
 
    this is a monster of the town Gelan

    coder(s):   Merlin & Maniac

    history:
              5/6/97    another revision of old file        Maniac
              26/7/95   major revision of old file          Maniac

    purpose:    this is an apprentice member of the fighter guards

    weapons:    apprentice fighter steel sword
    armours:    apprentice fighter helmet, plate, boots, gauntlets, gloves

    objects:    some money

    quests:     none
    special:    function to help others

    to do:      armours, weapon
    bug:        none known
*/

#include "monster.h"
inherit STD_GUARD;
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>

#define STATDIFF    20                          /* difference between */
#define SKILLDIFF   20                          /* highest and lowest */

#define ALIGNDIFF   200                         /* possible stat/skill... */
#define COPPERDIFF  30
#define SILVERDIFF  5

#define STATMIN     60                          /* lowest possible */
#define SKILLMIN    50                          /* stat/skill/... */
#define ALIGNMIN    50
#define COPPERMIN   0
#define SILVERMIN   0

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

    seteuid(getuid(this_object()));
    heap = MONEY_MAKE_CC(COPPERMIN + random(COPPERDIFF));
    heap->move(this_object());

    heap = MONEY_MAKE_SC(SILVERMIN + random(SILVERDIFF));
    heap->move(this_object());

    /* weapon(s) */

    weapon = clone_object(GELAN_WEAPONS + "apprentice_sword");
    weapon->move(this_object());
    command("wield sword");

    /* armour */

    armour = clone_object(GELAN_ARMOURS + "apprentice_helmet");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "apprentice_plate");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "apprentice_boots");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "apprentice_gauntlets");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "apprentice_gloves");
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
    set_adj("apprentice");

    set_long("This guard, wearing light blue platemail, is one " +
           "of the apprentice guards of Gelan.\n");

    set_alignment(ALIGNMIN + random(ALIGNDIFF));

    /* stats and skills */

    set_base_stat(SS_INT, STATMIN + random(STATDIFF));
    set_base_stat(SS_WIS, STATMIN + random(STATDIFF));
    set_base_stat(SS_DIS, 125);
    set_base_stat(SS_STR, STATMIN + random(STATDIFF));
    set_base_stat(SS_DEX, STATMIN + random(STATDIFF));
    set_base_stat(SS_CON, STATMIN + random(STATDIFF));

    set_skill(SS_WEP_SWORD, SKILLMIN + random(SKILLDIFF));
    set_skill(SS_PARRY,     SKILLMIN + random(SKILLDIFF));
    set_skill(SS_DEFENCE,   SKILLMIN + random(SKILLDIFF));
    set_skill(SS_BLIND_COMBAT, 75); 
    set_skill(SS_AWARENESS, 75);

    set_hp(query_max_hp());

    /* properties */

    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(5);
    add_act("@@return_check");
}

