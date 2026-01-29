/* Priest of Dephonia, playing a game in the lounge
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
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring2")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"priest","dephonian","human","novice"}));
    set_adj("Dephonian");
    set_adj("elderly");
    set_race_name("priest");
    set_short("elderly Dephonian priest");
    set_long(
        "He is an older member of the Order, his wisdom of the "+
        "years showing in his wrinkled but radiant face. He has "+
        "come here to relax and enjoy a game with one of his "+
        "friends from his youth.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_act_time(10);
    add_act("emote confidently moves one of the pieces on the table.");
    add_act("emote carefully moves one of the pieces on the table.");
    add_act("emote scratches his head.");
    add_act("emote smiles knowingly.");
    add_act("emote ponders his next move.");
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
