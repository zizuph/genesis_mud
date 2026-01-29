#include "../../../morgulmage.h"
#include <macros.h>

inherit MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/description_base";

void display_ignite_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, "In a whirlwind of motion, " + QTNAME(wielder)
        + " purls the " + weapon->short() + " above "
        + wielder->query_possessive() + " head. During the swift "
        + "revolutions, the end of the long weapon is engulfed in "
        + "flame.\n", wielder);

    wielder->catch_msg("You deftly handle the " + weapon->short() 
        + " and spin it aloft in a fell circumvolution causing its "
        + "end to burst into the flames of Mordor.\n");
}



