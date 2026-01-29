/*
 * Pirate captain of a ship in the high seas.
 *
 * Arman, February 2021.
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

#define WEP1   "/d/Ansalon/balifor/flotsam/obj/weapon/nice_clabbard"
#define ARM1   "/d/Ansalon/guild/pirates/obj/patch"
#define ARM2   "/d/Ansalon/balifor/flotsam/obj/armour/shirt"
#define ARM3   "/d/Ansalon/balifor/flotsam/obj/armour/jerkin"
#define MONK   "/d/Ansalon/guild/pirates/obj/monkey"

#define MONEY  ({ 0, 4, 8, 0 })

#define MINOTAUR_SOUL    "/d/Ansalon/guild/minotaurs/cmdsoul"
#define SS_GUILD_SPECIAL_SKILL   143015

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

string *gAdj1 = ({"muscular","sullen","one-eyed","huge",
  "evil","unfriendly","one-horned","black",
  "ugly","grey","merciless","tall","sturdy","grizzled"});

void get_me_soul();

int soul_id;

void
clone_guild_items()
{
    TO->add_cmdsoul(MINOTAUR_SOUL);
}

public string
query_guild_name_lay()
{
    return "Pirate of the Bloodsea";
}

void
create_krynn_monster()
{
    set_pick_up_team(({"_pirate_sailor"}));
    set_max_team_size_auto_join(20);

    set_name("captain");
    add_name("pirate");
    set_race_name("minotaur");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " minotaur pirate captain");
    set_gender(G_MALE);
    set_long("Before you stands the captain of the pirate frigate, " +
        "a huge bloodthirsty minotaur!\n");

    set_stats(({180, 150, 180, 130, 160, 160}));
    set_base_stat(SS_LAYMAN, 200);
    
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_ACROBAT, 100);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_GUILD_SPECIAL_SKILL, 100);

    add_prop(CONT_I_HEIGHT, 200 + random(10));
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_VOLUME, 80000);

    add_prop(OBJ_M_HAS_MONEY, MONEY);

    set_alignment(-400);
    set_knight_prestige(100);

    set_act_time(12);
    add_act("say The high seas are full of foolish landlubbers!");
    add_act("emote roars at his crew to fasten the grappling hooks.");

    set_cact_time(12);
    add_cact("change grip");
    add_cact("shout I'll go down with my ship!");
    add_cact("emote narrows his eyes threateningly.");
    add_cact("say You'll be fishbait before long!");

    set_introduce(1);
    set_all_hitloc_unarmed(65);

    // Good natural armour and a special attack
    set_exp_factor(135);

    equip(({ WEP1, ARM1, ARM2, ARM3, MONK }));

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
}

void
get_me_soul()
{
    add_cmdsoul(MINOTAUR_SOUL);
    update_hooks();
    remove_alarm(soul_id);
    command("wear patch");
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

    if (attacktype == 0)
    {
        command("gore");
        return 1;
    }

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
init_living()
{
    init_team_pickup();
    ::init_living();
}

