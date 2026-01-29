/*
 * Ergothian captain of a ship in the Turbidus Sea.
 *
 * Arman, January 2021.
 */

#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE
inherit AUTO_TEAM
inherit "/lib/unique";
inherit "/d/Krynn/std/equip";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#define WEP1   TOBJ + "boarding_axe"
#define WEP2   TOBJ + "phoenix_axe"
#define ARM1   "/d/Ansalon/balifor/flotsam/obj/armour/bandana1"
#define ARM2   "/d/Ansalon/balifor/flotsam/obj/armour/shirt"
#define ARM3   "/d/Ansalon/balifor/flotsam/obj/armour/jerkin"
#define RING1  TOBJ + "ring_of_swimming"
#define RING2  TOBJ + "ring"
#define MONEY  ({ 0, 4, 8, 0 })
#define KEY    TOBJ + "ergothian_key"

#define ATTACKED_ERGOTHIANS "_attacked_ergothian_sailors"

void
create_krynn_monster()
{
    set_pick_up_team(({"_ergothian_sailor"}));
    set_max_team_size_auto_join(20);

    set_name("geral");
    add_name("captain");
    set_living_name("geral");
    set_title("of Ergoth, Sea Captain of the 'Tears of the Rose'");
    set_race_name("human");
    set_adj("powerful");
    add_adj("dark-skinned");
    set_short("powerful dark-skinned captain");
    set_gender(G_MALE);
    set_long("Before you stands a powerful dark-skinned human from " +
        "the northern isle of Ergoth, the captain of this vessel. " +
        "He commands this galleon with a firm fist. By the looks of him, " +
        "he seems no novice in either negotiations or in battle.\n");

    set_stats(({180, 160, 220, 150, 150, 160}));
    
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_ACROBAT, 100);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_SPELLCRAFT, 20);

    add_prop(CONT_I_HEIGHT, 200 + random(10));
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    add_prop(OBJ_M_HAS_MONEY, MONEY);

    set_alignment(0);
    set_knight_prestige(0);

    set_act_time(12);
    add_act("say The high seas can be dangerous! Full of buccaneers and " +
        "pirates!");
    add_act("say Pirates are bad, but those cursed Sea Nomads are worse!");
    add_act("say This cargo must make it back to Ergoth!");
    add_act("say I don't have a lot of sympathy for the Solamnian knights " +
        "and their troubles with their peasants!");

    set_cact_time(12);
    add_cact("shout I'll go down with my ship!");
    add_cact("emote narrows his eyes threateningly.");
    add_cact("say You'll be fishbait before long!");

    set_introduce(1);
    set_all_hitloc_unarmed(65);

    // Good natural armour and a special attack
    set_exp_factor(135);

    equip(({ clone_unique(WEP2, 15, WEP1), 
        WEP1, ARM1, ARM2, ARM3,
        clone_unique(RING1, 10, RING2), KEY }));

}

int
special_attack(object enemy)
{
    int attacktype, pen, att, wloc;

    mixed hitres;

    string *hitloc, *attack, how, weapon;

    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"swipe","swing"});

    weapon = query_weapon(-1)[0]->query_short();

    // Activate the phoenix axe if the captain has it.
    command("praise habbakuk");

    if (attacktype == 1)
    {

        pen = query_pen_by_stat(TO->query_average_stat());
        hitres = enemy->hit_me(query_pen_by_stat(TO->query_average_stat()) 
            + random(600));

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " barely missing";
	if(hitres[0] > 0)
	    how = "his " + weapon + " lightly grazing";
	if(hitres[0] > 10)
	    how = "his " + weapon + " cutting";
	if(hitres[0] > 20)
	    how = "his " +weapon+ " slashing";
	if (hitres[0] > 40)
	    how = "his " + weapon + " badly wounding";
	if (hitres[0] > 60)
	    how = "his " + weapon + " lethally injuring";

	enemy->catch_msg(QCTNAME(TO) + 
            " takes a mighty " +attack[att]
            + " at you, " + how + " your " + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " takes a mighty " +attack[att]+ 
            " at " +QTNAME(enemy) + ", " +how+ " " +POSSESSIVE(enemy)
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
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_ERGOTHIANS))
        ob->add_prop(ATTACKED_ERGOTHIANS, 1);
}

void
attack_enemy_again(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        return;
    }

    command("say Repel the boarders! To arms!");
    command("kill " +enemy->query_name());
    return;
}

void
attack_enemy(object enemy)
{
    if(objectp(TO->query_attack()))
        return;

    if(!CAN_SEE(TO, enemy))
    {
        set_alarm(6.5, 0.0, &attack_enemy_again(enemy));
        return;
    }

    command("say Repel the boarders! To arms!");
    command("kill " +enemy->query_name());
    return;
}

void
init_living()
{
    if(this_player()->query_prop(ATTACKED_ERGOTHIANS))
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));

    init_team_pickup();
    ::init_living();
}

