inherit "/std/object";
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO this_object()
#define TP this_player()
#define EN environment
#define SUBLOC "_plague_subloc_"

int progress;

string view;


int set_view(int n){
   progress = n;
}



heal_disease(int n){
  progress = progress - n;
}

add_plague(int n){
   progress = progress + n;
}


create_object(){
   
   set_name("_plague_");
   set_no_show(1);
   
   add_prop(OBJ_M_NO_DROP, 1);
   
   progress = 0;
}

query_auto_load(){
   return MASTER + ":" +progress;
}

show_subloc(string subloc, object carrier, object for_obj){
   
   string str;
   
   if(progress < 1) str = "";
   if(for_obj == carrier)
      str = "You are " + query_view() + ".\n";
   else
      str = capitalize(carrier->query_pronoun()) + " is " + query_view() + ".\n";
   return str;
}


check_spread(object who){
   object ob;
  if(present("_plague_", who)) return 0;
   if(who->query_prop("blessed")) return 0;
   if(!living(who)) return 0;
   if(who->query_stat(SS_CON) + who->query_skill(SS_SPELLCRAFT) +
         random(100) < 200){
      ob = clone_object("/d/Terel/mecien/valley/guild/spells/plague");
      ob->move(who);
   }
}


enter_env(object ob, object from){
   ::enter_env(ob, from);
   if(living(ob)){
      ob->catch_msg("You feel foul.\n");
      ob->add_subloc(SUBLOC, TO);
      set_alarm(12.0, 2.0, "do_plague", ob);
   }
}

cure_disease(){
   TO->remove_object();
}

leave_env(object ob, object to){
   ::leave_env(ob, to);
   if(living(ob)){
      ob->catch_msg("You feel as though something horrible has left you.\n");
      ob->remove_subloc(SUBLOC, TO);
   }
}

do_plague(object who){
  object ob;
   switch(progress){
      case 0:
      break;
      case 1:
      who->catch_msg("You feel a bit light headed.\n");
      break;
      case 2:
      who->catch_msg("You feel a bit sick to your stomach.\n");
      break;
      case 3:
      who->add_fatigue(-20);
      break;
      case 4:
      break;
      case 5..10:
      who->catch_msg("You feel itchy all over.\n");
      tell_room(EN(who), QCTNAME(who) + " starts itching all over.\n", who);
      who->add_fatigue(-20);
      break;
      case 11..20:
      if(random(10) > 6) who->command("cough");
      who->reduce_hit_point(20);
      tell_room(EN(who), "You smell something foul.\n", who);
      break;
      case 21..30:
      who->catch_msg("Small sores break out on your skin.\n");
      if(random(10) > 5) who->command("cough");
      if(random(10) > 8) who->command("puke");
      who->reduce_hit_point(10);
      break;
      case 31:
      who->catch_msg("You feel your sores are getting worse.\n");
      if(random(10) > 5) who->command("sneeze");
      break;
      case 32..50:
      who->add_fatigue(-20);
      tell_room(EN(who), "A foul stench emanates from " + QTNAME(who) + ".\n", who);
      if(random(10) > 2) who->command("cough");
      if(random(10) > 4){
         who->command("sneeze");
         who->catch_msg("You notice blood run from you nose as your sneeze.\n");
  }
      who->reduce_hit_point(20);
      break;
      case 51..80:
      who->command("shiver");
    if(random(10) > 7) who->command("moan");
      if(random(10) > 5){
         tell_room(EN(who), QCTNAME(who) + " hunches over and pukes out a bit of blood and pus.\n", who);
         who->reduce_hit_point(100);
         who->catch_msg("You hunch over and vomit out bloos and pus.\n");
   }
      if(random(10) > 7) who->command("sneeze");
      who->reduce_hit_point(10);
      who->add_fatigue(-20);
      map(all_inventory(EN(TP)), check_spread);
      break;
      case 81..90:
      who->catch_msg("Your liver and kidneys begin to shut down and poison your body.\n");
      ob = clone_object("/std/poison_effect");
      ob->move(who);
      ob->start_poison();
      tell_room(EN(who), QCTNAME(who) + " begins shaking, pus and blood running from open sores.\n", who);
      break;
      case 91..999:
      who->catch_msg("Your mind begins to fail as your body starts convulsing.\n");
      tell_room(EN(who), QCTNAME(who) + "'s eyes roll over, " + who->query_possessive() +
         " body shaking and convulsing.\n", who);
      who->add_fatigue(-100);
      who->reduce_hit_point(500);
      who->do_die();
      break;
      default:
      who->catch_msg("You feel sick.\n");
   }
   if(who->query_stat(SS_CON) + who->query_skill(SS_SPELLCRAFT) +
         random(100) < 250) progress++;
   
}

query_view(){
   switch(progress){
      case 91..999:
      view = "covered with black and bloody pustules, rotted skin and open sores";
      break;
      case 81..90:
      view = "covered with rotting skin and open black sores";
      break;
      case 51..80:
      view = "covered with foul black sores and pale as a ghost";
      break;
      case 21..50:
      view = "covered with foul sores and horribly pale";
      break;
      case 15..20:
      view = "looking very pale and sickly";
      break;
      case 10..14:
      view = "looking rather pale";
      break;
      case 6..9:
      view = "looking pale";
      break;
      case 1..5:
      view = "looking somewhat pale";
      break;
      default:
      view = "looking pale and sickly";
   }
   return view;
}

