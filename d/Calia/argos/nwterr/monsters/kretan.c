/* Kretan Warrior - attacks visitors along the marble road
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           10/14/93   Created
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
    MONEY_MAKE_SC(12)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"kretan warrior","warrior","kretan","human","soldier"}));
    set_adj(({"belligerent","Kretan"}));
    set_race_name("human");
    set_short("belligerent Kretan warrior");
    set_long(
        "He is a member of the rebel army of Kretos which is trying "+
        "to drive foreigners from the valley. A sinister-looking " +
        "soldier, he looks at you with murder in his eyes. " +
        "He is wearing armour embellished with the Hydra of Kretos.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(75);
 
    set_act_time(10);
    add_act("emote peers at you maliciously.");
    add_act("say You are not welcome in our valley.");
    add_act("say You and your kind will be driven out!");
    add_act("east");
    add_act("west");
    add_act("emote rattles his sword offensively.");
 
    set_cact_time(5);
    add_cact("emote raises his sword in a mighty battle yell!");
    add_cact("say You and your kind shall be driven out, infidel!");
    add_cact("emote glares at you murderingly.");
    add_cact("say Pray to your false gods that your death will be swift!");
    add_cact("emote grins sadistically at you.");
 
    set_stats(({ 40, 40, 40, 20, 20, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(10000);
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
