/* Hierophant of Dephonia, in her chambers.
** See rooms/hiercham for additional special attack she has
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
int SpecAttackLevel=500; /* she's the strongest, of course */
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "staff")->move(this);
    clone_object(ARMOUR_DIR + "hierrobe")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"hierring")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Delphiana");
    add_name(({"dephonian","priestess","hierophant","human"}));
    set_adj(({"Dephonian","powerful"}));
    set_race_name("high priestess");
    set_short("powerful Dephonian high priestess");
    set_title("the Hierophant of Dephonia");
    intro_resp_cmd=(({"introduce myself",
                      "emote chants: Praised be the Light of Darkness!",
                      "emote bows her head prayerfully."}));
    set_long(break_string(
        "This enchanting woman is the leader of the Order, a woman " +
        "of enchanting beauty and mysteriously strong power. She "+
        "seems preoccupied with her meditations at the moment.\n",70));
 
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
    set_gender(1); /* female */
 
    set_act_time(5);
    add_act("emote kneels at the altar and prays.");
    add_act("emote whispers a chant to herself.");
    add_act("say Go to the reception room, I shall be there soon.");
    add_act("emote glances at you suspiciously.");
    add_act("emote bows her head reverently before the altar.");
    add_act("say What do you need?");
    add_act("smile mysteriously");
    add_act("emote raises her hands and whispers a prayer.");
    add_act("emote admires the tapestry on the wall.");
    add_act("emote glances into the wardrobe wonderingly.");
#include "dephcact.h"
 
    set_stats(({150,150,150,150,150,90})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_hp(10000);
    set_alignment(-350);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
