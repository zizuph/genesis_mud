/*
 * Orc for the roads in Faerie
 * By Finwe, April 2005
 *
 * Modified by Carnak 2021-03-11
 * - The adjectives were doubled, moved them to the create_orc
 *   function so that it is masked in cloned orcs.
 */

#include "defs.h"
#include "orc.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit "/d/Faerun/std/team_code";
inherit "/d/Faerun/lib/assist_friend";
inherit MAKE_MONEY;

void create_orc()
{
    string mental, phys;

    seteuid(getuid());

    npc_name = ORC_CAMP_NPC;

    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    add_name(npc_name);
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");

    set_long("The " + query_short() + " looks dirty and ferocious. It " +
        "is evil looking, and ready to destroy anything it meets.\n");

    equip(({ARM_DIR + "lbreastplate", 
            ARM_DIR + "i_greaves", 
            WEP_DIR + "longsword"}));
}

void create_monster()
{

    set_name("orc");
    set_race_name("orc");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_WEP_KNIFE,     50+random(10));
    set_skill(SS_WEP_AXE,       50+random(10));
    set_skill(SS_WEP_POLEARM,   50+random(10));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_WEP_CLUB,      50+random(10));
    set_skill(SS_UNARM_COMBAT,  50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));

    set_gender(0);

    set_alignment(0);
    default_config_npc(50 + random(20));

    set_m_in("lopes in");
    set_m_out("lopes");
    add_chat("Me killses elveses!");
    add_chat("Elveses only guds for eattin'");
    add_chat("Orcses will killses you.");
    add_chat("You looks gud to eatses.");
    add_chat("Elveses and dwarves be bad!");
    add_chat("Me findses eminies for big bosses.");

    add_act("snarl");
    add_act("emote looks you up and down as a meal.");
    add_act("emote licks its lips hungrily.");
    add_act("emote scratches itself.");
    add_act("emote picks something out of its fang.");
    add_act("emote growls dangerously.");


    ADD_MONEY;

    create_orc();
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
            clone_object(ARM_DIR + "lbreastplate")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "i_greaves")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "longsword")->move(TO);

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
    int avg_stat;
    string how;

    avg_stat = query_average_stat();

    if (!objectp(enemy))
        return 1;

    if (random(3))
    {
	    return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(avg_stat + random(30), W_IMPALE, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "barely hurt";
            break;
        case 1..10:
            how = "lightly hurt";
            break;
        case 11..20:
            how = "painfully hurt";
            break;
        default:
            how = "severely hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " slashes you with its claws!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " charges " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }

    return 1;
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}
