/* Priest of Dephonia - Captain of the Guard
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
int SpecAttackLevel=300;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "spear")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "helmet")->move(this);
    clone_object(ARMOUR_DIR + "shield")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring3")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
   set_name("domitian");
    add_name(({"priest","dephonian","captain","guard","Domitian"}));
    set_adj(({"temple","Dephonian","highly-decorated"}));
    set_race_name("human");
    set_title("the Captain of the Guard");
    set_short("highly-decorated Dephonian temple guard");
    intro_resp_cmd=(({"introduce myself","emote bows militantly."}));
    set_long(break_string(
        "He is a muscular middle-aged man dressed in the battle "+
        "gear of the Dephonian guards. His stern gaze lets you know "+
        "that he is no one to toy with.\n",70));
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    add_prop(NPC_I_NO_RUN_AWAY,1);
 
    set_act_time(5);
    add_act("emote reads the note on his desk.");
    add_act("say What is your business here?");
    add_act("say Watch what you do here, you don't want to get hurt.");
    add_act("say if you are looking for the conference, it is not here.");
    add_act("say are you with the Kretan military?");
    add_act("emote polishes his shield.");
    add_act("emote eyes you with a stern suspicious gaze.");
    add_act("say security is impossible with all you strangers about.");
    add_act("say keeping the temple doors open is a mistake.");
 
    add_ask(({"pass","permission","for pass","for permission",
              "about pass","about permission"}),
              "say Request permission from me, and we shall discuss it.\n",1);
 
    set_default_answer("The Captain of the Guard says: You should ask "+
                       "someone else that.\n");
 
#include "dephcact.h"
 
    set_stats(({200,200,200, 50, 50,100})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_hp(30000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
