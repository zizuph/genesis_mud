/* A boy cook, accompanying the stew pots in the camp
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           8/1/96     Created
**
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
    clone_object(DEPHTEMP_DIR+"weapons/woodspn")->move(this);
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wield all");
    command("wear all");
    MONEY_MAKE_GC(1)->move(this);
}
 
void create_monster() {
    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (adj=="young") adj="smelly";
    if (!IS_CLONE) return;
    set_name("cook");
    add_name("boy");
    set_adj(({"dirty","young","kretan",adj}));
    add_adj("kretan");
    set_race_name("human");
    set_short("young "+adj+" cook");
    set_long(
        "He is a dirty "+adj+" boy, forced into cooking for the soldiers "+
        "in this encampment. Despite his low status in life, he looks " +
        "proud to serve in his position.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
 
    set_act_time(10);
    add_act("emote drops some herbs into the stewpot.");
    add_act("emote drops some vegetables into the stewpot.");
    add_act("emote stirs the pot with his spoon.");
    add_act("emote stirs the pot with his spoon.");
    add_act("emote tastes the stew with his spoon.");
 
    set_cact_time(5);
    add_cact("say Its foreigners like you who cause all this trouble!");
    add_cact("say I knew I shouldn't have taken this job!");
    add_cact("say If you eat my stew, I hope you choke!");
    add_cact("emote spits on you.");
 
    set_stats(({ 50, 50, 50, 25, 25, 100})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_CLUB, 35);
    set_skill(SS_PARRY, 35);
    set_skill(SS_DEFENCE, 35);
    set_hp(query_max_hp());
    set_alignment(0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
