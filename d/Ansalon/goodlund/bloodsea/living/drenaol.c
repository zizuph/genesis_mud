#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

#define WEP "/d/Ansalon/goodlund/bloodsea/obj/stun_axe"
#define WEP2 "/d/Ansalon/common/wep/axe/skelaxe" 
#define WEP3 "/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail"
#define PARROT "/d/Ansalon/guild/pirates/obj/parrot"


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"pirate", "minotaur"}));
    set_max_team_size_auto_join(6);

    set_name("drenaol");
    set_living_name("drenaol");
    set_title("the Black, Ruthless Pirate Captain of the Bloodsea of Istar");
    set_race_name("half-ogre");
    set_adj("huge");
    add_adj("ruthless");
    set_gender("G_MALE");
    set_long("This giant half-ogre towers over you menacingly, well aware how " +
       "daunting his powerful frame can be to others. His eyes gleam with malevolent " +
       "intelligence, and you have no doubt he is a scourge of every merchant that " +
       "sails the Bloodsea of Istar!\n");

    set_stats(({180,130,200,130,130,130}));
    set_hp(query_max_hp());
    set_all_hitloc_unarmed(40);

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 300);

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_2H_COMBAT, 60);

    set_alignment(-800);
    set_knight_prestige(200);

    set_act_time(7);
    add_act("say All hands to deck! Merchant vessel on the horizon!");
    add_act("grin");
    add_act("say Hull Nightstarr thinks he is the greatest pirate " +
      "to sail these seas... i'll show him!");
    add_act("emote roars furiously!");
    add_act("say What are ye doing on my ship, worm?");
    add_act("say Bocephus did what to a mule?");

    set_cact_time(0);
    add_cact("emote roars: Die then scum!");
    add_cact("twinkle dangerous");
    add_cact("growl");

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
    how;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"jabs", "swings"});

    if (attacktype == 1)
    {
	pen = 200 + random(200);
	hitres = enemy->hit_me(40, W_BLUDGEON, TO, -1);

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "his fist barely missing";
	if(hitres[0] > 0)
	    how = "his fist lightly grazing";
	if(hitres[0] > 10)
	    how = "his fist bruising";
	if(hitres[0] > 20)
	    how = "his fist badly bruising";
	if (hitres[0] > 40)
	    how = "his fist crushing";
	if (hitres[0] > 60)
	    how = "his fist fatally crushing";

	enemy->catch_msg(QCTNAME(TO) + 
	  " " + attack[att] + " at you, " + how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " " + attack[att] + " at "
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
    clone_unique(WEP3, 3, WEP2)->move(this_object(),1);
    clone_unique(WEP, 7, WEP2)->move(this_object(),1);
    command("wield all");

    clone_object(PARROT)->move(TO,1);
    clone_object("/d/Ansalon/goodlund/bloodsea/obj/map_piece2")->move(TO, 1);

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
