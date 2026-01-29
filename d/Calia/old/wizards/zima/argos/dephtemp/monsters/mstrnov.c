/* Master of Novices of the Order of Dephonia
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
int SpecAttackLevel=60;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "dagger")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring2")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Domedron");
    add_name(({"priest","dephonian","human"}));
    set_adj(({"Dephonian","stern"}));
    set_race_name("priest");
    set_short("stern Dephonian priest");
    set_title("the Master of Novices");
    intro_resp_cmd=(({"introduce myself",
                   "say We do not accept outsiders, infidel. Be gone!"}));
    set_long(
        "He is a high priest in the Order of Dephonia in charge of " +
        "the instruction of the children and novices of the Order. " +
        "His stern look makes you think his tounge is probably " +
        "sharper than his dagger.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_act_time(5);
    add_act("say You must be lost. The meeting is in the reception chamber.");
    add_act("say Our Order is not open to infidels like you. Begone!");
    add_act("emote scowls sternly.");
    add_act("emote sniffs smugly.");
    add_act("emote glances at the note on his desk.");
    add_act("emote straightens the scrolls in the curio.");
    add_act("say Are you one of the new slaves?");
    add_act("say I may not instruct you in the mysteries of our Order.");
    add_act("say I have much to attend to. Be about your business and go.");
    add_act("emote gives you a contemptuous look.");
#include "dephcact.h"
 
    set_stats(({ 50, 50, 50, 50, 50, 50})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_default_answer("The Master of Novices says: I don't "+
                       "have time for you now. Begone!\n");
    set_hp(10000);
    set_alignment(-250);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
