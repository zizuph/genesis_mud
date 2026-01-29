/* Novice Priest of Dephonia, in his chambers
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
int SpecAttackLevel=30;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "dagger")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring1")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"priest","dephonian","human","novice"}));
    set_adj("novice");
    set_race_name("human");
    set_short("novice Dephonian priest");
    set_long(
        "He is a young novice priest of Dephonia, only a few years "+
        "past his boyhood. He is receiving training in "+
        "martial arts as well as the dark arts. He has a confident "+
        "smirk on his face.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_act_time(10);
    add_act("say Soon we will put our training to the test.");
    add_act("emote chants a simple prayer in an ancient language.");
    add_act("emote admires the new ring on his finger.");
    add_act("emote smiles mischieviously.");
    add_act("emote examines his dagger with a look of confidence.");
    add_act("say The Master should call us soon to start today's lesson.");
    add_act("emote studies you intently.");
    add_act("say Are you one of the new servants?");
#include "dephcact.h"
 
    set_stats(({ 20, 20, 20, 20, 20, 20})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(10000);
    set_alignment(-150);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
