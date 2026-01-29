/* Argosian Deuterian Commander - leader of the forces in NWTERR
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
    clone_object(WEAPON_DIR+"dcsword")->move(this);
    clone_object(ARMOUR_DIR+"dcmail")->move(this);
    clone_object(ARMOUR_DIR+"dchelmet")->move(this);
    clone_object(ARMOUR_DIR+"dcshield")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_GC(8)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"argosian commander","commander","deuterian","human","soldier",
               "argosian","deuterian commander"}));
    set_adj(({"imperious","Deuterian"}));
    set_race_name("human");
    set_short("imperious Deuterian Commander");
    set_long(
        "He is a Deuterian Commander in the Army of Argos, a field " +
        "commander for the forces in the area. He is an older soldier " +
        "and looks like he has endured many battles. He is wearing armour " +
        "embellished with the winged-horse of Argos with two gold cords "+
        "hanging from the shoulder.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(10);
    add_act("emote snaps impatiently.");
    add_act("emote reads his orders.");
    add_act("emote glares at you impatiently.");
    add_act("say What do you need? Have you been attacked?");
    add_act("emote drinks from one of the bottles.");
    add_act("say These attacks must stop!");
    add_act("say Increase the patrols! I want the head of every Kretan "+
            "north of the river!");
 
    set_cact_time(5);
    add_cact("say its foreigners like you who cause all this trouble!");
    add_cact("emote glares at you murderingly.");
    add_cact("say I'll put you in shackles, intruder!");
    add_cact("say pray to your false gods that your death will be swift!");
    add_cact("emote yells for reinforcements.");
 
    set_stats(({ 80, 80, 80, 40, 40, 80})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 80);
    set_hp(10000);
    set_alignment(120);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
