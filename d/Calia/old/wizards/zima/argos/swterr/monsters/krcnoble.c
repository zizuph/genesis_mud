/* Argosian Nobleman - loyal to Kretos - meeting with Kretans
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
    clone_object(OBJ_DIR+"nobring")->move(this);
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(20)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"Prosotus","prosotus","nobleman","argosian"}));
    set_title("Nobleman of Argos of the House of Benedictus");
    set_adj("noble");
    set_race_name("human");
    set_short("nobleman");
    set_long(
        "He is a well groomed nobleman of Argos, dressed in an ornate, " +
        "gold-threaded purple tunic. He looks out-of-place here, and " +
        "seems to be stricken with fear.\n");
 
    set_act_time(5);
    add_act("emote trembles in fear.");
    add_act("say I KNEW something would go wrong!");
    add_act("say please don't kill me...my father can pay you well!");
    add_act("emote tries to hide under the table.");
    add_act("emote glances nervously towards the entrance.");
    add_act("introduce myself");
    add_act("say if you outlanders hadn't come, none of this would happen!");
    add_act("shout guards!! In here!! Save me!!");
 
    /* the following puts this NPC in the Rebel Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
 
    set_stats(({ 20, 20, 20, 20, 20, 20})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(10000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
