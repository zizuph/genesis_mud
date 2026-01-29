/*
 * Half-elf for the roads in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

void arm_me();

void create_monster()
{
    int x,y,z;
    string *mental, *phys, *type;

    mental = ({"bright", "brilliant", "clever", "courageous", "dextrous", "dignified", "fierce", "glorious", "nimble", "noble", "perceptive", "proud", "quick", "robust", "serene", "thoughtful", "wise", "witty"});
    phys  = ({"smooth-skinned", "green-eyed", "brown-haired", "thin", "muscular", "tanned", "pale", "broad-shouldered"});
    type = ({"half-elf"});

    x = random(sizeof(mental));
    y = random(sizeof(phys));
    z = random(sizeof(type));
    set_name("half-elf");
    add_name(FAERIE+HALF_ELF+"_");
    add_name("elf");
    add_name(type[z]);
    set_race_name("half-elf");
    set_adj(mental[x]);
    set_adj(phys[y]);
    
    set_gender(random(2));
    set_alignment(0);

    default_config_npc(70 + random(20));

    set_short(mental[x] + " " + phys[y] + " " + type[z]);

    set_long("The " + query_short() + " is a cross between an elf and " +
        "a human. " + CAP(HE_SHE(TO)) + " is fairer than most humans, " +
        "slim, and has delicate, chiseled features.\n");

    default_config_npc(5+random(10));
    
    add_chat("Wherever you travel, keep your spirits high.");
    add_chat("My mother was an elf and she taught me much of them.");
    add_chat("Elves are a secretive race.");
    add_chat("I have travelled and learned many things.");
    add_chat("Beware of villains on the road. They are becoming bolder.");

    add_act("smile");
    add_act("emote looks up and studies the sky.");
    add_act("emote searches the bushes.");
    add_act("emote cleans some dust off of " + HIM_HER(TO) + "self.");
    add_act("emote looks up the road for danger.");
    add_act("chuckle");
 
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote shouts a battle cry at you.");
    add_cact("emote dodges your attack.");

    set_skill(SS_DEFENCE,       60+random(10));
    set_skill(SS_WEP_KNIFE,     60+random(10));
    set_skill(SS_WEP_AXE,       60+random(10));
    set_skill(SS_WEP_POLEARM,   60+random(10));
    set_skill(SS_WEP_SWORD,     60+random(10));
    set_skill(SS_UNARM_COMBAT,  60+random(10));
    set_skill(SS_AWARENESS,     60+random(12));
    set_skill(SS_PARRY,         60+random(10));

    arm_me();

    set_m_in("strolls in");
    set_m_out("strolls");
    ADD_MONEY;
    make_gold(1 + random(2));

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

    clone_object(WEP_DIR + "e_lsword")->move(TO);

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
            how = "barely hurt";
            break;
        case 1..10:
            how = "lightly hurt";
            break;
        case 11..20:
            how = "painfully hurt";
            break;
        default:
            how = "dreadfully hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " steps aside and executes a one-two punch on you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " steps aside and executes a one-two punch on " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1;
}

