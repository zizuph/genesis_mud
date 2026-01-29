/* ARGOS - metro - Alexis, the Quest Master of Argos
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/11/95   Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
string *intro_resp_cmd=(({"introduce myself","say Welcome to Argos!",
                          "say You may ask me for a tour if you like!",
                          "smile"}));
#include "defs.h"
#include "../tours.h"
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    clone_object(WEAPON_DIR+"czstaff")->move(this);
    clone_object(ARMOUR_DIR+"nobcloak")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Alexis");
    add_name(({"alexis","human","argosian"}));
    set_title("Sage of Argos");
    set_adj(({"gray-haired","bearded"}));
    set_race_name("human");
    set_long(
        "He is a gray-haired bearded man with a balding head. He is "+
        "very old, but his eyes seem to be full of life and happiness "+
        "as well as wisdom.\n");
 
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK,1);
 
    set_act_time(5);
    add_act("north"); /* these directions limit him to the park    */
    add_act("south"); /* where he is supposed to be, as opposed to */
    add_act("east");  /* letting him wander around everywhere      */
    add_act("west");
    add_act("emote breaths in the fresh air, smiling.");
    add_act("emote dips his stick in the pool.");
    add_act("say I remember my days travelling. What an adventure!");
    add_act("say Ask me about tours. I can give you some help.");
    add_act("say Ask me about tours. I can give you some help.");
    add_act("say Ask me about tours. I can give you some help.");
    add_act("say I should visit Gelan again soon.");
    add_act("say Calathin, now there's an interesting city.");
    add_act("say No one believed me when I told them about a land of hobbits!");
    add_act("say Gondor is a vast and dangerous land, but well worth the "+
            "trip.");
    add_act("say My days in Re-Albi were short. I wish I'd stayed longer.");
    add_act("say I can send you off on tours of the city, if you like.");
    add_act("say There is much to see here. I hope you enjoy your visit.");
 
    set_default_answer(QCTNAME(this_object())+" says: What did you say? "+
                       "Are you asking me about tours?\n");
    add_ask(({"tour","tours","about tour","about tours","for tour",
              "for tours","for a tour"}),"@@ask_tour",1);
    add_ask(({"reward","for reward","for a reward"}),"@@ask_reward",1);
 
    set_stats(({ 80, 80, 80, 80, 80, 80})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
#include "alexis.ext"
 
/*********************** response to asks  ***************************/
string ask_tour() {
   /* see explanations of values of Prop in metro/tours.h */
   object Tp=this_player();
   int    Prop=Tp->query_prop(ARGOS_TOUR_PROP);
 
   if (Prop==ON_NO_TOUR) {
      /* player hasn't been given a tour and didn't just finish a tour */
      give_tour(Tp);
      return ("say May the Tritheon be with you!");
   }
   if (Prop<DONE_SOME_TOUR) {
     /* player already given tour not solved */
     repeat_give_tour(Tp);
      return ("say May the Tritheon go with you!");
   }
   /* otherwise, Prop > DONE_SOME_TOUR, so player just finished some tour */
   tell_ask_reward();
   return("smile happily");
}
 
string ask_reward() {
   /* see explanations of values of Prop in metro/tours.h */
   object Tp=this_player();
   int    Prop=Tp->query_prop(ARGOS_TOUR_PROP);
 
   if (Prop==ON_NO_TOUR) {
      /* player hasn't been given a tour and didn't just finish a tour */
      tell_ask_tour();
      return ("whitle innocently");
   }
   if (Prop<DONE_SOME_TOUR) {
     /* player already given tour but not solved */
     tour_not_done(Tp);
     return ("sigh");
   }
   /* otherwise, Prop > DONE_SOME_TOUR, so player just finished some tour */
   reward_tour(Tp);
   return("smile happily");
}
