/* Priestess of Dephonia - at the bathing pool
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
    clone_object(WEAPON_DIR + "staff")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR+"dring1")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"young Dephonian priestess","priestess","dephonian","human"}));
    set_adj("Dephonian");
    set_adj("young");
    set_race_name("human");
    set_short("young Dephonian priestess");
    set_long(
        "She is a young priestess in the Order of Dephonia with long " +
        "black hair and enticing brown eyes. She seems a bit embarassed "+
        "that you are here.\n");
 
   set_gender(1);
   add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(10);
    add_act("say I think you are lost.");
    add_act("emote wipes some perspiration from her forehead.");
    add_act("emote blushes femininely.");
    add_act("emote smiles enticingly.");
    add_act("say You really shouldn't be in here.");
   add_act("emote dips her toe in the pool's waters.");
    add_act("emote studies you intently.");
    add_act("say Are you one of the new servants?");
 
#include "dephcact.h"
 
    set_stats(({ 50, 50, 50, 50, 50, 50})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_hp(15000);
    set_alignment(-150);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
