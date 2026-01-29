/*
 * Ruffian for North-South road
 * Finwe, Feb 2020
 * Removed their ability to introduce since a room with three
 * people named "Ruffian" looked really weird. Cherek, July 2020
 *  
 * 2021-05-22 - Cotillion
 * - Added missing axe skill
 */

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include "../defs.h";
#include "/d/Shire/common/make_money.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>


#define PHYSLOOK    ONE_OF_LIST(({"big-lipped", "dark-skinned", "dirty","disfigured", "foul-looking", "long-faced", "pock-marked", "slope-browed", "squint-eyed", "swarthy", "ugly", "yellow-skinned", "unkempt"}))
#define ALIGNLOOK   ONE_OF_LIST(({"annoying", "bothersome", "demanding", "dreadful", "ill-favored", "leering", "meddlesome", "miserable", "oppresive", "pesky", "tricky", "troublesome", "wretched"}))

#define WEP ONE_OF_LIST(({NS_WEP_DIR + "rsword", NS_WEP_DIR + "raxe"}))
#define ARM BREE_DIR + "arm/" + "ltunic"

int alarm_id;
//void after_attack();
//void after_attack_msg();


create_monster()
{
    int ran = random(11);

    if (!IS_CLONE)
        return;

    set_name("ruffian");
    set_race_name("human");
    set_adj(({PHYSLOOK}));
//    set_adj(({"squint-eyed","ill-favored"}));
    set_long("This is a ruffian from the south. He is " + PHYSLOOK + 
        " and " + ALIGNLOOK + " and looks like a lot of trouble. He " +
        "wanders through the Shire stirring up trouble and harassing " +
        "the locals.\n");
    set_stats(({70 + ran,  60 + ran, 65 + ran, 
                80 + ran, 100 + ran, 95 + ran}));

    MAKE_MONEY;
    set_alignment(-100 + ran);
//    set_aggressive(1);

    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_AXE, 50);

    set_skill(SS_DEFENCE,60);

    set_skill(SS_BLIND_COMBAT,35);
    set_skill(SS_AWARENESS,35);
    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_2H_COMBAT,40);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    set_gender(G_MALE);

    set_chat_time(45 + random(30));
    set_cchat_time(45 + random(30));
    set_act_time(45 + random(30));
    set_cact_time(45 + random(30));

    add_chat("Hey, where do you think you're going?!?");
    add_chat("No one travels around here without Sharkey's permission!");
    add_chat("Hobbits are worthless creatures!");
    add_chat("If you wanna get past us, you have to pay!");

    add_act("emote glares at you.");
    add_act("emote start to shake you down for money.");
    add_act("emote tries to look tough.");
    add_act("emote stands up and tries to look fearsome.");
    add_act("");
    
    add_cchat("You will pay for this!");
    add_cchat("Die, you fiend!");
    add_cchat("Haul this Disturber of the Peace away!");
    add_cchat("Stop this now!");
    add_cchat("This must end now!");

//    set_alarm(0.5,0.0,"arm_me");

    equip(({WEP, ARM }));

}

arm_me()
{
    object weapon, tunic, boots;

    FIXEUID;

    weapon = clone_object(BREE_DIR + "wep/" + "rsword");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");

    weapon->move(TO);
    tunic->move(TO);
    command("wear all");
    command("wield all");
}
/*
void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("say You should not mess with me, I am stronger than I look.");
    command("emote grips the hilt of his longsword!");
    command("wield all");
    command("wear all");

    alarm_id = set_alarm(10.0, 20.0, "after_attack");
}

void
after_attack()
{
    if(TO->query_attack())
    {
        return;
    }

    else
    {
      after_attack_msg();
      return;
    }
}

void after_attack_msg()
{
  mixed *calls = get_all_alarms();
  int i;

  command("unwield all");
  command("say I am too good for them!!");
  command("say I hope Sharkey will come soon.");

  for (i = 0; i < sizeof(calls); i++)
  {
    alarm_id = calls[i][0];
    remove_alarm(alarm_id);
  }
}
*/

/*
void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}
*/


public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
}


/*
void
no_notice(object player)
{
    player->catch_msg(QCTNAME(TO) + " does not seem to notice you.\n");
    return;
}
*/
/*
 * Function name: init_attack
 * Description:   Called from init_living() in monster.c
 */

/*
public void
init_attack()
{
//  if(TP->query_npc()) return;
//  if(TP->query_skill(SS_SNEAK) > 30)
//  {
//    set_alarm(2.0, 0.0, &no_notice(TP));
//    return;
//  }
  if(!TO->query_attack())
  {
    command("shout Stop this now, Disturber of the Peace!");
    set_alarm(2.0, 0.0, &aggressive_attack(TP));
  }
}
*/
