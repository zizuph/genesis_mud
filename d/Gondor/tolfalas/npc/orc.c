/*
 * 25 Sept 2006 - Toby
 *
 * 26 Sept 2006, Toby: 
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
    set_race_name("orc"); 
    set_adj(({"ugly","stinking"}));
    set_gender(G_MALE);
    set_scar(random(8));

    set_long("One of the many ugly stinking orcs inhabiting the ruins of Tolfalas.\n");

    add_prop(CONT_I_WEIGHT,90000 + random(20000));   /*  90-110 Kg */
    add_prop(CONT_I_HEIGHT,150 + random(20));        /* 150-170 cm */
    add_prop(LIVE_I_QUICKNESS, 135);                 /* speed up attacks */
    add_prop(LIVE_I_SEE_DARK,	10);                 /* Night vision. */

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 100+random(25), 
                 90+random(25), 
                 150+random(30), 
                 75+random(25), 
                 75+random(25), 
                 150+random(25)} ));

    set_skill(SS_UNARM_COMBAT, 40+random(20));
    set_skill(SS_WEP_KNIFE, 70+random(30));
    set_skill(SS_DEFENCE, 60+random(20));
    set_skill(SS_PARRY, 60+random(10));
    set_skill(SS_BLIND_COMBAT, 40+random(20));
    set_skill(SS_AWARENESS, 30+random(20));

    set_aggressive(1);
    set_attack_chance(35+random(25));
    set_alignment(-600);

    set_chat_time(200);
    set_act_time(150);

    add_act("emote growls: Get lost!");
    add_act("emote growls mockingly: Think you can handle this?!");
    add_act("emote mockingly snarls: One step closer to death, that's you!");
    add_act("emote fondles his knife.");
    add_act("emote snarls defiantly at you.");

    set_cchat_time(25);
    add_cact("emote snarls at you.");
    add_cact("emote laughs with a mad touch and exclaims: Now you die!");
    add_cact("emote works himself into a battle-frenzy!");
    add_cact("emote attacks with renewed strength.");

    set_alarm (0.0, 0.0, &add_stuff());

    set_random_move(20);
    set_restrain_path(TOLFALAS_DIR + "room/ruins");
    set_monster_home(TOLFALAS_DIR + "room/ruins_control.c");
}

void
add_stuff()
{
    object wep, arm;   
    FIXEUID;

    wep = clone_object("/d/Gondor/tolfalas/wep/orcknife");
    wep -> move(this_object());
   
    command("wield weapon");
}


void
do_die(object killer)
{
    command("emote falls heavily to to the ground!");
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
    int    iDo_attack,
           iPen,
           iAtt,
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

    iDo_attack = random(8);

    if (iDo_attack == 1)
    {
        iPen = 60+random(20);
        hitres = victim->hit_me(iPen, W_SLASH, TO, -1);

        wloc = random(5);

        if (hitres[0] <= 0)
            sHow = "quite clumsily miss";
        if(hitres[0] > 0)
            sHow = "cut";
        if(hitres[0] > 10)
            sHow = "rip";
       	if(hitres[0] > 20)
            sHow = "cut a nasty wound in";
       	if (hitres[0] > 40)
            sHow = "tearing a deep wound into";
        if (hitres[0] > 60)
            sHow = "rather painfully and deep, cut";

        victim	->catch_msg(QCTNAME(TO) + 
          " growls at you as he turns the blade of the " +sWeapon+ 
          " making a back swing and manage to " + sHow + " your " + 
          sHitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " growls at "  + QTNAME(victim) +
          " as he turns the blade of the " +sWeapon+ " making a back " +
          "swing and manages to " + sHow +  HIS_HER(victim) + 
          " " + sHitloc[wloc] + ".\n", ({ victim, TO }));

        if (victim->query_hp() <= 0)
        {
            victim->command("sigh .");
            victim->do_die(TO);
            command("laugh mercil");
        }
    }

    return 0;
}
