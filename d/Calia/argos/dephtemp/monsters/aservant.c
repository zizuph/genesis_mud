/* A servant in the Temple
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
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR + "slvtunic")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    int     gender=random(2);
    string  Poss;
 
    if (!IS_CLONE) return;
 
    set_name(({"servant","dephonian","argosian","human"}));
    set_race_name("human");
    if (gender) {
       Poss="her";
       set_long("She is one of the servants of the temple, probably "+
                "captured from the nearby city of Argos during her "+
                "childhood. She has a reserved smile on her face.\n");
          set_gender(1); /* female */
       }
    else {
       Poss="his";
       set_long("He is a servant in the temple, probably captured during "+
                "a skirmish with the Argosian army. He looks strong "+
                "but somewhat humbled.\n");
    }
    set_adj(Eyes[(random(sizeof(Eyes)))]+"-eyed");
    set_adj(Hair[(random(sizeof(Eyes)))]+"-haired");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(5);
    add_act("say May I help you?");
    add_act("emote hums an old Argosian tune.");
    add_act("emote brushes some dust from "+Poss+" tunic.");
    add_act("emote looks at you wonderingly.");
    add_act("emote smiles contentedly.");
    add_act("say You must be lost. The conference is on the lower level.");
    add_act("say I have never seen you before.");
 
    set_cact_time(4);
    add_cact("emote drops "+Poss+" mouth open as his eyes widen in fear.");
    add_cact("shout Guards! There's an intruder in the temple!");
    add_cact("say Do you think you will escape here?");
    add_cact("say There is no escape from here, you will die!");
    add_cact("emote holds "+Poss+" hand in front of "+Poss+"face.");
    add_cact("emote turns "+Poss+" eyes upwards and prays.");
    add_cact("say May Arxes protect me!.");
 
    set_stats(({ 15, 15, 15, 15, 15, 15})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 15);
    set_skill(SS_DEFENCE, 20);
    set_hp(1000);
    set_alignment(150);
    add_prop(CONT_I_WEIGHT,  90000);
    add_prop(CONT_I_VOLUME,  90000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
