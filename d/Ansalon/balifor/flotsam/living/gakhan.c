#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <wa_types.h>

inherit BOZAK;
inherit "/lib/unique";

#define WEP1 "/d/Ansalon/balifor/flotsam/obj/weapon/draco_dagger"
#define WEP2 "/d/Ansalon/balifor/flotsam/obj/weapon/long_dagger"
#define ARM1 ARMOUR + "barmour1"
#define ARM2 ARMOUR + "bleggings"
#define ARM3 ARMOUR + "bheavyboots"
#define ARM4 ARMOUR + "brobe"
#define ARM5 ARMOUR + "bhelmet"

void
create_bozak()
{
    if (!IS_CLONE)
	return;

    arm_draconian_called = 1;
    /* Necessary so that Gakhan does not automatically wield
    standard draconian equipment */

    set_name("gakhan");
    set_race_name("draconian");
    set_adj("hooded");
    set_title("the Dark Lady's military aide");
    set_long("This hooded draconian seems just like any " +
      "other draconian, with large clawed hands and scaly " +
      "skin. Its robe hides its small leathery wings. Yet " +
      "there the similarities stop. Its glittering black " +
      "eyes betray an unusual intelligence, and its calm " +
      "relaxed stance reveals a confidence only seen in " +
      "experienced warriors. \n");

    set_stats(({90,160,120,110,100,110}));
    set_alignment(-800);
    set_gender(G_MALE);
    set_knight_prestige(600);

    set_act_time(10);
    add_act("emote appraises you from the shadows of its " +
      "hood, its black reptilian eyes glittering.");
    add_act("emote moves into the shadows of its robe.");
    set_cact_time(1);
    add_cact("emote snarls: Die then fool!");
    add_cact("says I shall be rewarded greatly for " +
      "slaying you!");


    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_AWARENESS, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    trig_new("%w 'introduces' %s","react_to_intro");
}

/*
 * Function name: special_draconian_attack
 * Description:   Called from the draconian special_attack
 *                routine. By redefining this, draconians can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 */
public int
special_draconian_attack(object enemy)
{
    int    attacktype,
    pen,
    wloc;

    mixed  hitres;

    string *hitloc,
    how,
    weapon;

    if(!random(3))
    {
        command("cast arcanisvaes");
        tell_room(environment(TO), QCTNAME(TO) + " slowly " +
            "raises " + TO->query_possessive() + " clawed hand.\n");
        return 1;
    }

    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({ "left arm", "right arm",
      "body", "left leg", "right leg" });

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 400 + random(200);

	hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);

	wloc = random(5);

	if (hitres[0] <= 0)
	    how = "its " + weapon + " just missing";
	if (hitres[0] > 0)
	    how = "its " + weapon + " barely nicking the skin of";
	if (hitres[0] > 10)
	    how = "sinking the tip of its " + weapon + " into";
	if (hitres[0] > 20)
	    how = "its " + weapon + " penetrating";
	if (hitres[0] > 40)
	    how = "thrusting its " + weapon + " deeply into";
	if (hitres[0] > 60)
	    how = "almost burying its " + weapon + " to the hilt in";

	enemy->catch_msg(QCTNAME(TO) + " sidesteps your defences "
	  + "and stabs viciously at you, " + how + " your " 
	  + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO)+ " sidesteps " +QTNAME(enemy)
	  + "'s defences and stabs viciously at " + OBJECTIVE(enemy)
	  + ", " + how + " " + POSSESSIVE(enemy) + " " + hitloc[wloc]
	  + ".\n", ({ enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }

    return 0;
}

void
react_to_intro(string who, string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who, E(TO)))
    {
	command("introduce myself");
    }
}


void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_unique(WEP1, 5, WEP2)->move(this_object(),1); 
    command("wield all");

    clone_object(ARM1)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    clone_object(ARM4)->move(this_object(),1);
    clone_object(ARM5)->move(this_object(),1);
    command("wear all");

}
