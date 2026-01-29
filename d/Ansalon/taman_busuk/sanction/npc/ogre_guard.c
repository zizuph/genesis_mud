#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

string *gAdj1 = ({"warty","ugly","grey-skinned",
  "huge","giant","fat","bony"});
string *gAdj2 = ({"cruel","evil","brutal","depraved",
  "harsh","rugged","hungry"});

#define ARM1 "/d/Ansalon/balifor/flotsam/obj/armour/chain"
#define WEP1 SOBJ + "weapon/ogre_club"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("ogre");
    set_adj(ONE_OF(gAdj1));
    add_adj("elite");
    set_race_name("ogre");
    set_long("Standing over nine feet tall, this " +
      "is almost what you would call your average ogre. As with " +
      "most of its kind, this ogre is brutal, depraved, " +
      "and cruel, but the glimmer in its eyes suggests " +
      "exceptional cunning for its kind. That is probably " +
      "why this creature is being used as a guard for " +
      "Dragon Highlord Ariakas.\n");

    set_stats(({200, 80, 190, 70, 40, 100}));
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 50);

    set_act_time(1);
    add_act("assist ariakas");

    set_cact_time(0);
    add_cact("roar");
    add_cact("shout For the Emperor! Lord Ariakas!");
    add_cact("emote grins madly, his eyes a blaze with battlelust.");

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(ARM1)->move(TO,1);
    clone_object(WEP1)->move(TO,1);
    command("wield all");
    command("wear all");

}
