/* ARGOS City - Grand Master of the Thespian Guild
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
string *intro_resp_cmd=(({"introduce myself","emote bows nobly",
                          "say Greetings stranger."}));
#include "defs.h"
#include "citizen.h"
#include "../tours.h"
 
void equip_me() {
    /* this function should be called in the room which clones the npc */
    object this=this_object();
    clone_object(WEAPON_DIR+"czstaff")->move(this);
    clone_object(ARMOUR_DIR+"thesp_mstr_robe")->move(this);
    command("wear all");
    command("wield all");
}
 
void create_monster() {
    string Name="Dramaticus";
    string Adj1="husky";
    string Adj2="bearded";
 
    if (!IS_CLONE) return;
    set_name(Name);
    add_name(({(lower_case(Name)),"thespian","argosian"}));
    set_title("Grand Master of the Thespian Guild");
    set_adj(({Adj1,Adj2}));
    set_race_name("human");
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_alignment(100);
    set_long(
        "He is a "+Adj1+" "+Adj2+" man, dressed in the robes of the "+
        "Grand Master of the Thespian Guild. His face seems to portray "+
        "his creativity as well as his leadership.\n");
 
    set_act_time(5);
    add_act("say We'll never get to act until this insurrection is over.");
    add_act("say It's too dangerous to go outside and look for herbs.");
    add_act("say Visitors are in town now and they'll never see our drama.");
    add_act("say There is no need to practice while all is on hold.");
    add_act("say I wish I had a bottle of new wine.");
    add_act("emote glances at you suspiciously.");
    add_act("say I would really like a bottle of new wine.");
    add_act("emote stares at you puzzled.");
 
    set_cact_time(3);
    add_cact("say its outlanders like you who cause our problems!");
    add_cact("say may your head be chopped off!");
    add_cact("emote curses loudly in a foreign tounge.");
    add_cact("say may the Tritheon curse you and all your kind!");
 
    set_stats(({70,70,70,70,70,70}));
    set_skill(SS_PARRY, 70);
    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_DEFENCE, 70);
    set_hp(query_max_hp());
    add_prop(CONT_I_WEIGHT, 105000);
    add_prop(CONT_I_VOLUME, 105000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
/******************* check of objects given to me ***********************/
void object_given(object ob, object from) {
   string FromName=lower_case(from->query_name());
   string ObName=lower_case(ob->query_name());
 
   if (!(living(from))) return;
 
   if (ob->id(ARGOS_NEW_WINE))
      if ((from->query_prop(ARGOS_TOUR_PROP))==ON_WINE_QUEST) {
         /* object is new wine and is on quest */
         command("say Thank you stranger!");
         command("say Alexis has sent you. He knows how to cheer me up.");
         command("say Go back to him and give him my gratitude.");
         command("emote bows with a dramatic flair.");
         command("drink all");
         command("burp");
         command("smile happily");
         from->add_prop(ARGOS_TOUR_PROP, WINE_QUEST_DONE);
      }
      else {
         /* object new wine but not officially on quest */
         command("say I wasn't expecting this. Who is this from?");
         command("say I'm sorry, but I can't trust things from strangers "+
                 "these days.");
         command("say Now if Alexis sent you, that would be different.");
         command("give wine to "+FromName);
         command("drop wine"); /* in case give didn't work */
      }
   else {
      /* object not new wine */
      command("say What is this? I don't want this now!");
      command("give "+ObName+" to "+FromName);
      command("drop "+ObName); /* in case give didn't work */
   }
}

public void enter_inv(object ob, object from) {
   ::enter_inv(ob,from);
   set_alarmv(2.0,0.0,"object_given",({ob,from}));
}
