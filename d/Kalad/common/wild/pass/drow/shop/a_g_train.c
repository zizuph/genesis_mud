inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
#define NUM sizeof(query_money_types(-1))
#define CLOSED 0
int closed;
object meditate;
create_room() 
{
   ::create_room();
   closed = CLOSED;
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   set_short("The Adventurers' Guild Training Room, Undraeth");
   set_long("This darkened, quiet room is the training area for the "+
      "Adventurers' Guild of Undraeth. Here you may learn new skills or "+
      "try and improve on your existing ones, for a price. Spread out on "+
      "the floor is a large black silk carpet. Off to one corner is a set "+
      "of spiraling stairs leading down.\n"+
      "A golden brazier stands here.\n");
   add_item(({"darkened room","quiet room","room"}),
      "It is where you are, have a look around.\n");
   add_item(({"floor","ground","walls","wall","ceiling"}),
      "It is fashioned from the dark rock common to the Dark Dominion.\n");
   add_item(({"large black silk carpet","large carpet","black carpet","silk carpet","carpet"}),
      "Its incredibly smooth texture makes it the perfect tool for meditation.\n");
   add_item(({"corner"}),
      "A set of stairs lie there.\n");
   add_item(({"set","spiraling stairs","stairs"}),
      "It lies in the corner, leading down below.\n");
   add_item(({"golden brazier","brazier"}),
      "It provides a dim smoke-filled light for the room.\n");
   add_prop("_room_has_fire",1);
   add_exit(CPASS(drow/shop/adv_guild),"down",0,-1,-1);
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
      write("\n\nWARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/wild/pass/drow/shop/adv_guild");
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
   sk_add_train(SS_WEP_SWORD,   train_text(SS_WEP_SWORD),      0,0,30);
   sk_add_train(SS_WEP_KNIFE,   train_text(SS_WEP_KNIFE),      0,0,30);
   sk_add_train(SS_WEP_POLEARM, train_text(SS_WEP_POLEARM), 0,0,30);
   sk_add_train(SS_PICK_POCKET,   train_text(SS_PICK_POCKET),      0,0,20);
    sk_add_train(SS_HIDE, train_text(SS_HIDE), 0,0,20);
   sk_add_train(SS_SNEAK, train_text(SS_SNEAK), 0,0,20);
   sk_add_train(SS_CLIMB, train_text(SS_CLIMB), 0,0,30);
   sk_add_train(SS_TRADING,   train_text(SS_TRADING),      0,0,30);
   sk_add_train(SS_AWARENESS,   train_text(SS_AWARENESS),      0,0,30);
   sk_add_train(SS_TRACKING, train_text(SS_TRACKING), 0,0,30);
   sk_add_train(SS_HUNTING, train_text(SS_HUNTING), 0,0,30);
}
train_text(skill) {
   string what;
   switch(skill) {
      case SS_WEP_SWORD:
      what="use a sword";
      break;
      case SS_WEP_KNIFE:
      what="use a knife";
      break;
      case SS_WEP_POLEARM:
      what="use a polearm";
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
      case SS_CLIMB:
      what="climb";
      break;
      case SS_TRADING:
      what="get a good bargain for goods sold";
      break;
      case SS_AWARENESS:
      what="notice things in your environment";
      break;
      case SS_TRACKING:
      what="track things";
      break;
      case SS_HUNTING:
      what="hunt things";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}
