/* 	this is a skeleton found in the random dungeons when mining.

    coder(s):   Maelstrom

    history:
                2017/04     created                         Maelstrom

    purpose:    this is a skeleton that rises when looting.

    weapons:    random sword
    armours:    random pieces of armour

    special:    wake up other skeletons

TODO



*/

inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "../defs.h"

#define STATDIFF    20                          /* difference between highest */
#define SKILLDIFF   20                          /* and lowest possible stat/skill/... */
#define ALIGNDIFF   600
#define COPPERDIFF  40
#define SILVERDIFF  10

#define STATMIN     80                    /* lowest possible stat/skill/... */
#define SKILLMIN    60
#define ALIGNMIN    -300
#define COPPERMIN   10
#define SILVERMIN   2

#define SPECIAL     10

/*
 * Function name: arm_me
 * Description:   equips the skeleton
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

    /* weapon(s) */
/*
    weapon = clone_object(GELAN_WEAPONS + "fighter_sword");
    weapon->move(this_object());
    command("wield sword");
*/
    /* armour */
/*
    armour = clone_object(GELAN_ARMOURS + "fighter_helmet");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "fighter_plate");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "fighter_boots");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "fighter_gauntlets");
    armour->move(this_object());

    armour = clone_object(GELAN_ARMOURS + "fighter_gloves");
    armour->move(this_object());

    command("wear all");


    use this instead:
    add_weapon
    add_armour
*/
}

/*
 * Function name: create_monster
 * Description:   creates the skeleton
 * Arguments:     none
 * Returns:       none
 */

void
create_monster()
{
    seteuid(getuid());

    /* descritpion */
    set_name("skeleton");
    set_race_name("skeleton");
    set_adj("decayed");

    set_long("This skeleton looks rotted to the core, only bits of flesh "
          + "hang from the exposed bones.\n");

    set_alignment(ALIGNMIN + random(ALIGNDIFF));

    /* stats and skills */

    set_base_stat(SS_INT, STATMIN + random(STATDIFF));
    set_base_stat(SS_WIS, STATMIN + random(STATDIFF));
    set_base_stat(SS_DIS, 150);
    set_base_stat(SS_STR, STATMIN + random(STATDIFF));
    set_base_stat(SS_DEX, STATMIN + random(STATDIFF));
    set_base_stat(SS_CON, STATMIN + random(STATDIFF));

    set_skill(SS_WEP_SWORD, SKILLMIN + random(SKILLDIFF));
    set_skill(SS_PARRY,     SKILLMIN + random(SKILLDIFF));
    set_skill(SS_DEFENCE,   SKILLMIN + random(SKILLDIFF));
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_BLIND_COMBAT, 85); 

    set_hp(1-query_max_hp());//set_hp(query_max_hp());

    /* properties */

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_VOLUME, 70000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1); 
    add_prop(NPC_I_NO_LOOKS, 1);

    set_gender(G_NEUTER);

    set_aggressive(1, 100);
    set_attack_chance(100);
    set_attack_dare(0); //dont check

    arm_me();
}

public int
special_attack(object victim)
{
    object tp = this_player();
    object monster;

    string * action =
    ({
        "slaps",
        "grabs",
        "jerks",
        "kicks",
        "punches",
        "shakes",
        "pokes"
    });
    string * place =
    ({
        "neck",
        "skull",
        "hand",
        "leg",
        "arm",
        "foot",
        "chest"
    });
    string * consequence =
    ({
        "rises",
        "wakes up",
        "slowly grumbles and stands",
        "curses while getting ready to attack",
        "puts its feet back into place and gets up",
        "pulls off his arm from under a heavy rock and rises",
        "clears off a sword sticking out its chest and gets ready to attack"
    });

    tell_room(environment(tp), "debug skeleton 1.\n");

    if (random(100) < SPECIAL)
    {
        monster = clone_object(NPC_DIR + "skeleton");
        monster->move(environment(tp));
        tell_room(environment(tp), QCTNAME(tp) + one_of_list(action) + " the " + one_of_list(place) + " of " + QCTNAME(monster) + " and it " + one_of_list(consequence) + ".\n");
    }

    return 0;       
}

public void
init_living()
{
    ::init_living();
}