/* ARGOS - Temple of Pharos - Outdoor priest
** This priest is needed for one of the tours in the Metro area.
** He is cloned on the temple portico. When a player has a bottle of
** new grape juice (gotten in argos/metro/press), he can ask the priest
** to bless the juice. The priest will bless the juice and turn it into
** new wine.
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/27/95   Created
*/
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
#include METRO_TOURS_DEF
 
void equip_me() {
    object this=this_object();
    clone_object(ARMOUR_DIR+"tunic")->move(this);
    clone_object(ARMOUR_DIR+"ring")->move(this);
    command("wear all");
}
 
void create_monster() {
    if (!IS_CLONE) return;
    set_name("Presboter");
    add_name(({"priest","pharosian","human","argosian","presboter"}));
    set_title("Priest of the Order of Pharos");
    set_adj(({"gentle","slim"}));
    set_race_name("human");
    set_long(
        "He is a slim young man with a clean-shaven face which has a "+
        "boyish gentle quality about it. He is is dressed in the garb "+
        "of a Pharosian priest.\n");
 
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    /* these actions keep him on the portico */
    set_act_time(20);
    add_act("north");
    add_act("south");
 
    set_default_answer(QCTNAME(this_object())+" smiles gently.\n");
    add_ask(({"wine","for wine","about wine"}),"@@ask_wine",1);
    add_ask(({"blessing","for blessing","to bless juice",
              "to bless grape juice","to bless bottle",
              "to bless bottle of juice","to bless bottle of grape juice"}),
              "@@ask_blessing",1);
 
    set_stats(({ 20, 100, 100, 20, 20, 100})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(query_max_hp());
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
 
/*********************** response to introductions *********************/
void intro_me() {
      command("introduce myself");
      command("say Greetings. May the Peace of Pharos be with you.");
      command("emote smiles gently.");
}
 
public void add_introduced(string name) {
   if (this_player()->query_npc()) return;
   set_alarm(2.0,0.0,"intro_me");
}
 
/******************* "spell" to bless juice into wine ********************/
void bless_juice(object Tp, object juice, int step) {
   object To=this_object();
   object Tr=environment(To);
   object wine;
 
   if (!(present(Tp,Tr))) return;              /* player has left */
   if (!(present(juice,Tp))) return;           /* juice is gone   */
 
   switch (step) {
      case 1:
         command("emote closes his eyes and takes in a deep breath.");
         break;
      case 2:
         Tp->catch_msg(QCTNAME(To)+" holds his hands over you.\n");
         tell_room(Tr,QCTNAME(To)+" holds his hands over "+QTNAME(Tp),Tp);
         command("emote starts to mumble in an unknown language.");
         break;
      default:
         tell_room(Tr,"There is a flash of purple light then everything "+
                      "seems normal again.\n");
         command("emote smiles mysteriously.");
         juice->remove_object();
         wine=clone_object(OBJ_DIR+"new_wine");
         wine->move(Tp);
         return;
         break;
   }
   set_alarmv(3.0,0.0,"bless_juice",({Tp,juice,(step+1)}));
}
 
/******************* responses to questions asked ***********************/
string ask_wine() {
   if (present(ARGOS_GRAPE_JUICE,this_player())) {
      command("say I have no wine but I can bless that bottle of "+
              "juice you have and turn it into wine.");
      return("say Just ask me for a blessing");
      }
   else
      return("emote looks at you puzzled.");
}
 
string ask_blessing() {
   object Tp=this_player();
   object bottle=present(ARGOS_GRAPE_JUICE,Tp);
 
   if (bottle) {
      set_alarmv(3.0,0.0,"bless_juice",({Tp,bottle,1}));
      return("emote nods his head.");
      }
   else
      return("say I will only bless a bottle of grape juice for you.");
}
