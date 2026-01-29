/* ARGOS City - Inn Keeper
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
string *intro_resp_cmd=(({"introduce myself","say Welcome to my Inn!",
                          "say Can I offer you some food or a room?"}));
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
    set_name("Theros");
    add_name(({"theros","innkeeper","keeper","argosian"}));
    set_title("Innkeeper");
    set_adj("fat");
    set_adj("merry");
    set_race_name("human");
    set_long(
        "He is the keeper of the inn, his business open to provide "+
        "food and a place to stay for visitors to the city.\n");
 
    set_act_time(10);
    add_act("greet all");
    add_act("emote smiles happily");
    add_act("say Try the gemista, it's delicious.");
    add_act("say Bachlava is a favorite treat around here.");
    add_act("emote stirs the pots.");
    add_act("emote dusts the bar with a cloth.");
 
    set_cact_time(3);
    add_cact("shout Thief!! I am being robbed!");
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say you may kill me, but you will not get one cent!");
    add_cact("say may the Kretans chop off your head!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_default_answer(QCTNAME(this_object())+" says: What did you say? "+
                       "Are you asking about the room for rent?\n");
    add_ask(({"room","room for rent","rental","about room","about rental",
              "about room for rent","for room","for rental",
              "for room for rent"}),"@@ask_room",1);
 
    set_stats(({40,50,40,20,20,40}));
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
 
string ask_room() {
   command("say The room in my inn is very comfortable!");
   command("say It costs 8 silver coins to rent it for one night.");
   command("say All you have to do is 'rent room' here.");
   command("say You should read the card on the stand in the room first.");
   command("point south");
   return("say What do you think? Nice eh?");
}
