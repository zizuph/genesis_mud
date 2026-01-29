
/*   adv_guild.c    Styles   Wed Jan 22 1992
*
*   NOTE.
*   The player can't advance more than one level at the time.
*         This is intentional and not a bug. The players should
*   experience the effort of gaining each level. Thus they
*         will recieve each new rank that comes along with the level.
*
*   If the guild is closed you can toggle this by doing,
*   > Call here close_guild
*   This is a quick way to close/open it if needed
   *
*   /Styles.
*/



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
#define PATH "/d/Terel/common/town/street/"

int closed;
object meditate;


create_room() { 
   
   create_skill_raise();
   create_guild_support();
   closed = CLOSED; 
   
   set_short("Silver Hall");
   set_long("This is Silver Hall. It is the adventurer's haven in " +
      "Calathin. There is some equipment here for training skills " +
      "and learning. The hall is fashioned of a silver pine wood " +
      "that has been cut from the nearby forest.\n");
   
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   add_exit(PATH + "street1", "east", 0);
    add_exit("/d/Terel/calathin/obj/stadium","west",0);
   
   
   set_up_skills();
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
   
   if (!interactive(ob) || !closed)
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
    init_skill_raise();
    init_guild_support();
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

query_closed() { return closed; }

set_up_skills() {
   
   /* Add skill that can be trained. Do not add all skills, and vary a bit */
   
   sk_add_train(SS_WEP_SWORD,  train_text(SS_WEP_SWORD)[0],     0,0,20 );
   sk_add_train(SS_WEP_MISSILE,train_text(SS_WEP_MISSILE)[0],   0,0,10 );
   sk_add_train(SS_WEP_AXE,    train_text(SS_WEP_AXE)[0],       0,0,15 );
   
   sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT)[0],    0,0,10 );
   
   sk_add_train(SS_APPR_MON,train_text(SS_APPR_MON)[0],      0,0,30 );
   sk_add_train(SS_APPR_OBJ,train_text(SS_APPR_OBJ)[0],      0,0,30 );
   
   sk_add_train(SS_TRACKING,train_text(SS_TRACKING)[0],      0,0,30 );
   sk_add_train(SS_CLIMB,train_text(SS_CLIMB)[0],         0,0,30 );
   sk_add_train(SS_ANI_HANDL,train_text(SS_ANI_HANDL)[0],     0,0,30 );
   sk_add_train(SS_RIDING,train_text(SS_RIDING)[0],     0,0,30 );
   sk_add_train(SS_AWARENESS,train_text(SS_AWARENESS)[0],     0,0,25 );
   sk_add_train(SS_LOC_SENSE,train_text(SS_LOC_SENSE)[0],     0,0,30 );
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
      
      case SS_SPELLCRAFT:
      what="use spellcraft";
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
      case SS_RIDING:
      what="ride a steed";
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
      
      default:
      what="do nothing. THIS IS A BUG";
      does = "meditate";
      break;
   }
   text = ({what, does});
   return text;
}


