#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/b_pin"
#define ARM2  FOBJ + "armour/shirt"
#define ARM1  FOBJ + "armour/bandana2"
#define M1   MONEY_MAKE_CC(10)->move(TO);
#define M2 MONEY_MAKE_SC(2)->move(TO);

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("mariner");
    set_short("surly mariner");
    set_race_name("human");
    set_long("This mariner does not look too pleased about " +
      "becoming a crew member of a passenger ship. You believe " +
      "he would much rather rob you than anything else.\n");
    set_stats(({40,40,40,40,40,40}));
    set_hp(10000);

    set_skill(SS_WEP_CLUB, 25);
    set_skill(SS_DEFENCE, 30);

    set_alignment(0);
    set_knight_prestige(1);

    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("emote sings loudly:\n     Hoorah for the pirate " +
      "Lord! Hoorah! Hoorah for the pirate Lord!\n     It is, " +
      "it is, a glorious thing to be a pirate Lord!\n");
    add_act("shout All hail Captain Hull, the Pirate Lord!");
    add_act("say Damn land lubbers. We should chuck you " +
      "overboard and get back to piracy!");
    add_act("emote looks at you greedily, as if considering " +
      "robbing you.");
    add_act("spit");

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
