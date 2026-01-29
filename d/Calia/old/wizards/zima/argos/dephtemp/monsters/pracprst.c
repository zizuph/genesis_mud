/* Priest of Dephonia - in military practice
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
int SpecAttackLevel=50;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "sword")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "shield")->move(this);
    clone_object(ARMOUR_DIR+"dring1")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"young dephonian priest","priest","dephonian","human"}));
    set_adj("Dephonian");
    set_adj("young");
    set_race_name("priest");
    set_short("young Dephonian priest");
    set_long(break_string(
        "He is a young priest in the Order of Dephonia, here to train " +
        "in the martial arts. He is well built and has a confident "+
        "sparkle in his eyes.\n",70));
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(10);
    add_act("say Soon we will put our training to the test.");
    add_act("emote practices some defensive moves.");
    add_act("emote flexes his muscles.");
    add_act("emote smiles confidently.");
    add_act("emote bends over and stretches his back.");
    add_act("say The Captain should be here soon to start today's lesson.");
    add_act("say I killed an Argosian guard in the forest yesterday.");
    add_act("emote studies you intently.");
    add_act("say Are you one of the new servants?");
#include "dephcact.h"
 
    set_stats(({ 50, 50, 50, 50, 50, 50})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_hp(10000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
