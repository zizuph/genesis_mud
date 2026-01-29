/*
** A Triterian Commander, in the Temple for a meeting
**
** HISTORY:
** Date      Action
** --------  -----------------------------------------
** 1/1/95    Created
**
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
    clone_object(WEAPON_DIR + "ktsword")->move(this);
    clone_object(ARMOUR_DIR + "ktmail")->move(this);
    clone_object(ARMOUR_DIR + "kthelmet")->move(this);
    clone_object(ARMOUR_DIR + "ktshield")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_GC(6)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"kretan commander","commander","kretan","triterian",
               "human","dephonian"}));
    set_adj("kretan");
    set_race_name("commander");
    set_short("kretan triterian commander");
    set_pshort("kretan triterian commanders");
    set_long(
        "He is a Triterian commander in the Army of Kretos, probably " +
        "here for a meeting with the Dephonians. "+
        "A middle-aged soldier, he bears " +
        "a few scars of battle. He is wearing a black battle tunic " +
        "embelished with a hydra in red, a bronze cord hanging from " +
        "the shoulder.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_act_time(5);
    add_act("say This may be an infidel, they have been seen in the forest.");
    add_act("say The alliance between us will be good for both.");
    add_act("say This conference must start soon, time is wasting.");
    add_act("say Our troops have already killed several infidels.");
    add_act("emote looks at you suspiciously.");
    add_act("emote drums his fingers on the table impatiently.");
    add_act("emote sighs impatiently.");
    add_act("emote taps his foot impatiently.");
 
    set_cact_time(3);
    add_cact("say The infidels have infiltrated even here!");
    add_cact("say kill them before they escape!");
    add_cact("say I will have your head on a pole!");
    add_cact("emote smashes your head with the butt of his sword.");
    add_cact("emote screams in rage.");
    add_cact("say the blood of your kind will fill the river!");
    add_cact("emote knees you in the groin. \n"+
             "You fall to the ground in pain.");
 
    set_stats(({ 60, 60, 60, 60, 60, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_VOLUME, 110000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
