/* ARGOS City - Seamstress in the Wool Works
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
string *intro_resp_cmd=(({"introduce myself",
     "say We do fine work here. Is there anything I can make for you?",
      "smile hopefully"}));
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
    set_name("Rapstesia");
    add_name(({"rapstesia","keeper","argosian","seamstress"}));
    set_title("Seamstress of Argos");
    set_adj("old");
    set_adj("gray-haired");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_long(
        "She is an old gray-haired lady, one of the talented seamstresses "+
        "of the city. She is an expert at making anything with wool. "+
        "She looks like she might have a short temper though.\n");
 
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
 
