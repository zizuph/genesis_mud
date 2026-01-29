/* A Marble Mason - construction worker on marble road to Argos
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
    clone_object(WEAPON_DIR+"hammer")->move(this);
    clone_object(ARMOUR_DIR+"mtunic")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_CC(12)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("mason");
    set_adj(({"muscular","marble"}));
    set_race_name("human");
    set_short("muscular marble mason");
    set_long(
        "He is skilled in constructing things from marble, including " +
        "this road.  A quick glance at his muscles shows the hard work " +
        "being a marble mason is.  He is sweaty and looks tired.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_act_time(10);
    add_act("emote places a piece of marble on the path.");
    add_act("emote chips away at a slab of marble with his hammer.");
    add_act("emote lifts a slab of marble from the cart and drops it.");
    add_act("emote wipes the sweat from his brow.");
 
    set_cact_time(5);
    add_cact("say Its foreigners like you who cause all this trouble!");
    add_cact("say I knew I shouldn't have taken this job!");
    add_cact("say If more guards were here, you wouldn't have done this!");
    add_cact("say I'll crush your skull!");
 
    set_stats(({ 40, 30, 30, 10, 10, 20})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_CLUB, 30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_hp(10000);
    set_alignment(80);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
