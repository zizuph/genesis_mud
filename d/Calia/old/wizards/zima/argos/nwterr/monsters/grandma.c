/* ARGOS - Vineyard Keeper's Grandmother - part of tour in metro area
** Tour: get a newly made tunic and cloak for her, return to Alexis in park
** by Alexis
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/28/95   Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
#include METRO_TOURS_DEF
int TunicGiven=0;
int CloakGiven=0;
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Giagia");
    add_name(({"grandmother","human","argosian","giagia"}));
    set_title("Retired Vineyard Keeper");
    set_adj(({"plump","silver-haired"}));
    set_race_name("human");
    set_gender(G_FEMALE);
    set_short("plump silver-haired human");
    set_long(
        "She is a plump silver-haired grandmother with her hair wrapped "+
        "up in a bun on her head. She is dressed in an old, juice-stained "+
        "tunic. She looks like she could use some new clothes.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
 
    set_act_time(5);
    add_act("emote dusts around the hovel.");
    add_act("say These clothes are old but they'll do me just fine.");
    add_act("say I can't pick grapes the way I used to.");
    add_act("say Don't track dirt into my clean house!");
    add_act("emote smiles motherly.");
 
    set_stats(({ 20, 20, 20, 20, 20, 20})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(query_max_hp());
    set_alignment(100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
/*********************** response to introductions *********************/
void intro_me() {
      command("introduce myself");
      command("say Good day to you!");
      command("say My grandson is in the vineyards, if you're looking "+
              "for him.");
}
 
public void add_introduced(string name) {
   if (this_player()->query_npc()) return;
   set_alarm(2.0,0.0,"intro_me");
}
 
 
/******************* check of objects given to me ***********************/
void object_given(object ob, object from) {
   string ObName  =lower_case(ob->query_name());
   string FromName=lower_case(from->query_name());
 
   if (!(living(from))) return;
 
   if (((from->query_prop(ARGOS_TOUR_PROP))==ON_GRANDMA_QUEST)&&
      ((ob->id(ARGOS_NEW_TUNIC))||(ob->id(ARGOS_NEW_CLOAK)))) {
         if (ob->id(ARGOS_NEW_TUNIC)) {
            TunicGiven=1;
            command("say Thank you! It is beautiful!");
         }
         if (ob->id(ARGOS_NEW_CLOAK)) {
            CloakGiven=1;
            command("say Thank you! You are so nice to bring this!");
         }
         command("say I'll put it away for a special occassion.");
         command("emote puts away the "+ObName+".");
         ob->remove_object();
 
         if (CloakGiven&&TunicGiven) {
            command("hug "+FromName);
            command("say Give Alexis my thanks for sending you!");
            command("emote smiles gratefully.");
            from->add_prop(ARGOS_TOUR_PROP,GRANDMA_QUEST_DONE);
            TunicGiven=0; CloakGiven=0;
         }
         return;
   }
 
   /* not officially on tour or gave unknown object */
   command("say Oh no, I can't take this.");
   command("say Sometimes Alexis sends me things, but he didn't tell me "+
           "you were coming.");
   command("give "+ObName+" to "+FromName);
   command("drop "+ObName); /* just in case give didn't work */
   command("say Thank you anyway.");
}
 
public void enter_inv(object ob, object from) {
   ::enter_inv(ob,from);
   set_alarmv(2.0,0.0,"object_given",({ob,from}));
}
