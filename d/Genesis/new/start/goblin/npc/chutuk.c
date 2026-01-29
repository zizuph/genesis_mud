inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define TO              this_object()

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("Spot");
    set_race_name("chutuk");
    set_adj("voracious");
    set_gender(G_NEUTER);
    set_aggressive(1);

    set_long(BS("Its only problem seems to be deciding which of its six legs it will claw you with.\n"));

    set_stats(({ 80, 80, 80, 5, 5, 20 }));
    set_hp(10000); /* Heal fully */

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 80);
    
    add_prop(CONT_I_WEIGHT, 85000);
    add_prop(CONT_I_HEIGHT, 1830);
    add_prop(CONT_I_VOLUME, 84000);

    /* Leftover 1 */
    add_leftover("/std/leftover", "nose", 1, 0, 0, 0);
    /* Leftover 2 */
    add_leftover("/std/leftover", "ear", 2, 1, 0, 0);
    /* Leftover 3 */
    add_leftover("/doc/examples/mobiles/bb_heart.c", "heart", 1, 0, 0, 1);
    /* Leftover 4 */
    add_leftover("/std/leftover", "skull", 1, 0, 1, 1);
}