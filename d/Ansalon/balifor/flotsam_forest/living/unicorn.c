#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit AC_FILE
inherit "/std/act/attack";
inherit "/std/act/action";


void
create_creature()
{
    int i;

    set_name("unicorn");
    set_race_name("unicorn");
    set_adj("greater");

    set_gender(0);
    set_long("Before you stands a mythical creature, a greater unicorn! " +
      "This creature is believed to be one of the favoured children of " +
      "the god of nature, Chislev. They are known to protect blessed groves " +
      "from dire threats to nature.\n");

    set_stats(({185,225,200,140,140,180}));

    set_hp(10000);
    set_alignment(1200);
    set_knight_prestige(-2);

    add_prop(OBJ_I_WEIGHT, 700000);
    add_prop(OBJ_I_VOLUME, 450000);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(OBJ_I_RES_MAGIC, 40);

    set_skill(SS_DEFENCE, 80);  
    set_skill(SS_UNARM_COMBAT, 100);


    NEVERKNOWN;

    set_attack_unarmed(0, 50, 35, W_SLASH,  80, "hooves");
    set_attack_unarmed(1, 35, 80, W_IMPALE, 20, "ivory horn");

    set_hitloc_unarmed(1,  60, 90, "body");
    set_hitloc_unarmed(2, 20, 10, "head");

    add_leftover("/std/leftover","horn", 1, "", 0,0);

    set_act_time(10);
    add_act("emote rears up, its front hooves flashing out dangerously!");
    add_act("emote tosses its pure white mane.");
    add_act("emote stares at you with eyes full of intelligence and wisdom.");

    // Tough npc with nasty special attack.
    set_exp_factor(110);
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
	    how = "just missing";
	if(hitres[0] > 0)
	    how = "grazing the skin of";
	if(hitres[0] > 10)
	    how = "slicing deeply into";
	if(hitres[0] > 20)
	    how = "deeply penetrating";
	if(hitres[0] > 40)
	    how = "burying it deeply into";
	if(hitres[0] > 60)
	    how = "impaling";
	enemy->catch_msg(QCTNAME(TO)+ " lowers its head and charges at you " +
	  "with its dangerous ivory horn, " +how+ " your " +
	  hitloc[wloc]+ ".\n");
	tell_room(E(TO), QCTNAME(TO)+ " lowers its head and charges at " +
	  QTNAME(enemy)+ " with its dangerous ivory horn, " +
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
