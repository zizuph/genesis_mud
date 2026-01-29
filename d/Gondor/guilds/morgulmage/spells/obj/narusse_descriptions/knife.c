#include "../../../morgulmage.h"
#include <macros.h>

inherit MORGUL_SPELL_OBJ_DIR + "narusse_descriptions/description_base";

void display_ignite_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, QCTNAME(wielder) + " plunges the " + weapon->short() 
        + " into the ground with a blur of inhuman speed. As the blade is "
        + "extracted from the terra, a pale flame flickers along its "
        + "entirety.\n", wielder);

    wielder->catch_msg("You grasp the handle of the " + weapon->short()
        + " and plunge it into the ground with inhuman speed. As you pull "
        + "it from the bowels of the lome, a pale radiant flame surrounds "
        + "the blade.\n");
}