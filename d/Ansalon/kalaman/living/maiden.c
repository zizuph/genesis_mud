#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

#define sX 10 + random(15)
#define M1  MONEY_MAKE_CC(random(13))->move(TO)
#define M2  MONEY_MAKE_SC(random(7))->move(TO)

string *gAdj1 = ({"cranky","happy","sly","flirtatious",
  "thoughtful","solemn","anxious","curious","beautiful",
  "cute","ugly","wart-faced","comely","pretty",
  "charming","fair","friendly","lovely","ordinary"});

string *gAdj2 = ({"young","tall","petite","old","plump",
  "blond-haired","dark-skinned","blue-eyed","voluptuous",
  "red-headed","raven-haired","long-haired"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("maiden");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_short(implode(query_adjs()," ") + " maiden");
    set_race_name("human");
    set_gender(1);  /*female for the idiots */
    set_long("This " +short()+ " is one of the many citizens of Kalaman " +
      "wandering the streets and market area.\n");

    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_hp(10000);

    set_alignment(200);
    set_knight_prestige(-3);
    set_skill(SS_WEP_SWORD, 20 + random(20));
    set_skill(SS_DEFENCE, 5 + random(20));
    set_skill(SS_AWARENESS, 10 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 180 + random(10));
    add_prop(CONT_I_WEIGHT, 49000 + random(5000));

    set_act_time(50);
    add_act("say Lord Calof is so handsome.");
    add_act("wink");
    add_act("curtsey");
    add_act("say Now what was I to get from the market?");
    add_act("emote fusses with her hair.");
    add_act("say The Knights of Solamnia look " +
      "quite dashing on their horses, wouldn't you agree?");
    add_act("giggle");


}

void
arm_me()
{

    seteuid(getuid(TO));

    clone_object(KOBJ + "armour/dress")->move(TO);
    M1;
    M2;
    command("wield all");
    command("wear all");
}

#include "maiden_funcs.h"

void
init_living()
{
    if(P("ansalon_sword_object",TP))
	set_alarm(1.0, 0.0, "greet_func1",TP);
    if(TP->query_knight_level())
	set_alarm(0.5, 0.0, "knight_greet",TP);
    if(TP->query_race_name() == "goblin" || TP->query_race_name() == "hobgoblin")
	set_alarm(1.0,0.0, "goblin_greet",TP);
    if(TP->query_race_name() == "hobbit")
	set_alarm(1.0,0.0, "hobbit_greet",TP);
    ::init_living();
}
