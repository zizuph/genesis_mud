#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

create_krynn_monster()
{
    set_name("slag");
    set_title("the Kilnmaster of the Diamond Isle");
    set_long("Always manning the forge, this man has become like a " +
	"piece of leather. Enjoying his career melting down " +
	"equipment of violence, he will always try to accomodate " +
	"anyone willing to part with weapons or armours. Standing " +
	"out on his person, you notice typical leather gloves and a " +
	"smith's apron, but covered with what appears to be diamond " +
	"dust, most likely magical.\n");
    set_race_name("smith");
    set_gender(0);
    set_introduce(1);
    default_config_mobile(80);
    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alignment(0);
    set_knight_prestige(-5);

    add_prop(OBJ_M_NO_ATTACK, 1);

    ALWAYSKNOWN;
}
