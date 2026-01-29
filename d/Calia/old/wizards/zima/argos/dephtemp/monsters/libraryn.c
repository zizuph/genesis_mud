/* Keeper of the Chronicles (Librarian) of the Order of Dephonia
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
    clone_object(WEAPON_DIR + "dagger")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring1")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Darthecles");
    add_name(({"priest","dephonian","human"}));
    set_adj(({"Dephonian","wizened"}));
    set_race_name("priest");
    set_short("wizened Dephonian priest");
    set_title("the Keeper of the Chronicles");
    intro_resp_cmd=(({"introduce myself","emote bows slowly."}));
    set_long(break_string(
        "He is an old priest in the Order of Dephonia in charge of " +
        "maintaining the written wealth of the Order in the temple's"+
        "library. He has a kindly but stragely sinister face.\n",70));
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_default_answer("The wizened Dephonian priest says: Wisdom may be "+
                       "found in the ancient writings.\n");
    set_act_time(5);
    add_act("say We have been expecting visitors. Welcome.");
    add_act("say Please browse through our collection if you like.");
    add_act("emote looks at you questioningly.");
    add_act("emote coughs quietly.");
    add_act("emote glances at the note on his desk.");
    add_act("emote wipes some dust form the bookshelf.");
    add_act("say The chronicles in this cabinet are very old, " +
            "not to be touched.\n");
#include "dephcact.h"
 
    set_stats(({ 50, 50, 50, 50, 50, 50})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_hp(10000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
