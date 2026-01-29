/* Priest of Dephonia - in his quarters
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
int SpecAttackLevel=70;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "sword")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring3")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"noble dephonian priest","priest","dephonian","human"}));
    set_adj("Dephonian");
    set_adj("noble");
    set_race_name("human");
    set_short("noble Dephonian priest");
    set_long(
        "He is a noble-looking middle-aged priest of the Order. He " +
        "seems to be preparing for battle, but he looks rather relaxed "+
        "at the moment.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(10);
    add_act("say May Our Mother guide us in our efforts.");
    add_act("emote whispers a silent prayer.");
    add_act("emote handles his sword somewhat awkwardly.");
    add_act("emote peers at you suspiciously.");
    add_act("emote studies you intently.");
    add_act("say Are you one of the new servants?");
    add_act("say Who gave you permission to be here?");
    add_act("The power of the Light of Darkness grows stronger each day.");
#include "dephcact.h"
 
    set_stats(({ 70, 70, 70, 70, 70, 70})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 70);
    set_hp(10000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
