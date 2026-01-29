#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "../guild/local.h"
#include <const.h>

inherit M_FILE

create_krynn_monster()
{
    set_name("lunitari");
    set_long("@@my_long");

    set_adj(({"red-robed", "hooded"}));

    set_race_name("spectral");
    default_config_mobile(500);
    set_all_attack_unarmed(40, 40);
    set_all_hitloc_unarmed(40);

    set_alignment(1200);
    set_knight_prestige(10000);

    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    set_gender(G_FEMALE);

    NEVERKNOWN;
}

public string
my_long()
{
    string str;

    if (THIS_GUILD(TP))
    {
        str = "You are looking at Lunitari, the daughter of Gilean, ";

	if (ADMIN->query_member_order(RNAME(TP)) == TYPE_RED)
	  str += "the God, whom you draw your magic powers from. ";
	else
	  str += "the God, whom the red robes draws their powers from. ";

	str += "She is wearing a red robe, red as the purest blood, " +
	  "with a large hood that covers Her face.\n";

	return str;
    }

    return "The spectral is dressed in a red robe, with a large hood " +
      "that covers its head. You can feel how it emits great powers.\n";
}




