/* Priest of Dephonia - portico guard
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
int SpecAttackLevel=80;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "spear")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "helmet")->move(this);
    clone_object(ARMOUR_DIR + "shield")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring2")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"portico guard","priest","dephonian","guard","human"}));
    set_adj(({"vigilant","temple"}));
    set_race_name("human");
    set_short("vigilant temple guard");
    set_long(
        "He is a priest in the Order of Dephonia arrayed in battle gear " +
        "and trained to guard the temple. His stoic face portrays the " +
        "seriousness with which he performs his duty.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(10);
    add_act("emote studies you intently.");
    add_act("emote stares at you suspiciously.");
    add_act("emote scans the surrounding forest.");
    add_act("emote sniffs smugly.");
    add_act("emote straightens his body stiffly.");
 
#include "dephcact.h"
 
    set_stats(({ 80, 80, 80, 40, 40, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);
    set_hp(20000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
