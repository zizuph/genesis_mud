/* ARGOS City - Bartender in Pub
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
string *intro_resp_cmd=(({"introduce myself","say Welcome to my pub! "+
                          "How about some retsina?","emote raises his eyebrows hopefully."}));
#include "defs.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(ARMOUR_DIR+"cztunic")->move(this);
    clone_object(ARMOUR_DIR+"czcloak")->move(this);
    command("wear all");
    MONEY_MAKE_SC(random(3))->move(this);
    MONEY_MAKE_CC(random(15))->move(this);
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Ouzophilus");
    add_name(({"ouzophilus","bartender","argosian"}));
    set_title("Master of Fine Argosian Spirits");
    set_adj("sweaty");
    set_adj("stout");
    set_race_name("human");
    set_long(
        "He is the bartender, the owner and operator of the pub. " +
        "From the sweat on his face he looks like he's been working "+
        "hard.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles happily");
    add_act("say Try my ouzo, it's the best.");
    add_act("say A little retsina will take the sting from your travels.");
    add_act("emote arranges some bottles behind the bar.");
    add_act("emote dusts the bar with a cloth.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({40,50,40,20,20,40}));
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
