#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

#define WEP "/d/Ansalon/goodlund/bloodsea/obj/sea_slayer"
#define WEP2 "/d/Ansalon/common/wep/sword/rapier" 
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"
#define SHIELD "/d/Ansalon/goodlund/bloodsea/obj/dr_turtle_shell"


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;


    set_pick_up_team(({"sailor"}));
    set_max_team_size_auto_join(6);

    set_name("magellan");
    set_living_name("magellan");
    set_title("the Drake of Saifhum, Captain of the Sloop-of-War, the 'Cormorant'");
    set_race_name("human");
    set_adj("powerful");
    add_adj("ebony-skinned");
    set_gender("G_MALE");
    set_long("Standing confidently on the deck of his ship, this man is the " +
       "captain of the sloop-of-war, the Cormorant. Standing almost seven " +
       "feet tall and powerfully built, this ebony-skinned hails from the " +
       "isle of Saifhum.\n");

    set_stats(({200,160,160,130,130,130}));
    set_hp(query_max_hp());

    set_all_hitloc_unarmed(50);

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(600);
    set_knight_prestige(-10);
    set_act_time(5);
    add_act("emote stands confidently on the deck of his ship.");
    add_act("emote stares at you appraisingly.");
    add_act("say Lads, this storm doesn't look like it will end any time " +
       "soon! We won't be seeing Saifhum for some time!");
    add_act("emote looks out towards the sea.");

    set_cact_time(0);
    add_cact("emote roars: Die then scum!");
    add_cact("twinkle dangerous");
    add_cact("growl");

    add_ask(({"saifhum", "home"}),"say Aye, Saifhum is a rugged land, full " +
        "of a rugged folk who love the sea! I am proud to call it my home!",1);


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
    clone_unique(WEP, 7, WEP2)->move(this_object(),1);
    clone_object(FARM + "shirt")->move(TO,1);
    clone_unique(SHIELD, 20, WEP2)->move(TO,1);

    command("wield all");

    if(random(3) == 1)
        clone_object(FARM + "elven_cloth")->move(TO,1);
    else
        clone_object(FARM + "bandana4")->move(TO,1);

    command("wear all");

    clone_object(BOBJ + "map_piece4")->move(TO,1);

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
