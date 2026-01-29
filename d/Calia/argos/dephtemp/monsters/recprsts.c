/* Priestess of Dephonia, in the Reception Chamber, greeting guests
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/1/94    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
int SpecAttackLevel=60;
#include "dephatck.h"
 
void equip_me() {
    object this=this_object();
    clone_object(WEAPON_DIR + "staff")->move(this);
    clone_object(ARMOUR_DIR + "tunic")->move(this);
    clone_object(ARMOUR_DIR + "bplate")->move(this);
    clone_object(ARMOUR_DIR+"dring2")->move(this);
    command("wield all");
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"dephonian priestess","priestess","dephonian",
               "human"}));
    set_adj("dephonian");
    set_race_name("human");
    set_short("priestess of Dephonia");
    set_pshort("priestesses of Dephonia");
    set_long(
        "Dressed in full ceremonial garb, she is a priestess of the " +
        "Order of Dephonia. " +
        "She is an enchantingly beautiful woman, though someone you feel " +
        "you must never turn your back on. She is here to welcome those "+
        "invited to the conference.\n");
 
    add_prop(NPC_I_NO_LOOKS,1);
    set_gender(1); /* female */
    add_prop(ATTACK_TEAM,DEPH_ATTACK_TEAM);
 
    set_act_time(5);
    add_act("say Welcome to our allies from Kretos and Argos.");
    add_act("say Our alliance will be mutually beneficial.");
    add_act("say the remaining conferees should be here shortly.");
    add_act("say please take some food from the tray.");
    add_act("emote smiles confidently.");
    add_act("emote eyes you suspiciously.");
    add_act("emote sniffs impatiently.");
    add_act("emote checks the tray to see what is left.");
#include "dephcact.h"
 
    set_stats(({ 60, 60, 60, 60, 60, 60})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(-200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
