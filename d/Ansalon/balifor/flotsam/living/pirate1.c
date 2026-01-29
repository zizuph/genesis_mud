#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/dirk"
#define ARM1 FOBJ + "armour/shirt"
#define ARM2 FOBJ + "armour/bandana1"
#define M1   MONEY_MAKE_CC(5)->move(TO);
#define M2   MONEY_MAKE_SC(1)->move(TO);

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("sailor");
    set_short("immoral sailor");
    set_race_name("human");
    set_long("This sailor has signed up to be a crew " +
      "member of the Golden Lion, a ship reknown throughout " +
      "the Courrain ocean as an infamous pirate vessel.\n");
    set_stats(({30,30,30,30,30,30}));
    set_hp(10000);

    set_skill(SS_WEP_KNIFE, 15);
    set_skill(SS_DEFENCE, 30);

    set_alignment(0);
    set_knight_prestige(1);

    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("emote sings loudly:\n" +
      "     Hoorah for the pirate Lord!\n     Hoorah! Hoorah " +
      "for the pirate Lord!\n     It is, it is, a glorious " +
      "thing to be a pirate Lord!");
    add_act("shout All hail Captain Hull, the Pirate Lord!");
    add_act("say Damn land lubbers. We should chuck you " +
      "overboard and get back to piracy!");

}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    command("wear all");
    command("wield all");
    M1
    M2
}
