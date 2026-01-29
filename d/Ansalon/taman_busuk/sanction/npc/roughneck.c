#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
#define CLAW "/d/Krynn/icewall/plains/obj/claw"
#define DRAUGHT SOBJ + "draught_of_doom"
#define MONEY 100 + random(1000)

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("roughneck");
    set_adj("pugnosed");
    set_short("pugnosed roughneck");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("This large solid man is the taverns roughneck. He sits at " +
      "the bar, occasionally scowling around, looking for any target " +
      "of his cruel nature.\n");

    set_stats(({120,120,120,70,70,70}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(OBJ_M_HAS_MONEY, MONEY);

    set_all_hitloc_unarmed(40);

    set_alignment(-50);
    set_knight_prestige(40);
    set_act_time(0);
    add_act("emote scowls into his beer.");
    add_act("emote pounds a meaty fist into the bar and orders another drink.");
    add_act("emote snarls: What are you looking at wimp?");

    set_cact_time(0);
    add_cact("twinkle dangerous");
    add_cact("shout I'll bash you good!");
    add_cact("say Eat this scumbag!");
    add_cact("growl");

    add_ask(({"quest","task","help","tour"}),
      "The pugnosed roughneck says: Ha! What do I look like? " +
      "A quest master? Get out of my face " +
      "before I bash yours!\n");
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how;

    attacktype = random(5);

    hitloc = ({"face","stomach","left shoulder","right shoulder","jaw"});

    attack = ({"swings", "jabs"});


    if (attacktype == 1)
    {
	pen = 400 + random(200);
	hitres = enemy->hit_me(pen, 25, TO, -1);

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "just missing";
	if(hitres[0] > 0)
	    how = "just touching";
	if(hitres[0] > 10)
	    how = "bruising";
	if(hitres[0] > 20)
	    how = "bashing";
	if (hitres[0] > 40)
	    how = "powerfully slamming";
	if (hitres[0] > 60)
	    how = "absolutely smashing";

	enemy->catch_msg(QCTNAME(TO) + 
	  " " + attack[att]+ " at you with his meaty fist, " +how+
	  " your " +hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO)+ " " +attack[att]+ " at "+
	  QTNAME(enemy)+ " with his meaty fist, " +how+
	  " " +HIS(enemy)+ " " +hitloc[wloc] + ".\n", ({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }

    return 0;
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(CLAW)->move(TO,1);
    command("wear all");
    clone_object(DRAUGHT)->move(TO,1);
    clone_object("/d/Ansalon/taman_busuk/sanction/obj/picks")->move(TO, 1);
}
