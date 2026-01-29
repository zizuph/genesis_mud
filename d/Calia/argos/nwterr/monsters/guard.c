/* Argosian guard - guarding the marble masons on the marble road.
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           10/14/93   Created
** Zima           2/18/95    Cleaned up
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR+"gsword")->move(this);
    clone_object(ARMOUR_DIR+"gmail")->move(this);
    clone_object(ARMOUR_DIR+"ghelmet")->move(this);
    clone_object(ARMOUR_DIR+"gshield")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_SC(12)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"argosian guard","guard","argosian","human","soldier"}));
    set_adj(({"nervous","Argosian"}));
    set_race_name("guard");
    set_short("nervous Argosian guard");
    set_long(
        "This soldier is a member of the Argosian army, and has been " +
        "sent here to guard the surrounding territory. He knows his "+
        "enemies are nearby and looks a little nervous about being "+
        "assigned here. He is wearing armour bearing the winged-horse "+
        "of Argos. \n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(10);
    add_act("emote looks at you suspiciously.");
    add_act("emote glances nervously into the woods.");
    add_act("emote spits on the ground nervously.");
    add_act("southeast");
    add_act("northwest");
    add_act("emote stands at attention.");
 
    set_cact_time(5);
    add_cact("say its foreigners like you who cause all this trouble!");
    add_cact("emote glares at you murderingly.");
    add_cact("say if you are lucky, you will live and become a slave!");
    add_cact("say pray to your false gods that your death will be swift!");
    add_cact("emote smiles sadistically at you.");
 
    set_stats(({ 40, 40, 40, 20, 20, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(10000);
    set_alignment(100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
