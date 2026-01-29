/* ARGOS City - Pigeon Shop Keeper
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/11/95  Created
**
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({
   "introduce myself","say My birds know all the lands. Would you like "+
   "to buy one?","emote raises his eyebrows hopefully."}));
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
    set_name("Peristeri");
    add_name(({"peristeri","keeper","argosian"}));
    set_title("Pigeon Trainer of Argos");
    set_adj("dirty");
    set_adj("long-nosed");
    set_race_name("human");
    set_long(
        "He is a dirty long-nosed human, the one who tends to the "+
        "beautiful but slightly smelly caged birds. He reaks with the "+
        "odor of his trade.\n");
 
    set_default_answer(QCTNAME(this_object())+" looks confused.\n");
    add_ask(({"feather","quill","feathers","quills","for feather","for quill",
     "for feathers","for quills","about feather","about quill",
             "about feathers","about quills"}),
            "say I give all the feathers to the Bursar at the bank",1);
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles happily");
    add_act("say My birds know all the lands.");
    add_act("say I run a very clean establishment, considering...");
    add_act("emote checks a pigeon in its cage.");
    add_act("say You won't find stronger birds anywhere!");
 
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
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
