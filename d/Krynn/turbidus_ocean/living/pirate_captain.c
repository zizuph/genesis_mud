/*
 * Pirate captain of a ship in the Turbidus Sea.
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

#define WEP1   "/d/Ansalon/balifor/flotsam/obj/weapon/nice_clabbard"
#define ARM1   "/d/Ansalon/guild/pirates/obj/patch"
#define ARM2   "/d/Ansalon/balifor/flotsam/obj/armour/shirt"
#define ARM3   "/d/Ansalon/balifor/flotsam/obj/armour/jerkin"
#define MONK   "/d/Ansalon/guild/pirates/obj/monkey"

#define MONEY  ({ 0, 4, 8, 0 })

#define MINOTAUR_SOUL    "/d/Ansalon/guild/minotaurs/cmdsoul"
#define SS_GUILD_SPECIAL_SKILL   143015
#define ATTACKED_PIRATES "_attacked_pirate_sailors"

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

    set_name("rognak");
    add_name("captain");
    add_name("pirate");
    set_living_name("rognak");
    set_title("the Bold, Pirate Captain");
    set_race_name("minotaur");
    set_adj("huge");
    add_adj("bull-headed");
    set_short("huge bull-headed captain");
    set_gender(G_MALE);
    set_long("Before you stands the captain of the pirate frigate, " +
        "a huge bloodthirsty minotaur! He is directing his crew to " +
        "board the galleon they have managed to grapple up against.\n");

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
    add_act("say The Ergothian galley will have fine loot on board!");
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

    if (attacktype == 3)
    {
        object * teammates = enemy->query_team_others();
        int lowest_str = enemy->query_stat(SS_STR);
        int pirate_str = random(TO->query_stat(SS_STR)) + 
            random(TO->query_stat(SS_STR));

        if (sizeof(teammates) > 0)
        {
            foreach(object mate: teammates)
            {
                if(present(mate, E(TO)))
                {
                    int mate_str = mate->query_stat(SS_STR);

                    if(mate_str < lowest_str)
                    {
                        lowest_str = mate_str;
                        enemy = mate;
                    }
                }
            }           
        }

        if( (lowest_str + random(lowest_str)) < pirate_str )
        {
            enemy->catch_msg(QCTNAME(TO) + " kicks you mightily with " +
                "his powerful hoofed foot, launching you in the air " +
                "and over the side of the ship!\n\nYou land in the " +
                "water with a splash!\n");
            tell_room(E(TO), QCTNAME(TO) + " kicks " +QCTNAME(enemy) + 
                " mightily with a powerful hoofed foot, launching " +
                HIM(enemy)+ " in the air and over the side of the " +
                "ship!\n", ({ enemy, TO }));
            tell_room((ROOM + "10t"), QCTNAME(enemy) + 
                " comes flying over the side of the pirate frigate, " +
                "landing in the sea with a splash!\n", ({ enemy, TO }));

            enemy->move_living("M", ROOM + "10t", 1, 0);
            return 1;
        }

	enemy->catch_msg(QCTNAME(TO) + " kicks you mightily with " +
            "his powerful hoofed foot, forcing you back across " +
            "the deck of the ship.\n");

	tell_room(E(TO), QCTNAME(TO) + " kicks " +QCTNAME(enemy) + 
            " mightily with a powerful hoofed foot, forcing " +
            HIM(enemy)+ " back across the deck of the ship\n", 
            ({ enemy, TO }));

        return 1;
    }

    return 0;
}

void
attacked_by(object ob)
{    
    ::attacked_by(ob);

    if(!ob->query_prop(ATTACKED_PIRATES))
        ob->add_prop(ATTACKED_PIRATES, 1);
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

    if(!CAN_SEE_IN_ROOM(TO))
    {
        command("say Pirates! We need light!");
        return;
    }

    command("say Carrion trying to steal our kill! Attack!");
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

    if(!CAN_SEE_IN_ROOM(TO))
    {
        command("say Darkness? Pirates, we need light!");
        return;
    }

    command("say Carrion trying to steal our kill! Attack!");
    command("kill " +enemy->query_name());
    return;
}

void
init_living()
{
    if(this_player()->query_prop(ATTACKED_PIRATES))
        set_alarm(3.5, 0.0, &attack_enemy(this_player()));

    init_team_pickup();
    ::init_living();
}

