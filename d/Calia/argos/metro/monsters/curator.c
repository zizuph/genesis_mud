/* ARGOS - metro - Curator of the museum in the Library
** Gives hints to Cassock Quest if player has been sent on the quest
** by Alexis
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
string *intro_resp_cmd=(({"introduce myself","say Did you see the thief?",
                          "emote raises his eyes hopefully.",
                          "emote paces the floor."}));
#include "defs.h"
#include "../tours.h"
#define GO_AWAY "say I can't talk with you now. Go visit Alexis in the park."
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"nobtunic")->move(this);
    clone_object(ARMOUR_DIR+"nobcloak")->move(this);
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Epsoros");
    add_name(({"curator","human","argosian","epsoros"}));
    set_title("Curator of the Alexian Collection");
    set_adj(({"fat","silver-haired"}));
    set_race_name("human");
    set_long(
        "He is the curator of the collection of objects and artwork "+
        "of the travels of Alexis on display in the library's museum. "+
        "He looks rather upset about something.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
 
    set_act_time(5);
    add_act("emote paces the floor.");
    add_act("emote mumbles angrily to himself.");
    add_act("emote paces the floor.");
    add_act("say The thief should be executed!");
    add_act("say If only I'd gotten a better look at the thief!");
    add_act("say How could this happen in broad daylight?");
    add_act("emote sighs dejectedly");
    add_act("emote throws his hands up in frustration.");
    add_act("emote eyes the ninth pedestal worriedly.");
 
    set_default_answer(QCTNAME(this_object())+" says: What did you say? "+
                       "I don't know what to do.\n");
    add_ask(({"pedestal","about pedestal","ninth pedestal",
              "about ninth pedestal"}), "@@ask_pedestal",1);
    add_ask(({"item","object","stolen object","stolen item","cassock",
              "about item","about object","about stolen object",
              "about stolen item","about cassock"}),
              "@@ask_object",1);
    add_ask(({"thief","thieves","about thief","about thieves","robbery",
              "about robbery","theft","about theft"}),
              "@@ask_thief",1);
    add_ask(({"tunic","green tunic","axe","about tunic","about green tunic",
              "about axe"}), "@@ask_tunic",1);
    add_ask(({"calathin","Calathin","about calathin","about Calathin",
              "priest","about priest"}), "@@ask_priest",1);
    add_ask(({"alexis","Alexis","about alexis","about Alexis"}),
              "@@ask_alexis", 1);
    add_ask(({"quest","tour","job","for quest","for tour","for job",
              "about quest","about tour","about job"}),
              "@@ask_tour",1);
    add_ask(({"painting","paintings","about painting","about paintings"}),
              "@ask_painting",1);
 
    set_stats(({ 40, 40, 40, 40, 40, 40})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
 
/******************* check of objects given to me ***********************/
void object_given(object ob, object from) {
   if (!(living(from))) return;
   if (ob->id(STOLEN_CASSOCK))
      if ((from->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST) {
         from->add_prop(ARGOS_TOUR_PROP,CASSOCK_QUEST_DONE);
         command("say You found it!");
         command("say May the Tritheon bless you!");
         command("say Return to Alexis with my blessing.");
         command("say I must clean it immediately");
         command("emote hurries out of the room.");
         ob->remove_object();
         remove_object();
         }
      else {
         command("say Where did you get this? I did not tell you "+
                 "to search for this.");
         command("say You probably stole it. You better talk to "+
                 "Alexis before you do things like this.");
         command("say He knows how to handle these things.");
         command("emote gives you a stern suspicious look.");
         ob->remove_object();
      }
   else {
      command("say What do I want with this trash? Take it away.");
      command("give "+(ob->query_name())+" to "+
              (lower_case(from->query_name())));
   }
 
}
 
public void enter_inv(object ob, object from) {
   ::enter_inv(ob,from);
   set_alarmv(2.0,0.0,"object_given",({ob,from}));
}
 
/******************* responses to questions asked ***********************/
string ask_pedestal() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say The item that was on it was stolen. I wish you "+
              "could find it.");
   return (GO_AWAY);
}
 
string ask_object() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say It was a white cassock given to Alexis by a priest "+
              "while he was in Calathin. It is irreplacable!");
   return (GO_AWAY);
}
 
string ask_thief() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say I didn't get a good look at him, only that he was "+
              "wearing a green tunic and wielding a common axe.");
   return (GO_AWAY);
}
 
string ask_priest() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say A priest gave the cassock to Alexis in Calathin "+
              "long ago. He is dead now and it can't be replaced.");
   return (GO_AWAY);
}
 
string ask_alexis() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say He did not see the thief and is very upset about "+
              "the robbery.");
   return ("say He is usually in the park. Why don't you go see him?");
}
 
string ask_tour() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say An object has been stolen from here. Return the "+
              "stolen object and I shall be eternally thankful!");
   return ("say Go see Alexis in the park and then come back.");
}
 
string ask_painting() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say Yes the paintings are beautiful but I am too "+
              "worried to enjoy them. They can't help me now");
   return (GO_AWAY);
}
 
string ask_tunic() {
   if ((this_player()->query_prop(ARGOS_TOUR_PROP))==ON_CASSOCK_QUEST)
      return ("say The thief was wearing a green tunic with an axe "+
              "on it. I don't know what that means.");
   return (GO_AWAY);
}
