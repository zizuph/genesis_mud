/*
 * Yagluk, the terrible imposing troll of Annuminas
 * Name suggested by Serif (thanks serif!)
 * -- Finwe, July 2002
 *
 * 2002/07/21 Last update
 * 2011/08/02 Lavellan - Made introduction more normal, fixed typos
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

inherit "/std/monster";
inherit "/lib/unique";
inherit KILL_LOGGER;

//void return_introduce();
//void react(object ob);
int intro_alarm;

void add_stuff ();

void
create_monster()
{
   if (!IS_CLONE)
      return;

    set_name("yagluk");
    add_name(({"captain"}));
    set_living_name("yagluk");
    set_race_name("troll"); 
    set_adj(({"ugly","defiant"}));
    set_long("@@my_long");
    add_prop(CONT_I_WEIGHT, 240000);   /*  240 Kg */
    add_prop(CONT_I_HEIGHT, 350);     /* 3.5 meters*/
    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK,	10); /* Night vision. */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 150+random(25), 
                 145+random(25), 
                 130+random(25), 
                 50+random(25), 
                 50+random(25), 
                 95+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 80+random(20));
    set_skill(SS_WEP_AXE, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));
    set_skill(SS_PARRY, 80+random(20));
    set_skill(SS_BLIND_COMBAT, 80+random(20));
    set_skill(SS_AWARENESS, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));

    set_aggressive(0);
    set_attack_chance(0);
    set_alignment(-900);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(5);
    set_act_time(5);

    add_act("emote growls: No one gets past me!");
    add_act("emote snarls: Are you here to challenge me?");
    add_act("emote snarls defiantly at you.");
    add_act("emote snarls: Get to work and get me something to eat, NOW!");
    add_act("emote growls: I have yet to be defeated by puny soldiers like you!");

    set_cchat_time(5);
    add_cact("emote snarls enraged at you.");
    add_cact("emote growls: You'll never leave here alive!");
    add_cact("emote works himself into a battlerage.");
    add_cact("emote attacks with renewed strength.");
    add_cact("pledge soul");

    add_stuff();

// log killers
    set_kill_log_name("yagluk");
   	set_kill_log_size(50000);
}


my_long()
{
    //if (notmet_me(this_player())) this_player()->add_introduced("yagluk");
    return "This is an ugly and defiant troll, the captain of those " +
//        "the orcs and trolls who patrol the ruins of Annuminas. He " +
        "orcs and trolls who patrol the ruins of Annuminas. He " +
        "looks imposing in his armours and weapons stolen from the " +
//        "castle but there are few who dare challenge him and live to " +
        "castle and there are few who dare challenge him and live to " +
        "tell about it.\n";
}


void
add_stuff()
{
    equip(({ 
        ANN_ARM + "gauntlets",
        ANN_ARM + "greaves",
        ANN_ARM + "pmail",
        clone_unique("/d/Shire/annuminas/wep/dbaxe", MAX_UNIQUE_ITEMS, "/d/Shire/annuminas/wep/dbaxel")
    }));
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

    attack = ({"hit", "swing", "swipe", "strike", "stroke", "lunge"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 1000 + random(200);
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
	  " mocks you, then takes a terrible " + attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " mocks " + QTNAME(enemy)
	  + " and takes a viscious " + attack[att] + " at "
	  + HIM_HER(enemy) + ", " + how + " " + HIS_HER(enemy)
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
init_living()
{
    if (this_player()->check_seen(this_object()) && 
        notmet_me(this_player()))
    {
        remove_alarm(intro_alarm);
        intro_alarm = set_alarm(itof(random(3))+1.0, 0.0,
            &command("introduce me"));
    }
}

string
query_presentation()
{
    return "Yagluk";
}
