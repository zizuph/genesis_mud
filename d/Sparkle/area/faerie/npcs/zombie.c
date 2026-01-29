/*
 * Faerie Zombie
 * This zombie is found on the upper level of the graveyard
 * By Finwe, August 2004
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

void arm_me();
void
create_monster()
{
    set_race_name("zombie");

    set_adj("fetid");
    set_adj("lumbering");

    set_short("fetid old zombie");
    set_long("It looks like it has been dead for a while. It is rotting " +
        "and looks sickly.\n");

    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_WEP_KNIFE,     50+random(10));
    set_skill(SS_WEP_AXE,       50+random(10));
    set_skill(SS_WEP_POLEARM,   50+random(10));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_UNARM_COMBAT,  50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));

    default_config_mobile(40+random(10));

    set_gender(2);
    add_prop(NPC_I_NO_LOOKS,   1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_UNDEAD, 20);
    
    add_prop("_ranger_i_not_blind",1);

    set_act_time(5);
    add_act("emote makes some strange noise.");
    add_act("emote lumbers towards you.");
    add_act("moan");

    set_m_in("aimlessly lumbers in");
    set_m_out("lumbers aimlessly");     

    arm_me();

    ADD_MONEY;

}

void
arm_me()
{
    int arm_count = random(2);

    switch(arm_count)
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            clone_object(ARM_DIR + "burlap_shirt")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "burlap_pants")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "low_wep")->move(TO);

    command("wield all");
    command("wear all");

    return;
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;

    if (random(3))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(20 + random(30), W_IMPALE, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unhurt";
            break;
        case 1..10:
            how = "barely hurt";
            break;
        case 11..20:
            how = "hurt";
            break;
        default:
            how = "seriously hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " touches you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " touches " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
    	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}
