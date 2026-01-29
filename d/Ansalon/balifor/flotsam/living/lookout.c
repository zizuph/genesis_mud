#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE
inherit "/lib/unique";

#define WEP FOBJ + "weapon/cutlass"
#define ARM2  FOBJ + "armour/shirt"
#define ARM1 FOBJ + "armour/elven_cloth"
#define ARM3 FOBJ + "armour/jerkin"

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("mariner");
    set_short("vigilant mariner");
    set_race_name("human");
    set_long("This is the Golden Lions' lookout, who watches " +
      "from the crows' nest for land, storms, and other ships.\n");
    set_stats(({90,90,90,90,90,90}));
    set_hp(10000);

    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 45);
    set_skill(SS_DEFENCE, 30);

    set_alignment(0);
    set_knight_prestige(1);

    set_act_time(5);
    add_act("shout Ship ahoy!");
    add_act("say Hmm, looks like a storm is approaching.");
    add_act("emote peers far out to sea.");
    add_act("shout Captain! Dragonarmy ship approaching " +
      "fast! Man the ballistas, prepare for boarders!");

}

void
arm_me()
{
    object bandana;

    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);

    if (random(2))
    {
        bandana = clone_unique(ARM1, 10, FOBJ + "armour/bandana4");
    }
    else
    {
        bandana = clone_object(FOBJ + "armour/bandana4");
    }
    bandana->move(TO, 1);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    command("wear all");
    command("wield all");
}
