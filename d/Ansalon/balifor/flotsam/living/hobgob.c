#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP "/d/Krynn/solamn/splains/obj/bmace"
#define ARM "/d/Krynn/solamn/splains/obj/barmour3"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("hobgoblin");
    set_short("scarred hobgoblin");
    set_race_name("hobgoblin");
    set_long("This angular-faced fanged horror is one of the many " +
      "hobgoblins that have been attracted to the Highlords armies. " +
      "This one is at present guarding one of the army's warehouses. \n");

    set_stats(({50,45,50,36,36,36}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 35);
    set_skill(SS_DEFENCE, 35);
    set_skill(SS_PARRY, 15);

    set_alignment(-200);
    set_knight_prestige(85);

    set_act_time(5);
    add_act("say Smeggin wunderbul! More nosy peepels!");
    add_act("say Hey! Scitch yoo!");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
    clone_object(ARM)->move(this_object(),1);
    command("wear all");
}
