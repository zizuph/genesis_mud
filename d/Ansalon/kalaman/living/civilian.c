#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

string *gAdj1 = ({"burly","sullen","handsome","excited",
  "preoccupied","friendly","jovial","red-faced",
  "ugly","big-eared","big-nosed","tall","short","fat"});
string *gAdj2 = ({"black-bearded","clean-shaven","square-jawed",
  "young","sober","black-skinned","hairy","blue-eyed",
  "brown-eyed","thoughtful"});

#define sX 40 + random(15)
#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("civilian");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_short(implode(query_adjs()," ") + " human");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("This " +short()+ " is one of the many citizens of Kalaman " +
      "wandering the streets and market area.\n");

    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_hp(10000);

    set_alignment(200);
    set_knight_prestige(-3);
    add_prop(CONT_I_WEIGHT, 60000 + random(15000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));
    set_skill(SS_WEP_SWORD, 20 + random(20));
    set_skill(SS_DEFENCE, 5 + random(20));
    set_skill(SS_AWARENESS, 10 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, 61);

    set_act_time(40);
    add_act("say I have heard rumours the dragonarmy is approaching");
    add_act("grin");
    add_act("spit");
    add_act("say Not too bad a day today.");
    add_act("say I am glad kender are not allowed in the city, " +
      "otherwise our city would be looted quicker " +
      "than a goblin raid.");
    add_act("say Apparantly there is a clan of " +
      "gully dwarves living in the city sewers... " +
      "truly that is a sign that things cannot get " +
      "any worse.");


}

void
arm_me()
{

    seteuid(getuid(TO));

    if(random(3) == 1)
	clone_object("/d/Ansalon/balifor/flotsam/obj/weapon/lsword")->move(TO);
    if(random(4) == 1)
	clone_object(KOBJ + "armour/shirt")->move(TO);
    if(random(4) == 1)
	clone_object(KOBJ + "armour/cap")->move(TO);
    command("wield all");
    command("wear all");
}

#include "civilian_funcs.h"

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
