/* ARGOS - metro - Noblewoman in the visitors center
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/5/95    Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({
   "introduce myself", "emote bows elegantly.",
   "say Welcome to Argos! Help your self to any remaining refreshments!",
   "emote gestures at the tray."}));
#include "defs.h"
#include "../tours.h"
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    clone_object(ARMOUR_DIR+"nobcloak")->move(this);
    clone_object(ARMOUR_DIR+"pnobring")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name(({"Kalosori","kalosori","noblewoman","woman","human"}));
    set_title("Noblewoman of Argos of House Pistus");
    set_adj(({"charming","voluptuous"}));
    set_race_name("human");
    set_long(
        "She is a noblewoman of Argos here to welcome visitors "+
        "to the city. She has a charming smile and a shapely figure, "+
        "a very attractive choice for her position.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    set_gender(1); /* female */
    add_prop(NPC_I_NO_LOOKS,1);
 
    set_act_time(5);
    add_act("emote smiles charmingly.");
    add_act("emote greets you warmly.");
    add_act("say I hope you enjoy your visit to our beautiful city.");
    add_act("emote glances at you enchantingly.");
    add_act("say You should visit with Alexis in the park.");
    add_act("emote eyes the silver tray on the stand.");
    add_act("emote reads the book on the pedestal.");
 
    set_default_answer(QCTNAME(this_object())+" says: I am afraid I don't "+
                       "understand you.\n");
    add_ask(({"pedestal","book","registry","about pedestal","about book",
               "about registry"}),
              "say The book on the pedestal is a registry for visitors "+
              "to sign.",1);
    add_ask(({"quill","pen","pencil","for quill","about quill",
              "for pen","about pen","for pencil","about pencil" }),
              "@@ask_quill",1);
    add_ask(({"sign","about sign","about signing","about signing book",
              "about signing registry","how to sign","signing",
              "how to sign book","how to sign registry"}),
              "say You need a quill to sign the Registry.",1);
    add_ask(({"Alexis","alexis","about alexis","about Alexis"}),
              "say He is the Sage of Argos who has travelled the world and "+
              "is very wise. He usually stays in the park.\n",1);
    add_ask(({"bursar","Bursar","about bursar","about Bursar"}),
              "say He is in charge of the Royal Bank of Argos.\n",1);
    add_ask(({"quest","tour","adventure","for quest","about quest",
              "for tour","about tour","for adventure","about adventure"}),
              "say Go ask Alexis about that.\n",1);
    add_ask(({"ink","about ink","for ink"}),
              "say You need to dip a quill in the ink to sign the Registry.",
              1);
    add_ask(({"chariot","chariots","about chariot","about chariots",
              "for chariot","for chariots"}),
              "say Chariots arrive at the Strathmos, at the corner of Detueros "+
              "and Chiphas streets. Just ask the attendant for a chariot.",1);
 
    set_stats(({ 40, 40, 40, 40, 40, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
string ask_quill() {
   object Tp=this_player();
   if ((Tp->query_prop(ARGOS_TOUR_PROP))==ON_REG_TOUR)
 
      return "say I do not have a quill, but I believe the Royal "+
             "Bursar will give you one.";
  else
     return "say I am sorry, the quill is gone and I don't have another.";
}
