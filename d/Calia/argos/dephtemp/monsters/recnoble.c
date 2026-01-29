/*      An Argosian Nobleman, Loyal to Kretos, visiting the temple
**
** History
**   Date    Coder         Action
** -------- ------------  ----------------------------------
** 1/1/94   Zima          Created
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
    clone_object(OBJ_DIR+"nobring")->move(this);
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    clone_object(WEAPON_DIR+"dagger")->move(this);
    MONEY_MAKE_SC(20)->move(this);
    MONEY_MAKE_GC(6)->move(this);
    this->command("wield all");
    this->command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
 
    set_name(({"percletus","percletus","nobleman","argosian","human"}));
    set_title("Nobleman of Argos of the House of Benedictus");
    set_adj("elderly");
    set_race_name("human");
    set_short("elderly nobleman");
    set_long(
        "He is an elderly bearded nobleman of one of the houses of "+
        "Argos, a traitor to the king. He is well dressed and is "+
        "obviously very wealthy.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    add_prop(ATTACK_PASSIVE,1);
    set_act_time(5);
    add_act("emote sips on an ouzo from the tray.");
    add_act("emote eats a bachlava from the tray.");
    add_act("emote gives you a condescending look.");
    add_act("say there are many in the city who oppose the king.");
    add_act("introduce myself");
    add_act("say be assured our house will help in the overthrow.");
    add_act("emote stares at you suspiciously.");
    add_act("emote brushes some bachlava crumbs from his tunic.");
 
    set_cact_time(3);
    add_cact("say What an outrage! Infidels in the temple!");
    add_cact("emote tries to hide beneath the table.");
    add_cact("say It is because of infidels like you that we are at war.");
    add_cact("say Kretos' forces will kill you before you get out!");
    add_cact("say You think you can escape this temple now?");
    add_cact("emote smashes your face with his ring.");
    add_cact("emote throws ouzo in your eyes.");
 
    set_stats(({ 40, 40, 40, 40, 40, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_KNIFE, 70);
    set_hp(10000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
