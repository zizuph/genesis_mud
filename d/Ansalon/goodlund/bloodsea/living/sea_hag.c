#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE


string *gAdj1 = ({"nasty","deceptive","hideous",
  "old","warty","green-hided"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;


    set_name("hag");
    set_adj(ONE_OF(gAdj1));
    add_adj("sea");
    add_adj(ONE_OF(gAdj1));
    set_race_name("troll");
    set_short(ONE_OF(gAdj1)+ " sea hag");
    set_gender(1);
    set_long("This tall hideous creature is a sea hag. Wretched and pure " +
       "evil, this monster is a hater of all beauty and will attempt to " +
       "destroy it anywhere it finds it. While appearing as frail, old, " +
       "withered women, their strength is truly amazing, rivalling that of " +
       "giants! So be wary, this one looks particularly nasty!\n");

    set_stats(({280, 200, 200, 140, 130, 150}));
    set_intoxicated(1000);
    set_hp(10000);
    set_aggressive(1);
    set_appearance_offset(50);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 5);

    set_alignment(-1200);
    set_knight_prestige(1000);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 10);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 70);

    set_all_hitloc_unarmed(40);

    set_act_time(18);
    add_act("cackle");
    add_act("emote shriek: Ah my pretties! Come taste my spiteful rage.");
    add_act("emote hisses: I smell sea-elves! Ah, such sweet morsels...");
    add_act("emote gags: Who dares enter my lair?");

    set_cact_time(12);
    add_cact("emote turns her hideous gaze upon you! You are overwhelmed " +
       "by her ghastly appearance!");

    seteuid(getuid());
    clone_object(BOBJ + "map_piece3")->move(TO);
    clone_object("/d/Krynn/common/scrolls/geyser_scroll")->move(TO, 1);
    command("wear all");
  
}


int
special_attack(object enemy)
{

    int attacktype, pen, wloc;
    mixed hitres;

    string *hitloc, how;

    attacktype = random(5);
    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if(attacktype == 1)
    {
	pen = 100 + random(500);
	hitres = enemy->hit_me(pen, 50, TO, -1);
	wloc = random(5);

	if(hitres[0] <= 0)
	    how = "her clawed talons just missing";
	if(hitres[0] > 0)
	    how = "her clawed talons grazing the skin of";
	if(hitres[0] > 10)
	    how = "her clawed talons slicing deeply into";
	if(hitres[0] > 20)
	    how = "her clawed talons deeply penetrating";
	if(hitres[0] > 40)
	    how = "burying her clawed talons deeply into";
	if(hitres[0] > 60)
	    how = "her clawed talons almost rendering";
	enemy->catch_msg(QCTNAME(TO)+ " reaches for you " +
	  "with amazing speed for such a withered creature, " +how+ " your " +
	  hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+
	  " reaches for " +QTNAME(enemy)+ " with amazing speed, " +
	  how+ " " +QTNAME(enemy)+ "'s"+
	  " " +hitloc[wloc] + ".\n", ({enemy,TO}));

	if(enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}
	return 1;
    }
    return 0;
}
