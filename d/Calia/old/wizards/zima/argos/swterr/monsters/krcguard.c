/* Kretan Warrior - guards the camp
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           11/12/94   Created
** Zima           2/18/95    Cleaned up
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR+"ksword")->move(this);
    clone_object(ARMOUR_DIR+"kmail")->move(this);
    clone_object(ARMOUR_DIR+"khelmet")->move(this);
    clone_object(ARMOUR_DIR+"kshield")->move(this);
    command("wear all");
    command("wield all");
    command("shout intruders are in the camp! Kill them!");
    MONEY_MAKE_SC(10)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"kretan warrior","warrior","kretan","human","soldier"}));
    set_adj(({"intimidating","Kretan"}));
    set_race_name("warrior");
    set_short("intimidating Kretan warrior");
    set_long(
        "He is a member of the rebel army of Kretos sent here to guard "+
        "this camp. A sinister-looking " +
        "soldier, he looks at you with murder in his eyes. " +
        "He is wearing armour embellished with the Hydra of Kretos.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    set_act_time(10);
    add_act("emote peers at you maliciously.");
    add_act("say You are not welcome in our valley.");
    add_act("say You and your kind will be driven out!");
    add_act("emote rattles his sword offensively.");
 
    set_cact_time(5);
    add_cact("shout all outlanders must die!");
    add_cact("emote hisses: You shall not live to tell of us.");
    add_cact("say I will put your head on a spike!");
    add_cact("say I will receive a great reward for killing you!");
    add_cact("say you'll wish you never came to this valley!");
    add_cact("say your bloody corpse will be a warning to all invaders!");
 
    set_stats(({ 40, 40, 40,  0,  0, 150})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(10000);
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
