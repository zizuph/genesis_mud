inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";


#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#define NF(str) notify_fail(str)
#define TP this_player()
#define TO this_object()
#define NUM sizeof(query_money_types(-1))
#define BS(xxx) break_string(xxx,68)
#define CLOSED 0/* 1 = closed,   0 = open.  */
#define PATH "/d/Terel/mecien/valley/city/"

int closed;
object meditate;


object mon;

reset_room(){
  if(mon) return;
  mon = clone_object(PATH + "gmaster");
  mon->move(this_object());
}

create_room() { 
   
   create_skill_raise();
   create_guild_support();
   closed = CLOSED; 
   
  set_short("Hall of Mastery");
  set_long(
  "This great building seems to be a training center for various skills " +
"and abilities. From its rafters hang ropes, tools and various other " +
"pieces of equipment. Tables are spread out, with writings, maps and "
+"drawings available.\n"
);

add_item("rafters", "they are wooden beams in the ceiling.\n");
add_item("ropes", "Most likely used for training to climb.\n");
add_item("maps", "They show various terrains and landscapes.\n");
add_item("writings", "They contain special knowledge for those that train here.\n");
add_item("tools", "There are dozens of them, for the many skills taught here.\n");
add_item("equipment", "All used in training.\n");
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   add_exit(PATH + "street13", "west", 0);
   
   
   set_up_skills();
  reset_room();
}

wizinfo() {
   return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   /Styles.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   
   if (!query_ip_number(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Genesis/start/human/town/road3");
   }
}


init() {
   if(present("guild_master")){
    init_skill_raise();
    init_guild_support();
   ::init();
   }
}

close_guild() {
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() { return closed; }

set_up_skills() {
   
   /* Add skill that can be trained. Do not add all skills, and vary a bit */
   
   sk_add_train(SS_WEP_SWORD,  train_text(SS_WEP_SWORD)[0],     0,0,30 );
   sk_add_train(SS_WEP_MISSILE,train_text(SS_WEP_MISSILE)[0],   0,0,20 );
   sk_add_train(SS_WEP_AXE,    train_text(SS_WEP_AXE)[0],       0,0,30 );
   
   sk_add_train(SS_HUNTING, train_text(SS_HUNTING)[0],    0,0,20 );
   
   sk_add_train(SS_APPR_MON,train_text(SS_APPR_MON)[0],      0,0,40 );
   sk_add_train(SS_APPR_OBJ,train_text(SS_APPR_OBJ)[0],      0,0,40 );
   
   sk_add_train(SS_TRACKING,train_text(SS_TRACKING)[0],      0,0,50 );
   sk_add_train(SS_CLIMB,train_text(SS_CLIMB)[0],         0,0,50 );
   sk_add_train(SS_ANI_HANDL,train_text(SS_ANI_HANDL)[0],     0,0,30 );
   sk_add_train(SS_AWARENESS,train_text(SS_AWARENESS)[0],     0,0,25 );
   sk_add_train(SS_LOC_SENSE,train_text(SS_LOC_SENSE)[0],     0,0,30 );
   sk_add_train(SS_SWIM, train_text(SS_SWIM)[0],    0,0,30);
}

train_text(skill) {
   string what, does, *text;
   
   switch(skill) {
      case SS_WEP_SWORD:
      what="use a sword";
      does = what;
      break;
      case SS_WEP_MISSILE:
      what="use a bow and arrows";
      does = what;
      break;
      case SS_WEP_AXE:
      what="use an axe";
      does = what;
      break;
      
  case SS_SWIM:
    what = "swim";
      case SS_SPELLCRAFT:
      what="hunt an enemy";
      does = what;
      break;
      
      case SS_APPR_MON:
      what="appraise your opponents";
      does = what;
      break;
      case SS_APPR_OBJ:
      what="appraise different objects";
      does = what;
      break;
      case SS_TRACKING:
      what="tracking";
      does = what;
      break;
      case SS_CLIMB:
      what="climb walls and mountains";
      does = what;
      break;
      case SS_ANI_HANDL:
      what="animal handling";
      does = what;
      break;
      case SS_AWARENESS:
      what="be aware of your surroundings";
      does = "be aware of "+ TP->query_possessive() +" surroundings";
      break;
      case SS_LOC_SENSE:
      what="sense of location";
      does = what;
      break;
      
      case SS_HUNTING:
      what="hunt";
      does=what;
      break;

      default:
      what="do nothing. THIS IS A BUG";
      does = "meditate";
      break;
   }
   text = ({what, does});
   return text;
}


