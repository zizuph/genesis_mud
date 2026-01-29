/* Kretan Warrior - in hiding in the city - found in various hiding places
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           8/25/95    Created
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"cackle maniacally"}));
#include "defs.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR+"ksword")->move(this);
    clone_object(ARMOUR_DIR+"kmail")->move(this);
    clone_object(ARMOUR_DIR+"khelmet")->move(this);
    clone_object(ARMOUR_DIR+"kshield")->move(this);
    command("wield all");
    command("wear all");
    MONEY_MAKE_SC(10)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"kretan warrior","warrior","kretan","human","soldier"}));
    set_adj(({"clandestine","Kretan"}));
    set_race_name("human");
    set_short("clandestine Kretan warrior");
    set_long(
        "He is arrayed with the armour of the rebel army of Kretos, "+
        "embellished with the seven-headed Hydra, the symbol of fear "+
        "and rebellion. He seems to have been hiding and waiting for an "+
        "attack.\n");
 
    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    set_act_time(10);
    add_act("emote peers at you maliciously.");
    add_act("say The infidels will reveal our location!");
    add_act("say You won't live to speak of this, infidel!");
    add_act("emote stares at you with murder in his eyes.");
 
    set_cact_time(5);
    add_cact("shout All outlanders must die!");
    add_cact("emote hisses: You shall not live to tell of us.");
    add_cact("say I will put your head on a spike!");
    add_cact("say I will receive a great reward for killing you!");
    add_cact("say You'll wish you never came to this valley!");
    add_cact("say Your bloody corpse will be a warning to all invaders!");
 
    set_stats(({ 60, 60, 60,  0,  0, 150})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(query_max_hp());
    set_alignment(-110);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
