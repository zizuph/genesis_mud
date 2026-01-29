#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/cutlass"
#define ARM2  FOBJ + "armour/shirt"
#define ARM1 FOBJ + "armour/bandana4"
#define ARM3 FOBJ + "armour/jerkin"
#define M1   MONEY_MAKE_SC(15)->move(TO);
#define M2   MONEY_MAKE_GC(4)->move(TO);
#define PEARL "/d/Genesis/gems/obj/pearl"

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("buccaneer");
    set_short("muscular buccaneer");
    set_race_name("human");
    set_long("This muscular buccaneer looks like he has " +
      "worked as a sailor for many years. His muscular frame, " +
      "tanned body and confident stance clearly show that. " +
      "His cruel smile shows that he must really enjoy his " +
      "present occupation, that of a pirate on the Golden Lion.\n");
    set_stats(({60,60,60,60,60,60}));
    set_hp(10000);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 45);
    set_skill(SS_DEFENCE, 30);

    set_alignment(0);
    set_knight_prestige(1);

    set_act_time(0);
    add_act("scowl");
    add_act("emote tightens a rope at the commands of his " +
      "captain.");
    add_act("say Damn land lubbers. We should chuck you " +
      "overboard and get back to piracy!");
    add_act("emote looks at you greedily, as if considering " +
      "robbing you.");
    add_act("spit");
    add_act("emote snarls: You suck, I rule.");
    add_act("smile nast");

}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    command("wear all");
    command("wield all");
    M1
    M2

    if(random(3) == 1)
	clone_object(PEARL)->move(TO, 1);
}
