/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP this_player()
#define TO this_object()
#define MYS_SKILL       130001
#define ENV environment
#define GIFT "/d/Terel/mecien/valley/guild/spells/gift/"

donum(){
   
   object me;
   
   me = TP;
   
  if(TP->query_mana() < 100) return "You do not have the strength.\n";
  if(TP->query_skill(SS_FORM_CONJURATION) + random(100) <
  100) return "You fail to make your cry heard.\n";
   tell_room(ENV(TP), TP->query_name() + " clutches " + TP->query_possessive() + 
      " amulet in " + TP->query_possessive() + " hands and cries out in a loud voice!\n", TP);
   TP->catch_msg("You invoke the name of your chosen spirit.\n");
   set_alarm(3.0, -1.0, "fall", me);
  set_alarm(6.0, -1.0, "dread", me);
   switch(me->query_skill(MYS_SKILL))
   {
      case 1:
      set_alarm(9.0, -1.0, "gift1", me);
      break;
      case 2:
      set_alarm(9.0, -1.0, "gift2", me);
      break;
      case 3:
      set_alarm(9.0, -1.0, "gift3", me);
      break;
      case 4:
      set_alarm(9.0, -1.0, "gift4", me);
      break;
      case 5:
      set_alarm(9.0, -1.0, "gift5", me);
      break;
      case 6:
      set_alarm(9.0, -1.0, "gift6", me);
      break;
      case 7:
      set_alarm(9.0, -1.0, "gift7", me);
      break;
      case 8:
      set_alarm(9.0, -1.0, "gift8", me);
      break;
      case 9:
      set_alarm(9.0, -1.0, "gift9", me);
      break;
      case 10:
      set_alarm(9.0, -1.0, "gift10", me);
      break;
      case 11:
      set_alarm(9.0, -1.0, "gift11", me);
      break;
      case 12:
      set_alarm(9.0, -1.0, "gift12", me);
      break;
   }
   return 1;
}

fall(object me){
   tell_room(ENV(me), me->query_name() + 
      " falls down upon " + me->query_possessive() +
      " knees and wraps " + me->query_possessive() + 
      " mantle over " + me->query_possessive() + " eyes.\n");
   me->catch_msg("You drop to your knees and cover your face with " +
      "your mantle, awaiting the approach of the ancient powers.\n");
   
}

dread(object me){
   tell_room(ENV(me), "You sense the approach of something terrifying!\n");
}

gift1(object me){
   
   object gift;
   
   seteuid(getuid());
   tell_room(ENV(me), "A brilliant burning circle fills the air, it churns and flares like a fiery nova!\n");
   gift = clone_object(GIFT + "disk");
   gift->move(me);
   me->catch_msg("A fiery disk appears in your hand!\n");
   return 1;
}

gift2(object me){
}

gift3(object me){

}

gift4(object me){
  object ob;
}




