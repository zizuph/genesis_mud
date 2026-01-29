/*
 *   /d/Gondor/ithilien/poros/npcs/corsair_master.c
 *
 *   This is the corsair npc masterfile. The functions used are based 
 *   on those in /d/Gondor/morgul/npc/ithil_monster.c
 *
 *   Talisan,  February 1996
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Inherited logkill and make_money,
 *				removed the includes.
 *  7-Jul-1997, Gorboth:   Grammar improvements in language,
 *                         Changed 'Kill Him' to 'Death to you'
 *                          so as to avoid gender errors.
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#define ATTACKED_CORSAIRS   "_gondor_i_attacked_poros_corsairs"

#define QUIT_REACT(x) ({"shout You are a stinking coward, "+x+"!"})

//	Protoypes
void    help_friend(object ob, object friend);
void    test_can_see(object victim);

//	Global variables
int attack_alarm;


public void
create_corsair()
{
}


nomask void
create_monster()
{
    seteuid(getuid(TO));
    set_name("corsair");
    add_name(({"pirate", "man"}));
    add_name("_poros_corsair");
    set_race_name("human");
    set_long("This is one of the corsairs serving under the banner of the "
      + "Black Drake. He is a typical member of the pirate crew from Umbar, "
      + "that is made up of villians of varying backgrounds. The pirates "
      + "range from pure blooded Corsairs and Haradrim, to those of mixed "
      + "ancestry. Even a few Variags serve amongst this crew.\n");

    default_config_npc(60+random(15));
    set_base_stat(SS_DEX, 75+random(15));
    set_base_stat(SS_DIS, 80+random(15));
    set_skill(SS_WEP_SWORD, 55+random(15));
    set_skill(SS_PARRY, 45+random(10));
    set_skill(SS_DEFENCE, 45+random(10));
    set_skill(SS_AWARENESS, 70+random(15));

    set_alignment(-50);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 175 +random(50));
    add_prop(CONT_I_WEIGHT, 72500 +random(30*500));
    add_prop(CONT_I_VOLUME, 70000 +random(30*500));

    set_pick_up(50);
    set_tell_active(1);
    trig_new("%w 'leaves' 'the' 'game.\n'", "react_quit");

    create_corsair();

    /* XP Adjustment 2014-12-02 Cotillion */
    set_exp_factor(125);
}

public void
arm_me()
{
    clone_object(POROS_DIR + "weapons/cutlass")->move(this_object());
    command("wield all");

    clone_object(POROS_DIR + "armours/leather")->move(this_object());
    clone_object(POROS_DIR + "armours/helmet")->move(this_object());
    clone_object(POROS_DIR + "armours/shield")->move(this_object());
    command("wear all");

    get_money();
}

/*
 * Function Name:  attacked_by
 * Description:    This function is called when somebody attacks this object.
 * Arguments:      ob- the attacker
 */

void
attacked_by(object ob)
{
    object  room = ENV(TO),
           *arr;

    ::attacked_by(ob);

    arr = filter(all_inventory(room), &->id("_poros_corsair"));
    arr->notify_ob_attacked_me(TO, ob);
    ob->add_prop(ATTACKED_CORSAIRS, 1);
}

/*
 * Function Name:    notify_ob_attacked_me
 * Description:      This is called when someone attacks a team member.
 * Arguments:        friend- my teammate
 *                   attacker- the attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    object corsair = this_object();

    if (query_attack())
        return;
    if (random(10))
        set_alarm(5.0, 0.0, &help_friend(attacker, corsair));
}

void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    if (victim->query_npc())
        return;
    if (!present(victim,ENV(TO)))
        return;
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
    {
        command("shout Where is the stinking bastard? I can't see him!");
        return;
    }
    command("kill "+victim->query_real_name());
}

/*
 * Function Name:    help_friend
 * Description:      Help my friends by attacking thier attacker.
 * Arguments:        attacker- The person who attacked my friend.
 */
void
help_friend(object ob, object friend)
{
    if (objectp(ob) && !objectp(query_attack()) &&
        present(ob, ENV(TO)) && CAN_SEE(TO, ob) && F_DARE_ATTACK(TO, ob))
    {
        command("shout You're dead meat, "+ob->query_race_name()+"!");
        do_attack(ob);
    }
}

void
react_attacker(object player)
{
    if (IS_RANGER(player))
    {
        if (!random(4))
            command("shout It is one of the accursed Rangers!");
    }
    else if (!random(4))
    {
        command("shout This is the cur who has been attacking the crew!");
        command("shout Death take you!");
    }
    set_alarm(1.0, 0.0, &do_attack(player));
}


int
check_attack(object player)
{
    if (query_attack())
        return 0;
    if (CAN_SEE(TO, player) && CAN_SEE_IN_ROOM(TO) &&
        (player->query_prop(ATTACKED_CORSAIRS) ||
        (IS_RANGER(player) && random(player->query_stat(SS_OCCUP)) > 40)))
    {
        set_alarm(2.0, 0.0, &react_attacker(player));
        return 1;
    }
}

public void
init_attack()
{
    if (query_attack())
	return;
    if (!interactive(TP))
	return;
    check_attack(TP);
}

void
loot_corpse()
{
    command("get all from corpse");
}

void
test_can_see(object victim)
{
    if (!present(victim, ENV(TO)))
    {
	remove_alarm(attack_alarm);
	attack_alarm = 0;
	return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, victim))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        do_attack(victim);
    }
}

void
remove_surplus(object ob)
{
    command("wear all");
    if (!sizeof(query_weapon(-1)))
    command("wield weapon");
    if (!objectp(ob->query_worn()) && !objectp(ob->query_wielded()))
      ob->remove_object();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(ob) || !objectp(from))
      return;
    if (!query_prop(NPC_M_NO_ACCEPT_GIVE))
      return;
    if (query_encumberance_weight() > 50 ||
        query_encumberance_volume() > 80)
      set_alarm(1.0, 0.0, &remove_surplus(ob));
}

void
react_quit(string who)
{
    command("get all");
    if (random(2))
    command(ONE_OF_LIST(QUIT_REACT(who)));
}
