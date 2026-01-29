inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0
int closed;
object meditate;
create_room() 
{
   ::create_room();
   closed = CLOSED;
   set_short("Merchants of Kabal Training Room");
   set_long("You're within the training room of the Merchants Guild of Kabal.\n");
   add_item(({"carpet"}),
      "It looks quite comfortable.\n");
   INSIDE;
   hear_bell = 1;
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_prop("_room_has_fire",1);
   add_exit(CVAN(guild/joinroom),"west",0,-1,-1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
}
wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Anth.\n");
}
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\n\WARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/caravan/guild/joinroom");
   }
}
init() {
   init_guild_support();
   init_skill_raise();
   ::init();
}
close_guild() {
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}
query_closed() {return closed;}
set_up_skills() {
   sk_add_train(SS_WEP_KNIFE, train_text(SS_WEP_KNIFE), 0,0,50);
   sk_add_train(SS_PICK_POCKET,   train_text(SS_PICK_POCKET),      0,0,30);
   sk_add_train(SS_HIDE,   train_text(SS_HIDE),      0,0,40);
   sk_add_train(SS_SNEAK,   train_text(SS_SNEAK),      0,0,40);
   sk_add_train(SS_ANI_HANDL, train_text(SS_ANI_HANDL), 0,0,50);
   sk_add_train(SS_SWIM, train_text(SS_SWIM), 0,0,50);
   sk_add_train(SS_LOC_SENSE, train_text(SS_LOC_SENSE), 0,0,50);
   sk_add_train(SS_CLIMB, train_text(SS_CLIMB), 0,0,50);
   sk_add_train(SS_TRADING,   train_text(SS_TRADING),      0,0,75);
   sk_add_train(SS_AWARENESS,   train_text(SS_AWARENESS),      0,0,50);
   sk_add_train(SS_DEFENCE, train_text(SS_DEFENCE), 0,0,30);
   sk_add_train(SS_PARRY, train_text(SS_PARRY), 0,0,30);
   sk_add_train(SS_LANGUAGE, train_text(SS_LANGUAGE), 0,0,50);
   sk_add_train(SS_APPR_OBJ, train_text(SS_APPR_OBJ), 0,0,50);
   sk_add_train(SS_APPR_VAL, train_text(SS_APPR_VAL), 0,0,50);
}
train_text(skill) {
   string what;
   switch(skill) {
      case SS_WEP_KNIFE:
      what="use a knife";
      break;
      case SS_PICK_POCKET:
      what="pick someone's pocket";
      break;
      case SS_HIDE:
      what="hide";
      break;
      case SS_SNEAK:
      what="sneak";
      break;
      case SS_ANI_HANDL:
      what="handle and manipulate animals";
      break;
      case SS_SWIM:
      what="swim";
      break;
      case SS_LOC_SENSE:
      what="not get lost during trading runs";
      break;
      case SS_CLIMB:
      what="climb";
      break;
      case SS_TRADING:
      what="get a good bargain for goods sold";
      break;
      case SS_AWARENESS:
      what="notice things in your environment";
      break;
      case SS_DEFENCE:
      what="defend against irate customers";
      break;
      case SS_PARRY:
      what="parry with a weapon against armed and irate customers";
      break;
      case SS_LANGUAGE:
      what="understand foreign tongues";
      break;
      case SS_APPR_OBJ:
      what="appraise the value of an object";
      break;
      case SS_APPR_VAL:
      what="appraise an item's value";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}
void
gs_hook_start_meditating()
{
   write("You kneel down at the shrine to Ammercia and slowly drift into "+
      "a meditative trance. You block off your sense and concentrate upon "+
      "the intracacies of your mind. You can now <estimate> your different stats "+
      "and <set> the learning preferences at your own desire. Just <rise> when "+
      "you are done meditating.\n");
   say(QCTNAME(TP) + " kneels down before the shrine to Ammercia.\n");
}
int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness. You exhale and feel very relaxed as\n" +
      "you get up and leave the shrine.\n");
   say(QCTNAME(TP) + " rises from the shrine.\n");
}
