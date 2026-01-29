/* Sacristan of Dephonia
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
int SpecAttackLevel=120;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "staff")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring3")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Daphthenia");
    add_name(({"priestess","dephonian","human","sacristan"}));
    set_adj(({"Dephonian","mysterious"}));
    set_race_name("priestess");
    set_title("the Sacristan of Dephonia");
    intro_resp_cmd=(({"introduce myself",
                  "emote places her hands together prayerfully and bows."}));
    set_short("mysterious Dephonian priestess");
    set_long(
        "She is a very pious priestess, in charge of maintaining "+
        "the sacred objects of the Order and of overseeing the "+
        "rite of the Vision. Though she is small in stature, she "+
        "is strong in her mysterious powers.\n");
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_gender(1); /* female */
 
    set_act_time(5);
    add_act("emote straightens the cloth on one of the pedestals.");
    add_act("emote whispers a chant to herself.");
    add_act("say Great is the blessing of she who performs the Rite.");
    add_act("emote glances at you suspiciously.");
    add_act("say all praise be to Our Mother forever and ever.");
    add_act("smile mysteriously");
    add_act("emote raises her hands and whispers a prayer.");
    add_act("say Have you been selected? I have not been told.");
    add_act("say You must be of proper state to perform the Rite.");
#include "dephcact.h"
 
    set_default_answer("The Sacristan of Dephonia says: I do not "+
                       "understand what you say.\n");
    add_ask(({"vision","of vision","about vision"}),
              "say The vision is truly a great revelation.\n",1);
    add_ask(({"quest","of quest","about quest"}),
              "say I can not help you in your quest for enlightenment.\n",1);
    add_ask(({"wine","of wine","about wine"}),
              "say Only sacred wine may receive the blessing.\n",1);
    add_ask(({"fruit","of fruit","about fruit","fruit of the vine",
              "of fruit of the vine","about fruit of the vine"}),
              "say The fruit of the vine is crushed by mortal hands, "+
              "that its blood may become sacred.\n",1);
    add_ask(({"blessing","of blessing","about blessing","for blessing"}),
       "say I may not bless you infidel.\n",1);
    add_ask(({"crescent","crescent","witness","witnesses",
               "about crescent","about crescents","about witness",
               "about witnesses"}),
       "say The crescents are the witnesses of our prayers.\n",1);
    add_ask(({"enlightenment","about enlightenment","for enlightenment"}),
       "say Enlightenment is received through the vision.\n",1);
    add_ask(({"medallion","about medallion"}),
       "say Only one who is shrouded in darkness may wear the medallion.\n",1);
    add_ask(({"dagger","about dagger"}),
       "say The power of the dagger can be channeled only by the Chosen "
      +"One.\n",1);
    add_ask(({"bowl","about bowl"}),
       "say It is the vessel of the water of life of the Innocent.\n",1);

   add_ask(({"innocent","innocent one","about innocent",
      "about innocent one"}),
      "say He is shrouded in the robe of the mountain tops, the "+
      "youngest of his kind, protected from all blades but one by "+
      "his innocence.\n",1);
 
    set_stats(({ 60, 60, 60, 60, 60, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(-300);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
