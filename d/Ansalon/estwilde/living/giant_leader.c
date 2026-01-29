#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

#define WEP1 WEP + "frost_axe"

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

    set_pick_up_team(({"giant"}));
    set_max_team_size_auto_join(11);

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

    set_stats(({350, 100, 300, 40, 30, 100}));
    set_intoxicated(1000);
    set_hp(10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-450);
    set_knight_prestige(50);

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 10);

    set_all_hitloc_unarmed(40);

    set_act_time(10);
    add_act("shout Kill me bruddah! I whoop dem dwarves!");
    add_act("shout Dwarves! Me whoop you hard!!!");
    add_act("emote fumes about the death of his brother.");
    add_act("shout I'll flatten the lot of ya!");

    set_cact_time(0);
    add_cact("say Eat axe!");


    start_patrol();
    set_patrol_time(20);
    set_patrol_path(({"e","e","e","se","se","ne",
	"ne","se","e","se","ne",5,"kill clan_guard","shout For me bruddah!",
	700,"shout Me flatten yur Delving!","e","e","se",
	"say Iron Delving! Over da brudge!","kill guard",400,"se","se",
	"se","se","kill guard",700}));
    disable_patrol_loop();
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    command("wield all");

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
