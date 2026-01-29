/* ARGOS City - Glass Blower
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
string *intro_resp_cmd=(({"introduce myself",
                          "say Careful not to break anything.",
                          "emote eyes you carefully."}));
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
    set_name("Gaulios");
    add_name(({"gaulios","keeper","argosian"}));
    set_title("Crystal Artisan of Argos");
    set_adj("tall");
    set_adj("tanned");
    set_race_name("human");
    set_long(
        "He is a tall tanned human, one of the gifted artisans of the "+
        "city. He creates both beautiful and useful objects from glass "+
        "and crystal.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles happily");
    add_act("say Would you like to buy a hand made bottle?");
    add_act("say Be careful not to break anything.");
    add_act("emote eyes you worriedly.");
    add_act("say My finer works are not for sale to visitors.");
 
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
 
 
