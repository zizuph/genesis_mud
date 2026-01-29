/* ARGOS - metro - Chariot depot attendant
** Summons chariots and collects fees at the depots of the chariot transport
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           9/24/95   Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
string DepotRoom="none";
string *intro_resp_cmd=(({"introduce myself",
                          "say Ask me to summon a chariot for you and "+
                          "I shall do so.",
                          "emote bows deeply.",
                          "say I am at your service."}));
#include "defs.h"
#include "names.c"
 
void equip_me() { return; }
 
void set_this_depot(string room) {
   /* called from within cloning room when this NPC cloned */
   DepotRoom=room;
}
 
string query_depot_room() { return DepotRoom; }
 
void create_monster() {
    string Name=random_name();
    if (!IS_CLONE) return;
    set_name(Name);
    add_name(({"attendant","human","argosian",(lower_case(Name))}));
    set_title("Attendant of the Royal Argosian Chariot Service");
    set_adj(({"well-built","middle-aged"}));
    set_race_name("human");
    set_long(
        "He is the attendant of the chariot depot, dressed in a long "+
        "blue tunic bearing the royal arms of Argos and wearing an "+
        "amulet of protection. You may ask him to summon a chariot "+
        "and pay him the fee when the chariot arrives.\n");
 
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK,1);
    set_default_answer(QCTNAME(this_object())+" says: What did you say? "+
                       "Ask me to summon a chariot and I shall do so.\n");
    add_ask(({"summons","summon","chariot","summon chariot","summons chariot",
              "to summons chariot","to summon chariot","to summon a chariot",
              "to summons","to summon",
              "to summons a chariot","to summon the chariot",
              "to summons the chariot"}),"@@call_chariot",1);
 
    set_stats(({ 40, 40, 40, 40, 40, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
string call_chariot() {
   int     waiting=(DepotRoom->query_waiting());
   object  RoomPtr=(DepotRoom->pointer_me());
   object  To=this_object();
 
   if (!(present(To,RoomPtr)))
      return("say I am afraid I can't do that here.");
 
   if (DepotRoom->query_chariot_here())
      return("say The chariot is already here.");
 
   if (!(waiting)) {
      command("emote whistles shrilly.");
      DepotRoom->summons_chariot();
   }
   return ("say The chariot is on its way.");
}
