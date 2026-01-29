/*
 * Farmer for the roads in Faerie
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

    mental = ({"able-bodied", "adventurous", "alert", "bold", "brave", 
//        "capable", "decisive", "energetic", "happy", "impressive", 
        "capable", "decisive", "happy", "impressive", 
//        "intelligent", "profound", "strong", "watchful"});
        "intelligent", "profound", "watchful"});
    phys  = ({"strong", "energetic", "weather-worn"});
    type = ({"settler", "farmer", "homesteader", "pioneer"});

    x = random(sizeof(mental));
    y = random(sizeof(phys));
    z = random(sizeof(type));
    set_name("human");
    add_name(FAERIE+SETTLER+"_");
    add_name(type[z]);
    set_race_name("human");
    set_gender(random(2));

    set_adj(mental[x]);
    set_adj(phys[y]);
    set_short(mental[x] + " " + phys[y] + " " + type[z]);

    set_long("The " + query_short() + " appears to be someone looking " +
        "to settle down and build a farmstead. " + CAP(HE_SHE(TO)) + 
        " has long hair and leathery skin from countless years of working " +
        "in the sun.\n");

    default_config_npc(50+random(10));

    add_chat("There are so many places to settle in.");
    add_chat("My last village was so crowded, I had to move.");
    add_chat("This looks like a good place to build a farm.");
    add_chat("I heard a wolf last night and it was scary.");
    add_chat("Lots of people are moving down here.");
    add_chat("It is so peaceful and nice here, a perfect place for a new farm.");

    add_act("sigh wistf");
    add_act("emote looks around.");
    add_act("stretch");
    add_act("yawn");
    add_act("emote watches you carefully.");
    add_act("emote looks up at the sky.");
 
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote shouts a battle cry at you.");
    add_cact("emote dodges your attack.");

    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_WEP_KNIFE,     50+random(10));
    set_skill(SS_WEP_AXE,       50+random(10));
    set_skill(SS_WEP_POLEARM,   50+random(10));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_UNARM_COMBAT,  50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));

    set_alignment(0);
    default_config_npc(21);

    set_m_in("walks in");
    set_m_out("walks");

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
            clone_object(ARM_DIR + "lbreastplate")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "i_greaves")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "e_knife")->move(TO);

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
            how = "barely hurt ";
            break;
        case 11..20:
            how = "hurt";
            break;
        default:
            how = "seriously hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " charges you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " charges " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1;
}

