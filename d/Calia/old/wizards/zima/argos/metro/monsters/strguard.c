/* Argosian street guard
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/30/95    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"stares ahead stoically."}));
#include "defs.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR + "gdspear")->move(this);
    clone_object(ARMOUR_DIR + "gdtunic")->move(this);
    clone_object(ARMOUR_DIR + "gdhelmet")->move(this);
    clone_object(ARMOUR_DIR + "gdshield")->move(this);
    clone_object(ARMOUR_DIR + "gdmail")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"guard","veteran","argosian","soldier","human"}));
    set_adj(({"veteran","Argosian"}));
    set_race_name("guard");
    set_short("veteran Argosian guard");
    set_long(
        "He is a member of the Argosian Guard, a veteran of the recent " +
        "conflicts with the rebels. He is posted here to keep the peace "+
        "in the city and to be on the lookout for enemies of the crown.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(10);
    add_act("emote glances down the streets.");
    add_act("emote nods his head slightly at you.");
    add_act("emote straightens his body stiffly.");
    add_act("emote stares stoically straight ahead.");
 
    set_cact_time(5);
    add_cact("say its foreigners like you who cause all this trouble!");
    add_cact("say you'll never make it out of the city alive!");
    add_cact("emote glares at you murderingly.");
    add_cact("say if you are lucky, you will live and become a slave!");
    add_cact("say pray to your false gods that your death will be swift!");
    add_cact("emote smiles sadistically at you.");
 
    set_stats(({ 80, 80, 80, 40, 40, 80})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);
    set_hp(15000);
    set_alignment(300);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
