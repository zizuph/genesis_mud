#include "../../../morgulmage.h"
#include <macros.h>

inherit MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/description_base";

void display_ignite_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, "Waves of heat seem to coalesce as " + QTNAME(wielder)
        + " runs " + wielder->query_possessive() + " hand over the "
        + weapon->short() + ". A cannonade of flames encompasses the "
        + "entirety of the, now fell, weapon.\n", wielder);

    wielder->catch_msg("You run your hand along the axis of the "
        + weapon->short() + " causing waves of heat to coalesce into a "
        + "cannonade of flames, which engluf the weapon.\n");
}