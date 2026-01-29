/* Argosian Triterian Commander - leader of the dispatch of guards
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
    clone_object(WEAPON_DIR+"tcsword")->move(this);
    clone_object(ARMOUR_DIR+"tcmail")->move(this);
    clone_object(ARMOUR_DIR+"tchelmet")->move(this);
    clone_object(ARMOUR_DIR+"tcshield")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_GC(5)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"argosian commander","commander","triterian","human","soldier",
               "argosian","triterian commander"}));
    set_adj(({"stalwart","Argosian","Triterian"}));
    set_race_name("Commander");
    set_short("stalwart Argosian Triterian Commander");
    set_long(
        "He is a Triterian Commander in the Army of Argos, in charge of "+
        "a dispatch of guards. He is a middle-aged soldier and bears "+
        "the scars of battle. He is wearing armour " +
        "embellished with the winged-horse of Argos with a gold cord "+
        "hanging from the shoulder.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(10);
    add_act("emote smiles superiorly.");
    add_act("emote shouts a command to his troops.");
    add_act("emote nods at you confidently.");
    add_act("emote salutes you informally.");
    add_act("emote surveys the area.");
 
    set_cact_time(5);
    add_cact("say its foreigners like you who cause all this trouble!");
    add_cact("emote glares at you murderingly.");
    add_cact("say I'll put you in shackles, intruder!");
    add_cact("say pray to your false gods that your death will be swift!");
    add_cact("emote yells for reinforcements.");
 
    set_stats(({ 60, 60, 60, 30, 30, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(110);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
