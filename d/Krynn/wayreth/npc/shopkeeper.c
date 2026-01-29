#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"

inherit M_FILE

create_krynn_monster()
{
    set_name("demitrius");
    set_long("A kind looking old man, dressed in the red robes of his " +
             "order. He isn't very tall and time has left its mark on " +
             "both his stature and his skin. He is the shop keeper of " +
             "the Tower of Wayreth, and has been so for as long as " +
             "anybody can remember.\n");

    set_race_name("human");
    default_config_mobile(50);
    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);

    set_alignment(0);
    set_knight_prestige(-5);

    add_prop(OBJ_M_NO_ATTACK, 1);

    ALWAYSKNOWN;
}
