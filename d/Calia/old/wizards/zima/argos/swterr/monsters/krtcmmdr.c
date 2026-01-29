/* Kretan Triterian Commander - leader of the camp
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           11/12/94   Created
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
    clone_object(WEAPON_DIR+"ktsword")->move(this);
    clone_object(ARMOUR_DIR+"ktmail")->move(this);
    clone_object(ARMOUR_DIR+"kthelmet")->move(this);
    clone_object(ARMOUR_DIR+"ktshield")->move(this);
    command("wear all");
    command("wield all");
    command("shout Guards! Kill the intruders!");
    MONEY_MAKE_GC(4)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"kretan commander","commander","kretan","human","soldier"}));
    set_adj(({"fierce","Kretan","Triterian"}));
    set_race_name("Commander");
    set_short("fierce Kretan Triterian Commander");
    set_long(
        "He is a Triterian Commander in the Army of Kretos, in charge " +
        "of a small troop of guards. A middle-aged soldier, he bears " +
        "a few scars of battle. He is wearing armour embellished with " +
        "the Hydra of Kretos with a gold cord hanging from " +
        "the shoulder.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    set_act_time(10);
    add_act("say All the infidels must be driven out!");
    add_act("say Who lead you to our camp?");
    add_act("emote slams his fist into his hand in anger.");
    add_act("emote swears in an unknown tounge.");
    add_act("shout where are the other guards?");
 
    set_cact_time(5);
    add_act("say I will have your head for this intrusion!");
    add_act("say Who lead you to our camp?");
    add_act("emote slams his fist into your face.");
    add_act("emote swears in an unknown tounge.");
    add_act("shout Where are the other guards?");
 
    set_stats(({ 60, 60, 60,  0,  0, 150})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(-110);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
