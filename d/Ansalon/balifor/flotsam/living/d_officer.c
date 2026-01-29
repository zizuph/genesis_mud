/* Being a quest item and not terribly powerful, I have
 * increased spawn rate of knight magical sword.
 * Arman, December 2017
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE
inherit "/lib/unique";

#define PLAYER_I_KILLED_KERNAN  "_player_i_killed_flotsam_kernan"

#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/ksword"
#define WEP2 "/d/Ansalon/common/wep/sword/longsword3" 
#define ARM1 ARMOUR + "bdragonarm"
#define ARM2 ARMOUR + "bdragonhelm"
#define ARM3 ARMOUR + "bheavyboots"
#define ARM4 ARMOUR + "blargeshield"
#define ARM5 ARMOUR + "bshinguard"
#define ARM6 FOBJ + "/armour/bplatemail"


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("kernan");
    set_living_name("kernan");
    set_title("the Elite Officer of the Blue Dragonarmy");
    set_race_name("human");
    set_adj("cruel");
    add_adj("ruthless");
    set_gender("G_MALE");
    set_long("Before you stands an elite Dragon officer " +
      "of the Blue Lady's army. His calloused hands and muscular " +
      "frame show him to be an experienced warrior, and his almost " +
      "scarless body would make him out to be a good one at that. \n");

    set_stats(({160,160,160,130,130,130}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(-1200);
    set_knight_prestige(1200);
    set_act_time(12);
    add_act("say I wonder when Kitiara will return?");
    add_act("emote paces restlessly.");
    add_act("grin");

    set_cact_time(5);
    add_cact("emote roars: Die then scum!");
    add_cact("twinkle dangerous");
    add_cact("growl");

    add_ask(({"sword","broadsword","solamnian sword","solamnian " +
	"broadsword"}),"say Ha! Spoils of war!",1);
    add_ask(({"highlord","kitiara"}),"say Whats it to you scum?",1);
    add_ask("tanis","say Never heard of him",1);
    add_ask(({"berem","green gemstone man","gemstone man"}),
      "say There is a great reward for those who find him...",1);

    trig_new("%w 'introduces' %s","react_to_intro");
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
    how,
    weapon;


    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"thrust", "swing"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 400 + random(200);
	hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " barely missing";
	if(hitres[0] > 0)
	    how = "his " + weapon + " lightly grazing";
	if(hitres[0] > 10)
	    how = "his " + weapon + " slicing a shallow wound in";
	if(hitres[0] > 20)
	    how = "his " + weapon + " cutting a gash across";
	if (hitres[0] > 40)
	    how = "his " + weapon + " cutting a deep gash into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " lethally injuring";

	enemy->catch_msg(QCTNAME(TO) + 
	  " salutes you mockingly, then makes a vicious " + attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " salutes " + QTNAME(enemy)
	  + " mockingly, then makes a vicious " + attack[att] + " at "
	  + OBJECTIVE(enemy) + ", " + how + " " + POSSESSIVE(enemy)
	  + " " + hitloc[wloc] + ".\n", ({ enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }

    return 0;
}


void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_unique(WEP, 25, WEP2)->move(this_object(),1);
    command("wield all");

    if(random(4) == 1)
	clone_object(ARM1)->move(this_object(),1);
    else
	clone_object(ARM6)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    clone_object(ARM4)->move(this_object(),1);
    clone_object(ARM5)->move(this_object(),1);
    command("wear all");
}


public void
do_die(object killer)
{
    killer->add_prop(PLAYER_I_KILLED_KERNAN, 1);

    ::do_die(killer);
}

