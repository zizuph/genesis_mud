/* A Woodsman in the dark forest - at his campsite
**
**   Coder         Date                Action
** -------------- --------   ----------------------------------------------
** Zima           10/21/93   Created
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
    clone_object(WEAPON_DIR+"axe")->move(this);
    clone_object(ARMOUR_DIR+"wmtunic")->move(this);
    command("wear all");
    command("wield all");
    MONEY_MAKE_CC(20)->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"woodsman","human"}));
    set_adj(({"tall","stout"}));
    set_race_name("woodsman");
   set_pshort("tall stout woodsmen");
    set_long(
        "He is a woodsman, experienced in splitting things " +
        "with his axe.  He is wearing a dark green tunic with a " +
        "gold axe embroidered on it.  He looks as if he is contemplating "+
        "splitting your head.\n");
 
    /* the following puts this NPC in the Rebel Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
 
    set_act_time(10);
    add_act("emote swings his axe deep into a tree.");
    add_act("emote runs his thumb along the blade of his axe, smiling "+
            "evilly.");
    add_act("emote peers at you maliciously");
    add_act("say What are you doing here?");
    add_act("say If you are an Argosian spy, I will split your head open");
 
    set_cact_time(5);
    add_cact("shout all outlanders must die!");
    add_cact("emote hisses: You shall not live to tell of us.");
    add_cact("say I'll quarter you and hang you out to dry!");
    add_cact("say I should get a good bounty for killing you!");
    add_cact("say You'll wish you never came to this forest!");
    add_cact("say You'll soon be food for the wolves!");
 
    set_stats(({ 30, 30, 30, 20, 20, 30})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_AXE, 30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_hp(10000);
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
