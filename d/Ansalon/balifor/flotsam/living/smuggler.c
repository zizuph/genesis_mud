#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/b_pin"

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("smuggler");
    set_race_name("human");
    set_short("shifty smuggler");
    set_long("This rugged sailor is one of the many pirates " +
      "who sail the Bloodsea as a smuggler of goods and " +
      "people.\n");

    set_aggressive(1);
    set_stats(({50,50,50,50,50,90}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_PARRY, 30);

    set_alignment(0);
    set_knight_prestige(10);

    set_act_time(0);
    add_act("frown");
    add_act("scowl");
    add_act("say ... at midnight then.");

}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
}
