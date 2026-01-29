#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

string *gAdj1 = ({"strong","rugged-skin","dark-eyed",
                  "muscular","powerful","jovial","stern",
                  "ugly","scarred","barrel-chested","confident"});

#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/nice_clabbard"
#define SHIELD "/d/Ansalon/balifor/flotsam/obj/armour/nice_shield"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"sailor"}));
    set_max_team_size_auto_join(6);

    set_name("minotaur");
    set_race_name("minotaur");
    add_adj("tall");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " minotaur");
    set_gender("G_MALE");
    set_long("This minotaur corsair stands confidently on the deck " +
             "knowing he can take care of any trouble that might arise. "+
             "While others might stumble around the deck while the sea is high "+
             "you doubt this corsair won't lose his footing even slightly.\n");
    
    set_stats(({200,160,200,140,140,130}));
    set_hp(query_max_hp());

    set_all_hitloc_unarmed(50);

    add_prop(CONT_I_WEIGHT, 250000);
    add_prop(CONT_I_HEIGHT, 210);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(-500);
    set_knight_prestige(5);
    set_act_time(5);
    add_act("emote stands confidently on the deck of the ship.");
    add_act("emote stares at you appraisingly.");
    add_act("emote snorts: It looks like the storm will hit us anytime now. Prepare yourself lads.");
    add_act("emote looks out towards the sea.");

    set_cact_time(0);
    add_cact("emote snorts: By Sargas! I will feed you to the sharks!");
    add_cact("growl");
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

    attack = ({"slash", "swing"});

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
	  " balances himself expertly on the heaving deck, then makes a vicious " + attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " balances himself expertly on the heaving " +
	  "deck, then makes a vicious " + attack[att] + " at "
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
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(TO, 1);
    command("change grip");
    command("wield all");

    clone_object("/d/Ansalon/balifor/flotsam/obj/armour/chain")->move(TO,1);

    if(random(2))
        clone_object(SHIELD)->move(TO,1);
    command("wear all");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
