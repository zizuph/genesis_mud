#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit "/std/act/action";
inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

#define FOBJ "/d/Ansalon/balifor/flotsam/obj/"
#define WEP  BOBJ + "azure_spear"
#define WEP2 BOBJ + "trident"
#define ARM  BOBJ + "serpent_chain"


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"sea-elf"}));
    set_max_team_size_auto_join(6);

    set_name("osteichthyes");
    set_living_name("osteichthyes");
    set_title("the Prince of Deepshine Basin, True-blood of the Sea Elves");
    add_name("sea-elf");
    add_name("elf");
    set_race_name("sea-elf");
    set_adj("blue-skinned");
    set_adj("regal");
    set_gender(0);
    set_long("This blue-skinned elf with brilliant green eyes " +
      "is a creature of legends and childhood tales, a sea elf! "+
      "This one looks looks regal, and the other sea-elves seem to " +
      "treat him like nobility.\n");
    set_stats(({140, 200, 170, 200, 200, 150}));
    set_hp(10000);

    set_alignment(800);
    set_knight_prestige(-1);
    set_all_hitloc_unarmed(30); 

    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 85);

    set_act_time(15);
    add_act("emote swims playfully around the sea kelp.");
    add_act("emote bubbles: Be careful of the sunken cathedral, a nasty " +
      "sea hag lives there!");
    add_act("emote bubbles: Another vessel was lost at sea during the " +
      "last storm.");
    add_act("emote bubbles: Rumours speak of the return of the sea dragons.");

    set_default_answer("The sea elf indicates he doesn't know the answer to your question.\n");

    trig_new("%w 'introduces' %s","react_to_intro");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_unique(WEP, 9, WEP2)->move(this_object(),1);
    command("wield all");
    clone_object(ARM)->move(this_object(),1);
    command("wear all");
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
	    how = "his " + weapon + " jabbing a shallow wound in";
	if(hitres[0] > 20)
	    how = "his " + weapon + " piercing a wound in";
	if (hitres[0] > 40)
	    how = "his " + weapon + " piercing a deep wound in";
	if (hitres[0] > 60)
	    how = "his " + weapon + " lethally impaling";

	enemy->catch_msg(QCTNAME(TO) + 
	  " quickly lunges forward at you, " +how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " lunges forward at you, " +how+ " " +POSSESSIVE(enemy)
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
init_living()
{
    init_team_pickup();
    ::init_living();
}