#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/sabre"
#define ARM2  FOBJ + "armour/shirt"
#define ARM1  FOBJ + "armour/bandana3"
#define M1 MONEY_MAKE_SC(5)->move(TO);
#define M2 MONEY_MAKE_GC(1)->move(TO);

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("corsair");
    set_short("menacing corsair");
    set_race_name("human");
    set_long("You look upon a typical pirate that sails " +
      "the Bloodsea. He looks like he would be quite happy " +
      "to tear your heart out if it wasn't for the fact that " +
      "you are passengers on this ship.\n");
    set_stats(({50,50,50,50,50,50}));
    set_hp(10000);

    set_skill(SS_WEP_SWORD, 35);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 30);

    set_alignment(0);
    set_knight_prestige(1);

    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("shout All hail captain Hull, the Pirate Lord!");
    add_act("say Damn land lubbers. We should chuck you " +
      "overboard and get back to piracy!");
    add_act("emote looks at you greedily, as if considering " +
      "robbing you.");
    add_act("spit");
    add_act("emote stretches his tanned muscles.");
    add_act("twinkle danger");

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
