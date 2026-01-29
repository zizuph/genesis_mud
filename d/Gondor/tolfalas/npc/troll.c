/*
 * 12 Aug 2006 - Palmer
 *
 *
 *
 */

#include "/d/Gondor/private/gondor_admin.h"
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

inherit "/std/monster";
inherit "/lib/unique";


void add_stuff ();

void
create_monster()
{
   if (!IS_CLONE)
      return;

    set_name("throg");
    set_living_name("throg");
    set_race_name("troll"); 
    set_adj(({"ugly","smelly"}));
    set_long("@@my_long");
    add_prop(CONT_I_WEIGHT,67000);   /*  67 Kg */
    add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
    add_prop(LIVE_I_QUICKNESS, 150); /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK,	10); /* Night vision. */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 80+random(20));
    set_skill(SS_WEP_AXE, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));
    set_skill(SS_PARRY, 80+random(20));
    set_skill(SS_BLIND_COMBAT, 80+random(20));
    set_skill(SS_AWARENESS, 80+random(20));
    set_skill(SS_DEFENCE, 80+random(20));

    set_aggressive(1);
    set_attack_chance(1);
    set_alignment(-900);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(5);
    set_act_time(5);

    add_act("emote growls: What do you think you are?");
    add_act("emote snarls: Would you like to get passst me?");
    add_act("emote snarls defiantly at you.");

    set_cchat_time(5);
    add_cact("emote snarls at you.");
    add_cact("emote growls: I'll smash you!");
    add_cact("emote works himself into a battle-frenzy!");
    add_cact("emote attacks with renewed strength.");

    set_alarm (0.0, 0.0, &add_stuff());
    TELL_ADMIN("Throg cloned at " + ctime(time()));

}


my_long()
{
    if (notmet_me(this_player())) this_player()->add_introduced("throg");
    return "This is an ugly and defiant troll, the leader of " +
        "the orcs and trolls who patrol the ruins of Tolfalas island.\n";
}


void
add_stuff()
{
    object bracelet, wep, arm;   
    FIXEUID;

    // bracelet = clone_object("/d/Gondor/tolfalas/arm/bracelet");
    // bracelet -> move(this_object());
    wep = clone_object("/d/Gondor/tolfalas/wep/axe");
    wep -> move(this_object());
   
    command("wield weapon");
}


void
do_die(object killer)
{
    command("emote slams face-first into to the ground with a loud thump!");
    ::do_die(killer);
    log_file("throg", capitalize(killer->query_real_name()) +
        " killed the troll Throg in Tolfalas on " + ctime(time())+ ".\n");
}


void
attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[Throg attacked by " + ob->query_cap_name() + 
        "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
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
	pen = 800 + random(200);
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
	  " snarls at you, then takes a vicious " + attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

    tell_room(E(TO), QCTNAME(TO) + " snarls at " + QTNAME(enemy)
	  + " and takes a lightning-fast " + attack[att] + " at "
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
