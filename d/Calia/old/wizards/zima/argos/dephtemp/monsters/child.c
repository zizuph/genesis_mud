/* A child in the Temple
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/95    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
 
#define Eyes ({"blue","brown","green","gray","black"})
#define Hair ({"blonde","brown","red","black","auburn","white"})
#define Toys ({"toysword","doll","toyhorse","toyclub"})
 
void equip_me() {
    object this=this_object();
    clone_object(OBJ_DIR + Toys[(random(sizeof(Toys)))])->move(this);
    clone_object(ARMOUR_DIR + "chtunic")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    int     gender=random(2);
    string  Poss;
 
    if (!IS_CLONE) return;
 
    if (gender) {
       set_name(({"girl","dephonian","human","child"}));
       set_race_name("girl");
       Poss="her";
       set_gender(G_FEMALE);
       set_long("She is one of the children who lives in the temple. "+
                "She has a decievingly sweet smile on her face.\n");
       }
    else {
       set_name(({"boy","dephonian","human","child"}));
       set_race_name("boy");
       Poss="his";
       set_long("He is one of the children who lives in the temple. "+
                "He has a devious look in his eyes.\n");
    }
    set_adj(Eyes[(random(sizeof(Eyes)))]+"-eyed");
    set_adj(Hair[(random(sizeof(Eyes)))]+"-haired");
 
    set_act_time(5);
    add_act("say Do you have a gift for me?");
    add_act("emote kicks you in the leg and runs across the room.");
    add_act("emote smacks your arm with "+Poss+" toy and giggles.");
    add_act("emote runs around the room flaying "+Poss+" toy.");
    add_act("emote smiles deviously.");
    add_act("say Are you the monster the mistress tells us about?");
    add_act("say Your face is ugly!");
    add_act("say Why do you have so many scars?");
    add_act("say Did you come to play with us?");
 
    set_cact_time(4);
    add_cact("emote screams in terror.");
    add_cact("shout Help! The monster is here to get me!");
    add_cact("emote cries in an ear-bursting wail.");
    add_cact("emote throws a toy at you.");
    add_cact("emote screams bloody murder.");
    add_cact("emote trembles and falls weakly.");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    add_prop(ATTACK_PASSIVE,1);
 
    set_stats(({ 5, 5, 5, 5, 5, 5})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_CLUB, 5);
    set_skill(SS_PARRY, 5);
    set_skill(SS_DEFENCE, 5);
    set_hp(1000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT,  40000);
    add_prop(CONT_I_VOLUME,  40000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
