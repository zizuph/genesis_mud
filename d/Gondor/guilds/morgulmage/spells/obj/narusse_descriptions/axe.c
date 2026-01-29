#include "../../../morgulmage.h"
#include <macros.h>

inherit MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/description_base";

void display_ignite_message(object wielder, object weapon)
{
    object env = environment(wielder);

    tell_room(env, QCTNAME(wielder) + " snaps " + wielder->query_possessive()
        + " fingers and runs a dancing flame along the edge of the " 
        + weapon->short() + ". Suddenly the axe-head bursts into a feral, "
        + "searing flame.\n", wielder);

    wielder->catch_msg("You snap your fingers, causing a feral flame to "
        + "dance between your thumb and first finger. As you run the flame "
        + "along the edge of the " + weapon->short() + ", it bursts into a "
        + "pale flame.\n");
}

int display_death_message(object wielder, object enemy, object weapon) 
{
    wielder->tell_watcher("In an arcing swing, " + QTNAME(wielder) 
        + " bisects " + QTNAME(enemy) + ", cutting " + enemy->query_objective()
        + " from right shoulder to left hip with the " + weapon->short() 
        + ". Nothing remains except two halves of smoking carcass.\n",
        enemy, ({ wielder, enemy }));

    wielder->catch_msg("With all of the might granted you by the powers of "
        + "Mordor, you swing your " + weapon->short() + " in an high arc. "
        + "A sickening sound emenates from " + QTPNAME(enemy) + " body as "
        + "you bisect " + enemy->query_objective() + " from tip to stern.\n");
        
    enemy->catch_msg("You are frozen in terror and everything moves "
        + "excruciatingly slowly. You see in vivid detail, the "
        + weapon->short() + " wielded by " + QTNAME(wielder) + " moving "
        + "in a long arc toward you! A searing pain flares in your right "
        + "shoulder and you no longer have feeling in your fingers. The "
        + "last thing you see is a shadowy figure looming above you.\n");

    return 1;
}