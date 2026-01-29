#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

#define WEP1 WEP + "frost_club"

string *gAdj1 = ({"gigantic","massive","huge",
  "ferocious","white-bearded","furious"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;


    set_name("giant");
    set_adj(ONE_OF(gAdj1));
    add_adj("frost");
    add_adj(ONE_OF(gAdj1));
    set_race_name("giant");
    set_short(ONE_OF(gAdj1) + " frost giant");
    set_long("Towering high above you is the fearsome " +
      "visage of a frost giant! Over twenty feet in height and " +
      "wider than you are tall, this savage monster is " +
      "a daunting foe indeed! Its skin looks as tough " +
      "as stone, and you are not sure how you are going to "+
      "defeat such a huge creature.\n");

    set_stats(({350, 100, 300, 40, 30, 200}));
    set_intoxicated(1000);
    set_hp(query_max_hp());
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 10);

    set_all_hitloc_unarmed(40);

    set_act_time(10);
    add_act("shout Deh kill yur bruddah? We squish em!");
    add_act("emote thinks about chomping dwarves.");
    add_act("say Me tell ya me cleaved an elf in " +
      "one chop? Did me?");
    add_act("say Elfs are pussies! Half-elfs are half-pussies!");

    set_cact_time(0);
    add_cact("say Chomp on dis scumbag!");
    add_cact("assist");


}


public int
query_max_hp()
{
    return 7500 + random(3500);
}


void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    command("wield all");

}

