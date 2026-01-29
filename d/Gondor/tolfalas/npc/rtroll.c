/*
 * 25 Sept 2006 - Toby
 *
 * 26 Sept 2006, Toby: Modified the special_attack
 *                     Added support to wander around the ruins
 *
 */

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
    set_race_name("troll"); 
    set_adj(({"ugly","stinking"}));
    set_gender(G_NEUTER);
    set_scar(8);

    set_long("One of the many ugly stinking trolls inhabiting the ruins of Tolfalas.\n");

    add_prop(CONT_I_WEIGHT,150000);   /*  150 Kg */
    add_prop(CONT_I_HEIGHT,210);     /* 210 cm */
    add_prop(LIVE_I_QUICKNESS, 135); /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK,	10); /* Night vision. */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25), 
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 80+random(20));
    set_skill(SS_WEP_CLUB, 80+random(40));
    set_skill(SS_DEFENCE, 80+random(20));
    set_skill(SS_PARRY, 60+random(30));
    set_skill(SS_BLIND_COMBAT, 80+random(20));
    set_skill(SS_AWARENESS, 50+random(20));
    set_skill(SS_DEFENCE, 70+random(20));

    set_attack_unarmed(W_SLASH, 35, 45, W_SLASH, 30, "right hand claws");
    set_attack_unarmed(W_SLASH, 35, 45, W_SLASH, 30, "left hand claws");

    set_aggressive(1);
    set_attack_chance(60+random(25));
    set_alignment(-700);

    set_chat_time(200);
    set_act_time(150);

    add_act("emote growls: Whayou think youu are?");
    add_act("emote booms: Mi smack youuu head wit mi club!");
    add_act("emote booms: Mi club hurt youuu head!");
    add_act("emote laughs a booming laugh as it looks at you fingering the spikes of its club");
    add_act("emote snarls defiantly at you.");

    set_cchat_time(25);
    add_cact("emote snarls at you.");
    add_cact("emote growls: Me smash you!");
    add_cact("emote works himself into a battle-frenzy!");
    add_cact("emote attacks with renewed strength.");

    set_alarm (0.0, 0.0, &add_stuff());

    set_random_move(30);
    set_restrain_path(TOLFALAS_DIR + "room/ruins");
    set_monster_home(TOLFALAS_DIR + "room/ruins_control.c");
}

void
add_stuff()
{
    object wep, arm;   
    FIXEUID;

    wep = clone_object("/d/Gondor/tolfalas/wep/bandedclub");
    wep -> move(this_object());
   
    command("wield weapon");
}


void
do_die(object killer)
{
    command("emote falls heavily to to the ground with a loud thump!");
    ::do_die(killer);

}


void
attacked_by(object ob)
{
    object *arr;

    command("roar");

    ::attacked_by(ob);
}


int
special_attack(object victim)
{
    int    attacktype,
           pen,
           att,
           wloc;

    mixed  hitres;

    string *sHitloc,
           *sAttack,
           sHow,
           sWeapon;


    if (!sizeof(query_weapon(-1)))
	return 0;

    sHitloc = ({"left arm","right arm","body","left leg","right leg"});
    sAttack = ({"hit", "swing", "swipe", "strike", "stroke", "lunge"});

    sWeapon = query_weapon(-1)[0]->query_short();

    attacktype = random(8);

    if (attacktype == 1)
    {
        pen = 80;
        hitres = victim->hit_me(pen, W_SLASH, TO, -1);

        wloc = random(5);

        if (hitres[0] <= 0)
            sHow = "luckily missing";
        if(hitres[0] > 0)
            sHow = "lightly grazing";
        if(hitres[0] > 10)
            sHow = "pounding a shallow wound in";
       	if(hitres[0] > 20)
            sHow = "cutting a gash across";
       	if (hitres[0] > 40)
            sHow = "tearing a deep gash into";
        if (hitres[0] > 60)
            sHow = "ripping skin and flesh from";

        victim	->catch_msg(QCTNAME(TO) + 
          " snarls, taking another swing with its " +sWeapon+ 
          " at you. The spikes of the club " + sHow + " your " + 
          sHitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " snarls, taking another " +
          "swing with its " +sWeapon+ " at " + QTNAME(victim) + 
          ". The spikes of the club " + sHow + HIS_HER(victim) + 
          " " + sHitloc[wloc] + ".\n", ({ victim, TO }));

        if (victim->query_hp() <= 0)
        {
            victim->command("scream");
            victim->do_die(TO);
            command("laugh mercil");
        }
    }

    return 0;
}
