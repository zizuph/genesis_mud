#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

create_krynn_monster()
{
    set_name("gaidal");
    set_title("the Party Favor(ing) Guru");
    set_long("This ever-smiling drunk is the owner of the shop, " +
	"and for a modest fee can set you up with the best drinking " +
	"equipment available. You want a throw a party in the party " +
	"room? He's the man who will set up the bash. Just remember " +
	"to keep the noise level down, he's permanently hung over.\n");

    set_race_name("drunk");
    set_gender(0);
    set_introduce(1);
    default_config_mobile(50);
    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alignment(0);
    set_knight_prestige(-5);

    add_prop(OBJ_M_NO_ATTACK, 1);

    ALWAYSKNOWN;
}
