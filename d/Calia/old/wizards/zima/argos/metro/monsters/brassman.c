/* ARGOS City - Brass Tinker of Argos
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/25/95  Created
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({
   "introduce myself","say Would you like to buy some of my work?",
   "emote smiles hopefully."}));
#include "defs.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Mproutzo");
    add_name(({"mproutzo","keeper","argosian","tinker"}));
    set_title("Brass Tinker of Argos");
    set_adj("olive-skinned");
    set_adj("brown-eyed");
    set_race_name("human");
    set_long(
        "He is an olive-skinned brown-eyed human, one of the many gifted "+
        "artisans of Argos. He makes both beautiful and useful objects "+
        "from precious metals, especially brass.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles happily");
    add_act("say Would you like to buy a lamp?");
    add_act("say Be careful not to break anything.");
    add_act("emote eyes you worriedly.");
    add_act("say My finer works are not for sale to visitors.");
    add_act("say Orichalcum is a very precious metal here.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say Its outlanders like you who cause our problems!");
    add_cact("say You may kill me, but you will not get one cent!");
    add_cact("say May the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say May the Tritheon curse you and all your kind!");
 
    set_stats(({40,50,40,20,20,40}));
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(query_max_hp());
    set_alignment(100);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
