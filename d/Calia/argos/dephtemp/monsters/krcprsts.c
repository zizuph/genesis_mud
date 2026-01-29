/* Priestess of Dephonia - visiting the Kretan Camp
** SPECIAL NOTE: cloned in ~zima/argos/swterr/rooms/krcampt.c
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
int SpecAttackLevel=60;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "staff")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(OBJ_DIR + "krcpnote")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring2")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"priestess of Dephonia","priestess","dephonian","human"}));
    set_race_name("human");
    set_short("priestess of Dephonia");
    set_long(
       "Dressed in full ceremonial garb, she is a priestess of the " +
       "Order of Dephonia. " +
       "She is an enchantingly beautiful woman, though someone you feel " +
       "you must never turn your back on. She looks very confident of " +
       "herself.\n");
 
    /* the following puts this NPC in the Rebel Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_gender(1); /* female */
 
    set_act_time(5);
    add_act("emote glances at a note in her hand.");
    add_act("emote twists the ring on her finger.");
    add_act("emote studies you intently.");
    add_act("say Our Mother will not be happy to hear of outlanders so "+
            "close.");
    add_act("say I have brought a message from the Hierophant.");
    add_act("whispers a short prayer to herself.");
 
    set_cact_time(4);
    add_cact("say You and all your kind shall be driven out, infidel!");
    add_cact("emote surrounds herself in black light.");
    add_cact("emote points a crooked finger at you and chants a curse.");
    add_cact("say I will bring your blood in a bottle as a sacrifice!");
    add_cact("say run in fear, infidel, for the Light of Darkness " +
             "overshadows you!");
    add_cact("emote hisses a serpentile curse at you.");
    add_cact("emote glares at you with jet black eyes.");
 
    set_stats(({ 60, 60, 60, 60, 60, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_PARRY,   60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(-300);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
